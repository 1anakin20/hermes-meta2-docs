# 8. Camera inventory — what each endpoint carries

Written 2026-10-16. This is the current answer to "how many cameras are there and which
stream is which", with the evidence for each claim labelled the way the rest of these
documents label it.

Firmware version: **unknown** (not yet read from the device; to be filled in later).

---

## 8.1 EP 0x82 is a real stream, and it is a camera-class stream

Earlier documents recorded EP 0x82 as "nothing, in every capture attempted". That was
never tested with URBs genuinely pending: every streaming measurement so far used
`Recorder(dev, (0x83,))`. With a reader thread per endpoint started **before** any control
traffic, EP 0x82 streams more than any other endpoint. `[VERIFIED]`

In one 12 s window (port reset, full 417-transfer arm, then the 4-command strobe loop,
all four readers pending):

| Endpoint | Bytes in 12 s | Record size | Records | Records/s |
|---|---|---|---|---|
| `0x81` | 176,384 | 256 | 689 | 57 |
| `0x82` | 67,469,312 | 4,096 | 16,472 | 1,373 |
| `0x83` | 49,135,616 | 1,843,232 | 27 | 2.2 |
| `0x84` | 47,890,432 | 202,784 | 236 | 20 |

`[VERIFIED]` — these are counts from one run, not a rate spec. Per-endpoint rates vary
between runs by more than an order of magnitude (a second run with register reads
interleaved produced 222 MB on `0x82` and 142 MB on `0x83` in the same 12 s). The device
does not appear to allocate a fixed share per endpoint. `[VERIFIED]` that rates vary;
`[UNKNOWN]` what sets them.

### The 4,096-byte record

```
+0    ba ab ed fe          magic
+4    u16 tag              0x0044 or 0x0055, repeated at +6
+8    u16, u16             0x0000 0x0000 normally; 0xdeadbeef in 28 of 2,076 records
+12   u16 pair counter     increments by 1 per A/B pair
+14   u16                  0x8001 normally; 0xdadd (with +12 = 0xf00d = dadcf00d) in 28 records
+16   2,032 × u16          the data
+4080 16-byte trailer      u32 = 408 (constant), u32 timestamp, then dc ac 78 56 34 12
```

`[VERIFIED]` from `re/probe_arm_strobe_ep82.bin` (2,076 records, magic spacing exactly
4,096 for 2,019 of 2,075 gaps).

**A frame is an A/B record pair.** The tag alternates 0x44, 0x55, 0x44, 0x55 and the two
records of each pair carry the **same** pair counter (1,009 of 2,074 adjacent pairs share
one counter; 1,023 complete pairs in the capture). So one acquisition = 2 × 2,032 =
**4,064 samples**. `[VERIFIED]`

### The samples

10-bit range, strongly baseline-weighted: mode **42** (1,435,914 occurrences), saturation
marker **1023** (272,665 occurrences, 6.7% of samples), then 46–52. Within a record,
adjacent samples are highly coherent: mean |adjacent difference| 9.96 against a shuffled
baseline of 376 — ratio **0.026**. `[VERIFIED]`

That coherence is what an optical scanline looks like. It is not what an IMU, a microphone
or a counter looks like. `[INFERRED]`

---

## 8.2 EP 0x82 sees the same scene as EP 0x83

EP 0x83's frames are 1280×720 images (5.3). Averaging each frame over its rows gives a
1280-value horizontal profile; resampling it to 2,032 and cross-correlating against EP
0x82's records gives:

| 0x82 sub-stream | best correlation | shift | shuffled baseline |
|---|---|---|---|
| A (tag 0x0044) | **0.472** | −430 | 0.04–0.05 |
| B (tag 0x0055) | **0.252** | −438 | 0.04–0.07 |

Stable across four independent 0x83 frames. `[VERIFIED]` that the correlation exists and
is far above the shuffled baseline; `[INFERRED]` that it means the two endpoints look at
the same scene. Correlation of a smoothed profile is not proof of a shared optical path —
a processed derivative of the 0x83 image would correlate too.

Sub-stream A and sub-stream B of the *same* pair correlate only weakly with each other
(best residual 275 at shift 377, against 297 at zero shift). They are not two views of one
scene at a small disparity. `[VERIFIED]`

