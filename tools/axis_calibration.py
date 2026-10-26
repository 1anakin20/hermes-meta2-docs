#!/usr/bin/env python3
"""Accelerometer axis map from the six coached gravity poses.

Input is the coached session, which lives outside this repo in the
reverse-engineering scratch directory:
    /home/hermes/work/metavision/re/axis_poses.json   (axis_coach.py output:
        per-pose mean ax/ay/az for each IMU, in pose order Z+ Z- Y+ Y- X+ X-)
Run tools/axis_coach.py to produce it; it also graphs the live samples so each
pose can be confirmed before moving on. Results are written up in
docs/18-imu-axis-map.md; the numbers there are what this prints.

Six poses over-determine three axes, so the fit can grade itself. The grading is
four checks and `--selftest` shows each one firing on synthetic data.

At rest the accelerometer reads +1 g along whichever axis points up:
    m = k * R * u + b
Opposite poses are differenced, which cancels b exactly:
    k * R[:,j] = (m(+e_j) - m(-e_j)) / 2
"""
import math
import sys

POSES = [("Z+", (0, 0, 1)), ("Z-", (0, 0, -1)), ("Y+", (0, 1, 0)),
         ("Y-", (0, -1, 0)), ("X+", (1, 0, 0)), ("X-", (-1, 0, 0))]
PAIRS = [("X+", "X-"), ("Y+", "Y-"), ("Z+", "Z-")]
HNAMES = ("X forward", "Y wearer's-left", "Z up")
SNAMES = ("ax", "ay", "az")
RAW = "/home/hermes/work/metavision/re/axis_poses.json"


def load(path=RAW):
    import json
    with open(path) as f:
        raw = json.load(f)
    by_id = {}
    for r in raw:
        by_id[r[0]] = (tuple(r[2]), tuple(r[4]))
    return by_id


def fit(by_id):
    out = {}
    for ti, tag in enumerate(("IMU0", "IMU1")):
        C = [[0.0] * 3 for _ in range(3)]     # C[i][j] = k * R[i][j]
        B = [[0.0] * 3 for _ in range(3)]
        for j, (pa, pb) in enumerate(PAIRS):
            ma, mb = by_id[pa][ti], by_id[pb][ti]
            for i in range(3):
                C[i][j] = (ma[i] - mb[i]) / 2.0
                B[i][j] = (ma[i] + mb[i]) / 2.0
        col = [math.sqrt(sum(C[i][j] ** 2 for i in range(3))) for j in range(3)]
        k = sum(col) / 3.0
        R = [[C[i][j] / k for j in range(3)] for i in range(3)]
        bias = [sum(B[i][j] for j in range(3)) / 3.0 for i in range(3)]
        det = (R[0][0] * (R[1][1] * R[2][2] - R[1][2] * R[2][1])
               - R[0][1] * (R[1][0] * R[2][2] - R[1][2] * R[2][0])
               + R[0][2] * (R[1][0] * R[2][1] - R[1][1] * R[2][0]))
        angles = {}
        for x in range(3):
            for y in range(x + 1, 3):
                d = sum(C[i][x] * C[i][y] for i in range(3)) / (col[x] * col[y])
                angles[(x, y)] = math.degrees(math.acos(max(-1.0, min(1.0, d))))
        mag_net = []
        for pid, _ in POSES:
            m = by_id[pid][ti]
            mag_net.append(math.sqrt(sum((m[i] - bias[i]) ** 2 for i in range(3))))
        out[tag] = {"k": k, "R": R, "C": C, "bias": bias, "col": col, "det": det,
                    "angles": angles, "mag_net": mag_net}
    return out


def grade(a):
    """Four checks. None of them assumes the sensor axes line up with the headset
    axes - the chips turned out to be mounted ~45 deg off, and a test that assumes
    axis alignment fails good data (docs/18 §18.6)."""
    lines = []
    ok_all = True
    for tag in ("IMU0", "IMU1"):
        d = a[tag]
        coldev = max(abs(c - d["k"]) / d["k"] for c in d["col"])
        angdev = max(abs(90.0 - v) for v in d["angles"].values())
        magdev = max(abs(m - d["k"]) / d["k"] for m in d["mag_net"])
        detdev = abs(d["det"] - 1.0)
        ok = coldev < 0.04 and angdev < 10.0 and magdev < 0.05 and detdev < 0.15
        ok_all = ok_all and ok
        lines.append("%s: %s  1g agrees to %.1f%%, worst angle %.1f deg off 90, "
                     "|a| to %.1f%% after bias removal, det %+.3f"
                     % (tag, "CONSISTENT" if ok else "INCONSISTENT",
                        coldev * 100, angdev, magdev * 100, d["det"]))
    return ok_all, lines


