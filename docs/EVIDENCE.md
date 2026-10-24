# Evidence and reproduction

How the claims in these documents were produced, and how to reproduce them.

## 1. Method

Two independent paths, deliberately kept separate so they can cross-check each other.

**Path A — passive capture.** A Meta 2 was attached to a Windows 10 1809 virtual machine
running the vendor's Meta SDK 2.7.0.38 and its sample reader. While that software
streamed, the host captured every USB transfer on the physical bus via `usbmon`. This
gives the vendor software's real command sequence and real endpoint behaviour, without
interpreting anything.

**Path B — active probing.** The device was released from the VM and driven directly from
a Linux host with pyusb/libusb only. No Meta SDK, no Windows, no vendor driver. Every
register value in `04-register-map.md` and every "verified against a live device" claim
comes from this path.

A claim is only marked `[VERIFIED]` if Path B reproduced it against the device, or if it
is a direct arithmetic/statistical fact computed from a named artifact.

## 2. Artifacts

| Artifact | What it is |
|---|---|
| `data/ctrl_seq_full.json` | The complete captured start-up control sequence: 417 transfers, 138 OUT + 279 IN, in wire order, with payloads. Source for the handshake statistics in 3.1–3.2. |
| `data/vendor_out_seq.json` | The 131 OUT transfers whose payloads were recoverable, with `wValue`/`wIndex`/`wLength`. |
| `data/vendor_in_responses.json` | Live IN responses read from the device: `[sequence_index, wValue, wLength, hex]`. Source of the register table. |
| `data/ep81_record0.hex` | First 256-byte EP 0x81 record, hex dump. Source for the layout in 5.2. |
| `data/ep84_head.hex` | EP 0x84 header and trailer regions, hex dump. Source for 5.4. |
| `data/strip_chunk0.png`, `strip_chunk1.png` | 1280×25 images rendered from raw EP 0x83 samples. Visual proof of the 1280 stride. |

Large raw captures (a 21.7 MB `pcapng` of 147,874 USB frames, a 7.5 MB EP 0x81 stream, an
8.1 MB EP 0x83 burst) are not committed here; the statistics derived from them are quoted
inline with their counts so they can be checked against whatever you capture yourself.

## 3. Reproducing the passive capture

The rig itself - QEMU configuration, Windows 10 1809 install, SDK install, reader build,
how to find the right `usbmon` device, and how to hand the device between the VM and the
host - is documented in [appendix-capture-rig.md](appendix-capture-rig.md). The commands
below assume that rig exists.


```sh
# host side: capture the bus the device sits on (bus 4 = XHCI 07:00.0 here)
dumpcap -i usbmon3 -i usbmon4 -a duration:45 -w /tmp/meta2_trace.pcapng

# while that runs, run the vendor reader in the VM (foreground, blocking)
ssh -p <port> <user>@<vm> 'C:\MetaReader\MetaReader.exe C:\MetaReader\OUT 40'
```

Then extract control transfers:

```sh
tshark -r meta2_trace.pcapng -Y 'usb.transfer_type==0x00 && usb.device_address==2' \
       -T fields -e frame.number -e usb.urb_type -e usb.bmRequestType \
       -e usb.setup.bRequest -e usb.setup.wValue -e usb.setup.wIndex \
       -e usb.setup.wLength
```

**tshark 4.4 gotchas that cost real time, recorded so you do not repeat them:**

- `frame.raw` is not a valid field. Use `-V` verbose dissection instead.
- `-T fields` aborts the whole extraction if *any* listed field name is invalid.
- `-c N` truncates **before** the `-Y` filter is applied, so `-c 1 -Y '...'` returns
  nothing. Never combine them.
- Control payloads appear in `Data Fragment` under `-V`, not in `usb.capdata`
  (`usb.capdata` is empty for control transfers in this trace).
- Correct setup field names: `usb.setup.bRequest`, `usb.setup.wValue`,
  `usb.setup.wIndex`, `usb.setup.wLength`. `usb.setup.bmRequestType` does not exist;
  use `usb.bmRequestType`.
- `usb.urb_type` prints with quotes; naive equality filters silently return nothing.
- Raw `usbmon` binary traces on kernel 6.12 use the **48-byte API0** record header
  (`PKT_SZ_API0 48`), not 56 or 64. API0 has no `data_flag` field; API1 does.
- URB ids are **not unique** — the kernel reuses them. Pair SUBMIT/COMPLETE by frame
  sequence or timestamp, never by URB id. Frame numbers are unique.

## 4. Reproducing the active probing

```sh
# release the device from the VM (QEMU, device added with an explicit id)
echo '{"execute":"qmp_capabilities"}{"execute":"device_del","arguments":{"id":"meta2usb"}}' \
  | socat - UNIX-CONNECT:/tmp/meta2vm.qmp

# confirm it is on the host bus
lsusb | grep 2cfa

# run the documented example
cc -O2 -Wall -o meta2_probe examples/meta2_probe.c $(pkg-config --cflags --libs libusb-1.0)
sudo ./meta2_probe
```

To give the device back to the VM, re-add it with the same id, or restart the VM launcher.

## 5. Methods that do not work here

Recorded because they look reasonable and produce confident-looking numbers.

**Row-boundary discontinuity test — invalid on this data.** For a candidate width `W`,
compare `mean |v[i]-v[i+1]|` at row boundaries (`i+1 ≡ 0 mod W`) against within-row
positions. Tested as a control against EP 0x83, whose stride 1280 is independently
established: the method ranked 1280 at **3692 of 3969 candidates** and instead promoted
2363, 3199 and 4096 — artefacts of small sample counts at large `W`. Do not use it. The
autocorrelation lag scan (5.3, 5.4) is the method that works, and it must be reported
against a random-pair baseline, not in absolute terms.

## 5i. Enable masks, reader back-pressure, mono framing — VERIFIED

`re/capture_mask.py` screening table, the all-four-readers requirement, the hysteretic state across
port reset, the warm-up-mask control of framing quality, the exact-frame mono renderer, and the
negative mic result are all in `docs/10-enable-masks.md` §10.1–§10.5.

## 6. Claims that are weaker than they look

Recorded explicitly, because a reader will build on these.

| Claim | Actual strength |
|---|---|
| "EP 0x83 is 1280-wide 16-bit image data" | Strong, and now **resolution is established too**: frame records are spaced by exactly 1,843,232 B = 1280×720×2 + 32, which only fits that geometry. `[VERIFIED]` |
| "EP 0x83 blocks are 65,536-byte acquisitions of 25.58 rows" | **Withdrawn 2026-10-16.** An artefact of URB size in a handshake-then-read client. See 5.3. |
| "Continuous streaming is not achievable without the SDK" | **Withdrawn 2026-10-16.** It was a client defect: no URB pending during control traffic. See 7.1. |
| "EP 0x84 is depth" | `[INFERRED]`. The 12-bit sentinel and smoothness support it; no stride was found and no unit mapping exists. |
| "The register space is contiguous" | **Withdrawn.** See 3.5. A wide read returns a device-chosen span whose base is not the requested address. |
| "All 138 OUT commands accepted" | True for the sequence as captured. 7 of the 138 had no recoverable payload, so those were replayed as zero-length OUTs — which may not be what the device actually received. |
| "45 slots, all absent" | True for the one capture analysed (29,462 records). Never observed populated. |
| "The device needs SuperSpeed" | Descriptor fact is `[VERIFIED]`; the practical consequence is `[INFERRED]` from `bFunctionalitySupport`. |
| "The identity string is the SDK's serial number" | `[INFERRED]`. The reader queried it before the device had it ready and logged empty. |
| "Data flows only while control transfers run" | **Narrowed 2026-10-16.** True from a quiescent device. A device left armed by an earlier session produced 304 frame records (30.35 fps) on EP 0x83 during a 10 s window with zero control transfers. See 7.1. |
| "The 4-command set streams at 30 fps" | 30 **records** per second, not 30 complete frames. In a 30 s capture, 332 of 975 record gaps are shorter than 1,843,232 B while every counter still advanced by 1. Complete-frame ceiling ≈ 27.7 fps. See 5.7. |
| "Time-to-silence identifies a reset action" | **Withdrawn 2026-10-16.** Measuring silence *after* the arm sequence has finished measures the client, not the device: doing nothing and applying the candidate both reported 5.0 s, because the stream had already stopped on its own. Silence is only meaningful while sustaining traffic is running. |
| "EP 0x83 is the RGB camera" | **Withdrawn 2026-10-16, then reinstated the same day — and it was right for the wrong reason both times.** The original support (a mean-brightness match) identified nothing. The withdrawal rested on a bit-group coherence test that read the payload as 16-bit samples; the payload is **YUV422**, so every little-endian u16 is `chroma | luma<<8` — the test saw the luma in the high byte and called the chroma "noise". The decompiled driver names `0x83` `RGBCameraEndPoint` → `YUV422Image(1280, 720)`, and a 4-byte phase analysis separates luma (slots 1, 3; std 48.6; mutual correlation 0.992) from chroma (slots 0, 2; mean 128.05/126.71; std 4.5). `[VERIFIED]` See 09 §9.4. |

| "No bulk endpoint carries colour data" | **Withdrawn 2026-10-16 (latest).** Followed from the same misreading. EP 0x83 carries chroma on the wire: decoded to RGB, 11% of pixels have channel spread > 20, maximum 189. The Bayer and channel-sequential tests were correct — the format is neither — but "therefore monochrome" did not follow. See 09 §9.4. |

| "EP 0x84 has no spatial coherence in any candidate geometry" | **Reinstated 2026-10-16 (latest).** It was withdrawn earlier the same day on a bad comparison: the "random baseline" was drawn uniformly over the whole 12-bit range while the payload lives in a ~140-level band, so the 36× ratio measured histogram width, not structure. Against a permutation baseline (same pixels, same histogram) EP 0x84 is 1.0× — no coherence. The original 08 §5.4 measurement, which used a matched random-pair baseline and also got ratio 1.000, was right. `[VERIFIED]` See 09 §9.6. |

| "EP 0x81 is a 45-slot status table with all slots absent; 233 constant bytes per record means it is not sensor data" | **Withdrawn 2026-10-16 (latest).** EP 0x81 is the multiplexor: IMU0 (`0x77`), IMU1 (`0x66`), microphones (`0x88`), buttons (`0x99`). The 24 byte positions that vary across 2,875 records are the record tag, `GyroscopeX/Y/Z` at header+30, `AccelerometerX/Y/Z` at header+38, the trailer timestamp and the packet counter. Both IMUs decode with gravity visible (\|a\| ≈ 16,360 and 17,043 counts at rest). The `0xDADDF00D` value read as an "absent" sentinel is the trailer's `FixedSentinelLow`. `[VERIFIED]` See 09 §9.7. |

| "EP 0x82's A/B pair is 2,032 samples per acquisition, frames displaced by ~223 samples" | **Withdrawn 2026-10-16 (latest).** A 4,096-byte URB is a *fragment* of a 752 × 480 `GrayScale16` frame, not an acquisition. Split by tag and stripped of trailers, EP 0x82 yields 5.76 complete frames per 4.16 MB with a trailer delta of exactly 721,952 = 752×480×2 + 32, and coherence 27–52× better than random. `[VERIFIED]` See 09 §9.5. |

| "The register protocol (`3D \| op \| addr \| data`) is how the driver talks to the device" | **Narrowed 2026-10-16.** The decompiled driver never sends that shape. It sends whole-command requests (`0xC0`/`0xC1`/`0xB9`/`0xC2`) with short payloads, e.g. `[0, 4, 0, 0, 0, 0x7E]` for the endpoint feed. The register layer and the command layer are separate, and how they relate is `[UNKNOWN]`. See 09 §9.8, §9.11. |
| "EP 0x83's 16-bit samples mean 16-bit dynamic range" | **Narrowed 2026-10-16.** Effective depth measured ~5 bits: `hi5` std 4.71–6.10 on a 0–31 scale, `mid6` std 18.37–18.41 against 18.47 for a uniform field. The low 11 bits are noise. See 1.6a. |
| "The 27-command tail set is the sustaining set to minimise" | **Superseded 2026-10-16.** A 4-command strobe was found behind a port reset. The 27-command numbers predate the reset and are not comparable. See 7.1c. |

## 7. Environment

- Host: Debian 13 (trixie), kernel 6.12.x, x86-64, XHCI USB 3 controller.
- libusb 1.0.28, pyusb, gcc 14.
- `tshark` / `dumpcap` 4.4.19.
- VM: QEMU 10.0, Windows 10 1809 build 17763, Meta SDK 2.7.0.38.
- Device firmware version: `bcdDevice 0.00` — the device reports no useful firmware
  version, so you cannot tell which firmware these results describe. `[UNKNOWN]`

## 8. Redactions

One deliberate redaction: the identity string returned by command class `0x0002` is
this project's own headset serial number. It has been replaced with `<unit-serial>` in
the documents, and in `data/vendor_in_responses.json` the corresponding bytes of that
one response have been replaced with `ff` padding (record length and structure are
unchanged; only the identifying bytes are removed). Nothing else in this repo is
redacted. No credentials, hostnames, IP addresses or SSH endpoints appear anywhere.