### Consecutive frames are the same content, displaced

Circular cross-difference between consecutive frames of one sub-stream (fixed 2,032-sample
length, averaged over 150 pairs):

| sub-stream | residual at shift 0 | best shift | residual there |
|---|---|---|---|
| A | 339.9 | **1808** (≡ −224) | 81.1 |
| B | 206.8 | **1808** | 70.2 |

Stacking records with a shear of 223 samples per record improves vertical alignment by a
factor of 4.3 over randomly paired records (ratio 0.23 against 0.83 unshared). `[VERIFIED]`

**The displacement does not accumulate.** Best shift for lag 2 is 304, for lag 3 is 80 —
not 2×1808 and 3×1808. So this is not a constant-rate lateral scan, and the overlap model
("each record advances the scene by a fixed step, so neighbours overlap") is **refuted**:
comparing the tail of record *i* with the head of record *i+1* at every candidate step
gives mean |difference| 367 with 0.7% exact matches. `[VERIFIED]`

What produces a strong pairwise displacement that does not accumulate is `[UNKNOWN]`.

---

## 8.3 EP 0x84's geometry is now named by the device

Register **0xa886** reads back `00 0000 015f 0001 0120` — words 351 and 288. `[VERIFIED]`
read-back, see 8.5.

352 × 288 = **101,376**, which is exactly the EP 0x84 payload sample count (202,752 bytes
of u16 per 202,784-byte record). `[VERIFIED]` arithmetic match.

The record header of EP 0x84 also carries `0x0016` and `0x0120` (= 288) in its first
32 bytes, consistent with 288 rows. `[VERIFIED]` presence, `[INFERRED]` meaning.

This replaces the "704 is the leading candidate stride" guess in 5.4, which was based on a
18% autocorrelation dip. That dip is still real and still weak; the register read-back is
much stronger evidence and points at 352, not 704. `[VERIFIED]` read-back; `[INFERRED]`
that 0xa886 configures EP 0x84 rather than some other subsystem.

Spatial coherence of EP 0x84's payload remains **absent**: reshaping one frame as
352×288, 704×144, 128×792 or 1024×99 gives horizontal mean-|difference| equal to the
random-pair baseline (ratio 1.000) in every candidate geometry, and scanning every width
from 16 to 1099 finds no width with better coherence than any other. `[VERIFIED]`

So EP 0x84 is a 352×288 array of 12-bit values that is **not a spatially coherent image**.
Depth/range remains `[INFERRED]`, and the mapping to metres remains `[UNKNOWN]`.

---

## 8.4 EP 0x81 is not a camera

256-byte records, 57/s. Across 689 records only **23 of the 256 byte positions vary at
all** (std > 1). The varying positions are 8, 10, 20–23, 30–31, 34–35, 38–43, 228–231,
252; position 252 increments by 1 per record. `[VERIFIED]`

A stream with 233 constant bytes per record is a status/metadata record, not sensor data.
`[INFERRED]`

---

## 8.5 Register reads: only at the vendor's own positions

`[VERIFIED]`, and it overturns how these documents have described register access:

- Replaying `ctrl_seq_full.json` transfer-for-transfer and answering each IN with the
  vendor's own `wValue`/`wLength` serves **70 reads with data**. Status byte `00` then the
  value.
- Re-issuing those **identical** read commands immediately after the sequence completes:
  98 of 98 attempts return a **1-byte status only** (`01` or `06`), never the value.
- Querying 376 addresses in ten ranges after the sequence with a 2-byte mask: **0
  readable**.
- Querying the 34 written addresses as a batch, unarmed or during a live streaming
  window: status `07` + zeros for 33 of 34.

So the control endpoint behaves as a **fixed script**, not a register bus: a read is
honored only at the step where the firmware's own sequence expects it. Reading an
arbitrary address is not available with the shapes observed so far. `[VERIFIED]` for the
behaviour; `[UNKNOWN]` whether another command shape unlocks general reads.

Values captured by in-order replay (`re/replay_reads.log`), status byte stripped:

