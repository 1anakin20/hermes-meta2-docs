# Handoff — continuing the Meta 2 reverse-engineering project

Written 2026-10-16. This file is the resume point for the next session, human or agent.
Read it, then go to the document named in "Next actions".

---

## 1. What the project is

**Ultimate goal:** a custom cross-platform library — **C/C++ over libusb** — that talks to
every Meta 2 sensor and camera directly, with no Meta SDK, no Windows requirement, and
better performance and currency than the vendor's software.

**Current phase:** understand the device completely enough to build that library. The
protocol layer is cracked **and continuous full-frame streaming now works with no SDK**
(2026-10-16) at 10-11 fps on EP 0x83, above the vendor SDK's ~3.1 fps. What remains is
identifying the minimal sustaining command set and what the registers and remaining streams
mean.

**The device is Meta (Metavision Inc.), USB `2cfa:00f3`. It has nothing to do with
Facebook/Meta Platforms or Oculus.** Never describe it as an Oculus/Facebook device, and
never assume Facebook-era SDK knowledge applies to it.

---

## 2. Where everything lives

| Thing | Location |
|---|---|
| Documentation (this repo) | `github.com/1anakin20/hermes-meta2-docs`, public, branch `main` |
| Working artifacts (not in the repo) | `<workspace>/re/` on the RE host — raw captures, pcapng, extracted streams, probe scripts |
| VM + launcher | `<workspace>/vm/` — `vm.sh` (modes: `install`, normal, `usb`, `stop`), `qmp.sh` |
| Reader source | `<workspace>/reader/MetaReader.cs` |
| SDK (extracted) | `<workspace>/sdk/Meta/Meta SDK2 Beta/bin/` |
| HTTP file delivery | `python3 -m http.server` on port `8090` from `<workspace>/verify` — **required**: the agent client's file download is broken, so files reach the user only over HTTP |

Credentials, hostnames, LAN addresses and SSH endpoints are deliberately absent from this
repo. They live only in the operator's own environment.

---

## 3. What is already established — do not re-derive it

These are `[VERIFIED]` against a live device. Re-confirming them wastes a session.

- **Transport is plain WinUSB/libusb.** `cyapi.dll` is Cypress's FX3 host API. There is no
  proprietary kernel driver to reimplement.
- **Enumeration works from Linux with no vendor software.** `2cfa:00f3`, one vendor-class
  interface, 4 bulk IN endpoints @1024, `bMaxBurst 15`, EP0 max packet 512.
- **Vendor control grammar.** `bRequest = 0xC0` always. OUT: `bmRequestType 0x40`,
  `wIndex == wLength == payload length` (138/138). IN: `bmRequestType 0xC0`, `wIndex = 1`
  (279/279). Every OUT is followed by exactly two INs (137/138; the identity command gets
  five).
- **A vendor IN without a preceding OUT always stalls.** The OUT arms the response. This is
  the single most important rule for writing a client.
- **Register access.** Payload `3D | op | addr(u16 BE) | data`. `op 0x21` = read, data is an
  `N`-byte `0xFF` mask, response is `1 status byte + N value bytes` (70/70). Write ops seen:
  `0x40, 0x20, 0x60, 0xA0, 0xC0, 0xE0`. `op` does **not** encode length.
- **A wide read is not a byte window.** For `0xc2bc` the span base is 4 bytes *below* the
  requested address. The old "contiguous byte-addressable" model is **withdrawn** — see
  03 §3.5. Do not reintroduce it.
- **Identity string** is readable via `wValue=0x0002` even though `iSerial = 0`. Format:
  17 ASCII chars starting `META2D`. The test unit's actual value is redacted repo-wide.
- **EP 0x83 carries whole 1280×720 16-bit frames.** Frame records are spaced by exactly
  **1,843,232 B = 1280×720×2 + 32**, and the 32-byte record's counter increments by 1 per
  frame (102 → 152 across 51 markers). The earlier "65,536-byte block = 32,744 samples +
  trailer at 65,488, 25.58 rows" model is **withdrawn** — it measured URB size, not device
  framing. See 05 §5.3. Row stride 1280 (autocorrelation) still stands.
