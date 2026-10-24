#!/usr/bin/env python3
"""IR-65: is EP 0x84 a stream of RAW multi-phase correlation frames rather than range?

Everything measured so far treats one EP 0x84 frame as one range image. That assumption has
never been tested. royale.2.3.1.dll contains UseCaseTwoPhase / UseCaseFourPhase /
UseCaseEightPhase and a RawFrameSet / CapturedUseCase type, which is the classic PMD contract:
the imager returns N frames per measurement, each correlated at a different phase offset, and
amplitude + phase are computed from the group:

    I_k = A cos(phi + 2 pi k / N) + B
    N=4:  A cos phi = (I0 - I2)/2      A sin phi = (I3 - I1)/2      B = mean(I0..I3)
          phi = atan2(I3 - I1, I0 - I2)

If EP 0x84 is raw phase frames, then:
  (a) consecutive frames must differ systematically, in a cycle of period N;
  (b) the demodulated amplitude map must be spatially coherent (it is a reflectance image);
  (c) the demodulated phase map must vary with the scene.
If EP 0x84 is already-computed range, (a) and (b) fail and the constant 2037 is the range.

This runs entirely offline on re/ir29_tof_ep84.bin - no device, no physical action.
"""
import pathlib
import numpy as np

RE = pathlib.Path("/home/hermes/work/metavision/re")
SRC = RE / "ir29_tof_ep84.bin"

W, H = 352, 288
DESC, IMG, FRAME = 16, W * H, 101392


def frames(a):
    """Resynchronise on the 0xDEAD/0xF00D descriptor pair; yield image blocks (H, W)."""
    idx = np.nonzero(a == 0xDEAD)[0]
    out = []
    for i in idx:
        if i + 1 < len(a) and a[i + 1] == 0xF00D and i + DESC + IMG <= len(a):
            out.append(a[i + DESC:i + DESC + IMG].reshape(H, W).astype(np.float64))
    return out


def coherence(m):
    """Mean |adjacent difference| horizontally, divided by the same statistic on a shuffled
    copy of the array. ~1.0 means no spatial structure; <<1 means a real image."""
    a = np.abs(np.diff(m, axis=1)).mean()
    rng = np.random.default_rng(7)
    b = np.abs(np.diff(rng.permutation(m), axis=1)).mean()
    return float(a / b)


def demod4(g):
    """g: (4, H, W) frames I0..I3 -> amplitude, phase, brightness."""
    ac = (g[0] - g[2]) / 2.0
    as_ = (g[3] - g[1]) / 2.0
    B = (g[0] + g[1] + g[2] + g[3]) / 4.0
    return np.hypot(ac, as_), np.arctan2(as_, ac), B


def main():
    raw = SRC.read_bytes()
    raw = raw[:len(raw) & ~1]
    a = np.frombuffer(raw, dtype="<u2")
    fr = frames(a)
    print(f"{SRC.name}: {len(a):,} samples -> {len(fr)} complete frames")
    if len(fr) < 64:
        print("too few frames for a phase test")
        return
    S = np.stack(fr)                      # (F, H, W)
    F = len(S)

    # (a) is there a per-frame cycle?
    fm = S.mean(axis=(1, 2))
    print(f"\nper-frame mean: min {fm.min():.2f} max {fm.max():.2f} sd {fm.std():.2f}")
    print("first 16 frame means:", " ".join(f"{v:.1f}" for v in fm[:16]))
    x = fm - fm.mean()
    print("\nautocorrelation of the frame-mean sequence:")
    for lag in range(1, 17):
        r = float(np.dot(x[:-lag], x[lag:]) / np.dot(x, x))
        flag = "  <-- candidate phase period" if r > 0.25 else ""
        print(f"  lag {lag:2d}: {r:+.4f}{flag}")

    # per-pixel lag-1 difference vs a shuffled baseline: do consecutive frames differ?
    d1 = np.abs(S[1:] - S[:-1]).mean()
    rng = np.random.default_rng(11)
    base = np.abs(S[1:] - rng.permutation(S[:-1])).mean()
    print(f"\nconsecutive-frame |difference|: {d1:.2f}  shuffled baseline: {base:.2f}  "
          f"ratio {d1/base:.4f}")

    # (b) 4-phase demodulation on consecutive groups
    n = (F // 4) * 4
    G = S[:n].reshape(-1, 4, H, W)
    A, P, B = demod4(G)
    print(f"\n4-phase demodulation on {G.shape[0]} consecutive groups:")
    print(f"  amplitude  mean {A.mean():8.2f}  sd {A.std():8.2f}  "
          f"p1 {np.percentile(A,1):.1f} p99 {np.percentile(A,99):.1f}")
    print(f"  phase      mean {P.mean():8.4f}  sd {P.std():8.4f}  "
          f"p1 {np.percentile(P,1):.3f} p99 {np.percentile(P,99):.3f}")
    print(f"  brightness mean {B.mean():8.2f}  sd {B.std():8.2f}")
    print(f"  amplitude spatial coherence ratio: {coherence(A):.4f}   (1.0 = noise)")
    print(f"  brightness spatial coherence ratio: {coherence(B):.4f}   (1.0 = noise)")
    print(f"  raw frame 0 spatial coherence ratio: {coherence(S[0]):.4f}   (1.0 = noise)")

    # temporal mean of amplitude across groups: a stable reflectance image would show structure
    Abar = A.mean(axis=0)
    print(f"\ntemporal mean amplitude: sd {Abar.std():.2f}, "
          f"spatial coherence {coherence(Abar):.4f}")

    # 2-phase variant (UseCaseTwoPhase): I0 - I1 only
    n2 = (F // 2) * 2
    G2 = S[:n2].reshape(-1, 2, H, W)
    D2 = np.abs(G2[:, 0] - G2[:, 1])
    print(f"\n2-phase |I0-I1|: mean {D2.mean():.2f} sd {D2.std():.2f}, "
          f"spatial coherence {coherence(D2.mean(axis=0)):.4f}")

    # save the most informative maps
    out = RE / "ir65_maps"
    out.mkdir(exist_ok=True)
    def save(name, m, lo=None, hi=None):
        m = np.asarray(m, dtype=np.float64)
        lo = m.min() if lo is None else lo
        hi = m.max() if hi is None else hi
        q = np.clip((m - lo) / max(hi - lo, 1e-9), 0, 1)
        rows = b"".join(bytes(int(255 * v) for v in row) for row in q)
        png = out / name
        import zlib, struct
        rawz = zlib.compress(b"".join(b"\x00" + rows[y*W:(y+1)*W] for y in range(H)))
        png.write_bytes(
            b"\x89PNG\r\n\x1a\n"
            + struct.pack(">I", 13) + b"IHDR" + struct.pack(">IIBBBBB", W, H, 8, 0, 0, 0, 0)
            + struct.pack(">I", zlib.crc32(b"IHDR" + struct.pack(">IIBBBBB", W, H, 8, 0, 0, 0, 0)))
            + struct.pack(">I", len(rawz)) + b"IDAT" + rawz
            + struct.pack(">I", zlib.crc32(b"IDAT" + rawz))
            + struct.pack(">I", 0) + b"IEND" + struct.pack(">I", zlib.crc32(b"IEND")))
    save("amp_mean.png", Abar)
    save("bright_mean.png", B.mean(axis=0))
    save("phase_mean.png", P.mean(axis=0))
    save("raw_frame0.png", S[0])
    print(f"\nmaps written to {out}/")


if __name__ == "__main__":
    main()