## 8b. Multiplexor claims withdrawn and reinstated (E3)

- **Withdrawn:** "microphone enable produces no data." The negative result came from
  reading EP 0x81 alone, which flushes a fixed ~645-record backlog and then stalls. With
  all four endpoints drained, MICS records (tag 136) appear at ~370/s carrying 176 bytes
  of audio each.
- **Withdrawn:** "mux tags are 102 = IMU0 and 119 = IMU1." The vendor's `DataScanner`
  tests 119 for IMU0 and 102 for IMU1.
- **Reinstated as measured:** the 212-byte payload region is a slot table, 45 slots of
  `[index, ff, ff, ff]` in IMU records, replaced by 176 bytes of audio in MICS records.
- **Open, not resolved:** the microphone sample rate is measured at 8,405 samples/s, but a
  played 1 kHz tone appears at 240.6 Hz in that stream. No explanation is offered.

## 9. What was not available

A web search for the Meta 2's published hardware specifications returned **no results**
from the configured search backend while these documents were written. No external
specification is cited anywhere in this repo. Every claim is device-derived. If you have
the vendor's published specs, reconcile them against `01-device.md` section 1.6.

## 10. IR / ToF enable experiments (IR-1, IR-4, IR-6, IR-7)

Artifacts, all local to the working tree and not published because they contain raw camera
data or host-specific paths:

| artifact | what it is |
|---|---|
| `ir4.pcap` | 6,287,126 B `usbmon` capture, snaplen 1024, covering a forced re-enumeration plus a 20 s SDK run |
| `ir4_ctrl.tsv` | 1108 control URBs extracted by `tshark -T fields` |
| `ir4_driver_arm.txt` | 405 control transfers (134 OUT, 271 IN) rebuilt from that capture, in the library's arm-file format with decimal fields |
| `ir6_b800.json` | register read-backs of `0xb800`, `0xb880`, `0xb900`, `0xb980` before and after the SDK's 920-byte blob write |
| `ir7_ep84_min2.bin`, `ir7_ep84_blob.bin` | 12 s EP 0x84 captures, strobe only vs strobe plus blob |

Claims withdrawn or corrected in this round:

- **Withdrawn:** "no IR illumination observed from the headset" (§12.7). The emitter lights,
  and it is gated on the vendor SDK running, 2/2 coached cycles.
- **Withdrawn:** "every coordinate is `0.0000` in all 29 captured point clouds" as a general
  statement. True for run `live3`; later runs contain 11 and 103 non-zero coordinates out of
  1,313,312 and 5,556,320. §12.6.
- **Withdrawn:** "the emitter enable may happen during first enumeration, before our capture
  started." The vendor driver sends no vendor control transfers at all during enumeration.
  §12.11.
- **Corrected:** the `wIndex` column of `arm_full.txt` is corrupt in 27 of 138 OUT lines;
  131 of 138 match a base-16 misparse of decimal-formatted tshark output. §12.12.
- **Corrected:** the lag-704 stride candidate for EP 0x84 gets −1.1 % and +3.5 % contrast at
  20 M samples. §12.11, and 7.5.

A measurement trap worth not repeating: `tshark -T fields` formats `usb.setup.wValue` as hex
but `usb.setup.wIndex` and `usb.setup.wLength` as decimal for this dissector. Parsing all of
them with one base silently corrupts half the table.

## 11. IR-8 / IR-9 — the armed state survives every reset short of a power-off (2026-10-21)

Two experiments were designed to ask whether our own command set drives the IR emitter, and
both were invalidated before they could answer it by the same discovery: the device has no
quiescent state reachable from the host.

IR-8 alternated `NO COMMANDS` / `COMMANDS ON` with the bulk readers pending throughout. It
produced `control transfers ok=45512 fail=0`, `EP 0x83 total = 13,363,052,544 B`,
`EP 0x84 total = 11,552,161,792 B`, `errors = 0` — and the `NO COMMANDS` phases streamed at
the same rate as the `COMMANDS ON` phases. The device had been left armed by the previous
run. `[CAPTURED]`

IR-8b added a USB port reset at the start of every phase so both conditions would be
symmetric. A smoke test of the reset path showed the premise was already dead: post-reset
with zero control transfers the device streamed EP 0x83 at 53.48 MB/s and EP 0x84 at
36.44 MB/s. `[CAPTURED]`

IR-9 used the one reset the host cannot fake — the operator physically removing and
reinserting the USB cable. The script timestamped the disappearance and reappearance
(`device GONE 05:32:00.611`, `device BACK 05:32:04.821`, gap 4.21 s) and opened the handle
10 ms after the device returned.

| phase | control transfers | EP 0x83 | EP 0x84 |
|---|---|---|---|
| COLD, 3 windows | none | 52.31, 55.58, 57.01 MB/s | 55.59, 43.69, 41.43 MB/s |
| STROBE ON, 4 windows | 15,500 accepted, 0 failed | 54.74, 56.60, 56.57, 55.78 MB/s | 43.05, 41.63, 47.96, 57.83 MB/s |
| STROBE OFF, 2 windows | none | 53.32, 55.18 MB/s | 56.60, 51.89 MB/s |

`[CAPTURED]` EP 0x84 mean sample stayed within 2041.17–2043.64 across all nine windows.

Claims established:

- **`libusb_reset_device` resets the link, not the device.** It remains the correct reset for
  making command sequences reproducible and it does not produce silence. `[VERIFIED]`
- **sysfs `authorized` toggling does not produce silence.** `[VERIFIED]`
- **Physical USB removal does not produce silence.** `[VERIFIED]` The mechanism is not
  established: no power source has been observed on this device, and "it kept state because
  it has a battery" was an assumption imported from a different product, not a measurement.
  Candidate explanations — internal battery, always-on rail, stored charge, FX3 firmware
  state surviving a link disconnect — are all consistent with the data. `[UNKNOWN]`
- **In the armed state a reader needs no control traffic at all.** `[VERIFIED]`

Claims still open: whether the armed state can be exited at all by any means short of
whatever power control this device actually has (its physical power controls have not been
observed or documented), and therefore whether our command set drives the IR emitter.
Neither IR-8 nor IR-8b nor IR-9 answers that, and none of their light observations should be
read as evidence either way. `[UNKNOWN]`

Artifacts, local to the working tree: `ir8_stats.json`, `ir8b.log`, `ir9.log`,
`ir9_stats.json`, and the operator click logs `clicks_ir8.jsonl`, `clicks_ir8b.jsonl`,
`clicks_ir9.jsonl` written by `verify/coach_server.py`.

Two implementation traps recorded the same day:

- numpy dtype strings are byte widths: `<u16` is a 16-**byte** integer and raises
  `TypeError: data type '<u16' not understood`. A 16-bit little-endian sample stream is
  `<u2`.
- pyusb's `Device` has `reset()`, not `reset_device()`, and has no `close()`; dropping a
  handle is `usb.util.dispose_resources(dev)`.

## 12. IR-11 to IR-17 — register 0xb007, and a throughput claim that will not hold (2026-10-21)

### What the vendor SDK actually does at shutdown (IR-11) `[CAPTURED]`

`usbmon4` capture, snaplen 1024, forced re-enumeration, a 20 s `MetaReader.exe` run, and the
capture held open 20 s past the reader's exit. 134 vendor OUTs. The last two, 0.80 s and
0.75 s before the reader process exited:

```
wValue=0x0006 wIndex=6 wLength=6  payload 000400000000
wValue=0x0009 wIndex=4 wLength=4  payload 00000000
```

Those are the deassert halves of the two assert/deassert pairs our minimal sustaining strobe
loops. The SDK deasserts them and leaves them deasserted; we re-assert them every iteration.
**Zero vendor OUTs occurred after the reader process exited** — the teardown is explicit and
inside the process. One write, `3d40b0070040`, appears exactly once in the whole capture and
is never repeated; steady state uses `3d40b0070180`.

Static corroboration from the SDK binaries: `cyapi.dll` exports `CCyUSBDevice::PowerState()`
and `CCyUSBDevice::Reset()`; `meta2_host_itf.dll` exports `System_RegisterPowerOff` on both
`DriverManagerAdapter` and `EventHandlerAdapter`. `[CAPTURED]`

### The lever is register 0xb007, but it is not a clean gate

Sending captured teardown candidates collapsed all four endpoints to 0.00 MB/s (IR-12). After
that collapse:

| action | result |
|---|---|
| minimal 4-command strobe, 5 s | ep81/82/83/84 all 0.00 MB/s |
| full 134-transfer vendor arm, 0 failures | all 0.00 MB/s |
| full arm + strobe, then one `3d40b0070180`, then strobe | ep82 114.47, ep83 98.39, ep84 97.69 MB/s |

`[CAPTURED]` A single write to 0xb007 restored data that neither the strobe nor the full arm
sequence could restore on its own.

Three follow-up attempts to show that the **value** written determines the state all failed
to reproduce (IR-13, IR-14, IR-15). IR-13 alternated 0x0180 and 0x0040 and got 0.00, 62.9,
62.9, 0.00, 0.00, 0.00 MB/s on EP 0x82 — which does not track the value. IR-14 wrote each
value once with no other traffic and got 0.00 MB/s in all 18 windows. IR-15 ran a defined ON
procedure and OFF procedure twice each and got OFF 0.01, ON 0.01, OFF 55.16, ON 0.01 MB/s.
`[CAPTURED]`

Those three runs share one methodological flaw that IR-9 and IR-12 do not: the bulk readers
were torn down and rebuilt for every measurement window. The original streaming finding is
that bulk URBs must already be pending while control traffic is in flight, so tearing readers
down mid-stream is precisely the condition to avoid. IR-16 removed that variable: one reader
set, opened once, never stopped; only the control traffic changed.

IR-16, 15 s phases, 5 s windows, EP 0x82 / 0x83 / 0x84 MB/s `[CAPTURED]`:

| phase | window 1 | window 2 | window 3 |
|---|---|---|---|
| strobe only | 0.00 / 0.00 / 0.00 | | |
| strobe + `0xb007=0x0040` | 6.32 / 1.31 / 8.14 | 3.98 / 1.47 / 5.24 | 3.77 / 1.78 / 5.45 |
| strobe only | 0.05 / 0.13 / 0.01 | 0.00 / 0.00 / 0.00 | 0.00 / 0.00 / 0.00 |
| strobe + `0xb007=0x0180` | 4.19 / 2.52 / 5.66 | 4.40 / 1.47 / 6.08 | 4.61 / 1.68 / 6.71 |
| strobe only | 0.14 / 0.18 / 0.20 | 0.00 / 0.00 / 0.00 | 0.00 / 0.00 / 0.00 |
| no control at all | 0.00 / 0.00 / 0.00 | 0.00 / 0.00 / 0.00 | 0.00 / 0.00 / 0.00 |

In that state, **a write to 0xb007 on every loop iteration was necessary for any bulk data at
all**, and it produced data with either value. 4 of 4 no-0xb007 phases gave ~0; 2 of 2
with-0xb007 phases gave data. `[CAPTURED]`

### The throughput ceiling is not a device constant

A later probe with the same continuous-reader method measured, in 5 s windows:

```
arm + strobe + 0xb007=0x0180 :  ep82  3.98 ->  9.23 -> 14.68   ep83 2.10 -> 3.53 -> 6.47
arm + strobe (no 0xb007)      :  ep82 71.72 -> 135.06 -> 197.97 ep83 55.96 -> 111.12 -> 166.06
strobe + 0xb007=0x0180        :  ep82 203.21 -> 208.04 -> 213.91 ep83 167.53 -> 169.42 -> 171.30
```

`[CAPTURED]` Rates climbed monotonically inside a run and exceeded 200 MB/s per endpoint.
Minutes later, an otherwise identical capture measured 1.0–2.1 MB/s. **These numbers are not
reproducible across runs.**

**IR-18 (same day) shows those high numbers are not credible as payload.** Three checks:

1. **Not a read-size artifact.** 1 MiB reads, then 64 KiB reads, then 1 MiB again, all with
   the same continuous readers and the same control traffic: 13.8, 15.9 and 12.2 MB/s
   aggregate. The rate does not track our read size, so that explanation is dead. `[VERIFIED]`
2. **The aggregate exceeds the physical link budget.** That run reported ep82 213.91,
   ep83 171.30, ep84 199.86 MB/s simultaneously — 585 MB/s, i.e. 4.68 Gbps of payload through
   one SuperSpeed port. USB 3 SuperSpeed is 5 Gbps raw with 8b/10b encoding, so 500 MB/s is
   the payload ceiling **before any protocol overhead**. 585 MB/s is 17 % above an absolute
   ceiling. It cannot all be payload. `[VERIFIED]` arithmetic against the link rate; the
   5 Gbps / 8b/10b figure is general USB 3 specification, not derived from this device.
3. **Bytes and frames are decoupled.** In the same 15 s windows the device's own EP 0x83
   frame counters advanced 28428 → 28434, about 0.12 frames/s, while bytes flowed at
   13–16 MB/s aggregate. 200 MB/s would be 108 frames/s. The record markers in those captures
   had **zero** gaps of the expected 1,843,232 bytes. `[CAPTURED]`

