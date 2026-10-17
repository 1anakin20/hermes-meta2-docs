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
- **EP 0x84 is the ToF camera, 352 × 288, and it carries no scene information.** The
  "36–38× coherent" figure was a bad baseline (uniform 12-bit random vs a narrow-band
  payload); against a permutation baseline it is 1.0×. What persists across frames is a
  fixed pattern: corr(frame, temporal mean) = 0.986, corr(ToF, mono0 in the same window)
  ≈ 0.0, occlusion-invariant. `[VERIFIED]` Whether it ever measures distance is
  `[UNKNOWN]`, not `[INFERRED]`. Frame rate measured: 302 fps.
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
   decode EP 0x84 as a depth map. **Display output is not a USB problem** — the
   operator reports the display is a generic HDMI display driven by the headset's own SoC
   (01 §1.7), so there is no USB display path to reverse-engineer.

Full detail and the experiment for each: `07-open-questions.md`.

---

## 4b. Enable masks, reader back-pressure, and mono framing (2026-10-16)

Full detail: `10-enable-masks.md`. The four results that change how captures must be run:

1. **The enable mask gates cameras.** `0xC0`/6 with `[0,4,0,0,0,mask]`; screening shows
   `0x48` (ToF|STD) + a reader on EP 0x84 alone gives **63.4 MB/s, 313 fps, 99.9% complete
   frames** — the cleanest capture in the project.
2. **EP 0x82 collapses unless a URB is pending on all four bulk IN endpoints.** With readers on
   `{0x82}`, `{0x81,0x82}` or `{0x82,0x83}` mono runs at 0.06–0.16 MB/s; with all four it runs at
   49–74 MB/s. Undrained endpoints back-pressure the mono stream even when the mask enables only
   the mono cameras.
3. **Device state is hysteretic across `libusb_reset_device`.** The same configuration gave
   74 MB/s and 2.12 MB/s on two runs. The *warm-up mask* used in the same process before the
   measured phase decides framing quality: warm `0x7e` → mono 54 MB/s but only 7.6% complete
   frames; warm `0x00` → 49 MB/s with **71.3%** complete frames. Never trust a single run's rate.
4. **The mono trailer is not a frame delimiter** (~62 Hz trailers vs 27–44 fps frames). The
   concatenate-and-cut model splices two acquisitions into one frame and *is* the horizontal
   slice-tearing the operator saw; fragment counters prove no data is dropped.
   `re/make_mono_exact.py` keeps only exact 721,952 B chunks and renders tear-free mono
   (44 fps on `screen_66_ep82.bin`, 27 fps on `cap_cold_ep82.bin`).

Microphones still do not appear: mux mask `0x1f` yields only tags 102/119, and buttons (153)
are absent even though bit 3 was already set in `0x1b`.

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


## 4c. Device-side files read successfully; mono naming resolved (2026-10-16)

`docs/11-device-files.md` is the authority. Headlines:

- The `0xC2`/4 + `0xC0`/2 file protocol works on the host with plain libusb.
  `hwinfo.bin` at `0x00ff0000` (17 B, the unit serial), `calibration.bin` at
  `0x00fe0000` (7,520 B, 62 chunks). `_maxRetries = 32` in the vendor source is a
  **retry** cap, not a chunk cap — stopping at 32 chunks truncates the calibration.
- Device `calibration.bin` and the host `META2D<unit-serial>.xml` are **byte-identical**
  after CR normalisation (7,361 B); the host copy just duplicates the CR on each line.
- The serial is **not** inside the calibration blob; it lives in `hwinfo.bin`. Read that
  first to bind calibration to a unit.
- **`EP 0x82` tag `0x44` = calibration `mono_left` = wearer's left camera; tag `0x55` =
  `mono_right` = wearer's right.** Established by operator lens occlusion and confirmed
  6/6 by RGB-bridge reprojection through the calibration poses (~20 px correct vs
  ~390 px swapped). The file's index order (`mono_right`=1, `mono_left`=2) does **not**
  match wire order — do not infer it.
