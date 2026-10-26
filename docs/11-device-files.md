# 11. Device-side files: the protocol works, and the calibration naming is resolved

All measurements in this file are from 2026-10-16 on the host-side `2cfa:00f3`
device, using `meta2lib/tools/e1_files.py` and `meta2lib/tools/e1_naming_test.py`.

**Safety note.** Everything here is read-only. Only two command shapes were sent:
`0xC2`/4 (file address lookup) and `0xC0`/2 with `data[0] == 19` (read opcode). No
write opcode (`0x40`/`0x20`/`0x60`/`0xA0`/`0xC0`/`0xE0`), no FX3 SPI-flash path, and
the golden-image probe that shares request value `2` was never sent. Addresses used
were only the ones the device itself returned for the two named files.

## 11.1 The file protocol, verified end to end

Transcribed from `Meta2DeviceFiles.cs` and confirmed against the live device:

```
GetFileAddress(name)
  OUT  bmRequestType=0x40  bRequest=0xC2  wValue=4  wIndex=len(name+1)  data="<name>\0"
  IN   bmRequestType=0xC0  bRequest=0xC2  wValue=4  wIndex=1  wLength=38
  address = u32 little-endian of response[1..4]      (response[0] must be 0)

ReadFile(name, bufferSize)
  OUT  bmRequestType=0x40  bRequest=0xC0  wValue=2  wIndex=bufferSize
       data = [19, addr>>24, addr>>16, addr>>8, addr&0xFF, 0x00 * (bufferSize-5)]
  IN   bmRequestType=0xC0  bRequest=0xC0  wValue=2  wIndex=1
       wLength = bufferSize+1 if bufferSize+1 > 38 else 38
  payload starts at response[6]; the first 0xFF byte terminates the file
  address advances by (response length - 6) per chunk
```

Two details that are easy to get wrong and that the decompiled source makes explicit:

1. **The IN transfer repeats the OUT's `bRequest`.** It is `0xC2` for the address
   lookup and `0xC0` for the read — not `0xC0` for everything.
2. **`_maxRetries = 32` in `Meta2DeviceFiles` is a retry cap, not a chunk cap**, even
   though the same variable bounds the chunk loop. `calibration.bin` needs 62 chunks;
   a reader that stops at 32 gets 3,936 of 7,520 bytes. `[VERIFIED]`

Measured addresses and sizes:

| File | Address | Size | Content |
|---|---|---|---|
| `hwinfo.bin` | `0x00ff0000` | 17 B | the unit serial string `META2D<unit-serial>` |
| `calibration.bin` | `0x00fe0000` | 7,520 B | the full rig calibration XML |

`hwinfo.bin` answered on the first chunk: `resp 33 B payload 17 B` and the payload
ended at a `0xFF`. `calibration.bin` streamed 61 full chunks of 123 B plus a final
17 B chunk, terminating on `0xFF` at `0x00fe1d4f`. `[VERIFIED]`

## 11.2 The serial pairing is now closed

Earlier docs noted that the host-side calibration file is matched to a unit **by
filename only** — the serial is not inside the XML. That is confirmed: `grep META2D`
over `calibration.bin` returns **0** matches. The serial lives in `hwinfo.bin`, and the
SDK composes the host filename from it. Reading `hwinfo.bin` is therefore the correct
way to bind a calibration blob to a device. `[VERIFIED]`

## 11.3 The device copy and the host copy are the same file

`calibration.bin` (7,520 B) and the host-side
`AppData/Roaming/Meta Company/calibration/META2D<unit-serial>.xml` (7,679 B) differ
only in line endings: the host copy carries a **duplicated `\r` on every line**
(159 lines, 159 extra bytes). After normalising `\r\r\n` and `\r\n` to `\n`, both are
**7,361 bytes and byte-identical**. `[VERIFIED]`

So the host XML is a faithful copy of the device file, and the size difference is a
transfer artifact, not an SDK edit. A driver should still read the device copy — it is
the only copy guaranteed to match the unit in hand.

## 11.4 Structure of the calibration file

The repeating element is `<camera>`, which contains a `<camera_model>` **and a sibling
`<pose>`** holding `T_wc`. Parsing `camera_model` alone misses every pose.

`T_wc` is 3 rows × 4 columns: a 3×3 rotation plus a translation column, camera→world
(`X_world = R · X_cam + t`, so `t` is the camera centre in the world frame).

Model types are named in the `type` attribute:

- `calibu_fu_fv_u0_v0_kb4` — **Kannala-Brandt fisheye**, 4 distortion terms
  (`d = θ(1 + k1θ² + k2θ⁴ + k3θ⁶ + k4θ⁸)`). Both mono cameras use this.
- `calibu_fu_fv_u0_v0_k1_k2_k3` — ordinary radial. `depth` and `rgb` use this.

The `type` string names a parameter layout, not a formula, and `k1_k2_k3` is ambiguous
between radial-in-radius and radial-in-angle. **That ambiguity is resolved in docs/19 §19.3**:
`meta_calibu.dll`'s own disassembly gives `rd = r(1 + k1r² + k2r⁴ + k3r⁶)` with `r` from
`x/z, y/z` and no tangential term, and reprojecting matched features on a real capture
gives 13.4 px under that reading against 103 px under the other.

The declared index order is:

```
0 depth   1 mono_right   2 mono_left   3 rgb
4 accelerometer_right   5 gyroscope_right   6 accelerometer_left   7 gyroscope_left
8 g_cad_display   9 g_pmd_cad
```

**This index order does not correspond to USB tag order** (see §11.5). Anyone writing a
driver must not assume index 1 is the first mono stream on the wire.

