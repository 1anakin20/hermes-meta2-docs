# 10. Enable masks, reader back-pressure, and mono framing

Everything here was measured on 2026-10-16 with `re/capture_mask.py`, which arms with the
full 417-transfer sequence, starts a reader thread per chosen endpoint **before** any control
traffic, then loops a 4-command sustaining set with the masks substituted. Framing quality is
reported as the fraction of trailer-to-trailer gaps that are exactly one frame.

## 10.1 The enable mask is real and it gates cameras

The endpoint feed is `0xC0` / value 6 with `[0, 4, 0, 0, 0, mask]`;
`Mono0 = 2, Mono1 = 4, ToF = 8, Multiplexor = 16, RGB = 32, STD = 64`. Screening, 8 s per
mask, readers pending on all four endpoints:

| mask | enabled | EP 0x81 | EP 0x82 | EP 0x83 | EP 0x84 |
|---|---|---|---|---|---|
| `0x7e` | everything | 0.06 MB/s | **112.5 MB/s** | **108.8 MB/s** | **74.0 MB/s** |
| `0x66` | mono + STD | 0.02 | **74.5** | 52.3 | 9.0 |
| `0x60` | RGB + STD | 0.02 | 4.6 | 4.8 | 4.0 |
| `0x48` | ToF + STD | 0.02 | 5.8 | 4.8 | **65.1** |
| `0x50` | mux + STD | 0.02 | 4.8 | 4.8 | 9.1 |

`[VERIFIED]` The mask selects which camera streams fast. With `0x48` and a reader on EP 0x84
only, ToF delivered **63.45 MB/s, 4,692 complete frames in 15 s = 313 fps, 99.9% of gaps
exactly one frame** — the cleanest capture of any endpoint in the project.

`[UNKNOWN]` why `0x60` (RGB only) is *slower* on EP 0x83 than `0x66` (mono only) is. The
mask clearly gates something, but the rate allocation is not a simple "enabled ⇒ fast".

## 10.2 Mono needs pending readers on all four endpoints

Same mask (`0x66`), different reader sets, 8–15 s:

| readers pending | EP 0x82 rate | complete mono frames |
|---|---|---|
| `{0x82}` | 0.13 MB/s | 0% |
| `{0x81, 0x82}` | 0.06 MB/s | 0% |
| `{0x82, 0x83}` | 0.16 MB/s | 0% |
| `{0x81, 0x82, 0x84}` | 27.7 MB/s | 7.8% |
| `{0x81, 0x82, 0x83, 0x84}` | 49–74 MB/s | 71–77% |

`[VERIFIED]` EP 0x82 collapses to near-zero when the other endpoints have no reader, even
though the mask enables only the mono cameras. The device writes to endpoints whether or not
anyone is draining them, and an undrained endpoint back-pressures the mono stream. A reader
must keep a URB pending on **every** bulk IN endpoint, including ones whose data it discards.
`[INFERRED]` a shared FIFO or a single FPGA DMA engine behind all four endpoints.

## 10.3 Device state is hysteretic across `libusb_reset_device`

Identical configuration, two runs, same day: **74 MB/s** and **2.12 MB/s** on EP 0x82. Both
did the port reset, both re-armed with the full 417-transfer sequence (`ok=279 fail=138`
every time). The reset does **not** restore a known state.

What does control it is the mask the device was last left in. Adding a warm-up phase in the
same process, before the measured phase:

| warm-up mask | measured mask | EP 0x82 rate | complete mono frames | EP 0x83 | EP 0x84 |
|---|---|---|---|---|---|
| `0x7e` (everything on) | `0x66` | 54.2 MB/s | **7.6%** | 80.4 MB/s, 99.8% | 87.5 MB/s, 99.6% |
| `0x00` (everything off) | `0x66` | 49.1 MB/s | **71.3%** | 34.8 MB/s, 99.6% | 6.0 MB/s, 98.9% |

`[VERIFIED]` Warming with everything off and then measuring with mono-only produces mono
frames that are complete 71% of the time; warming with everything on produces the same byte
rate with frames complete only 7% of the time. `[UNKNOWN]` the mechanism — plausibly the
FPGA keeps a per-camera readout configuration latched that a USB port reset does not clear.

**Practical rule:** warm the device with the mask you intend to measure, or with `0x00`, and
never trust a single run's rate. Always report framing quality alongside the byte rate.

## 10.4 The mono trailer is not a frame delimiter

