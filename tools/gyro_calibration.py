#!/usr/bin/env python3
"""Final gyro calibration.

Input files are the capture from the coached session, which lives outside this
repo in the reverse-engineering scratch directory:
    /home/hermes/work/metavision/re/gyro_cal.csv     (meta2_imu_log output)
    /home/hermes/work/metavision/re/gyro_marks.txt   (gyro_coach.py output)
Run tools/gyro_coach.py to produce them. Results are written up in
docs/17-imu-calibration.md; the numbers below are what that document quotes.

A 360-degree turn about a fixed axis integrates to a vector whose MAGNITUDE is
360 degrees, whichever axis that was. So the scale comes from |SUM (c-bias) dt|,
not from picking the largest component - which was unstable because a standing
person's turn is never perfectly pure.
"""
import math

CSV = "/home/hermes/work/metavision/re/gyro_cal.csv"
MARKS = "/home/hermes/work/metavision/re/gyro_marks.txt"
TAGS = {119: "IMU0", 102: "IMU1"}
AXES = ("gx", "gy", "gz")

RGB_CADENCE = 3_927_221      # trailer ticks per RGB frame record  (docs/16)
MONO_CADENCE = 1_963_229     # trailer ticks per mono frame record (docs/16)


def load():
    rows = []
    with open(CSV) as f:
        for line in f:
            if line.startswith("#") or not line.strip():
                continue
            p = line.split(",")
            if len(p) < 10 or p[0] == "host_us":
                continue
            rows.append((int(p[0]), int(p[1]), TAGS.get(int(p[3]), p[3]),
                         int(p[4]), int(p[5]), int(p[6])))
    return rows


def marks():
    out = []
    for line in open(MARKS):
        if line.startswith("#") or not line.strip():
            continue
        p = line.split()
        out.append((p[0], p[1], int(p[2]), int(p[3])))
    return out


rows = load()
mk = marks()
print(f"rows={len(rows)}")

# ---- clock -----------------------------------------------------------------
print("\n=== device tick rate ===")
tick = {}
for tag in ("IMU0", "IMU1"):
    r = [x for x in rows if x[2] == tag]
    hs = (r[-1][0] - r[0][0]) / 1e6
    ts = r[-1][1] - r[0][1]
    tick[tag] = ts / hs
    print(f"  {tag}: host={hs:.3f}s  trailer span={ts}  -> {ts/hs:.6e} ticks/s")
print(f"  agreement between the two IMUs: "
      f"{abs(tick['IMU0']-tick['IMU1'])/tick['IMU0']*100:.4f} %")

print("\n=== what that rate makes the cameras ===")
t = (tick["IMU0"] + tick["IMU1"]) / 2
print(f"  RGB  cadence {RGB_CADENCE} ticks/frame -> {t/RGB_CADENCE:.4f} frames/s")
print(f"  mono cadence {MONO_CADENCE} ticks/frame -> {t/MONO_CADENCE:.4f} frames/s")
print(f"  RGB cadence / mono cadence = {RGB_CADENCE/MONO_CADENCE:.6f}")

# ---- bias ------------------------------------------------------------------
bias = {}
for tag in ("IMU0", "IMU1"):
    v = [[], [], []]
    for name, axis, a, b in mk:
        if not name.startswith("REST"):
            continue
        for r in rows:
            if a <= r[0] <= b and r[2] == tag:
                for i in range(3):
                    v[i].append(r[3 + i])
    bias[tag] = [sum(c) / len(c) for c in v]
    print(f"\n  {tag} gyro bias (n={len(v[0])}): " +
          " ".join(f"{AXES[i]}={bias[tag][i]:+.2f}" for i in range(3)))

# ---- one turn per window ---------------------------------------------------
print("\n=== each coached turn ===")
print(f"{'step':6s} {'axis':11s} {'tag':5s} {'gx_int':>9s} {'gy_int':>9s} {'gz_int':>9s}"
      f" {'|int|':>8s} {'deg/s per count':>16s}")
scales = []
for name, axis, a, b in mk:
    if name.startswith("REST"):
        continue
    pad = 400_000
    for tag in ("IMU0", "IMU1"):
        sel = [r for r in rows if a - pad <= r[0] <= b + pad and r[2] == tag]
        if not sel:
            continue
        integ = [0.0, 0.0, 0.0]
        for i in range(len(sel) - 1):
            dt = (sel[i + 1][0] - sel[i][0]) / 1e6
            for j in range(3):
                integ[j] += (sel[i][3 + j] - bias[tag][j]) * dt
        mag = math.sqrt(sum(x * x for x in integ))
        sc = 360.0 / mag
        scales.append((name, tag, mag, sc))
        print(f"{name:6s} {axis:11s} {tag:5s} " +
              " ".join(f"{integ[j]:9.1f}" for j in range(3)) +
              f" {mag:8.1f} {sc:16.6f}")

mags = sorted(x[2] for x in scales)
scs = sorted(x[3] for x in scales)
mean_sc = sum(scs) / len(scs)
print(f"\n  n={len(scs)} turn integrals: {mags[0]:.0f} .. {mags[-1]:.0f} "
      f"(spread {(mags[-1]-mags[0])/mags[0]*100:.1f} %)")
print(f"  scale: min={scs[0]:.6f} mean={mean_sc:.6f} max={scs[-1]:.6f} deg/s per count")
print(f"  counts per deg/s: {1/mean_sc:.3f}")
print(f"  counts at 100 deg/s: {100*mean_sc:.1f}")
print(f"  implied full-scale at i16 saturation: {32767*mean_sc:.1f} deg/s")
for fs in (1000, 2000, 2500):
    print(f"    if full scale is +/-{fs} deg/s: {fs/32768:.6f} deg/s per count "
          f"-> measured is {(mean_sc - fs/32768)/(fs/32768)*100:+.2f} % off")

# ---- axis mapping between the two IMUs ------------------------------------
print("\n=== axis/sign relationship between IMU0 and IMU1 ===")
for name, axis, a, b in mk:
    if name.startswith("REST"):
        continue
    pad = 400_000
    vec = {}
    for tag in ("IMU0", "IMU1"):
        sel = [r for r in rows if a - pad <= r[0] <= b + pad and r[2] == tag]
        integ = [0.0, 0.0, 0.0]
        for i in range(len(sel) - 1):
            dt = (sel[i + 1][0] - sel[i][0]) / 1e6
            for j in range(3):
                integ[j] += (sel[i][3 + j] - bias[tag][j]) * dt
        vec[tag] = integ
    a0, a1 = vec["IMU0"], vec["IMU1"]
    n0 = math.sqrt(sum(x * x for x in a0))
    n1 = math.sqrt(sum(x * x for x in a1))
    dot = sum(a0[j] * a1[j] for j in range(3)) / (n0 * n1)
    print(f"  {name:6s} ({axis:11s}) cos angle between IMU0 and IMU1 turn vectors = {dot:+.3f}")
