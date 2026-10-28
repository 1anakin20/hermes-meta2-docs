# 22. The alignment app — complete plan before any code

`[OPERATOR-DIRECTED]` *"Let's do the alignment app, must run on linux and windows. Note the windows box
still has no working GPU. Make a complete plan of it and what comes next before moving forward, I want to
make sure it is right. It is starting to look like we do not need the in-tree, but I am still unsure."*

This document is the plan. It contains no implementation.

---

## 22.0 What this app is for, in one line

It answers **one** question — *is a pose-only display model adequate for this visor?* — and that answer
decides whether the in-tree Monado driver is ever needed. Everything else in the app exists to make that
answer trustworthy.

---

## 22.1 Hard constraints, measured

| Constraint | Status | Evidence |
|---|---|---|
| Must run on Linux **and** Windows | required | operator |
| **Windows target has no working GPU** | operator-reported, decisive | operator, 2026-10-28 |
| No GPU ⇒ **no OpenXR runtime is testable on that box today** | `[MEASURED]` | Monado `CMakeLists.txt:251` `XRT_HAVE_VULKAN "…(also needed for compositor)"`; `:285` even `XRT_MODULE_COMPOSITOR_NULL` `DEPENDS … XRT_HAVE_VULKAN`; `:304` `XRT_FEATURE_OPENXR DEPENDS … "COMPOSITOR_MAIN OR COMPOSITOR_NULL"`; `vcpkg.json` hard-depends on `vulkan` + `glslang` |
| Therefore the app must depend on **no runtime** | `[INFERRED]` | consequence of the two rows above |
| GPU-free rendering stack that is **already proven on the Windows 11 host** | `[MEASURED]` | `meta2-demo-viewer`: `find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)` — no GL/Vulkan component; rendering via `QPainter` + `QImage` (raster). Operator confirmed "It works" on the physical Windows 11 machine |
| Device plumbing already a library, cross-platform | `[MEASURED]` | `meta2lib` public headers: `stream.h` (`meta2_stream_start/read/health/pending/dropped/describe/stop`), `transport.h`, `mux.h`, `imu_calibration.h`, `calibration.h`, `trailer.h`, `frame.h`, `os.h` |
| Windows cross-build recipe already exists | `[MEASURED]` | viewer `CMakeLists.txt`: `META2LIB_LOCAL` or `FetchContent` with a **pinned revision**, and `LIBUSB_WIN` → `META2_LIBUSB_ROOT` so meta2lib does not pick up host libusb under MinGW |
| USB device and HDMI panel must be on the **same machine** | `[INFERRED]` | the app renders to the panel and reads the IMU; both must be local |

`[INFERRED]` **Consequence worth stating plainly:** the GPU situation blocks *both* integration tiers on
Windows. Tier 1 (Monado + remote driver) and Tier 2 (in-tree driver) both need Monado's Vulkan
compositor. The alignment app is the only substantial thing that can move right now, because it needs no
runtime at all.

---

## 22.2 The dependency the idea hides: it needs pose

The decisive test is "does a virtual object stay put when I move my head". That requires pose, and pose
does not exist yet. So **Phase 1 (IMU-only 3-DoF AHRS) is a prerequisite of this app, not a separate
milestone.** The app *is* Phase 1's payoff.

`[MEASURED]` What we have to build it from: two IMUs, device free-running ~400 mux records/s ≈ **200 Hz
per IMU** under paced-async sustain (`docs/10` §10.5); device clock **117,821,900 Hz** (`docs/16`); gyro
axes coincide with accelerometer axes on the same die (`docs/18`).

`[MEASURED]` **The limitation that will contaminate the test:** the mux record inventory contains
`IMU0`, `IMU1`, `MICS`, `NULL_AA` and `other=0` — **no magnetometer record type has ever been observed**.
An accelerometer+gyro AHRS therefore has **unbounded yaw drift**. A drifting yaw looks exactly like the
"swim" we are testing for.

`[INFERRED]` Design consequence, and it is the single most important correctness decision in this plan:

- **Pitch and roll are observable and bounded** (gravity fixes them). The stay-put test is trustworthy on
  those two axes.
- **Yaw is drift-limited.** Do not use yaw motion as evidence of calibration error. Either accept a short
  window before drift dominates, or measure the drift rate first and quote it.
- **A static test needs no pose at all** and is immune to both drift and latency. It must be the first
  test, not an afterthought.

---

## 22.3 Geometry: the portrait trap

`[MEASURED]` Panel EDID: one source mode, **2560 × 1440 @ 72 Hz**, 8-bit RGB SDR, no VRR.
`[MEASURED]` External spec: "Single LCD binocular", **1280 × 1440 per eye**.
`[OPERATOR-REPORTED]` Windows is set to **portrait**, so the desktop surface is 1440 × 2560.

`[INFERRED]` The eye split exists in **panel-native** coordinates (left 1280 × 1440, right 1280 × 1440,
side by side). Windows rotates the image, so in **desktop** coordinates each eye becomes a **1440 × 1280
band** — top or bottom, depending on rotation direction.

