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
| `0x83` | 1280×720 mono image, 8-bit image data in the high byte of each u16, ~25 complete frames/s alone, ceiling 27.7 fps; **light-sensitive, responds to a centre-only cover (−43%)** | whether it is one camera or two, and its exact lens position |
| `0x82` | A/B record pairs, 2,032 coherent 10-bit samples each, 4,064 samples per acquisition, correlates with 0x83's scene; **light-sensitive (saturation 0.1995 → 0.0000 under cover), responds to left and right covers, not to a centre cover; not Bayer** | whether A and B are the two side cameras, two halves of one camera, or one camera plus something else |
| `0x84` | 101,376 12-bit samples per frame; 352×288 matches register `0xa886`'s read-back exactly; **not light-sensitive — unchanged (±0.3%) by every cover** | that it is an image at all, and whether it is a rangefinder that was simply not enabled |
| `0x81` | 256-byte status records, 233 constant bytes each; **not light-sensitive** | what the 23 varying fields mean |

The user's working model — **two monochrome cameras, one RGB camera, one Time-of-Flight
camera** — is now partly confirmed and partly contradicted. The two side positions and the
centre position are both occupied by light-sensitive monochrome streams, which matches the
two-monochrome-plus-one-more-camera shape. What is **not** found anywhere is colour: no
endpoint carries Bayer, channel-sequential, or colour-phase structure, and there is no
fifth endpoint to hide it in. `[VERIFIED]` for the absence of colour in the current
configuration; `[UNKNOWN]` for where the vendor SDK's colour frames come from. See 8.8
and 8.9.

What static analysis cannot settle: every camera in the headset looks at the same room, so
scene correlation cannot separate them. Occlusion can, and it did — see 8.8.

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

---

## 8.8 Occlusion results — the cameras are now separated by position

`re/occlusion_test2.py`, run 2026-10-16 15:59. Ten windows: prepare, then four covers each
bracketed by a baseline. Arm **once**, readers and the 4-command strobe run continuously,
8 s settle + 12 s measured per window, statistics accumulated per second over the whole
window. Per second per endpoint: u16 sample mean, sentinel fraction, bytes.

| window | mean 0x81 | mean 0x82 | mean 0x83 | mean 0x84 |
|---|---|---|---|---|
| baseline (2) | 52,374 | **577.5** | **29,042** | 2,072.4 |
| **COVER_ALL** (3) | 53,515 | **234.7** | **13,211** | 2,079.1 |
| baseline (4) | 52,975 | 460.1 | 22,212 | 2,073.3 |
| **COVER_LEFT** (5) | 53,363 | **332.5** | **15,175** | 2,074.2 |
| baseline (6) | 53,190 | 433.2 | 21,115 | 2,075.9 |
| **COVER_RIGHT** (7) | 52,933 | **368.4** | **24,970** | 2,074.8 |
| baseline (8) | 53,377 | 449.1 | 21,458 | 2,074.6 |
| **COVER_MIDDLE** (9) | 53,094 | **449.5** | **12,206** | 2,076.1 |
| baseline (10) | 53,467 | 491.6 | 23,120 | 2,077.6 |

Sentinel fractions over the same windows:

| endpoint | sentinel | baseline | cover_all | cover_left | cover_right | cover_middle |
|---|---|---|---|---|---|---|
| `0x82` | `== 1023` | 0.1995 | **0.0000** | 0.0026 | 0.0049 | 0.0048 |
| `0x84` | `== 0x0fff` | 0.0053 | 0.0049 | 0.0051 | 0.0053 | 0.0050 |
| `0x81`, `0x83` | — | 0.0000 | 0.0000 | 0.0000 | 0.0000 | 0.0000 |

Throughput did **not** change between windows (0x82 1.63–1.79 MB/s, 0x83 3.81–4.04 MB/s,
0x84 4.29–4.61 MB/s, 0x81 17.9–20.8 kB/s), so the value changes below are not bandwidth
artefacts. `[VERIFIED]`

### What each result means

**EP 0x82 is an optical camera, and it is not in the middle.** Covering everything drops
its mean 59.4% and takes its saturation fraction from **0.1995 to exactly 0.0000** — every
sample that was pinned at 1023 in a lit room stops being pinned when the light goes. That
is as clean a light-sensor signature as this project has produced. Covering only the left
half moves it −27.7%, only the right half −15.0%, and covering **only the middle moves it
+0.1%, i.e. not at all**. `[VERIFIED]`