def report(a):
    for tag in ("IMU0", "IMU1"):
        d = a[tag]
        print("%s: k = %.1f counts/g   det(R) = %+.3f" % (tag, d["k"], d["det"]))
        print("  bias " + "  ".join("%s=%+.1f" % (SNAMES[i], d["bias"][i]) for i in range(3))
              + "   |b| = %.0f counts = %.3f g"
              % (math.sqrt(sum(x * x for x in d["bias"])),
                 math.sqrt(sum(x * x for x in d["bias"])) / d["k"]))
        for j in range(3):
            v = [d["C"][i][j] / d["col"][j] for i in range(3)]
            print("  headset %-16s -> sensor %s   (%.1f counts, should be %.1f)"
                  % (HNAMES[j], " ".join("%s=%+.3f" % (SNAMES[i], v[i]) for i in range(3)),
                     d["col"][j], d["k"]))
        for i in range(3):
            row = d["R"][i]
            n = math.sqrt(sum(x * x for x in row))
            ang = [math.degrees(math.acos(max(-1.0, min(1.0, row[j] / n)))) for j in range(3)]
            print("  %-3s in headset frame: %s  norm %.3f  angles to %s: %s"
                  % (SNAMES[i], " ".join("%+.3f %s" % (row[j], HNAMES[j][0]) for j in range(3)),
                     n, "/".join(HNAMES), " ".join("%.0f deg" % x for x in ang)))
        print()
    print(grade(a)[1][0])
    print(grade(a)[1][1])


# --------------------------------------------------------------------------
# selftest: does the grading actually catch the mistakes it is supposed to catch
# --------------------------------------------------------------------------
K = 16384.0
# The mount this device actually turned out to have, so the clean case is a
# 45-degree mount and not the axis-aligned one the first version of this test used.
TRUTH = [
    {"R": [[-0.707, -0.707, 0.000], [0.160, -0.160, 0.973], [-0.691, 0.691, 0.205]],
     "bias": [-965.0, 94.0, 296.0]},
    {"R": [[-0.707, 0.707, 0.000], [0.160, 0.160, -0.973], [-0.691, -0.691, -0.205]],
     "bias": [88.0, 243.0, -280.0]},
]
for t in TRUTH:
    for i in range(3):
        n = math.sqrt(sum(x * x for x in t["R"][i]))
        t["R"][i] = [x / n for x in t["R"][i]]


def synth():
    by_id = {}
    for pid, up in POSES:
        means = []
        for t in TRUTH:
            means.append(tuple(sum(t["R"][i][j] * up[j] for j in range(3)) * K + t["bias"][i]
                               for i in range(3)))
        by_id[pid] = (means[0], means[1])
    return by_id


def selftest():
    def run(label, by_id, expect):
        ok, lines = grade(fit(by_id))
        print("%-40s %-12s (expected %s)  %s"
              % (label, "CONSISTENT" if ok else "INCONSISTENT", expect, lines[0]))
        assert ok == expect, label

    base = synth()
    run("clean 45 deg canted mount", base, True)

    swapped = dict(base)
    swapped["Y+"] = (base["Y-"][0], base["Y-"][1])
    swapped["Y-"] = (base["Y+"][0], base["Y+"][1])
    run("the two Y poses recorded swapped", swapped, False)

    mis = dict(base)
    mis["Y+"] = (base["X+"][0], base["X+"][1])
    mis["X+"] = (base["Y+"][0], base["Y+"][1])
    run("X+ pose recorded as Y+", mis, False)

    bad = dict(base)
    bad["Z+"] = ((base["Z+"][0][0] + 800.0, base["Z+"][0][1], base["Z+"][0][2]), base["Z+"][1])
    run("one pose contaminated (+800 counts)", bad, True)   # differencing absorbs it

    d = fit(base)["IMU0"]
    for i in range(3):
        got = d["R"][i]
        want = TRUTH[0]["R"][i]
        err = max(abs(got[j] - want[j]) for j in range(3))
        assert err < 0.002, (i, got, want)
    assert abs(d["k"] - K) < 2.0
    print("map recovered from synthetic truth: max component error < 0.002, k within 2 counts")


if __name__ == "__main__":
    if "--selftest" in sys.argv:
        selftest()
    else:
        report(fit(load()))
