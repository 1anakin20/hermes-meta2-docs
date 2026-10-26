"""Which reading of calibu_fu_fv_u0_v0_k1_k2_k3 the vendor actually uses.

Reprojects SIFT matches from an RGB frame onto a timestamp-paired mono frame and
scores both readings of the radial block. Needs a capture pair with matched RGB
and mono: pass the stem, e.g. `camera_model_test.py /path/ir29` for
ir29_ep83.bin + ir29_ep82.bin. Needs the venv with cv2 and numpy.

Evidence for docs/19 §19.3.

The name says fu, fv, u0, v0 and three k's. Two readings fit:

  (A) radial in radius   r_d = r (1 + k1 r^2 + k2 r^4 + k3 r^6),  r = sqrt(x^2+y^2)/z
      - what OpenCV's perspective model does, and what e1_naming_test.py assumed.
  (B) radial in angle    d = theta (1 + k1 theta^2 + k2 theta^4 + k3 theta^6),
      theta = atan(r) - the same polynomial family the kb4 block uses, one term shorter.

They agree near the image centre and diverge hard toward the edge, and the RGB
block has k1 = -0.379, which is far from negligible. The mono pair is Kannala-Brandt
and its intrinsics and poses are already validated to ~20 px, so the mono cameras
are a measuring stick: match RGB to mono, undistort the RGB pixel under each
candidate, project through the mono kb4 model, and bucket the error by RGB pixel
radius. The model that is right stays small at the edge; the wrong one blows up
there while looking fine in the middle.

Run:  venv/bin/python3 tools/camera_model_test.py <capture_stem>
"""
import math
import re
import struct
import sys

import cv2
import numpy as np

sys.path.insert(0, "/home/hermes/work/metavision/re")
from make_mono_exact import exact_frames, split_streams
from make_videos import frames_rgb

CAL = "/home/hermes/work/metavision/re/e1_calibration.bin.txt"
STEM = sys.argv[1] if len(sys.argv) > 1 else "/home/hermes/work/metavision/re/probe8"


SENT = bytes.fromhex("efbeadde 0df0ddda".replace(" ", ""))
RGB_PAT = bytes.fromhex("efbeadde0df0ddda00000000")
MONO_PAT = bytes.fromhex("efbeadde0df0ddda")
RGB_N = 1280 * 720 * 2
MONO_N = 752 * 480 * 2


def ts_at(buf, off):
    """Device timestamp from the start of the 32-byte trailer block.

    The block is TimeStampHi then TimeStampLow, so the 64-bit value is Hi<<32 | Low,
    not a little-endian u64 read at the block start. Reading it as a u64 there
    swaps the halves and gives values around 7e18.
    """
    hi, lo = struct.unpack_from("<II", buf, off)
    return (hi << 32) | lo


def positions(buf, pat):
    out, i = [], 0
    while True:
        j = buf.find(pat, i)
        if j < 0:
            return out
        if j % 4 == 0:
            out.append(j)
        i = j + 4


def rgb_with_ts(buf):
    """(payload, timestamp) per complete RGB frame.

    frames_rgb() drops the trailer; the timestamp lives 16 bytes before the
    sentinel, so re-derive both from the raw buffer with the same filter.
    """
    pos = positions(buf, RGB_PAT)
    out = []
    for a, b in zip(pos, pos[1:]):
        if b - a - 32 == RGB_N:
            out.append((buf[a + 16:a + 16 + RGB_N], ts_at(buf, a - 16)))
    return out


def mono_with_ts(s):
    """(payload, timestamp) per complete mono frame record for one camera stream.

    exact_frames() anchors at sentinel-16 and takes samples from +32; the
    timestamp u64 therefore sits exactly at that anchor.
    """
    pos = positions(s, MONO_PAT)
    out = []
    for a, b in zip(pos, pos[1:]):
        if b - a - 32 == MONO_N:
            anchor = a - 16
            out.append((np.frombuffer(s[anchor + 32:anchor + 32 + MONO_N], np.uint16),
                        ts_at(s, anchor)))
    return out


def ts_of(buf):
    """Device trailer timestamp of a frame record.

    The 32-byte trailer block carries TimeStampHi/Low 16 bytes before the fixed
    sentinel pair EF BE AD DE 0D F0 DD DA. Same block on every endpoint.
    """
    i = buf.find(SENT)
    if i < 16:
        return None
    return struct.unpack_from("<Q", buf, i - 16)[0]


def num(s):
    return [float(x) for x in re.findall(r"-?\d+\.?\d*(?:[eE][-+]?\d+)?", s)]


def parse_calibration():
    text = open(CAL, "rb").read().decode("utf-8", "replace").replace("\r", "")
    out = {}
    for m in re.finditer(r"<camera>\s*(.*?)\s*</camera>", text, re.S):
        cm = re.search(r'<camera_model index="(\d+)" name="([a-z_]+)"', m.group(1))
        pm = re.search(r"<params>\s*\[([^\]]*)\]", m.group(1))
        tm = re.search(r"<T_wc>\s*\[([^\]]*)\]", m.group(1))
        if not (cm and pm and tm):
            continue
        mat = np.array(num(tm.group(1))).reshape(3, 4)
        out[cm.group(2)] = {"index": int(cm.group(1)), "params": num(pm.group(1)),
                            "R": mat[:, :3], "t": mat[:, 3]}
    return out


