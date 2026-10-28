# 21. 6-DoF tracking and OpenXR — plan (DRAFT, for review)

**Status: PLAN ONLY. No implementation has been done. No device was probed while writing this.**

Every claim is tiered:
- `[MEASURED]` — produced by a tool run recorded in this repo (a doc section, an artifact, a test).
- `[INFERRED]` — derived from measured facts by reasoning stated in the open.
- `[UNKNOWN]` — the corpus does not establish it.
- `[COMPUTED HERE]` — arithmetic I did in this document from `[MEASURED]` constants, with the inputs named so it can be re-derived.

Citations point at `docs/NN-*.md` sections and `artifacts/*`. Nothing here is invented; where the corpus is silent, the gap is named.

---

## 21.0 The two facts that decide the whole architecture

**Fact A — head pose is a host-side product. The device does not compute it.**
`[MEASURED]` The vendor SDK's own graph, extracted from `meta_core_api.dll`, wires
`DeviceStreamBlock.mono0_OUT → VSlamBlock.left_mono_IN` and `mono1_OUT → right_mono_IN`
(`artifacts/sdk_graph_schema.txt` lines 815–848); `VSlamBlock.pose_OUT → LooseFusionBlock.pose_IN`
(same file, lines 853–866); `LooseFusionBlock` additionally takes `imu0_acc_OUT`/`imu0_gyro_OUT`
and carries `imu_only_tracking=false` (`artifacts/sdk_application_graph.txt`).
`[MEASURED]` In the only device-layer transcript of a healthy vendor session (IR-83), the SDK
configures RawImu ×2 / Mono ×2 / Rgb / Tof and then issues **zero** commands during seven minutes
of full-rate streaming (`docs/12-tof-investigation.md` §12.45).
`[MEASURED]` The same SDK build produced live pose on a physical PC (559 distinct translation
triples, 560 distinct quaternions) and a static pose in a VM (`docs/12-tof-investigation.md` §12.28).

**Consequence:** 6-DoF is a *host computation on streams we already deliver*. We are not trying to
make the headset produce a pose. We are trying to reproduce, on our own transport, the input set
that the vendor's host pipeline consumes. That reframes the whole problem as solvable with what we
have, plus calibration.

**Fact B (corrected 2026-10-28 by the operator) — the display is a generic HDMI display driven from
the host, and the headset speakers are driven through the same HDMI. It is not a USB problem at all.**

`[OPERATOR-REPORTED]` "The display is a simple HDMI display, the headset speakers are also driven
through the HDMI. It is not driven by the headset SoC, but rather as a HDMI display from the host."
(2026-10-28.) This **retracts** the sentence my first draft quoted, and it is not new information in
the corpus — `docs/01-device.md` §1.7 already carries the correction two paragraphs below the sentence
I quoted: "**Confirmed by the operator (2026-10-16): the display is a generic display driven over
HDMI.** It is not a USB data path at all, which is why no endpoint, command class or register in any
capture has ever looked like a display interface — there is nothing on the USB side to reverse-engineer
for it." `docs/09` §9.11 repeats it ("the display is simply not a USB problem"), and `docs/12` §12.9
has an experiment phase labelled literally "**90–150 s HDMI attached**". My draft quoted the stale
first paragraph and missed the retraction. That was the mistake.

What remains `[VERIFIED]` is only the **absence on the USB side**: no endpoint, command class or
register has ever looked like a display or audio interface, which is now *explained* rather than
mysterious — the display and speakers are not on this bus.

`[MEASURED]` What the vendor rig does have for the display is pose-only: `META2_LENS_DISPLAY /*
DisplayCalibration: pose only */` (`meta2lib/include/meta2/calibration.h` line 46), and `g_cad_display`
carries a forward vector `(0, +0.922, +0.388)` in the rig's world frame (`docs/19` §19.5). No lens
model, no screen geometry, no IPD.

`[OPERATOR-REPORTED]` One nuance worth keeping: `docs/13` §13.9 records that holding the left-arm light
button toggles the HDMI display off and on with an audible "bloop". So the headset's own hardware may
still gate the display's *enable/power* even though the pixels come from the host.

**Consequence — and it is the opposite of what my first draft said:** an OpenXR **HMD role** is
feasible. Putting pixels and sound on this headset is an ordinary host-side display problem that the
host's GPU and audio stack already solve; it is "just a screen". What is *not* solved is rendering
**correctly**: with no display intrinsics, no screen geometry and no IPD, there is nothing to warp a
rendered image against. So the HMD blocker moves from *no data path* (false) to *no display optics
calibration* (true, and measurable). See §21.4.

### Fact B.1 — the display, measured from the host (2026-10-28)

`[MEASURED]` The operator enumerated the panel from Windows with no device probing:

| Fact | Value | Source |
|---|---|---|
| Panel count | **One.** Windows enumerates exactly two displays: `DISPLAY\DELD01D\…` (the operator's Dell monitor) and `DISPLAY\MVNEA60\…` (the headset). | `Get-CimInstance -Namespace root\wmi -ClassName WmiMonitorID` |
| EDID vendor/product | `MVN` + `EA60` — a distinct EDID identity, not a generic sink. `[INFERRED]` `MVN` = Metavision. | same |
| EDID declared modes | **`NumOfMonitorSourceModes = 1`**, `PreferredMonitorSourceModeIndex = 0` — a fixed embedded panel that declares exactly one mode. | `WmiMonitorListedSupportedSourceModes` |
| Mode | **1440 × 2560 @ 72 Hz**, 8-bit, RGB, SDR, **variable refresh rate: Not Supported** | Windows display adapter properties, display named **"Meta2"** |
| GPU driving it | Intel(R) Iris(R) Xe Graphics (host iGPU) | same |
| Optics | **No lenses.** The panel is **reflected onto a visor** — an optical see-through combiner, not a lens-coupled direct-view HMD. | `[OPERATOR-REPORTED]` |
| Orientation | **Portrait is a deliberate Windows setting so the image fills the panel.** Windows therefore reports the desktop/active mode as 1440 × 2560; the panel itself is 2560 × 1440. | `[OPERATOR-REPORTED]` 2026-10-28 |

### Fact B.2 — the first independent external specification ever checked against this unit (2026-10-28)

`docs/07` §7.8's standing complaint — "no external spec has been cited anywhere in this repo" — is now
addressed. VRcompare's Meta 2 spec page and a 2016 RoadToVR pre-order article were read directly:

| External claim | Our measurement | Verdict |
|---|---|---|
| "Display Type: **Single LCD binocular**", "Ocularity: **Binocular**" | One EDID panel (`DISPLAY\MVNEA60`) | **Agrees.** One panel, seen by both eyes through the combiner. |
| "Optics: **Curved mirrors**" | "reflected back on a visor" | **Agrees, and it matters:** a *curved* combiner is not a flat mirror — see the correction under Phase 7. |
| "Resolution 1280×1440 per-eye … **3.69 million pixels overall**" | 1440 × 2560 reported = **2560 × 1440 = 3,686,400 px** | **Agrees exactly.** The panel is 2560 × 1440 and each eye is served a 1280 × 1440 half of it. |
| "Native passthrough, **720p camera**" | EP `0x83` = **1280 × 720** UYVY | **Agrees exactly.** |
| "PC-powered AR", "requires a connection to a PC", HDMI from the host | `[OPERATOR-REPORTED]` HDMI display + speakers from the host | **Agrees.** |
| "6 DoF tracking", "does not require external base stations" | not yet measured by us | Corroborates that inside-out 6-DoF is a real shipped capability of this device — the whole premise of this plan. |
| "Refresh Rate **60 Hz**" | EDID/Windows active signal mode **72 Hz** | **Conflict.** `[UNKNOWN]` which is real; resolve before pacing a renderer. |
| "Meta (2016) … **no relation to Meta Platforms Inc**"; liquidated, assets acquired by Campfire | `docs/14` §1's identity rule | **Agrees**, and adds lineage: the Meta 2 design was adapted into the Campfire Headset. |

`[INFERRED]` **Correction to what I wrote above: this is a binocular single-panel see-through display,
not a monocular one.** One panel, both eyes, served through curved mirrors, each eye taking a 1280 × 1440
half. That changes the rendering target concretely: a renderer must produce **two 1280 × 1440 views into
one 2560 × 1440 swapchain**, not one full-panel image.
`[MEASURED]` The vendor's per-eye compositor views (`GetDepthStencilViewForLeftEye/RightEye`) now read as
corroboration of that split rather than as a software artefact, which is what I claimed a moment ago.
`[UNKNOWN]` binocular overlap, IPD range (the external spec leaves it blank, consistent with fixed
optics), and how the two halves map onto the visor.

`[MEASURED]` This corroborates the rig. `g_cad_display`'s forward is `(0, +0.922, +0.388)` — "the
screen faces mostly downward and 22° toward the front" (`docs/19` §19.5) — which is exactly the layout a
downward-facing panel reflecting off a visor produces. `[MEASURED]` The rig has **no visor entry at
all**: `DisplayCalibration` gives poses for `g_cad_display` and `g_pmd_cad` and no intrinsics, and
nothing in the rig describes the combiner itself.

`[INFERRED]` **This is an optical see-through display, not a lens-coupled VR HMD.** One panel, no lenses,
a curved-mirror visor. That removes one blocker my draft listed and sharpens two others — and my first
pass at this got the ocularity wrong; see Fact B.2 for the correction.

- **No lens to invert.** There is no lens distortion model to fit. `[MEASURED]` The rig agrees:
  `DisplayCalibration` entries carry poses and **no intrinsics**.
- **But the combiner is curved** (`[MEASURED]` external spec: "Optics: Curved mirrors"), so the panel →
  virtual-image mapping is **not** a plain pose either. My earlier "start from a pose model, not a
  distortion model" was too optimistic and is corrected under Phase 7.
- **IPD is not something we can set.** `[MEASURED]` The external spec lists no IPD range, consistent with
  fixed optics; the rig has no IPD parameter. So IPD is a property of the hardware we must measure or
  work around, not a knob.
- **What the whole display-calibration problem reduces to:** the mapping from panel pixels to
  virtual-image rays through a curved combiner, per eye. Nothing in the corpus or the rig describes it.

`[MEASURED]` A concrete lead for reimplementing the vendor's alignment setup: `CompositorBlock`
(library `meta_block_compositor`) declares `loose_fusion_name = LooseFusionBlock` and
`sensors_db_task_name = SensorsDbBlock` (`artifacts/sdk_graph_schema.txt` lines 118–137) — the vendor's
renderer consumes **pose from the fusion block and calibration from the sensors DB**, and the sensors DB
is what holds the rig including `g_cad_display`. `[INFERRED]` So the vendor's "align the rendered
content" step is very likely a pose stored in that rig, which `meta2lib` already reads off the device.
`[UNKNOWN]` whether the vendor setup writes a new value into the rig, into a separate file, or keeps it
in memory only — that is a host-side SDK observation to make, not a device experiment.

---

## 21.1 What is already solved (measured inventory)

| Layer | State | Evidence |
|---|---|---|
| Transport / arm / sustain | Solved. Pump thread, 8 async IN transfers per endpoint, gated startup. `ctest` 6/6 green, 163 MB/s aggregate across all four endpoints. | `docs/14-project-state.md` §3 |
| Endpoint → sensor map | Solved. `0x81` mux (IMU0/IMU1/mics/`0xAA`), `0x82` mono pair 2×752×480 10-bit, `0x83` RGB 1280×720 UYVY, `0x84` ToF 352×288. | `docs/05`, `docs/08`, `docs/13`, `docs/15` |
| Enable masks | Solved. `0xC0`/6 `[0,4,0,0,0,mask]`: Mono0=2 (wearer's left, tag `0x44`), Mono1=4 (wearer's right, `0x55`), ToF=8, Mux=16, RGB=32, STD=64. `mux_mask`: IMU0=1, IMU1=2, Mics=4, Buttons=8, unnamed bit 4=16. | `docs/09-driver-decompiled.md` (SensorType table), `docs/10-enable-masks.md` §10.1, `docs/08-camera-inventory.md` §8.10 |
| Time base | Solved. 32-byte trailer on **every** endpoint, u64 `TimeStampHi:TimeStampLow` at `magic-8`, **117,821,900 ticks/s** (`META2_TICKS_PER_S`), RGB/mono/IMU on one axis. RGB cadence 3,927,221 ticks/frame (30.0013 fps), mono 1,963,229 (60.0143 fps). | `docs/16-time-base.md` §16.3.2, §16.4.1, §16.7, §16.12; `docs/17-imu-calibration.md` §17.4 |
| Mono pair simultaneity | Solved. Identical trailer timestamps, independent packet counters; exposure phases 0.08–0.12 ms apart, within 1.2σ of zero, two runs. | `docs/16` §16.4.2, `docs/15` §3 item 2 |
| Camera intrinsics | Solved, read off the device. `calibration.bin` (7,520 B UTF-8 rig XML at `0x00fe0000`), byte-identical to the host copy. Mono = KB4 fisheye, `fu 221.7278 / 222.269`, `fv 221.8668 / 222.1534`, `u0/v0 365.36/242.17` and `388.64/237.37`, 752×480. RGB = `k1 k2 k3`, `fu 638.4901`, 1280×720. | `docs/11-device-files.md` §11.4–11.7, `docs/19` §19.1, fixture `meta2lib/tests/fixtures/calibration.xml` |
| Camera-to-camera extrinsics | Solved. `T_wc` per camera; baseline **0.137995 m**, axes 83.30° apart, canted 41.65° outward, fields overlap ±49.6° around straight ahead. `meta2lib` already parses them (`meta2_rig_stereo`, `meta2_camera_transform`). | `docs/15` §1, `docs/19` §19.5, `meta2lib/include/meta2/calibration.h` |
| IMU scales | Solved. Gyro **0.0613 deg/s per count** (16.32 counts per deg/s), ±2000 deg/s full scale. Accel **16,430 / 16,506 counts/g**, ±2 g. Rest biases measured. Turn-integral spread 4.5%. | `docs/17` §17.2–17.3, `docs/18-imu-axis-map.md` §18.5 |
| IMU axis map | Solved to a stated floor. Chips sit ~45° off the headset frame; `ay` is vertical on both with opposite signs; `meta2_imu_to_headset()` exists. | `docs/18` §18.2, `meta2lib/include/meta2/imu_calibration.h` |
| Frame integrity | Solved *by the gated recipe, in one run*: mono delivered 1,199/1,199 frame slots per camera, resyncs 0, dropped 0. The corpus itself marks repeating this as open. See §21.3 for the full delivery picture. | `docs/15` §1 EP `0x82` (and its `[OPEN]` note in §3) |
| Vendor architecture reference | Decoded. `VSlamBlock` (library `meta_block_slam`, vocabulary `data/vslam_voc.bin`, `target_frame=mono_right`, `source_frame=world`, REALTIME TRIGGERED thread) → `LooseFusionBlock`. Vendor SLAM is ORB-SLAM2-derived (`meta_block_pangolin_viewer.dll`). | `artifacts/sdk_graph_schema.txt`, `docs/12` §12.19 |
| Display (host side) | Solved as a display, unsolved as optics. `[MEASURED]` One panel, `DISPLAY\MVNEA60`, one EDID source mode, **1440 × 2560 @ 72 Hz**, 8-bit RGB SDR, no VRR, on Intel Iris Xe. `[OPERATOR-REPORTED]` No lenses; reflected onto a visor. `[MEASURED]` The rig has a `g_cad_display` pose and **no combiner entry**. | `docs/21` Fact B.1, `docs/19` §19.5 |
| OpenXR prior work | **None.** Zero occurrences of OpenXR / Monado / libsurvive / SteamVR anywhere in `meta2-docs` or the skill references. Greenfield. | corpus-wide grep, 2026-10-28 |

---

## 21.2 What is missing, ranked by how hard it blocks 6-DoF

1. **Camera-to-IMU extrinsics.** `[MEASURED]` absent: all four vendor IMU poses in the rig are the
   identity, and identity is *proven wrong* by six coached gravity poses (`docs/15` §1;
   `calibration.h` header comment; `docs/18`). The corpus's own conclusion: **"what is still missing
   for a real VIO input set is calibration, not protocol"** (`docs/15` §5 Phase 4). This is the
   blocker.
2. **IMU sample rate — resolved 2026-10-27, and it was our own loop, not the device.**
   `[MEASURED]` `docs/10` §10.5: the mux rate is set by the **host's control-write cadence** and is
   host-independent. Four Linux and four Windows runs of the same binary, cameras at nominal, zero
   dropped bytes: assert-only synchronous → 7 records/s; toggle off→on synchronous → 46–53; paced
   async with 8 writes in flight and the submask never deasserted → **399 (Linux) / 398–401
   (Windows)**; same with `mux=0x1f` (microphones added) → **2,542 / 2,544**. An 8× sweep of the write
   rate (50 → 400/s) moved the steady rate by 11 records/s, so the high mode is a free-run, not a rate
   control. **The device's rate is ~400 records/s for the IMU pair, ~200 Hz each.** The old 46.4/46.6
   figure was the previous sustain loop's own write rate read back. `[MEASURED]` `docs/10` §10.9
   independently: IMU0 and IMU1 each advance 589,109 ticks per record = **200.05 Hz**, and the IMU
   cadence is invariant across starved and healthy sessions.
   `[OPEN]` what remains is *which sustain shape a tracking session will use*, because the rate is a
   property of the host loop — a tracking front end must run the paced-async sustain or it silently
   drops to ~23 Hz per IMU. That is a design constraint, not an unknown.
3. **IMU noise characterisation.** `[UNKNOWN]`. Vendor `noise_sigma`/`bias_sigma` are 0 and
   `bias_cov` is zero — placeholders. Only rest standard deviations exist (gyro ~2 counts, accel
   37–148 counts). No Allan variance has ever been computed.
4. **Absolute latency and the device↔host clock bridge.** `[UNKNOWN]`. No measurement of
   sensor-event → host-arrival latency exists anywhere (`docs/16` §16.7 lists offsets as
   `[INFERRED]`, never calibrated; 1.48e9 ticks in one session, 179,005 in another). Two measured
   facts bracket how much room there is to be wrong: `[MEASURED]` RGB and mono frames were paired by
   trailer timestamp **to within 20 ms** for SIFT reprojection (`docs/19` §19.3) — a whole frame
   period, and the only cross-stream pairing accuracy ever demonstrated; and `[MEASURED]` after the
   arm the device holds **seconds** of backlog, while fixed 4/8/1 MiB reader rings are only 46 ms of
   a healthy mono stream (`references/demo-viewer.md`; `docs/13` §13.4). OpenXR needs a pose at a
   *predicted display time in host time* — that requires a maintained device↔host mapping and a
   latency budget, neither of which exists yet.
5. **Clock semantics under host load.** `[MEASURED]` the clock is production-coupled: a 3.000 s host
   read stall removed 500,101,379 ticks from the delivered span, so **a host-caused gap is invisible
   in device time** (`docs/16` §16.11). Any integrator must detect gaps host-side and refuse to
   integrate across them. This is a design requirement, not an open question.
6. **Mono shutter model.** `[UNKNOWN]`, and the corpus says a 60 Hz target cannot settle it
   (`docs/15` §3). Matters only for fast rotation if it is rolling.
7. **The mono lens model does not cover the corners of its own frame.** `[MEASURED]` `docs/19`
   §19.6: the KB4 `θ_d = θ(1 + k1θ² + k2θ⁴ + k3θ⁶ + k4θ⁸)` polynomial stops growing at
   **θ = 1.92–1.95 rad**, so `θ_d` has a hard ceiling of **1.98 rad**; `rd` at a frame corner is
   **2.06**, above that ceiling. "A driver must reject the corner pixels, not extrapolate them."
   `[COMPUTED HERE]`, re-derived from the measured coefficients and the actual principal points
   (`u0/v0` = 365.36/242.17 right, 388.64/237.37 left on a 752×480 frame) — this reproduces
   `docs/19`'s numbers exactly, which is the check that the arithmetic is right:
   `θ_d` ceiling 1.9858 / 1.9842 rad at θ = 1.946 / 1.922; far horizontal edge at **91.19° /
   91.17°** (docs/19 says 91.2° on both) → **HFOV 182.4° / 182.3°**; far vertical edge at
   59.83° / 59.55° → **VFOV 119.7° / 119.1°**; corner `rd/f` = 2.054 / 2.059 rad → **outside the
   model**. So the horizontal and vertical spans are covered and only the corner regions are not.
   `[INFERRED]` the unusable region is the corner caps beyond `θ_d = 1.98`, i.e. pixels whose radius
   from the principal point exceeds `1.98 × f ≈ 439 px` — a corner band roughly 100 px deep on the
   diagonal, not a border band on all four edges.
   **Practical rule: feature extraction must reject pixels `meta2_camera_bearing()` returns −1 for,
   and must not be given a rectangular mask that throws away good edge pixels.** The RGB model has
   the same class of problem, worse: `docs/19` §19.6 shows the vendor `k1 k2 k3` polynomial is
   monotone only to **r = 1.3213 rad (52.9°, a 534 px radius)** against a 640 px half-width, so
   "the outer ring of the RGB image cannot be produced by any ray under these coefficients".
8. **Buttons have never been seen on the wire** (`docs/15` §1, mux tag `0x99`). Blocks any OpenXR
   input profile. Another reason to start with a role that needs no inputs.
9. **Two headsets are indistinguishable by USB descriptors** — no serial number, `bcdDevice 0.00`
   (`docs/01` §1.3). Unit identity must come from `hwinfo.bin` (`docs/11` §11.2/§11.6).

---

## 21.3 What this rig can physically deliver (arithmetic, so expectations are honest)

Inputs: measured `f ≈ 222 px` (mono), measured baseline `B = 0.137995 m`, so `f·B = 30.635 m·px`.

- **Stereo depth from the mono pair** (`σ_Z = Z²·σ_d / (f·B)`, `[COMPUTED HERE]`):

  | range | disparity | σ at 0.05 px | σ at 0.1 px | σ at 0.3 px |
  |---|---|---|---|---|
  | 0.5 m | 61.3 px | 0.4 mm | 0.8 mm | 2.4 mm |
  | 1 m | 30.6 px | 1.6 mm | 3.3 mm | 9.8 mm |
  | 2 m | 15.3 px | 6.5 mm | 13.1 mm | 39.2 mm |
  | 3 m | 10.2 px | 14.7 mm | 29.4 mm | 88.1 mm |
  | 5 m | 6.1 px | 40.8 mm | 81.6 mm | 245 mm |
  | 8 m | 3.8 px | 105 mm | 209 mm | 627 mm |

  `[INFERRED]` Metric translation is credible to roughly **1–3 m at centimetre level** and degrades
  as Z². The corpus reaches the same conclusion from the geometry rather than from this error model
  (`docs/15` §1, "What that pair is for"): "A wide baseline, outward-canted, ultra-wide fisheye pair
  is the standard mounting for **visual tracking over a room**: the splay covers a large workspace and
  13.8 cm gives strong parallax at distance. It is a poor near-field stereo depth rig — close content
  has enormous parallax and does not correspond between the frames. Ship the tracking capability; do
  not promise metric depth at arm's length."
- **Angular resolution** `[COMPUTED HERE]`: `1/f = 0.258°/px` ≈ 929 arcsec/px. Rotation accuracy
  from many matched features is far better than one pixel; the limiting factor will be IMU bias and
  extrinsics, not pixels.
- **Field of regard** `[COMPUTED HERE]`: each mono axis is canted 41.65° outward from the rig's world
  +z (`docs/19` §19.5), so a point dead ahead sits at θ = 41.65° off each mono axis, which the KB4
  model maps to `r_d = f·θ_d = 164 px` from the principal point — 43% of the way to the frame edge,
  comfortably inside both frames. `[MEASURED]` agreement: `docs/15` §1 reports a dead-ahead point at
  `u ≈ 204` in `mono_right` and `u ≈ 551` in `mono_left`, i.e. 161 px and 162 px from the respective
  principal points, against 164 computed. The pair is outward-canted, so the *overlap* is centred
  ahead and the outer halves of each fisheye see wide side fields.
  `[INFERRED]` Tracking will be strongest when the wearer faces textured scenery and weakest when
  facing a blank wall or looking down — and the display normal `(0, +0.922, +0.388)` says the wearer
  looks *down* through the optics (`docs/19` §19.5). `[INFERRED]` The cameras do not cover where the
  wearer looks. That is a usability finding for any AR application, and it is worth stating to the
  user before anyone builds an app.
- **Frame budget and what mono delivery actually is.** `[COMPUTED HERE]`: the mono pair is
  721,952 B per frame record × 60.0143 fps ≈ **43.3 MB/s**; RGB measured 58–85 MB/s when all four
  endpoints are drained (`docs/10` §10.5). `[MEASURED]` mono delivery completeness is **not** a fixed
  rate, and the plan must be built for that:

  | configuration | mono complete | fps/camera | source |
  |---|---|---|---|
  | non-gated capture | 71–76% of trailer gaps exact, ~20% torn | **27.0** | `docs/15` §1 EP `0x82` |
  | `meta2_stream_start()` defaults, gate accepted, 20 s, mux+RGB enabled and drained | 1,199 of 1,199 device slots | **60.00** | `docs/15` §1 EP `0x82` |
  | all four endpoints drained, mask `0x7e`, five 8 s runs | 33.5 / 69.2 / 55.5 / 74.0 / 75.0% | 41.5 / **76.6** / 72.6 / 47.7 / **3.0** | `docs/10` §10.5 |

  `[INFERRED]` VIO tolerates an irregular frame rate — it does not tolerate an unrecognised one — so
  the design must key on **whole frames plus device timestamps plus `PacketNum`**, and treat a missing
  slot as a detected gap rather than as a thing to interpolate. The frame-locked mono pair and the
  `resyncs=0` behaviour over 426,367 fragments (`docs/15` §1) make that possible.
  `[FLAG]` The **76.6 fps/camera** entry exceeds the measured 60.0143 fps device cadence, so that
  table's accounting has not been reconciled with the slot rate and must be re-derived before anyone
  uses it as a budget. The 3.0 fps run in the same table is `docs/10` §10.3 hysteresis, not a new
  failure mode.
  `[MEASURED]` Whatever mask is used, `docs/10` §10.2 holds: "A reader must keep a URB pending on
  **every** bulk IN endpoint, including ones whose data it discards", and `docs/10` §10.5 shows the
  library already drains EP `0x84` and throws it away for exactly that reason. A tracking mode that
  stops servicing `0x83`/`0x84` will look like a camera failure and is not one.

---

## 21.4 The OpenXR decision, made early because it changes everything

OpenXR device roles are not interchangeable. Given Fact B **as corrected**:

| Role | Feasible today? | Why |
|---|---|---|
| **TRACKER** (`XR_EXT_tracking_only`, position+orientation in a tracking space) | **Yes — and still the right first target**, but for a different reason than my first draft gave. Not because the display is unreachable, but because pose is the part that does not exist yet and every other role depends on it. | Needs pose + a space + a clock bridge. All three are buildable; none is built. |
| **HMD** (runtime composites, headset shows) | **Yes, feasible.** `[OPERATOR-REPORTED]` The display and speakers are host-driven HDMI — "it's just a screen". `[MEASURED]` One panel, 1440 × 2560 @ 72 Hz, 8-bit RGB SDR, no VRR. The blocker is **not** a data path. | Blocked instead on: the visor projection (below), no validated pose, no latency measurement. All measurable, so this is a calibration-and-quality problem, not a missing capability. |
| **See-through rendering** (the honest description of this device) | **Yes.** `[OPERATOR-REPORTED]` One panel, **no lenses**, reflected onto a visor. `[MEASURED]` External spec: "Single LCD binocular", "Optics: Curved mirrors", 1280 × 1440 per eye from a 2560 × 1440 panel. | Needs two 1280 × 1440 views into one swapchain, and a **curved-combiner projection** per eye — which nothing in the corpus or the rig describes. The vendor has a user-facing alignment setup for exactly this; see Fact B.1 for the lead on reimplementing it. |
| **Stereo HMD in the VR sense** (two panels, lens-coupled, IPD adjustment) | **No — and this unit is not one.** `[MEASURED]` One EDID panel, no lenses, no IPD range. | Do not describe this device as a VR HMD. It is binocular see-through AR through curved mirrors. |
| **HMD with passthrough/depth** | No. | Depth (`0x84`) has never produced scene information (`docs/14` §3: "Depth has never been observed in any path"). |
| **Hand/controller inputs** | No. | Buttons never observed on the wire (`docs/15` §1). `[OPERATOR-REPORTED]` Audio **output** is available, over the same HDMI. |

Two implementation routes for the tracker role, both real work, pick one in Phase 0. **Fact B as
corrected changes this choice, because a runtime that also drives a display is a different amount of
work than one that does not:**

- **Route A — provider plugin for an existing OpenXR runtime (Monado). Chosen by the operator
  2026-10-28, and it must be cross-platform: Monado on the Linux box *and* on Windows.** `[MEASURED]`
  What that actually means, read from Monado's own documentation:
  - The surface we would write against is `xrt_device`, plus a prober — either `xrt_auto_prober` or an
    `xrt_prober_found_func_t` — registered in `src/xrt/targets/common/target_lists.c`. Monado's own
    guidance: "you use the auto prober interface when the basic USB VID/PID-based interface is not
    sufficient … or if you don't want to use the built-in HID support." Our device is VID/PID-visible
    (`2CFA:00F3`) but not HID, so the auto prober path is the one.
  - **A maintenance warning from Monado itself:** "Monado is intended to not expose any external API
    other than the OpenXR API: the XRT interfaces are subject to change as required so those writing
    drivers or other software on those interfaces are encouraged to upstream as much as possible to
    minimize maintenance burden." `[INFERRED]` A private out-of-tree driver is a standing rebase tax;
    upstreaming `meta2` into Monado is the low-maintenance path if we ever want that.
  - **The Windows problem is real and specific.** `[MEASURED]` Monado's own Windows build page: "Monado
    has a **work-in-progress port to Windows**. While it's **not ready for widespread usage due to some
    rough edges and lack of drivers**, it does build and can serve as a base for further development."
    And under Limitations: "there are current limitations in the Windows build. The main one currently is
    **no actual headset drivers yet**, partially because **some USB stuff needs porting**, and partially
    because **direct mode on Windows is more complicated**." `[INFERRED]` That is precisely the surface we
    need — a USB device driver plus display presentation — so on Windows we would be writing the driver
    *and* porting underneath it.
  - Practical Windows details from the same page: build with CMake + vcpkg, `-DXRT_FEATURE_SERVICE=ON`
    for the out-of-process `monado-service.exe`, and point clients at the runtime with
    `XR_RUNTIME_JSON=…\openxr_monado-dev.json` instead of installing the manifest into the registry.

`[INFERRED]` Consequence for sequencing: **Linux is where the Monado provider should be built first**,
because that is where Monado is a finished product. The Windows target is real work on Monado's own
unfinished port, and it should be scheduled as its own phase rather than assumed to be a rebuild.

### 21.4a If Monado on Windows turns out to be bad: the alternatives, measured

Read from Monado's own tree (`gitlab.freedesktop.org/monado/monado`, sparse clone at
`~/work/monado-src`, 2026-10-28), its changelog, and its developer site.

