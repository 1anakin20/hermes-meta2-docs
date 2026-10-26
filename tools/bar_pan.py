#!/usr/bin/env python3
"""Measure the readout time of the mono sensors by panning the headset.

    bar_pan.py <capture_prefix>            # analyse a real capture
    bar_pan.py --selftest                  # prove it recovers a known readout time

Why this test and not the flashing screen: a rolling shutter's signature is the time
difference between the first row exposing and the last row exposing. To see it,
something has to change FASTER than the readout. A 60 Hz display changes at the same
rate the sensor reads out, so its transitions land as a ramp across the whole frame
(see docs/15). A pan does not have that problem: the shear it produces is
readout_time x pan_rate, and it is a GEOMETRIC effect, so it survives being blurred.

What to do physically: stand about 2 m from something with straight vertical edges
(a door frame, a bookshelf, window mullions), in as bright a room as you can get,
and pan the headset side to side a few times, briskly, then hold still. Record with

    ./build/meta2_mono_bar /home/hermes/work/metavision/re/pan1 20 gate=10 raw imu=/home/hermes/work/metavision/re/pan1.imu.csv

How it works: for every frame, the sub-pixel column position of the strongest vertical
edge is measured row by row, and the slope of that position against row is fitted.
A static scene has a slope too - the fisheye bends a straight vertical line - so the
slope measured while holding still is subtracted from the slope measured while turning.
What is left is the shear, and shear = readout x pan_rate x pixels-per-degree.

--selftest generates frames with a KNOWN readout time, blurs them by the exposure,
adds noise, and checks the recovery. Run it before believing a real result.
"""
import math, os, struct, sys, statistics

W, H = 752, 480
FRAME_BYTES = W * H * 2
GYRO_DEG_PER_COUNT = 0.0613          # docs/17, measured over a 400 s coached session
PX_PER_DEG = W / 182.4                 # 182.4 deg of horizontal FOV across 752 px = 4.12 px/deg
TICK_HZ = 117821900.0


# ---------------------------------------------------------------- measurement

def edge_slope(frame, c0, c1):
    """Sub-pixel column of the vertical edge, per row, then the slope of that column
    against the row number. Returns (slope, n_rows_used).

    The estimate is the thresholded CENTROID of the horizontal gradient across the band,
    not the location of the biggest gradient. A peak location carries one column's worth
    of information and jitters by whole pixels; a centroid averages the whole edge
    profile. Two details matter and both were found by the selftest failing without them:
    the row is box-smoothed before differencing, and only columns above 30% of the band's
    strongest gradient are counted. Without the threshold the photometric noise across the
    flat parts of the band outweighs the edge and pins the centroid to the middle of the
    band no matter where the edge is - the slope came out 0.0005 instead of 0.0200.

    It assumes the band holds ONE dominant edge: point it at a single door frame rather
    than a busy shelf, or pass --band= to pick a quieter span.
    """
    pos = []
    for r in range(24, H - 24):
        row = frame[r]
        sm = [(row[c - 2] + row[c - 1] + row[c] + row[c + 1] + row[c + 2]) / 5.0
              for c in range(c0 - 2, c1 + 3)]
        g = [sm[x + 3] - sm[x + 1] for x in range(c1 - c0 + 1)]
        mx = max(abs(x) for x in g)
        if mx < 3.0:
            continue
        thr = 0.30 * mx
        wsum = acc = 0.0
        for x, v in enumerate(g):
            a = abs(v)
            if a < thr:
                continue
            wsum += a
            acc += a * (c0 + x)
        if wsum <= 0:
            continue
        pos.append((r, acc / wsum))
    n = len(pos)
    if n < 60:
        return None, n
    mx_r = sum(q[0] for q in pos) / n
    my = sum(q[1] for q in pos) / n
    sxx = sum((q[0] - mx_r) ** 2 for q in pos)
    if sxx == 0:
        return None, n
    return sum((q[0] - mx_r) * (q[1] - my) for q in pos) / sxx, n