| address | value read | note |
|---|---|---|
| `0xb007` | `0180` | round-trip of the write `3d 40 b0 07 01 80` |
| `0xb062` | `a3c355680000000000000000aaaa032a` | exactly the 22 bytes written |
| `0xa882` | `0280105700000004` | 640, 4183, 0, 4 |
| `0xa886` | `0000015f00010120` | **351, 288** → 352×288 |
| `0xa88c` | `4000` | 16384 |
| `0xa88f` | `031e` | 798 |
| `0xa892` | `0311`, later `001d` | 785, then 29 — changes |
| `0xbff8` | `0800 072b 0800 0800 0800 0800 0800 0a2a` | **six words of 2048** |
| `0xc2bc` | `004e 0000 2000 0000 08d3 …` | 30 bytes, `08d3` (2259) ×4 |
| `0xc2c0` | `07f1` | **2033** |
| `0xc2c4` | `07f1` | **2033** |
| `0xc2c8` | `07f1` | **2033** |
| `0xc2cc` | `07f1 03b7` | 2033, 951 |
| `0xc352` | `68391b4f03e880453d71060a` | |
| `0xc363` | `552955554e15c71b0000`, then `5529e83234f457120002` | read twice, **different** |
| `0xb09e/9f/a0/a1` | `0670`, `6665`, `056c`, `089c` | read repeatedly |
| `0x0204` | `ffff` | |

`0xbff8` holding six copies of **2048** is consistent with EP 0x82's 2,032-sample halves
inside 4,096-byte records; `0xc2c0`/`0xc2c4`/`0xc2c8` all holding **2033** is consistent
with a 2,033-sample line length. `[INFERRED]` — the numbers match the stream geometry, no
register has been proven to configure a specific endpoint.

### Device identity string

A 56-byte vendor IN (`wValue=2`, `wLength=56`) at capture index 388 returns the model
string `META2D` followed by 11 digits. Per EVIDENCE §8 those digits are this unit's serial
number and are **redacted here as `<unit-serial>`**; the raw bytes are in the scratch
capture log only, which is not part of this repo. `[VERIFIED]` observed payload structure.

`META2D` is the model prefix the device reports. Whether the digits are a serial number, a
firmware build id, or both is `[UNKNOWN]`. This is the best lead available for the unknown
firmware version, and reconciling it against any vendor label on the headset shell is the
way to settle it.

---

## 8.6 Current inventory, stated honestly

| Stream | Established | Not established |
|---|---|---|
| `0x83` | 1280×720 mono image, 8-bit image data in the high byte of each u16, ~25 complete frames/s alone, ceiling 27.7 fps | which physical camera it comes from |
| `0x82` | A/B record pairs, 2,032 coherent 10-bit samples each, 4,064 samples per acquisition, correlates with 0x83's scene | whether A and B are two cameras, two halves of one camera, or one camera plus something else |
| `0x84` | 101,376 12-bit samples per frame; 352×288 matches register `0xa886`'s read-back exactly | that it is an image at all — no spatial coherence in any candidate geometry |
| `0x81` | 256-byte status records, 233 constant bytes each | what the 23 varying fields mean |

The user's working model — **two monochrome cameras, one RGB camera, one Time-of-Flight
camera** — is consistent with four bulk IN endpoints, and nothing measured so far
contradicts it. It is **not confirmed**: no stream has been tied to a physical lens, and
the RGB camera has not been located. `[UNKNOWN]`

What static analysis cannot settle: every camera in the headset looks at the same room, so
scene correlation cannot separate them. Occlusion can. See 8.7.

---

## 8.7 The experiment that separates the cameras

`re/occlusion_test.py` runs six timed phases (baseline, cover whole headset, uncover,
cover left half, uncover, cover right half), keeps readers pending on all four endpoints
through each phase, arms and strobes, and saves a raw capture per endpoint per phase. A
live countdown page (`verify/occlusion_status.html`, served on `:8090`) tells the operator
what to do and when.

Reading the result:
- a stream whose mean value collapses under `cover_all` is **light-sensitive** — an optical
  camera;
- a stream that changes under `cover_left` but not `cover_right` (or the reverse) is
  **positionally asymmetric**, which separates cameras by where their lens sits;
- a stream unchanged by any occlusion is not an optical camera.

Compare per endpoint per phase with the saved captures: per-record mean, saturation
fraction (1023 for 0x82, 0x0fff for 0x84, 0xffff for 0x83) and adjacent-sample coherence.

**Do not commit or publish the captures.** They are pictures of the operator's room.
