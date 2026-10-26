#!/usr/bin/env python3
"""Fit the mono pair's exposure phase out of a bar_coach.py run.

  bar_offset.py <capture_prefix> [--coach-dir DIR] [--mode seq|bar] [--verbose]

Reads <capture_prefix>.prof (written by meta2lib's examples/meta2_mono_bar) and,
for the absolute-phase numbers, the page's bar_state.json and bar_timeline.csv.

WHAT IS BEING FITTED
Each mono camera integrates the screen over its own exposure window. The commanded
screen state is piecewise constant over the display's own frame intervals, taken
from the page's recorded timeline. So the level a frame reports is the fraction of
its exposure window that fell on a bright display interval:

    level_k = L0 + (L1 - L0) * fraction( [t_ref + k*T, t_ref + k*T + T] )

with T the mono frame period, known from the device clock (1,963,229 ticks per
frame slot at 117,821,900 ticks/s = 60.0143 fps), and k the DEVICE frame index,
recovered from the trailer timestamp rather than the arrival order. That is what
makes dropped frames harmless: a frame that never arrived still occupies its slot,
and the slots that did arrive still say where the window sat.

One unknown per camera: t_ref, the exposure phase. The difference between the two
cameras is the exposure offset the experiment is about.

WHY THE DIFFERENCE IS THE HONEST NUMBER
t_ref is anchored to wall clock, and three clocks are in the chain: the monitor's
browser clock, this machine's clock, and the device clock. Their offsets are not
measured. They are COMMON MODE - they shift both cameras' t_ref by the same amount
- so they cancel in t_ref_left - t_ref_right and they do not cancel in t_ref itself.
Report the offset; treat the absolute phase as indicative.

THE BAR MODE IS A DIFFERENT QUESTION
With the sweeping bar the reading is a position, and a position through a 182 deg
fisheye is a warp. Cross-camera comparison of bar row is therefore NOT a clean
timing measurement. What the bar does give is the shutter model: a rolling sensor
exposes its rows at different times, so a bar sweeping at a known rate lands at a
different row for each row of the sensor, and the captured band is slanted / spread
over more rows than its own thickness. The fit here is peak_row against frame index;
its slope in rows-per-frame is the readout time in frame periods.
"""

import json
import os
import struct, sys, statistics
import sys

TICK_HZ = 117821900.0          # docs/17: calibrated from a 400 s coached session
MONO_TICKS_PER_FRAME = 1963229.0   # docs/16: measured mono cadence
MONO_FPS = TICK_HZ / MONO_TICKS_PER_FRAME
SLACK = 3.0   # seconds of capture kept either side of the target window

LCG_A, LCG_C = 1103515245, 12345


def sequence(seed, n):
    x = seed & 0xFFFFFFFF
    out = []
    for _ in range(n):
        x = (LCG_A * x + LCG_C) & 0xFFFFFFFF
        out.append((x >> 16) & 1)
    return out


def read_prof(path):
    with open(path, "rb") as f:
        head = f.read(4)
        if head != b"M2BP":
            raise SystemExit("%s is not a M2BP profile file" % path)
        ver, h, w, b0, b1 = struct.unpack("<IIIII", f.read(20))
        rec = struct.Struct("<qQIBBd")
        rows = struct.Struct("<%df" % h)
        out = []
        while True:
            buf = f.read(rec.size)
            if len(buf) < rec.size:
                break
            host_us, ts, pkt, tag, has_tr, mean = rec.unpack(buf)
            prof = rows.unpack(f.read(rows.size))
            out.append(dict(host_us=host_us, ts=ts, pkt=pkt, tag=tag,
                            has_trailer=has_tr, mean=mean, profile=prof))
    return ver, h, w, b0, b1, out


def read_anchor(csv_path):
    real = mono = None
    for line in open(csv_path):
        if not line.startswith("#"):
            break
        if "anchor" in line:
            for tok in line.split():
                if tok.startswith("realtime="):
                    real = float(tok.split("=")[1])
                elif tok.startswith("monotonic="):
                    mono = float(tok.split("=")[1])
    return real, mono


