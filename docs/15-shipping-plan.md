# 15. Shipping plan — RGB, mono pair, IMU

Written 2026-10-25. Scope: what it takes to ship `meta2lib` around EP `0x83` (RGB), EP `0x82`
(mono pair) and EP `0x81` (mux: IMU0, IMU1, mics). ToF / EP `0x84` is excluded by user decision;
its state is in `docs/14-project-state.md` §4 and stays there.

Every number below was recomputed from saved captures and capture logs on 2026-10-25, not copied
from the earlier documents. Where the recomputation disagrees with `docs/14-project-state.md`, this
document is the corrected one and the disagreement is called out.

---

## 1. Readiness, measured

### EP 0x83 — RGB, 1280×720 YUV422

`[MEASURED]` from `re/probe3.log`: 1,146,880,000 B in 12.0 s = 95.57 MB/s, **621 frame records,
619 with a gap of exactly 1,843,232 B (99.7% complete) → 51.6 complete frames/s.**

| window | MB/s | records/s | complete frames/s | framing |
|---|---|---|---|---|
| probe3 (all endpoints streaming) | 95.57 | 51.75 | 51.58 | 99.7% |
| 12 s run | 59.05 | 31.92 | 31.75 | 99.5% |
| 10 s run | 53.21 | 28.80 | 28.60 | 99.3% |
| `cap_four` 32 s | 56.36 | 30.58 | — | not logged |

**Correction to `docs/14-project-state.md` §2:** the RGB rate is not "30 fps". 30 fps is what a
~55 MB/s window gives; the device reaches **~52 fps at 95.6 MB/s with 99.7% framing**. The rate
tracks bus load, so it is a bandwidth question, not a camera setting. `[MEASURED]`

`[CORRECTED 2026-10-25]` the 99.7% framing figure above is from `probe3` and **does not reproduce**.
Measured fresh with `examples/meta2_capture_live.c`, RGB exact-gap framing is 68.7% when only EP
`0x82`+`0x83` are drained and 13-21% when EP `0x81` or `0x84` are drained alongside it, at 41-49
MB/s. The dominant variable is how many endpoints are drained at once. See `docs/EVIDENCE.md` §40.
`probe3` itself is `[UNREPRODUCED]`, not disproved - its file is still on disk. Until that is
settled, quote RGB framing as **68.7% best case measured**, not 99.7%.

`[VERIFIED]` framing: 32-byte record + 1,843,200 B payload (1280×720×2), record-delimited, counter
u32 at record+20 advances +1 per frame. `meta2_find_frames` implements it; `burst83.bin` gives
`frames=74 monotonic=1`.

`[VERIFIED]` pixel phase: luma at odd phases, chroma at even (phase correlations 0.994 / −0.675).
`[MEASURED 2026-10-26]` chroma order is **UYVY**: phase 0 is Cb, phase 2 is Cr, settled against
full-screen red then blue inside one session (docs/05 §5.3.1) and pinned by `tests/test_decode.c`.

### EP 0x82 — mono pair, 2 × 752×480 10-bit

`[MEASURED]` `meta2_mono_check` over `cap_cold_ep82.bin` (736,280,576 B, 15.0 s per
`re/*.log`):

```
mono0 (0x44, wearer's left):  fragments=89,878  exact_frames=405  partial_gaps=164  resyncs=1
mono1 (0x55, wearer's right): fragments=89,877  exact_frames=405  partial_gaps=164  resyncs=1
framing quality: 71.2% of trailer gaps are exactly one frame   (both tags)
```

`[MEASURED]` `screen_66_ep82.bin` (745,111,552 B): fragments 90,955 / 90,956, exact frames 435 / 435,
framing 76.4% / 76.3%.

Derived, and this is the number that matters:

- data volume = fragments × 4,096 B = **34.0 frame-equivalents/s per camera** (`cap_cold`)
- usable complete frames = 405 / 15.0 s = **27.0 fps per camera**
- **79.4% of the mono data volume arrives as a clean single acquisition** (84.3% on `screen_66`)

**Correction to `docs/14-project-state.md` §2:** "36 fps each" is the *slot* rate
(`cap_four`: 1,684,602,880 B / 32 s / 721,952 B = 72.9 slots/s total = 36.5 per camera). The
**usable** rate is ~27 fps, and ~20% of frames are torn. `[MEASURED]`

