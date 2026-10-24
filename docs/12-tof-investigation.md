# 12. ToF / EP 0x84 investigation (E4)

Status: **the ToF endpoint streams, is fully calibrated, and is not missing any command we
could send — but it carries no range data, and neither does the vendor SDK.** The IR emitter
**is** active, and it is gated on the vendor SDK running (§12.7). The five commands the
SDK's own arm adds over ours have now been captured verbatim and do not explain the missing
range data (§12.11).

Everything below is from direct measurement unless marked *hypothesis*.

## 12.1 What EP 0x84 actually contains

Capture: mask `0x48` (ToF + STD), 12 s, EP 0x84 only → 74,612,736 B (6.22 MB/s),
7,664 trailer hits,
365 complete `352 × 288` frames.

| measure | value |
|---|---|
| value range | 0 … 4095 (12-bit container) |
| global mean / σ | 2040.4 / 125.1 |
| samples in 2000–2060 | 60.6 % |
| samples exactly 2048 | 0.94 % |
| samples > 4000 | 0.33 % |
| pixels that change over time | **99.66 %** |
| per-pixel temporal σ | mean 12.98, p95 17.64 |
| frame-to-frame \|Δ\| | median 5, p95 43 |

This corrects the earlier description of EP 0x84 as a "fixed pattern". It is a live,
noisy stream. What it lacks is *scene structure*, not temporal variation.

## 12.2 Row 0 is a sentinel row — calibration height 287 explained

`0xa886` reads back `0000 015f 0001 0120` → 351, 288 (0-based maxima) → 352 × 288, and the
payload is `352 × 288 × 2 = 202,752` bytes. The calibration XML, however, gives the depth
camera a height of **287**.

Reason, measured: row 0 is 4095 (the invalid marker) in **335 of its 352 columns**, mean
4013.8, while rows 1–287 average 2034–2049. Row 0 is not an image row. The payload is
288 rows; the calibrated image is 287.

## 12.3 Trailer and header fields

Trailer (32 B, u16 LE): sentinel `48879, 57005, 61453, 56029`, then `0, 0`, a frame
counter (`28638, 28639, 28640, …`), `2`, a field holding `278`, a field holding `288`
(the frame height), a varying field (`1092, 3276, 0, 0, …`), `0`, and three `4095`
sentinels.

Header (16 B before the sentinel): `47, 0`, a varying u32 timestamp, a second u32
(`4,277,199,354`-class value), `34, 34` (`0x22, 0x22`).

## 12.4 No USB command is missing

- `TimeOfFlightEndPointStateController.InternalEnableSensor` sets `_enableState = 8` and
  does nothing else. The driver's entire ToF enable is bit 8 of the endpoint feed mask,
  which our captures already send (`0x48`, `0x7e`).
- The capture harness's `arm` replays `ctrl_seq_full.json` — the vendor's full
  **417-transfer** sequence (`ok=279 fail=138`; every failure is a second IN transfer).
  That sequence contains **46 FPGA register writes**, including the whole ToF band:
  `0xa880`, `0xa882` (8-byte payload), `0xa88c`, `0xa88d`, `0xa88f`, `0xa892`, `0xa893`,
  `0xa886`.
- The USB configuration descriptor exposes one interface and four bulk **IN** endpoints
  and no bulk OUT. Every device control therefore travels over EP0; there is no other
  data path to send a ToF command through.

## 12.5 Config-before-stream ordering is not the cause

`royale.2.3.1.dll` contains *"BridgeEnclustra only supports changing use case when
stopped"*, which suggested our config writes might be ignored because the bulk readers
were already pending. Test `e4_config_first.py`: reset, replay the full sequence with **no
reader outstanding**, sustain feeds for 3 s, then start readers.

| run | order | EP 0x84 mean | σ | frames |
|---|---|---|---|---|
| `e4a` | readers first | 2040.4 | 125.1 | 365 |
| `e4b` | config first | 2034.2 | 124.7 | 1201 |

Statistically identical. Hypothesis rejected.

## 12.6 The vendor SDK gets no depth either

`MetaReader.exe` (our own client for `meta_core_api.dll`) was run in the Windows VM with
the headset attached. Its `meta_get_point_cloud` output, from run `live3`:

- `element vertex 101024` — exactly `352 × 287`, the ToF resolution.
- in run `live3`: **every coordinate is `0.0000`** in all 29 captured point clouds.
- in two later runs, parsed in Python after copying the `.ply` files out of the VM rather
  than with an in-shell regex:
  - `orch2`: 13 clouds × 101,024 = 1,313,312 points, **11 non-zero**, max magnitude 0.5813 m.
  - `ir1_c1`: 55 clouds × 101,024 = 5,556,320 points, **103 non-zero** (0.00185 %), 29 of the
    55 clouds contain any, magnitudes 0.36 – 0.67 m, largest 0.6735 m.

  So "every coordinate is zero" was literally true only for `live3`. The defensible statement
  is that the vendor point cloud is empty to within about 0.002 %, with a handful of points
  at plausible distances. `[CAPTURED]`
- `status.csv` reports `streams=4095` (`0xFFF`), i.e. the SDK marks
  `IMU0_ACC, IMU0_GYRO, IMU1_ACC, IMU1_GYRO, MONO0, MONO1, RGB, PCLOUD, DEPTH, IR, NOISE, CONF`
  all active.

So the official stack reports the DEPTH and IR streams as live and still produces an
all-zero point cloud. This matches EP 0x84 exactly: frames arrive, they carry no scene
information.

**Consequence:** the absence of range data in `meta2lib` is not a gap in our
implementation. The vendor stack's own depth output is empty in this state too.

