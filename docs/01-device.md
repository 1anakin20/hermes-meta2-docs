# 1. The device

## 1.1 What it is

The Meta 2 is a standalone AR (see-through) headset. It renders a stereoscopic image to
the wearer and tracks its own position in space using onboard cameras and inertial
sensors. It connects to a host over USB 3.0 and is powered from the host.

Vendor: Meta (Metavision Inc.). **Not Facebook/Meta Platforms, not Oculus.**
`[VERIFIED]` from the USB string descriptors: manufacturer `USB Design By Meta`,
product `Meta2`.

## 1.2 Internal architecture as observed

The host does **not** talk to the headset's application processor directly. It talks to
a **Cypress FX3 USB 3.0 bridge**, and the bridge talks to the rest of the headset.

Evidence:

- The vendor's own host library `cyapi.dll` is Cypress's FX3 host API. Its class
  hierarchy is `CCyFX3Device -> CCyUSBDevice -> CCyUSBInterface -> CCyBulkEndPoint /
  CCyControlEndPoint`, and `CCyUSBDevice` is constructed from a WinUSB device GUID.
  `[CAPTURED]` — static inspection of `cyapi.dll` from the SDK installer.
- The USB surface is the classic FX3 surface: one vendor-class interface, four bulk IN
  endpoints at 1024-byte max packet with `bMaxBurst 15`, and a vendor control port on
  EP0 used as a generic read/write window into a 16-bit-addressed register space.
  `[VERIFIED]` — descriptors read live plus live control transfers.
- The vendor's higher-level library `meta2_host_impl.dll` contains the string
  `Device not connected in SuperSpeed mode.`, which matches the device descriptor's
  own speed requirement (section 1.4). `[CAPTURED]`

**Consequence for anyone writing a driver:** the transport is standard WinUSB on
Windows and standard libusb on Linux. There is no proprietary kernel driver to
reimplement. The only closed part is what to say to the bridge. `[VERIFIED]`

What sits behind the FX3 register window (a headset SoC, an FPGA, the FX3's own RAM) is
`[UNKNOWN]`.

## 1.3 Identity

| Field | Value | Confidence |
|---|---|---|
| `idVendor` | `0x2CFA` — "USB Design By Meta" | `[VERIFIED]` |
| `idProduct` | `0x00F3` — "Meta2" | `[VERIFIED]` |
| `bcdDevice` | `0.00` | `[VERIFIED]` |
| `iSerial` | **0 — the device exposes no USB serial number** | `[VERIFIED]` |
| Unit identity string | `<unit-serial>` (redacted, see note below) | `[VERIFIED]` (see below) |

Because `iSerial` is 0, you cannot distinguish two headsets by USB descriptors. The
identity lives behind the vendor control port.

**Reading the identity string** `[VERIFIED]`:

```
OUT  bmRequestType=0x40 bRequest=0xC0 wValue=0x0002 wIndex=64 wLength=64
     payload = 13 00 FF 00 00 ... 00            (64 bytes)
IN   bmRequestType=0xC0 bRequest=0xC0 wValue=0x0002 wIndex=1 wLength=56
     response = 00 00 00 00 00 00
                "<unit-serial>"             (17 ASCII bytes)
                FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
```

> **Redaction note.** The literal identity string of the specific headset used for
> this work has been replaced with `<unit-serial>` throughout these documents and in
> the committed data files. The *mechanism* is fully documented and reproducible; only
> this unit's identifier is withheld. The format observed is a 17-character ASCII string
> beginning `META2D` followed by digits.

The response is padded with `FF` past the end of the string. Its length is **not
fixed**: a passive capture saw 41 bytes returned for a 56-byte request (the short packet
terminating the transfer), while a live read of the same command returned the full 56
bytes. `[VERIFIED]` both observations. Parse the printable run, do not assume a length.

The vendor's SDK exposes this as `meta_get_serial_number()`, and its internal
`device_stream_block.cpp` logs `Reading Serial Number...`. That the SDK's value is the
same string is `[INFERRED]` — strongly consistent, but our test reader queried it
before the device had it ready and logged an empty value, so byte-for-byte equality is
`[UNVERIFIED]`.

## 1.4 The device only works at SuperSpeed

From the BOS / SuperSpeed USB Device Capability descriptor:

```
wSpeedsSupported        0x000e   Full Speed, High Speed, SuperSpeed
bFunctionalitySupport   3        lowest fully-functional speed = SuperSpeed
```

`[VERIFIED]` — read live from the device.

Practical meaning: the device will enumerate at a lower speed but is not functional
there. **Plug it into a USB 3.0 port.** A USB 2-only host is not a supported
configuration. The vendor's own software carries the matching error string (section
1.2). `[VERIFIED]` for the descriptor fact; `[INFERRED]` for the strength of the
practical claim, which follows from `bFunctionalitySupport`.

## 1.5 Power

The configuration descriptor declares `bmAttributes 0x80` (bus powered) and
`MaxPower 64 mA`. `[VERIFIED]` as a descriptor value.

That number is not credible as the headset's actual draw — a headset with two tracking
cameras, a display and an SoC draws far more than 64 mA. Either the descriptor is
stale, or the bulk of the power does not come from the USB port. `[UNKNOWN]` which.
Do not use this value to size a hub or cable.

## 1.6 Sensor inventory

Two independent sources: the vendor SDK's own type system, and what actually appears on
the wire.

### From the SDK's type system `[CAPTURED]`