**The same endpoint through `meta2_stream_start()` defaults (2026-10-26).** `[MEASURED]`
`examples/meta2_mono_bar`, 20.001 s window, gate accepted on attempt 1 (coverage 1.3804, mux clock
252.60 MHz):

```
tag 0x44: frames=1199 fragments=213,183 partial_gaps=3 resyncs=0  device frame slots=1199 delivered=100.0%
tag 0x55: frames=1199 fragments=213,184 partial_gaps=3 resyncs=0  device frame slots=1199 delivered=100.0%
dropped(mono=0 rgb=0 mux=0)
```

1,199 complete frames per camera against 1,199 device frame slots: **every frame the device produced
arrived whole**, 60.00 fps delivered against the 60.0143 fps cadence, zero bytes dropped, zero resyncs.
So the 20% tearing above describes a *non-gated* capture, not what the library's startup recipe gives.
That also settles the ordering question for this endpoint: at `queue=8` the mono assembler saw
`resyncs=0` over 426,367 fragments, so out-of-order transfer completion did not damage the mono byte
stream here, even though it demonstrably scrambled mux timestamp analysis (docs/16 §16.11).

`[VERIFIED]` fragment format: 4,096 B fragments, magic at +8, tag u16 at +20, fragment counter u16
at +28 advancing +1 per fragment per camera, 2,032 u16 samples at +32, 16-byte trailer. Full frame
= 721,920 B samples + 32 B trailer. `meta2_mono_feed` assembles exact frames; `meta2_mono_to_gray`
maps 10→8 bit (black level 42, max 1023).

**Geometry, from the vendor rig (docs/19 §19.5.1).** Each mono camera is a **182° × 120° fisheye**:
half-angle 91.2° at the horizontal frame edge, 59.8° / 59.5° vertically. The axes are **83.30° apart**,
canted **41.65° outward** each side of straight ahead, on a **0.13799 m** baseline. The fields of view
therefore overlap over **±49.6° around straight ahead** — a point dead ahead lands at `u ≈ 204` in
`mono_right` and `u ≈ 551` in `mono_left`, well inside both frames.

**What that pair is for.** A wide baseline, outward-canted, ultra-wide fisheye pair is the standard
mounting for **visual tracking over a room**: the splay covers a large workspace and 13.8 cm gives strong
parallax at distance. It is a poor near-field stereo depth rig — close content has enormous parallax and
does not correspond between the frames. Ship the tracking capability; do not promise metric depth at
arm's length.

### EP 0x81 — mux: IMU0, IMU1, microphones, `0xAA`

`[MEASURED]` 33 saved captures, all with records contiguous at exactly 256 B spacing.

`[VERIFIED]` record: magic `00 00 00 00 ab ba ed fe` at +0, tag u16 at +8, payload_len u32 at +12
(44 IMU, 176 MICS), field at +16, u64 at +20, payload at +28, trailer sentinel at +240, packet
counter u32 at +252.

`[MEASURED]` IMU block at +28 is 8 × i16: `gyro_valid, gx, gy, gz, accel_valid, ax, ay, az`.
Both valid flags are 1 in every record of every capture. At rest:

| capture | IMU0 \|a\| | IMU1 \|a\| | IMU0 gyro sd | IMU1 gyro sd |
|---|---|---|---|---|
| `cap_warm` | 17,015.5 ± 35.6 | 16,362.7 ± 72.8 | 1.5–1.9 | 1.5–2.0 |
| `e3b` | 16,994.3 ± 78.5 | 16,391.6 ± 99.7 | 2.2–2.9 | 2.2–3.2 |

`[MEASURED]` gravity magnitude ≈ 16,700 counts/g, and IMU0 / IMU1 have mirrored accel axes
(IMU0 `ay` +15,958, IMU1 `ay` −15,943) — two IMUs mounted in opposite senses. Gyro noise floor
≈ 2 counts at rest. `[MEASURED]` gyro scale 0.0613 deg/s per count (16.32 counts per deg/s),
±2000 deg/s full scale, from a coached 360° session - docs/17 §17.3. Accel scale now
`[MEASURED]`: 16,430 counts/g (IMU0) and 16,506 counts/g (IMU1), +0.3% and +0.7% off the nominal
LSB size for ±2 g, so the ±2 g range holds - docs/18 §18.5. Absolute axis map: `ay` is vertical on
both chips, `ax`/`az` at ~45° in the headset X-Y plane - docs/18 §18.2.

