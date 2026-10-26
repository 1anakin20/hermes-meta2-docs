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
import struct
import sys

TICK_HZ = 117821900.0          # docs/17: calibrated from a 400 s coached session
MONO_TICKS_PER_FRAME = 1963229.0   # docs/16: measured mono cadence
MONO_FPS = TICK_HZ / MONO_TICKS_PER_FRAME

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


def fit_phase(frames, disp_t, disp_b, T, verbose=False):
    """Search the exposure phase that best explains this camera's brightness
    sequence. Returns (t_ref, rms, corr, levels)."""
    levels = [r["mean"] for r in frames]
    lo = min(levels)
    hi = max(levels)
    # Robust bright/dark levels: the sequence is random, so the 10th/90th
    # percentiles are well populated, and a single blown-out frame cannot move them.
    s = sorted(levels)
    L0 = s[max(0, int(0.10 * (len(s) - 1)))]
    L1 = s[min(len(s) - 1, int(0.90 * (len(s) - 1)))]
    if L1 - L0 <= 1e-9:
        return None, 0.0, 0.0, (lo, hi), 0.0

    D = disp_t[1] - disp_t[0]
    n = len(disp_t)

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

    max_shift = 200
    best_s, best_score = None, -1.0
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
        if score > best_score:
            best_score, best_s = score, sh
    if best_s is None or best_score < 0.40:
        # Below this the camera is not tracking the target: the screen is not in
        # view, or the scene's own brightness changes are drowning the target.
        return None, 0.0, 0.0, (L0, L1), best_score
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
    m = sum(levels) / len(levels)
    mp = sum(p) / len(p)
    num = sum((levels[i] - m) * (p[i] - mp) for i in range(len(levels)))
    den = (sum((v - m) ** 2 for v in levels) * sum((v - mp) ** 2 for v in p)) ** 0.5
    corr = num / den if den > 0 else 0.0
    if verbose:
        print("    levels %.1f..%.1f  fitted L0=%.1f L1=%.1f  rms=%.2f  corr=%.3f"
              % (lo, hi, L0, L1, rms, corr))
    return t_ref, rms, corr, (L0, L1), best_score


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
    prefix = sys.argv[1]
    coach = "/home/hermes/work/metavision/re"
    mode = None
    verbose = "--verbose" in sys.argv
    for a in sys.argv[2:]:
        if a.startswith("--coach-dir="):
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
    fitted = {}
    for tag in sorted(by_tag):
        if len(by_tag[tag]) < 12:
            print("  tag 0x%02x: only %d frames, not fitting" % (tag, len(by_tag[tag])))
            continue
        print("  tag 0x%02x:" % tag)
        t_ref, rms, corr, lv, align = fit_phase(by_tag[tag], disp_t, disp_b, T, verbose)
        if t_ref is None:
            print("    no fit: this camera's brightness does not track the commanded"
                  " sequence (best correlation %.3f). The screen is not in its field of"
                  " view, or the scene's own brightness changes are larger than the"
                  " target's." % align)
            continue
        fitted[tag] = (t_ref, rms, corr)
        phase = ((t_ref - disp_t[0]) % D) / D
        print("    exposure starts %.4f of a display frame after the display frame "
              "boundary (%.3f ms), rms %.2f counts" % (phase, phase * D * 1000.0, rms))

    tags = sorted(fitted)
    if len(tags) == 2:
        a, b = tags
        dt = fitted[a][0] - fitted[b][0]
        print("\nRESULT")
        print("  tag 0x%02x exposure starts %.3f ms %s tag 0x%02x's exposure"
              % (a, abs(dt) * 1000.0, "before" if dt < 0 else "after", b))
        print("  tag 0x%02x minus tag 0x%02x = %+.3f ms (%.4f display frames, %.4f mono frame periods)"
              % (a, b, dt * 1000.0, dt / D, dt / T))
        print("  |offset| %.3f ms vs one mono frame period %.3f ms" % (abs(dt) * 1000.0, T * 1000.0))
        print("  rms of the two fits: %.2f / %.2f counts; correlation %.3f / %.3f"
              % (fitted[a][1], fitted[b][1], fitted[a][2], fitted[b][2]))
        if abs(dt) > 0.8 * T:
            print("  NOTE: the offset is close to a whole frame period. At that size the")
            print("  pair is not 'slightly skewed', it is one frame apart, and a pairing")
            print("  built on shared trailer timestamps would be pairing the wrong frames.")
        print("\n  This difference is common-mode safe: the monitor clock, this machine's")
        print("  clock and the device clock all shift both cameras identically.")
        print("  The absolute phases above are NOT - they depend on those offsets.")
    else:
        print("\nRESULT: need both cameras fitted to get an offset.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