Conclusion: our byte counter measures bytes the device sent, not imagery. In states where the
1,843,232 framing breaks, a byte counter will report whatever the device emits, including
re-sent or filler data, and it can exceed what the link can physically carry. **Throughput on
this device must be measured by counting complete frame records, not bytes.** The only rate
ever corroborated end to end is the 20 s video run: 500 complete 1280×720 frames in 19.889 s
= 25.1 fps = 46.3 MB/s of useful payload, verified by `ffprobe` and by rendered, playable
frames. `[VERIFIED]`

Consequently the previously recorded "device-side ceiling of ~51 MB/s on EP 0x83", the derived
"~27.7 complete frames/s ceiling", and the statement that concurrent transfers do not scale
are **not established as device constants** — they were measurements of one device state. But
IR-18 discredits the high numbers that replaced them, so the correct position is: **~46 MB/s
of useful EP 0x83 payload at ~25 complete frames/s is the only corroborated rate**, it is
consistent with the link budget, and whether it is a hard ceiling or merely what that state
produced remains `[UNKNOWN]`.

The EP 0x83 full-frame model also did not hold in the low-rate capture taken afterwards: 12.6
MB of EP 0x83 contained 6 record markers with gaps of 1,048,576 (×4) and 4,194,304 (×1), and
**zero** gaps of the expected 1,843,232. `[CAPTURED]` The frame model established in 5.4 is
therefore state-dependent, and which states produce it is `[UNKNOWN]`.

### Device health

After every experiment above, the headset was re-attached to the VM and run under the vendor
SDK: `Done: rgb_frames=45 pclouds=10 polls=381`. The device is not damaged and the vendor
stack still works. `[VERIFIED]`

### What is not claimed

- That the value written to 0xb007 selects a specific stream configuration. Not shown.
- What state the device is in, or what moves it between states. Unknown.
- Any throughput figure. The only honest statement is that the rate is state-dependent and
  currently unpredictable, spanning 0 to >200 MB/s per endpoint.
- Anything about the emitter. IR-8, IR-8b and IR-9 were invalidated and their light
  observations are not evidence.

Artifacts, local to the working tree: `ir11.pcap`, `ir11_ctrl.tsv`, `ir12_results.json`,
`ir13_results.json`, `ir13_ep83_sample.bin`, `ir14_results.json`, `ir15_results.json`,
`ir16_results.json`, `ir17_ep83.bin`, and the scripts `ir11_teardown.sh`, `ir12_disarm.py`,
`ir13_b007.py`, `ir14_b007_timeline.py`, `ir15_onoff.py`, `ir16_continuous.py`.

## 13. IR-21 to IR-23 — the Windows driver's identity, a second command family, and a capture route that does not exist

**The Windows driver is stock Cypress, not Meta code.** `[VERIFIED]` read from the guest's
device properties: service `CYUSB3`, INF `oem2.inf`, provider "Meta Company", driver version
**1.1.1.19**, device class "AR Experience Devices", parent `USB\ROOT_HUB30\4&1760152&0&0`.
`cyapi.dll` is the matching Cypress user-mode companion. This matters for the driver goal:
the kernel side of the vendor stack is a generic FX3 driver, so nothing Meta-specific sits
between the function driver and the wire.

**The vendor interface DLL has an explicit LED and ToF configuration path.** `[VERIFIED]`
from the export tables. `meta2_host_itf.dll` exports `ConfigureLed(...)`,
`ConfigureTofCamera(...)`, `ConfigureRgbCamera(...)`, `ConfigureMonoCameras(...)`,
`ConfigureRawImu(...)`, `ConfigureFusedImu(...)`, `ConfigureMic(...)`,
`ConfigureThermometers(...)` and `ConfigureButton(...)` on both `DriverManagerAdapter` and
`InitConfigAdapter` (namespace `sdc`), plus a `Data_RegisterNewFarDepthFrame` event.
`meta2_host_impl.dll` exports `ConfigureLed@InitConfigImpl@sdc` taking a `LedConfig*`, and
`SetExposure` / `GetExposure` on `SAQDriverManagerAdapterCls`. `royale.2.3.1.dll` carries
`IlluminationConfig`, `UseCaseTwoPhase`, `UseCaseFourPhase`, `UseCaseEightPhase`,
`ExposureGray`, `IntensityPhaseOrder` and `AutoExposureRefAmplitude_Float`. So the vendor
stack names the illumination and ToF configuration objects directly. **No command has yet
been attributed to `ConfigureLed` or `ConfigureTofCamera`.** `[UNKNOWN]`

**`meta_core_api.dll` exposes no CPU-readable ToF buffer.** `[VERIFIED]` all 63 exports were
listed. The only depth-related exports are `meta_get_eye_depth_stencil` and
`meta_get_eye_depth_stencil_texture`, and the `DXCompositor` exports
`GetDepthStencilViewForLeftEye` / `...RightEye` returning `ID3D11DepthStencilView*` — GPU
resources, not host buffers. There is no `meta_*` getter for raw ToF frames.

**SET_INTERFACE is never used.** `[VERIFIED]` zero transfers with `bRequest == 0x0B` in the
full 40 s SDK capture (`ir11.pcap`, 1084 control transfers). The FX3 alternate-setting
hypothesis for the emitter is therefore not the mechanism. The only non-vendor requests the
vendor stack sends are `SET_CONFIGURATION` (`bRequest 9`) and `SET_FEATURE` (`bRequest 3`) at
each attach, plus `bmRequestType 0x00 bRequest 0x30` with a 6-byte payload `550055000000`
and `bmRequestType 0x00 bRequest 0x31 wValue 0x0028`, both at every attach and neither
dissected by tshark; they occur before any vendor app runs, so they are not the emitter
enable. Their meaning is `[UNKNOWN]`.

**There is a second vendor command family that `MetaReader.exe` never sends.** `[CAPTURED]`
IR-21 ran `Meta.SystemTray.exe` in the guest while host `usbmon4` recorded control transfers
(`ir21_meta.systemtray.pcap`, `ir21_meta.systemtray_ctrl.tsv`). It sent 8 vendor OUTs, none
of which appear in the 134-command `MetaReader.exe` arm, and they do **not** follow the
`3D | op | addr16BE | data` grammar — the payload begins `13 00`:

```
wValue=0x0007 wIndex=1  wLength=0   (no data stage)
wValue=0x0005 wIndex=2  wLength=2   00 74
wValue=0x0002 wIndex=40 wLength=40  13 00 6d 00 00 ...
wValue=0x0002 wIndex=40 wLength=40  13 00 6d 40 00 ...
wValue=0x0002 wIndex=40 wLength=40  13 00 06 d2 00 ...
wValue=0x0002 wIndex=32 wLength=32  13 00 ff 00 ...
```

**IR-22: that family is a teardown, not an enable.** `[CAPTURED]` `ir22_tray_led.py` kept one
process with continuous readers on EP `0x82/0x83/0x84` open for the whole run and varied only
the control traffic (the reader-churn trap from section 12 was avoided):

| phase | ep82 | ep83 | ep84 |
|---|---|---|---|
| STROBE ONLY | 8.51 MB/s | 2.95 MB/s | 13.52 MB/s |
| STROBE + TRAY CMDS | 0.04 MB/s | 0.65 MB/s | 3.02 MB/s |
| STROBE ONLY (after) | 0.00 MB/s | 0.00 MB/s | 0.00 MB/s |

`control transfers ok=13069 fail=0`. The `13 00` family collapses all three bulk endpoints
and strobe alone does not restore them. It is a stop/disconnect path, consistent with what a
system-tray app does to a device it is releasing. **It is not the IR emitter enable.**

**Recovery from that collapsed state works with the vendor driver's own arm.** `[CAPTURED]`
`ir23_capture_ep84.py` replayed `meta2lib/data/arm_driver.txt` verbatim (405 transfers,
`ok=274 fail=131` — the failures are vendor IN transfers, which stall unless armed by a
preceding OUT) followed by the 4-command strobe, and bulk data returned at 8.46 MB/s on
EP `0x84` with 40 complete 202,784-byte frame records and consecutive counters
(244310, 244311, 244312, 244314, 244315 …).

**IR-23: EP `0x84` decoded at 352 × 288 still shows no scene.** `[CAPTURED]` frames located
by the `baabedfe` record marker, payload 202,752 B = 352 × 288 uint16, rendered to PNG.
Per frame: mean 2079–2118, standard deviation 1630–2124, `0x0FFF` sentinel fraction
0.33–0.66 %. Frame 0 vs frame 1: mean |difference| 77.5, only 1.59 % of samples identical.
Vision assessment of the rendered frame: unstructured per-pixel speckle, no edges, no objects,
no depth gradient; the only organisation is **vertical column banding** (fixed-pattern) and a
**distinct brighter top row**, which is consistent with the already-recorded finding that row 0
is a special row. This is the third independent capture in which the ToF stream carries no
scene structure.

**A capture route we do not have.** Two facts that close off "record the wire while the vendor
SDK streams":

1. Host `usbmon` truncates bulk payloads. `[VERIFIED]` `ir11.pcap` contains 45,518 bulk
   transfers; the largest captured payload in the whole file is 256 bytes, and it came only
   from EP `0x81` (whose URBs are 256 bytes). Every `0x82/0x83/0x84` COMPLETE event was
   dropped. Control transfers are captured in full; bulk payloads are not.
2. USBPcap 1.5.4.0 does not capture live traffic in this QEMU/xHCI guest. `[VERIFIED]`
   installed in the Windows 10 1809 guest: driver package published (`oem3.inf`), service
   `USBPcap` created and set to boot-start, `UpperFilters = USBPcap` set on class
   `{36fc9e60-c465-11cf-8056-444553540000}`, `\\.\USBPcap1` opens, and the driver reports
   `Found standard HWID: USB\ROOT_HUB30&VID1B36&PID000D`. Capture during a 20 s
   `MetaReader.exe` run produced a **24-byte pcap** (global header only). Capture across a
   forced re-enumeration produced 400 bytes, all of them `--inject-descriptors` records at
   timestamp 0.000000. No live URB was ever recorded.

**Correction to a named target that does not exist.** `[CORRECTED]` `docs/12-tof-investigation.md`
listed `Diagnostics/Meta.SimpleDiagnostics.exe` and `Meta.DisplayManager.exe` as things to run.
Neither exists in the SDK. The actual contents of `Meta SDK2 Beta/Utilities` are
`firmware-update.exe`, `Meta.FirmwareUpdate.exe`, `Meta.OOBE.exe`, `Meta.SystemTray.exe`,
`WorkspaceHelper.exe`; `Apps` contains only `Eye Alignment`. The two firmware-update programs
have not been run and are out of scope: they are the SPI-flash path.

Artifacts, local to the working tree: `ir21_meta.systemtray.pcap`,
`ir21_meta.systemtray_ctrl.tsv`, `ir22_results.json`, `ir23_ep84/ep84.bin`,
`ir23_ep84/frame_00..07.ppm|.png`, and the scripts `ir21_apps.sh`, `ir22_tray_led.py`,
`ir23_capture_ep84.py`.

## 14. IR-24 to IR-28 — the protocol has more than one request code, and the device went into a state nothing host-side recovers

**The arm files were missing four transfers.** `[VERIFIED]` A census of every control transfer
in `ir11.pcap`, without filtering on `bRequest`, gives 138 vendor OUTs: 134 on `0xC0`, 2 on
`0xB8`, 1 on `0xC1`, 1 on `0xC2`. `ir26_build_full_arm.sh` regenerates the sequence with
`bRequest` explicit into `meta2lib/data/arm_full2.txt`; the old files carried only the 134.
Details of the three extra codes are in `03-control-protocol.md` §3.1.

**The stored arm sequences also carried the wrong field on IN transfers.** `[VERIFIED]`
`arm_driver.txt` writes `I <wValue> <wLength>`, and replayers fed that third number in as
`wIndex`. On the wire every vendor IN has `wIndex = 1` and `wLength` in
`{1, 3, 5, 9, 11, 13, 17, 19, 21, 38, 41, 149, 257}`. With the fields corrected
(`ir24_diag.py`): **134 of 134 OUTs accepted, 140 of 274 INs succeed, 134 stall** with
`Errno 32`. The stall count equals the OUT count, so each OUT arms one IN and the second IN of
the documented pair is not armed.

**`Meta.OOBE.exe` and `Eye Alignment.exe` send no vendor commands at all.** `[CAPTURED]`
IR-21 run against each (`ir21_meta.oobe.pcap` 3,652 B, `ir21_eyealignment.pcap` 6,187 B,
70 packets). `Eye Alignment.exe` was confirmed running (`tasklist` PID 4924, 44,920 K). Both
pcaps contain only enumeration traffic — `GET_DESCRIPTOR`, `SET_FEATURE`, `SET_CONFIGURATION`
and the `bRequest 0x30 / 0x31` pair. Combined with IR-21's `Meta.SystemTray.exe` result, every
vendor application available in the SDK has now been captured and none issues an enable command
that `MetaReader.exe` does not.