**Correction to `docs/14-project-state.md` §2:** "~57 records/s" is one configuration, not the
device's rate. Measured across captures with the same tag mix: 80.6 records/s (`e3a`, 8.0 s),
371 records/s (`cap_warm`, 15.0 s), 448 records/s (`probe3`, 12.0 s). The mux rate is not fixed.
`[MEASURED]`

`[MEASURED]` the packet counter at +252 advances +1 per record in 5,565 / 5,567 (`cap_warm`),
20,372 / 20,395 (`e3b`), 636 / 637 (`occl_baseline`) steps — i.e. **mostly +1, with occasional
repeats**. `meta2_mux_counters_monotonic()` returns 0 on real captures because of those repeats.

---

## 2. The blocker: there is no usable timestamp

> **SUPERSEDED 2026-10-26 — read docs/16 and docs/17 §17.4 instead.** The timestamp was found: a
> 32-byte trailer block on every endpoint, one shared time base, calibrated at 117,821,900 Hz, device
> uptime and production-coupled. What follows is the history of why the search was hard, not an open
> item.

This was the single thing that decides whether the library ships as a *capture* library or as a
*tracking front end*.

`[MEASURED]` across the 33 saved EP `0x81` captures, the u64 at +20 advances monotonically with the
packet counter, but ticks-per-record ranges **148,867 → 18,573,604 — a factor of 125**.

The only captures with a trustworthy wall-clock anchor are four independent 8.0 s windows, and they
agree tightly:

| capture | records | wall window | ts span | implied clock |
|---|---|---|---|---|
| `e3a` | 645 | 8.0 s | 96,248,561 | 12.03 MHz |
| `e3mic_tone` | 646 | 8.0 s | 96,593,145 | 12.07 MHz |
| `probe4` | 646 | 8.0 s | 96,593,238 | 12.07 MHz |
| `screen_66` | 650 | 8.0 s | 96,929,161 | 12.12 MHz |

Captures taken while EP `0x83` and `0x84` were also streaming imply a completely different rate:

| capture | records | wall window | ts span | implied clock |
|---|---|---|---|---|
| `probe3` | 5,379 | 12.0 s | 2,466,178,386 | 205.5 MHz |
| `cap_warm` | 5,568 | 15.0 s | 2,584,665,293 | 172.3 MHz |

Both cannot be a fixed-frequency clock. Either the field's rate depends on device configuration /
bus load, or the field is not wall time, or the long captures drained a device-side backlog. The
saved data cannot separate these.

**Consequences, stated plainly:**

1. `include/meta2/mux.h` currently documents the timestamp as "unit is ~1.2e8 per second". That
   constant is **not reproducible from any saved capture**, and the only wall-clock-anchored
   measurement gives 12.06 MHz — a factor of 10 lower. The header comment is wrong and must be
   corrected to `[UNKNOWN]` before anyone builds a timeline on it. `[MEASURED]`
2. `docs/13-multiplexor-records.md`'s "~120.8 MHz" is the same unverified figure.
3. **Cameras have no timestamp in the API at all.** `meta2_frame_t` exposes `offset` and `counter`
   only. `meta2_mono_cb` receives `tag, frame, bytes` only — even though the mono fragment trailer
   carries a u32 timestamp that the assembler currently discards. There is therefore no way, with
   the library as it stands, to put an RGB frame, a mono frame and an IMU sample on one time axis.
4. Without (3) and a characterised clock, VIO cannot be built on this library, and metric scale
   from stereo cannot be claimed.

---

## 3. Open items on the shipping path, ranked