- **EP 0x81** delivers 256-byte records: tag `45 00 00 ea`, 45-slot table (`0x00..0x2C`,
  `0xFFFFFF` = absent), magics `baabedfe`/`efbeadde`/`abbaedfe`, sentinel `0xDADDF00D`.
  All 45 slots were absent in all 29,462 records analysed.
- **EP 0x84** is a 12-bit field with `0x0FFF` = no data, body values clustered 2017–2033.
  Depth interpretation is `[INFERRED]`, units unknown.
- **EP 0x82 returns nothing**, despite having the largest requested URBs.
- **Throughput achieved without the SDK:** up to **21 MB/s ≈ 11.4 fps on EP 0x83** with
  bulk URBs kept pending during control traffic. The old 197 KB/s figure was what a
  handshake-then-read client gets.

Details, numbers and evidence: `03-control-protocol.md`, `04-register-map.md`,
`05-data-streams.md`, `EVIDENCE.md`.

---

## 4. The blocking problem is solved — and what replaced it

**Bulk streaming works.** The requirement is that bulk URBs are already **pending** on the
endpoints while control traffic is in flight. Handshake-then-read yields one 65,536-byte URB
per endpoint; a looping reader per endpoint, started before the control sequence, yields
100-155 whole 1280×720 frames per 12 s. `[VERIFIED]`

Two hard constraints, both `[VERIFIED]`:

- **One process, one thread per endpoint.** Two processes cannot both claim interface 0; the
  second bulk reader fails with `LIBUSB_ERROR_BUSY`.
- **Control traffic starts and sustains streaming from a quiescent device.** Narrowed
  2026-10-16: a device left armed by an earlier session produced 304 frame records in a 10 s
  window with zero control transfers.

**Also solved on 2026-10-16**, all `[VERIFIED]` unless marked otherwise:

- **The reset is a USB port reset** (`libusb_reset_device`, then close and reopen the
  handle). Without it the same command set measured 7.50 fps then 0.00 fps twice; with it,
  7.80 / 7.50 / 7.20 — spread 0.080. Closing and reopening the handle is not a reset.
- **The minimal sustaining set is 4 vendor OUT commands** — two assert/deassert pairs, in
  `data/minimal_outs.json`. Dropping any one of them gives 0.00 fps. Halving the 9-command
  parent set fails outright; leave-one-out is what works.
- **EP 0x83 tops out at ~51 MB/s inside the device.** 1, 2 and 4 concurrent bulk transfers
  give 52.9, 50.7 and 50.9 MB/s. The device is SuperSpeed, so it is not the bus, and a C
  reader matches a Python reader (51.1 vs 51.6 MB/s, `dropped=0`), so it is not the client.
- **~30 records/s is not ~30 complete frames.** 332 of 975 record gaps in a 30 s capture are
  shorter than a full frame while every counter still advances by 1. Complete-frame ceiling
  ≈ 27.7 fps `[INFERRED]`. A client must check each gap and discard truncated frames.

Ranked next actions, highest value first:

1. **Locate the colour camera.** EP 0x83 is monochrome (1.6a) — a 25 fps grey stream is a good
   SLAM input and a poor passthrough, so the display use case is not yet served. Capture
   EP 0x82 while the vendor reader runs (it has the largest requested URBs and has never
   returned a byte for us), and sweep for a pixel-format register. Full experiment order in
   7.9.
2. **Establish a trustworthy quiescent baseline.** Port reset, prove silence, then apply
   commands. Until that exists, "no arm" and "no control traffic" are not clean baselines and
   the free-running observation cannot be explained. This is the blocker for everything else.
3. **Find what the two strobed registers gate** — `wValue=0x0006/wIndex=0x0006` and
   `wValue=0x0009/wIndex=0x0004`. Read both before and after the strobe. The sequence is
   reproducible; its meaning is not.
