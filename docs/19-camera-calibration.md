# 19. Camera calibration

Per-unit intrinsics and extrinsics for the four imaging sensors, read out of the
vendor calibration rather than re-measured.

Status: camera intrinsics and camera-to-camera extrinsics are extracted and
validated. Camera-to-IMU extrinsics are **not** in the vendor calibration and
remain measured-only (`docs/18`).

---

## 19.1 Where the numbers come from

Two copies of the same per-unit calibration exist and they agree byte-for-byte
after whitespace normalisation (`docs/11` §11.3):

| copy | origin | path in this repo's work tree |
|---|---|---|
| `calibration.bin` | device, read over the vendor file protocol | `re/e1_calibration.bin.txt` (text dump) |
| `META2D<serial>.xml` | host, written by the SDK | `re/unit_calib.xml` |

The rig declares `version="5.0"` and holds **10 entries**: `depth`, `mono_right`,
`mono_left`, `rgb`, `accelerometer_right`, `gyroscope_right`, `accelerometer_left`,
`gyroscope_left`, `g_cad_display`, `g_pmd_cad`.

`meta2lib` parses this directly: `include/meta2/calibration.h`,
`src/calibration.c`, fixture `tests/fixtures/calibration.xml` (the device copy),
test `tests/test_calibration`.

---

## 19.2 The rig frame

`depth` has `T_wc` exactly equal to the identity, so **the world frame is the
depth camera's frame**. Independently confirmed from the other blocks:

- `mono_right` at `x = +0.06914`, `mono_left` at `x = −0.06885` → `+x` is the
  wearer's right.
- the mono optical axes are `(+0.663, +0.020, +0.748)` and `(−0.666, +0.011, +0.746)`;
  their bisector is `(−0.0018, +0.0212, +0.9998)` → `+z` is forward.
- `rgb`'s optical axis is `(+0.0069, +0.0012, +0.99998)` → also forward, and `+y`
  completes the frame pointing down.

So: **`+x` right, `+y` down, `+z` forward**, origin at the depth camera.

`docs/18` uses a different headset frame (`+X` forward, `+Y` wearer's left,
`+Z` crown). The conversion is `X = z`, `Y = −x`, `Z = −y`.

---

## 19.3 Lens models — settled two independent ways

The `<camera_model type="...">` name is a parameter *layout*, not a formula. The
five names present in `meta_calibu.dll`'s `.rdata` are `pinhole`, `k1_k2`, `kb4`,
`k1_k2_k3`, `rational6`.

**Evidence 1 — the vendor binary.** `meta_calibu.dll` imports OpenCV 3.20
`opencv_calib3d320.dll` and `opencv_core320.dll`, all by ordinal. Mapping the
ordinals through the OpenCV export tables shows only `solvePnP` and
`solvePnPRansac` come from calib3d: the distortion arithmetic is implemented
inside `meta_calibu.dll`. Disassembling the functions reached from each model's
vtable (`0x180251830` pinhole, `0x1802518f0` k1_k2, `0x1802519b0` kb4,
`0x180251a70` k1_k2_k3, `0x180251b30` rational6) gives, at `0x1800562b0` and
`0x1800563a0`:

```
k1_k2_k3   (radial, in radius)      rd = r * (1 + k1 r^2 + k2 r^4 + k3 r^6)
kb4        (Kannala-Brandt)         d  = theta * (1 + k1 theta^2 + k2 theta^4
                                              + k3 theta^6 + k4 theta^8)
```

with `r = sqrt(xn^2 + yn^2)` from `xn = x/z`, `yn = y/z`, and no tangential
(`p1`/`p2`) term in either. `[MEASURED — disassembly]`

**Evidence 2 — real images.** The two readings of `k1_k2_k3` differ by tens of
pixels, so they can be told apart by reprojecting matched features. On the
`ir29` capture (matched RGB + mono, frames paired by device trailer timestamp to
within 20 ms, SIFT matches RGB→mono, mono intrinsics and the extrinsics from
§19.5 held fixed, only the RGB lens model varied):

| RGB pixel radius band | radial **in radius** (vendor) | radial in angle (rejected) |
|---|---|---|
| 25–50 % of half-width (n = 242) | **13.4 px** median | 103.4 px median |
| 50–75 % (n ≈ 90) | 141.7 px | 144.3 px |
| all bands (n = 368) | **30.0 px** | 107.1 px |

`[MEASURED]` The mid-band figure of 13.4 px reproduces the 15–22 px that
`docs/11` §11.6 method 2 obtained independently. The outer bands are bad for
both models, which is what §19.6 predicts: past ~75 % of the half-width the
fitted model cannot represent the pixel at all.

