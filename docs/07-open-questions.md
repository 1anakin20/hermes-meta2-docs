# 7. Open questions

Each item states what is known, what is not, and the specific experiment that would
close it. Nothing here is hand-waved.

## 7.1 The streaming trigger — SOLVED 2026-10-16

**Solved:** continuous full-frame streaming works with no SDK. The requirement is that bulk
URBs are already **pending** on the endpoints while control traffic is in flight. A
handshake-then-read client gets one 65,536-byte URB per endpoint; a client that keeps a
looping reader on each endpoint running gets 100 to 155 full 1280x720 frames per 12 s.
`[VERIFIED]`

Data flows only while control transfers are running — **from a quiescent device**. That
sentence was too strong and has been narrowed. After a port reset, a 10 s window with zero
control transfers produced 304 frame records (30.35 fps) on EP 0x83, when the device had
been armed by an earlier session. `[CAPTURED]` Control traffic is what starts and sustains
streaming; a device already left armed can free-run. Which state the device is in is
`[UNKNOWN]`, and it is the same unknown as the hysteresis below.

**2026-10-21: the armed state is stickier than believed, and no host-side or cable-level
reset clears it.** Three resets were tested in one session, each followed by a bulk read
with **zero** control transfers:

| reset applied | EP 0x83 | EP 0x84 |
|---|---|---|
| none (device left armed) | 51.7 MB/s | 54.5 MB/s |
| USB port reset + close/reopen | 53.48 MB/s | 36.44 MB/s |
| `authorized=0` → `authorized=1` on the sysfs device (full logical unplug/replug) | 49.49 / 53.27 MB/s | 44.25 / 36.28 MB/s |
| physical USB cable removed 4.21 s and reinserted | 52.31 / 55.58 / 57.01 MB/s | 55.59 / 43.69 / 41.43 MB/s |

`[CAPTURED]` The cable removal is the important row: the device re-enumerated and was
streaming at full rate 10 ms after the handle reopened. **Why** it survived is not known —
it could be an internal battery, an always-on rail, stored charge, or the FX3 simply keeping
its firmware state across a link disconnect. Nothing in our measurements distinguishes these
and no battery has been observed. `[UNKNOWN]`

Consequences:

- `libusb_reset_device` resets the **link**, not the device's internal state. It is the right
  reset for making command sequences reproducible (7.1b) and the wrong tool for reaching
  quiescence. `[VERIFIED]`
- A reader in the armed state needs **no control traffic at all**. In the same session,
  strobe-on and strobe-off windows were indistinguishable (EP 0x83 54.74–56.60 MB/s with
  15,500 control transfers accepted, versus 53.32–55.18 MB/s with none). `[CAPTURED]`
- A trustworthy quiescent baseline is **not reachable** from the host. It needs the headset
  powered off, which has not been done. `[UNKNOWN]`

Concurrency shape: **one process, one thread per endpoint.** Two processes cannot both
claim interface 0; the second bulk reader fails with `LIBUSB_ERROR_BUSY`. `[VERIFIED]`

The ruled-out table below still stands, but its interpretation changes: every one of those
experiments read *after* arming, so "0 bytes" measured the client, not the device.
`[VERIFIED]`

| Hypothesis tested | Result |
|---|---|
| Vendor IN polling alone | 0 bytes |
| Vendor OUT alone (each of the 138 individually) | 0 bytes |
| A single OUT + IN pair | 0 bytes |
| The `wValue=0x0004` enable quad `0c00 / 0d00 / 0c01 / 0d01` alone | 0 bytes |
| One large bulk URB with a long timeout | 65,536 bytes, then nothing |
| Full interleaved OUT+IN sequence | 65,536 bytes |
| **Pending bulk URBs + control traffic in flight** | **100-155 full frames per 12 s** |

## 7.1b The reset protocol — SOLVED 2026-10-16

**A USB port reset (`libusb_reset_device`) followed by closing and reopening the handle is
the deterministic reset.** `[VERIFIED]`

| Trial protocol | frames/s over three 10 s trials | mean | spread |
|---|---|---|---|
| No reset between arms | 7.50, 0.00, 0.00 | 2.50 | 3.000 |
| Port reset before every arm | 7.80, 7.50, 7.20 | 7.50 | 0.080 |

The port-reset run started from the state the other run had left the device in — 0 fps —
and recovered 7.80 fps on its first trial. It recovers the device; it does not merely avoid
entering the bad state. `[VERIFIED]`

Closing and reopening the handle is **not** a reset. Every trial of both rows opened a
fresh handle and closed it at the end, and the no-reset row still produced 0.00 fps twice.
`[VERIFIED]`

Arm success is not evidence that streaming will work: `arm ok=279 fail=138` appears in all
six trials, and only three of them streamed. `[VERIFIED]`

What the stuck state is: `[UNKNOWN]`. The device accepts everything — the sustaining loop
completed 6,874 and 6,872 control transfers with **zero** failures — and emits no bulk data.

## 7.1c The minimal sustaining set — SOLVED 2026-10-16