Extracted from `meta2_host_impl.dll` (C++ symbols in namespace `sdc`):

| Type | Implies |
|---|---|
| `CameraConfig<RgbCameraResolution, RgbCameraPixelType, RgbCameraRate>` | An RGB camera with selectable resolution, pixel format and frame rate. |
| `CameraConfig<MonoCameraResolution, MonoCameraPixelType, MonoCameraRate>` | Mono camera(s) with the same three configurable dimensions. |
| `RawImuConfig`, `RawImuData` | Unfused accelerometer/gyroscope stream. |
| `FusedImuConfig`, `FusedImuData` | Filtered 6-DoF orientation stream. |
| `AudioData` | Microphone. |
| `ButtonData` | On-device buttons. |
| `TemperatureData` | Temperature sensor. |
| `ImageData` | Generic image callback. |

The presence of `MonoCameraResolution` (plural type family, separate from RGB) is
consistent with the Meta 2's stereo tracking cameras, but the SDK type alone does not
prove how many mono cameras exist. `[INFERRED]`

### From the wire `[VERIFIED]`

| Endpoint | What was observed | Interpretation |
|---|---|---|
| `0x81` | 256-byte records, 45-slot table, µs-scale timestamps | tracking / feature stream. Semantics `[UNKNOWN]` |
| `0x83` | 1280×720 16-bit image samples, **single-channel** (1.6a) | a monochrome camera. `[VERIFIED]` that it is 1280×720 16-bit single-channel image data; `[UNKNOWN]` which physical camera |
| `0x84` | 12-bit field, `0x0FFF` = invalid sentinel | depth / range data. `[INFERRED]` |
| `0x82` | no data in any capture | `[UNKNOWN]` |

## 1.6a EP 0x83 is monochrome, and only its top 5 bits carry the image `[VERIFIED]` 2026-10-16

An earlier version of this document claimed a brightness cross-check `[VERIFIED]` tied
EP 0x83 to the SDK's RGB camera: mean of the 16-bit samples 20804 → `20804 / 65535 * 255 =
81.0`, and the SDK's RGB frames from the same session had mean brightness ~80/255. **That
claim is withdrawn** (EVIDENCE.md §6). Matching mean brightness does not identify a sensor,
and a direct structural test separates the two streams.

**Test.** Split each 16-bit sample into its three bit-groups — `hi5 = v >> 11`,
`mid6 = (v >> 5) & 0x3F`, `lo5 = v & 0x1F` — and measure spatial coherence: mean absolute
difference between horizontal neighbours divided by the same statistic on a shuffled version
of the same pixels. A coherent image gives a low ratio; a field of independent noise gives
≈ 1.0. Run on a complete frame from a 93.9 MB capture (`counter 126`) and independently on
`burst83.bin`, the EP 0x83 burst from the full 417-transfer vendor sequence:

| bit-group | coherence, strobe capture | coherence, full vendor sequence |
|---|---|---|
| `hi5` (bits 15–11) | **0.070** | **0.101** |
| `mid6` (bits 10–5) | 0.948 | 0.988 |
| `lo5` (bits 4–0) | 1.296 | 1.241 |

`mid6` std is 18.37 and 18.41; a uniform random 6-bit field has std 18.47. Cross-group
correlations are −0.114, −0.047, −0.004.

The test is published as `tools/bitgroup.py` in the `meta2lib` repo. Run against the whole
93.9 MB capture rather than one frame it gives 0.066 / 0.931 / 1.264 and against
`burst83.bin` 0.101 / 0.988 / 1.238 — the same conclusion from a different window.

**This refutes the RGB565 hypothesis.** A 1280×720 RGB565 frame is exactly 1,843,200 bytes —
the same size as an EP 0x83 frame body — so the frame size alone cannot distinguish mono
from RGB565. But under RGB565 the three bit-groups would be the R, G and B planes and **all
three would be coherent images**. Only the top group is. The lower 11 bits are statistically
indistinguishable from noise.

**Consequence.** The SDK's colour frames are genuinely 3-channel: `last_frame.png` from the
vendor reader measures mean R 71.5 / G 84.4 / B 87.4 with mean |R−B| 17.4, and
`f_frame_000200.png` measures mean |R−B| 9.6 — real chroma, not a replicated grey channel.
EP 0x83 as armed by the 4-command strobe *and* by the full vendor sequence is single-channel.
**The colour the SDK produces does not come from the EP 0x83 stream we can capture.** Where it
comes from is `[UNKNOWN]`; see 7.9.

**Practical consequence for a reader.** Rendering by taking the high byte (`v >> 8`) is
correct and loses nothing: the image information lives in bits 15–11, and the 3 bits of noise
below them dither away what would otherwise be 32-level banding. Do not interpret the low
bits as data, and do not treat the 16-bit range as 16-bit dynamic range — the effective
depth measured here is ~5 bits (`hi5` std 4.71–6.10 on a 0–31 scale).

Raw IMU is reachable on the wire in principle (`RawImuData` exists in the SDK) but the
vendor's public C API exposes only fused pose. Which stream carries raw IMU is
`[UNKNOWN]`.

## 1.7 What the device does *not* appear to have

No evidence was found for: onboard storage accessible over USB, an audio output path,
or a display data path over USB. The display is driven by the headset's own SoC, not by
the host. `[INFERRED]` from the absence of any such endpoint or command class in the
captured traffic; absence of evidence, not proof.
