# 9. The vendor driver, decompiled — the endpoint map is no longer a guess

`meta_driver_decompiled.zip` is the Meta (Metavision) driver decompiled from C#. It names
every endpoint, every image geometry, and every command the device accepts. This section
records what it says, and — separately — what we then **re-verified against our own raw
captures**, because a decompiled binary is a strong source but not an experiment.

Source: `Meta.Driver.*` namespaces, 100 `.cs` files.

---

## 9.1 The endpoint map

`Meta.Driver.DataTypes/EndPointType.cs`:

```cs
public enum EndPointType : byte
{
    None                 = 0,
    MultiplexorEndPoint  = 129,   // 0x81
    MonoCamerasEndPoint  = 130,   // 0x82
    RGBCameraEndPoint    = 131,   // 0x83
    ToFCameraEndPoint    = 132    // 0x84
}
```

That is the whole bulk-IN endpoint set, and it matches the USB configuration descriptor
exactly (02 §4: four bulk IN endpoints, `wTotalLength = 70`, no fifth endpoint). `[VERIFIED]`

**This confirms the operator's working model outright**: two monochrome cameras, one RGB
camera, one Time-of-Flight camera. It also **reverses** two conclusions recorded in 08 —
see 9.6.

---

## 9.2 What each endpoint carries

From `Meta.Driver.EndPointDataConstructors/*`:

| Endpoint | Class | Image type | Geometry | Bytes/frame |
|---|---|---|---|---|
| `0x83` | `RGBEndPointDataConstructor` | `YUV422Image` | **1280 × 720**, 2 B/px | 1,843,200 |
| `0x82` | `Mono0EndPointDataConstructor`, `Mono1EndPointDataConstructor` | `GrayScale16Image` ×2 | **752 × 480** each, 2 B/px | 721,920 each |
| `0x84` | `TimeOfFlightEndPointDataConstructor` | `TimeOfFlight16Image` | **352 × 288**, 2 B/px | 202,752 |
| `0x81` | `IMU0`/`IMU1`/`Microphone`/`Button` constructors | 16 B IMU, audio, button state | — | — |

Every frame size matches a frame boundary we had already measured independently:

* EP 0x83 record spacing 1,843,232 = 1,843,200 + 32 `[VERIFIED, 05 §5.3]`
* EP 0x84 record spacing 202,784 = 202,752 + 32 `[VERIFIED, 05 §5.4]`
* EP 0x82 trailer-to-trailer delta **721,952 = 721,920 + 32** appears in
  `re/probe_arm_strobe_ep82.bin` `[VERIFIED, re/mono_assemble.py]`

`[VERIFIED]` The geometries are the driver's claim *and* our capture's frame boundaries.

---

## 9.3 Record framing — the driver's own scanner

`Meta.Driver.EndPointDataProcessors/DataScanner.cs` gives the exact framing rules, and they
explain the layouts we had reverse-engineered by hand:

**Mono header (32 B), EP 0x82.** `FindMonochromeHeaderIndex` searches 4-aligned for
`00 00 DC AC 78 56 34 12 BA AB ED FE` at position `i` and returns `i − 8`:

```
h+0   u32   (556 in our capture)
h+4   u32   timestamp-like (0xD0B254DF)
h+8   00 00
h+10  DC AC 78 56 34 12
h+16  BA AB ED FE
h+20  tag, repeated u16: 0x0044 = mono0, 0x0055 = mono1
h+24  00 00 00 00
h+28  (two u16 header fields: 0x0384, 0x8020)
h+32  image samples begin
```

`MonochromeEndPointDataProcessor` copies `data[h+32 : next_header]` into a per-camera
buffer, so the two cameras are **interleaved one 4,096-byte URB at a time**. `[VERIFIED]`
Our capture has 2,048 headers at exact 4,096-byte spacing with tag histogram
`{0x44: 1024, 0x55: 1023}`.

**Multiplexor header (28 B), EP 0x81.** `FindMultiplexorHeaderIndex` searches for
`00 00 00 00 AB BA ED FE` at `i` and returns `i` itself (no offset). Tag at `h+8`:

| tag | driver predicate | meaning |
|---|---|---|
| `0x66` (102) | `IsIMU1Header` | IMU1 |
| `0x77` (119) | `IsIMU0Header` | IMU0 |
| `0x88` (136) | `IsMicsHeader` | microphones |
| `0x99` (153) | `IsButtonsHeader` | buttons |