The same script on the `probe8` pair gave 129 px vs 164 px — that capture is a
weak scene and does not discriminate; it is reported only to show the test is
sensitive to capture quality.

---

## 19.4 Intrinsics

| entry | model | fu | fv | u0 | v0 | distortion | frame |
|---|---|---|---|---|---|---|---|
| `mono_right` | `kb4` | 221.7278 | 221.8668 | 365.3564 | 242.1651 | `+0.0301576, +0.01465129, −0.003123266, −0.0006527817` | 752×480 |
| `mono_left` | `kb4` | 222.2690 | 222.1534 | 388.6442 | 237.3683 | `+0.03430237, +0.009457684, +0.0001394337, −0.001237485` | 752×480 |
| `rgb` | `k1_k2_k3` | 638.4901 | 638.6942 | 644.9223 | 377.5392 | `−0.3788911, +0.1770645, −0.04601525` | 1280×720 |
| `depth` | `k1_k2_k3` | 151.9015 | 151.8631 | 177.1966 | 142.2995 | `+0.1575959, −0.1942623, +0.04948911` | 352×287 |

Principal points sit within a few pixels of the frame centre for all four.
`fu ≈ fv` to 0.1 % everywhere: square pixels, no skew term in any model.

---

## 19.5 Poses and stereo geometry

`T_wc` is camera→world: `X_world = R · X_camera + t`, `R` the first three columns.
Every camera block measured is a proper rotation (orthogonality error ≤ 2e-7,
`det = +1.0000`); the vendor rotations are fitted, not exact, so a test tolerance
of `1e-9` is too tight.

| entry | rotation off identity | translation (m) | optical axis in world |
|---|---|---|---|
| `depth` | 0.00° | (0, 0, 0) | (0, 0, +1) |
| `mono_right` | 45.05° | (+0.06914, +0.00735, −0.01046) | (+0.66325, +0.02047, +0.74812) |
| `mono_left` | 44.97° | (−0.06885, +0.00648, −0.01004) | (−0.66592, +0.01125, +0.74593) |
| `rgb` | 0.68° | (−0.02701, +0.00111, +0.00085) | (+0.00689, +0.00123, +0.99998) |
| `g_cad_display` | 67.16° | (0, −0.03880, +0.05241) | (0, +0.92160, +0.38820) |
| `g_pmd_cad` | 25.00° | (−0.00040, +0.07307, −0.07321) | (0, −0.42262, +0.90631) |

Derived, from the table above:

- **mono baseline 0.13799 m** (13.8 cm).
- **mono optical axes 83.30° apart**, 41.65° each side of the bisector.
- the bisector **is the world `+z` axis** to 1.2°, i.e. the pair is symmetric about
  straight ahead.
- **`rgb` looks straight ahead**, 0.68° from the world frame, and sits 2.7 cm to
  the wearer's left of the depth camera.

Sanity check in the test: a world point 5 m straight ahead projects to
`mono_left (550.8, 283.8)` and `mono_right (204.5, 288.0)` — symmetric about each
image's principal point, as a symmetric pair should be.