**Caveat on how strong that is.** `meta_core_api.dll` exposes 63 `meta_*` exports and has
**no raw depth or ToF frame getter**. Depth reaches an application only through
`meta_get_point_cloud` (a fused SLAM output) and `meta_get_eye_depth_stencil` (an AR
occlusion buffer). So the all-zero point cloud proves the vendor pipeline produced no
usable depth, but it does not by itself prove the raw ToF stream was empty under the SDK,
because the point cloud also depends on tracking being initialised. In run `live3`,
`pose.csv` shows `tracking_state,tracking_reason` = `0,0` for 196 polls and `1,3` for 576
polls; the SDK's enum meaning is not documented in the shipped files, so `1,3` is not
confirmed to mean "tracking initialised".

The stronger argument is indirect but sound: the SDK consumes the same `EP 0x84` we read
directly, and `EP 0x84` carries no scene information under the full vendor command
sequence. Unless the SDK sends a command that changes what `EP 0x84` contains, the SDK
cannot obtain depth either - which is what the zero point cloud is consistent with.

`meta_start -> 0 (SUCCESS)` was confirmed in `probe.log` and `orch.log`, the SDK read the
serial number, and `orch.log` ended with `rgb_frames=111 pclouds=23 polls=646`, so the SDK
was genuinely running and streaming, not failing to start.

## 12.7 IR illumination: observed, and gated on the SDK running

An earlier version of this section stated that no IR illumination was observed. **That claim
is withdrawn.** The operator's camera is IR-sensitive (control test against a TV remote,
§12.9), so both the earlier negative and the new positive are meaningful.

Experiment `IR-1`: a self-driving coach (`re/ir1_coach.py`, phases rendered on the operator's
screen with a countdown and a wall clock) ran two full cycles of NO SDK → SDK RUNNING →
SDK STOPPED. `MetaReader.exe` was the SDK. Phase timestamps are in the run log.

| clock (UTC) | phase | SDK state | operator observation |
|---|---|---|---|
| 04:03:15 – 04:03:35 | NO SDK (cycle 1) | stopped | off |
| 04:03:35 – 04:04:54 | SDK RUNNING (cycle 1) | `MetaReader.exe` | **on** |
| 04:04:56 – 04:05:26 | SDK STOPPED (cycle 1) | stopped | off |
| 04:05:26 – 04:05:46 | NO SDK (cycle 2) | stopped | off |
| 04:05:47 – 04:07:33 | SDK RUNNING (cycle 2) | `MetaReader.exe` | **on** |
| 04:07:33 – 04:08:03 | SDK STOPPED (cycle 2) | stopped | off |

Four off-windows and two on-windows, every one matching its phase. `[CAPTURED]`: **the vendor
SDK run drives the emitter.** The companion half of that sentence — that our host-side replay
does **not** — is **withdrawn**; §12.15 shows a blinded test in which our own arm lights the
emitter in 8 of 8 armed trials and 0 of 8 un-armed trials.
Both SDK cycles genuinely streamed — `rgb_frames=272 pclouds=55 polls=1290` and
`rgb_frames=233 pclouds=47 polls=1133` — so the light is not an artifact of a process that
started and then did nothing.

The light is a purple glow from the front faceplate on the wearer's right. `unit_calib.xml`
places the `depth` camera optical centre at the rig origin (`x = 0.0000`), with `mono_left`
at `x = -0.0689`, `rgb` at `x = -0.0270` and `mono_right` at `x = +0.0691`; left to right
across the front face the order is mono_left, rgb, depth, mono_right. The described location
matches the depth camera. `[INFERRED]`

This retires the "the emitter is broken" hypothesis. It also sharpens §12.8 rather than
confirming it: the emitter lights under the SDK, yet `EP 0x84` still carries no scene
structure under the SDK's commands or ours, and the SDK's own point cloud is still empty
(§12.6). Illumination alone is not what makes a Royale phase output meaningful.

## 12.8 ToF stack identity

`Meta SDK2 Beta/bin` ships `royale.2.3.1.dll` and `royaleCAPI.2.3.1.dll` — Intel Royale, a
ToF processing stack. Strings of interest:

- Use cases: `UseCaseCalibration`, `UseCaseEightPhase`, `UseCaseFourPhase`,
  `UseCaseGrayScale`, `UseCaseTwoPhase`.
- `EightPhase`, `Amplitude`, `AmplitudeThreshold`, `ExposureReferenceAmplitude`,
  `AutoExposureRefAmplitude_Float`, `ExposureTimes`, `ExposureLimits`.
- *"exposure time reconfiguration failed, it is not allowed to set a new modulation PLL
  frequency"*.
- LED vocabulary: `CX3_UVC_LED`, `EVALBOARD_LED_STANDARD`,
  `EVALBOARD_INFINEON_IRS16X5C_EVALUATION_KIT_LED` — the IRS16X5C is an IR LED driver IC,
  so the illumination is active, not ambient.
- Bridge: `BridgeEnclustra` (Enclustra is an FPGA SoM vendor), `BridgeWithI2cSensors`,
  `SensorRoutingConfigI2c`, `SensorRoutingConfigSpi`, temperature sensors
  `TemperatureSensorTMP102`, `TemperatureSensorMCP98x43`.

A mid-scale value with noise and no scene dependence is consistent with a phase output
whose modulation/illumination is not running. *Hypothesis*, not established.

## 12.9 Physical-state experiments (all negative so far)

`e4_watch.py` logs per-second byte rates for all four endpoints plus EP 0x84 mean, sigma
and invalid-sample fraction, so operator actions correlate with timestamps. Mask `0x7e`,
mux `0x1b`, all four readers.

Run `e4c` (180 s):

| phase | EP 0x84 | ToF mean | sigma | invalid frac |
|---|---|---|---|---|
| 0-45 s baseline | 223.9 MB | 2049.5 | 896 | 0.0038 |
| 45-90 s single button press | 228.9 MB | 2049.3 | 888 | 0.0038 |
| 90-135 s hand 10 cm / 1 m in front of centre | 204.7 MB | 2050.5 | 924 | 0.0038 |