**First, what is actually missing on Windows — it is narrower than "Monado doesn't work there."**
`[MEASURED]`

- The runtime is actively maintained and released: vNEXT (2026-10-24), 25.1.0 (2025-12-09), 25.0.0
  (2025-04-18), 24.0.0 (2024-06-07).
- The Windows *runtime* side is getting fixed continuously: IPC over named pipes (!1525), D3D11 client
  compositor (!943), D3D12 (!1340), OpenGL on Windows (!1465), Win32 GL handle import (!2302), "Build
  system support for D3D on Windows" (!2276), and a Windows named-pipe shutdown fix in the current
  vNEXT (!3029).
- What is missing is the **device** side and **presentation**: in-tree `doc/winbuild.md` — "no actual
  headset drivers yet, partially because some USB stuff needs porting, and partially because direct mode
  on Windows is more complicated" — and the developer site, more bluntly: *"Most of the included VR
  hardware drivers are limited to Linux at this time… On Windows, mostly simulated HMD and controller
  drivers are usable. **Direct Mode access for existing HMDs when not using NDA APIs remains a major
  blocker.**"*

`[INFERRED]` That splits our problem cleanly. We are not blocked by "OpenXR on Windows" — clients work
there. We are blocked by (a) nobody has written a USB headset driver for Windows Monado, and (b) direct
mode. Both are avoidable by choosing a different *shape* of integration.