- Mono cameras are **Kannala-Brandt fisheye** (`kb4`); RGB and depth are radial
  (`k1_k2_k3`). Feeding mono intrinsics to a pinhole model is wrong.
- Raw-pair disparity correlation without rectification is a dead end (documented as a
  method that does not work).
- Safety: only `0xC2`/4 and `0xC0`/2 with read opcode 19 were sent. No write opcode, no
  SPI-flash path, no golden-image probe.

## 4d. E4: the ToF streams, is calibrated, and carries no range data (2026-10-17)

`docs/12-tof-investigation.md` is the authority. Headlines:

- EP 0x84 is a **live noisy stream**, not a fixed pattern: 99.66 % of pixels change over
  time, per-pixel temporal sigma ~13, values mid-scale around 2034-2040 in a 12-bit
  container. What it lacks is scene structure, not variation.
- **Row 0 is a sentinel row** (4095 in 335 of 352 columns). Payload is 352x288; the
  calibrated depth image is 352x287. That resolves the long-standing 288-vs-287 mismatch.
- **No USB command is missing.** The driver's whole ToF enable is feed-mask bit 8, and the
  capture arm already replays the vendor's full 417-transfer sequence including all 46
  FPGA register writes (the 0xa8xx ToF band). The config descriptor has no bulk OUT, so
  EP0 is the only control path.
- "Config before stream" ordering was tested and made no difference (e4a vs e4b, identical
  statistics). Hypothesis rejected.
- **The vendor SDK gets no depth either**: `meta_get_point_cloud` returns exactly
  352x287 = 101,024 points, all coordinates 0.0000, while `streams=0xFFF` marks DEPTH and
  IR active. So the missing range data is a device-state problem, not a meta2lib gap.
- ToF stack is Intel Royale (`royale.2.3.1.dll`), with use cases (TwoPhase/FourPhase/
  EightPhase/GrayScale/Calibration), `BridgeEnclustra`, and IR LED driver vocabulary
  (`CX3_UVC_LED`, Infineon IRS16X5C eval kit) - the illumination is active, not ambient.
- Operator saw no IR emission from the headset. Not yet sanity-checked against a known IR
  source (TV remote) - do that before trusting the negative.
- E4 is **paused by the operator**, not closed. The one experiment that could still change
  the conclusion is running the vendor SDK live in the VM while the operator watches the
  faceplate for IR emission; if the official stack lights the emitter, it sends something
  the replayed sequence does not.

## 4e. E3: EP 0x81 record format fully mapped; microphones do stream (2026-10-17)

`docs/13-multiplexor-records.md` is the authority. Headlines:

- Every EP 0x81 record is **exactly 256 bytes**: 28-byte header, 212-byte payload,
  12-byte trailer sentinel, u32 packet counter. Header magic is
  `00 00 00 00 ab ba ed fe` (171,186,237,254 - easy to mis-write as `ab be ed fe`, which
  yields zero header hits and looks like a dead endpoint).
- **Tag mapping corrected**: `IsIMU0Header` tests 119 and `IsIMU1Header` tests 102 -
  the opposite of earlier notes. MICS = 136, BUTTONS = 153.
- The "212 unmapped bytes" are a **slot table**, not hidden sensors. IMU records carry
  16 bytes of IMU samples plus 45 slots of `[index, ff, ff, ff]`; MICS records carry
  176 bytes of audio plus 5 empty slots.
- **The earlier "microphones produce nothing" result was an artifact.** EP 0x81 read
  alone flushes a fixed ~645-record backlog and then goes silent forever. It sustains
  only when the other three endpoints are drained (627 records/s with all four readers).
- Mic samples: 4-byte groups, low byte always `0x00`, 24-bit signed LE in bytes 1..3,
  each group duplicated in identical pairs (22 unique samples per record).
- Mic rate measured at **8,405 samples/s** from a 10 Hz gate (three agreeing methods),
  cross-checked at 8,150/s from the record arrival rate.
