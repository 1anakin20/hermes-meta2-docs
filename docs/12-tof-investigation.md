# 12. ToF / EP 0x84 investigation (E4)

Status: **the ToF endpoint streams, is fully calibrated, and is not missing any command we
could send — but it carries no range data, and neither does the vendor SDK.** The IR
illumination is not active in the current device state.

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
- **every coordinate is `0.0000`** in all 29 captured point clouds.
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

## 12.7 No IR illumination observed

The operator pointed a camera at the headset, including during the config-first run, and
saw **no light coming from the headset**. *Not yet sanity-checked:* it has not been
confirmed that the operator's camera renders IR at all (see §12.9).

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

Operator observations:
- The headset's status button blinks **slow pink** with PSU + USB connected and HDMI
  disconnected. A single press and a 3 s hold both leave the blink unchanged.
- The operator's phone camera **is** IR-sensitive (verified against a TV remote), so the
  absence of visible IR from the headset is a meaningful negative result.

## 12.10 Open questions

1. Is the operator's camera actually IR-sensitive? Control test: point it at a working TV
   remote and press a button; if the remote's LED appears as a bright dot, the camera
   renders IR and the negative result on the headset is meaningful.
2. What is the headset's own power state? The IR LED driver may be enabled by the
   headset's SoC rather than by anything reachable over USB.
3. Does the vendor SDK, run live with the device attached, cause the emitter to fire? If
   it does not, the enable path is outside the USB command set.
4. `Meta.OOBE.exe` ("Setup Headset") and `Diagnostics/Meta.SimpleDiagnostics.exe`
   ("Meta Diagnostic", contains `diagMeta2Calibration`) are untested vendor tools that may
   put the headset into a fuller mode.