`[UNKNOWN]` Which band is which eye, and the rotation direction. **Do not assume it.** Milestone M2
exists only to determine it empirically: render a marker into each native half and ask the operator which
band they see it in. Getting this wrong silently produces an app that renders the correct image to the
wrong eye, which would then be *interpreted* as a calibration failure.

`[INFERRED]` The app renders **two views into one surface**, and must keep native-coordinate rendering
separate from the rotated presentation, so the eye split is defined in panel coordinates and never
re-derived from the desktop mode.

---

## 22.4 Calibration parameterisation — v1 is pose-only, matching the vendor

`[MEASURED]` The vendor's own display model is pose-only: `DisplayCalibration` entries `g_cad_display`
and `g_pmd_cad` carry poses and **no intrinsics** (`docs/19` §19.5). `g_cad_display`: rotation 67.16°,
translation `(0, −0.03880, +0.05241)`, forward `(0, +0.92160, +0.38820)`, in the rig frame.

`[INFERRED]` So v1 stores, per eye, a **6-DoF pose** of the virtual image relative to the head/IMU frame,
initialised from `g_cad_display` — not a distortion model.

Knob set, deliberately small enough that a human can actually converge on it:

| Knob | Why it is there |
|---|---|
| x, y, z | where the virtual image sits |
| yaw, pitch, roll | how it is oriented — the dominant error for a see-through display |
| one **depth/scale** knob | a virtual image at the wrong apparent distance is a real and common failure mode, and it is not a pose error |

`[INFERRED]` Deliberately **not** in v1: radial or polynomial distortion terms. A user cannot fit them by
eye, and adding them before the test would make the test uninterpretable.

`[INFERRED]` Storage: a JSON file, shaped to be reusable by Monado later — the North Star file
(`baseline`, per-eye FOV, `t265_to_nose_bridge`, and optionally the 4 × 16 `uv_to_rect` polynomials) is
the format template, so a v2 distortion result drops straight into a Monado driver if we ever need one.

---

## 22.5 Architecture

`[INFERRED]` New small tool, **`meta2-align`**, in its own repo, linking `meta2lib` by pinned revision
using the viewer's proven recipe (`META2LIB_LOCAL` / `FetchContent`, `LIBUSB_WIN` for the Windows
cross-build). Keeping it out of `meta2-demo-viewer` so a calibration instrument is not entangled with a
dev/debug viewer.

```
meta2lib stream thread  ->  AHRS (2 IMU, device-clock stamped)  ->  pose buffer
                                                        |
GUI thread: read latest pose -> project pattern into two native eye halves
          -> rotate to portrait desktop surface -> present via Qt raster
```

- **Qt6 Widgets, raster only.** No OpenGL, no Vulkan, no D3D. This is the GPU-free path already proven on
  the Windows 11 host.
- **No Monado, no OpenXR, no runtime.** The app is its own renderer.
- Arm/sustain/streaming: entirely `meta2lib` (`meta2_stream_start` with the measured `warm=7e`,
  `muxasync=8`, `muxhz=100`, `muxkeep` shape).
- Alignment UI: keyboard/gamepad nudges on the knob set, live preview, save/load JSON.

---

## 22.6 The test, and the three outcomes it can produce

Run in this order, because each phase is immune to a different confounder.

1. **Static (no head motion, no pose).** Render a fixed pattern. Compare against a physical reference the
   operator can see through the visor. Tests *placement* only. Immune to drift and to latency.
2. **Rotation, pitch and roll only.** Object should stay put. Trustworthy because gravity bounds these
   axes.
3. **Off-axis inspection.** Look at a straight rendered line while pitched/rolled. Tests whether the
   combiner bends geometry.
4. **Yaw, explicitly labelled drift-limited.** Recorded, not used as primary evidence.

| Observed | Meaning | Consequence |
|---|---|---|
| Object stays put and sits where intended | pose-only adequate | **out-of-tree is the destination**; in-tree needed only for passthrough |
| Stays put but offset / wrong apparent distance | pose + scale error, varies per user | **operator's per-user manual alignment fixes it, out-of-tree** |
| Straight lines visibly bend, or geometry deforms off-axis | real combiner distortion | **in-tree driver required** (`compute_distortion`) |

---

## 22.7 The confounder that could make the whole test lie: latency

`[INFERRED]` Qt raster + the desktop compositor is not a low-latency presentation path. Unknown, likely
multi-frame lag produces swim that is **indistinguishable from calibration error** to a human. On a
GPU-less Windows box we cannot currently fix this — the honest position is that the app measures
*placement*, and latency must be quantified separately rather than assumed away.

Mitigations, in order of value:

1. **Static phase first** — latency-immune, and it is the phase that answers the vendor-model question.
2. **Measure end-to-end latency before interpreting anything**: a known IMU rotation (a quick manual
   tilt) versus when the rendered object visibly moves. The headset's own RGB camera can film the panel,
   so this is measurable without extra hardware.
