#!/usr/bin/env python3
"""Turn recorded mono frames into pictures you can look at.

    bar_frames.py <capture_prefix> [--n=12] [--mode=diff] [--out=dir]

Needs the capture to have been recorded with the recorder's `raw` option, which
writes META2_MONO_FRAME_BYTES (752x480 u16) per frame, in the same order as the
rows of <prefix>.csv. So frame i of the .raw is row i of the .csv, and the csv
carries its tag, counter and trailer timestamp.

--mode=raw   the frame itself, stretched to 8 bits.
--mode=diff  the frame minus the median frame of the run. This is the view that
             answers "can I see it": a global shutter lights the whole frame at
             once, so the difference is a smooth wash; a rolling shutter cuts a
             horizontal edge across the frame, and the edge shows up as a hard
             line in the difference.

Selection picks the frames whose whole-frame brightness sits between the dark and
the bright clusters - the ones whose exposure contains a display transition - and
among those, the ones furthest from the mean, because those carry the most signal.
"""
import os, struct, sys, zlib, statistics

W, H = 752, 480
FRAME_BYTES = W * H * 2


def read_csv(path):
    rows = []
    for line in open(path):
        if line.startswith('#') or line.startswith('host_us'):
            continue
        p = line.rstrip('\n').split(',')
        if len(p) < 6:
            continue
        rows.append({'host_us': int(p[0]), 'ts': int(p[1]), 'pkt': int(p[2]),
                     'tag': int(p[3]), 'has_trailer': int(p[4]),
                     'mean': float(p[5]), 'peak_row': int(p[6]),
                     'peak_val': float(p[7]), 'above_half': int(p[8])})
    return rows


def png_gray(path, w, h, pix):
    """pix: bytearray of w*h bytes, row major."""
    raw = bytearray()
    for y in range(h):
        raw.append(0)
        raw += pix[y * w:(y + 1) * w]
    def chunk(typ, data):
        c = struct.pack('>I', len(data)) + typ + data
        return c + struct.pack('>I', zlib.crc32(typ + data) & 0xffffffff)
    out = b'\x89PNG\r\n\x1a\n'
    out += chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 0, 0, 0, 0))
    out += chunk(b'IDAT', zlib.compress(bytes(raw), 6))
    out += chunk(b'IEND', b'')
    open(path, 'wb').write(out)


def load_frame(raw, i):
    with open(raw, 'rb') as f:
        f.seek(i * FRAME_BYTES)
        return f.read(FRAME_BYTES)


def main():
    argv = sys.argv[1:]
    if not argv:
        print(__doc__)
        return 2
    prefix = argv[0]
    n = 12
    mode = 'diff'
    outdir = prefix + '_frames'
    for a in argv[1:]:
        if a.startswith('--n='):
            n = int(a[4:])
        elif a.startswith('--mode='):
            mode = a[7:]
        elif a.startswith('--out='):
            outdir = a[6:]
    csv, raw = prefix + '.csv', prefix + '.raw'
    if not os.path.exists(raw):
        print('%s does not exist. Record with the recorder\'s `raw` option.' % raw)
        return 2
    rows = read_csv(csv)
    nframes = os.path.getsize(raw) // FRAME_BYTES
    if nframes != len(rows):
        print('mismatch: %s holds %d frames, %s lists %d' % (raw, nframes, csv, len(rows)))
        return 2
    os.makedirs(outdir, exist_ok=True)

    means = [r['mean'] for r in rows]
    lo, hi = min(means), max(means)
    mid = (lo + hi) / 2.0
    swing = hi - lo
    if swing < 1.0:
        print('this capture has no brightness swing to work with')
        return 2
    # frames whose exposure contains a transition, furthest from the run mean
    mean_all = statistics.mean(means)
    cand = [i for i in range(nframes) if abs(means[i] - mid) < swing * 0.30]
    cand.sort(key=lambda i: -abs(means[i] - mean_all))
    picked = cand[:n]
    if not picked:
        print('no intermediate-brightness frames found')
        return 2

    # median frame, for the difference view
    med = None
    if mode == 'diff':
        step = max(1, nframes // 40)
        samples = []
        for i in range(0, nframes, step):
            samples.append(load_frame(raw, i))
        med = [0] * (W * H)
        for s in samples:
            u = struct.unpack('<%dH' % (W * H), s)
            for k in range(W * H):
                med[k] += u[k]
        cnt = len(samples)
        med = [v / cnt for v in med]

    tags = {}
    for i in picked:
        tags.setdefault(rows[i]['tag'], []).append(i)
    print('%d frames recorded; picking %d intermediate-brightness frames' % (nframes, len(picked)))
    for t, idxs in sorted(tags.items()):
        print('  tag 0x%02x: %d of them' % (t, len(idxs)))

    for i in picked:
        b = load_frame(raw, i)
        u = struct.unpack('<%dH' % (W * H), b)
        if mode == 'diff':
            vals = [u[k] - med[k] for k in range(W * H)]
            span = max(1.0, max(max(vals), -min(vals)))
            pix = bytearray(min(255, max(0, int(128 + 127 * v / span))) for v in vals)
        else:
            lo_f, hi_f = min(u), max(u)
            span = max(1, hi_f - lo_f)
            pix = bytearray(int(255 * (v - lo_f) / span) for v in u)
        name = '%s/%04d_tag%02x_ctr%d.png' % (outdir, i, rows[i]['tag'], rows[i]['ctr'] if 'ctr' in rows[i] else rows[i]['pkt'])
        png_gray(name, W, H, pix)
    print('wrote %d frames to %s' % (len(picked), outdir))
    return 0


if __name__ == '__main__':
    sys.exit(main())