Run `e4d` (150 s):

| phase | EP 0x84 | ToF mean | sigma | invalid frac |
|---|---|---|---|---|
| 0-40 s baseline | 191.6 MB | 2049.0 | 893 | 0.0037 |
| 40-90 s button held 3 s | 246.4 MB | 2049.1 | 901 | 0.0037 |
| 90-150 s HDMI attached | 297.5 MB | 2048.2 | 875 | 0.0037 |

The ToF statistics are invariant to within noise across every action. Mono (`EP 0x82`)
dropped to 0 B/s during the last two phases of `e4d`, the known hysteretic mono state;
that is unrelated to the ToF result.

Run `e4i` — the valid one. A self-driving coach (`e4_coach.py` + `verify/coach.html`)
put COVER / UNCOVER / HAND AT 10 CM / HAND AT 1 METRE on the operator's screen with a
countdown, so actions were timestamped automatically. 138 s, **zero silent seconds, zero
re-arms**, display on, all phases measured:

| phase | ToF mean | sigma | invalid frac |
|---|---|---|---|
| GET READY | 2048.27 | 869 | 0.00370 |
| COVER NOW (1) | 2048.61 | 881 | 0.00368 |
| UNCOVER (1) | 2048.97 | 905 | 0.00368 |
| COVER NOW (2) | 2048.46 | 885 | 0.00365 |
| UNCOVER (2) | 2049.09 | 894 | 0.00372 |
| COVER NOW (3) | 2049.94 | 932 | 0.00365 |
| UNCOVER (3) | 2049.28 | 916 | 0.00373 |
| HAND AT 10 CM (1) | 2048.77 | 890 | 0.00370 |
| HAND AT 1 METRE | 2049.94 | 937 | 0.00365 |
| HAND AT 10 CM (2) | 2048.78 | 900 | 0.00368 |
| HANDS OFF | 2047.66 | 852 | 0.00368 |

The spread across every phase is **2.3 counts out of 2048**. Covering the entire front
face with both hands, and a hand at 10 cm versus 1 m, are indistinguishable.

**Why the covering is known to be effective:** the earlier occlusion experiment
(`occlusion2_stats.json`) measured `EP 0x83` mean falling 55 % and `EP 0x82` falling 59 %
under cover-all, with `EP 0x84` moving 0.3 %. The same physical intervention moves the
optical endpoints massively and the ToF not at all. That is the cleanest statement E4
produces.

Two harness failures worth recording so they are not repeated:
- `e4g` first attempt delivered **0 bytes on every endpoint for 135 s** because the coach
  script omitted the full vendor arm and only sent sustaining feeds, after a killed run had
  left the device in its dead state. A capture script that does not send `ctrl_seq_full.json`
  will silently produce nothing.
- `e4g` second attempt collapsed to zero bytes at t=45 s mid-run. The untouched dry run
  (`e4h`) held 138 s with zero silences, so the collapse is state-dependent, not inherent.
  `e4_coach.py` now re-arms automatically after 5 s of total silence.

Operator observations:
- The headset's status button blinks **slow pink** with PSU + USB connected. A single press
  and a 3 s hold both leave the blink unchanged, and it still blinks slowly with the HDMI
  display connected and lit.
- The operator's phone camera **is** IR-sensitive (verified against a TV remote), so the
  absence of visible IR from the headset is a meaningful negative result.

## 12.10 Open questions

1. ~~Is the operator's camera actually IR-sensitive?~~ **Answered: yes.** Control test
   against a working TV remote. The negatives in §12.9 and the positive in §12.7 both stand.
2. What is the headset's own power state? The IR LED driver may be enabled by the
   headset's SoC rather than by anything reachable over USB. Still open.
3. ~~Does the vendor SDK, run live with the device attached, cause the emitter to fire?~~
   **Answered: yes**, 2/2 cycles (§12.7). The enable path is therefore *not* outside the
   USB-observable world — but it is also not any command we had recorded, and it is not one
   of the five commands the SDK adds over ours (§12.11).
4. ~~`Meta.OOBE.exe` and `Diagnostics/Meta.SimpleDiagnostics.exe` are untested vendor tools~~
   **Corrected: `Meta.SimpleDiagnostics.exe` and `Meta.DisplayManager.exe` do not exist.**
   `[VERIFIED]` `Meta SDK2 Beta/Utilities` contains `firmware-update.exe`,
   `Meta.FirmwareUpdate.exe`, `Meta.OOBE.exe`, `Meta.SystemTray.exe`, `WorkspaceHelper.exe`;
   `Apps` contains only `Eye Alignment`. `Meta.SystemTray.exe` has now been run and captured
   (IR-21, IR-22): it sends a `13 00 …` command family that `MetaReader.exe` never sends, and
   that family **tears the bulk streams down** rather than enabling anything. See
   `EVIDENCE.md` §13. `Meta.OOBE.exe` and `Eye Alignment` remain untested. The two
   firmware-update programs are out of scope (SPI-flash path).
5. New and currently the sharpest question: the SDK lights the emitter, and the five
   commands its arm adds over ours change neither the register block they touch nor
   `EP 0x84`. So what does the SDK do that is *not* a vendor control transfer? Narrowed by
   IR-21/IR-22 `[VERIFIED]`: **SET_INTERFACE is never sent** (zero `bRequest 0x0B` in a full
   SDK session), so the FX3 alternate-setting idea is out; the only non-vendor requests are
   `SET_CONFIGURATION`, `SET_FEATURE` and two unexplained `bmRequestType 0x00 bRequest 0x30 /
   0x31` transfers that occur at every attach before any app runs. Remaining candidates: a
   timing/ordering requirement in the vendor sequence, a command issued by a vendor app other
   than `MetaReader.exe`, or something on the headset's own SoC.