def project_kb(p, ray):
    fu, fv, u0, v0, k1, k2, k3, k4 = p
    x, y, z = ray
    r = math.hypot(x, y)
    if r < 1e-12:
        return np.array([u0, v0])
    th = math.atan2(r, z)
    d = th * (1 + k1 * th**2 + k2 * th**4 + k3 * th**6 + k4 * th**8)
    return np.array([u0 + fu * (x / r) * d, v0 + fv * (y / r) * d])


def solve_mono(f, target, lo, hi):
    """Bisection on a monotone increasing f with f(0)=0, for f(r) = target."""
    if target == 0.0:
        return 0.0
    hi_v = f(hi)
    if hi_v < target:
        return None                      # outside the model's range
    for _ in range(80):
        mid = 0.5 * (lo + hi)
        if f(mid) < target:
            lo = mid
        else:
            hi = mid
    return 0.5 * (lo + hi)


def radial_limit(k):
    """Largest r where rd(r) is still increasing. Past this the polynomial turns
    around and a pixel has no unique bearing, so the inverse must refuse."""
    r, step = 0.0, 1e-4
    while r < 20.0:
        r2 = r * r
        if 1.0 + 3*k[0]*r2 + 5*k[1]*r2*r2 + 7*k[2]*r2*r2*r2 <= 0.0:
            break
        r += step
    return r


def undistort_radial_radius(rd, k, lim):
    """Model A: rd = r(1 + k1 r^2 + k2 r^4 + k3 r^6)."""
    f = lambda r: r * (1 + k[0] * r*r + k[1] * r**4 + k[2] * r**6)
    return solve_mono(f, rd, 0.0, lim)


def undistort_radial_angle(rd, k):
    """Model B: rd = theta(1 + k1 theta^2 + k2 theta^4 + k3 theta^6), r = tan(theta)."""
    f = lambda t: t * (1 + k[0] * t*t + k[1] * t**4 + k[2] * t**6)
    th = solve_mono(f, rd, 0.0, math.pi / 2 - 1e-9)
    return None if th is None else math.tan(th)