**Two Monado capabilities that change the whole plan.** `[MEASURED]`

1. **Monado already has a VIO backend.** "Inside-out (VIO/SLAM) tracking using an improved basalt fork
   (`gitlab.freedesktop.org/mateosss/basalt`) with all supported stereo or more cameras such as Windows
   Mixed Reality, Oculus Rift S, Valve Index." Changelog: `t/slam: Add Basalt as a possible external SLAM
   system` (!941); "Introduce visual-inertial tracking interface header … remove `XRT_HAVE_BASALT` and
   `XRT_HAVE_KIMERA` from CMake" (!2058); `d/twrap: Correct axis assignments for poses provided by basalt
   VIO/SLAM, so they match the OpenXR axis definition` (!2228). The WMR driver does 6DoF through Basalt and
   "Send calibration automatically to SLAM tracker … out of the box without user intervention" (!1334).
   The interface header is `xrt/xrt_tracking.h`; `d/wmr/wmr_camera.c` pushes SLAM frames through Monado's
   frame pipeline (`u_sink`, `u_frame`) exactly as our `meta2` driver would.
   `[INFERRED]` **We may not need to write a VIO at all.** Our job could be: deliver stereo frames + IMU +
   calibration into Monado's frame/tracking pipeline, and let Monado's Basalt fork produce the pose. That
   makes §21.5's "reuse-first" recommendation much cheaper than it looked.
2. **Monado already has an out-of-process device path.** `src/xrt/drivers/remote/` (`d/remote`), wire
   protocol header `mndrmt3` (`r_interface.h:70`), connection by address + port
   (`r_remote_connection_init(rc, addr, port)`). `r_hmd.c` implements a real HMD: `device_type =
   XRT_DEVICE_TYPE_HMD`, `name = XRT_DEVICE_GENERIC_HMD`, orientation **and** position tracking,
   `get_view_poses`, `view_count` 1 or 2 built with `u_device_setup_split_side_by_side` — **two views
   side-by-side in one panel, which is exactly our geometry** — with display geometry supplied by the
   caller (`r_hub_create(..., view_count, w_pixels, h_pixels, w_meters, h_meters, ...)`).
   `[MEASURED]` What the protocol carries: per-view FOV, per-view pose, head-centre pose, two controllers.
   What it does **not** carry: camera frames, display refresh control, swapchains. Distortion is explicitly
   none (`u_distortion_mesh_set_none`), and FOV is hardcoded (85° per view for two views, 120° for one).

**The alternatives, ranked.**

| # | Option | What it buys us | Cost / risk |
|---|---|---|---|
| **A′** | **Remote device into Monado** (`d/remote`, `mndrmt3`): *we* run VIO (Basalt, BSD-3) in our own process and stream poses to `monado-service`. | No Monado fork, no patching internals, no rebase tax on the device side. Works with the runtime as shipped, and on Windows it sidesteps the missing USB headset driver entirely — the device becomes a TCP client in our own process. Cheapest path to a live OpenXR session. | `[MEASURED]` `r_hmd` has no refresh control, no distortion mesh, hardcoded FOV — so the curved-mirror projection cannot be expressed through it today. Pose-only. |
| **A** | **In-tree Monado driver** (`xrt_device` + auto prober) feeding Monado's own Basalt VIO. | The "real" integration: cameras, IMU, calibration, display geometry, distortion all expressible. The only route where Monado does the tracking. | `[MEASURED]` On Windows this is the option that collides head-on with "no actual headset drivers yet … some USB stuff needs porting". On Linux it is straightforward. Monado warns XRT interfaces are not a stable external API → upstream or rebase forever. |
| **B** | **Skip OpenXR for the display role.** Our own app renders straight to `DISPLAY\MVNEA60` as a borderless-fullscreen D3D11/Vulkan swapchain at 72 Hz; OpenXR is used only for tracking consumers. | Available **now**, on the machine the headset is already plugged into, with no runtime at all. Monado's own direct-mode doc confirms HMD panels "present themselves as a conventional monitor", and names our exact case: "Some HMD displays are **portrait mode** — either the application would need to rotate its rendering, or the monitor would need to be configured as a rotated monitor." Monado itself falls back to extended mode (`XRT_COMPOSITOR_FORCE_XCB=1`, `XRT_COMPOSITOR_XCB_FULLSCREEN=1`), with the caveat "Monado does not ensure displaying the compositor on the correct display." | `[INFERRED]` Extended mode costs latency versus direct mode; acceptable for a dev/debug viewer, not for a final see-through product. Third-party OpenXR apps would not target the headset. |
| **C** | **Split the roles across machines.** `mndrmt3` connects by address + port, so the pose producer and the runtime can be different hosts: device on Windows (where it is plugged in) → poses → Monado on the Linux box → display on the Linux box. | Uses Monado where it is finished, and the device where it physically is. | `[INFERRED]` Requires the headset's HDMI to move to the Linux box, and adds a network hop into the pose path. |
| **D** | **Monado inside WSL2, device passed through.** `[MEASURED]` Microsoft: `usbipd attach --wsl`, WSL kernel ≥ 5.10.60.1; "As long as the device is attached to WSL, it cannot be used by Windows." | A Linux Monado on the Windows machine, no dual boot. | `[UNKNOWN]` whether usbip carries 43 MB/s mono (or 58–85 MB/s RGB) with the control-write cadence our paced-async sustain needs — that is a measurement, not a guess. Presentation would go through WSLg. Experimental fallback, not a plan. |
| **E** | **SteamVR as the Windows runtime.** `[MEASURED]` Valve's OpenVR Driver API is the supported way for third-party devices ("the OpenVR driver API, your devices will be supported in SteamVR games"); Monado also ships the reverse bridge (`monado.freedesktop.org/steamvr.html`) where "the SteamVR compositor and its direct mode implementation is used". | The mature Windows display/direct-mode path — someone else already solved presentation. | `[INFERRED]` Proprietary, requires Steam, and a custom-HMD OpenVR driver is a larger contract than an OpenXR device. Not the default. |
| **F** | **Our own minimal OpenXR runtime** (Route B in §21.4). | Full ownership of presentation and the curved-mirror projection. | `[INFERRED]` By far the most work; justified only if A/A′/B all fail to give acceptable results. |

`[MEASURED]` **A precedent worth stealing:** Monado's support table already lists "Direct-Tek WVR2 /
VR-Tek Windows VR Glasses with the **2560x1440** resolution supported through OpenHMD" — a single-panel
2560 × 1440 binocular HMD. Our panel geometry is not exotic to Monado, and
`u_device_setup_split_side_by_side` is the helper that already implements it.

`[INFERRED]` **Recommended shape given all of the above:** build the tracking pipeline as a standalone
process from day one (it has to exist regardless), speak `mndrmt3` into Monado on Linux for the first
live OpenXR session (A′), and render our own see-through content directly to the panel (B) while the
in-tree Monado driver (A) is developed on Linux. That ordering means Windows never blocks us: the only
Windows-specific work left is presentation, and B already covers it.

`[MEASURED]` Monado source is now on the Linux box at `~/work/monado-src` (sparse: `doc`,
`src/xrt/drivers/remote`, `src/xrt/drivers/wmr`) for reference.

### 21.4b The Windows question, answered from Monado's build system (2026-10-28)

The user's requirements are now **fixed constraints**, not preferences:

1. Any game engine or software that supports OpenXR should be able to use the headset. Existing AR
   OpenXR software working is a *maybe*, not a priority.
2. Tracking may run in a separate process.
3. Rendering must actually work — the headset must show a picture.
4. **Linux and Windows are both targets.** Not Linux-first-with-Windows-later: "lots of people and
   software only use windows".

Against those constraints, four facts read directly out of Monado's tree.

**1. The remote driver is explicitly a Windows-supported driver.** `[MEASURED]`
`CMakeLists.txt:375`:

```cmake
option_with_deps(XRT_BUILD_DRIVER_REMOTE "Enable remote debugging driver"
                 DEPENDS "XRT_HAVE_LINUX OR ANDROID OR WIN32")