| # | Item | State | Experiment that closes it | Cost |
|---|---|---|---|---|
| 1 | **Device clock semantics** (§2) | **DONE 2026-10-26.** `[MEASURED]` a 32-byte trailer timestamp on every endpoint, one shared time base, device uptime rather than wall time, production-coupled, calibrated at **117,821,900 Hz** (`META2_TICKS_PER_S`) — docs/16, docs/17 §17.4 | — | done |
| 2 | **Mono pair: exposure-locked, and what it is for** | **DONE 2026-10-26 (measured).** The old framing ("identical trailer timestamps vs weak image correlation") was a contradiction between a direct read and a test that never measured timing. `[MEASURED]` from the rig (docs/19 §19.5.1): each mono is a **182° × 120° fisheye**, axes 83.30° apart on a 0.13799 m baseline, so the pair shares a **±49.6° wedge around straight ahead** — weak correlation there is expected (worst distortion, largest viewpoint angle, biggest parallax) and says nothing about simultaneity. Frame-lock itself is `[MEASURED]`: identical trailer timestamps, two independent `PacketNum` counters advancing together. **Measured 2026-10-26, first flashing-display run** (`re/bar_seq1`: 20 s of sequence, 1,561 camera frames inside the target window per camera): both cameras track the commanded sequence at correlation **0.986 / 0.984**, residual rms 26–27 counts on a 367-count swing, and their exposure phases differ by **0.080–0.102 ms** depending on the fitting window, against a 1σ of ±0.082–0.096 ms — **0.8–1.2σ from zero, so not distinguishable from locked**. That is ≤0.6% of a 16.663 ms frame period. The absolute phase is not trustworthy (it moved from 1.8 ms to 9.9 ms when the fitting window changed); only the difference is common-mode safe. **Second run, 60 s** (`re/bar_seq2`, 3919 camera frames in the window per camera, fit correlation 0.885 / 0.884): **+0.120 ms ± 0.176**, 0.7σ from zero. Two independent runs, magnitudes 0.08–0.12 ms, both within 1.2σ of zero. Shutter model is `[OPEN]`: the seq-frame shape test on `bar_seq2` gave shape consistency 0.65 / 0.60 across 1085 straddling frames with the best-fit step position uncorrelated with sub-exposure phase (+0.005 / +0.036) — no rolling signature, but not the ≈1.0 that would affirm a global shutter. A tool bug worth recording: `fit_phase` used the FIRST display interval as the period. The page's first `requestAnimationFrame` interval was 15.70 ms against a 16.69 ms mean, and over a 60 s run that drifts the frame-index map by ~240 frames, so the alignment search cannot reach the true shift and the tool reported "no correlation" (0.046) on a capture where a direct scan finds 0.75. Use the mean interval. A pitfall the first run exposed: the capture began 11.95 s — 716 display frames — before the screen started flickering, and fitting the whole capture gave correlation 0.07 and no answer. Frames outside the target window are not weak evidence, they are noise: their brightness tracks the room. The fit now runs only inside the window `tools/bar_coach.py` serves two targets off the display's own vsync, so the timing is known without trusting any host clock. **seq** — a bright/dark random sequence, one decision per displayed frame: each camera integrates the screen over its own exposure window, so a frame straddling a bright/dark boundary comes out intermediate, and fitting each camera's brightness sequence against the commanded sequence gives that camera's exposure phase. Global, so fisheye distortion and the 83° between the cameras do not matter. **bar** — a bar jumping STEP rows per displayed frame: it does NOT give a clean cross-camera offset (each camera warps a screen row to a different image row, and that static bias is the same size as the effect sought), but it does give the **shutter model** cleanly — a rolling sensor smears a sweeping bar into a slanted band, a global sensor keeps it horizontal — and the shutter model decides how the seq result is read. The commanded sequence is reproducible from the seed on the analysis side; verified identical between the page's JS and `sequence()` over 1200 frames. `meta2lib` `examples/meta2_mono_bar` records what the cameras saw: one record per complete mono frame carrying trailer timestamp, `PacketNum`, tag, whole-frame mean, and a 480-row profile over a 64-column band centred on the direction the two cameras share. `tools/bar_offset.py` fits each camera's exposure phase against the commanded sequence, taking the frame alignment from the data rather than from a clock. `tools/bar_synthetic.py` proves that estimator can measure what it claims: 10 synthetic runs with a known offset, recovered to 0.000–0.047 ms, including 25% truncated frame records, 4× photometric noise, and a deliberately withheld clock anchor | a shutter-model run with more contrast: fill the frame with the target, dim the room, and a seq run long enough to push the 1σ below 0.1 ms | done, one sub-item open |
| 3 | **Mono / RGB intrinsics and camera-to-IMU extrinsics** | **Split 2026-10-26.** Intrinsics and camera-to-camera extrinsics: `[EXTRACTED]` — they were never hidden in a binary region, they are in the plain-text rig both copies of `calibration.bin` already carry (docs/19). Camera-to-IMU extrinsics: `[NOT IN THE FILE]` — all four vendor IMU poses are the identity, so the measured `docs/18` map is the only usable transform | Done for intrinsics (`meta2lib` `calibration.h/.c`, `tests/test_calibration`). Extrinsics need an optical run: checkerboard seen by the cameras while the IMU is coached | 1 coached session |
| 4 | **Gyro scale factor** | `[MEASURED]` | Done 2026-10-25 by coached 360° turns: 0.0613 deg/s per count, ±2000 deg/s range, plus the tick rate 117,821,900 Hz and the IMU0↔IMU1 axis map - docs/17 | done |
| 4b | **IMU axes in the headset frame** | `[MEASURED]` | Done 2026-10-25 by six gravity poses: `ay` vertical on both chips (IMU0 `+Z`, IMU1 `-Z`), `ax`/`az` ~45° in the X-Y plane, cross-checked against the gyro map to 10-18° - docs/18. `[OPEN]` the ~18° cant of `az` out of that plane: real mount cant or resting-geometry artifact, unresolved | done, one sub-item open |
| 5 | **U vs V in the YUV422 stream** | **DONE 2026-10-26.** `[MEASURED]` UYVY — phase 0 is Cb, phase 2 is Cr, settled against full-screen red then blue inside one session (docs/05 §5.3.1), pinned by `tests/test_decode.c` | — | done |
| 6 | **Mono frame tearing, 20% of frames** | **Largely closed 2026-10-26.** `[MEASURED]` the 71–76% of gaps / 79–84% of volume figure is what a *non-gated* capture gives. Through `meta2_stream_start()` defaults with the gate accepted, a 20 s run delivered **1,199 of 1,199 device frame slots per camera — 100.0%**, `resyncs=0`, `dropped=0` (§1 EP 0x82). `[OPEN]` why: the warm mask and the sustain loop are known to matter, the mechanism is not, and one 20 s run is one run | Repeat the 100% figure across several gate-accepted sessions before quoting it in the README | offline, from saved captures |
| 7 | **IMU sample rate** | `[UNKNOWN]` — mux record rate varies 80–448/s with configuration, so the IMU rate is not established | Same live capture as #1 | folded into #1 |
| 8 | **Buttons (`0x99`) never observed on the wire** | `[UNKNOWN]` | Press and hold each button while capturing `0x81` with mux bit 3 enabled | 1 coached session |
| 9 | **Microphone sample rate** | `[INFERRED]`, two conflicting figures | Tone injection at a known frequency; count zero crossings per device-timestamp interval | folded into #1 |
| 10 | **SuperSpeed is a hard gate** | `[VERIFIED]` | none — design constraint, ~160 MB/s aggregate is impossible on USB 2.0 | — |