The mono poses put the cameras at `x = ±0.069` m with forward vectors
`(±0.664, ~0.016, 0.748)` — each canted about **42°** outward from world `+z`, baseline
≈ 13.8 cm. The RGB `T_wc` is near identity, so the RGB image centre *is* the world `+z`
direction, which makes RGB a usable bridge between the two mono cameras.

## 11.5 Resolved: which calibration block is which camera on the wire

Established by two independent methods that agree.

**Method 1 — operator occlusion.** In the live preview, covering the wearer's left lens
blacked out the `EP 0x82 · tag 0x44` panel. `[VERIFIED]` The driver corroborates the tag
values: `DataScanner.IsMono0Header` tests `buffer[header+20] == 68` (`0x44`) and
`IsMono1Header` tests `85` (`0x55`), so `Mono0 = 0x44`, `Mono1 = 0x55`.

**Method 2 — reprojection through the calibration.** For SIFT matches between an RGB
frame and a mono frame, the RGB pixel is undistorted and back-projected, rotated into
the world frame with the RGB `T_wc`, rotated into the candidate mono camera frame with
that block's `T_wc`, and projected through that block's Kannala-Brandt intrinsics. The
median distance to the actual matched mono pixel:

| Frame pair | tag | vs `mono_left` | vs `mono_right` | match |
|---|---|---|---|---|
| 0.15 | `0x44` | **20.7 px** | 376.7 px | `mono_left` |
| 0.15 | `0x55` | 368.7 px | **72.6 px** | `mono_right` |
| 0.40 | `0x44` | **22.9 px** | 388.7 px | `mono_left` |
| 0.40 | `0x55` | 404.0 px | **14.9 px** | `mono_right` |
| 0.65 | `0x44` | **21.1 px** | 386.6 px | `mono_left` |
| 0.65 | `0x55` | 405.0 px | **15.5 px** | `mono_right` |

Six of six pairs agree, with a 20 px versus ~390 px margin. `[VERIFIED]`

**Conclusion: `EP 0x82` tag `0x44` = calibration `mono_left` = the wearer's left camera,
and tag `0x55` = `mono_right` = the wearer's right camera.** The SDK's naming is *not*
mirrored relative to the wearer.

Honest caveats on method 2:

- The reprojection uses **ray direction only** and ignores the 13.8 cm baseline
  parallax, which is why the correct block lands at ~15–22 px rather than a few pixels.
  At room distances the ignored parallax is on the order of 20 px, so the residual is
  expected and is not evidence against the mapping.
- Match counts were small (16–43 per pair) because the RGB and mono cameras differ in
  modality, resolution and focal length (`fu` 638 vs 222). The upper quartiles
  (p75 ≈ 120–310 px) show outlier matches; the medians are the meaningful statistic.
- A naive raw-pair disparity check (no calibration) was tried first and is **not
  usable**: across 204 textured rows, 70 % of best horizontal shifts were positive
  (median +116 px) but 30 % were strongly negative and the lower half pinned at the
  search boundary. The pair is unrectified fisheye with a 42° cant, so horizontal-only
  correlation is meaningless. `[VERIFIED]` as a method that does not work.

## 11.6 What a driver needs from this

1. Read `hwinfo.bin` first to bind calibration data to the unit.
2. Read `calibration.bin` in 128-byte chunks with no 32-chunk cap, terminating on `0xFF`.
3. Use Kannala-Brandt for the mono cameras and radial for RGB/depth; do not feed the
   mono intrinsics to a pinhole model.
4. Map wire tags to calibration blocks explicitly: `0x44 → mono_left`, `0x55 → mono_right`.
5. Treat the file index order as unrelated to wire order.

## 11.7 Depth camera intrinsics (from this unit's `calibration.bin`)

`re/e1_calibration.bin.txt` is the device's own `calibration.bin` read over the vendor
file path, and it is the rig XML. The `depth` block is the ToF camera:

```xml
<camera_model index="0" name="depth" type="calibu_fu_fv_u0_v0_k1_k2_k3">
  <width> 352 </width>
  <height> 287 </height>
  <right> [ 1; 0; 0 ] </right>
  <down>  [ 0; 1; 0 ] </down>
  <forward>[ 0; 0; 1 ] </forward>
  <params> [ 151.9015; 151.8631; 177.1966; 142.2995;
             0.1575959; -0.1942623; 0.04948911 ] </params>
</camera_model>
<pose><T_wc> [ 1,0,0,0; 0,1,0,0; 0,0,1,0 ] </T_wc></pose>
```

`fu 151.9015`, `fv 151.8631`, `u0 177.1966`, `v0 142.2995`, radial `k1 k2 k3`
= `0.1575959, -0.1942623, 0.04948911`. `[VERIFIED]` read from the device.

Two consequences:

1. **Height 287 confirms the row-0 sentinel independently.** The wire frame is
   352×288 (`0xa886` read-back and `TimeOfFlight16Image(352, 288)`), the calibrated
   image is 352×**287**. The extra row is the sentinel row, not a calibration error.
   `[VERIFIED]` by two independent sources.
2. The depth camera is the **rig reference frame** (`T_wc` is identity). Mono and RGB
   poses are given relative to it, so a depth pixel back-projects directly into rig
   coordinates with no extra transform.

Back-projection once values are interpretable:

```
x = (u - u0) / fu ; y = (v - v0) / fv ; ray = (x, y, 1) / ||(x, y, 1)||
point = depth_value * ray            # already in rig frame
```

Horizontal FOV implied by `fu 151.9` at 352 px: 2·atan(176/151.9) ≈ **98.4°**.
Vertical: 2·atan(143.5/151.86) ≈ **87.0°**. Both `[INFERRED]` from the intrinsics alone.