def load_raw(prefix):
    rows = []
    for line in open(prefix + ".csv"):
        if line.startswith("#") or line.startswith("host_us"):
            continue
        p = line.rstrip("\n").split(",")
        if len(p) < 6:
            continue
        rows.append({"host_us": int(p[0]), "ts": int(p[1]), "tag": int(p[3]),
                     "mean": float(p[5])})
    raw = prefix + ".raw"
    n = os.path.getsize(raw) // FRAME_BYTES
    out = []
    with open(raw, "rb") as f:
        for i in range(n):
            b = f.read(FRAME_BYTES)
            u = struct.unpack("<%dH" % (W * H), b)
            out.append((rows[i], [list(u[r * W:(r + 1) * W]) for r in range(H)]))
    return out


def load_imu(path):
    out = []
    for line in open(path):
        if line.startswith("#") or line.startswith("host_us"):
            continue
        p = line.rstrip("\n").split(",")
        if len(p) < 12:
            continue
        out.append((int(p[0]), int(p[1]), int(p[3]),
                    (int(p[5]), int(p[6]), int(p[7]))))
    return out


def rate_at(imu, host_us, half_us=60000):
    """Peak angular rate in deg/s over a +-60 ms window around host_us."""
    lo, hi = host_us - half_us, host_us + half_us
    best = 0.0
    for h, ts, tag, g in imu:
        if lo <= h <= hi:
            m = math.sqrt(g[0] ** 2 + g[1] ** 2 + g[2] ** 2) * GYRO_DEG_PER_COUNT
            if m > best:
                best = m
    return best


# ---------------------------------------------------------------- selftest

def selftest():
    import random
    rnd = random.Random(4)
    print("synthetic: a vertical edge, a static fisheye bend of 0.020 px/row, blur from")
    print("the exposure, noise 8 counts, and a KNOWN readout time. Pixels of shear")
    print("across the 480-row frame = readout x pan_rate x %.2f px/deg.\n" % PX_PER_DEG)
    # The method has an operating range and the selftest states it rather than
    # pretending otherwise. It recovers the readout time exactly when the exposure is
    # short compared with it and the scene is bright. It does not work when the exposure
    # is comparable to the readout, because motion blur during each row's own exposure is
    # then the same size as the shear between rows and attenuates it (16.66 ms exposure at
    # 120 deg/s: 8.2 px of blur against 8.2 px of shear, recovered 10.3 ms instead of
    # 16.7). It also stops working when photometric noise approaches the edge's own
    # gradient. Those are not bugs to tune away; they are the limits of what a moving
    # camera can tell you, and a real run has to be judged against them.
    cases = [
        # readout_ms, pan_deg_s, exposure_ms, noise_counts, in_range
        (16.66, 120.0, 2.0, 8.0, True),
        (8.0, 120.0, 2.0, 8.0, True),
        (0.0, 120.0, 2.0, 8.0, True),
        (16.66, 40.0, 2.0, 8.0, True),
        (2.0, 120.0, 2.0, 8.0, True),
        (16.66, 120.0, 16.66, 8.0, False),   # exposure == readout: attenuated
        (16.66, 200.0, 16.66, 8.0, False),   # ditto, worse
        (16.66, 120.0, 2.0, 40.0, False),    # noise-dominated
    ]
    ok_all = True
    for readout_ms, pan_deg_s, exposure_ms, noise, in_range in cases:
        static_slope = 0.020
        shear = (readout_ms / 1000.0) * pan_deg_s * PX_PER_DEG / H   # px per row
        frames = []
        for k in range(40):
            turning = (k % 3) != 0                                    # 2/3 turning, 1/3 still
            w = pan_deg_s if turning else 0.0
            s = static_slope + ((readout_ms / 1000.0) * w * PX_PER_DEG / H)
            blur = max(0.5, (exposure_ms / 1000.0) * w * PX_PER_DEG)
            fr = []
            for r in range(H):
                centre = 300 + s * r
                row = []
                for c in range(140, 470):
                    # erf-ish edge blurred over `blur` pixels
                    x = max(-40.0, min(40.0, (c - centre) / (blur * 0.6)))
                    v = 200.0 / (1.0 + math.exp(-x))
                    row.append(v + rnd.gauss(0.0, noise))
                # edge_slope indexes absolute columns, so pad the generated band out
                fr.append([0.0] * 140 + row)
            frames.append(({"host_us": k * 16663, "tag": 0x44, "mean": 0.0,
                            "rate": w}, fr))
        still = [edge_slope(f, 150, 450)[0] for _, f in frames
                 if _["rate"] < 1.0 and edge_slope(f, 150, 450)[0] is not None]
        turn = [edge_slope(f, 150, 450)[0] for _, f in frames
                if _["rate"] > 1.0 and edge_slope(f, 150, 450)[0] is not None]
        ds = statistics.median(turn) - statistics.median(still)
        got_ms = ds * H / (pan_deg_s * PX_PER_DEG) * 1000.0 if pan_deg_s else 0.0
        err = got_ms - readout_ms
        good = abs(err) < 2.0
        if in_range:
            ok_all = ok_all and good
        label = ("OK" if good else "FAIL") if in_range else (
            "outside the range, as documented" if not good else "in range after all")
        print("  readout %6.2f ms, pan %5.1f deg/s, exposure %5.2f ms, noise %4.1f counts:"
              "  shear %5.2f px over the frame -> recovered %6.2f ms  error %+5.2f ms  %s"
              % (readout_ms, pan_deg_s, exposure_ms, noise, shear * H, got_ms, err, label))
    print("\n%s" % ("the pan test recovers the readout time it is given, inside its stated range"
                    if ok_all else "SELFTEST FAILED inside its own range - do not run this on real data yet"))
    return 0 if ok_all else 1