6. `meta2_host_itf.dll` exports `ConfigureLed(...)` and `ConfigureTofCamera(...)` on its
   driver-manager and init-config adapters, and `meta2_host_impl.dll` has a `LedConfig`
   struct and `SetExposure`/`GetExposure`. `[VERIFIED]` export tables. **No wire command has
   yet been attributed to any of them.** `[UNKNOWN]`

## 12.11 IR-4: the vendor driver's own control traffic, captured from a cold start

Method. `tcpdump` on the host `usbmon` interface for the bus carrying the headset, snaplen
1024 so control payloads are captured whole. Two events inside one capture: a forced
re-enumeration of the passthrough device (QMP `device_del` then `device_add`) so the Windows
vendor driver initialises from scratch, then a 20 s `MetaReader.exe` run. USB passthrough
does not hide anything here: every URB the guest submits still goes through the host kernel,
so `usbmon` sees the guest driver's transfers. 1108 control URBs, 554 SUBMITs, 6.3 MB.

Extraction used `tshark -T fields` with `usb.bmRequestType`, `usb.setup.bRequest`,
`usb.setup.wValue`, `usb.setup.wIndex`, `usb.setup.wLength`, `usb.data_fragment`. Note that
tshark formats `wValue` as hex and `wIndex`/`wLength` as decimal in this dissector; mixing
those up is what corrupted `arm_full.txt` (§12.12).

**Finding 1 — the vendor driver sends no vendor commands during enumeration.** `[VERIFIED]`
All 134 vendor OUTs (`bRequest 0xC0`) begin 19.7 s after capture start, i.e. after
`MetaReader.exe` launched. Everything the driver does at enumeration is standard:
`GET DESCRIPTOR` DEVICE / CONFIGURATION / BOS / STRING, `SET FEATURE`, `SET ISOCH DELAY`, and
hub `GET_STATUS` with `PORT_RESET`, `C_PORT_RESET`, `C_PORT_CONNECTION`,
`C_PORT_LINK_STATE`. The hypothesis that motivated IR-4 — that the emitter enable happens
during first enumeration and our original mid-stream capture missed it — is **false**. There
is no hidden init command.

**Finding 2 — the SDK's arm differs from ours by exactly five commands.** `[VERIFIED]`
129 shared, 5 driver-only, 9 arm-only, compared by payload content.

| driver-only command | what it is |
|---|---|
| `3d 60 b800` + 916 data bytes | a **920-byte write** to register `0xb800`, `wValue=3`, `wIndex = wLength = 920` |
| `3d 21 b800` + 256 × `0xFF` | wide read, paired vendor IN of 257 bytes |
| `3d 21 b880` + 256 × `0xFF` | wide read, paired vendor IN of 257 bytes |
| `3d 21 b900` + 256 × `0xFF` | wide read, paired vendor IN of 257 bytes |
| `3d 21 b980` + 148 × `0xFF` | wide read, paired vendor IN of 149 bytes |

The nine arm-only commands are mostly artifacts of the original capture: five have empty
payloads (their data fragments were lost), two are `0000030020` at `wValue=1`, one is
`wValue=253` with no payload, and one is the `hwinfob` write already proven droppable by
leave-one-out.

**Finding 3 — the 920-byte blob is not the lever.** `[CAPTURED]` With the headset held by our
own libusb client, after a port reset:

- Registers `0xb800`, `0xb880`, `0xb900`, `0xb980` are **not empty**: 233/256, 243/256,
  232/256 and 134/148 bytes non-zero, status byte `0x00` on every read.
- Writing the SDK's exact 920-byte blob changed **0 of 257, 0 of 257, 0 of 257 and 0 of 149**
  readable bytes. The blob's own bytes do not match what the registers return, so this is not
  the SDK writing back what it read.
- `EP 0x84` is unchanged by it. Two 12 s captures, same harness, port reset first, sustaining
  strobe in both:

  | run | throughput | `0x0FFF` sentinels | mean sample | frame markers |
  |---|---|---|---|---|
  | strobe only | 33.3 MB/s | 0.32 % | 2043.5 | 377 |
  | blob + strobe | 33.3 MB/s | 0.34 % | 2041.1 | 238 |

  A first control run reported 0.2 MB/s; its reader thread died on a USB error. The figures
  above are from the re-run with `reader errors=0` and `dropped` accounted for.

**Finding 4 — the lag-704 stride candidate gets no support at scale.** `[VERIFIED]` In both
captures above, mean |difference| at lag 704 against a random-pair baseline gives contrast
of **−1.1 %** and **+3.5 %** over 20 M samples. The 25 % figure that made 704 the leading
candidate came from a 1 M-sample capture and does not reproduce. `docs/08` already replaced
the guess with a register read-back naming `352 × 288`; this is independent confirmation that
the autocorrelation route was measuring noise.

## 12.12 `arm_full.txt` has a corrupt `wIndex` column

`[VERIFIED]` In the freshly captured sequence, **0 of 134** vendor OUTs have
`wIndex != payload length`, which independently confirms the grammar recorded in
`docs/04-control-protocol.md`: for vendor OUTs, `wIndex == wLength == payload length`.

In `meta2lib/data/arm_full.txt`, **27 of 138** OUT lines have `wIndex != payload length`, and
131 of 138 match `wIndex = int(str(true_value), 16)` — the original extractor applied base 16
to tshark's *decimal*-formatted output, so a true `wIndex` of 20 was recorded as 32.

Consequence for the library: `meta2_capture.c` reads the column with `%d` and transmits the
inflated value. `wLength` is derived from the payload length, not from the file, which is why
arming still works. The corrected sequence, captured live and self-consistent, is committed
as `meta2lib/data/arm_driver.txt`.

## 12.13 The depth path has a host-side mode register: `0xb00e`

This is the first control found that a host can use to change what EP `0x84` emits. Full
measurements in `docs/EVIDENCE.md` §17.5.