**The device entered a device-wide off state that no host-side procedure recovers.**
`[CAPTURED]` All of the following produced **0.00 MB/s on EP `0x82`, `0x83` and `0x84`**:

| procedure | result |
|---|---|
| full 138-OUT arm from `arm_full2.txt` | `ok=280 fail=140`, 0 bytes |
| 134-OUT `0xC0`-only arm | 0 bytes |
| 4-command sustaining strobe, 60 s | 0 bytes |
| positive control `3d40b0070180` | 0 bytes |
| each of the six tray commands individually (IR-28) | 0 bytes in all six windows |
| vendor SDK run in the guest, then handoff after it exits | 0 bytes |
| vendor SDK run in the guest, `device_del` **mid-run** so no teardown is sent | 0 bytes |

The vendor SDK sees the same condition: its own `status.csv` for that run reads
`device=2, connection=2` with an empty streams field, `pose.csv` is all zeros, and the run
wrote 17 point clouds and **no RGB frames** — against 68 RGB frames from a healthy run earlier
the same day. Kernel-side the device is normal: `4-1 2cfa:00f3 config=1 authorized=1
power=active`, no driver bound to interface `4-1:1.0`.

**`0xb007` no longer holds the steady-state value and a write to it does not stick.**
`[CAPTURED]` It reads `00 0040` — the teardown value that IR-11 saw exactly once at SDK exit —
not the `0x0180` used in steady state. Writing `3d40b0070180` returns success, the register
reads `07` one second later and `00 0040` five seconds later. `0xa886`, which read
`00 0000 015f 0001 0120` (the 352 × 288 geometry) in earlier sessions, reads `07 07 07 07` and
then `00 400000` on consecutive probes. Reads of `0x0006` (`00 07fd`) and `0x0009` (`00 080e`)
still succeed, so the control path is alive while the register contents are not stable.

**Consequence for the ToF goal.** No ToF frame has been captured since IR-23, and the reason is
not the emitter question — it is that the device is not streaming anything to anyone, including
the vendor SDK. The remaining known route back to a streaming state is a headset-side power
cycle, which is a physical action.

Artifacts, local to the working tree: `ir21_meta.oobe.pcap`, `ir21_eyealignment.pcap`,
`ir24_ep84/`, `ir25_ep84/results.json`, `ir26_ep84/`, `ir27_ep84/results.json`,
`ir28/results.json`, and the scripts `ir24_build_arm_wire.sh`, `ir24_diag.py`,
`ir24_replay.py`, `ir25_handoff_ep84.py`, `ir26_build_full_arm.sh`,
`ir26_full_arm_replay.py`, `ir27_handoff_midrun.py`, `ir28_tray_leave_one_out.py`.

## 15. IR-29 to IR-31 — a power cycle restores streaming, and the four extra request codes turn out to be a trap

**Cycling the headset's power (unplug / replug) is what recovers the off state of section 14.**
`[CAPTURED]` After the operator unplugged and replugged the unit, the device re-enumerated with a
new address (`Bus 004 Device 003`), the register reads returned to sane values (`0xC1/253` answered
`00 0106` = FX3 1.6, `0xC0/5` answered with a value, `0xb007` no longer latched at `0x0040`), and
`capture_mask.py 7e 1b 15` gave EP `0x82` 38.18 MB/s, EP `0x83` 58.28 MB/s with 471 complete
1,843,232-byte frames (99.8% of gaps), EP `0x84` 63.44 MB/s with 4,692 complete 202,784-byte
frames (100.0%). No host-side procedure had achieved that in section 14.

**A port reset before the arm is not the cause of an arm failure.** `[VERIFIED]` IR-30 ran four
phases alternating reset / no-reset with the same arm and the same reader setup:

| phase | ep82 | ep83 | ep84 |
|---|---|---|---|
| no reset | 54.75 | 58.58 | 71.71 MB/s |
| port reset | 64.14 | 46.84 | 11.35 MB/s |
| no reset again | 67.23 | 59.02 | 63.99 MB/s |
| port reset again | 105.3 | 101.7 | 71.96 MB/s |

All four streamed. Rates vary by a factor of ~9 between phases, which is the hysteresis already
recorded, not an arm failure.

**Replaying the `0xB8` / `0xC1` / `0xC2` transfers with their true request codes breaks the arm.**
`[VERIFIED]` IR-31 held the device, the readers and the sustaining strobe fixed and changed only
how the arm was sent:

| arm sent | ep82 | ep83 | ep84 |
|---|---|---|---|
| `ctrl_seq_full.json`, every OUT on `bRequest 0xC0` | 67.0 | 47.0 | 11.5 MB/s |
| `arm_full2.txt`, OUTs on their captured `bRequest` (`0xB8`/`0xC1`/`0xC2`) | **3.27** | **2.66** | **2.0** |
| `arm_full2.txt`, every OUT forced to `bRequest 0xC0` | 57.7 | 56.1 | 60.5 |

The two `arm_full2.txt` rows contain the same 138 OUTs and the same payloads; only the request
code differs. So the four transfers described in section 14 are **not part of the arming path**.
Read against the driver's own request constants they are a version query (`0xC1`/`wValue 253`,
which answers `00 0106`) and a device-file address lookup (`0xC2`/`wValue 4` with payload
`6877696e666f2e62` = ASCII `hwinfob`, i.e. the truncated name `hwinfo.bin`). Issuing them during
the arm puts the device in a degraded state. **The arming sequence is the 134 `bRequest 0xC0`
register transfers.** `[VERIFIED]`

**Consequence for `03-control-protocol.md` §3.1:** the four extra request codes are real traffic
the vendor driver sends, but a reader must not fold them into its arm sequence.

**EP `0x84` after recovery: stable, structured at the sensor level, still no scene.**
`[CAPTURED]` `capture_mask.py 48 1b 15` (`48` = ToF | STD) produced 4,934 complete frames in 15 s
= **328.9 frames/s**. Over 200 frames:

| measurement | value |
|---|---|
| mean / std | 2037.0 / 212.6 |
| samples in `[1920, 2176)` | **99.615 %** (12-bit mid-scale is 2047.5) |
| median | 2030 |
| `0x0FFF` sentinel fraction | 0.33 % overall; **94.60 % in row 0**, 0.00 % in rows 1+ |
| row 0 mean vs rows 1+ mean | 4031.5 vs 2030.1 |
| temporal per-pixel std | mean 3.47, median 2.95 |
| frame 0 vs frame 199 | mean \|diff\| 3.87, 10.22 % identical |
| corr(frame 0, temporal mean) | 0.991 |
| spatial coherence, permutation / real | 1.37 horizontal, 1.45 vertical |

The coherence ratio moved from 1.0x in the off state to 1.37 / 1.45 here, and the temporal noise
fell from ~13 to 3.47 counts, so the field is now stable and weakly structured. It is still not
scene data: the two orders of magnitude that separate it from the mono cameras (31x / 21x) are
absent, and vision assessment of both a single frame and the 200-frame temporal mean is
"speckle plus vertical column banding, no edges, no objects, no depth gradient". The column-mean
spread is 166.5 and the banding runs top to bottom, which is a readout fixed pattern.

**The value distribution is the sharpest statement available.** 99.615 % of all samples fall in a
256-count band centred on 12-bit mid-scale. A ToF phase output that was demodulating returned
light would spread across the range with depth. This is the quantitative form of the earlier
inference that the modulation is not running. `[CAPTURED]` mechanism `[UNKNOWN]`.

Artifacts, local to the working tree: `ir29_ep8{1,2,3,4}.bin`, `ir29_tof_ep8{1,2,3,4}.bin`,
`ir29_analysis/`, `ir30_results.json`, `ir31_results.json`, and the scripts
`ir29_cold_probe.py`, `ir29_analyse_ep84.py`, `ir30_reset_vs_noreset.py`,
`ir31_arm_variants.py`.

## 16. IR-32 to IR-37 — the register map becomes readable (2026-10-23)

> **Corrected in §17.** The heading of this section originally read "…and the `0xB8` family kills
> the device". That claim is **withdrawn**. §17 shows the device streaming normally after 1,056
> `0xB8` probes, and shows that the all-zero measurements which produced the claim were an artifact
> of a broken reader guard, not a device state.

### IR-33 — the first time any vendor IN payload was read

Every earlier statement about register values rested on our own live probes, because the
passive captures carry no control-IN data (§3.4). `re/ir33_register_dump.py` replayed the
captured arm and kept the IN bytes. `[CAPTURED]`

74 register-read OUTs in the captured arm, 52 distinct addresses, spanning `0x0204` to
`0xc40f`. **All 74 answered.** Notable:

| address | value bytes | read back |
|---|---|---|
| `0xa886` | 8 | `00 0000 015f 0001 0120` — the 352×288 geometry, confirmed by read-back |
| `0xa882` | 8 | `00 0280 1057 …` |
| `0xa893` | 18 | wide block |
| `0xb00e` | 20 | wide block |
| `0xb062` | 16 | the block the vendor writes a 22-byte value into |
| `0xb800` `0xb880` `0xb900` `0xb980` | 256 + 256 + 256 + 148 | **920 bytes total** |
| `0xbff8` | 16 | `00 0800 072b 0800 0800 0800 0800 0800 0a2a` |
| `0xc2bc` | 40 | table of 4-byte entries, `0x08d3` recurring |
| `0xc2c0` `0xc2c4` `0xc2c8` | 2 each | all `07f1`; `0xc2cc` = `07f1 03b7` |
| `0xc352` | 12 | `00 6839 1b4f 03e8 8045 3d71 060a` |
| `0xc35e` `0xc363` `0xc368` `0xc36d` | 10 each | `00 5529 5555 4e15 c71b 0000` |

**The four `0xb8xx` blocks are exactly the 920-byte blob** the vendor driver writes at
`0xb800` (IR-6). Read as 16-bit big-endian, **every one of the 458 values is below
`0x1000`** — a 12-bit table, the same container width as the EP `0x84` samples. `[CAPTURED]`
What the table contains is `[UNKNOWN]`; there is no ASCII in it.

**Nine addresses changed value between two reads inside the same run**, so they are live
rather than static configuration: `0x0204`, `0xa882`, `0xa892`, **`0xb007`** (`000040` vs
`000180` — the bulk-data lever of §12), `0xb0ae`, `0xc036`, `0xc363`, `0xc401`, `0xc402`.
`[CAPTURED]`

The identity read (`0xC0`/`wValue 2`, opcode 19, address `0xff000000`) returned 38 bytes:
six header bytes, then `META2D<unit-serial>`, then `0xFF` fill — the file-read framing of
§11.1 reached directly. `[VERIFIED]`

### IR-32 — a byte-order error, corrected

`re/ir32_device_files.py` re-derived `GetFileAddress` from the IL and parsed the four
address bytes **big-endian**. §11.1 has them **little-endian**, and §11.1 is right. The
addresses IR-32 printed (`0xfe00`, `0xff00`) are byte-swapped versions of the real
`0x00fe0000` / `0x00ff0000`, so the bodies it printed are **not** file contents.
`[CORRECTED]` — §11 stands as written and is not superseded.

What IR-32 does establish independently: `0xC0`/`wValue 2` opcode 19 is a **32-bit device
memory read**, not a file-specific call. Reading `0xff000000` returned `4d 41 32` ("MA2")
from inside the `hwinfo.bin` region, and reading arbitrary addresses works whether or not a
name resolved to them. `[VERIFIED]`

### IR-34 — `0xB9` is a live second command channel

`re/ir34_request_families.py`, OUTs with no payload: `0xB0` answers `03` for every value
tried; `0xB8` answers `06` (values 1–2) or `05` (values 4–9, 0xFD); `0xC1` answers `00` or
`05` and `00 0106` at `wValue 0xFD`; `0xC2` stalls with no payload. **`0xB9` answers at
`wValue 1` → `00 000e0000` and `wValue 2` → `00 200f0000` and stalls at 4–9 and 0xFD.**
`[CAPTURED]` The meaning of both values is `[UNKNOWN]`.

### IR-35 and IR-37 — the device went into the dead state again, and `0xB8` is the suspect

IR-35 (register-map diff between the `0xC0`-only arm and the full faithful arm) never ran:
the arm accepted 134/134 OUTs, produced **0 MB/s on all four endpoints** and **0 of 52
registers readable**. IR-37 characterised the state directly:

| transfer | result |
|---|---|
| `0xC1` / `wValue 0xFD` | **answers `00 0106`** |
| `0xC0`/7, `0xC0`/5, `0xC0`/3 register reads, `0xB8`, `0xB9`, `0xC2` | all IN stall, `errno 32 (EPIPE)` |
| after `libusb reset` + reopen | identical |
| after the full 134-transfer `0xC0` arm (134/134 accepted) | identical, 0 MB/s |

`[CAPTURED]` **`0xC1`/`wValue 253` is answered by the FX3 bridge itself and is therefore the
liveness indicator for the bridge, not for the headset.** Everything that has to be
forwarded to the headset stalls. That is a new and useful diagnostic: it separates "the USB
end of the pipe is fine" from "the far end is answering". `[VERIFIED]`