- **Unresolved and stated as such:** the played 1 kHz carrier appears at 240.6 Hz, a
  factor 4.15 low, with essentially nothing at 1 kHz or 2 kHz. Not interleaving
  (tested 1/2/3/4/6/11/22 phases). 240.6 = 4x60 Hz and 48.8 Hz is also present.
- Mic occlusion test **inconclusive**: std moved 11 % across tone/cover/stop phases while
  peak-to-peak dropped 7x. The physical mic location on the headset is unknown.
  **Microphone work is deprioritised by the operator for the first SDK version.**
- IMU left/right signature: both accelerometers read ~1 g at scale 16384 with **opposite
  Y signs** (IMU0 +13,014, IMU1 -12,736). Not yet matched to the calibration file's
  `accelerometer_left` / `accelerometer_right` blocks.
- BUTTONS (153) has never appeared on the wire. `ButtonType` = Video 1, VolumeUp 2,
  VolumeDown 4, Power 8; `ButtonState` = Release 0, ShortPress 1, LongPress 3. A press
  experiment is the way to get them. Operator reports holding the left-arm light button
  toggles the HDMI display with a "bloop".

## 4f. E9: the C library now decodes mux, IMU and mono (2026-10-17)

`meta2lib` gained three things, all validated against real captures rather than only
against synthetic fixtures:

- **`include/meta2/mux.h` + `src/mux.c`** - EP 0x81 record finder, IMU decoder, MICS
  audio decoder, and the `0xAA` record decoder. On `e3mic_occl_ep81.bin` the C parser
  finds **22,585 records** with the same per-tag counts as the Python tool
  (IMU0 4,416 / IMU1 4,498 / MICS 13,670) and identical IMU means.
- **`include/meta2/mono.h` + `src/mono.c`** - a streaming exact-frame mono assembler
  with bounded memory. On `screen_66_ep82.bin` it emits **435 frames per camera** and
  on `cap_cold_ep82.bin` **405 frames per camera**, matching the Python renderer's
  published numbers exactly (76.4 % and 71.2 % of trailer gaps are exactly one frame).
- **Enable-mask / feed API** in `src/transport.c`: `meta2_feed_enable`,
  `meta2_feed_disable`, `meta2_sustain_cycle`, plus endpoint and mux mask constants.

Two new EP 0x81 findings came out of writing the parser, both documented in
`docs/13-multiplexor-records.md`:

- **A fifth record type, tag `0xAA` (170)**, present in 10 captures (25 records),
  periodic every ~2,650 records, payload_len 0, header timestamp 0, tail tag 102.
  Meaning unknown; the vendor's own `DataScanner` does not test this tag either.
  See §13.10.
- **The packet counter is not strictly +1.** In a healthy sustained capture: 22,573
  steps of +1, 11 repeats, 0 skips, and every repeat involves a MICS record. See §13.11.

Build/test state: `cmake -S . -B build && cmake --build build && ctest --test-dir build`
→ **3/3 tests pass** (`frame`, `mux`, `mono`), warning-free. Tests are built with
`-UNDEBUG` because a `Release` build would otherwise compile every `assert` away.
Fixtures are synthetic (`tools/make_mux_fixture.py`, `tools/make_mono_fixture.py`);
no capture is committed.

## 4g. Library additions for a live consumer, and the demo viewer (2026-10-17)

`meta2lib` commit `7d03c41` added what a *continuously running* consumer needs, which
the batch-capture examples never exercised:

- **`meta2_reader_drain` / `meta2_reader_pending`** (`transport.h/.c`). Without a drain
  API the reader thread appends until its buffer is full and then counts overflow in
  `dropped`. For a batch capture that is fine; for a viewer it silently throws away the
  entire stream.
- **`meta2_rgb_decode_yuv422`** (`frame.h/.c`). EP 0x83 pixel unpacking with the packing
  as a parameter (`UYVY`/`VYUY`/`YUYV`/`YVYU`), BT.601 full-range coefficients scaled by
  2^16 (91881, 22553, 46828, 116163). Phase evidence supports UYVY/VYUY; **which chroma
  slot is U and which is V is still unresolved** - every capture taken so far is
  near-neutral, so the swap is unmeasurable.
