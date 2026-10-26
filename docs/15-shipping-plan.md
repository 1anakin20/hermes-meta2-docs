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
`[UNKNOWN]` which chroma phase is U and which is V — every capture so far is near-neutral, so no
statistic distinguishes them.

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

`[VERIFIED]` fragment format: 4,096 B fragments, magic at +8, tag u16 at +20, fragment counter u16
at +28 advancing +1 per fragment per camera, 2,032 u16 samples at +32, 16-byte trailer. Full frame
= 721,920 B samples + 32 B trailer. `meta2_mono_feed` assembles exact frames; `meta2_mono_to_gray`
maps 10→8 bit (black level 42, max 1023).

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
±2000 deg/s full scale, from a coached 360° session - docs/17 §17.3. Accel ≈ 16,384 counts/g at
±2 g `[INFERRED, moderate]` - docs/17 §17.5.

**Correction to `docs/14-project-state.md` §2:** "~57 records/s" is one configuration, not the
device's rate. Measured across captures with the same tag mix: 80.6 records/s (`e3a`, 8.0 s),
371 records/s (`cap_warm`, 15.0 s), 448 records/s (`probe3`, 12.0 s). The mux rate is not fixed.
`[MEASURED]`

`[MEASURED]` the packet counter at +252 advances +1 per record in 5,565 / 5,567 (`cap_warm`),
20,372 / 20,395 (`e3b`), 636 / 637 (`occl_baseline`) steps — i.e. **mostly +1, with occasional
repeats**. `meta2_mux_counters_monotonic()` returns 0 on real captures because of those repeats.

---

## 2. The blocker: there is no usable timestamp

This is the single thing that decides whether the library ships as a *capture* library or as a
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
| 1 | **Device clock semantics** (§2) | `[UNKNOWN]`, and the documented constant is wrong | Live capture: readers pending on `0x81`+`0x82`+`0x83`, log host wall clock per URB *and* the device timestamp per record, 30 s, repeat 3× with different masks. Gives ticks/s directly and shows whether it is load-dependent | 1 session, device required |
| 2 | **Mono A/B simultaneity** | `[UNKNOWN]`. A and B correlate with EP `0x83` (0.472 / 0.252 vs 0.04–0.07 shuffled) but weakly with each other — consistent with time-interleaved acquisition | Capture `0x82` with a known scene and read the per-fragment trailer timestamps; if A and B carry distinct, alternating timestamps they are not simultaneous | 1 capture, no operator |
| 3 | **Mono / RGB intrinsics and camera-to-IMU extrinsics** | `[UNKNOWN]`. ToF intrinsics are extracted; mono/RGB are in the SDK's `g_pmd_cad` region and have never been extracted cleanly | Parse the calibration region for the mono/RGB blocks; failing that, a planar-calibration run (checkerboard at 12 positions) against captured frames | parse + 1 coached session |
| 4 | **Gyro scale factor** | `[MEASURED]` | Done 2026-10-25 by coached 360° turns: 0.0613 deg/s per count, ±2000 deg/s range, plus the tick rate 117,821,900 Hz and the IMU0↔IMU1 axis map - docs/17 | done |
| 5 | **U vs V in the YUV422 stream** | `[UNKNOWN]`, coin flip | Capture against a saturated primary (a red and a blue target) and compare mean R−B under each packing | 1 coached session |
| 6 | **Mono frame tearing, 20% of frames** | `[MEASURED]` 71–76% of gaps exact, 79–84% of volume usable | Determine whether the partial gaps are host-side URB scheduling or device-side: correlate `partial_gaps` against `timeouts` and concurrent-reader count | offline, from saved captures |
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
Remaining: per-tag mux clocks on EP `0x81`, and the mono tick→second scale.

**Phase 2 — offline, from saved captures.** Open items #2 and #6. `cap_cold_ep82.bin`,
`screen_66_ep82.bin`, `ir29_ep82.bin` and `cap_four_ep82.bin` are already on disk; the mono trailer
timestamps are already inside them. No headset needed.

**Phase 3 — coached physical session.** Open items #4, #5, #8, and the mono/RGB calibration run for
#3. Use `re/scene_coach.py` (`:8095`), which waits for the operator's start click.

**Phase 4 — decide the product shape.** Phase 1 answered this, partially and against us: A/B are
**not** simultaneous (constant 64-fragment skew, calibratable) and RGB has **no** device clock.
So the honest product statement is: mono pair + dual IMU alignable in the mono sample domain with
a fixed correction; RGB ordered by frame counter only, loosely clocked against the rest. Not a
full VIO input set. Say that in the README.
