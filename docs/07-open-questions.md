# 7. Open questions

Each item states what is known, what is not, and the specific experiment that would
close it. Nothing here is hand-waved.

## 7.1 The streaming trigger — SOLVED 2026-10-16

**Solved:** continuous full-frame streaming works with no SDK. The requirement is that bulk
URBs are already **pending** on the endpoints while control traffic is in flight. A
handshake-then-read client gets one 65,536-byte URB per endpoint; a client that keeps a
looping reader on each endpoint running gets 100 to 155 full 1280x720 frames per 12 s.
`[VERIFIED]`

Data flows **only while control transfers are running**. With zero control traffic the
endpoints go silent within seconds — the device is not free-running once armed.
`[VERIFIED]`

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

**What is still open:** `[UNKNOWN]`

1. **The sustaining command set is not a single command.** The 27 unique OUTs from the last
   100 transfers of the captured sequence sustain 18.4 MB/s with no vendor INs at all, once
   the `0xb007` writes are removed (`data/sustaining_outs.json`). Replaying all 138 OUTs in
   their original order sustains nothing. `[CAPTURED]`
2. **`0xb007` writes suppress streaming.** Same set with them: 7.4 frames in 10 s. Without
   them: 100.1 frames. `[CAPTURED]` What `0xb007` gates is not known.
3. **Results are state-dependent.** The identical 27-command set produced 18.4 MB/s in one
   run and 1.0 MB/s in another, depending on what had armed the device beforehand. No
   minimal command set can be claimed until trials run behind a deterministic arm-then-test
   reset. `[VERIFIED]` that the variance exists; `[UNKNOWN]` what governs it.

**Experiment that would settle the remainder:** arm with the full 417-transfer sequence,
let the stream stop, then test one candidate subset at a time with the same arm before
every trial, recording frames/s per subset, and bisect from there. The previously proposed
active WinUSB shim logging `cyapi.dll` transfers during steady state is now lower value:
the mechanism is understood and what remains is a search over commands.

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

**Not known:** the row stride and image dimensions, and the mapping to distance.
Autocorrelation gives only an 18% contrast (29.0 at lag 704 against a 35.4 random baseline),
where the same test on EP 0x83 gives 95%. 704 is the leading candidate because 352 / 704 /
1408 / 2112 form a harmonic family and 704 × 144 equals the payload sample count exactly.
`[INFERRED]`

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