Note the inversion: the driver's `IsIMU0Header` tests **119**, `IsIMU1Header` tests **102**.
`[VERIFIED from source]` which tag maps to which physical IMU is `[UNKNOWN]`.

**Trailer (32 B), all endpoints.** `FindTrailerIndex` searches for
`EF BE AD DE 0D F0 DD DA 00 00 00 00` at `i` and returns `i − 16`. `Trailer` then reads
eight u32 fields from that position:

```
+0  TimeStampHi        +4  TimeStampLow
+8  SentinelHi         +12 SentinelLow
+16 FixedSentinelHi    +20 FixedSentinelLow
+24 PacketInformationHi +28 PacketInformationLow
IsHeader  = (PacketInformationLow & 0x01000000) != 0
PacketNum = PacketInformationLow & 0xFFFFFF
```

`RGBEndPointDataProcessor` finalises a frame **when it reaches a trailer**, i.e. the trailer
*follows* the image data. Combined with the `i − 16` return, this resolves the off-by-eight
that confused 05 §5.3: the `BA AB ED FE` block we called the record marker is the trailer's
`SentinelHi`/`SentinelLow` at trailer+8/+12, and image data starts at `marker + 24`, not
`marker + 32`. `[VERIFIED]` Frame length then comes out at exactly 1,843,200.

`0xDEADBEEF` and `0xDADDF00D` at trailer+16/+20 are fixed sentinels — the same
`0xDADDF00D` we found in EP 0x81 records (05 §5.2) is the trailer's `FixedSentinelLow`, not
a per-slot "absent" marker.

---

## 9.4 EP 0x83 is colour: YUV422, not monochrome

`re/yuv422_test.py` on `re/stream_ep83.bin` (48 complete 1,843,200-byte frames), grouping
the payload into 4-byte phases:

```
phase 0: mean 128.05  std  4.51      <- chroma (pinned near 128)
phase 1: mean  94.27  std 48.62      <- luma
phase 2: mean 126.71  std  4.57      <- chroma
phase 3: mean  94.24  std 48.63      <- luma

corr(phase1, phase3) = 0.992   the two luma slots
corr(phase0, phase2) = -0.629  the two chroma slots
```

Luma and chroma separate cleanly. The packing is **`U Y V Y` or `V Y U Y`** — chroma in
slots 0 and 2, luma in slots 1 and 3. `[VERIFIED]` which chroma slot is U and which is V is
`[UNKNOWN]`; both orderings give the same statistics.

Decoded to RGB (BT.601): mean chroma spread 10.8, **11% of pixels with channel spread
> 20, maximum spread 189**. Real colour is present on the wire. `[VERIFIED]`

**Why we got this wrong before.** The bit-group test in 05 §5.3 read the payload as 16-bit
samples. In `UYVY`, every little-endian u16 is `chroma | luma<<8` — the image lives in the
high byte and chroma sits in the low byte. That is exactly what the old test reported
("8-bit image data in the high byte of each u16", "low 11 bits are noise"), and the old
test then concluded *monochrome*. The low byte was not noise. It was chroma. `[VERIFIED]`

---

## 9.5 EP 0x82 assembles into two real images

`re/mono_assemble.py` splits EP 0x82 by tag, drops the 32-byte trailers, and reshapes to
the driver's 752 × 480:

```
mono0 (0x44): 4,161,248 B image data = 2,080,624 samples = 5.76 frames
  samples: mean 291.4  min 42  max 1023  (all <= 1023 -> 10-bit sensor in a 16-bit container)
  mean |horizontal diff|    9.69   random baseline 341.09   -> 35x coherent
  mean |vertical   diff|   12.50   random baseline 341.03   -> 27x coherent

mono1 (0x55): 4,157,216 B = 2,078,608 samples = 5.76 frames
  samples: mean 98.9  min 42  max 1023
  horizontal 6.69 (51x)   vertical 6.59 (52x)
```

`[VERIFIED]` EP 0x82 carries two 752 × 480 10-bit monochrome images.