`g_cad_display` and `g_pmd_cad` are `DisplayCalibration` entries with real poses
and no intrinsics. `g_cad_display`'s `forward` is `(0, +0.922, +0.388)`: the
screen faces mostly downward and 22° toward the front. `[MEASURED]` What
`g_pmd_cad` physically is (projector, or the PMD's own reference frame) is
`[UNRESOLVED]`.

---

## 19.6 How far each fitted model reaches

These are properties of **this unit's coefficients**, not of the models. They
matter because a driver has to refuse pixels it cannot explain rather than
invent a bearing.

**Mono (`kb4`).** The theta polynomial stops growing at **1.92–1.95 rad**
(110–112°). The far horizontal frame edge sits at **91.2°** on both cameras, so
the model covers the horizontal span comfortably. The extreme **corners do not**:
`rd` at a corner is 2.06 while the model's ceiling is 1.98. A driver must reject
the corner pixels, not extrapolate them.

**RGB (`k1_k2_k3`).** Read with the vendor's own formula, the polynomial
`r(1 + k1 r² + k2 r⁴ + k3 r⁶)` is monotone only out to **r = 1.3213**, i.e.
**52.9° off axis**, a pixel radius of **534 px**. The frame half-width is 640 px.
The test pins the boundary: 1170 px is representable, 1200 px is not. **The outer
ring of the RGB image cannot be produced by any ray under these coefficients.**
`[MEASURED]`

Two readings of that, and the difference has not been settled:

1. the coefficients were fitted on a crop, or on a lens whose real FOV is
   narrower than the delivered frame; or
2. the RGB entry is not the whole story for this camera (a different model, or
   additional terms the SDK applies elsewhere).

Nothing in the file decides between them. The practical consequence is the same
either way: undistorting RGB beyond 534 px from `(644.9, 377.5)` is undefined
behaviour and must be guarded.

**Depth (`k1_k2_k3`).** Monotone throughout its frame; no reach problem.

---

## 19.7 IMU entries: intrinsics yes, extrinsics no

Every IMU block carries:

- `<misalignment>` — cross-axis terms, all under 1.4 %, unit diagonal exactly 1;
- `<scale_factors>` / `<inverse_scale_factors>` — per-axis, spanning 0.9648–1.0199;
- `<bias>`;
- `<right> <down> <forward>` — the identity triad;
- `<T_wc>` — **the identity**.

| entry | scale_factors | bias |
|---|---|---|
| `accelerometer_right` | 0.997223, 1.00503, 0.985256 | −1.166, +0.747932, +0.757977 |
| `gyroscope_right` | 0.964847, 1.01712, 1.00389 | +0.00191901, −0.000309816, −0.000713799 |
| `accelerometer_left` | 0.992368, 0.992222, 0.980653 | −0.762126, +0.528013, +0.414564 |
| `gyroscope_left` | 0.971359, 1.01994, 1.00541 | +0.0107951, +0.00144179, −0.0110095 |

**There are no camera-to-IMU extrinsics here.** All four IMU poses are the
identity and the file asserts the sensor axes already coincide with the rig
frame. `docs/18` measured the opposite: the chips sit ~45° off the headset frame,
with `ay` the vertical axis on both. The vendor IMU poses are placeholders. The
measured map in `meta2lib/include/meta2/imu_calibration.h` is the only usable
camera-to-IMU transform. `[MEASURED]`

**The gyro biases are real, and they cross-check.** `docs/17` measured gyro bias
at rest of (1.0, −0.1, 0.5) counts on IMU0 and (7.6, 0.0, −13.8) counts on IMU1,
at 0.0613 deg/s per count. Converting to rad/s and comparing with the vendor
entries:

| vendor entry | magnitude | coached stream | magnitude | ratio |
|---|---|---|---|---|
| `gyroscope_right` | 0.00207 rad/s | IMU0 | 0.00120 rad/s | 1.72 |
| `gyroscope_left` | 0.01549 rad/s | IMU1 | 0.01686 rad/s | 0.92 |

The vendor's own left/right asymmetry (7.1×) reproduces the measured chip
asymmetry (14×), and no other pair of entries in the file does. That is what
pairs `gyroscope_left` with IMU1 (mux tag `0x66`) and `gyroscope_right` with IMU0
(mux tag `0x77`). `[INFERRED]`

**Accelerometer bias units are unresolved.** The gyro entries are plainly rad/s.
The accel entries (magnitude 1.03–1.57) match nothing in the coached data under
any unit assumption tried: `docs/18` measured IMU0 bias ≈ (−965, 94, 296) counts
at 16,430 counts/g, i.e. ≈ 0.06 g, three orders below the vendor number read as
g and two orders above it read as counts. Do not apply these accel biases until
the unit is established. `[OPEN]`

---

## 19.8 What `meta2lib` exposes

`include/meta2/calibration.h`:

- `meta2_rig_load_file()` / `meta2_rig_load_buffer()` — parse a rig;
- `meta2_rig_find()` — by name;
- `meta2_rig_stereo()` — the mono pair and its baseline;
- `meta2_camera_bearing()` — pixel → unit bearing in the camera frame, rejecting
  pixels outside the fitted model's range;
- `meta2_camera_project()` — unit bearing → pixel;
- `meta2_camera_to_world()` / `meta2_camera_from_world()`.

`bearing()` uses the spherical form for `kb4` (`sin θ cos φ`, `sin θ sin φ`,
`cos θ`), not `tan θ`: these fisheyes reach 91° at the frame edge, where `tan`
flips the ray. `project()` guards `z ≤ 0` only for the perspective models, for
the same reason.

---

## 19.9 Open

1. **Camera-to-IMU extrinsics.** Not in the vendor calibration. The measured map
   (`docs/18`) has a 6–10° accuracy floor from gravity poses, and the face test
   could not beat it (`docs/18` §18.3.1). The remaining route is optical: a
   checkerboard seen by the cameras while the IMU is coached, which ties the IMU
   to a camera axis instead of to gravity.
2. **The RGB model's 534 px reach** — crop, wrong model, or missing terms (§19.6).
3. **Accelerometer bias units** (§19.7).
4. **Which mux tag is "left" and which is "right"** — strongly suggested by the
   gyro-bias cross-check, not proven.
