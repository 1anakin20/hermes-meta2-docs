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

Consequently the previously recorded "device-side ceiling of ~51 MB/s on EP 0x83", the derived
"~27.7 complete frames/s ceiling", and the statement that concurrent transfers do not scale
are **withdrawn as device constants**. They were measurements of one device state, not of the
device. `[CORRECTED]` They remain valid as what was observed in those specific runs.

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