The state was reached during IR-34, whose last actions were `0xB8`, `0xB0` and `0xB9` OUTs
**carrying** the vendor payload `00 00 03 00 20` outside any arm sequence — every one of
those INs stalled, and nothing afterwards worked. `[INFERRED]` as the cause; `[VERIFIED]`
that the state exists and that no host-side procedure recovers it, which is the same
finding as §14 and again required the operator to cycle the headset's power.

**Trap for future experiments (withdrawn — see §17):** query-shaped probes on `0xB8` / `0xB0` /
`0xB9` were recorded as state-changing. That attribution does not survive §17's controlled runs.
Checking `0xC1`/`0xFD` before and after a batch is still worth doing, but a zero-byte reading
after such a batch must be confirmed with `capture_mask.py` before it is believed, because the
reader guard described in §17 produces exactly that reading.

Artifacts, local to the working tree: `ir32_results.json`, `ir33_dump/register_map.json`,
`ir33_dump/full_transcripts.json`, `ir34_families.json`, `ir35_mapdiff.json`, and the
scripts `ir32_device_files.py`, `ir33_register_dump.py`, `ir34_request_families.py`,
`ir35_map_diff.py`, `ir37_state_probe.py`.

## 17. IR-38 to IR-49 — `0xB8` is a readable manifest, and `0xb00e` is a mode register (2026-10-23)

### 17.1 The `0xB8` family is not lethal

`[VERIFIED]` IR-40 issued 1,056 `0xB8` OUT/IN probe pairs in one session. Afterwards
`capture_mask.py` measured 9.67 MB/s on EP `0x83` and 8.09 MB/s on EP `0x84`, and a full arm
accepted 134/134 transfers. IR-41 re-read `0xB8` index 0..7 forty-six times across a
re-open and got byte-identical replies every time.

The all-zero readings that produced §16's lethal-device claim came from the two host-side
defects in §17.6, not from the device.

### 17.2 What `0xB8` returns

Request: `OUT bRequest 0xC0 wValue 3 wIndex 5 wLength 5`, payload `00 00 idx hi lo`.
Reply: a 33-byte IN.

`[VERIFIED]` index 0..7 return content; index 8..31 return `ff` × 33. The content carries the
ASCII tokens `PMDTEC` and `PMDSCL`, a build stamp `22.09.2017-14:16:18`, and the identifiers
`01J0.DN1W` and `0006-2512-0043-1707`.

`[UNKNOWN]` the mapping from `(idx, hi, lo)` to the returned window is not a linear offset, and
it showed history dependence within a sweep — the same query returned different windows
depending on what had been queried before it. Not resolved.

`[INFERRED]` a per-module manifest table, consistent with the `g_pmd_cad` symbol in the
calibration file.

### 17.3 Ablation: which arm writes the depth path needs

IR-45 replayed the 138-transfer arm with groups removed and measured EP `0x84`.

| removed | EP `0x84` |
|---|---|
| the ToF-band write set (`0xa880`–`0xa893`, `0xb00e`) | endpoint silent |
| `0xb00e` only | streams, but 100% of samples are the `0x0FFF` invalid sentinel |
| `0xa893` alone | no measurable change |
| `0xa886` alone | no measurable change |

`[VERIFIED]` the behaviour. `[UNKNOWN]` what any of those registers contain.

### 17.4 The arm is order-sensitive

`[VERIFIED]` Re-issuing the `0xb00e` write *after* the arm completed — same opcode `0x60`, same
20 bytes the vendor itself writes — dropped every bulk endpoint to 0.00 MB/s, while
`capture_mask.py` measured 9.67/8.09 MB/s minutes before and after. A candidate value therefore
has to be substituted at the position the vendor uses, not appended.

### 17.5 `0xb00e` is a mode register, and its response is a bit field

Vendor command, `arm_full2.txt` line 95:
`OUT bRequest 0xC0 wValue 3 wIndex 24 wLength 24`, payload
`3d 60 b00e` + `15 15 15 15 15 15 15 15 15 15 15 15 13 15 15 13 15 15 04 15`.

IR-47 and IR-48 substituted a uniform byte value into all 20 positions and measured EP `0x84`.
Twenty-three values tested, no exceptions to the rule below.

| condition on the byte value | EP `0x84` behaviour | values |
|---|---|---|
| bit1 `0x02` set | every sample is `0x0FFF` | `02 03 06 07 0a 0b 0e 0f 12 13 16 17` |
| bit1 clear, bit2 `0x04` set | 12-bit mid-scale data | `04 05 0c 0d 14 15` |
| bit1, bit2 clear, bit4 `0x10` set | endpoint silent | `10 11 18` |
| bit1, bit2, bit4 clear | near-zero (`01`), or out-of-range garbage at 0.01 MB/s (`08 09`) | `01 08 09` |

`[VERIFIED]` the mapping. `[INFERRED]` that bit1 forces invalid samples, bit2 enables the data
path, and bit4 disables the endpoint unless bit2 is set. `[UNKNOWN]` what the register physically
configures.

Exact moments, IR-49, accumulated in a 4096-bin histogram:

| value | mean | sd | distinct values | p1 / p25 / p50 / p75 / p99 |
|---|---|---|---|---|
| vendor | 2037.37 | 142.12 | 567 | 1952 / 2007 / 2029 / 2052 / 2113 |
| `0x04` | 2037.42 | 143.51 | 564 | 1952 / 2007 / 2029 / 2052 / 2113 |
| `0x14` | 2037.30 | 141.49 | 572 | 1952 / 2007 / 2029 / 2052 / 2113 |
| `0x01` | 1.50 | 77.05 | 79 | 99.88% of samples are `0x0000` |

The three data-producing settings are statistically indistinguishable, so `0xb00e` selects a
**mode**, not a gain or a scale. The mid-scale band is tight — an inter-quartile range of 45
counts — with a small population of outliers at `0x0000` and `0x0FFF` that inflate the sd well
above what the quartiles imply.

`[UNKNOWN]`, and this is the open question: whether that 2037 ± 142 band is a scene-dependent
correlation value or a fixed unmodulated output. Distinguishing them needs the scene to change
while everything else is held constant.

### 17.6 Three host-side defects that produced false "device is dead" readings

1. A reader loop that treated any exception as fatal. pyusb reports a bulk timeout as
   `USBError(110, '[Errno 110] Timed out')` — `errno` is `110` and the text is `Timed out`, not
   `timeout`. A guard matching the wrong string ends every reader on the first idle endpoint,
   which makes a live device read as 0.00 MB/s on every endpoint.
2. An unanswered register read. Each `3d21` read OUT arms one control IN. Issuing the read and
   never collecting the reply leaves that IN pending and wedges the control channel: the
   sustaining strobe still reports success while every bulk endpoint falls to 0.00 MB/s.
3. Filtering an arm transcript by register address without excluding opcode `0x21` picks up the
   *read* of that address — a 20-byte `0xFF` mask — and replays it as if it were the written
   value.

Any future experiment that reports a device as dead must first be checked against
`capture_mask.py`, which is the shortest path to a trustworthy rate measurement.

### 17.7 Correction to IR-48

IR-48's `sd` column is wrong: it reported ~1010 for the mid-scale settings, which is impossible
given its own band histogram. The correct figure is ~142, from IR-49's histogram-based moments.
IR-48's mean, rate and sentinel columns are consistent with IR-49 and stand.

Artifacts, local to the working tree: `ir38_mask_maps.json`, `ir40_b8_table.json`,
`ir42_b8_sweep.json`, `ir43_b8_cursor.json`, `ir44_ep81_imu.json`, `ir45_ablation.json`,
`ir47_b00e_inplace.json`, `ir48_b00e_full_sweep.json`, `ir49_moments.json`, and the scripts
`ir38_mask_maps.py`, `ir39_b8_enum.py`, `ir40_b8_table.py`, `ir42_b8_sweep.py`,
`ir43_b8_cursor.py`, `ir44_ep81_imu.py`, `ir45_ablation.py`, `ir46_b00e_sweep.py`,
`ir47_b00e_inplace.py`, `ir48_b00e_full_sweep.py`, `ir49_moments.py`.

## 18. IR-51 to IR-53 — the depth output does not respond to the scene, and the frame layout becomes readable (2026-10-23)

### 18.1 IR-51 — seven physical conditions, coached through a web page

`scene_coach.py` (served on `:8095`) drives an operator through a protocol: it shows the condition,
waits for an explicit "I'm ready" click with no timeout, counts down 5 s of prep, runs a 60 s capture
with live per-second statistics on screen, then shows the result before advancing. Every second is
appended to `ir51_scene.jsonl` with its condition label.

| condition | mean | Δ vs no-scene reference | t |
|---|---|---|---|
| `baseline_room` | 2037.32 | — | — |
| `front_covered_hand` | 2037.37 | −0.026 | −0.59 |
| `front_covered_opaque` | 2037.35 | −0.044 | −0.94 |
| `wall_close` (~15 cm) | 2037.35 | −0.045 | −0.92 |
| `wall_far` (>3 m) | 2037.46 | +0.059 | +1.29 |
| `floor_down` (~15 cm) | 2037.55 | +0.153 | +3.21 |
| `control_repeat` | 2037.48 | +0.163 | +2.95 |

`[VERIFIED]` The reference is the two *identical* conditions pooled (n = 120, mean 2037.397,
sd 0.313). The drift between `baseline_room` and `control_repeat` is **+0.163 counts at t = 2.95** —
larger than four of the five scene conditions. The largest scene effect, `floor_down`, is +0.153
counts, which is **0.0037% of the 4096-count full scale** and is not distinguishable from that
drift.

A one-way ANOVA over the seven conditions returns F(6, 413) = 5.16, which is nominally significant
only because n = 420 makes a 0.2-count offset detectable. It is not evidence of a scene effect: the
no-scene control pair shows the same magnitude.

`[VERIFIED]` Distribution *shape* is also unchanged: the median per-second quartiles are
**2007 / 2030 / 2052 in every second of every condition**, and per-second sd stays in 131–148
throughout.

`[CONCLUSION]` With the vendor arm as written, EP `0x84` emits a distribution that does not depend
on what the headset is looking at. Occluding the front, a wall at 15 cm, a wall across the room and
the floor directly below are all indistinguishable.

### 18.2 IR-52 — it is not a fixed repeating pattern either

3 s of EP `0x84`, 697 transfers, all 65,536 bytes.

`[VERIFIED]` **0 exactly duplicated transfers.** Consecutive transfers match byte-for-byte on
30.1% of positions at every lag tested (1, 2, 3, 5, 10, 20) — flat in k, which is what the value
distribution predicts: 12-bit little-endian samples in bands 7 and 8 have a constant high byte
(`0x07` / `0x08`) and a varying low byte, giving ≈ 0.5·0.58 + 0.5·small ≈ 30%. A repeating frame
would show a lag-dependent peak; there is none.

`[VERIFIED]` Sample autocorrelation does show a harmonic series — 16, 32, 48, 64 samples with
r = 0.71, 0.62, 0.54, 0.45 — but that is produced by large-valued magic markers, not by the samples.

Correction to the first reading of this data: two of the marker values were mis-decoded as
`0xBECF` and `0xDA7D`. The actual values are **`0xBEEF` (48879) and `0xDADD` (56029)**.

### 18.3 IR-53 — the descriptor block and the frame geometry

3 s of EP `0x84` alone, 41,877,504 bytes = 20,938,752 samples.

`[VERIFIED]` Six 16-bit magic values, each occurring exactly 605 times:
`0xDEAD`, `0xF00D`, `0xDADD`, `0xABBA`, `0xFEED`, `0xBEEF`. They are not scattered — they sit at
fixed offsets inside a **16-sample (32-byte) descriptor block**:

| slot | value | note |
|---|---|---|
| 0 | `0xDEAD` | block start, constant in 605/605 |
| 1 | `0xF00D` | constant in 605/605 |
| 2 | `0xDADD` | constant in 605/605 |
| 3, 4 | `0x0000` | constant in 605/605 |
| 5 | varies (`0xEA2D`…) | looks like a sequence counter |
| 6 | `0x0004` | constant in 605/605 |
| 7 | `0x0244` (580) in 335 | |
| 8 | `0x0000` in 335, else varies | |
| 9 | `0x0120` (**288**) in 198 | matches the calibration height |
| 10 | `0x00C6` (198) in 73, else varies | |
| 11 | `0xABBA` in 335, `0x0000` in 204 | |
| 12 | `0xFEED` in 335, `0x0FFF` in 204 | |
| 13 | `0x0022` (34) in 335, `0x0FFF` in 204 | |
| 14 | `0x0022` (34) in 335, `0x0FFF` in 204 | |
| 15 | `0xBEEF` in 335, `0x0FFF` in 204 | |

`[VERIFIED]` There are two block variants: 335 blocks carry the full `ABBA / FEED / 0x0022 / 0x0022 /
BEEF` tail, 204 carry `0x0000 / 0x0FFF` in those slots.