EP 0x82 emits its trailer (`efbeadde 0df0ddda 00000000`) at roughly **62 Hz per camera**
while complete 752 × 480 frames arrive at **27–44 fps**. Only 7–77% of trailer-to-trailer
gaps are exactly 721,952 B, depending on device state; the rest are partial acquisitions
(195,072 / 227,584 / 260,096 / 292,608 / 325,120 B, all multiples of 32,512 B = 8 fragments).

Consequences, all `[VERIFIED]`:

- The **concatenate-and-cut** model (strip every trailer, cut every 721,920 B) splices two
  acquisitions into one frame. That is what produces the horizontal slice-shift — tearing —
  in rendered mono video. It is not data loss: the fragment counter at mono header +28
  increments by exactly 1 across all 205,640 fragments per camera in `cap_four_ep82.bin`,
  with zero drops.
- The **exact-frame** model (keep only chunks whose gap is exactly 721,952 B) produces
  frames with no tearing. `re/make_mono_exact.py` implements it. On `screen_66_ep82.bin` it
  yields 435 complete frames per camera in 10 s = **44 fps**; on `cap_cold_ep82.bin`, 405 in
  15 s = **27 fps**.
- The vendor driver has the same exposure to this. Its `FindTrailerIndex` searches the
  identical 12-byte pattern, `Mono0EndPointDataConstructor` allocates
  `GrayScale16Image(752, 480)` = 721,920 B, and `BaseImageEndPointDataConstructor.AddData`
  logs *"Fragment data is too short for finalizing image"* and sets `IsComplete = false`
  whenever a chunk is short. So the SDK also gets incomplete mono frames unless the device
  is in a state where the trailer period matches the frame period. `[VERIFIED]` from source;
  `[INFERRED]` that the SDK reaches that state through configuration we have not replicated.
- 752 is the correct raster width: a lag scan over 4.3 M samples ranks **lag 752** first
  (mean |diff| 11.92, ratio 0.051 against a permutation baseline). `[VERIFIED]`

## 10.5 All four endpoints at once, usable for tracking (2026-10-25)

`examples/meta2_capture_live.c` now has the two controls `capture_mask.py` had and it did not: a
warm-up phase in a chosen mask, and a selectable sustain mode. EP `0x84` is drained and **discarded**
— its only job is to stay serviced, because §10.2 showed an undrained endpoint back-pressures mono.
Accumulating it instead fills the ring and the drain loop stops servicing it, which reintroduces the
problem.

Recipe that works: port reset + full arm → readers pending on **all four** endpoints before any
control traffic → warm-up holding mask `0x7e` for 4 s → sustain = assert+deassert as fast as
possible → keep all four serviced for the whole session.

Five consecutive runs, queue 8, read_size 65536, mask `0x7e`, mux `0x1b`, 8 s windows, `host dropped
bytes = 0` on mono/rgb/mux:

| run | mono complete | mono complete fps/camera | EP `0x83` | EP `0x81` records/s |
|---|---|---|---|---|
| 1 | 33.5% | 41.5 | 60.9 MB/s | 375.9 |
| 2 | 69.2% | **76.6** | 84.1 MB/s | 236.6 |
| 3 | 55.5% | 72.6 | 85.0 MB/s | 280.3 |
| 4 | 74.0% | 47.7 | 58.4 MB/s | 46.4 |
| 5 | 75.0% | 3.0 | 3.5 MB/s | 46.6 |

`[VERIFIED]`

**Mono is the good news: 41–77 complete frames/s per camera with every endpoint drained at once**,
against the 27 fps `docs/15` quotes and the 34.6 fps the two-endpoint configuration gives. The
frames that arrive are whole, so they carry no tearing.

**RGB is 58–85 MB/s in four of five runs** — above the 41–49 MB/s measured in §40, and above the
55 MB/s that produced the old "30 fps" figure.

Two things are not settled:

1. **Run 5 is a dud** — 3.5 MB/s on EP `0x83`, 3.0 fps mono. Same binary, same recipe. This is the
   hysteresis of §10.3, not a new failure mode. `[OPEN]` what distinguishes a run that enters the
   fast state from one that does not.