# ---------------------------------------------------------------- real run

def main():
    argv = sys.argv[1:]
    if not argv:
        print(__doc__)
        return 2
    if argv[0] == "--selftest":
        return selftest()
    prefix = argv[0]
    c0, c1 = 150, 450
    for a in argv[1:]:
        if a.startswith("--band="):
            c0, c1 = (int(x) for x in a[7:].split(","))
    imu_path = prefix + ".imu.csv"
    if not os.path.exists(prefix + ".raw"):
        print("%s.raw missing - record with the recorder's `raw` option" % prefix)
        return 2
    if not os.path.exists(imu_path):
        print("%s missing - record with imu=%s" % (imu_path, imu_path))
        return 2
    frames = load_raw(prefix)
    imu = load_imu(imu_path)
    print("%d frames, %d IMU samples" % (len(frames), len(imu)))
    still, turn = [], []
    for meta, fr in frames:
        sl, n = edge_slope(fr, c0, c1)
        if sl is None:
            continue
        w = rate_at(imu, meta["host_us"])
        (turn if w > 40.0 else still if w < 10.0 else []).append((sl, w))
    print("%d frames while turning (>40 deg/s), %d while still (<10 deg/s)"
          % (len(turn), len(still)))
    if len(turn) < 10 or len(still) < 10:
        print("not enough frames in both groups. Pan briskly a few times, then hold still.")
        return 1
    s_still = statistics.median(x[0] for x in still)
    s_turn = statistics.median(x[0] for x in turn)
    w_turn = statistics.median(x[1] for x in turn)
    ds = s_turn - s_still
    print("  edge slope while still  : %+.4f px/row  (this is the fisheye bending the line)" % s_still)
    print("  edge slope while turning: %+.4f px/row" % s_turn)
    print("  median pan rate         : %.1f deg/s" % w_turn)
    print("  extra shear             : %+.2f px across the whole frame height" % (ds * H))
    readout_ms = ds * H / (w_turn * PX_PER_DEG) * 1000.0
    print("\n  implied readout time    : %.2f ms  (%.4f of one 16.663 ms frame period)"
          % (readout_ms, readout_ms / 16.663))
    if abs(readout_ms) < 2.0:
        print("  -> GLOBAL SHUTTER: no measurable row-time skew.")
    elif readout_ms > 8.0:
        print("  -> ROLLING SHUTTER: rows expose over %.1f ms, which is a real skew for"
              " tracking and has to be modelled." % readout_ms)
    else:
        print("  -> partial skew; the number is small enough that the label matters less"
              " than the measurement.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
