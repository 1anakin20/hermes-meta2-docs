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
ssh -p 2222 hermes@<vm> 'C:\MetaReader\MetaReader.exe C:\MetaReader\OUT 40'
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

## 9. What was not available

A web search for the Meta 2's published hardware specifications returned **no results**
from the configured search backend while these documents were written. No external
specification is cited anywhere in this repo. Every claim is device-derived. If you have
the vendor's published specs, reconcile them against `01-device.md` section 1.6.