**EP 0x83 is an optical camera, and it is the middle one.** Covering only the centre drops
it 43.1% — nearly as much as covering the whole headset (54.5%). Covering the left half
drops it 31.7%, consistent with a wide field of view that the left hand partly intrudes
on. `[VERIFIED]` for the drops; `[INFERRED]` that the response pattern locates the lens
centrally.

**EP 0x83 under COVER_RIGHT went *up* 18.3%.** Unexplained. The baselines around it drift
(29,042 → 22,212 → 21,115 → 21,458 → 23,120), and a hand entering the right side of a wide
field of view can be a bright near object. Do not treat this number as meaningful.
`[UNKNOWN]`

**EP 0x84 is not driven by light reaching the front of the headset.** Its mean moves by at
most 0.3% across every cover, and its `0x0fff` "no data" sentinel fraction is flat
(0.0049–0.0054) — covering an active rangefinder should make returns vanish and the
sentinel spike. It does not. `[VERIFIED]` That weakens the depth/ToF reading of 0x84 rather
than supporting it, unless the subsystem was simply not enabled in this configuration.
`[UNKNOWN]`

**EP 0x81 is not optical.** Mean 52,374–53,515, ±2%, unchanged by every cover. `[VERIFIED]`

### No endpoint carries colour

The colour hypothesis was tested directly on EP 0x82, which had never been tested for it:

| sub-stream | lag-1 | lag-2 | lag-4 | lag4 / lag1 |
|---|---|---|---|---|
| A (tag 0x0044) | 15.85 | 22.54 | 67.95 | **4.29** |
| B (tag 0x0055) | 18.69 | 26.04 | 79.01 | **4.23** |

A Bayer mosaic makes lag-1 *less* coherent than lag-2 and lag-4 (adjacent pixels are
different colours), so lag4/lag1 < 1. Both sub-streams give > 4, and splitting samples by
position mod 4 gives identical means (A: 524.1 / 525.8 / 527.1 / 524.7; B: 212.9 / 211.3 /
212.6 / 214.0) — no colour-phase structure. `[VERIFIED]` EP 0x82 is monochrome, like 0x83.

Combined with 8.2 (0x83 is not Bayer, not channel-sequential) this means: **in the
configuration the vendor command sequence puts the device in, no bulk endpoint delivers
colour data.** The vendor SDK nevertheless produced 1280×720 colour frames with mean
`|R−B| = 17.4`. Where those frames come from is the open question. `[UNKNOWN]`

### There is no hidden fifth endpoint

Raw `GET_DESCRIPTOR(configuration)`: `wTotalLength = 70`, **one** interface (class `0xff`
vendor-specific, alt setting 0), exactly four bulk IN endpoints `0x81`–`0x84`, each
`wMaxPacketSize = 1024`, `bInterval = 0`, each followed by a 6-byte type `0x30` companion
descriptor. No interrupt, isochronous or OUT bulk endpoints exist. `[VERIFIED]`

### The 138 "failed" arm transfers are not lost commands

Every arm reports `ok=279 fail=138` of 417 transfers. `re/arm_failures.py` shows **all 138
failures are IN transfers** — the second IN of a pair, which stalls because the device
produces only one response for those commands. **No OUT ever fails.** So the hypothesis
that a colour-camera enable command is being lost in the arm is refuted: every command the
vendor sent was accepted. `[VERIFIED]` All 138 errors are `[Errno 32] Pipe error`.

---

## 8.9 Next: where do the SDK's colour frames come from?

The decisive experiment is to watch the vendor software produce colour and see which
endpoint feeds it.

1. Hand the headset to the VM (`vm/vm.sh usb`), start `usbmon` on the host for that bus.
2. Run MetaReader until it emits colour frames, and save several frames with timestamps.
3. Attribute completed bulk bytes per endpoint in the trace — **completed**, not requested;
   05 §5.1 warns that requested URB sizes describe the software's intent, not the device.
4. Compare a saved SDK colour frame against the candidate endpoint's stream at the same
   instant, geometrically (edge positions, not pixel values).

If colour arrives on an endpoint already known to be monochrome, the colour is being
produced downstream of the wire — by the FPGA or by the SDK — and that changes what a
Linux driver has to do.