The vendor writes it once, inside the arm, as
`OUT bRequest 0xC0 wValue 3 wIndex 24 wLength 24` with payload
`3d 60 b00e` + `15 15 15 15 15 15 15 15 15 15 15 15 13 15 15 13 15 15 04 15`.
`3d` is the frame tag, `60` is the write opcode, `b00e` is the register address.

Substituting a uniform byte value into all 20 data positions, in place, changes EP `0x84`
according to this rule — tested on 23 values with no exceptions:

| condition on the byte | EP `0x84` |
|---|---|
| bit1 `0x02` set | every sample is the `0x0FFF` invalid sentinel |
| bit1 clear, bit2 `0x04` set | 12-bit data, mean 2037, sd 142, ~570 distinct values |
| bit1, bit2 clear, bit4 `0x10` set | endpoint emits nothing |
| bit1, bit2, bit4 clear | near-zero output (`0x01`), or broken framing at 0.01 MB/s (`0x08`, `0x09`) |

Two constraints a library must respect:

1. **Position matters.** Writing `0xb00e` after the arm finishes collapses every bulk endpoint to
   zero, even with the vendor's own opcode and bytes. It has to be written where the vendor writes
   it, before the transfers that follow.
2. **It must be written at all.** Dropping only this one write leaves EP `0x84` streaming at
   normal rate with 100% invalid samples. Dropping the whole `0xa880`–`0xa893` + `0xb00e` band
   silences the endpoint.

`[UNKNOWN]` whether the 20 bytes are 20 independent settings or one 160-bit field. The vendor's
own value mixes `0x15` (data-producing) with two `0x13` and one `0x04`, which is consistent with
a per-frame schedule in which some frames are deliberately invalidated; that has not been tested.

`[UNKNOWN]`, and it is the blocking question for the proof of concept: the data-producing modes
all yield the *same* distribution — mean 2037, sd 142, quartiles 2007/2029/2052 — regardless of
the value used. Nothing observed so far makes that band respond to anything. The test that would
settle it is a scene change with every register held constant, which needs physical access to the
headset.

`0xB8`, previously recorded as lethal, is not: 1,056 probes left the device streaming normally
(`docs/EVIDENCE.md` §17.1). It answers `00 00 idx hi lo` with a 33-byte window, carries `PMDTEC`,
`PMDSCL` and a `22.09.2017` build stamp for index 0..7, and is a plausible route to the PMD module
manifest — but its index-to-window mapping is not yet understood.

## 12.14 EP 0x84 frame layout, and the fact that it does not see the scene

Two things a library needs from this endpoint, both now measured. Full detail in
`docs/EVIDENCE.md` §18.

**The frame.** Each frame is a 32-byte descriptor block followed by 101,376 samples of body —
101,392 samples, 202,784 bytes, and 101,376 = 352 × 288. The descriptor block is identified by six
magic values at fixed slots:

```
slot  0  0xDEAD    slot  6  0x0004
slot  1  0xF00D    slot  7  0x0244 (580)   in 335/605 blocks
slot  2  0xDADD    slot  8  0x0000         in 335/605 blocks
slot  3  0x0000    slot  9  0x0120 (288)   in 198/605 blocks
slot  4  0x0000    slot 10  0x00C6 (198)   in  73/605 blocks
slot  5  varies    slot 11  0xABBA / 0x0000
slot 12  0xFEED / 0x0FFF
slot 13  0x0022 / 0x0FFF
slot 14  0x0022 / 0x0FFF
slot 15  0xBEEF / 0x0FFF
```

Blocks arrive in runs (1..9 blocks back to back). In 130 of 269 inter-run gaps the distance from the
end of one run to the start of the next is exactly 101,392 samples. The other 139 gaps are partial —
61,376 / 57,280 / 60,176 / 64,368 samples and so on — because transfers are being lost, the
slice-and-tear problem in `docs/05`. A parser must therefore resynchronise on `0xDEAD` rather than
trust a fixed stride.

**The body does not respond to the scene.** Seven physical conditions, 60 s each, operator-coached:
baseline, palm over the front, opaque cloth, wall at 15 cm, wall across the room, floor directly
below, and a repeat baseline. Every mean fell within 0.23 counts of the pooled no-scene reference
(2037.397, sd 0.313), and the two *identical* conditions differed from each other by 0.163 counts at
t = 2.95 — larger than four of the five scene conditions. Median per-second quartiles were
2007 / 2030 / 2052 in every second of every condition.

`[VERIFIED]` It is also not a fixed pattern: 0 duplicated transfers in 697, and transfer-to-transfer
byte identity is flat at 30.1% across every lag, which is exactly what a constant high byte plus a
varying low byte produces.

So the body is well-formed, correctly framed, internally structured, and blind.

**The earlier `[INFERRED]` explanation — that illumination is off under the host-only arm — is
now falsified** (§12.15: our arm lights the front IR emitter in 8/8 blinded armed trials). The
remaining candidates are therefore that (a) the emitter is on but the **modulation** is not
running or not synchronised, (b) the plane we read is not a correlation image at all but a
quality/confidence map, or (c) the depth path needs a configuration step that is not a vendor
control transfer. `[UNKNOWN]` which of these it is.

## 12.15 The host-only arm lights the front IR emitter — blinded test `[VERIFIED]`

This reverses the conclusion of §12.7 and falsifies the explanation offered in §12.14.

**Detector validated first.** The operator's phone camera saw an IR flash from a TV remote
(`illum_obs.jsonl`, phase `phone_control`). Without this control, a negative is meaningless.

**Design** (`re/illum_blind.py`). The operator sees only "Trial N of 16 — is there a glow?".
The script chooses, from a seeded random balanced order, whether the device is **armed and
streaming** or **port-reset and idle**, and records the ground truth beside the answer. The
coach page is deliberately given no throughput, no arm countdown and no state name, so the
operator cannot infer the condition. Each trial also measures EP `0x84` throughput during the
14 s observation window, so the optical claim is corroborated electrically.