**Four vendor OUT commands**, looped in this order. `[VERIFIED]` `data/minimal_outs.json`

| # | wValue | wIndex | payload | role |
|---|---|---|---|---|
| 1 | 0x0006 | 0x0006 | `00040000007e` | assert |
| 2 | 0x0009 | 0x0004 | `0000001b` | assert |
| 3 | 0x0006 | 0x0006 | `000400000000` | clear |
| 4 | 0x0009 | 0x0004 | `00000000` | clear |

Two assert/deassert pairs. Found by leave-one-out on the 9 commands that survived halving:

| dropped from the 9 | frames/s | verdict |
|---|---|---|
| `00040000007e` | 0.00 | required |
| `0000001b` | 0.00 | required |
| `6877696e666f2e62` (ASCII `hwinfob`) | 29.89 | droppable |
| the 64-byte `1300ff…` write | 29.35 | droppable |
| `3d40a8800000` | 29.84 | droppable |
| `3d21a880ffff` | 29.80 | droppable |
| `3d21a881ffff` | 29.99 | droppable |
| `000400000000` | 0.00 | required |
| `00000000` | 0.00 | required |

Halving does not work: the first 4 and the last 5 of those 9 each give 0.00 fps. The set
behaves as a sequence, not as a bag of independent triggers. `[VERIFIED]`

Order is partly load-bearing. As found: 29.90 fps, spread 0.020. Sorted by `wValue`: 29.85,
spread 0.003. Reversed: 29.89 then 0.20, spread 1.973 — unstable. `[VERIFIED]`

**Withdrawn:** the framing that the 27-command tail set was the thing to minimize. Those
numbers predate the port reset and are not comparable with anything measured after it.

**Still open:** `[UNKNOWN]`

1. What the two strobed registers gate. The sequence is reproducible; its meaning is not.
2. Whether the 417-transfer arm is needed at all. With the arm, the 4 commands sustain
   ~30 records/s. Without it, two trials gave 0.30 and 0.00 fps — but a device left armed
   by an earlier session streams with no commands at all, so "no arm" is not yet a clean
   baseline.
3. What `0xb007` gates. The suppression observation (7.4 vs 100.1 frames) predates the port
   reset and has not been re-measured behind it.
4. What state allows the device to free-run with zero control traffic. As of 2026-10-21 the
   answer looks like "the armed state, and it survives everything short of a power-off", but
   the armed state itself has never been entered from a proven-off device.

**Experiment that would settle the remainder:** reach a genuinely disarmed device. Port
reset, handle close/reopen, sysfs `authorized` toggling and physical USB cable removal have
all been tried and none produced silence (7.1). The next candidate is not a physical one: the
SDK's own teardown. `cyapi.dll` exports `CCyUSBDevice::PowerState()` and
`meta2_host_itf.dll` exports `System_RegisterPowerOff` on both `DriverManagerAdapter` and
`EventHandlerAdapter`, which means the vendor stack has a device power path that is visible
as USB traffic and can be captured rather than guessed at. Until a disarm is demonstrated,
the arm/no-arm comparison and the `0xb007` suppression test cannot be given a trustworthy
baseline.

## 7.2 What the registers mean

**Known:** 40+ registers read live with values; some change between reads within one
session. `[VERIFIED]`

**Not known:** units, scale, or which register does what.

**Experiment:** differential probing. Read the full observed address range at a fixed
width, then change one physical condition (cover the cameras, tilt the headset, warm it
up) and read again. Addresses whose values move are sensor-related; the direction and
scale of the movement gives you the units. This is mechanical and would likely resolve
the IMU registers quickly.

Registers that changed within one session, and are therefore the first candidates:
`0x0204`, `0xa882`, `0xa892`, `0xb007`, `0xb0ae`, `0xc400`, `0xc401`. `[VERIFIED]` that
they changed; `[INFERRED]` that they are status/telemetry.

## 7.3 Span base offsets

**Known:** a wide read does not return the byte window you asked for. For `0xc2bc` the
base is 4 bytes below the requested address. `[VERIFIED]`

**Not known:** the rule.

**Experiment:** write a recognisable pattern (e.g. `0xA5A5A5A5...`) across a 64-byte
address range, then read at many addresses and widths and map where the pattern appears.
That determines the base rule directly. Low cost, high value.

## 7.4 EP 0x82

**Known:** it exists, has the largest URBs requested of any endpoint (262,144 B), and
returned zero bytes in every capture and every attempt. `[VERIFIED]`

**Not known:** what it is for. Plausible: a second camera, or a stream the device only
arms for a configuration we have not produced. `[INFERRED]`

**Experiment:** once continuous streaming is solved, check whether EP 0x82 starts. If the
Meta 2's stereo tracking cameras stream, EP 0x82 is the leading candidate for one of them.

## 7.5 EP 0x84 geometry and units