2. **The mux rate is bimodal**: 46.4 / 46.6 records/s in two runs (identical byte counts, 95,488 B)
   and 236.6 / 280.3 / 375.9 in three. For a tracking front end this is the blocking number — 46
   records/s across two IMUs is ~23 Hz each, 376 is ~188 Hz each.
   **Resolved 2026-10-27: the host's control-write cadence selects it, and it is host-independent.**
   Four Linux runs and four Windows runs, same binary, cameras at nominal and zero dropped bytes in
   every one:

   | sustain shape | mux-submask writes/s | steady records/s | Linux | Windows |
   |---|---|---|---|---|
   | assert-only, synchronous | ~6.7 | 7 | 7 | 7 |
   | toggle off→on, synchronous | ~49 | 46–53 | **52** | 46–53 |
   | paced async, 8 in flight, submask never deasserted | ~97 | **399** | 399 | 398–401 |
   | same, `mux=0x1f` (microphones added) | ~98 | **2,542** | 2,542 | 2,544 |

   The low mode is ~1 record per control write and reproduces on both hosts at the same write rate:
   `muxtoggle muxhz=50` gives 52 records/s on Linux against the 46.4 / 46.6 recorded above, and
   46–53 on Windows. The high mode is not a rate control at all — once the submask stays asserted
   and enough writes are in flight the mux free-runs, and an 8× sweep of the write rate (50 → 400/s)
   moved the steady rate by 11 records/s. So 46 was never the device's rate; it was the old sustain
   loop's own write rate read back. The device's rate is ~400 records/s for the IMU pair (~200 Hz
   each), and the microphones add ~2,150 records/s. `[VERIFIED]`

**Practical rule for a tracking session:** do not start one on a single arm. Gate on throughput —
measure the first second after arming and re-warm/re-arm if the endpoints are below a floor, because
a run like 5 looks identical to a working run until you count bytes.

## 10.6 Measurement bugs that produced wrong numbers in this area

- A greedy drain loop (`drain until the ring is empty`) never returns while data is continuous, so
  the outer time check is never re-evaluated. An 8 s window measured 24.8 s and every rate derived
  from it was understated. Bound the inner drain loops by the window as well. `[VERIFIED]`
- A capture tool that closes its window after the reader joins and the final drain overstates it
  (13.0 s reported for a 10 s capture). `[VERIFIED]`
- Warm-up threads must have their own stop flag; sharing the session's `quit` deadlocks the join.
  `[VERIFIED]`

## 10.7 Microphones still do not appear

Setting the multiplexor mask to `0x1f` (adding bit 2 = Mics) produced **no** `0x88` records:
645 multiplexor records in `cap_mux2_ep81.bin` carry tags `102` (323) and `119` (321) only.
Buttons (`153`) are absent too, even though bit 3 was already set in the old `0x1b` mask.
`[VERIFIED]` negative result. `[UNKNOWN]` whether mics need an additional command, only
stream when the vendor app requests audio, or are not routed through EP 0x81 at all.

## 10.8 The health gate works, and re-arming recovers a healthy session in 1-3 attempts (2026-10-25)

`meta2lib` `src/health.c` + `include/meta2/health.h` classify a session as `OK`, `STARVED`, `FROZEN`
or `NO_DATA` from the EP `0x81` record clock, and `meta2_capture_live gate tries=N probe=S` re-arms
from a port reset until a session is fit. `docs/13` §13.11 is what the gate is built on.

Gate decisions on the device, all four endpoints, mask `0x7e`, mux `0x1b`, warm `0x7e`, fast sustain,
queue 8, 12 s windows, probe 4 s:

| session | attempt | gate decision | window coverage | clock | records | counter span | mono fps/cam | EP `0x83` |
|---|---|---|---|---|---|---|---|---|
| 2 | 1 | rejected | 0.077 | 14.0 MHz | 383 | 380 | – | – |
| 2 | 2 | **accepted** | **0.9989** | **182.80 MHz** | 3772 | 3335 | 48.6 | 58.76 MB/s |
| 3 | 1 | rejected | 0.026 | 4.73 MHz | 377 | 375 | – | – |
| 3 | 2 | rejected | 0.075 | 13.76 MHz | 379 | 377 | – | – |
| 3 | 3 | **accepted** | **0.9944** | **181.98 MHz** | 3754 | 3382 | 47.0 | 59.34 MB/s |

`[VERIFIED]`

The two signatures are unambiguous. A starved run frames 377–383 records with the counter advancing
one per record and a clock of 4.7–14 MHz. A healthy run frames 3754–3772 records with counter span
3335–3382 and a clock of 182.0–182.8 MHz. Mono completeness alone does **not** separate them: a
starved attempt reported 74.1% complete frames while delivering 12.7 fps.

**The probe must be anchored at the first multiplexor record, not at the window opening.** Before
that fix, twenty attempts across four sessions produced zero accepts, because EP `0x81` delivered 0
bytes for the first ~3 s of the window while EP `0x82` was already delivering 100–400 MB. A probe
anchored to the window start reported `NO_DATA` for a session whose mux stream was about to start and
re-armed forever. `[VERIFIED]`

Two things the gate does not do yet:

1. **The probe is looser than the window verdict.** Accepted probes reported coverage 2.10 while the
   same session's full-window coverage was 0.9989 — the probe window is measured from when the first
   bytes were drained into the ring, not from the first record's own timestamp, so it credits the
   probe with data that arrived before it. The full-window verdict is the authoritative one. `[OPEN]`
2. **Nothing prevents the bad state, it only detects it.** Re-arming works, but the cost is 1–3
   discarded attempts of ~25 s each. `[OPEN]` what actually selects the mode.

**Measurement bug found while building this:** `mux.h` records that the `0xAA` record always carries
header timestamp 0. A `max - min` span over a window containing one of them equals the entire
magnitude of the clock. A starved 10 s run of 374 records measured 88 GHz at 48,300% coverage that
way, and the first version of the gate accepted it as the healthiest run ever recorded. The gate now
excludes timestamp-less records and decides on the median consecutive delta times the record rate.
`[VERIFIED]`

## 10.9 The recipe is now a library call, and one of its steps was wrong

`meta2lib` gained `meta2_stream_start()` (`include/meta2/stream.h`, `src/stream.c`). It owns the whole
startup: port reset, the arm sequence, readers pending before any control traffic, warm mask `0x7e`
for 4 s, fast sustain, and the gate re-arm loop. The arm sequence is embedded in the library
(`src/arm_sequence.h`, generated by `scripts/gen_arm_sequence.py` from `data/arm_capture.txt`), so a
caller needs no commands file and no flags. `tests/test_stream.c` asserts the embedded copy still
matches the file, so it cannot drift silently.

Measured through that API, four consecutive runs, defaults, 8 s windows:

| run | attempts to reach health=OK | mono | RGB | host dropped |
|---|---|---|---|---|
| 1 | 1 | 87.2 MB/s, 59.7 complete frames/s per camera | 55.2 MB/s | 0 |
| 2 | 5 | 87.3 MB/s, 59.7 | 55.2 MB/s | 0 |
| 3 | 3 | 87.3 MB/s, 59.7 | 55.2 MB/s | 0 |
| 4 | none (5 rejected) | - | - | - |

`[VERIFIED]` The mono frame count was 478 per camera in every accepted run. Mono device-time span
936,653,532 ticks over 8.00 s divided by 477 frame gaps is 1,963,634 ticks/frame, which reproduces
the independently measured 1,963,229 ticks/frame slot from §16.4.1 to 0.02%. `[VERIFIED]`

**Correction to §10.5: servicing EP `0x84` is not free.** §10.5 concluded that EP `0x84` must be kept
drained even when its data is discarded, because an undrained endpoint back-pressures mono. In these
sessions the opposite happened. With `service_depth = 1`:

- the arm landed differently - `403 ok / 4 fail` in 0.73 s, instead of `272 ok / 135 fail` in 8.23 s;
- every endpoint was starved: 0.59-1.44 MHz, coverage 0.003-0.008, mono 3-5 MB in 4 s;
- three consecutive runs of 3, 5 and 5 attempts were all rejected.

With EP `0x84` not read at all - which is `meta2_capture_live`'s own default, `read_tof = 0` - the same
binary sequence reached `health=OK` on the first probe at 197.82 MHz window coverage 1.081, mono 54.3%
complete. `[VERIFIED]`

So the §10.5 claim is kept for what it measured - a session that *is* reading EP `0x84` must keep
draining it or it collapses - but it is not a reason to read EP `0x84`. For the shipping sensor set
(RGB, mono, IMU) the default is to not read it. `[VERIFIED]`

**Two caveats the new API exposed.**

1. `meta2_stream_start()` accepts on the 4 s probe, and the probe is looser than the full window -
   the same session printed `health=OK` at acceptance (probe coverage 1.51-1.54, clock 277-281 MHz)
   and `health=FROZEN` from `meta2_stream_health()` over the following 8 s (coverage 0.77-0.83, clock
   141-151 MHz). This is §10.8 caveat 1 inside the library now. The acceptance decision is lenient by
   construction; `meta2_stream_health()` is the authoritative one. `[VERIFIED]`
2. The gate's reference constant is `META2_MUX_CLOCK_HZ = 183 MHz`, taken from the old mux `+20`
   span measurement. §16.11 brackets the actual tick rate at 162-205 MHz with a best estimate of
   ~167 MHz. A genuinely healthy session at 150-165 MHz therefore scores coverage 0.82-0.90 against
   a constant that is probably too high, and lands just under the 0.85 threshold. `[OPEN]` - the
   constant has not been re-based, because the gate was validated against it.