- armed: `reset_open()`, full `ctrl_seq_full.json` arm, then continuous `sets()` strobe
- idle: `open_device()`, `dev.reset()`, `finalize()`, reopen, claim, **no control traffic at all**

**Run 2 — 16 trials, seed 1792809976,** order
`idle arm arm arm idle idle arm idle arm idle idle arm arm idle idle arm`:

| trial | truth | EP `0x84` | answer |
|---|---|---|---|
| 1, 5, 6, 8, 10, 11, 14, 15 | idle | 0.00 MB/s | NO GLOW |
| 2, 3, 4, 7, 9, 12, 13, 16 | arm | 13.45 – 14.08 MB/s | **GLOW** |

**8/8 armed → GLOW. 8/8 un-armed → NO GLOW. Perfect separation.** Fisher exact one-sided
**p = 7.77 × 10⁻⁵**. The probability that 16 answers all match ground truth by chance is
2⁻¹⁶ = 1.53 × 10⁻⁵.

**Run 1 — 8 trials, seed 1792808896** — armed 3/4, un-armed 0/4, p = 0.071. Not significant on
its own; the single miss was trial 1, where the gate advanced before the operator was looking.
Pooled across both runs: armed 11/12, un-armed 0/12, **p = 4.81 × 10⁻⁶**.

**Supporting single observations** (`illum_obs.jsonl`): glow reported while armed at
02:22:42Z; no glow reported at 02:25:08Z, which was after the 150 s arm had already ended; and
"Glow is GONE" in the un-armed control at 02:27:26Z, during a 60-second window measured at
0.000 MB/s on every endpoint (`ir52_idle.jsonl`).

**What is established.** An IR emitter at the front of the headset is on when our host-only
vendor arm is applied and off when the device is port-reset and un-armed. `[VERIFIED]`

**What is not established.** That this emitter is specifically the ToF illuminator rather than
another front-facing IR LED. It is the only front IR emitter described, and §12.7 places the
depth camera at the front centre where the glow was seen, so the identification is
`[INFERRED]`, not shown.

**Consequence.** The §12.14 explanation for scene-blindness — illumination off — is dead. The
depth path is illuminated and streaming, and still does not respond to a palm, an opaque cloth,
a wall at 15 cm or a wall at 4 m. The missing ingredient is modulation, or the plane is not a
range image.

**Method note.** A first attempt at this test (`re/illum_coach.py` + `illum_hostarm.py` +
`illum_idle.py`) was non-blinded and is reported only as supporting evidence. The blinded
design is the one that carries the conclusion. A unit bug in `illum_blind.py` printed
`bytes / 1e6` over the whole 14 s window as `mb_s`; the table above is corrected to true MB/s.

## 12.16 Attacking the registers instead of the scene: IR-56, IR-57, IR-58

The scene test (§12.14) and the illumination test (§12.15) removed two candidate explanations for
why the depth body does not see the room. What is left is the configuration itself: the depth path
is armed by a band of writes in `0xa880`–`0xa893` plus the `0xb00e` table, and we have never
established what any of them *mean*. IR-56, IR-57 and IR-58 probe those registers directly, with no
physical task and no scene dependence. Full data and tables: `EVIDENCE.md` §22.

**`0xb00e` is a structured table, not a repeated mode byte.** Perturbing one byte at a time moves
the output at 10 of 20 positions, against a control drift of 0.28 counts. Sensitivity grows by a
factor of ~3–4 per 2-byte slot across slots 0–5 (Δmean 1.29, 4.27, 15.93, 37.86, 150.17, 1438.78)
and then collapses to under 1.2 counts for slots 6–9. The high-byte/low-byte effect ratio is
~1.6–2.3 rather than ~255, so the table is not ten independent linear 16-bit knobs. The three
positions the vendor sets away from `0x15` (12, 15, 18) are precisely the insensitive ones.

**`0xa886` is the first register in the band with a readable meaning.** Its data is four big-endian
`u16` values: `0, 351, 1, 288` — a window spanning x 0…351 and y **1**…288. The wire frame is
352×288 and the calibrated image is 352×287, so the row-0 sentinel is a configured exclusion, not
an artifact. Corroborating byte sensitivity: destroying the low byte of either x bound (byte 1, or
byte 3 which turns 351 into 350) silences EP 0x84 entirely, while destroying the high bytes of the
y bounds produces the same broken-but-populated output in both cases (mean 2092.30 / 2094.27,
sd 369.7 / 369.3, sentinel 3.093% in both).

**`0xa882` carries a live parameter in its 4-byte write.** `op 0x60` is `02 80 10 57`; flipping one
bit of the last byte (`57` → `56`) moves the mean by −49.9 counts, **narrows** the support from 564
distinct sample values to 237, and **raises** the endpoint rate from 9.55 to 14.04 MB/s. Narrowing
while speeding up is not a failure mode. This is the strongest remaining candidate for a genuine
integration or modulation parameter, and it is the natural next thing to sweep.

By contrast, in the 8-byte `op 0xa0` form of the same register the first five bytes are inert, byte
5 breaks framing, byte 6 triples the distinct-value count without changing mean or sd, and byte 7
makes the output **bimodal** (mean 3046.54, sd 1592.79, quartiles 1/2029/4022/4060/4095) — mass
piled at both the floor and the invalid ceiling.

**`0xa88f` is a stepped selector, not a bias.** IR-50's "+391 counts, rigidly" looked additive. A
13-point sweep rejects linearity: `mean = 0.258 × value + 1972.8`, R² = 0.685, worst residual +194
counts. The real structure is discrete levels (~2022, ~2037, ~2089, ~2431, ~2476) selected such
that the high byte has a single threshold between 3 and 4 and is otherwise ignored, while the low
byte acts non-monotonically. 0x00ff and 0x0100 differ by one count and produce outputs 67 counts
apart.

