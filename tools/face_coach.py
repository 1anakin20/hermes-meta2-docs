#!/usr/bin/env python3
"""Which way do the headset's actual SURFACES point?

The axis session (axis_coach.py, docs/18) assumed a headset frame - X out through
the screens, Y wearer's left, Z crown - and laid the device on the table in six
poses. That fit came out with the three assumed headset directions 96.7 / 93.5 /
86.7 degrees apart in sensor space instead of 90. Two explanations fit the data
and nothing in that session could separate them:

  A. the poses were sloppy - the front of this headset is not a flat face, so
     "screens to the table" never put +X exactly vertical;
  B. the device's own geometry is not orthogonal there - a visor's optics plane
     and its crown direction are not necessarily 90 degrees apart.

This coach measures the surfaces directly instead of assuming axes. Three faces
that sit squarely on a table (front face is not one of them), each resting down
and then flipped, so each pair differences out the sensor bias exactly and gives
that face's outward normal in sensor coordinates. The angle between two measured
normals is then a fact about the housing, not about how carefully someone laid
the device down.

Reuse of axis_coach.py is deliberate: same capture path, same live graphs, same
pair differencing. Only the pose list, the file names and the report change.

Run:  ./face_coach.py 8095
"""
import importlib.util
import math
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
spec = importlib.util.spec_from_file_location("ac", os.path.join(HERE, "axis_coach.py"))
ac = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ac)

# --- swap the frame of reference: surfaces, not assumed axes -----------------
ac.POSES = [
    ("TEMPLES-", "rest on the temple arms",
     "Lay the headset on its two side arms so both arms sit flat on the table. "
     "Let go of it - the graph must be steady before you continue.", (0, 0, 0)),
    ("TEMPLES+", "temple arms flipped up",
     "Same resting position, flipped over, so the arms point at the ceiling and "
     "the body rests on them from the other side.", (0, 0, 0)),
    ("TOP-", "rest on the top of the band",
     "Turn it so the top of the head band sits flat on the table.", (0, 0, 0)),
    ("TOP+", "top of the band flipped up",
     "Flip it over so the top of the band faces the ceiling.", (0, 0, 0)),
    ("BACK-", "rest on the back of the headband",
     "Rest it on the rear pad of the headband.", (0, 0, 0)),
    ("BACK+", "back of the headband flipped up",
     "Flip it over so the rear pad faces the ceiling.", (0, 0, 0)),
]
ac.PAIRS = [("TEMPLES+", "TEMPLES-"), ("TOP+", "TOP-"), ("BACK+", "BACK-")]
ac.HNAMES = ("temple-arm plane", "top of band", "back of headband")
ac.SNAMES = ("ax", "ay", "az")
ac.CSV = os.path.join(HERE, "face_cal.csv")
ac.OUT = os.path.join(HERE, "face_results.txt")
ac.RAW = os.path.join(HERE, "face_poses.json")
ac.up_text = lambda up: ""

# The docs/18 accelerometer map: rows are sensor axes in the assumed headset frame.
M = {"IMU0": [[-0.661, -0.702, -0.005], [0.115, -0.166, 0.944], [-0.753, 0.692, 0.304]],
     "IMU1": [[-0.737, 0.710, -0.029], [-0.081, -0.287, -0.942], [-0.686, -0.638, 0.314]]}
# The fit in docs/18 is not orthonormal (det 0.989; its assumed axes come out 96.7 deg
# apart). Interpreting a measured surface normal through a non-rotation corrupts the
# angle, so snap the map to its nearest proper rotation first. Verified in
# scratch/test_face_flow.py: with the raw fit the injected geometry comes back 6.7 deg
# wrong, which is the same size as the anomaly being investigated.
def _norm(v):
    n = math.sqrt(sum(x * x for x in v))
    return [x / n for x in v]

