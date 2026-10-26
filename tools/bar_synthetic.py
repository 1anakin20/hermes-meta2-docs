#!/usr/bin/env python3
"""Prove bar_offset.py can actually recover an exposure offset, before trusting it
on a real capture.

Generates a synthetic capture with a KNOWN offset between the two cameras - same
binary layout as examples/meta2_mono_bar, same page timeline format as
bar_coach.py - then runs the analysis on it and compares what it reports against
what was put in.

Nothing here is a claim about the device. It is a check that the estimator is
capable of measuring the quantity the experiment asks for, at the resolution the
experiment needs. If the estimator cannot recover a 2 ms offset from clean data,
then a null result on the real headset would mean nothing.
"""

import json
import os
import struct
import subprocess
import sys

TICK_HZ = 117821900.0
MONO_TICKS = 1963229.0
T = MONO_TICKS / TICK_HZ
MONO_H, MONO_W = 480, 752
LCG_A, LCG_C = 1103515245, 12345


def sequence(seed, n):
    x = seed & 0xFFFFFFFF
    out = []
    for _ in range(n):
        x = (LCG_A * x + LCG_C) & 0xFFFFFFFF
        out.append((x >> 16) & 1)
    return out


def bright_fraction(t0, bits, disp_t, D):
    """Fraction of [t0, t0+T] that fell on a bright display interval."""
    a, b = t0, t0 + T
    acc = span = 0.0
    j = max(0, int((a - disp_t[0]) // D) - 2)
    while j < len(disp_t):
        s0 = disp_t[j]
        s1 = disp_t[j + 1] if j + 1 < len(disp_t) else disp_t[-1] + (j + 1) * D
        if s0 >= b:
            break
        ov = min(b, s1) - max(a, s0)
        if ov > 0:
            acc += ov * bits[j]
            span += ov
        j += 1
    if span <= 0:
        return None
    return acc / span


def footprint(H):
    """The monitor does not fill the recorder's column band evenly, and a synthetic
    capture that ignores that lets the shutter test pass for the wrong reason: a flat
    profile is trivially consistent with a global shutter. This gives the target a
    shape, so "same shape every frame" has to be earned."""
    f = []
    for i in range(H):
        if 120 <= i <= 380:
            v = 1.0
        elif i < 120:
            v = 0.30 + 0.70 * i / 120.0
        else:
            v = 1.0 - 0.70 * (i - 380) / float(H - 380)
        m = sum(f) / H if f else 1.0
        f.append(v)
    m = sum(f) / H
    return [x / m for x in f]


def make_run(dirpath, prefix, seed, dt, nframes=1200, page_fps=59.94,
             drain_lag=0.030, L0=45.0, L1=180.0, noise=1.5, wall_epoch=0.0,
             drop=0.0, seed_rng=7, roll=0.0):
    os.makedirs(dirpath, exist_ok=True)
    D = 1.0 / page_fps
    disp_t = [i * D for i in range(nframes)]
    bits = sequence(seed, nframes)

    t_exp_left = 0.0040                 # arbitrary absolute phase
    t_exp_right = t_exp_left + dt      # the truth

    # Device clock epoch, and the wall<->monotonic anchor the real tool prints.
    ts0 = 40_000_000_000
    real_off = 1_793_021_083.828669
    mono0 = 3151.976183

    rec = struct.Struct("<qQIBBd")
    rows = struct.Struct("<%df" % MONO_H)
    prof = open(os.path.join(dirpath, prefix + ".prof"), "wb")
    prof.write(b"M2BP")
    prof.write(struct.pack("<IIIII", 1, MONO_H, 64, 552, 202))

    csv = open(os.path.join(dirpath, prefix + ".csv"), "w")
    csv.write("# synthetic\n")
    csv.write("# anchor realtime=%.6f monotonic=%.6f\n" % (real_off + mono0, mono0))
    csv.write("host_us,trailer_ts,packet,tag,has_trailer,mean,peak_row,peak_val,rows_above_half\n")

    tl = open(os.path.join(dirpath, "bar_timeline.csv"), "w")
    tl.write("# frame_index,page_clock_ms,server_clock_s\n")

    import random
    rnd = random.Random(seed_rng)
    keep = random.Random(seed_rng + 1)
    truth = {}
    for k in range(nframes):
        # The device truncates frame records rather than stalling, so a real capture
        # is missing slots. The frame index comes from the trailer timestamp, so a
        # missing slot must not shift every later frame - this is the case that
        # behaviour exists, and it is tested rather than assumed.
        if drop and keep.random() < drop:
            continue
        for tag, t_exp in ((0x44, t_exp_left), (0x55, t_exp_right)):
            f = bright_fraction(t_exp + k * T, bits, disp_t, D)
            if f is None:
                continue
            # roll is the readout time as a fraction of the frame period. roll=0 is a
            # global shutter: every row integrates the same window. roll=1 staggers the
            # row start times across a whole frame, which is what a rolling sensor does,
            # and it turns a straddling frame into a horizontal step.
            foot = footprint(MONO_H)
            rowvals = []
            for i in range(MONO_H):
                if roll > 0.0:
                    fi = bright_fraction(t_exp + k * T + (i / MONO_H) * roll * T,
                                         bits, disp_t, D)
                    if fi is None:
                        fi = f
                else:
                    fi = f
                rowvals.append((L0 + (L1 - L0) * fi) * foot[i] + rnd.gauss(0.0, noise))
            level = sum(rowvals) / MONO_H
            wall = disp_t[0] + k * T + drain_lag      # drain happens after exposure
            host_us = int((wall - real_off) * 1e6)
            ts = ts0 + k * int(MONO_TICKS)
            prof.write(rec.pack(host_us, ts, 1000 + k, tag, 1, level))
            prof.write(rows.pack(*rowvals))
            csv.write("%d,%d,%d,%d,1,%.4f,%d,%.1f,%d\n"
                    % (host_us, ts, 1000 + k, tag, level, 240, level, 1))
            truth[tag] = t_exp
    prof.close(); csv.close()

    # The page posts its frame buffer once a second, so the server receipt stamp is
    # up to one POST interval after the frame was displayed. The analysis has to
    # live with that, and the offset must survive it.
    for i, t in enumerate(disp_t):
        receipt = t + (i % 60) * 0.0167 + 0.5
        tl.write("%d,%.3f,%.6f\n" % (i + 1, t * 1000.0, receipt))
    tl.close()

    st = {"phase": "done", "mode": "seq", "seed": seed, "frames": nframes,
          "page_fps": page_fps, "screen_h": 1080, "seconds": nframes / page_fps}
    if wall_epoch is not None:
        # What the page reports once it records Date.now() alongside performance.now().
        st["wall_epoch"] = wall_epoch
    json.dump(st, open(os.path.join(dirpath, "bar_state.json"), "w"), indent=1)
    return truth


def main():
    base = "/home/hermes/work/scratch/synth"
    script = "/home/hermes/work/scratch/bar_offset.py"
    print("mono frame period T = %.6f s (%.4f fps); display period %.6f s"
          % (T, 1.0 / T, 1.0 / 59.94))
    print("one mono frame period = %.3f ms\n" % (T * 1000))

    cases = [(0.0, 0.0), (0.002, 0.0), (0.004, 0.0), (0.008331, 0.0),
             (0.012, 0.0), (-0.006, 0.0),
             # The page's wall epoch is the good anchor. These cases withhold it so
             # the analysis has to fall back on POST receipt times, which land up to
             # a second after the frame was displayed, and still get the offset right.
             (0.003, None), (-0.009, None),
             # Real device conditions: 25% of frame records truncated, and a noisier
             # photometry than the clean cases.
             (0.005, 0.0, 0.25, 6.0),
             (-0.005, 0.0, 0.25, 6.0),
             # Shutter-model cases: the same target, one with rows staggered across a
             # whole frame. The shutter test has to tell these apart, or its verdict on
             # a real capture means nothing.
             (0.004, 0.0, 0.0, 1.5, 0.0),
             (0.004, 0.0, 0.0, 1.5, 1.0)]
    all_ok = True
    for case in cases:
        dt, epoch = case[0], case[1]
        drop = case[2] if len(case) > 2 else 0.0
        noise = case[3] if len(case) > 3 else 1.5
        roll = case[4] if len(case) > 4 else 0.0
        d = os.path.join(base, "dt%d_%s_drop%d_roll%d" % (int(dt * 1e6),
                                                          "exact" if epoch is not None else "receipt",
                                                          int(drop * 100), int(roll)))
        seed = 12345 + int(abs(dt) * 1e6) + int(roll * 7)
        make_run(d, "cap", seed, dt, wall_epoch=epoch, drop=drop, noise=noise, roll=roll)
        out = subprocess.run([sys.executable, script, os.path.join(d, "cap"),
                              "--coach-dir=" + d],
                             capture_output=True, text=True).stdout
        got = None
        verdicts = []
        cons_log = []
        for line in out.splitlines():
            if line.strip().startswith("tag 0x44 minus tag 0x55 ="):
                got = float(line.split("=")[1].split("ms")[0]) / 1000.0
            if line.strip().startswith("-> GLOBAL:"):
                verdicts.append("global")
            elif line.strip().startswith("-> ROLLING:"):
                verdicts.append("rolling")
            elif line.strip().startswith("-> INCONCLUSIVE:"):
                verdicts.append("inconclusive")
            elif "shape consistency across straddling frames" in line:
                cons_log.append(line.strip())
        # Both cameras must agree, or it is not a verdict.
        verdict = verdicts[0] if (verdicts and len(set(verdicts)) == 1) else (
            "mixed" if verdicts else None)
        want = "global" if roll == 0.0 else "rolling"
        shutter_ok = (verdict == want)
        # The analysis reports left minus right. The generator sets
        # right = left + dt, so the expected answer is -dt.
        expect = -dt
        err = None if got is None else got - expect
        ok = got is not None and abs(err) < 0.0005 and shutter_ok
        all_ok = all_ok and ok
        print("truth right-minus-left = %+7.3f ms  anchor=%-19s  reported left-minus-right = %s   error = %s   %s"
              % (dt * 1000,
                 "%s drop%d noise%.1f roll%.1f" % ("exact" if epoch is not None else "receipt",
                                           int(drop * 100), noise, roll),
                 "n/a" if got is None else "%+7.3f ms" % (got * 1000),
                 "n/a" if err is None else "%+6.3f ms" % (err * 1000),
                 "shutter=%s(want %s) %s" % (verdict, want, "OK" if ok else "FAIL")))
        if not ok:
            print("      " + "\n      ".join(cons_log))
        if got is None:
            print(out[-1200:])
    print("\n%s" % ("estimator recovers offsets to well under half a millisecond"
                    if all_ok else "ESTIMATOR FAILED ITS OWN TEST - do not trust a null result"))
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