def main():
    cal = parse_calibration()
    rgb = cal["rgb"]
    p = rgb["params"]
    fu, fv, u0, v0 = p[0], p[1], p[2], p[3]
    k = p[4:7]
    W, H = 1280, 720
    print("capture %s" % STEM)
    print("rgb intrinsics fu %.4f fv %.4f u0 %.4f v0 %.4f  k %s" % (fu, fv, u0, v0, k))

    # How far apart the two readings are, on their own, across the frame.
    lim = radial_limit(k)
    print("radial model A stays monotone only out to r = %.4f (rd = %.4f); beyond that a "
          "pixel has no unique bearing" % (lim, k and (lim * (1 + k[0]*lim*lim + k[1]*lim**4 + k[2]*lim**6))))
    print("\n=== the two models disagree by how much, on the image itself ===")
    for frac in (0.1, 0.25, 0.5, 0.75, 1.0):
        rd = frac * (W / 2.0) / fu                      # distorted normalised radius
        a = undistort_radial_radius(rd, k, lim)
        b = undistort_radial_angle(rd, k)
        if a is None or b is None:
            print("  r_pix %5.0f : one model has no solution" % (frac * W / 2.0))
            continue
        pa, pb = fu * a, fu * b
        print("  r_pix %5.0f  ->  model A undistorts to %6.1f px, model B to %6.1f px, "
              "difference %6.1f px" % (frac * W / 2.0, pa, pb, abs(pa - pb)))

    rgb_recs = rgb_with_ts(open(STEM + "_ep83.bin", "rb").read())
    rgb_frames = [f for f, _ in rgb_recs]
    rgb_ts = [t for _, t in rgb_recs]
    print("\nrgb frames: %d  timestamps %d .. %d  (span %.1f s of device time)"
          % (len(rgb_recs), rgb_ts[0], rgb_ts[-1], (rgb_ts[-1] - rgb_ts[0]) / 117821900.0))
    streams = split_streams(open(STEM + "_ep82.bin", "rb").read())
    mono = {t: mono_with_ts(streams[t]) for t in (0x44, 0x55)}
    for t in mono:
        print("mono frames 0x%02x: %d  timestamps %d .. %d"
              % (t, len(mono[t]), mono[t][0][1], mono[t][-1][1]))
    mono_frames = {t: [f for f, _ in mono[t]] for t in mono}

    def to8(a):
        a = a.astype(np.float32)
        lo, hi = np.percentile(a, (2, 98))
        return np.clip((a - lo) * 255.0 / max(hi - lo, 1.0), 0, 255).astype(np.uint8)

    names = {0x44: "mono_left", 0x55: "mono_right"}
    buckets = {}
    nmatch = 0
    # Pair by device timestamp, not by index. RGB runs at 30 fps and mono at 60 fps
    # in device time, and the two captures do not start together, so index pairing
    # compares different moments.
    mono_ts = {t: [ts for _, ts in mono[t]] for t in mono}
    TICK = 117821900.0
    pairs = []
    for ri, tr in enumerate(rgb_ts):
        if tr is None:
            continue
        for tag, frames in mono.items():
            best, bestd = None, None
            for mi, tm in enumerate(mono_ts[tag]):
                if tm is None:
                    continue
                d = abs(tm - tr)
                if bestd is None or d < bestd:
                    best, bestd = mi, d
            if best is not None and bestd < 0.02 * TICK:      # within 20 ms of device time
                pairs.append((ri, tag, best, bestd / TICK))
    print("\ntimestamp-paired frame pairs within 20 ms: %d" % len(pairs))
    for ri, tag, mi, dt in pairs[:8]:
        print("   rgb #%d <-> mono 0x%02x #%d   gap %.1f ms" % (ri, tag, mi, dt * 1000))

    pairs = pairs[:40]          # SIFT on every pair would take the better part of an hour
    for ri, tag, mi, dt in pairs:
        raw = np.frombuffer(rgb_frames[ri], np.uint8).reshape(H, W // 2, 4)
        img_rgb = raw[:, :, [1, 3]].reshape(H, W)
        img_mono = to8(mono_frames[tag][mi].reshape(480, 752))
        sift = cv2.SIFT_create(nfeatures=6000)
        ka, da = sift.detectAndCompute(img_rgb, None)
        kb, db = sift.detectAndCompute(img_mono, None)
        if db is None or len(ka) < 4:
            continue
        raw_m = cv2.BFMatcher().knnMatch(db, da, k=2)
        good = [m for m, n in (x for x in raw_m if len(x) == 2) if m.distance < 0.75 * n.distance]
        bcal = cal[names[tag]]
        Rb, tb = bcal["R"], bcal["t"]
        Rrgb, trgb = rgb["R"], rgb["t"]
        for g in good:
            # knnMatch(db, da): queryIdx indexes the mono keypoints, trainIdx the rgb ones.
            mi_idx, ri_idx = g.queryIdx, g.trainIdx
            mx, my = kb[mi_idx].pt                          # pixel in the mono image
            u, v = ka[ri_idx].pt                            # pixel in the rgb image
            rd_u = (u - u0) / fu
            rd_v = (v - v0) / fv
            rd = math.hypot(rd_u, rd_v)
            if rd_u == 0:
                ang = 0.0
            else:
                ang = math.degrees(math.atan2(rd_v, rd_u))
            for model, und in (("A_radial_radius", lambda x: undistort_radial_radius(x, k, lim)),
                               ("B_radial_angle", lambda x: undistort_radial_angle(x, k))):
                ru = und(rd_u)
                rv = und(rd_v)
                if model == "A_radial_radius":
                    # The vendor model is radial in the *radius*, so the correct
                    # inverse rescales the whole vector, not each component.
                    su = und(rd)
                    if su is None:
                        continue
                    ru, rv = (su * rd_u / rd, su * rd_v / rd) if rd > 0 else (0.0, 0.0)
                if ru is None or rv is None:
                    continue
                ray_rgb = np.array([ru, rv, 1.0])
                ray_rgb /= np.linalg.norm(ray_rgb)
                if model == "B_radial_angle":
                    pass  # control: same code path, wrong reading of the block
                ray_world = Rrgb @ ray_rgb
                ray_cam = Rb.T @ (ray_world - tb)
                if ray_cam[2] <= 0:
                    continue
                pred = project_kb(bcal["params"], ray_cam)
                err = math.hypot(*(pred - np.array([mx, my])))
                if not (0 <= pred[0] < 752 and 0 <= pred[1] < 480):
                    continue
                band = int(min(rd * fu / (W / 2.0), 1.0) * 4)   # 0..3, centre -> edge
                buckets.setdefault((model, band), []).append(err)
                if model == "A_radial_radius":
                    nmatch += 1

    print("\n=== reprojection error vs RGB pixel radius (fraction of half-width) ===")
    print("matches used: %d" % nmatch)
    print("%-18s %-22s %8s %8s %8s" % ("model", "radius band", "n", "median", "p90"))
    for model in ("A_radial_radius", "B_radial_angle"):
        for band in range(4):
            e = buckets.get((model, band), [])
            if not e:
                print("%-18s %-22s %8s" % (model, "%d-%d%%" % (band * 25, band * 25 + 25), 0))
                continue
            e.sort()
            print("%-18s %-22s %8d %8.1f %8.1f"
                  % (model, "%d-%d%%" % (band * 25, band * 25 + 25), len(e),
                     e[len(e) // 2], e[int(len(e) * 0.9)]))

    for model in ("A_radial_radius", "B_radial_angle"):
        allv = [x for band in range(4) for x in buckets.get((model, band), [])]
        if allv:
            allv.sort()
            print("ALL  %-16s n=%d median %.1f px" % (model, len(allv), allv[len(allv) // 2]))


if __name__ == "__main__":
    main()
