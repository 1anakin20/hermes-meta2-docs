# 7. Open questions

Each item states what is known, what is not, and the specific experiment that would
close it. Nothing here is hand-waved.

## 7.1 The streaming trigger — the blocking problem

**Known:** replaying the vendor start-up sequence (138 OUT + 279 IN, in order) causes the
device to produce exactly one burst per cycle: 1 KB on EP 0x81, 64 KB on EP 0x83, 64 KB on
EP 0x84. Re-triggering yields 197 KB/s sustained. `[VERIFIED]`

**Not known:** which command switches the device to continuous full-frame streaming. The
vendor SDK produced 141 full 1280×720 frames in 45 s from the same device, so the
capability exists. `[CAPTURED]`

**What has been ruled out, by experiment:** `[VERIFIED]`

| Hypothesis tested | Result |
|---|---|
| Vendor IN polling alone | 0 bytes |
| Vendor OUT alone (each of the 138 individually) | 0 bytes |
| A single OUT + IN pair | 0 bytes |
| The `wValue=0x0004` enable quad `0c00 / 0d00 / 0c01 / 0d01` alone | 0 bytes |
| One large bulk URB with a long timeout | 65,536 bytes, then nothing |
| **Full interleaved OUT+IN sequence** | **65,536 bytes** |

**Remaining hypotheses, in the order worth testing:**

1. A register write whose value encodes frame geometry (width, height, row stride). The
   candidates are the wide writes: `0xc2bc` (40 B), `0xb00e` (21 B), `0xa893` (18 B),
   `0xbff8` (16 B), `0xb062` (16 B). `[INFERRED]`
2. A command present in the vendor sequence that the passive capture lost. 7 of 138 OUTs
   had no recoverable payload, and two (`wValue=0x0007`, `0x00FD`) look zero-length, which
   is suspicious. `[UNCERTAIN]`
3. Continuous streaming requires the control handshake to run *concurrently* with bulk
   reads rather than before them. The vendor software keeps polling throughout a stream;
   our client replays once, then reads. `[INFERRED]`

**Experiment that would settle it:** capture the vendor software's control traffic
*while it is already streaming steadily*, not only during start-up. Our capture covers
start-up plus steady state, but the control payloads during steady state were only
partially recoverable from a passive capture. An active man-in-the-middle on the VM side
— a WinUSB shim that logs every transfer the vendor DLL makes, including payloads — would
give the complete picture in one run. That is the highest-value next step.

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

**Known:** 12-bit field, `0x0FFF` = no data, body values tightly clustered around
2017–2033 in one capture, a few values above 4095, `1312` present as an explicit header
field. `[VERIFIED]`

**Not known:** resolution, row stride (autocorrelation found none), and the mapping to
distance.

**Experiment:** place the headset at a measured distance from a flat wall, capture EP
0x84, and regress body values against known distance. One run gives you the units or
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