3. **Slow head motion**, so lag is small relative to the motion being judged.
4. **Distinguish by signature**: a constant offset that persists at rest is calibration; an error that
   appears only during motion and then settles is latency.

`[UNKNOWN]` The actual motion-to-photon figure for this path. It is a measurement, and it belongs in the
report next to the alignment result, not in a footnote.

---

## 22.8 Milestones, each with an exit test

| # | Milestone | Exit test (pass = measured, not asserted) |
|---|---|---|
| **M0** | Build matrix: Linux native + Windows cross-build using the viewer's pinned-meta2lib recipe | Both binaries start and open `2cfa:00f3` on their machines |
| **M1** | Live IMU + AHRS, numeric readout only (no display calibration) | A slow, deliberate 90° tilt reads within a stated tolerance; yaw drift rate measured and quoted |
| **M2** | Fixed pattern rendered to the panel, correct eye bands in portrait | Operator states which band is which eye; app config records it; no assumption left |
| **M3** | Pose-driven render using `g_cad_display` unmodified | The §22.6 phases run and land in exactly one row of the outcome table |
| **M4** | Alignment UI + saved JSON | Operator improves alignment in under 5 minutes, and the saved file reloads to the same result |
| **M5** | *(conditional, only if row 3)* distortion terms | Straight-line test improves measurably |

M3 is the milestone that answers the operator's question. M0–M2 exist so that M3 cannot be invalidated by
a build, a drift, or an eye-band mistake.

---

## 22.9 What this settles about in-tree — the operator's open doubt

`[INFERRED]` The decision is now a tree with a measurement at its root, not a judgement call:

- **Row 1 or 2** → out-of-tree (Tier 1) is sufficient for *display and pose*. In-tree is then needed only
  for **passthrough for third-party AR apps**, which is a separate, later goal — not a reason to build it
  now. The rebase tax measured in §21.4d (≈2–3 breaking changes per 2.4 years, 5–25 lines each) is the
  price of that later option, and it is small.
- **Row 3** → in-tree is mandatory, because `d/remote` hardcodes `u_distortion_mesh_set_none`
  (`r_hmd.c:175`) and cannot express distortion at all.

`[MEASURED]` What out-of-tree *can* already do, so the "row 1/2" branch is not a hope: `r_hmd.c:86-109`
returns client-supplied per-view poses and FOV **verbatim** when `per_view_data_valid` is set.

`[INFERRED]` So the operator's instinct is probably right, but it should stay uncommitted until M3
produces its row. Building the in-tree driver before M3 is the failure mode this plan exists to prevent.

---

## 22.10 Risks and unknowns, stated plainly

1. **GPU-less Windows.** Blocks any OpenXR runtime there (Vulkan), and makes presentation latency
   unknown. Not a blocker for this app; a blocker for everything after it on that machine.
2. **No magnetometer ⇒ yaw drift.** Handled by test ordering and by quoting the drift rate, not by hoping.
3. **Eye-band / rotation direction unknown.** Handled by M2.
4. **3-DoF cannot reveal parallax or depth errors.** A rotation-only rig cannot expose a wrong apparent
   distance the way a 6-DoF translation test would. The depth/scale knob is a hedge, not a substitute.
   `[INFERRED]` Full confidence in the display model needs 6-DoF, i.e. the VIO work.
5. **AHRS quality is itself unvalidated.** The corpus has never validated a pose against anything
   (`docs/21` §21.8). M1's tolerance must be measured, not assumed.
6. **`[UNRESOLVED]` tension:** external spec says `Optics: Curved mirrors`, vendor calibration is
   pose-only. M3 row 3 is exactly the test that resolves it.

---

## 22.11 What comes next, after this app

`[INFERRED]` In order, with the app's outcome deciding the branch:

1. **Fix the Windows GPU** (or accept Linux as the OpenXR host). Until then no runtime work is testable
   on Windows, which conflicts with the "Linux *and* Windows both" constraint. This is now a
   prerequisite, not a preference.
2. **VIO / 6-DoF** — needed for row-1/2 confidence (risk 4) and for the OpenXR tracker role regardless.
   Basalt (BSD-3) is the leading candidate; Monado's own tracker already speaks KB4.
3. **Then** the OpenXR integration, choosing Tier 1 or Tier 2 from the M3 row.
4. **Passthrough / third-party AR compatibility** stays a later goal, as the operator scoped it.

---

## 22.12 What I need before writing any code

1. **Which Windows box has no working GPU** — the physical Windows 11 host the headset is plugged into, or
   the QEMU VM? The EDID read earlier named **Intel Iris Xe** as the adapter for `DISPLAY\MVNEA60`, which
   is why I will not guess. If it is the physical host, §22.1's runtime-blocked conclusion applies to the
   primary target; if it is the VM, the physical host is unaffected.
2. **Approval of the milestone order** — specifically that M1 (AHRS) comes before any display work, since
   the app's central test depends on pose existing.
3. **A physical session** for M2–M4: they need eyes on the visor. Schedule when available.