4. **Differential register probing.** Read the whole observed address range, change one
   physical condition (cover cameras, tilt, warm up), read again. Moving addresses are
   sensor registers. Cheap, and the likely route to raw IMU.
5. **EP 0x84 framing and units.** It now streams (88.6 MB in one session) but its frame
   spacing is unestablished. Headset at a measured distance from a flat wall; regress values
   against distance.
6. **EP 0x81 semantics.** Capture while actively tracking a textured scene in motion so the
   45 slots populate.
7. **Span-base experiment.** Write a recognisable pattern across a 64-byte range, read at
   many addresses/widths, map where it lands. Settles 03 §3.5.

The previously top-ranked experiment — an active WinUSB shim logging `cyapi.dll` transfers
during steady state — is now lower value: the command set is known, and what remains is what
the commands mean.

### 2026-10-16 update — the camera question is now the front rank

`08-camera-inventory.md` is the current answer to "how many cameras and which stream is
which". What changed since the list above was written:

- **EP 0x82 is a live camera-class stream**, not silent. 4,096-byte records, A/B pairs
  sharing one counter, 2,032 coherent 10-bit samples each. The "EP 0x82 returns nothing"
  claim is withdrawn (05 §5.1).
- **EP 0x84's geometry is 352 × 288**, named by register `0xa886` reading back 351 and 288.
  The 704-stride guess in 05 §5.4 is superseded.
- **Register reads work, but only at the vendor's own sequence positions** (03 §3.4). Batch
  reads, post-sequence re-reads and a 376-address scan all fail. Do not build a reader that
  assumes a register bus.
- **EP 0x81 is not a camera**: 233 of its 256 bytes are constant.
- **The RGB camera is still not located**, and no stream has been tied to a physical lens.
  Scene correlation cannot separate cameras that all look at the same room; occlusion can.

### 2026-10-16 (later) — occlusion ran, and the cameras separated

`re/occlusion_test2.py` (ten windows, arm once, continuous readers, per-second statistics,
operator covering whole / left / right / middle with baselines between every cover) gave a
clean result. Full table in `08-camera-inventory.md` §8.8.

- **EP 0x82 is light-sensitive and is not central.** Cover-all drops its mean 59.4% and
  takes its saturation fraction from 0.1995 to **exactly 0.0000**. Left cover −27.7%,
  right cover −15.0%, **middle cover +0.1% — no response at all.**
- **EP 0x83 is light-sensitive and is the central one.** Middle-only cover drops it 43.1%,
  against 54.5% for cover-all. Its +18.3% under right cover is unexplained and should not
  be trusted.
- **EP 0x84 is not light-sensitive at all** — ±0.3% under every cover, sentinel fraction
  flat. That weakens the depth/ToF reading unless the subsystem was never enabled.
- **No endpoint carries colour.** EP 0x82 gives lag4/lag1 = 4.29 (A) and 4.23 (B) with
  identical mod-4 phase means, so it is not Bayer either. In this configuration the wire
  carries no colour, yet the vendor SDK produced colour frames — that gap is now the front
  rank question (08 §8.9).
- **There is no hidden fifth endpoint**: one interface, exactly four bulk IN, `wTotalLength
  = 70`.
- **The 138 "failed" arm transfers are all IN transfers** — the second IN of a pair. No OUT
  ever fails, so no enable command is being lost.

That section's "No endpoint carries colour" bullet and the usbmon next-step are both
superseded by the section below. The occlusion numbers themselves stand.

### 2026-10-16 (latest) — the decompiled vendor driver settles the camera question