def frame_index(ts_list):
    """Device frame index from the trailer timestamp, so a dropped frame still
    occupies its slot instead of shifting every later frame by one."""
    t0 = min(r["ts"] for r in ts_list)
    return [int(round((r["ts"] - t0) / MONO_TICKS_PER_FRAME)) for r in ts_list]


def fit_phase(frames, disp_t, disp_b, T, verbose=False, window=None):
    global SLACK
    """Search the exposure phase that best explains this camera's brightness
    sequence. Returns (t_ref, rms, corr, levels, align_score, used).

    window is (t_start, t_end) of the target run in wall time. Frames outside it are
    dropped before anything is fitted. A capture is normally longer than the target
    run - this one started 11.95 s, or 716 display frames, before the screen began
    flickering - and those frames are not weak evidence, they are noise: their
    brightness tracks the room, not the commanded sequence, and including them both
    dilutes the correlation and puts the alignment out of reach of the search."""
    if window is not None:
        lo, hi = window
        slack = SLACK
        frames = [r for r in frames if lo - slack <= r["host_wall"] <= hi + slack]
        if len(frames) < 12:
            return None, 0.0, 0.0, (0.0, 0.0), 0.0, len(frames), 0.0
    levels = [r["mean"] for r in frames]
    lo = min(levels)
    hi = max(levels)
    # Robust bright/dark levels: the sequence is random, so the 10th/90th
    # percentiles are well populated, and a single blown-out frame cannot move them.
    s = sorted(levels)
    L0 = s[max(0, int(0.10 * (len(s) - 1)))]
    L1 = s[min(len(s) - 1, int(0.90 * (len(s) - 1)))]
    if L1 - L0 <= 1e-9:
        return None, 0.0, 0.0, (lo, hi), 0.0, len(levels), 0.0

    n = len(disp_t)
    D = (disp_t[-1] - disp_t[0]) / (n - 1)
    # The MEAN display interval, not the first one. The page's frame clock is
    # requestAnimationFrame and individual intervals jitter: in this capture the very
    # first interval was 15.70 ms against a 16.69 ms mean. Using the first interval as
    # the period makes the frame-index mapping drift ~240 frames over a 60 s run, and
    # the alignment search then cannot reach the true shift at all - it reports "no
    # correlation" on a capture where the target is plainly visible.

    import bisect
    last_start = disp_t[-1]

    def predicted(t_ref):
        """Integrate the piecewise-constant commanded screen over each frame's
        exposure window. Uses the MEASURED display interval starts, not an assumed
        uniform period, so display jitter lands in the residual where it can be
        seen rather than being silently absorbed."""
        out = []
        for k in kidx:
            a = t_ref + k * T
            b = a + T
            j = max(0, bisect.bisect_right(disp_t, a) - 2)
            acc = 0.0
            span = 0.0
            while j < n:
                s0 = disp_t[j]
                s1 = disp_t[j + 1] if j + 1 < n else last_start + D
                if s0 >= b:
                    break
                ov = min(b, s1) - max(a, s0)
                if ov > 0:
                    acc += ov * disp_b[j]
                    span += ov
                j += 1
            if b > last_start + D:      # window ran past the recorded timeline
                ov = min(b, last_start + D) - max(a, last_start + D)
                if ov > 0:
                    span += ov
            frac = acc / span if span > 0 else 0.0
            out.append(L0 + (L1 - L0) * frac)
        return out

    kidx = frame_index(frames)
    x = [(v - L0) / (L1 - L0) for v in levels]

    # ---- stage 1: read the frame alignment off the data ----
    # The absolute wall alignment cannot be trusted. host_us is when a frame was
    # DRAINED from the reader ring, not when it was exposed, and the ring holds
    # seconds. The page's timeline may be anchored to POST receipt times, up to a
    # second late. Neither is bounded, so no search window around either is safe.
    #
    # Instead: slide the camera's brightness sequence against the commanded sequence
    # and take the shift that correlates best. The commanded sequence is random, so
    # the peak is sharp and the alignment comes from the data, not from a clock.
    #
    # The slide is applied on top of a per-frame time estimate, not on top of the
    # frame index. The cameras run at 60.0143 fps and the display at whatever the
    # browser manages, so the two drift apart - measured 1.5 frames over 20 s at
    # 59.94 Hz. A single integer shift over the whole run therefore aligns one end
    # and misaligns the other, and halves the correlation. Using each frame's own
    # elapsed time as the starting index absorbs that drift; the unknown part is a
    # constant offset, which is exactly what the slide searches for.
    j0 = [(r["host_wall"] - disp_t[0]) / D for r in frames]
    mx = sum(x) / len(x)
    sx = (sum((v - mx) ** 2 for v in x) / len(x)) ** 0.5
    mb = sum(disp_b) / n
    sb = (sum((v - mb) ** 2 for v in disp_b) / n) ** 0.5

    # Bounded by the window filter above: nothing further out can matter, because
    # every kept frame is within `slack` of the target run. The residual is clock
    # skew between the monitor and this machine plus the drain lag.
    max_shift = int(slack / D) + 40
    best_s, best_score = None, -1.0
    scored = []
    for sh in range(-max_shift, max_shift + 1):
        acc = 0.0
        cnt = 0
        for i in range(len(kidx)):
            j = int(round(j0[i])) + sh
            if 0 <= j < n:
                acc += (x[i] - mx) * (disp_b[j] - mb)
                cnt += 1
        if cnt < 0.6 * len(kidx) or sx <= 0 or sb <= 0:
            continue
        score = acc / (cnt * sx * sb)      # Pearson: 1.0 is a perfect match
        scored.append((score, sh, cnt))
        if score > best_score:
            best_score, best_s = score, sh
    if verbose:
        scored.sort(reverse=True)
        print("    coarse search: max_shift %d, j0 spans %.1f..%.1f, frames %d, n %d"
              % (max_shift, j0[0], j0[-1], len(kidx), n))
        print("    top shifts: " + ", ".join("sh%+d corr %+.3f cnt %d" % (s, c, k)
                                            for c, s, k in scored[:6]))
        # direct recomputation at sh=-11, to see which ingredient disagrees
        sh0 = -11
        xs = []; ys = []
        for i in range(len(kidx)):
            j = int(round(j0[i])) + sh0
            if 0 <= j < n:
                xs.append(x[i]); ys.append(disp_b[j])
        mx2 = sum(xs)/len(xs); my2 = sum(ys)/len(ys)
        num2 = sum((a-mx2)*(b-my2) for a,b in zip(xs,ys))
        den2 = (sum((a-mx2)**2 for a in xs)*sum((b-my2)**2 for b in ys))**0.5
        print("    direct at sh=-11: n=%d pearson=%.3f  sx=%.3f sb=%.3f  x range %.2f..%.2f"
              % (len(xs), num2/den2 if den2 else 0, sx, sb, min(x), max(x)))
        print("    host_wall range %.3f .. %.3f ; disp_t[0] %.3f ; D %.6f"
              % (min(r["host_wall"] for r in frames), max(r["host_wall"] for r in frames),
                 disp_t[0], D))
        want = {s: (c, k) for c, s, k in scored if -15 <= s <= -5}
        print("    scores near sh=-11: " + ", ".join(
            "sh%+d corr %+.3f cnt %d" % (s, want[s][0], want[s][1]) for s in sorted(want)))
        print("    disp_b[:24]=%s  j0[:4]=%s  x[:4]=%s"
              % ("".join(str(b) for b in disp_b[:24]),
                 ["%.1f" % q for q in j0[:4]], ["%.2f" % q for q in x[:4]]))
        skipped = sum(1 for _ in range(1) if False)
    if best_s is None or best_score < 0.40:
        # Below this the camera is not tracking the target: the screen is not in
        # view, or the scene's own brightness changes are drowning the target.
        return None, 0.0, 0.0, (L0, L1), best_score, len(levels), 0.0
    if verbose:
        print("    frame alignment: camera frame k <-> displayed frame %+.1f%+d, "
              "correlation %.3f" % (j0[0], best_s, best_score))

    # ---- stage 2: the sub-frame phase ----
    # Now the search is genuinely local: one display period either side of the
    # alignment stage 1 found.
    coarse = 40          # grid points per display period -> ~0.42 ms at 60 Hz
    span = 2
    steps = coarse * span * 2
    base = disp_t[0] + (j0[0] + best_s) * D
    best = (None, 1e30)
    for i in range(steps + 1):
        t_ref = base - span * D + D * i / coarse
        pv = predicted(t_ref)
        sse = sum((pv[i2] - levels[i2]) ** 2 for i2 in range(len(levels)))
        if sse < best[1]:
            best = (t_ref, sse)
    # Refine inside the coarse cell. predicted() is piecewise linear in t_ref with
    # breakpoints at display boundaries, so a cell this wide cannot hide a minimum.
    t_c, _ = best
    cell = D / coarse
    for i in range(-coarse * 20, coarse * 20 + 1):
        t_ref = t_c + cell * i / 20.0
        pv = predicted(t_ref)
        sse = sum((pv[i2] - levels[i2]) ** 2 for i2 in range(len(levels)))
        if sse < best[1]:
            best = (t_ref, sse)
    t_ref, sse = best
    p = predicted(t_ref)
    rms = (sse / len(levels)) ** 0.5

    # Uncertainty on the phase, from the curvature of the residual near its minimum.
    # SSE(t) ~ SSE_min + a (t - t*)^2, and for a least-squares fit with residual
    # variance s^2 the parameter variance is s^2 / a. Without this, a number like
    # "0.102 ms" carries no information about whether it differs from zero.
    N = len(levels)
    s2 = sse / max(1, N - 1)
    delta = D / 200.0
    def sse_at(t):
        pv = predicted(t)
        return sum((pv[i2] - levels[i2]) ** 2 for i2 in range(N))
    a = (sse_at(t_ref + delta) - 2.0 * sse + sse_at(t_ref - delta)) / (2.0 * delta * delta)
    sigma = (s2 / a) ** 0.5 if a > 0 else float("inf")
    m = sum(levels) / len(levels)
    mp = sum(p) / len(p)
    num = sum((levels[i] - m) * (p[i] - mp) for i in range(len(levels)))
    den = (sum((v - m) ** 2 for v in levels) * sum((v - mp) ** 2 for v in p)) ** 0.5
    corr = num / den if den > 0 else 0.0
    if verbose:
        print("    levels %.1f..%.1f  fitted L0=%.1f L1=%.1f  rms=%.2f  corr=%.3f"
              % (lo, hi, L0, L1, rms, corr))
    return t_ref, rms, corr, (L0, L1), best_score, len(levels), sigma