```

`src/xrt/drivers/CMakeLists.txt:279-292` builds `drv_remote` and, under `if(WIN32)`, links `ws2_32`
(Windows Sockets). `r_interface.h` includes `<winsock2.h>` under `XRT_OS_WINDOWS` with an explicit
comment that winsock2 must precede `windows.h`, and `r_hub.c` carries 11 `XRT_OS_WINDOWS` branches
wrapping `SOCKET`/`closesocket` versus `int`/`close`. This is cross-platform code that Monado
intends to build on Windows.

`[INFERRED]` **This removes Monado's two named Windows blockers from our path.** `doc/winbuild.md`
blocks Windows on "no actual headset drivers yet … some USB stuff needs porting" and "direct mode on
Windows is more complicated". `d/remote` needs **no USB** (poses arrive over TCP) and **no direct
mode** (our panel is an ordinary HDMI monitor). Neither blocker applies to the A′ shape.

**2. The Windows build-and-run path is documented end to end.** `[MEASURED]` `doc/winbuild.md`:
vcpkg manifest mode + Visual Studio 2022 + Vulkan SDK + Ninja; `-DXRT_FEATURE_SERVICE=ON` for the
out-of-process build; start `monado-service.exe`; register the runtime by pointing
`XR_RUNTIME_JSON` at the generated `openxr_monado-dev.json` ("Proper install of a runtime in Windows
involves registry modifications"); then `hello_xr.exe -G Vulkan`. `[INFERRED]` An OpenXR client on
Windows can run against Monado today, from a binary tree we build ourselves — no upstream packaging
is required for us to ship it.

**3. The wire contract is one fixed struct — small enough to implement directly.** `[MEASURED]`
`r_interface.h`: `r_remote_data { uint64_t header /* "mndrmt3\0" */; r_head_data head;
r_remote_controller_data left, right; }`. `r_head_data` = 2 × {`xrt_fov`, `xrt_pose`, pad} (48 B each)
+ `center` pose + `per_view_data_valid`. Device geometry is supplied by the caller:
`r_create_devices(port, view_count, w_pixels, h_pixels, w_meters, h_meters, &out_xsysd)`. So our
client sends head-centre pose, per-eye poses, per-eye FOV, and panel pixels/metres. Controller fields
exist in the struct; we have no controllers, so they stay `active = false`.

**4. Correction to §21.4a's FOV claim.** `[MEASURED]` FOV is **supplied by the client** for view
poses — `r_hmd.c:107` returns `latest.head.views[i].fov` from the wire. Only `hmd_get_info` hardcodes
it (`r_hmd.c:157-163`: 120° for one view, 85° per view for two). So our measured FOV reaches
`get_view_poses`; the FOV reported in `XrViewConfigurationView` is not client-controlled. Distortion
remains `u_distortion_mesh_set_none` (`r_hmd.c:175`).

**5. Monado's tracking interface fits our sensor set.** `[MEASURED]`
`src/xrt/include/xrt/xrt_tracking.h`: `XRT_TRACKING_MAX_CAMS 8`, `XRT_TRACKING_MAX_IMUS 3`. We have
2 mono + 1 RGB and 2 IMUs — inside both limits.

**6. `libmonado` is not an embedding API.** `[MEASURED]` `doc/packaging-notes.md`: "`libmonado`, which
_does_ have a public API as a management interface for software serving as a Monado front-end or
dashboard". `[INFERRED]` "Ship one binary that is a runtime" means building Monado **in-process**
(`XRT_FEATURE_SERVICE=OFF`) with our driver linked in — not calling `libmonado`.

**7. Passthrough exists in Monado's OpenXR surface.** `[MEASURED]` Changelog: "OpenXR: Implement
extension 'XR_FB_passthrough'", plus "Add interface for XR_FB_passthrough in Ipc communication" and
"…in client side"; source files `oxr/oxr_passthrough.c`, `oxr/oxr_api_passthrough.c`. `[INFERRED]`
Third-party AR apps that want a camera feed would use it, but it is fed by a driver that produces
passthrough frames — i.e. option **A**, not A′. `[UNKNOWN]` whether Monado will expose passthrough to
clients for a device that has no native passthrough system.

**What works on each OS, as of today.**

| Capability | Linux | Windows | Evidence |
|---|---|---|---|
| `meta2lib` device access at nominal rates | proven | proven | our own runs on both |
| Monado serving OpenXR clients | yes | yes, from our own build | `doc/winbuild.md` |
| Pose-only HMD device via `d/remote` | yes | **yes, explicitly enabled** | `CMakeLists.txt:375`, `ws2_32` link |
| In-tree driver reading our USB device | straightforward | our work, not a Monado blocker — `meta2lib` already works on Windows | `[INFERRED]` |
| Monado's Basalt VIO fed by our frames | needs the in-tree driver | same | `[INFERRED]` |
| Curved-mirror distortion through `d/remote` | no (`set_none`) | no | `r_hmd.c:175` |
| Third-party AR passthrough | needs the in-tree driver | needs the in-tree driver | `XR_FB_passthrough` |

`[INFERRED]` **Consequence: A′ is the cross-platform spine, and it is cheap because tracking is a
separate process.** Since the pose producer is out-of-process, the OpenXR device provider never
touches USB — it is a TCP client with identical code on both operating systems. Device access stays
in `meta2d`, already proven on both. Presentation works because `d/remote` yields a 2-view
side-by-side HMD on a 1440 × 2560 panel, which Monado composites as an ordinary window on both OSes.
What A′ cannot express: the visor's projection (no distortion hook) and passthrough for third-party
apps.

`[INFERRED]` **Two-tier plan, which is what "Linux and Windows both" actually implies.**
- **Tier 1 — both OSes, no Monado fork:** `meta2d` + our VIO + a `mndrmt3` client. Any OpenXR app gets
  a tracked, 2-view HMD on the headset panel, on Linux and on Windows. This satisfies constraints 1,
  2, 3 and 4 with the least new code.
- **Tier 2 — the AR product:** an in-tree Monado driver that feeds Monado's Basalt and supplies
  distortion + passthrough. Developed on Linux, ported to Windows second. This is the only tier that
  can express the curved mirror.
- **Route B — our own minimal OpenXR runtime** that PC apps connect to. Full control, much larger
  surface (session lifecycle, spaces, swapchains, conformance). `[INFERRED]` Only worth it if the HMD
  role turns out to need display behaviour no existing runtime offers — which is exactly the question
  Phase 7's first bullet answers.

`[INFERRED]` Recommendation: **Route A**, because it converts OpenXR from a research risk into an
integration task, and because a Monado provider is testable with existing OpenXR clients.

**What OpenXR additionally demands that we do not yet have:**
- Pose **prediction** (`XrSpaceVelocity`, an answer for a future `predictedDisplayTime`) → needs the
  device↔host clock bridge (§21.2 item 4) and a velocity estimate.
- A **stable space origin** with a defined convention (§21.6).
- A **bounded latency** claim (`XrFrameTiming`) → needs the latency measurement (§21.2 item 4).
- Honest degradation: `XR_TRACKING_LOST` / `XR_TRACKING_PAUSED` semantics when VIO loses features.

---

## 21.5 Reuse an existing VIO, or build ours

`[INFERRED]` **Do both, in that order, and do not debate it before Phase 4 numbers exist.**

**Step 1 — reuse as a measurement instrument.** Feed a known-good open-source VIO our own frames and
see what accuracy this rig can actually produce. This answers "is the mono pair + IMU good enough
for 6-DoF at all?" without spending months on our own estimator. Candidates, ranked by fit against
our *measured* rig:

| Candidate | Fit against our measured facts | Concern |
|---|---|---|
| **Basalt** | Supports Kannala-Brandt fisheye natively (our model is KB4), stereo-inertial, and ships offline calibration tooling including camera-IMU extrinsics — which is exactly §21.2 item 1. | **License now verified: BSD 3-Clause** (`[MEASURED]` read from `raw.githubusercontent.com/VladyslavUsenko/basalt/master/LICENSE`, "BSD 3-Clause License Copyright (c) 2019, Vladyslav Usenko and Nikolaus Demmel"). This **corrects** my draft's "believed GPLv3". No copyleft obstacle. Remaining concern: irregular timestamps. |
| **OpenVINS** | Stereo-inertial, fisheye support, actively maintained, good docs, designed around irregular sensor rates. | Camera model is the equidistant/division model; our KB4 must be converted or refitted. **License now verified: GPLv3** (`[MEASURED]` read from `raw.githubusercontent.com/rpng/open_vins/master/LICENSE`). |
| **ORB-SLAM3** (stereo-inertial) | Its fisheye branch supports Kannala-Brandt. Needs a vocabulary; `data/vslam_voc.bin` is **not in our possession** (named in the graph, no copy exists in `meta2-docs` or `meta2lib` — verified by `find`, 2026-10-28). | **License now verified: GPLv3** (`[MEASURED]` read from `raw.githubusercontent.com/UZ-SLAMLab/ORB_SLAM3/master/LICENSE`). Heavier. Vocabulary must come from its own distribution. `[CORRECTED]` I previously justified this candidate as "closest to the vendor's own stack". **That is not a reason** — see §21.5a. Its real merits are KB4 support and maturity; its real costs are GPL and weight. |

`[INFERRED]` A decisive practical point: **modern VIO backends can estimate the camera-IMU extrinsic
online.** So Phase 4 can *start before* Phase 3 finishes and *produce* the missing calibration as a
by-product. That is the reason to sequence reuse before in-house work.

### 21.5a Why the vendor SDK appears in this plan at all — and what it is *not*

`[OPERATOR-REPORTED]` The operator's position, 2026-10-28: **"this is a custom implementation to make it
as good as possible. It will not be faithful to the original SDK."** That is the correct posture, and
nothing in this plan may be justified by "the vendor does it that way."

So what is the decoded vendor graph actually for here? Four things, and only four:

1. **A feasibility proof about the hardware, not a design to copy.** `[MEASURED]` The vendor's tracking
   consumed exactly `mono0_OUT`, `mono1_OUT` and `imu0` — nothing else — and produced live pose on a
   physical PC (559 distinct translation triples, `tracking_status (1,3)` in 559 of 637 polls). That is
   the strongest evidence in the corpus that *our* input set is sufficient for 6-DoF on this rig. It says
   nothing about whether their estimator is good, and beating it is the goal.
2. **A free benchmark.** `[MEASURED]` A working implementation of the exact problem is installed on the
   same machine. Running §21.8's protocol through both pipelines is a cross-check that costs nothing, and
   it turns "our tracking works" into "our tracking is better by this much". Being *measured against* the
   vendor is the opposite of being faithful to it.
3. **Facts about frames and conventions.** `[MEASURED]` `target_frame=mono_right` tells us which frame
   their numbers live in — needed only for comparison or for reusing their calibration.
4. **Calibration we may be able to read instead of reinvent.** `[MEASURED]` `CompositorBlock` consumes
   pose plus the sensors-DB rig, which is where `g_cad_display` lives. If the vendor's alignment setup
   stores a pose, `meta2lib` already reads that file. Reusing a measured value is not faithfulness; it is
   not redoing work that was already done.

What must **not** happen is choosing an architecture because the vendor chose one. This plan already
departs from the vendor on three points, and none of them needs justifying:

- The vendor fuses **one** IMU (`imu0` only; `imu1` goes only to `DeviceStatusBlock`). `[MEASURED]` We
  have two measured chips with a measured axis map and measured scales. Using both is an improvement to
  test, not a deviation to defend.
- The vendor's pose lives in the **`mono_right`** frame. `[INFERRED]` An OpenXR runtime wants a head/body
  frame; producing pose there is better for our purpose.
- The vendor's depth output is a fixed ~2.45 m shell with `pc_nz = 0` in every healthy poll.
  `[MEASURED]` There is nothing in it worth reproducing.

`[RULE]` Whenever this document cites the vendor, it is citing **evidence about the device** or **a
benchmark to beat**. Any sentence that uses the SDK as a *reason to build something a particular way* is
a defect in this document and should be deleted. That is a standing review criterion for future edits.

**Step 2 — build ours only if Step 1 shows the rig is capable but the third-party estimator fights
our quirks.** Our quirks are precisely the things generic VIOs assume away: a production-coupled
device clock that is uptime rather than wall time, host-caused gaps invisible in device time, a
host-loop-dependent IMU rate that silently drops to ~23 Hz if the sustain shape is wrong, torn frames
that must be rejected rather than spliced, and a lens model
that fails at the corners of its own frame. An in-house pipeline would be: keyframe stereo VO on the
mono pair (KB4, known extrinsics, frame-locked) + IMU preintegration + EKF fusion + ORB relocalisation
with our own vocabulary. That is a multi-month project and should not be started on faith.

**A scope decision already on record that this plan must either honour or explicitly overturn.**
`[MEASURED]` `docs/14` §7: "Add to `meta2lib` only what is protocol-shaped: frame timestamps, a
documented arm-file format, and a stable capture API. **SLAM, rectification and rendering stay out of
the library.**" So the corpus has already decided that tracking does not live in `meta2lib`. This plan
keeps that boundary: `meta2lib` gains a **capture/serialization API for VIO input** (Phase 4's
`meta2_vio` format), and tracking lives in a separate layer — the viewer, a `meta2_track` library, or a
third-party VIO. That is decision 3 in §21.12, and it should be confirmed rather than assumed.

---

## 21.6 Frame conventions — a deliverable, not an afterthought

Four different frames are already in play and they do not agree:

1. **Rig world frame** `[MEASURED]`: `depth` is the reference (identity `T_wc`), its optical axis is
   world +z; mono cameras sit ±41.65° off it; `g_cad_display` forward is `(0, +0.922, +0.388)`
   (`docs/19` §19.5).
2. **Vendor SLAM frames** `[MEASURED]`: `VSlamBlock` and `LooseFusionBlock` both declare
   `target_frame=mono_right`, `source_frame=world` (`artifacts/sdk_graph_schema.txt` lines 294–317,
   69–110). The vendor's pose is therefore expressed **in the `mono_right` camera frame**, not in a
   body frame — there is no body frame anywhere in the vendor graph.
3. **Headset body frame** `[MEASURED]`: the one `docs/18` §18.2 defines (+X forward through the
   screens, +Y wearer's left, +Z crown) and `meta2_imu_to_headset()` implements.
4. **OpenXR world frame**: right-handed, +X right, +Y up, −Z forward, with a space origin
   (`XR_TS_LOCAL`/`XR_TS_STAGE`/unbounded).

`[INFERRED]` Two consequences worth stating before anyone writes code:
- **Comparing our pose to the vendor's is only clean if both are expressed in `mono_right`.**
  `mono_right → rig world` is measured (`T_wc`), so that comparison is available. A comparison in a
  *body* frame is not, because the body↔rig-world link is precisely the camera-to-IMU extrinsic that
  §21.2 item 1 says we do not have.
- **The vendor fuses one IMU, not two.** `[MEASURED]` `LooseFusionBlock`'s wired inputs are
  `DeviceStreamBlock.imu0_acc_OUT → acceleration_IN` and `imu0_gyro_OUT → gyro_IN` plus
  `VSlamBlock.pose_OUT → pose_IN`; `imu1_*` goes only to `DeviceStatusBlock`
  (`artifacts/sdk_graph_schema.txt` lines 351–380, 980–1000). A two-IMU fusion is something we *could*
  do that the vendor does not, and it is worth a measurement rather than an assumption.

`[INFERRED]` Deliverable: a **frame tree document** with one named transform per edge, each one
either measured or explicitly declared arbitrary (the world↔body yaw at session start *must* be
arbitrary — that is the origin, not a bug). Without this, every accuracy number in this project is
ambiguous, and it is the kind of thing that produces "the pose looks wrong by 90°" debugging.

---

## 21.7 Sequenced phases, each with an exit test

**Phase 0 — Decide (no device work, no code).**
Four decisions, recorded in this document: (a) OpenXR role = TRACKER first; (b) Route A vs B;
(c) reuse-first VIO strategy; (d) license posture for a GPL VIO inside our stack.
*Exit:* this doc annotated with the decisions and their reasons.

**Phase 1 — 3-DoF attitude from IMU only.** `[INFERRED]` Achievable today with zero new device
capability: measured scales, measured axis map, measured biases, per-sample device timestamps.
Build an AHRS (complementary or Madgwick/MSF) that outputs orientation in the headset body frame.
This is **not** 6-DoF and must never be described as such; it is the cheapest way to exercise the
entire pose path — time base, gap detection, units, axis map — before any visual work.
*Exit tests:* a coached 360° turn integrates to 360° ± the already-measured 4.5% spread
(`docs/17` §17.3); a protractor tilt agrees within the 6–11° gravity floor (`docs/15` §3); a
published **drift rate in deg/min** and a published noise floor.

**Phase 2 — Pin the IMU time base, noise, and the clock bridge.** (device work, small)
- **Adopt the paced-async sustain as the tracking session's sustain shape and prove the IMU rate holds
  under tracking load.** The bimodality question is closed (`docs/10` §10.5, resolved 2026-10-27): the
  rate follows the host's write cadence, and only "submask never deasserted, ~8 writes in flight"
  reaches the device's free-run ~400 records/s. A tracking front end that uses a synchronous toggle
  silently runs the IMUs at ~23 Hz instead of ~200 Hz. The test is whether that rate survives *while
  the mono pair is also being drained at 60 fps* — that combination has not been measured.
- Allan variance on both chips at rest → noise density, bias instability, correlation time.
- Measure absolute latency: an event with a known host-side instant timestamped on both sides.
  `[INFERRED]` The headset's own HDMI display is a host-controlled light source, **but it cannot
  measure itself**: `[MEASURED]` every camera on this unit looks *forward, away from the wearer* —
  mono optical axes `(+0.663, +0.020, +0.748)` and `(−0.666, +0.011, +0.746)`, RGB `(+0.007, +0.001,
  +1.000)` in the rig world frame where `+z` is forward (`docs/19` §19.5) — while the screen faces the
  wearer. The headset's cameras see the back of its own display. So the flash test needs an **external**
  time-known observer: a photodiode on the screen, or a second camera whose own clock is tied to the
  host. `[MEASURED]` The display CAD frame sits 3.9 cm above and 5.2 cm forward of the depth-camera
  origin, with forward `(0, +0.922, +0.388)` and 67.16° off identity — the only display geometry the
  corpus has, and it is a CAD frame, not a screen normal.
- Measure the per-endpoint trailer offsets that are currently `[INFERRED]` (1.48e9 ticks vs 179,005
  ticks in two sessions).
*Exit:* a sample rate with uncertainty, an Allan plot, a latency number, a device↔host clock offset
with uncertainty. **These four numbers are what make OpenXR pose prediction possible at all.**

**Phase 3 — Camera-to-IMU extrinsics (the real blocker).** (device work, medium)
Optical route: a known target seen by the mono pair while the IMU is coached, both streams on the
device clock, written to a capture file a calibrator can read. Two options: feed Kalibr (multi-CAM-IMU,
fisheye-capable) from a `meta2` capture mode, or solve it in-house. `[INFERRED]` Also run the online
extrinsic estimate from Phase 4 and cross-check the two.
*Exit:* two independent estimates of the rotation agreeing **better than the 6–11° gravity floor**
(`docs/15` §3 — that floor is the bar to beat, and it is the reason the gravity route was closed
rather than retried), and a translation consistent with a tape measure.

**Phase 4 — First 6-DoF: feed an existing VIO.** (mostly no device work)
A `meta2_vio` capture format (mono pair + IMU + device timestamps + rig XML) and a thin adapter per
candidate in §21.5. Run the §21.8 protocol against each.
*Exit:* a measured translation error and rotation error per candidate, on the same protocol, plus a
decision: keep it, or build ours.

**Phase 5 — In-house VIO, only if Phase 4 justifies it.** Keyframe stereo VO + IMU preintegration +
EKF + relocalisation with our own vocabulary.
*Exit:* beats the Phase 4 best on our own protocol, or the third-party one is adopted.

**Phase 6 — OpenXR surface (tracker role).** Provider plugin or minimal runtime; the frame tree from
§21.6; `XrSpace` with velocity; honest `TRACKING_LOST` reporting.
*Exit:* an OpenXR client enumerates the device and receives live pose that matches the §21.8 protocol
to within the Phase 4 error budget.

**Phase 7 — See-through rendering on the curved-mirror visor.** `[OPERATOR-REPORTED]` + `[MEASURED]`
(Facts B.1 and B.2) make this possible; Phases 1–6 make it worth doing.

Panel facts are **settled**: one panel, `DISPLAY\MVNEA60`, **2560 × 1440 native** (Windows rotates it to
portrait so it fills the visor), 8-bit RGB SDR, no VRR, driven by the host's Intel Iris Xe, served
binocularly through **curved mirrors** at 1280 × 1440 per eye. `[COMPUTED HERE]` **3.69 Mpix/frame**,
which matches the external spec's "3.69 million pixels overall" exactly. At the measured 72 Hz that is a
**13.9 ms** frame period; at the 60 Hz the external spec claims it is **16.7 ms**. `[MEASURED conflict]`
The two refresh figures disagree and must be resolved before a renderer is paced — `[UNKNOWN]` which is
real. No VRR either way, so the runtime must pace to a fixed rate.

What is left, in order:

- **The visor projection — the only remaining display unknown, and it is not just a pose.**
  `[MEASURED]` No lens, so no lens-distortion model to fit; `[MEASURED]` external spec says the optics are
  **curved mirrors**; `[MEASURED]` the rig has a `g_cad_display` pose and **no combiner entry at all**.
  `[CORRECTED]` My earlier "start from a pose model, only add terms if forced" was too optimistic — a
  curved combiner is a distortion element, and a flat-panel-to-virtual-image mapping through it will not
  be a pure rotation. The honest plan is: measure it, then pick the simplest model the measurement
  supports, rather than assuming the simplest model.
- **An alignment procedure we can run ourselves**, mirroring the vendor's: render a known pattern, have
  the operator report where it lands against a physical edge, solve the transform. `[INFERRED]` This is
  the cheapest display calibration available and needs no fixture beyond a ruler and a wall.
- **Display pose in the head frame** — needs the Phase 3 camera-to-IMU extrinsic; today `g_cad_display`
  is expressed only in the *rig* frame.
- **Motion-to-photon latency**, measured with the external observer from Phase 2 (the headset cannot see
  its own visor — every camera faces forward).

*Exit:* an OpenXR client's rendered content appears correctly aligned on the visor, with a published
motion-to-photon number and a published description of how the alignment was obtained. If the alignment
turns out to need more than a pose — i.e. the visor has real distortion — say so in the docs rather than
forcing it into a pose model.

**Phase 8 — Optional research branches, explicitly not on the critical path.**
- ToF resume: the decisive experiment is already designed and unbuilt — the v10 proxy run (IR-84) on
  the physical PC, which must print `WIRE HOOK OK` and be read from its `DEVIO` blocks, to recover the
  five control OUT transfers whose data stage `usbmon` never captured (4,498 bytes, including the
  2,336-byte `0x920` transfer at the vendor's `WriteI2C(reg=0xb800)`) (`docs/14` §4, §7).
- ~~Display data path probe~~ — **withdrawn.** There is no display data path to find; the display is
  HDMI from the host (`docs/01` §1.7, operator-confirmed 2026-10-16 and again 2026-10-28). Phase 7
  replaces it.
- RGB as the appearance/relocalisation stream (`docs/14` §7 item 1).
- Buttons on the wire (needed for any OpenXR input subaction).

---

## 21.8 Ground-truth protocol (the corpus has never validated a pose against anything)

`[MEASURED]` The vendor pose output has **never** been validated against ground truth in this repo —
only cross-checked by pose-log audit rules (`docs/12` §12.28, and the skill's audit rule). Every
accuracy claim in this plan is meaningless until a reference exists. Cheap, sufficient rig:

- **Translation:** a straight line marked on the floor at 1.0 m and 2.0 m; walk the marked distance
  holding the headset still relative to a cart or a fixed mount. Report measured vs tracked.
- **Rotation:** a turntable or a taped floor compass for 90°/180°/360° about the crown axis; the
  coached-turn method already produced a 4.5% spread (`docs/17` §17.3) — reuse it.
- **Cross-check against the vendor SDK:** run the vendor pipeline and ours **sequentially** (the
  device can only be opened by one client) against the same protocol, and compare. `[INFERRED]` This
  is the highest-value validation available: a working reference implementation of the exact problem
  is installed on the same machine.
- Report every number as *measured error against the protocol*, never as "tracking works".

---

## 21.9 Device runs the user must perform (the agent never probes the headset)

Standing constraint, unchanged: `[MEASURED]` "Never probe the user's physical devices directly; for
the headset, tell the user what to run and wait for results" (`docs/14` §6). The user's own protocol
also stands: leave the headset plugged in for 20 minutes before a run.

Runs this plan will need, in order:
1. **Tracking-mode capture** — arm with `enable_mask 0x56` = `Mono0(2) | Mono1(4) | Multiplexor(16) |
   STD(64)`, i.e. mono pair + mux + STD with ToF and RGB not enabled (`docs/10` §10.1 bit table:
   `Mono0 = 2, Mono1 = 4, ToF = 8, Multiplexor = 16, RGB = 32, STD = 64`), mux submask **`0x1b`** — the
   value every measured run in `docs/10`, `docs/13` and `docs/20` used; a minimal `0x03` (IMU0|IMU1 only)
   has **never been tested** and should not be assumed. Warm with `0x7e` then sustain, readers pending on
   all four endpoints (`docs/10` §10.2). Deliver: mono frames + IMU records + device timestamps in one
   file.
   `[MEASURED]` Caveat that changes the intent: disabling RGB in the mask does **not** silence EP `0x83`.
   `docs/10` §10.1 measured `0x66` (mono + STD) still delivering 52.3 MB/s on EP `0x83`, and flags as
   `[UNKNOWN]` why `0x60` (RGB only) is slower on `0x83` than `0x66` (mono only) is. So `0x56` is a
   *statement of intent*, not a bandwidth switch, and the reader set must still drain everything.
2. **IMU rate under tracking load** — the bimodality question is closed (`docs/10` §10.5); what is
   unmeasured is the paced-async sustain (`muxkeep`, `muxasync=8`, submask never deasserted) running
   **while the mono pair is drained at 60 fps**. Report the IMU record rate in that configuration.
3. **IMU rest capture** — several minutes perfectly still, for Allan variance.
4. **Latency capture** — a flashing target with host-side timestamps, observed by an observer that is
   *not* the headset's own cameras (they face away from its screen; see Phase 2).
5. **Extrinsic calibration capture** — target + coached IMU.
6. **Ground-truth protocol runs** — §21.8, ours and the vendor SDK's, sequentially.
7. ~~Display identification~~ — **DONE 2026-10-28, host-side only.** Results in Fact B.1: one panel
   (`DISPLAY\MVNEA60`, one EDID source mode), 1440 × 2560 @ 72 Hz, 8-bit RGB SDR, no VRR, Intel Iris Xe,
   no lenses, image reflected onto a visor. **Orientation now answered:** portrait is a deliberate Windows
   setting so the image fills the panel, so the panel is 2560 × 1440 native. One cheap follow-up remains:
   **the refresh conflict.** EDID/Windows report 72 Hz, the external spec says 60 Hz. A fixed-pattern
   frame-count run on the panel settles which one a renderer should pace to. `[UNKNOWN]`
8. **Vendor alignment observation** — host-side, no device probing. Run the Meta SDK's display alignment
   setup and record what it actually changes: a file, a registry value, a rig rewrite, or nothing
   observable. That tells us whether the alignment is a stored pose we can read with `meta2lib` or
   something else entirely (Fact B.1).

---

## 21.10 Risk register

| Risk | Severity | Mitigation |
|---|---|---|
| Camera-to-IMU extrinsics stay out of reach (6–11° floor is the size of the thing we're measuring) | High | Online extrinsic estimation inside the VIO (Phase 4 before Phase 3 closes); optical route with a proper target. |
| IMU rate silently drops to ~23 Hz per chip under a synchronous sustain | High | Use the paced-async sustain (`docs/10` §10.5); assert the rate at acceptance and monitor it, not just throughput. |
| Host-caused gaps silently corrupt integration | High | Host-side gap detector; refuse to integrate across a gap; report gap statistics. |
| Mono frame delivery is irregular run to run (27 / 41–77 / 60 fps measured) | High | Design for whole-frames-plus-timestamps; detect missing slots as gaps; never interpolate. Re-derive the `docs/10` §10.5 accounting. |
| Mono tearing under load | Medium | Gated recipe; **reject** torn frames — the trailer is not a frame delimiter and concatenate-and-cut splices two frames together (`docs/10` §10.4). |
| EP `0x82` collapse when other endpoints are undrained | Medium | Drain readers on all four endpoints even when discarding (`docs/10` §10.2). |
| Lens model fails at the frame corners | Medium | Reject out-of-model pixels (`meta2_camera_bearing() == -1`); mask the corner caps, not a rectangular border. |
| HMD role is feasible but the **visor projection is uncalibrated** — the rig has a panel pose and no combiner | High | Phase 7: observe what the vendor's alignment setup changes host-side, then run our own ruler-and-wall alignment procedure. The optics are **curved mirrors**, so measure before choosing a model. |
| Third-party VIO license incompatible with our distribution | **Resolved 2026-10-28** | Measured from each project's own `LICENSE`: Basalt **BSD 3-Clause**, OpenVINS **GPLv3**, ORB-SLAM3 **GPLv3**. The best-fitting candidate is permissive. |
| Refresh rate: external spec says 60 Hz, EDID/Windows say **72 Hz** | **Resolved by operator 2026-10-28** | "The display does appear as 72hz on the windows settings." **Pace to 72 Hz under ideal conditions** (13.9 ms budget), but read the refresh the display actually reports at runtime rather than hardcoding it, and degrade gracefully if a mode ever lands at 60. |
| Curved combiner assumed to be a pose when it is a distortion element | High | Measure the panel→virtual-image mapping before choosing a model (Phase 7). Do not assume the simplest model that fits the words "no lenses". |
| Monado's Windows port has no headset drivers and needs USB porting | High | Build the provider on Linux first. Treat the Windows target as its own phase with its own risk, not as a rebuild of the Linux driver. |
| Out-of-tree Monado driver carries a rebase tax (Monado explicitly discourages external XRT API use) | Medium | Decide early whether to upstream `meta2` into Monado; the alternative is permanently tracking a moving internal interface. |
| Plan built on a stale corpus sentence (this document's first draft got Fact B wrong) | Process | Quote the **whole** section, not the first paragraph. `docs/01` §1.7 retracts its own sentence two paragraphs down; a grep for the sentence, not for the topic, is what missed it. |
| Blank-wall / looking-down scenes break visual tracking | Medium | Report it honestly as a property of the rig (§21.3); IMU-only fallback with degraded status. |
| Reusing vendor `vslam_voc.bin` | N/A | Not available; not needed if we use a third-party vocabulary or build our own. |

---

## 21.11 Search backend: was blocked, now working (with one caveat)

Earlier in this session `web_search` returned `success: true` with **zero results** for every query,
including the control query "OpenXR specification". That was reported rather than worked around. The
operator then asked for it to be fixed. Re-tested 2026-10-28:

- `web_search` now returns real results, and `web_extract` returns full page text with `error: null` on
  Wikipedia, Monado's docs, raw GitHub `LICENSE` files and VRcompare.
- **The caveat is honest:** two of the first six queries returned `success: true` with an empty result
  array, and the same queries rephrased returned five results each. So the backend is **intermittently**
  empty rather than reliably populated — consistent with an upstream engine in the self-hosted meta-search
  being rate-limited or blocked for some query shapes. `[UNKNOWN]` which upstream, and it is not diagnosed
  further here.
- **Attribution caveat:** this Hermes build strips the per-item `category` field from `web_search`
  results, so the SearXNG fingerprint is unavailable. Attribution to the self-hosted backend is therefore
  **not proven** by the responses themselves; it rests on the host config. `[UNKNOWN]` — and the host
  config is not reachable from this terminal backend (`~/.hermes/config.yaml` does not exist on `server3`,
  and the Docker socket is permission-denied for user `hermes`). If you want attribution proven, run
  `hermes config get web` on the gateway host.

Everything this plan previously listed as blocked by the outage is now answered with a citation:

1. **External specification** — answered, see Fact B.2 (VRcompare Meta 2 spec page, read directly).
2. **VIO candidate licenses** — answered by reading each `LICENSE` file from `raw.githubusercontent.com`:
   Basalt **BSD 3-Clause**, OpenVINS **GPLv3**, ORB-SLAM3 **GPLv3**. My draft's "Basalt believed GPLv3"
   was wrong.
3. **Monado's Windows capability** — answered, see Route A: Monado's own docs describe the Windows port as
   work-in-progress with **no headset drivers yet** and USB porting outstanding.

Everything else in this plan is grounded in the repo.

---

## 21.12 Decisions needed from the user before any work starts

1. **OpenXR role:** TRACKER-first (still recommended — pose is the part that does not exist and
   everything else depends on it), or HMD-first now that the display is measured as a single
   1440 × 2560 @ 72 Hz panel with no lenses? `[INFERRED]` The display side is now the *easier* half, so
   the sequencing argument for tracker-first got stronger, not weaker: rendering to a visor without
   validated pose produces something that visibly swims.
2. **OpenXR route — CLOSED by the operator 2026-10-28: Monado (Route A), cross-platform — Linux *and*
   Windows, both required.** `[OPERATOR-REPORTED]` "With cross platform, we want linux and windows
   support (lots of people and software only use windows)." `[MEASURED]` §21.4b revises my earlier
   reading: Monado's remote driver is explicitly enabled on Windows by its own CMake
   (`DEPENDS "XRT_HAVE_LINUX OR ANDROID OR WIN32"`, `ws2_32` link), and `doc/winbuild.md` documents a
   working `monado-service.exe` + `XR_RUNTIME_JSON` client path. Monado's two named Windows blockers —
   USB headset drivers and direct mode — do not apply to our device shape. **Windows is not a
   prerequisite; it is a same-tier target.**
2a. **Integration shape — CLOSED by the operator 2026-10-28.** `[OPERATOR-REPORTED]` "The tracking can
   be run on another process, that is fine." "Rendering is important to be doable, we want the headset
   to show a picture." That approves the two-tier shape in §21.4b: standalone tracking process, Tier 1
   over `mndrmt3` on both OSes, Tier 2 in-tree driver for distortion and passthrough.
   `[INFERRED]` One consequence worth naming: because the runtime must present on the machine that has
   the panel, and the panel is on the Windows 11 host, **Tier 1 has to be demonstrated on Windows**, not
   only on Linux.
2b. **Display pacing — CLOSED by the operator 2026-10-28: aim for 72 Hz.** `[OPERATOR-REPORTED]` "The
   display does appear as 72hz on the windows settings." `[INFERRED]` Design budget 13.9 ms/frame, but
   query the mode at runtime instead of hardcoding 72, so a 60 Hz fallback is a config change rather than
   a rewrite.
3. **VIO strategy:** reuse-first as a measurement instrument (recommended) vs in-house from day one?
4. **License posture — largely dissolved by measurement.** Basalt, the best-fitting candidate, is
   **BSD 3-Clause**, so the GPL worry that motivated this question applies only to OpenVINS and
   ORB-SLAM3. `[MEASURED]` All three licenses read from their own `LICENSE` files. The remaining question
   is only: do we want a GPL VIO in the stack at all, given a permissive option covers our camera model?
5. **Tracking host — largely dissolved by §21.4b.** The earlier framing ("device on Windows, Monado
   finished on Linux") assumed the runtime needed USB access to our device. With the pose producer
   out-of-process, the runtime needs only a local socket, so **the runtime runs on whichever machine
   has the panel** — Windows 11 today, Linux whenever the headset moves. `[INFERRED]` The remaining
   host question is only where the *tracking* process runs, and it can be the same machine as the
   runtime. Cross-machine (`mndrmt3` connects by address + port) stays available as option C, not as a
   requirement.
6. ~~Search backend~~ — **CLOSED 2026-10-28.** It works; the residual caveat (some queries return an
   empty array and succeed when rephrased) is recorded in §21.11. Nothing in this plan is blocked on it.
7. **Scope discipline:** ToF stays paused (recommended — it is not on the 6-DoF critical path), or
   resume IR-84 in parallel?
8. **Library boundary:** keep `docs/14` §7's rule that "SLAM, rectification and rendering stay out of
   the library", with tracking in a separate layer (recommended), or put tracking inside `meta2lib`
   after all?
9. **First build:** Phase 1 (IMU-only 3-DoF AHRS, no new device capability, exercises the whole pose
   path) before any visual work (recommended), or go straight at the VIO?

---

## 21.13 What the four doc-mines added, and what this plan does *not* resolve

Four parallel doc-mines ran over `meta2-docs` on 2026-10-28 (visual/SLAM, control/API, VIO data,
project state/display/identity). The findings that changed this plan:

- **Pose is host-side, and the device is told nothing while tracking.** `[MEASURED]` IR-83: seven
  minutes of full-rate streaming with **zero** device commands (`docs/12` §12.45). This is Fact A.
- **`meta_get_point_cloud` is the device's depth product, not a SLAM output** — it is
  `DeviceStreamBlock.point_cloud_OUT`, wired to Compositor / HandsDataPreprocessing /
  EnvironmentReconstruction (`docs/12` §12.19). An earlier description of it as "a fused SLAM output"
  is explicitly corrected in the corpus.
- **The vendor API gives us no pose getter we can rely on.** `[MEASURED]` `meta_get_pose` appears only
  as an audit rule in the skill, with no signature recorded anywhere; no `meta_set_*` tracking export
  exists anywhere in the corpus; `meta_get_tracking_status`'s `(1,3)` enum meaning is undocumented
  (`docs/12` §12.6). So "just read the vendor's pose" is not a plan.
- **The vendor SDK does deliver camera frames to applications** — `DataSinkBlock` ports
  `mono_left_IN`, `mono_right_IN`, `buttons_IN`, `rgb_IN` (`artifacts/sdk_application_graph.txt`).
  `[INFERRED]` That makes the vendor pipeline usable as a *reference implementation on the same
  machine*, which is what §21.8's cross-check depends on.
- **Nothing in the register map or enable masks is attributed to tracking, SLAM or mono
  exposure/strobe.** `[MEASURED]` `docs/04` "What is NOT known": "Which register enables which sensor
  stream (the central open problem)". Every attributed register is ToF-imager side. So there is no
  hidden device-side tracking knob to find.
- **What sits behind the Cypress FX3 bridge is unidentified** — headset SoC, FPGA, or the FX3's own RAM
  (`docs/01` §1.2, `docs/04`). The headset SoC is invoked in the corpus only for the buttons and a
  possible IR-emitter enable path — never for tracking. ~~and for the display~~ **corrected
  2026-10-28:** the display is not on the SoC, it is HDMI from the host (Fact B).
- **One of the four doc-mines reproduced a stale sentence, and so did I.** The mine reported the corpus
  as saying there is no display data path and the display is SoC-driven, because that is what
  `docs/01` §1.7's *first* paragraph says. The same section retracts it two paragraphs later. `[LESSON]`
  Quote a section whole before turning it into a load-bearing fact; grepping for the topic finds the
  claim, not the retraction.
- **Zero prior art in the corpus:** no occurrence of OpenXR, Monado, libsurvive or SteamVR anywhere in
  `meta2-docs` or the skill references (corpus-wide grep, 2026-10-28).

What this plan does **not** resolve, and should not be read as resolving:

1. Whether the mono pair + IMU on *this* unit actually achieves usable 6-DoF. Nothing in the corpus
   has ever validated a pose — ours or the vendor's — against ground truth. §21.8 exists because that
   gap is the largest single unknown in the project.
2. The camera-to-IMU extrinsic, and whether the 6–11° gravity floor can be beaten at all.
3. The IMU noise spectrum, and whether the ~200 Hz IMU rate actually holds while the mono pair is
   drained at 60 fps — the combination has never been measured (`docs/10` §10.5 closed *why* the rate
   varies; it did not measure it under tracking load).
4. Absolute latency, and therefore whether OpenXR pose prediction is achievable to any useful bound.
5. Whether the mono shutter is global or rolling — `docs/15` §3 says a 60 Hz target cannot decide it,
   and the pan test has no recorded real-device verdict.
6. ~~Whether the display has a host-reachable path, and how many panels~~ — **resolved 2026-10-28**
   (Fact B.1): one panel, 1440 × 2560 @ 72 Hz, no lenses, reflected onto a visor. What is still unknown
   is the thing that actually matters for rendering: **the visor's projection** — nothing in the corpus
   or the rig describes the combiner, only the panel's CAD pose — plus the panel's native orientation,
   and whether the vendor's alignment setup stores a pose we can read or does something else.
7. ~~Whether the Meta 2's published specifications agree with anything independent~~ — **checked
   2026-10-28**, see Fact B.2. The agreement is strong (single binocular panel, 3.69 Mpx overall, 720p
   front camera, PC-powered, curved-mirror optics, 6-DoF without base stations). Two things it does **not**
   settle: the **60 Hz vs 72 Hz** refresh conflict, and the fact that "1280×1440 per-eye" is VRcompare's
   interpretation of a single 2560 × 1440 panel rather than a measurement of two displays — which is
   consistent with our one-panel EDID but has not been verified on this unit.