`[VERIFIED]` Blocks arrive in runs — 270 runs in 3 s, lengths 1 (210 runs), 7, 4, 8, 9, 5, 6. The
gap from the end of one run to the start of the next is **101,392 samples in 130 of 269 cases**, and
101,392 = 352 × 288 + 16. Two runs show a following data span of exactly **101,376 samples = 352 ×
288**.

`[INFERRED]` A frame is one descriptor block followed by 101,376 samples of body: 101,392 samples,
202,784 bytes. Runs of several blocks are a table of pending descriptors.

`[VERIFIED]` The remaining 139 gaps are partial — 61,376 / 57,280 / 60,176 / 60,524 / 62,320 /
64,368 samples and so on — which is the slice-and-tear problem already recorded in `docs/05`:
transfers are being lost, so not every frame arrives whole.

`[UNKNOWN]` what slots 5, 7, 8, 10 mean, and why two block variants exist. Slot 9 holding 288 is
consistent with a height field but has not been confirmed against a second geometry.

### 18.4 What this means for the proof of concept

The camera path (`0x83`) produces real images. The depth path (`0x84`) produces a well-formed,
correctly framed 352 × 288 body whose values do not change with the scene, whose mode is selected by
`0xb00e`, whose offset is moved by `0xa88f`, and which requires `0xa882` and `0xa886` to emit
anything at all. The most consistent reading is that the ToF illumination is not running under the
host-only arm, so the correlation body is a fixed internal pattern rather than measured light. That
is `[INFERRED]`, not established: no register found so far has been shown to switch illumination on.

Artifacts, local to the working tree: `scene_coach_results.json`, `ir51_scene.jsonl`,
`ir52_frame_repetition.json`, `ir52_ep84_raw.bin`, `ir53_frame_layout.json`,
`ir53_ep84_raw.bin`, and the scripts `scene_coach.py`, `ir51_scene.py`,
`ir52_frame_repetition.py`, `ir53_frame_layout.py`.

## 19. usbmon does not record bulk payload bytes on this host `[VERIFIED]`

`re/control_usbmon.pcap` (6,037,805 B, 75,033 packets, snaplen 245824) was captured on
`usbmon4` while our own host-side reader ran for 10 s and **measurably** received:

| EP | bytes in 10 s | URBs |
|---|---|---|
| `0x81` | 644,864 | 2,519 |
| `0x82` | 867,893,248 | 13,243 |
| `0x83` | 550,764,544 | 8,404 |
| `0x84` | 607,256,576 | 9,266 |

In the resulting pcap, the number of frames carrying a `data_fragment` longer than 100
bytes is **0**. Bulk completions are present; their payloads are not.

Consequences:

1. **Withdrawn:** any inference that the vendor SDK "received nothing" on EP `0x82`/`0x83`/`0x84`
   because `meta2_trace.pcapng` shows zero-length bulk completions. That is a capture artifact.
   `[WITHDRAWN]`
2. **Method rule:** usbmon may be used for **control transfers only** (setup payloads and
   `data_fragment` on `bmRequestType` frames are recorded faithfully — 138/138 vendor OUTs
   recovered from `meta2_trace.pcapng`). It may **never** be used to measure bulk throughput
   or bulk content. Bulk data must be read by an active libusb client on the host.
3. Any future experiment that needs the SDK's own bulk data must read it **inside the guest**
   (SDK API), not from a host-side capture.

## 20. SDK arm vs our arm: the full diff `[VERIFIED]`

Mining `meta2_trace.pcapng` for `usb.bmRequestType==0x40 && usb.src==host` yields **138 vendor
OUTs across a 47 s SDK session**, and **zero vendor control transfers during streaming**. Two
arm sequences appear: frames 185–971 (session start) and frames 146436–147829 (immediately
before teardown, ending with the `000400000000` / `00000000` deassert pair).

Set-difference against our 134-transfer `ctrl_seq_full.json` arm is exactly five transfers, all
adjacent at arm position 68:

```
3d 60 b800 + 916 data bytes     (920-byte write, wValue 3, wIndex = wLength = 920)
3d 21 b800 + 256 x 0xFF         (wide read, paired 257-byte vendor IN)
3d 21 b880 + 256 x 0xFF
3d 21 b900 + 256 x 0xFF
3d 21 b980 + 256 x 0xFF
```

The `0xb800` blob write was already tested in IR-6 and produced no change in readable bytes and
no change on EP `0x84` (§12). **No hidden illumination or modulation command distinguishes the
SDK's configuration from ours.** `[VERIFIED]`

## 21. Our host-only arm drives the IR emitter `[VERIFIED]`

Blinded, randomised, balanced 16-trial test (`re/illum_blind.py`, seed 1792809976):
**armed 8/8 reported GLOW, un-armed 8/8 reported NO GLOW**, with EP `0x84` measured at
13.45–14.08 MB/s in every armed trial and 0.00 MB/s in every un-armed trial. Fisher exact
one-sided p = 7.77 × 10⁻⁵. Detector validated against a TV remote first.

- **Withdrawn:** "our host-side replay of the vendor command sequence does not drive the
  emitter" (§12.7). `[WITHDRAWN]`
- **Withdrawn:** the §12.14 `[INFERRED]` explanation that the depth body is scene-blind because
  illumination is off under the host-only arm. Illumination is on. `[WITHDRAWN]`
- **Still open:** whether the lit emitter is the ToF illuminator specifically (`[INFERRED]`), and
  what makes the depth body respond to the scene now that illumination is ruled out as the cause.

## 22. IR-56 / IR-57 / IR-58 — the depth-band registers are live knobs, and none of them is linear (2026-10-24)

All three runs are host-only, same harness (`re/tof_probe.py`), each variant bracketed by an
unmodified-arm control at the start and at the end. Every variant does `reset_open()` first, so
variants are comparable. Substitutions are **in place** at the site's own position in the arm.

Method note that matters for reading the numbers: the control-to-control drift was tiny in all
three runs — **0.28 counts** (IR-56), **0.03 counts** (IR-57), and the same order in IR-58. Any
effect above a few counts is therefore real, not run-to-run noise.

### 22.1 IR-56: `0xb00e` is position-sensitive `[VERIFIED]`

IR-47/48/49 established `0xb00e` as a mode register by substituting a **uniform** byte into all
20 data positions. That experiment destroyed the table's structure, so it could never show
whether the **positions** carry information. This run XOR-ed `0xFF` into exactly one byte at a
time.

Vendor table (site 84, opcode `0x60`, 20 data bytes):

```
15 15 15 15 15 15 15 15 15 15 15 15 13 15 15 13 15 15 04 15
                                 ^        ^        ^
                              pos 12   pos 15   pos 18
```

Controls: mean 2037.24 → 2037.52, sd 141.22 → 142.54, sentinel 0.403% → 0.411%, EP 0x84
9.18 → 9.18 MB/s. **Drift 0.28 counts.**

| pos | vendor | Δmean | sd | sentinel % | verdict |
|----:|:------:|------:|---:|-----------:|:--------|
| 0 | 15 | +1.29 | 142.95 | 0.415 | no effect |
| 1 | 15 | +0.82 | 143.01 | 0.416 | no effect |
| 2 | 15 | +4.27 | 142.64 | 0.412 | no effect |
| 3 | 15 | +2.11 | 141.43 | 0.406 | no effect |
| 4 | 15 | **+15.93** | 141.75 | 0.404 | matters |
| 5 | 15 | **+8.38** | 143.51 | 0.418 | matters |
| 6 | 15 | **+37.86** | 161.84 | 0.414 | matters |
| 7 | 15 | **+23.71** | 146.02 | 0.402 | matters |
| 8 | 15 | **+150.17** | 289.38 | 0.407 | matters |
| 9 | 15 | **+75.23** | 195.97 | 0.410 | matters |
| 10 | 15 | **+1438.78** | 909.28 | 1.487 | matters |
| 11 | 15 | **+300.07** | 505.91 | 0.417 | matters |
| 12 | 13 | +0.28 | 142.82 | 0.413 | no effect |
| 13 | 15 | +0.12 | 141.06 | 0.402 | no effect |
| 14 | 15 | −0.01 | 140.96 | 0.401 | no effect |
| 15 | 13 | +0.16 | 142.15 | 0.409 | no effect |
| 16 | 15 | −1.10 | 123.62 | 0.320 | matters (sd only) |
| 17 | 15 | +0.06 | 140.86 | 0.400 | no effect |
| 18 | 04 | +0.23 | 142.03 | 0.408 | no effect |
| 19 | 15 | **−11.85** | 149.50 | 0.444 | matters |

**10 of 20 positions change the output.** The table is not a mode byte replicated 20 times.

Two structural facts fall out:

1. **Sensitivity grows geometrically with byte position, then collapses.** Taking the high byte of
   each 2-byte slot: slot 0 → 1.29, slot 1 → 4.27, slot 2 → 15.93, slot 3 → 37.86, slot 4 → 150.17,
   slot 5 → **1438.78**, then slot 6 → 0.28, slot 7 → 0.01, slot 8 → 1.10, slot 9 → 0.23. A factor
   of ~3–4 per slot across slots 0–5, then dead. `[VERIFIED]` as an observation; the mechanism is
   unknown.
2. **The high-byte / low-byte effect ratio is ~1.6–2.3, not 255.** If the 20 bytes were ten
   independent linear `u16` values, XOR into the high byte would change the value by 255 and into
   the low byte by 1, so a linear knob would predict a ratio near 255. Observed ratios per slot:
   1.6, 2.0, 1.9, 1.6, 2.0, 4.8, 2.3, 0.1, 18.3, 0.0. The table is therefore **not** ten linear
   16-bit knobs. `[INFERRED]`, from the ratio pattern.

A coincidence worth recording: the three positions the vendor deliberately sets away from `0x15`
(12, 15, 18) are all **insensitive**, while the sensitive positions are all vendor `0x15`. The
vendor's own exceptions are don't-cares. `[VERIFIED]` observation, no interpretation attached.

Position 10 is the strongest single byte found anywhere in the depth band: mean 3476.02, quartiles
2049/2086/4050/4074/4095 — the distribution splits against the invalid ceiling.

### 22.2 IR-57: byte-level sensitivity of `0xa882` and `0xa886` `[VERIFIED]`

Perturbation was the mildest possible, XOR `0x01`, which flips one bit and leaves the value
recognisable. Controls: mean 2037.37 → 2037.34, sd 141.23 → 141.24, sentinel 0.404% → 0.404%,
distinct 564 → 564. **Drift 0.03 counts, and `distinct` identical** — the tightest control band in
this project so far.

`0xa882`, two write sites:

```
op 0xa0  02 80 10 57 00 00 00 04     (8 bytes)
op 0x60  02 80 10 57                 (4 bytes)
```

| site | byte | vendor | result |
|:-----|-----:|:------:|:-------|
| op 0xa0 | 0–4 | 02 80 10 57 00 | all inert |
| op 0xa0 | 5 | 00 | **breaks framing**: EP 0x84 0.13 MB/s, sentinel 5.70%, quartiles 6/2007/2026/2046/4095 |
| op 0xa0 | 6 | 00 | moments unchanged, but **distinct 1495 vs 564** — support nearly triples with the same mean and sd |
| op 0xa0 | 7 | 04 | **bimodal**: mean 3046.54, sd 1592.79, distinct 2690, quartiles 1/2029/4022/4060/4095 |
| op 0x60 | 0 | 02 | inert |
| op 0x60 | 1 | 80 | **silences EP 0x84** |
| op 0x60 | 2 | 10 | mild: mean 2038.22, distinct 627 |
| op 0x60 | 3 | 57 | **live parameter**: mean 1987.50 (−49.9), distinct **237** (narrowed from 564), EP 0x84 **14.04 MB/s** (up from 9.55) |

The `op 0x60` byte 3 result is the most interesting single number in this run: flipping one bit
moved the mean by −49.9 counts, **narrowed** the support from 564 distinct values to 237, and
**raised** the endpoint rate by 47%. A narrower support at a higher rate is not a broken mode; it
looks like a parameter that changes what the device is integrating. `[VERIFIED]` effect,
`[INFERRED]` interpretation.

`0xa886`, read back as four `u16` big-endian values:

```
0000 015f 0001 0120   ->   0, 351, 1, 288
```

That is a window: x from 0 to 351, y from **1** to 288. The wire frame is 352×288 and the
calibrated image is 352×**287** (§11.7). A window that starts at y = 1 independently confirms that
row 0 is excluded **by configuration**, not by accident. `[VERIFIED]` values; `[INFERRED]` that the
four values are a bounding window.

Byte sensitivity of `0xa886` matches that reading:

| byte | vendor | result |
|-----:|:------:|:-------|
| 0 | 00 | mean 2035.09, distinct 1166, EP 0x84 11.17 MB/s |
| 1 | 00 | **silences EP 0x84** (x-maximum low byte) |
| 2 | 01 | mean 2036.94, distinct 1139, EP 0x84 11.18 MB/s |
| 3 | 5f | **silences EP 0x84** (351 → 350: window no longer matches the emitted frame) |
| 4 | 00 | mean 2092.30, sd 369.73, sentinel 3.09%, distinct 2543 |
| 5 | 01 | inert |
| 6 | 01 | mean 2094.27, sd 369.33, sentinel 3.09%, distinct 2427 |
| 7 | 20 | inert |