def shutter_test(by_tag, fitted, disp_t, disp_b, T, h, window):
    """Read the shutter model off the seq frames themselves.

    A frame whose exposure window straddles a bright/dark boundary integrates part
    bright and part dark. What distinguishes the two shutter models is the SHAPE of
    that partial light across the frame, not its amount.

    Global shutter: every row integrates the same window, so a frame's residual is the
    monitor's footprint in the recorded band scaled by one number. Every straddling
    frame has the SAME shape.

    Rolling shutter: rows integrate at staggered times, so the bright/dark boundary
    lands at a different row in every frame. The shapes stop matching.

    Two groups are measured. Frames whose exposure contains NO display transition
    (bright fraction near 0 or 1) look the same under either model - they are the
    control. Only straddling frames can separate the models. Comparing the two makes
    the test self-calibrating: if the room itself is unstable, both numbers fall
    together and the honest answer is "inconclusive", not "global".

    An earlier version compared a uniform model against the best two-level step model.
    That is biased towards "rolling" - under a global shutter the residual is the
    monitor's footprint, which a step model fits well too - and a real capture scored
    48% against a 50% threshold, so the verdict came out of noise.
    """
    import bisect
    n = len(disp_t)
    D = (disp_t[-1] - disp_t[0]) / (n - 1)
    last = disp_t[-1]
    print("\nSHUTTER TEST from the seq frames (no bar needed)")
    for tag in sorted(fitted):
        t_ref = fitted[tag][0]
        v = [r for r in by_tag[tag]
             if window[0] - SLACK <= r["host_wall"] <= window[1] + SLACK]
        v.sort(key=lambda r: r["ts"])
        if len(v) < 60:
            continue
        kidx = frame_index(v)
        bg = [sum(r["profile"][i] for r in v) / len(v) for i in range(h)]
        fracs = []
        for k in kidx:
            a = t_ref + k * T
            b = a + T
            jj = max(0, bisect.bisect_right(disp_t, a) - 2)
            acc = span = 0.0
            while jj < n:
                s0 = disp_t[jj]
                s1 = disp_t[jj + 1] if jj + 1 < n else last + D
                if s0 >= b:
                    break
                ov = min(b, s1) - max(a, s0)
                if ov > 0:
                    acc += ov * disp_b[jj]
                    span += ov
                jj += 1
            fracs.append(acc / span if span > 0 else 0.0)
        # A frame's residual is (its bright fraction - the mean bright fraction) times
        # the monitor's footprint. A frame sitting exactly at the mean therefore has NO
        # shape signal at all, and its "shape" is pure photometric noise - which is how
        # this test produced a confident false "ROLLING" on a synthetic global-shutter
        # capture at 4x noise. Two consequences: keep only frames far enough from the
        # mean that the signal beats the noise. (Normalising each residual by its deviation
        # was tried and is wrong: it lifts the noise-dominated frames to the same scale as
        # the signal-bearing ones, and the rolling signature - which lives in the raw
        # magnitudes of the shape - disappears. Filter, do not rescale.)
        fbar = sum(fracs) / len(fracs)
        dev = [f - fbar for f in fracs]
        mid = [i for i, f in enumerate(fracs) if 0.15 < f < 0.85 and abs(dev[i]) > 0.18]
        ctrl = [i for i, f in enumerate(fracs)
                if (f < 0.10 or f > 0.90) and abs(dev[i]) > 0.18]
        if len(mid) < 20 or len(ctrl) < 20:
            print("  tag 0x%02x: %d straddling and %d control frames - not enough to read"
                  " the shutter" % (tag, len(mid), len(ctrl)))
            continue

        def edge_measure(idxs):
            """For one frame: the biggest single-row jump in the background-subtracted
            profile, divided by that frame's brightness deviation.

            A global shutter's residual is the monitor's footprint scaled by one number.
            Its biggest row-to-row jump is whatever the footprint's own gradient is, plus
            noise - and the control frames carry the same footprint at a larger deviation,
            so dividing by the deviation puts both groups on the same scale. A rolling
            shutter's residual has a hard horizontal edge where the display changed mid
            exposure, and that edge is a jump of the FULL amplitude. This is exactly the
            thing a person would see looking at one frame, which is why it is the metric
            worth trusting."""
            out = []
            for i2 in idxs:
                res = [v[i2]["profile"][rr] - bg[rr] for rr in range(h)]
                amp = sum(abs(x) for x in res) / h
                if amp < 2.0:
                    continue
                jump = max(abs(res[rr + 1] - res[rr]) for rr in range(h - 1))
                out.append(jump / abs(dev[i2]))
            return out

        str_e = edge_measure(mid)
        ctl_e = edge_measure(ctrl)
        if len(str_e) < 20 or len(ctl_e) < 20:
            print("  tag 0x%02x: only %d straddling and %d control frames carry measurable"
                  " signal" % (tag, len(str_e), len(ctl_e)))
            continue
        s_edge = statistics.median(str_e)
        c_edge = statistics.median(ctl_e)
        print("  tag 0x%02x: %d straddling frames, %d control frames" % (tag, len(str_e), len(ctl_e)))
        print("      biggest row-to-row edge, straddling frames : %.3f of the frame's"
              " brightness deviation" % s_edge)
        print("      biggest row-to-row edge, control frames    : %.3f  (control frames"
              " cannot contain an edge, so this is the baseline)" % c_edge)
        # No verdict. A rolling shutter's signature is a difference between the time the
        # first row exposes and the time the last row exposes. This target cannot produce
        # one: the display changes state every 16.69 ms and the sensor reads out every
        # 16.66 ms, so a row's exposure window slides across exactly one display state
        # over the height of the frame. The transition is therefore spread over the whole
        # frame as a ramp, never as an edge, and a ramp is what the target's own shape
        # already looks like. Sweeping the synthetic model over exposure times from a full
        # frame down to 0.67 ms, the biggest normalised edge is 0.121 global vs 0.080
        # rolling at full exposure and 0.193 vs 0.138 at 0.67 ms - the rolling case is the
        # SMOOTHER of the two at every exposure. Three formulations of this test were
        # tried and each produced a wrong verdict on synthetic captures with known
        # answers, which is the point of having them.
        #
        # Settling the shutter model needs something that changes faster than the readout
        # time: a real strobe, mains-frequency flicker, or a fast pan measured against the
        # gyro. A 60 Hz display cannot do it, at any brightness.
        print("      -> NOT MEASURABLE WITH THIS TARGET. The target changes state at 60 Hz")
        print("         and the sensor reads out at 60 Hz, so a row-time skew appears as a")
        print("         ramp across the whole frame rather than an edge. The numbers above")
        print("         are reported for completeness, not as a verdict.")