**Known:** frames of 202,784 bytes (record 32 + payload 202,752); a 696-byte header that is
byte-identical across all 435 frames; 101,028 samples of image data; 16-bit containers
holding 12-bit values (2 samples in 101,376 exceed 4095); `0x0FFF` as an explicit no-data
sentinel, all 339 occurrences inside the header in this capture; body mean 2,066.7.
`[VERIFIED]` See 5.4.

**Not known:** the mapping from sample value to distance. The row-stride question itself is
resolved elsewhere: `docs/08-camera-inventory.md` names `352 × 288` from a register read-back
(`0xa886` → 351, 288 as 0-based maxima) and supersedes the autocorrelation guess.
`[VERIFIED]` read-back.

The autocorrelation route is now **actively unsupported**, not merely weak. Over 20 M samples
in two independent 12 s captures, mean |difference| at lag 704 against a random-pair baseline
gives contrast of −1.1 % and +3.5 %. The earlier 18 % figure (29.0 at lag 704 against a 35.4
baseline) came from a 1 M-sample capture and does not reproduce. The 352 / 704 / 1408 / 2112
"harmonic family" argument therefore has no statistical support behind it. `[VERIFIED]`
See 12.11.

**Withdrawn:** the earlier "`1312` present as an explicit header field" observation — it came
from a URB-sized slice, not from a frame boundary. `[VERIFIED]`

**Experiments, in order:**

1. **Geometry without the operator.** Capture EP 0x84 while the headset faces a high-contrast
   edge (a doorway, a wall meeting open floor) at a known angle. A real 2D grid makes the
   edge appear as a straight line at some row offset; scanning candidate strides for the one
   that renders that line straight is decisive where flat-scene autocorrelation is not.
2. **Units.** Headset at measured distances (0.5 m, 1.0 m, 1.5 m, 2.0 m) from a flat wall,
   one capture per distance, regress body values against distance. One run gives the units or
   proves the field is not range at all.

## 7.6 EP 0x81 record semantics

**Known:** full 256-byte framing, 45-slot table, all slots absent in 29,462 consecutive
records. `[VERIFIED]`

**Not known:** what the record is, and what the slots hold. Never observed populated.

**Experiment:** capture while the headset is actively tracking a textured scene in motion
— the condition under which the vendor software reports tracking as healthy. Slots that
were `0xFFFFFF` should populate. Then correlate slot values with the pose the vendor SDK
reports at the same time.

## 7.7 Raw IMU, audio, buttons, temperature

**Known:** the vendor SDK has types for all four (`RawImuData`, `AudioData`,
`ButtonData`, `TemperatureData`). `[CAPTURED]`

**Not known:** which bytes on which endpoint carry them.

**Experiment:** press a button and cover a microphone while capturing all four endpoints;
diff the streams against a baseline. Cheap and decisive.

## 7.8 Public hardware specifications

**Not established.** A web search for the Meta 2's published hardware specifications
returned no results from the configured search backend during the writing of these docs,
so no external spec has been cited anywhere in this repo. Everything in these documents
is derived from the device itself or from the SDK installer.

If you have the original product documentation, the sections worth reconciling are:
camera resolutions and frame rates, display resolution, and the sensor list. Those are
the claims here that would benefit most from an independent source.

## 7.9 Where does the SDK's colour come from? `[UNKNOWN]` — added 2026-10-16

**Known:** the vendor reader writes 3-channel colour frames at 1280×720 with real chroma
(mean |R−B| 17.4 and 9.6 on two frames). EP 0x83, armed either by the 4-command strobe or by
the full 417-transfer vendor sequence, delivers single-channel data whose image lives in bits
15–11 (1.6a). EP 0x84 is a 12-bit field with an invalid sentinel. EP 0x82 has returned **zero
bytes** in every capture we made — and it is the endpoint the vendor software requests the
largest URB on, 262,144 B.

**Not known:** which endpoint carries the colour camera, or whether colour is a register-selected
pixel format on the same camera that currently gives mono. The SDK's type system makes the
format configurable in three separate dimensions — `RgbCameraPixelType`,
`MonoCameraPixelType`, `RgbCameraRate`, `MonoCameraRate` — so a format register plausibly
exists.

**Experiment, in order of cost:**

1. **Capture EP 0x82 while the vendor reader runs.** It is the only endpoint we have never
   gotten data from and the one the SDK requests most bytes on. Run the reader in the VM,
   capture on the host with the reader's own URB sizes, and check whether 0x82 yields a
   3-channel 1280×720 stream. Apply the 1.6a bit-group coherence test to whatever arrives.
2. **Sweep the pixel-format registers.** Read candidate registers before and after the SDK
   configures a camera, diff, and write the difference. The `0x0006/0x0006` and
   `0x0009/0x0004` strobe pair is the cheapest known lever over streaming behaviour and
   should be probed first.
3. **Correlate with `status.csv`.** The vendor reader's `status.csv` records what it thinks it
   configured; aligning those values with register writes gives a semantic anchor.

**Why it matters:** the whole point of this project is colour passthrough to the headset
display. A monochrome 25 fps stream is a good SLAM input and a poor passthrough. Until the
colour stream is located, the display use case is not actually served.