- **`meta2_mono_to_gray`** (`mono.h/.c`): fixed 10→8 bit map `out = in >> 2`, no
  auto-gain, so display brightness does not hunt.
- Tests now **5/5** (`frame`, `mux`, `mono`, `decode`, `drain`), warning-free.

**`meta2-demo-viewer`** (`github.com/1anakin20/meta2-demo-viewer`, commit `b7b9a4b`) is a
Qt 6 PoC that consumes the library: RGB + both mono cameras live, four scrolling IMU
charts, status bar with rates and dropped-byte counters. Verified on the real headset,
35 s at scale 0.5:

| stream | result |
|---|---|
| RGB EP 0x83 | 29.3 fps at 1280x720, 41.8 MB/s sustained |
| mono EP 0x82 | **60.6 fps per camera**, exact single-acquisition frames only |
| IMU0 / IMU1 | ~120 Hz instantaneous, ~130 Hz averaged |
| dropped bytes | **0 / 0 / 0** on all three endpoints |

The 60.6 fps mono rate is higher than the 36–43 fps documented earlier. Both are real
observations under different device states; neither is a device constant. `0xAA` appeared
once in 35 s. **MICS count was 0** with the default mux mask `0x1b`, confirming that bit 4
(the MICS bit) is what gates audio: `--mux-mask 31` (`0x1f`) is required to get mic records.

**Operational recipe that actually works** (the obvious sequence gives three black panels
and no error): port reset → close → reopen → start readers and drain them *before* arming →
one pass of `arm_full.txt` (265 of 410 commands accepted; the rest are recorded IN
transfers that stall on purpose) → 6 s warm strobing at enable `0x7e` → sustain at `0x66`
with mux `0x1b`. A **stall watchdog** re-arms after 3 s with no bytes on any endpoint,
because the device stops streaming at unpredictable times *including immediately after a
successful arm*, and because replaying the arm sequence can itself stop a device that was
already streaming. Re-arm is bounded (5 attempts) rather than infinite.

Next: settle U-vs-V with a saturated colour target; calibrate the accelerometer against a
known static orientation and derive a gyro scale; deterministic mono framing (71–76 % exact
yield is still not a clean frame boundary story); buttons on the wire.

## 4h. Capture archive pruned, and a Windows cross-build (2026-10-17)

**Disk reached 100 %** (54 MB free) and blocked further work. Pruned by rule, not by
impression: a capture was deleted only if it was **referenced by no document and no analysis
script** *and* larger than 50 MB.

- Deleted: **38 bulk raw captures, 28.89 GB** (the multi-gigabyte EP 0x82/83/84 dumps from
  the probe and E3 mic runs, whose analysis is already written up and whose small mux-side
  counterparts were kept). Manifest: `metavision/re/PRUNED_MANIFEST.txt` (path, bytes, mtime).
- Retained: **33 captures cited by meta2-docs or `re/` scripts (1.82 GB)** — including
  `screen_66_ep82.bin`, `cap_cold_ep82.bin`, `e3mic_occl_ep81.bin`, `ep83_live.bin`,
  `occl_baseline_ep83.bin` — plus 69 unreferenced captures under 50 MB (0.44 GB) as cheap
  insurance. `vm/` (43.9 GB) and the Windows ISOs were left alone.
- Filesystem went 100 % → 75 % used.

**Evidence re-verified after the prune**, not assumed intact: 5/5 library tests pass, the mux
dump on `e3mic_occl_ep81.bin` still reports 4,416 / 4,498 / 13,670 records with `0xAA` at
counter 11908, and `screen_66_ep82.bin` still yields 435 exact frames per camera at 76.4 % /
76.3 % framing quality.

**New finding from the prune pass:** chroma was measured across all 16 EP 0x83 captures
before any were deleted. Every one is near-neutral — per-phase chroma std between 2.3 and
12.5, with no capture above 25. This independently confirms that **U versus V cannot be
resolved from existing captures**; it needs a saturated colour target captured for the purpose.