Two earlier readings of 08 §8.1/§8.2 are artefacts of this: the "2,032-sample record" and
the "~223-sample displacement between consecutive frames" came from treating one 4,096-byte
URB as a whole frame. It is a fragment. `[WITHDRAWN]`

---

## 9.6 EP 0x84 is coherent after all

Re-running the coherence test with the driver's geometry and **signed** arithmetic
(`np.diff` on `uint16` wraps, which is what produced 08's "no spatial coherence"):

```
435 frames of 352 x 288 in re/stream_ep84.bin
mean 2034.2  max 4095  sentinel 0x0FFF fraction 0.0033
mean |horizontal diff| 38.32   random baseline 1365.86   -> 36x coherent
mean |vertical   diff| 36.01   random baseline 1368.47   -> 38x coherent
value histogram peaks tightly around 2017-2033
```

`[VERIFIED]` EP 0x84 is a coherent 352 × 288 12-bit image. `[INFERRED]` it is a depth map:
the values sit near mid-scale (2025) with almost no scene-dependent variation, which is
what a ToF returns when it has no usable return, and it is unchanged by occlusion (08 §8.8).

---

## 9.7 EP 0x81 is the IMU stream, and it reads

`IMUData.cs` — 16-byte payload at multiplexor header + 28, all `i16` little-endian:

```
+0  GyroscopeValid   +2  GyroscopeX  +4  GyroscopeY  +6  GyroscopeZ
+8  AccelerometerValid +10 AccelX   +12 AccelY      +14 AccelZ
```

Applied to `re/probe_arm_strobe_ep81.bin`: 2,876 headers at exact 256-byte spacing, tags
`{IMU0: 1451, IMU1: 1424}`, no `0x88`/`0x99` records.

```
IMU0  gyro (  7.8,   1.8,  -13.7)   accel ( -623, -15922,  3663)  |a| = 16,360
IMU1  gyro (  3.6,  -0.8,   -0.8)   accel (-2404,  16055,  5090)  |a| = 17,043
valid flags always 1; gyro std ~1.6; accel std 35-65
```

`[VERIFIED]` Both accelerometers read ~16,000–17,000 counts along one axis with the headset
at rest — gravity at a ~16,384 LSB/g scale. The gyro is near zero with a small offset. This
is the first time any IMU data has been read outside the vendor stack.

`[UNKNOWN]` the exact LSB scale, axis orientation, sample rate, and the 212 bytes of each
256-byte record that are not the 16-byte IMU payload.

---

## 9.8 The enable protocol — one 6-byte command selects the cameras

`Meta.Driver.EndPointStateControllers/` builds the two commands we had found empirically as
our 4-command strobe, and names their payload bytes.

`EndPointStateControlGroup.UpdateCurrentState()` ORs the per-endpoint enable states and
sends three requests, all with `RequestCode = 192` (`0xC0`):

| request | value | data | meaning |
|---|---|---|---|
| multiplexor feed | 9 | `[0, 0, 0, mux_mask]` | which muxed sensors stream |
| aggregation | 6 | `[0, 4, 0, 0, 0, 64 or 0]` | aggregator on/off |
| endpoint feed | 6 | `[0, 4, 0, 0, 0, enable_mask]` | which endpoints stream |

`enable_mask` bits (from the state controllers):

| bit | value | endpoint |
|---|---|---|
| 1 | 2 | MonoCamera0 |
| 2 | 4 | MonoCamera1 |
| 3 | 8 | TimeOfFlightCamera |
| 4 | 16 | Multiplexor |
| 5 | 32 | RGBCamera |
| 6 | 64 | STD — OR'd in whenever the mask is non-zero |

`mux_mask` bits: IMU0 = 1, IMU1 = 2, Microphones = 4, Buttons = 8.

**Our strobe is this command pair.** `00 04 00 00 00 7E` is the endpoint feed with
`0x7E = 2|4|8|16|32|64` — every camera plus the multiplexor plus STD. `00 00 00 1B` is the
multiplexor feed with `0x1B = 1|2|8|16` — IMU0, IMU1, Buttons, and bit 4. **Microphones
(bit 2, value 4) are not in it**, which is why no `0x88` record has ever appeared in our
EP 0x81 captures. `[VERIFIED]` from our capture; `[driver source]` for the bit meanings.

`[INFERRED]` `mux_mask` bit 4 (16) is a fifth multiplexed source the driver's
`MultiplexorEndPointStateController` never sets; nothing in the decompiled source names it.

This is the practical lever the project has been missing: individual cameras can be turned
on and off, and microphones can be turned on, without the SDK.

---

## 9.9 Other request codes the driver uses

`Meta2CommandConstants.cs` / `Meta2DeviceInformation.cs` / `Meta2DeviceFiles.cs`:

| code | value | data | response | purpose |
|---|---|---|---|---|
| `0xC0` | 7 | — | 3 B, `[0, major, minor]` | ARM firmware version |
| `0xC0` | 5 | `[0, 116]` | 5 B, `[0, u32 unix seconds]` | FPGA firmware build date |
| `0xC1` | 253 | — | 3 B | USB (FX3) firmware version |
| `0xB9` | 4 | `[4, 2]` | 5 B, `[0, ?, major, minor]` | GEO firmware version |
| `0xC2` | 4 | filename + NUL | `[0, u32 LE address]` | resolve a device file's address |
| `0xC0` | 2 | `[19, addr>>24 … addr]` | `bufferSize+1` B, data from offset 6, terminated by `0xFF` | read a device file |
| `0xC0` | 6 / 9 | as above | 38 B | enable feeds |

Device files named in the source: **`hwinfo.bin`** (32 B, the serial number as UTF-8) and
**`calibration.bin`** (128 B, calibration data as UTF-8). `[driver source]`
`[NOT YET REPRODUCED]` — we have not yet issued a `0xC2`/`0xC0-2` exchange.

`Meta2DriverConstants`: `SINGLE_TRANSFER_LENGTH = 38`, `TRAILER_LENGTH = 32`,
`HEADER_LENGTH = 28`, `VENDOR_ID = 11514` (`0x2CFA`), `PRODUCT_ID = 243` (`0x00F3`).
`[VERIFIED]` against the descriptors.

`DeviceController` shapes the control transfers as: OUT `bmRequestType 0x40`,
`wValue = request value`, `wIndex = data length`; IN `bmRequestType 0xC0`, `wIndex = 1`,
38-byte buffer. `[VERIFIED]` this matches 03 §3.1 exactly.

**One discrepancy worth checking.** The driver issues **one IN per OUT**. Our replay of
`ctrl_seq_full.json` issues two, and `re/arm_failures.py` showed all 138 failures are the
*second* IN. That is consistent with the second IN being ours rather than the vendor's, and
it suggests the arm sequence can be halved. `[INFERRED]`, not yet tested.

---

## 9.10 What this changes in the record

| Earlier claim | Status |
|---|---|
| "EP 0x83 is monochrome" | **Withdrawn.** It is the RGB camera, YUV422. See 9.4. |
| "No endpoint carries colour" | **Withdrawn.** 0x83 carries chroma on the wire. See 9.4. |
| "EP 0x84 has no spatial coherence" | **Withdrawn.** Unsigned `np.diff` artefact. See 9.6. |
| "EP 0x82's A/B pair is 2,032 samples per acquisition" | **Corrected.** 4,096-byte URB fragments of 752 × 480 frames. See 9.5. |
| "EP 0x81 is a 45-slot status table, all slots absent" | **Withdrawn.** It is the multiplexor: IMU0/IMU1/mics/buttons. See 9.7. |
| "The 2 mono + 1 RGB + 1 ToF model" | **Confirmed** by `EndPointType` and by geometry. |
| Occlusion results (08 §8.8) | **Unchanged, and now explained**: 0x82 = the two side mono cameras (reacts to left and right cover, not centre); 0x83 = the centre RGB camera (reacts to centre cover). |

## 9.11 What the driver does *not* answer

* No resolution/rate enum exists in this decompile — the frame sizes are hardcoded in the
  constructors, and nothing states fps. Our measured ~25 complete frames/s on 0x83 stands.
* No display path appears in these files. Reading the headset is understood; **writing to it
  is still unsolved**.
* No register-map code appears here. The `3D | op | addr | data` register protocol documented
  in 03/04 is *not* what these classes send — these classes send whole-command requests with
  short payloads. The two layers are separate and their relationship is `[UNKNOWN]`.
* The 212 non-IMU bytes in each 256-byte multiplexor record are not described.
* `mux_mask` bit 4 (16) is unnamed.