**What this does not yet buy us.** None of these runs tested whether a register setting makes the
depth body scene-responsive; they tested whether registers affect the output at all. They do,
strongly, and none of them behaves linearly — which weakens the model "output = f(scene) + register
offsets" and points instead at a device whose depth body is assembled from discrete configuration
levels. The next decisive step is to sweep `0xa882 op 0x60` byte 3 and `0xb00e` slot 5 finely and
look for a setting where the distribution becomes scene-dependent, rather than merely shifted.

## 12.17 The registers are mode selectors, and what they select is a device-fixed pattern

IR-56 through IR-61b were all host-only. Full data: `EVIDENCE.md` §22–§25.

**The registers are live, and none of them is a linear knob.** `0xb00e` changes the output at 10 of
20 byte positions against a control drift of 0.28 counts, with sensitivity growing ~3–4× per slot
across slots 0–5 and then collapsing. `0xa882 op 0x60` byte 3 resolves into five discrete modes
(flat, vendor, narrow-and-fast, broken, all-invalid) with mean-fit R² = 0.0124. `0xa88f` resolves
into stepped levels with R² = 0.685 and a +194-count worst residual. `0xb00e` slot 5 produces ten
recurring output signatures, and the slope ratio between its high and low byte is 0.01 where a single
linear 16-bit value predicts 256.

**`0xa886` is the one register with a readable meaning:** `0000 015f 0001 0120` = 0, 351, 1, 288 — a
window of x 0…351 and y **1**…288, which makes the row-0 sentinel a configured exclusion rather than
an artifact.

**The frame is not organised by the table.** Perturbing `0xb00e` slot 5 changes all 288 rows and all
352 columns, and per-row means stay flat. The idea that the table's ten slots index ten regions of
the image is refuted.

**The frame is a pattern the device generates.** With 2,295 frames per pass and three independent
arms, the vendor configuration gives within-arm split-half correlation **0.9950** and cross-reset
correlation **0.9567** with a mean absolute difference of 4.27 counts. Two of three arms agree very
closely; the third landed in a different state. So EP 0x84 under our arm is stable within an arm and
reproducible across a port reset — which is consistent with the negative scene test and with the
register-level shifts, and inconsistent with both random noise and room-dependent data.

**Where that leaves the ToF goal.** We can obtain, frame, geometry-check, mode-select and
reproducibly reproduce the depth endpoint. We still cannot interpret its samples as distance, and we
now have a precise reason: the registers choose *which level* a generated pattern reports, and no
register setting found so far puts the device into a state where the reported value depends on the
room. The remaining unknown is the configuration that enables measuring, and the vendor SDK is the
only known producer of that state. The next decisive experiment is SDK-side: read the depth the SDK
itself reports and test whether it responds to the scene.

### 12.18 The SDK-side depth test is negative: the SDK's point cloud is a fixed 2.45 m shell

That experiment ran as IR-55 and its follow-up IR-55b. Both used `reader/MetaDepth.cs` inside the
Windows VM: `meta_start()`, `meta_start_reconstruction()`, `meta_reset_reconstruction()` at each
phase boundary, then `meta_get_point_cloud` (101,024 slots = 352 × 288, metres) polled every ~100 ms,
plus `meta_get_reconstruction_mesh`, `meta_get_tracking_status` and `meta_get_rgb_frame` as a camera
control. Phases were pushed to the guest and every one was click-gated by a coach page.

**IR-55 — five conditions, 60 s each.**

| phase | polls with points | max points | distance bins |
|---|---|---|---|
| `init_motion` | 92 / 782 | 8 | 1–3 m |
| `wall_close` (~30 cm) | 0 / 772 | 0 | — |
| `wall_far` (~2 m) | 33 / 790 | 3,132 | 1–3 m |
| `cameras_covered` | 26 / 609 | 17,395 | 1–3 m |
| `wall_close_repeat` | 0 / 494 | 0 | — |

`meta_get_reconstruction_mesh` returned **0 vertices** and `meta_get_tracking_status` returned
**0/0** in all 3,881 polls. Every non-zero point fell in the 1–3 m bin; **no point was ever in the
0.3–1 m bin**; the maximum radius was pinned at **2.487–2.488 m** in every burst.

**IR-55b — range map, 45 s each, same wall, with spike-triggered coordinate dumps.**

| phase | polls with points | max points |
|---|---|---|
| `wall_2m` | 0 / 418 | 0 |
| `wall_1m` | 0 / 416 | 0 |
| `wall_05m` | 0 / 587 | 0 |
| `wall_03m` | 4 / 587 | 3,864 |
| `cover_03m` | 113 / 374 | 1,167 |

The 30 spike dumps contain 13,412 points at radius ≥ 0.1 m and 5,311 points at radius < 0.1 m. The
far points form **one thin shell**: pooled mean radius **2.4465 m**, per-spike standard deviation
**0.021–0.027 m**, hard maximum **2.4876 m** — identical in every spike, including the spike taken
while the wall was **30 cm** away. The shell radius does not move when the wall moves.

So the SDK's point cloud is not measured depth. It is a fixed-radius artifact at ~2.45 m whose
*presence* is intermittent and whose *radius* is a constant of the pipeline — the same 2.488 m ceiling
that bounded IR-55.

**Camera control confirms the SDK link is live.** `meta_get_rgb_frame` produced real images in every
phase: room, out-of-focus close wall, room at distance, near-total black when covered. The failure is
specific to the depth/reconstruction output, not to the device link.

**Two caveats, stated explicitly.**

1. In both runs the SDK's stream mask was `0xFCF`: IMU ×4, RGB, PCLOUD, DEPTH, IR, NOISE, CONF active
   and **MONO0/MONO1 absent**, and the SDK never localized (`track=0/0`, 0 mesh vertices). §12.19
   later showed the point cloud is *not* a SLAM product — it is an output of `DeviceStreamBlock`, the
   device's own depth product — so missing mono input does not explain an empty point cloud. What is
   *established* is that the depth output the SDK produces is a fixed 2.45 m shell; what is *not*
   established is whether any configuration makes that output scene-metric.