def _orth(rows):
    r0 = _norm(rows[0])
    r1 = _norm([rows[1][i] - sum(rows[1][k] * r0[k] for k in range(3)) * r0[i] for i in range(3)])
    r2 = [r0[1] * r1[2] - r0[2] * r1[1], r0[2] * r1[0] - r0[0] * r1[2], r0[0] * r1[1] - r0[1] * r1[0]]
    return [r0, r1, r2]

M = {k: _orth(v) for k, v in M.items()}

AX = ("+X forward", "-X back", "+Y left", "-Y right", "+Z crown", "-Z down")


def unit(v):
    n = math.sqrt(sum(x * x for x in v))
    return [x / n for x in v]


def in_headset(tag, v):
    """sensor vector -> assumed headset frame (project onto the rows of M)"""
    m = M[tag]
    return [m[0][j] * v[0] + m[1][j] * v[1] + m[2][j] * v[2] for j in range(3)]


def ang(a, b):
    ua, ub = unit(a), unit(b)
    c = sum(ua[i] * ub[i] for i in range(3))
    return math.degrees(math.acos(max(-1.0, min(1.0, c))))


def nearest(label):
    """Which assumed headset axis is this direction closest to, and by how much?"""
    best = None
    for i, name in enumerate(AX):
        e = [0.0, 0.0, 0.0]
        e[i // 2] = 1.0 if i % 2 == 0 else -1.0
        d = ang(label, e)
        if best is None or d < best[1]:
            best = (name, d)
    return best


def report(a):
    """Grade on what this experiment actually asks: are the housing surfaces
    orthogonal to each other, and where do they land in the assumed headset frame?
    The 90-degree test axis_coach uses is NOT applied here - if the device is not
    orthogonal, insisting on 90 degrees just re-creates the original confusion."""
    lines = []
    for tag in ("IMU0", "IMU1"):
        d = a[tag]
        coldev = max(abs(c - d["k"]) / d["k"] for c in d["col_norm"])
        magdev = max(abs(m - d["k"]) / d["k"] for m in d["mag_net"])
        det = d["det"]
        lines.append("%s: k = %.1f counts/g  (1 g agrees across the six rests to %.1f%%, "
                     "|a| to %.1f%% after bias removal)"
                     % (tag, d["k"], coldev * 100, magdev * 100))
        lines.append("  the three normals span a volume of |det| = %.3f - it reaches 1.000 only "
                     "if all three faces are mutually orthogonal, so it is a summary of the angles "
                     "below, not an independent check" % abs(det))
        normals = {}
        for j, (pa, pb) in enumerate(ac.PAIRS):
            v = [d["C"][i][j] for i in range(3)]
            normals[pa[:-1]] = v
            h = in_headset(tag, v)
            name, dev = nearest(h)
            lines.append("  %-18s outward normal: sensor %s   in assumed headset frame %s"
                         % (pa[:-1], " ".join("%+.3f" % x for x in unit(v)),
                            " ".join("%+.3f" % x for x in unit(h))))
            lines.append("  %-18s -> closest assumed axis %s, %.1f deg away"
                         % ("", name, dev))
        keys = list(normals)
        for x in range(3):
            for y in range(x + 1, 3):
                lines.append("  measured angle between the %s and the %s: %.1f deg%s"
                             % (keys[x], keys[y], ang(normals[keys[x]], normals[keys[y]]),
                                "  (orthogonal)" if abs(ang(normals[keys[x]], normals[keys[y]]) - 90) < 5 else ""))
        lines.append("")
    lines.append("Reading: if the faces come out mutually orthogonal, the 96.7 deg anomaly in "
                 "docs/18 came from sloppy poses (the front of this headset is not a flat face). "
                 "If a pair comes out consistently off 90 deg on both chips, the housing itself is "
                 "not orthogonal there and the assumed headset frame in docs/18 has to be replaced "
                 "by these measured surface normals.")
    return "\n".join(lines)


ac.verdict = report

if __name__ == "__main__":
    sys.argv = [sys.argv[0]] + sys.argv[1:]
    print("face coach: measuring housing surface normals instead of assumed axes")
    ac.main()