`meta_driver_decompiled.zip` (C#, `Meta.Driver.*`) names every endpoint. `EndPointType`:
`MultiplexorEndPoint = 129`, `MonoCamerasEndPoint = 130`, `RGBCameraEndPoint = 131`,
`ToFCameraEndPoint = 132` — i.e. `0x81`–`0x84`, exactly the four bulk IN endpoints. Every
claim below was then re-verified against captures we already had. **New document:
`09-driver-decompiled.md`.**

- **EP 0x83 is the RGB camera, in YUV422, 1280 × 720.** The "EP 0x83 is monochrome"
  conclusion was an artefact: read as 16-bit samples, every u16 in `UYVY` is
  `chroma | luma<<8`, so the old bit-group test saw luma in the high byte and called the
  chroma "noise". A 4-byte phase test separates them cleanly (luma std 48.6, mutual
  correlation 0.992; chroma mean 128.05/126.71, std 4.5), and the decoded frames have 11%
  of pixels with channel spread > 20, max 189. `[VERIFIED]`
- **EP 0x82 is the two mono cameras**: `GrayScale16Image(752, 480)` ×2, mono0 tag `0x44`,
  mono1 tag `0x55`, interleaved one 4,096-byte URB at a time. Assembled per the driver's
  own scanner it gives 5.76 complete frames per 4.16 MB, trailer delta exactly 721,952,
  coherence 27–52× better than random, 10-bit values (max 1023). `[VERIFIED]`
- **EP 0x84 is the ToF camera, 352 × 288, and it *is* coherent** — the earlier "no spatial
  coherence" was `np.diff` wrapping on `uint16`. 435 frames, 36–38× better than random,
  values clustered 2017–2033. `[VERIFIED]` Coherence is not the same as ranging; whether it
  measures distance is still `[INFERRED]`.
- **EP 0x81 is the multiplexor, and the IMUs now read.** 256-byte records, 28-byte header,
  tag at +8 (`0x66` IMU1, `0x77` IMU0, `0x88` mics, `0x99` buttons), 16-byte IMU payload at
  +28: gyro valid/X/Y/Z then accel valid/X/Y/Z as `i16` LE. Both accelerometers show gravity
  at rest (\|a\| ≈ 16,360 and 17,043). `[VERIFIED]` First IMU data read outside the SDK.
- **The enable protocol is one 6-byte command.** `0xC0`/value 6 with `[0, 4, 0, 0, 0, mask]`
  selects endpoints (Mono0 = 2, Mono1 = 4, ToF = 8, Multiplexor = 16, RGB = 32, STD = 64);
  `0xC0`/value 9 with `[0, 0, 0, mux_mask]` selects muxed sensors (IMU0 = 1, IMU1 = 2,
  Mics = 4, Buttons = 8). Our 4-command strobe *is* this pair: `00040000007E` and
  `0000001B`. **Microphones are missing from our mask** (`0x1B` omits bit 2) — that is why
  no `0x88` record has ever appeared. `[VERIFIED]`
- **The occlusion results are unchanged and now explained**: 0x82 reacts to left and right
  covers and not to the centre = the two side mono cameras; 0x83 reacts to the centre = the
  centre RGB camera.
- **`usbmon` pcap cannot be used on this host.** A control capture against our own reader,
  known to move ~50 MB/s on EP 0x83, recorded 0 bytes for all 7,670 completions. Do not
  repeat that experiment. `[VERIFIED]`

**Next actions, in order:**

1. Set the multiplexor mask to `0x1F` and look for `0x88` microphone records.
2. Query firmware versions — `0xC0`/7 ARM, `0xC0`/5 + `[0,116]` FPGA build date,
   `0xC1`/253 USB, `0xB9`/4 + `[4,2]` GEO. This fills the "firmware unknown" field in 07.
3. Try the file protocol: `0xC2`/4 with `hwinfo.bin` then `0xC0`/2 with `[19, addr BE]` to
   read the serial and `calibration.bin` straight off the device. `[NOT YET REPRODUCED]`
4. Test whether the arm sequence can be halved: the driver issues **one** IN per OUT, our
   replay issues two and the second always fails.
5. Decode EP 0x83 to RGB properly (resolve which chroma slot is U and which is V) and
   decode EP 0x84 as a depth map. Display output is still unsolved.

Full detail and the experiment for each: `07-open-questions.md`.

---

## 5. Environment notes that will bite you

- **The device must be on a SuperSpeed port.** `bFunctionalitySupport = 3`. On USB 2 it
  enumerates and answers control transfers but never streams.
- **Only one thing can hold the device at a time.** The VM's QEMU holds it exclusively.
  Hand it over with `device_del {"id":"meta2usb"}` and take it back with `device_add` —
  no VM restart needed, because `vm.sh` gives the device an explicit id.
- **The reader only streams in a foreground, blocking session.** `start /b`, backgrounded
  SSH and detached console launches produce zero frames while appearing to succeed. Three
  separate 0-frame runs were misdiagnosed as a broken reader before this was found.
- **`pgrep -f qemu-system-x86_64` gives false positives** (it matches its own wrapper).
  Use `ps -eo pid,comm | awk '$2 ~ /^qemu/'`.
- **If libusb enumerates 0 devices on the host**, the cause is a VM holding the device or a
  container without `usbfs` — not a driver problem. Check before theorising.
- **A second bulk reader in a second process fails with `Resource busy`.** Only one process
  can claim interface 0. Threads inside one process are the correct shape.
- **A 65,536-byte read that then goes silent is not the device's limit.** It means no URB
  was pending when the buffer filled. Fix the client before concluding anything about the
  device.
- **Streaming results are hysteretic.** The same command set gave 18.4 MB/s and 1.0 MB/s in
  two runs depending on prior state. Re-arm identically before every trial or the number is
  meaningless.
- **tshark 4.4 field-name traps** are listed in `EVIDENCE.md` §3. Read them first; they cost
  hours otherwise. `frame.raw` invalid; `-c` truncates before `-Y`; control payloads are in
  `Data Fragment` not `usb.capdata`; URB ids are reused by the kernel so never pair
  SUBMIT/COMPLETE by URB id.
- **Raw usbmon binary traces use the 48-byte API0 header** on kernel 6.12, not 56 or 64.
- **`web_search` is currently returning zero results** on the operator's configured backend.
  Until that is fixed, no external hardware specification can be cited. Say so rather than
  inventing specs.

---

## 6. Documentation rules for whoever continues

These are the operator's standing requirements, not suggestions.

1. **Every claim carries a confidence marker**: `[VERIFIED]` / `[CAPTURED]` / `[INFERRED]` /
   `[UNKNOWN]`. Mark per claim, not per document.
2. **If something cannot be made accurate, say so in the document.** A labelled unknown is
   correct; a plausible-sounding guess is a defect.
3. **Write for programmers.** Precise, straight to the point, numbers included so a reader
   can check them.
4. **Code in the docs must compile, and be run if it claims to work.** `examples/
   meta2_probe.c` compiles clean under `-Wall -Wextra` and its quoted output is literal
   program output. Keep it that way.
5. **When a claim is disproven, withdraw it explicitly** and record the disproof. See the
   register-window model in 03 §3.5 — do not quietly delete a wrong claim.
6. **Never invent hardware specifications.** Everything in this repo is device-derived
   because no external spec source has been available. If you obtain one, reconcile it
   against `01-device.md` §1.6 and mark which claims it confirms.
7. **Keep the unit serial redacted.** `<unit-serial>` is the placeholder. Do not reintroduce
   the literal value into docs or committed data.
8. **No credentials, hostnames, LAN addresses, SSH endpoints or key paths in this repo.**
9. **GitHub writes are per-action authorised.** Pushes to this repo are authorised; force
   pushes, deletions, and any other repo mutation require explicit authorisation each time.

---

## 7. Open administrative items

- Commit authorship is `Hermes Agent <hermes@localhost>`. The operator may want it changed.
- The repo history was rewritten to a single commit to remove the serial from history. The
  old commit may still be served by GitHub by direct SHA until it is garbage-collected.
- The large raw captures (21.7 MB pcapng, 7.5 MB EP 0x81 stream, 8.1 MB EP 0x83 burst) are
  intentionally **not** published; derived statistics are quoted inline with their counts.
- The Meta 2 reports `bcdDevice 0.00` — **the firmware version is unknown**. Any result in
  these docs is tied to an unidentified firmware build. Flag this when a result fails to
  reproduce.