---

## 4. Library work that needs no device and can start now

`meta2::frame` and the mono/mux parsers are pure parsing and unit-tested (`ctest` 6/6). The
following are protocol-shaped, in the library's stated scope, and independent of the open questions:

1. **Expose timestamps that already exist on the wire.** Add the trailer u32 to the mono frame
   callback (`meta2_mono_cb` gains a timestamp argument) and the record u64 to the RGB path if a
   time field is found in the 32-byte frame record. Today the assembler throws the mono timestamp
   away.
2. **Fix the mux.h clock comment** to `[UNKNOWN]` with a pointer to §2 of this document. Leaving a
   wrong constant in a public header is worse than admitting the gap.
3. **Make the monotonicity checks honest.** `meta2_mux_counters_monotonic()` returns 0 on real
   captures because of counter repeats. Replace the boolean with a gap report (count of +1 steps,
   count of repeats, count of jumps) so a caller can tell "clean" from "mostly clean".
4. **Report framing quality as a first-class result**, not a log line: exact frames, partial gaps,
   resyncs, and usable-fps already exist in `meta2_mono_stats_t`; give the RGB path the same struct.
5. **A single capture API** that owns the standing rule "all enabled endpoints must be drained"
   instead of leaving it to the caller, because a reader set that omits an endpoint looks like a dead
   camera (`docs/05`).