Bytes 4 and 6 produce **nearly identical** results (2092.30 / 2094.27, sd 369.7 / 369.3, sentinel
3.093% in both) — consistent with them being the two high bytes of the same pair of window values.

### 22.3 IR-58: `0xa88f` is a stepped selector, not a bias `[VERIFIED]`

IR-50 found that XOR `0xFF` into `0xa88f` moved the mean 2036.6 → 2427.6 and shifted every quartile
by the same ~391 counts, which looks exactly like an additive term. This run swept the `u16` across
its range to test linearity. **It is not linear.**

| value | hi | lo | mean | sd | quartiles |
|------:|:--:|:--:|-----:|---:|:---------|
| 0x0000 | 00 | 00 | 2089.22 | 138.50 | 2060/2081/2104 |
| 0x00ff | 00 | ff | 2021.74 | 142.42 | 1990/2014/2038 |
| 0x0100 | 01 | 00 | 2089.22 | 138.19 | 2060/2081/2104 |
| 0x0200 | 02 | 00 | 2089.34 | 139.41 | 2060/2081/2104 |
| 0x0300 | 03 | 00 | 2089.26 | 138.73 | 2060/2081/2104 |
| **0x031e** (vendor) | 03 | 1e | 2037.42 | 142.09 | 2007/2029/2052 |
| 0x033c | 03 | 3c | 2037.30 | 141.62 | 2007/2029/2052 |
| 0x035a | 03 | 5a | 2077.33 | 140.98 | 2047/2069/2092 |
| 0x0400 | 04 | 00 | 2430.63 | 122.78 | 2403/2426/2449 |
| 0x0500 | 05 | 00 | 2430.69 | 122.75 | 2403/2426/2449 |
| 0x0600 | 06 | 00 | 2430.83 | 123.53 | 2403/2426/2449 |
| 0x0700 | 07 | 00 | 2430.78 | 123.13 | 2403/2426/2449 |
| 0x07ff | 07 | ff | 2475.81 | 144.87 | 2435/2493/2529 |

Linear fit: `mean = 0.2579 × value + 1972.80`, **R² = 0.685**, worst residual **+193.72 counts** at
0x0400. The linear model is rejected.

The structure that does fit:

- With `lo = 0x00`, `hi = 0x00, 0x01, 0x02, 0x03` give 2089.22, 2089.22, 2089.34, 2089.26 —
  identical to 0.12 counts. `hi = 0x04, 0x05, 0x06, 0x07` give 2430.63, 2430.69, 2430.83, 2430.78 —
  identical to 0.20 counts. **The high byte has exactly one threshold, between 3 and 4, and is
  otherwise ignored.**
- With `hi = 0x03`, `lo = 0x00, 0x1e, 0x3c, 0x5a` give 2089.26, 2037.42, 2037.30, 2077.33 —
  **non-monotonic**.
- 0x00ff and 0x0100 differ by 1 in value but give 2021.74 and 2089.22 — 67 counts apart.

`0xa88f` selects between discrete output levels (~2022, ~2037, ~2089, ~2431, ~2476). It is a
selector, not a bias, and the "+391 shift" from IR-50 was one step of that ladder, not a slope.

### 22.4 What this changes

- The earlier reading of `0xb00e` as "a mode register" is **incomplete but not wrong**: it is a
  mode register **and** a position-structured table. `[VERIFIED]`
- `0xa886` is now the best-understood register in the band: four `u16` values that read as a
  352-wide, y-from-1 window. `[VERIFIED]` values.
- `0xa882 op 0x60` byte 3 is the first register found whose perturbation **narrows** the output
  distribution while **raising** the rate. It is the strongest remaining candidate for a real
  integration/modulation parameter. `[VERIFIED]` effect.
- No register swept so far behaves linearly. Any model of the depth path as "output = f(scene) +
  register offsets" is not supported by these data. `[VERIFIED]` for the registers tested.
- **Still open:** whether any setting of these registers makes the depth body scene-responsive.
  None of IR-56/57/58 tested scene response; they tested register response.

## 23. IR-59a / IR-59b — the two strongest registers are mode selectors, and the modes are mixtures of quarter-scale levels (2026-10-24)

Fine sweeps of the two leads from §22, same harness, in-place substitution, controls at both ends.

### 23.1 IR-59a: `0xa882 op 0x60` byte 3 is a **mode selector**, not a knob `[VERIFIED]`

Controls: mean 2037.40 → 2037.45, drift 0.06 counts.

| byte3 | mean | sd | distinct | sentinel % | EP 0x84 MB/s | quartiles p25/p50/p75 |
|------:|-----:|---:|--------:|-----------:|-------------:|:----------------------|
| 0x40 | 2029.57 | 149.26 | 66 | 0.125 | 5.79 | 2035/2035/2036 |
| 0x48 | 2015.09 | 225.55 | 248 | 0.120 | 5.89 | 2035/2035/2036 |
| 0x50 | 2025.39 | 172.44 | 1056 | 0.115 | 5.58 | 2035/2035/2036 |
| 0x54 | 2017.59 | 219.29 | 691 | 0.141 | 5.78 | 2035/2035/2036 |
| 0x55 | 2975.10 | 1791.03 | 67 | 71.689 | 0.01 | 789/4095/4095 |
| **0x56** | 1987.56 | 138.44 | 228 | 0.400 | **14.04** | 1962/1980/1998 |
| **0x57** (vendor) | 2037.61 | 143.13 | 560 | 0.415 | 9.00 | 2007/2030/2052 |
| 0x58 | 2024.42 | 179.85 | 521 | 0.120 | 5.70 | 2035/2035/2036 |
| 0x59 | 2976.11 | 1790.76 | 59 | 71.729 | 0.01 | 791/4095/4095 |
| **0x5A** | 1987.69 | 138.56 | 278 | 0.400 | **13.95** | 1962/1980/1998 |
| 0x60 | 4059.50 | 379.35 | 66 | 99.131 | 5.75 | 4095/4095/4095 |
| 0x70 | 2025.50 | 174.46 | 65 | 0.125 | 5.79 | 2035/2035/2036 |
| 0x77 | 2030.49 | 74.62 | 352 | 0.078 | 9.23 | 2007/2029/2052 |

**Linearity is rejected outright.** Fits over the byte value: mean `R² = 0.0124` (worst residual
+1701 counts), distinct `R² = 0.0173`, endpoint rate `R² = 0.0215`, sd `R² = 0.0045`. There is no
knob here at all.

What there is instead is a set of **reproducible discrete modes**:

- **Flat mode** — quartiles `2035/2035/2036`, i.e. p25 = p50 = p75 to the count. The output is
  essentially a constant 2035 with a small minority of other values supplying the sd. Rate ~5.6–5.9
  MB/s, sentinel ~0.12%. Entered by 0x40, 0x48, 0x50, 0x54, 0x58, 0x70.
- **Vendor mode** — `2007/2030/2052`, sd 143, rate 9.0–9.2 MB/s. Entered by 0x57 and 0x77.
- **Narrow-and-fast mode** — `1962/1980/1998`, sd 138, distinct only 228–278, rate **13.95–14.04
  MB/s**. Entered by 0x56 and 0x5A. This is the mode IR-57 found by a single bit flip, and it is
  reproducible from two different byte values, so it is a real device mode and not an accident.
- **Broken mode** — `789/4095/4095`, sentinel 71.7%, rate 0.01 MB/s. Entered by 0x55 and 0x59.
- **All-invalid mode** — `4095/4095/4095`, sentinel 99.13%. Entered by 0x60.

The vendor value sits adjacent to a broken mode on one side (0x55) and the narrow-and-fast mode on
the other (0x56). `[VERIFIED]` adjacency; no claim about why.

### 23.2 IR-59b: `0xb00e` slot 5 produces **10 discrete output modes** `[VERIFIED]`

Slot 5 is bytes 10 and 11 of the `0xb00e` table (vendor `0x15 0x15`), the peak of the sensitivity
ladder in §22.1. Phase A varied the high byte with the low byte held at vendor; phase B the reverse.
Controls: mean 2037.40 → 2037.45, drift 0.06 counts.

Phase A (high byte varied, low = 0x15):

| slot5 | mean | sd | distinct | sentinel % | quartiles p1/p25/p50/p75/p99 |
|------:|-----:|---:|--------:|-----------:|:-----------------------------|
| 0x0015 | 1431.14 | 910.19 | 549 | 0.079 | 1/39/2002/2026/2047 |
| 0x0515 | 2037.24 | 140.89 | 848 | 0.401 | 1952/2007/2029/2052/2113 |
| 0x0a15 | 3476.51 | 909.09 | 543 | 1.463 | 2049/2087/4050/4074/4095 |
| 0x0f15 | 3476.42 | 909.12 | 893 | 1.467 | 2049/2087/4050/4074/4095 |
| 0x1515 | 2037.41 | 141.75 | 566 | 0.406 | 1952/2007/2030/2052/2113 |
| 0x1f15 | 1431.52 | 910.15 | 545 | 0.082 | 1/39/2002/2026/2047 |
| 0x2515 | 2870.14 | 1838.73 | 545 | 1.146 | 1/39/4050/4074/4095 |
| 0x3515 | 2871.52 | 1838.05 | 564 | 1.144 | 1/39/4050/4074/4095 |
| 0x5515 | 2037.36 | 141.81 | 561 | 0.407 | 1952/2007/2029/2052/2113 |
| 0x7515 | 2869.70 | 1838.87 | 558 | 1.145 | 1/39/4050/4074/4095 |
| 0xea15 | 3477.15 | 908.83 | 544 | 1.481 | 2049/2087/4051/4074/4095 |

Phase B (low byte varied, high = 0x15):

| slot5 | mean | sd | distinct | sentinel % | quartiles p1/p25/p50/p75/p99 |
|------:|-----:|---:|--------:|-----------:|:-----------------------------|
| 0x1500 | 1314.51 | 508.32 | 589 | 0.082 | 928/983/1006/2052/2113 |
| 0x1505 | 2037.42 | 142.09 | 962 | 0.407 | 1952/2007/2030/2052/2113 |
| 0x150a | 2336.56 | 505.41 | 558 | 0.409 | 1952/2007/2029/3076/3137 |
| 0x150f | 2336.91 | 505.61 | 599 | 0.409 | 1952/2007/2029/3076/3137 |
| 0x1515 | 2037.21 | 140.34 | 552 | 0.397 | 1952/2007/2030/2052/2113 |
| 0x151f | 1314.52 | 508.55 | 545 | 0.082 | 928/983/1006/2052/2113 |
| 0x1525 | 1614.94 | 963.38 | 565 | 0.082 | 928/983/1006/3076/3131 |
| 0x1535 | 1613.85 | 962.74 | 1323 | 0.072 | 928/983/1006/3076/3131 |
| 0x1555 | 2037.22 | 140.34 | 1547 | 0.396 | 1952/2007/2030/2052/2113 |
| 0x1575 | 1614.65 | 963.17 | 566 | 0.077 | 928/983/1006/3076/3131 |
| 0x15ea | 2337.75 | 505.75 | 796 | 0.402 | 1952/2007/2030/3076/3137 |

**Not a linear 16-bit value.** Slope of mean against the slot value: phase A (high byte) 0.01764,
phase B (low byte) 1.42026 — a ratio of **0.01**, where a single linear `u16` knob predicts ~256.
The low byte dominates.

**The modes are mixtures of a small set of value clusters.** Clustering all 22 variants by quartile
signature gives 10 signatures, and the same signature recurs from different slot values:

| quartile signature | mean | sd | variants producing it |
|:---|---:|---:|:---|
| 1952/2007/2030/2052/2113 | 2037.32 | 141.1 | A:0x1515, B:0x1505, B:0x1515, B:0x1555 |
| 1/39/4050/4074/4095 | 2870.45 | 1838.5 | A:0x2515, A:0x3515, A:0x7515 |
| 928/983/1006/3076/3131 | 1614.48 | 963.1 | B:0x1525, B:0x1535, B:0x1575 |
| 1/39/2002/2026/2047 | 1431.33 | 910.2 | A:0x0015, A:0x1f15 |
| 1952/2007/2029/2052/2113 | 2037.30 | 141.3 | A:0x0515, A:0x5515 |
| 2049/2087/4050/4074/4095 | 3476.47 | 909.1 | A:0x0a15, A:0x0f15 |
| 928/983/1006/2052/2113 | 1314.51 | 508.4 | B:0x1500, B:0x151f |
| 1952/2007/2029/3076/3137 | 2336.73 | 505.5 | B:0x150a, B:0x150f |

Read as mixtures of five recurring clusters —

```
L5  ~    1 /   39
L1  ~  928 /  983 / 1006
L2  ~ 1952 / 2007 / 2030 / 2052   <- the vendor operating point
L3  ~ 3076 / 3131
L4  ~ 4050 / 4074 / 4095
```