**Windows cross-build works from Linux**, no Windows install: mingw-w64 + Qt 6.8.2
win64_mingw fetched with `aqtinstall` + libusb 1.0.28 cross-built from source. Two real
fixes came out of it, both in the library/build rather than papered over:

- `meta2lib` `ea4e8d3`: `#include <libusb-1.0/libusb.h>` only resolved on Linux because
  `/usr/include` is a default search dir; `${includedir}` is now requested explicitly, and
  the Windows-side link libraries a static libusb needs are named.
- `meta2-demo-viewer` `91b9ed3`: Qt6 AUTOMOC insists on its own `Qt6::moc` target and ignores
  `QT_MOC_EXECUTABLE`, so a cross build generates `moc_*.cpp` with a host moc and refuses to
  configure unless the host moc version equals the linked Qt version exactly.

`meta2-viewer.exe` is a valid PE32+ x86-64 image whose every import edge resolves against the
shipped DLLs (checked by resolving import tables against export tables; note pefile
under-enumerates the Qt MinGW DLLs' exports, roughly 8,606 of 17,212 rows, which makes it
report Qt's own internal vtable imports as unresolved — objdump is authoritative here).
**It has not been executed on Windows**: this host's Wine cannot initialise a prefix, and no
Windows system was set up for it.

## 4i. The Windows viewer crashed on Start; one definite bug found, one suspected (2026-10-17)

Reported symptom: the shipped `meta2-viewer.exe` dies when **Start** is clicked.

**Definite bug, and it was in the shipped artifact.** `src/main.cpp` baked the build
machine's path into the binary as the default arm file:

```c
#define ARM_FILE META2LIB_DATA_DIR "/arm_full.txt"   /* /home/hermes/work/meta2lib/... */
```

That path does not exist on Windows, and the zip did not ship `arm_full.txt` at all, so the
Windows build could never arm the device. Fixed in `meta2-demo-viewer` `a958e3f`: the default
is now resolved relative to the executable (`data/arm_full.txt`, then `arm_full.txt`, and only
then the compile-time path), and the zip ships `data/arm_full.txt` next to the exe.

**Suspected contributor, not proven.** The status tick called `meta2_reader_pending()` before
`meta2_reader_start()` had initialised the reader's mutex. A zero-initialised `pthread_mutex_t`
is a valid mutex on glibc, where the old build ran, and is **not** valid on winpthreads, which
is what the Windows build links. That is a plausible access violation exactly on the Start
path, and it is Windows-only, which matches the report. Fixed with a `readers_live_` flag:
dropped/pending counters are only read while readers are actually running.

**Diagnostic scaffolding added, because the crash could not be reproduced here.** The viewer now
writes a step log next to the executable (`meta2-viewer.log`: open, port reset, reopen, arm file
and command count, liveness probe, readers started, threads running, then arm/warm/stall/re-arm),
and on Windows an unhandled-exception filter writes `meta2-viewer.exe.crash.log` with the
exception code, the faulting address, and the module that address belongs to. Verified in the
shipped binary by disassembly: `main` loads `&crash_filter` and calls
`SetUnhandledExceptionFilter`. Note GCC inlines short literals like `.crash.log` as immediates,
so that string is not contiguous in the image — do not conclude from `strings` that it is
missing.

**Still unverified.** The fixed binary has not run on Windows. This host's Wine cannot initialise
a prefix (`wine: could not load kernel32.dll, status c0000135`) even after adding the i386
multiarch and installing `wine32:i386` + `wine`; the Windows VM's SSH refuses every credential
available here, and no QGA socket exists. So the crash cause is inference, not observation, and
the honest statement is: one real Windows-breaking bug is fixed, the crash is not confirmed fixed.

**Device note:** the headset is currently attached to the Windows VM (`-device
usb-host,vendorid=0x2cfa`), so it is absent from the host bus and the Linux viewer now fails
`meta2_open` with `-2` (`LIBUSB_ERROR_NOENT`). That is the VM holding it, not a regression;
release it with QMP `device_del` when the host needs it.