2. IR-55's `wall_close_repeat` control is compromised: its RGB frames came back dark (mean 26.8
   against 85.8 for `wall_close`), so the cloth was probably still covering the headset. And burst
   *presence* did not reproduce between runs — IR-55 had bursts at 2 m and covered with none at 30 cm,
   IR-55b had none at 2 m / 1 m / 50 cm and bursts at 30 cm and covered. Burst presence is not a
   reliable signal; the shell radius is.

### 12.19 What the SDK's depth block actually is: Royale over an SAQ USB bridge

Reading `meta_block_device_stream.dll` settles the architecture question §12.1–§12.18 had been
circling. `DeviceStreamBlock` owns `std::unique_ptr<royale::ICameraDevice>` and
`std::unique_ptr<royale::IDepthDataListener>` (a `RoyaleDataListener`) and registers a callback taking
`royale::DepthData const*`. In the graph schema embedded in `meta_core_api.dll`, the
`point_cloud_OUT` port that feeds `CompositorBlock`, `HandsDataPreprocessingBlock0` and
`EnvironmentReconstructionBlock` is an **output of `DeviceStreamBlock`** — the point cloud is the
device's depth product, not a reconstruction product.

`royale.2.3.1.dll` carries the HAL that talks to this device over USB:

- `royale::usb::bridge::BridgeSAQBase`, `BridgeImagerSAQ`, `royale::usb::enumerator::BusEnumeratorSAQ`,
  `royale::usb::pal::saq::I2cAccessSAQ`, all parameterised on `sdc::SAQDriverManagerAdapterCls` — the
  same "SAQ" name the vendor driver uses. **The vendor control protocol we decoded is Royale's SAQ
  bridge protocol.**
- Imagers `ImagerM2450` (`A11`, `A12_SR`, `A12_SSC`, `DirectAccess`) and `ImagerM2452` (`A11`,
  `A11_SR`, `A11_SSC`, `B1x_SR`, …), with `DphyPllStrategyM2450_A12`, `ModPllStrategyM2450_A12`,
  `ModPllStrategyM2452_A11`.
- Modulation is expressed as Royale *use cases*: `UseCaseTwoPhase`, `UseCaseFourPhase`,
  `UseCaseEightPhase`, `UseCaseGrayScale`, `UseCaseCalibration`, carrying `ExposureGray`,
  `IntensityPhaseOrder`, `ExposureTimes`, `ExposureReferenceAmplitude`,
  `AutoExposureRefAmplitude_Float`, executed through
  `BridgeSAQBase::executeUseCase(uint64, int, int, uint64)`.
- Processing is configured through `royale::setProcessingParameters(Vector<Pair<ProcessingFlag,
  Variant>>)` / `getProcessingParameters`, with `getProcessingFlagName` naming each flag.

The graph itself is also readable (`re/sdk_graph_schema.txt`, extracted from `meta_core_api.dll`):
`DeviceStreamBlock` has attributes `enable_depth=true`, `enable_royale_recording=false`,
`royale_recording_filename=""`, and the graph wires `mono0_OUT`/`mono1_OUT` into `VSlamBlock`,
`depth_OUT`, `ir_OUT`, `point_cloud_noise_OUT` and `point_cloud_confidence_OUT`.

That is the vocabulary the missing "measuring state" would be expressed in.

### 12.20 IR-63 — the 920-byte `0xb800` blob is inert for the depth stream `[VERIFIED]`

The wire census (`arm_full2.txt`, 138 OUTs) contains one transfer larger than anything else the vendor
driver sends: a **920-byte write to `0xb800`**, followed by reads of `0xb800`, `0xb880`, `0xb900`,
`0xb980`. Every host-side probe so far used `ctrl_seq_full.json`, whose largest write is 40 bytes —
so the arm we have been streaming with **never contained that blob**. IR-6 had tested a `0xb800` blob
write and found it inert, but as an isolated write, and IR-46 later proved that a write issued outside
its arm position collapses the bulk endpoints; that null result was not conclusive.

IR-63 inserts the blob **in place** in the working arm, bracketed by controls.

| variant | EP 0x84 MB/s | mean | sd | sentinel % |
|---|---|---|---|---|
| control | 8.98 | 2037.31 | 141.85 | 0.407 |
| `0xb800` blob inserted in place | 9.18 | 2037.44 | 141.99 | 0.409 |
| `0xb800` slot inserted, data zeroed | 8.90 | 2037.58 | 143.20 | 0.416 |
| `0xb800` blob appended at arm end | 0.00 | — | — | — |
| `0xc2bc` table zeroed | 7.10 | 2042.81 | 146.89 | 0.442 |
| control again | 9.14 | 2037.13 | 140.35 | 0.397 |

Control-to-control drift **0.18 counts**. The blob moves the mean by **0.13 counts** — inside the
drift. Appending it at the end kills every endpoint, reconfirming the in-place rule. The largest
configuration write the vendor driver performs therefore has no measurable effect on what the depth
endpoint reports, and the "we were missing the modulation table" hypothesis is closed for that
transfer.

**What did move:** zeroing the 40-byte payload of the `3da0c2bc` write shifted mean by **+5.5 counts**
(30× the drift), raised sd from 141 to 147 and cut EP 0x84 from 8.98 to 7.10 MB/s. `0xc2bc` is a live
parameter no probe had touched. Its vendor payload is a table, not a scalar:

```
004e 0000 2000 0000 08d3 0000 000a 0001 08d3 0000 004e 0001 08d3 0000 0082 0001 08d3 03ac 00c6 0001
```

with `0x08d3` recurring. IR-64 sweeps its bytes one at a time.