— every signature is two clusters blended: `0x1500` is L1 in its lower half and L2 in its upper
half; `0x150a` is L2 below and L3 above; `0x2515` is L5 below and L4 above. `[VERIFIED]` that the
histograms are two-cluster mixtures.

**The cluster centres are spaced by ~1024.** L1 ≈ 1006, L2 ≈ 2030, L3 ≈ 3100, L4 ≈ 4095 — quarter,
half, three-quarter and full scale of a 12-bit range. `[VERIFIED]` as measured cluster centres;
`[INFERRED]` that the depth body reports quarter-scale levels rather than a continuous range.

A global mean cannot distinguish "the whole frame moved to a new level" from "half the frame moved
to a new level". IR-60 was written to make that distinction.

## 24. IR-60 — the depth frame is not spatially organised by the register table, and the vendor output is one cluster (2026-10-24)

Frame-level capture per setting (3 s of EP 0x84 while strobing, resynchronised on the
`0xDEAD`/`0xF00D` descriptor pair, 352×288 image blocks). Parser validated offline against
`ir29_tof_ep84.bin` first: 4,957 frames resynchronised, row-0 sentinel 93.41%, rows 1+ 0.005% —
matching §12.14 independently.

### 24.1 Correction to §23.2: the vendor mode is a **single** cluster `[VERIFIED]`

§23.2 inferred mixtures from quartile signatures. The frame capture shows the vendor operating
point is **not** a mixture:

```
control histogram peaks (value, count): 2033, 2027, 2029, 2023, 2025, 2035
control band occupancy 0-1023 / 1024-2047 / 2048-3071 / 3072-4094 / 4095:
                                  0.04%   70.68%     28.89%      0.35%     0.04%
```

Every peak sits between 2023 and 2035. The 70.68 / 28.89 split across the 2048 boundary is one
broad cluster straddling that boundary, **not** two clusters. `[WITHDRAWN]` the implied reading that
the vendor signature `1952/2007/2030/2052/2113` is a blend of two levels — it is one level.

The mixture reading **does** hold for the perturbed settings, where band occupancy and quartiles
agree: `0x1500` → peaks at ~1005 **and** ~2051, bands 51.59% / 19.25% / 29.01%; `0x150a` → 70.89% in
1024–2047 and 29.03% in 3072–4094 with quartiles 1952/2007/2029/**3076/3137**.

### 24.2 The spatial-table hypothesis is **refuted** `[VERIFIED]`

The hypothesis worth refuting was that `0xb00e`'s ten slots index ten regions of the frame, so that
changing a slot changes some rows and not others — which would explain a global histogram that moves
with registers but never with the scene.

Diff of per-row and per-column means against control:

| setting | rows changed >20 counts | cols changed >20 counts | max row change | max col change |
|:---|---:|---:|---:|---:|
| `0xb00e` slot5 lo=0x00 | 288/288 | 352/352 | 2353 | 885 |
| `0xb00e` slot5 lo=0x0a | 288/288 | 352/352 | 344 | 490 |
| `0xb00e` slot5 hi=0x0a | 288/288 | 352/352 | 3645 | 1632 |
| `0xb00e` slot5 hi=0x25 | 288/288 | 348/352 | 2615 | 1474 |
| `0xb00e` slot5 hi=0x00 | 288/288 | 352/352 | 3597 | 1210 |

Every variant changes **every** row and **every** column. And the per-row means stay flat under
perturbation — `0x1500` gives 1338, 1348, 1349, 1368, 1335, 1361, 1347, 1338, 1332, 1330 sampled
every 24 rows. A per-row or per-column band table would have moved some rows and left others alone.
It did not. `[WITHDRAWN]` the per-slot spatial-table hypothesis.

Row 0 remains distinct in every setting (mean 3633 / 4870 / 3596 / 7278 / 5769 / 7230 versus ~2041 /
1340 / 2330 / 3390 / 2900 / 1420 for the rest of the frame), consistent with the configured y-window
of §22.2.

### 24.3 The cluster centres sit just below multiples of 1024 `[VERIFIED]` measurement, `[INFERRED]` meaning

| cluster centre | nearest multiple of 1024 | offset |
|---:|:---|---:|
| ~1005 | 1 × 1024 = 1024 | −19 |
| ~2030 | 2 × 1024 = 2048 | −18 |
| ~3100 | 3 × 1024 = 3072 | +28 |
| ~4077 | 4 × 1024 = 4096 | −19 |

Four independent clusters, three of them within 19 counts of a quarter-scale step. `[INFERRED]` that
the depth body reports quarter-scale levels rather than a continuous range; the offsets are not
explained and are not small enough to call them rounding.

### 24.4 The two cleanest outputs produced so far `[VERIFIED]`

- **Flat mode** (`0xa882 op 0x60` byte3 = `0x40`): peak 2035 carries 10,162,570 of ~17.4 M samples —
  **58% of every sample in the capture is exactly 2035**, and the next-busiest value has a count of
  2,057. Band occupancy 99.92% in 1024–2047. This is a constant output.
- **Narrow-and-fast mode** (byte3 = `0x56`): a tight unimodal cluster at ~1980, 99.52% in one band,
  rate 14 MB/s. The cleanest non-constant output obtained.

A device that can be made to emit a constant is a device whose measurement path can be switched
off. That makes 2035 a strong candidate for the no-signal level, and it sharpens rather than softens
the open question: no register setting found so far produces data that varies with the room.

## 25. IR-61 / IR-61b — under our host-only arm, EP 0x84 is a stable pattern fixed by the device, not scene data and not noise (2026-10-24)

### 25.1 IR-61, and why its first numbers were not trustworthy

First pass over four settings, two arms each, 4 s captures. Reported:

| setting | frames (pass 0 / pass 1) | spatial_sd | temporal_sd | r across reset |
|:---|:---:|---:|---:|---:|
| control (vendor) | 21 / 18 | 275.42 | 82.93 | 0.1528 |
| `0xb00e` slot5 lo=0x00 | 1004 / 10 | 721.75 | 505.68 | 0.0991 |
| `0xa882` byte3=0x56 | 1187 / 23 | 375.77 | 87.96 | 0.4293 |
| `0xa882` byte3=0x40 | 1193 / 45 | 420.99 | 119.60 | 0.5374 |

The frame counts are the problem: the control mode yielded 21 and 18 frames, and every second pass
yielded 10–45. A temporal mean built from 20 frames is noisy enough to depress a correlation by
itself, so `r = 0.15` could not be separated from thin sampling. IR-61b was written to decide which
it was. `[WITHDRAWN]` any use of IR-61's control-mode spatial/temporal split as a measurement.

### 25.2 IR-61b: vendor configuration, three independent arms, 8 s each, ≥300 frames per pass `[VERIFIED]`

```
pass 0: 60,260,352 samples -> 2,295 frames (15.07 MB/s)
pass 1: 57,802,752 samples -> 2,203 frames (14.45 MB/s)
pass 2: 74,186,752 samples -> 2,293 frames (18.55 MB/s)
```

| pass | frames | spatial_sd | temporal_sd |
|-----:|------:|-----------:|------------:|
| 0 | 2,295 | 155.43 | 112.88 |
| 1 | 2,203 | 190.88 | 68.03 |
| 2 | 2,293 | 87.55 | 307.04 |

Correlation of the temporal-mean frame **across a full port reset and close/reopen**:

| pair | Pearson r | mean \|difference\| |
|:---|---:|---:|
| pass 0 vs pass 1 | **0.9567** | **4.27 counts** |
| pass 0 vs pass 2 | 0.2579 | 18.99 counts |
| pass 1 vs pass 2 | 0.2692 | 20.70 counts |

Within-arm split-half on pass 0 (first 1,147 frames vs next 1,147): **Pearson r = 0.9950**.

### 25.3 What this establishes

- **The frame is stable within an arm.** Split-half r = 0.9950 across 2,295 frames. The spatial
  arrangement of values is not per-sample noise. `[VERIFIED]`
- **The frame is reproducible across a complete reset and re-arm.** Two of three independent arms
  agree at r = 0.9567 with a mean absolute difference of **4.27 counts** on a frame whose spread is
  ~150 counts. A room that never changed cannot explain that, and neither can random noise. `[VERIFIED]`
- **The third arm diverged** (r ≈ 0.26 against the other two, temporal_sd 307 against 68–113). So
  the arm does not deterministically land in one state; it landed in a different one once. The
  reproducibility claim is "two of three arms agree very closely", not "always". `[VERIFIED]`
- IR-61's low r was thin sampling, as suspected: with 2,295 frames the control correlation rises from
  0.15 to 0.96. `[VERIFIED]`

### 25.4 The conclusion this forces

Under our host-only arm, EP 0x84 delivers a **device-fixed pattern** that survives a port reset,
shifts level when `0xb00e` or `0xa882` is changed, and does not move when a hand, a cloth, a wall at
15 cm or a wall at 3 m is placed in front of the headset (§12.14). Those three facts are now
mutually consistent instead of contradictory: it is a pattern the device generates, whose levels the
registers select.

That is a coherent description of what we are receiving. It is **not** yet a description of the
device's ranging measurement. The open question is no longer "why is the depth body scene-blind" but
**"which configuration puts the device into its measuring state"**, and the only known producer of
that state is the vendor SDK (§12.1, §12.15). The decisive test is therefore the SDK-side one: read
the depth the SDK itself reports and establish whether *it* responds to the scene. If it does, the
missing configuration is findable by diffing behaviour; if it does not, this unit's ranging path may
not be reachable from USB at all.

## 26. SDK-side depth verdict — the SDK's point cloud is a fixed 2.45 m shell `[VERIFIED]`

IR-55 and IR-55b ran `MetaDepth.exe` against `meta_core_api.dll` in the VM and read the depth the SDK
itself reports. Result: it does not respond to the scene either.

- `meta_get_point_cloud` (101,024 slots = 352 × 288) is zero almost everywhere. Non-zero points appear
  only in short bursts whose *presence* is not reproducible between runs.
- Where points exist, they lie on **one thin shell at radius 2.4465 m** (13,412 points, per-spike
  standard deviation 0.021–0.027 m, hard maximum **2.4876 m**), plus a cluster at radius < 0.1 m.
- The shell radius is the same when the wall is at 2 m, 1 m, 50 cm, 30 cm and when the front is
  covered. In IR-55b the wall at 2 m, 1 m and 50 cm produced **no points at all**, and the 30 cm and
  covered conditions produced the points — all of them at 2.45 m.
- `meta_get_reconstruction_mesh` = 0 vertices and `meta_get_tracking_status` = 0/0 in all 3,881 polls
  of IR-55.
- The SDK's camera path is confirmed live in the same runs: `meta_get_rgb_frame` returned real images
  matching each condition.

Withdrawn / bounded: any reading of these point clouds as measured distance. They are a fixed-radius
pipeline artifact.

Open boundary, stated rather than papered over: the SDK ran with stream mask `0xFCF`, which excludes
MONO0/MONO1. §12.19 later established that the point cloud is *not* a SLAM product but an output of
`DeviceStreamBlock` — the device's own depth product — so absent mono input does not explain an empty
point cloud. "The SDK's depth output is a fixed shell" is verified; whether any configuration makes it
scene-metric is not.

## 27. IR-63 — the vendor driver's largest configuration write is inert for depth `[VERIFIED]`

The wire census contains a **920-byte write to `0xb800`** that no host-side arm had ever replayed
(`ctrl_seq_full.json`'s largest write is 40 bytes). Inserted in place, bracketed by controls with
0.18-count drift, it moved the EP 0x84 mean by **0.13 counts** — inside the noise. Appended at the end
of the arm it collapsed every endpoint to zero, reconfirming the in-place rule (§12.13).

Withdrawn: the hypothesis that the missing "measuring state" is a modulation table we had been dropping
from the arm. For this transfer it is not.

What did respond: zeroing the 40-byte `0xc2bc` table moved mean **+5.5 counts** (30× drift), sd
141 → 147, and EP 0x84 8.98 → 7.10 MB/s. `0xc2bc` is a live parameter, previously unprobed.

## 28. IR-65 — the "we just need to demodulate it ourselves" hypothesis is closed `[VERIFIED]`

Royale's `UseCaseTwoPhase/FourPhase/EightPhase`, `RawFrameSet` and `UseCaseDefinition::getRawFrameCount`
describe a camera that returns N raw correlation frames per measurement. If EP 0x84 were that stream,
the constant 2037 would be an artefact of looking at single frames instead of groups.

Tested offline on `re/ir29_tof_ep84.bin` (4,957 resynchronised frames, `re/ir65_multiphase.py`):
consecutive frames differ by 3.82 counts against a shuffled baseline of 3.99 (**ratio 0.9574**);
frame-mean autocorrelation peaks at +0.19 with no period-2/4/8 signature; 4-phase demodulation over
1,239 groups yields amplitude mean 13.14 and a uniform phase distribution; spatial coherence of the
demodulated amplitude, of brightness, and of a raw frame is **1.0000** in all three cases.

There is no phase sequence in the stream. Withdrawn: any expectation that host-side demodulation of
existing EP 0x84 captures can recover range.