def bar_analysis(by_tag, h, verbose=False):
    """Sweeping bar: peak row against device frame index, per camera."""
    import statistics
    res = {}
    for tag, frames in by_tag.items():
        if len(frames) < 8:
            res[tag] = None
            continue
        k = frame_index(frames)
        rows = [r["profile"] for r in frames]
        peaks = []
        widths = []
        for prof in rows:
            mx = max(prof)
            mn = min(prof)
            peaks.append(prof.index(mx))
            half = mn + 0.5 * (mx - mn)
            widths.append(sum(1 for v in prof if v >= half))
        # least squares slope of peak row vs frame index
        n = len(k)
        mk = sum(k) / n
        mp = sum(peaks) / n
        num = sum((k[i] - mk) * (peaks[i] - mp) for i in range(n))
        den = sum((k[i] - mk) ** 2 for i in range(n))
        slope = num / den if den else 0.0
        res[tag] = dict(slope_rows_per_frame=slope,
                        mean_peak=sum(peaks) / n,
                        mean_width=sum(widths) / n,
                        min_width=min(widths), max_width=max(widths),
                        n=n)
    return res


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    global SLACK
    prefix = sys.argv[1]
    coach = "/home/hermes/work/metavision/re"
    mode = None
    verbose = "--verbose" in sys.argv
    for a in sys.argv[2:]:
        if a.startswith("--slack="):
            SLACK = float(a.split("=", 1)[1])
        elif a.startswith("--coach-dir="):
            coach = a.split("=", 1)[1]
        elif a.startswith("--mode="):
            mode = a.split("=", 1)[1]

    ver, h, band_w, b0, b1, frames = read_prof(prefix + ".prof")
    real, mono = read_anchor(prefix + ".csv")
    if real is None:
        raise SystemExit("no clock anchor in %s.csv" % prefix)

    for r in frames:
        # host_us is CLOCK_MONOTONIC; the page's timeline is wall clock.
        r["host_wall"] = r["host_us"] / 1e6 + (real - mono)

    by_tag = {}
    for r in frames:
        by_tag.setdefault(r["tag"], []).append(r)
    for v in by_tag.values():
        v.sort(key=lambda r: r["ts"])

    print("capture %s: %d frames, band width %d (left centre %d, right centre %d)"
          % (prefix, len(frames), band_w, b0, b1))
    for tag in sorted(by_tag):
        v = by_tag[tag]
        span = (v[-1]["ts"] - v[0]["ts"]) / TICK_HZ
        print("  tag 0x%02x: %d frames over %.3f s device time -> %.2f fps delivered"
              % (tag, len(v), span, (len(v) - 1) / span if span > 0 else 0))

    state = {}
    try:
        state = json.load(open(os.path.join(coach, "bar_state.json")))
    except Exception as e:
        print("no bar_state.json in %s (%s) - absolute phase unavailable" % (coach, e))
    if mode is None:
        mode = state.get("mode", "seq")

    if mode == "bar":
        print("\nBAR MODE - shutter model")
        res = bar_analysis(by_tag, h, verbose)
        for tag in sorted(res):
            r = res[tag]
            if r is None:
                print("  tag 0x%02x: too few frames" % tag)
                continue
            print("  tag 0x%02x: peak row drifts %.3f rows/frame; band width "
                  "mean %.1f rows (range %d..%d) over %d frames"
                  % (tag, r["slope_rows_per_frame"], r["mean_width"],
                     r["min_width"], r["max_width"], r["n"]))
        print("\n  A band no wider than its own thickness, with no peak-row drift, is a")
        print("  global shutter. Drift and extra width mean rows expose at different")
        print("  times, and there is no single exposure instant to quote.")
        return 0

    # ---- seq mode ----
    if not state:
        return 1
    seed = state.get("seed")
    nframes = int(state.get("frames") or 0)
    if not seed or nframes < 8:
        print("page run unavailable (seed=%s frames=%s)" % (seed, nframes))
        return 1

    tl = []
    for line in open(os.path.join(coach, "bar_timeline.csv")):
        if line.startswith("#") or not line.strip():
            continue
        fi, pclock_ms, sclock = line.split(",")
        tl.append((int(fi), float(pclock_ms) / 1000.0, float(sclock)))
    if len(tl) < 8:
        print("timeline too short (%d rows)" % len(tl))
        return 1
    tl.sort()

    # The page's frame clock is performance.now(), relative to page load. Its wall
    # epoch is recorded by the page itself (Date.now() at the same instant), which
    # makes a frame index placeable on the wall clock exactly.
    #
    # Without that, the only wall anchor is the server's receipt stamp, which lands
    # up to one POST interval (1 s) after the frame was displayed. That is a 1 s
    # error in absolute phase - harmless for the camera-to-camera difference, which
    # is common mode, and fatal for any absolute claim. Say so rather than hide it.
    wall_epoch = state.get("wall_epoch")
    exact = wall_epoch is not None
    if exact:
        disp_t = [wall_epoch + pc for _, pc, _ in tl]
    else:
        disp_t = [tl[0][2] + (pc - tl[0][1]) for _, pc, _ in tl]

    bits = sequence(seed, nframes + 2)
    # The page numbers its displayed frames from 1 (it increments before drawing),
    # and bit(seed, i) is the i-th step of the same LCG, so frame_index i is
    # sequence(seed)[i-1]. Off by one here is a whole display frame of error.
    disp_b = [bits[fi - 1] if 1 <= fi <= len(bits) else 0 for fi, _, _ in tl]

    D = (disp_t[-1] - disp_t[0]) / (len(disp_t) - 1)
    jit = [disp_t[i + 1] - disp_t[i] for i in range(len(disp_t) - 1)]
    print("  display intervals: mean %.6f s, min %.6f, max %.6f, sd %.6f"
          % (D, min(jit), max(jit), statistics.stdev(jit)))
    if not exact:
        print("  WARNING: the page did not report its wall-clock epoch, so the display")
        print("  timeline is anchored to POST receipt times, up to ~1 s late. The")
        print("  camera-to-camera offset below is unaffected; the absolute phase is not.")
    print("\ntarget: seed %d, %d displayed frames recorded, mean display period "
          "%.6f s (%.2f Hz)" % (seed, len(disp_t), D, 1.0 / D))
    print("        %d bright of %d" % (sum(disp_b), len(disp_b)))

    T = MONO_TICKS_PER_FRAME / TICK_HZ
    print("mono frame period from the device clock: %.6f s (%.4f fps)" % (T, 1.0 / T))
    if abs(T - D) > 0.0005:
        print("  NOTE: the cameras and the display are NOT locked (%.4f fps vs %.4f fps),"
              % (1.0 / T, 1.0 / D))
        print("  the relative phase drifts %.3f frames per second, which the fit absorbs."
              % abs(1.0 / T - 1.0 / D))

    print("\nSEQ MODE - exposure phase per camera")
    print("  fitting only frames inside the target window (plus %.1f s of slack):"
          " %.3f .. %.3f wall" % (SLACK, disp_t[0], disp_t[-1] + D))
    window = (disp_t[0], disp_t[-1] + D)
    fitted = {}
    for tag in sorted(by_tag):
        inside = [r for r in by_tag[tag]
                  if window[0] - SLACK <= r["host_wall"] <= window[1] + SLACK]
        if len(inside) < 12:
            print("  tag 0x%02x: only %d of %d frames fall inside the target window,"
                  " not fitting" % (tag, len(inside), len(by_tag[tag])))
            continue
        print("  tag 0x%02x: %d of %d frames inside the target window"
              % (tag, len(inside), len(by_tag[tag])))
        t_ref, rms, corr, lv, align, used, sigma = fit_phase(
            by_tag[tag], disp_t, disp_b, T, verbose, window)
        if t_ref is None:
            print("    no fit: this camera's brightness does not track the commanded"
                  " sequence (best correlation %.3f over %d frames). Either the screen"
                  " is not in its field of view, or the room's own brightness changes"
                  " are larger than the target's." % (align, used))
            continue
        fitted[tag] = (t_ref, rms, corr, sigma)
        phase = ((t_ref - disp_t[0]) % D) / D
        print("    exposure starts %.4f of a display frame after the display frame "
              "boundary (%.3f ms), rms %.2f counts, phase uncertainty %.3f ms"
              % (phase, phase * D * 1000.0, rms, sigma * 1000.0))

    tags = sorted(fitted)
    if len(tags) == 2:
        a, b = tags
        dt = fitted[a][0] - fitted[b][0]
        sdt = (fitted[a][3] ** 2 + fitted[b][3] ** 2) ** 0.5
        print("\nRESULT")
        print("  tag 0x%02x exposure starts %.3f ms %s tag 0x%02x's exposure"
              % (a, abs(dt) * 1000.0, "before" if dt < 0 else "after", b))
        print("  tag 0x%02x minus tag 0x%02x = %+.3f ms (%.4f display frames, %.4f mono frame periods)"
              % (a, b, dt * 1000.0, dt / D, dt / T))
        print("  uncertainty of that difference: +-%.3f ms (1 sigma, from the curvature"
              " of each fit)" % (sdt * 1000.0))
        print("  |offset| %.3f ms vs one mono frame period %.3f ms  ->  %.2f%% of a frame"
              % (abs(dt) * 1000.0, T * 1000.0, 100.0 * abs(dt) / T))
        if abs(dt) < 3 * sdt:
            print("  The offset is NOT distinguishable from zero: it is %.1f sigma."
                  % (abs(dt) / sdt if sdt > 0 else 0.0))
        else:
            print("  The offset is %.1f sigma from zero - that is a real skew, not noise."
                  % (abs(dt) / sdt))
        print("  rms of the two fits: %.2f / %.2f counts; correlation %.3f / %.3f"
              % (fitted[a][1], fitted[b][1], fitted[a][2], fitted[b][2]))
        if abs(dt) > 0.8 * T:
            print("  NOTE: the offset is close to a whole frame period. At that size the")
            print("  pair is not 'slightly skewed', it is one frame apart, and a pairing")
            print("  built on shared trailer timestamps would be pairing the wrong frames.")
        print("\n  This difference is common-mode safe: the monitor clock, this machine's")
        print("  clock and the device clock all shift both cameras identically.")
        print("  The absolute phases above are NOT - they depend on those offsets.")

        shutter_test(by_tag, fitted, disp_t, disp_b, T, h, window)
    else:
        print("\nRESULT: need both cameras fitted to get an offset.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