6. **A regression corpus**: check a small set of saved captures into a data repo (or a checksum
   manifest — the captures themselves are 0.7–1.8 GB each and must not go into git) so parser
   changes are measured, not asserted.

Out of scope, unchanged: SLAM, rectification, rendering, calibration solving.

---

## 5. Sequenced plan

**Phase 0 — no device, no risk.** Items 1–6 above. This is real library work and it is not blocked
on the headset being connected.

**Phase 1 — DONE 2026-10-25, answered in `docs/16-time-base.md`.** Run in gate-certified
sessions via `examples/meta2_capture_live.c … gate tries=5 probe=4 clock`. Result: the mono
fragment timestamp is a **sample-domain counter** (9,204 ticks per fragment, identical in two
sessions whose fragment rates differed 23.5×), so it orders samples but does not tie them to
real time; the mono A/B skew is a **constant 64 fragments**; **RGB carries no device timestamp
at all** — every 4-byte slot of its 32-byte header is constant, zero, the frame counter, or
unstructured. The 336.29 MHz mono "clock" quoted earlier is withdrawn as a drain-rate artifact.
Two claims in that paragraph were later superseded by the same document, and are repeated here
because they were load-bearing: **RGB does carry a device timestamp**, in the 32-byte trailer
block 8 bytes before the `baabedfe` magic, not in the 32-byte header that was swept; and the
"constant 64-fragment" A/B skew is a property of the per-fragment sample-domain field, not of
the cameras — the frame-record trailers of A and B carry identical timestamps with separate
packet counters. The tick→second scale is now measured, not open: 117,821,900 Hz (docs/17).

**Phase 2 — offline, from saved captures.** Open items #2 and #6. `cap_cold_ep82.bin`,
`screen_66_ep82.bin`, `ir29_ep82.bin` and `cap_four_ep82.bin` are already on disk; the mono trailer
timestamps are already inside them. No headset needed.

**Phase 3 — coached physical session, mostly DONE 2026-10-26.** Open items #4, #5, #8, and the
mono/RGB calibration run for #3. Coaches live in `tools/` (`gyro_coach.py`, `axis_coach.py`,
`face_coach.py`, `colour_coach.py`) and all wait for the operator's start click.

- #4 gyro calibration: done (docs/17).
- The colour-target item: **done**. The YUV422 chroma order is UYVY, measured against a
  saturated red/blue target (5.3.1), and pinned by `tests/test_decode.c`.
- The attempt to settle the 18 deg cant: **negative result** (18.3.1). Gravity poses on this
  device have an accuracy floor of 6–11 deg, which is the same size as the anomaly being
  tested, so that route is closed rather than retried. The cant now needs the camera optical
  axis, which is offline work in docs/08.
- The calibration run for #3 no longer needs coaching at all, and turned out not to need a
  run either: the mono/RGB intrinsics and the camera-to-camera extrinsics were read straight
  out of the vendor rig (docs/19). A healthy all-four session delivered RGB complete at
  30.0000 fps over two 25 s windows with contiguous frame counters and zero host drops.
- What #3 still needs from a coached session is one thing only: camera-to-IMU extrinsics,
  which the vendor file does not contain.

**Phase 4 — decide the product shape.** Re-opened 2026-10-26, because the answer Phase 1 appeared
to give was wrong in the direction that matters. A/B do carry the same device timestamp, and RGB
does have one, on the same clock as the IMU stream. So the product statement is stronger than the
one written on 2026-10-25: mono pair, RGB and dual IMU all timestamped in one device clock at
117,821,900 ticks/s, that clock being device uptime rather than wall time and production-coupled
(it stops when the device stops producing, docs/16 §16.11). What is still missing for a real VIO
input set is calibration, not protocol — and the calibration half has moved: camera intrinsics
and camera-to-camera extrinsics are extracted and validated (docs/19), camera-to-IMU extrinsics
are not in the vendor file at all and remain a measured map with a 6–10 deg floor (docs/18).
The mono pair is a **tracking** pair, not a depth pair: 182° × 120° fisheyes, 83.30° apart on a 13.8 cm
baseline, overlapping over ±49.6° around straight ahead (docs/19 §19.5.1). Frame-lock is measured from
the trailer; whether the shared stamp is an exposure instant or only a framing stamp is still open
(item 2). Say that in the README instead.
