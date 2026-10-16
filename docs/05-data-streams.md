# 5. Data streams

All sensor data arrives on the four bulk IN endpoints. There is no bulk OUT.

## 5.1 Endpoint behaviour

Measured with a no-SDK libusb client after replaying the vendor start-up sequence. These
are what a **handshake-then-read** client gets:

| Endpoint | Bytes per trigger cycle | Content |
|---|---|---|
| `0x81` | 1,024 | tracking-class records (5.2) |
| `0x82` | 0 | nothing, in every capture attempted |
| `0x83` | 65,536 | 1280-wide 16-bit image samples (5.3) |
| `0x84` | 65,536 | 12-bit field with `0x0FFF` invalid sentinel (5.4) |

`[VERIFIED]` — reproduced across repeated trigger cycles.

**Those figures are a property of the client, not of the device.** With bulk reads already
pending on the endpoints *while* the control sequence runs, the same device delivers 100 to
155 full 1280x720 frames per 12 s on EP 0x83. See 5.3 and 5.5. `[VERIFIED]`

The vendor software's own URB sizes (from a passive capture) were larger: 16,384 B
requested on EP 0x81, 262,144 B on EP 0x82, 131,072 B on EPs 0x83 and 0x84. EP 0x81
completed with 256-byte chunks. EPs 0x82–0x84 completed with **zero** bytes in that
capture. `[CAPTURED]`

**Do not infer the endpoint map from URB sizes.** The vendor software submits huge URBs
to endpoints that return nothing, and modest URBs to the endpoint that carries data. The
sizes describe the software's intent, not the device's behaviour.

## 5.2 EP 0x81 — record stream

Fixed 256-byte records. Over a 7,545,344-byte capture: 29,462 records located by their
tag, of which 29,447 were exactly 256 bytes apart. `[VERIFIED]`

Record layout, offsets relative to the record tag:

```
+0    45 00 00 ea          record tag
+4    u32                  timestamp-like, microseconds scale (see below)
+8    u32                  sequence value: 897 in 25,201 records, 896 in 4,253, 883 in 5
+12   u16, u16, u16        varying small integers
+18   u16, u16             varying small integers
+22   f32                  observed range -126.4992 .. 1.4061, mean -23.6698
+26   u16                  varying, common values ~4060-5281
+28   45 slots x 4 bytes   slot k at +28 + 4k, k = 0x00..0x2C
                             byte 0: slot index (equals k)
                             bytes 1-3: value, 0xFFFFFF = absent
+208  u32                  same sequence value as +8
+212  u32                  second timestamp-like value
+216  ba ab ed fe          magic
+220  u16, u16             102, 102  (29,460 of 29,462 records)
+224  ef be ad de          magic (0xDEADBEEF)
+228  u32                  sentinel; 0xDADDF00D in the majority of records, not all
+232  u32                  0
+236  u32                  varies: 29,147 distinct values across the capture
+240  u32                  0
+244  ab ba ed fe          magic
+248  u16, u16             102, 102
+252  u32                  44  (29,448 of 29,462 records)
```

`[VERIFIED]` as observed framing.

### The 45-slot table

Slot indices run `0x00` through `0x2C` — **45 slots**, not 44. The `u32 = 44` at offset
+252 is adjacent to the last slot and is easy to mistake for the slot count; the table
itself has 45 entries. `[VERIFIED]`

Across the entire 7.5 MB capture, **every slot value was `0xFFFFFF` (absent) in every
record** — one single non-absent value in 29,462 records. `[VERIFIED]`

So in this capture the device reported no feature points at all. That is consistent with
a headset sitting still on a desk with poor texture, but it means **the slot contents
have never been observed populated**. Their meaning is `[UNKNOWN]`.

### Timestamps

The two u32 fields at +4 and +212 are consistent with microsecond timestamps: the
difference between them is tightly clustered around 83,700–83,930 µs. `[VERIFIED]` that
the difference is stable; `[INFERRED]` that they are µs timestamps.

They are **not** a simple per-record clock. Consecutive records differ by values that
cluster near 290,000–296,000, and one record in the sample jumped by 448,000,000. A
u32 microsecond counter wraps every 4295 s, and the observed values (~3.13e9) are near
that wrap. `[VERIFIED]` the observations; `[UNKNOWN]` the exact clock semantics.

Do not build a timeline on these fields until their wrap behaviour is characterised.

### Alignment warning

The record tag is **not** at a fixed offset within the 256-byte URB completion. In the
assembled stream the tag appeared at `offset mod 256` = 8 (16,343 times), 4 (11,715),
12 (1,272), 16 (128), 0 (5). `[VERIFIED]`

A reader must therefore **resynchronise on the tag**, not assume that URB boundaries
coincide with record boundaries. They do not.

Caveat on this measurement: the stream was assembled by concatenating per-URB payloads
from a passive capture. A small number of the alignment shifts may be assembly
artifacts rather than device behaviour. The need to resync on the tag is real either
way. `[UNCERTAIN]` which.

## 5.3 EP 0x83 — the camera stream

Each trigger cycle yields one 65,536-byte block. Interpreted as little-endian u16:
32,768 samples. `[VERIFIED]`

Statistics over an 8,126,464-byte capture (124 blocks):

```
min 0   max 65,399   mean 20,803.8   median 19,585
5th percentile 8,833    95th percentile 38,271
non-zero fraction 0.9999
values above 4095: 4,062,632 of 4,063,232  -> this is 16-bit data, not 12-bit
```

`[VERIFIED]`

### It is an image, and the row stride is 1280

Established by autocorrelation of the 16-bit sample stream — mean `|v[i] - v[i+L]|` for
lag `L`:

| Lag | Mean abs difference | Reading |
|---|---|---|
| 1 | 1,096 | horizontal neighbours — best |
| **1280** | **1,342** | **row stride — the only strong non-trivial minimum** |
| 1279 / 1281 | 1,638 / 1,612 | off-by-one, clearly worse |
| 1312 | 4,202 | another plausible camera width — **not** the stride |
| 2560 | 1,895 | harmonic of 1280 |
| 2048 | 14,089 | random-pair level |

`[VERIFIED]`

1312 was tested specifically because it is another width the device's software is
associated with; the data rejects it. `[VERIFIED]`

Independent confirmation: rendered strips of 1280×25 pixels from three separate blocks
show a smooth vertical gradient, with row means 15,704 → 18,801 → 19,626 → 19,962 →
19,991 → 20,157 → 20,298 → 20,363, and the same gradient repeats across blocks. A
random or non-image buffer does not produce that. `[VERIFIED]`

### The frame record — 1,843,232 bytes per frame

Visible only once bulk reads are kept pending during the control sequence (5.5). From a
93,880,320-byte capture: 51 frame records, spaced by exactly **1,843,232 bytes =
1280 x 720 x 2 + 32**. `[VERIFIED]`

EP 0x83 therefore carries **whole 1280x720 16-bit frames**, each followed by a 32-byte
record:

```
+0    ba ab ed fe        magic
+4    u16 51, u16 51
+8    ef be ad de        magic (0xDEADBEEF)
+12   u32 0xDADDF00D     little-endian on the wire
+16   u32 0
+20   u32 counter        102, 103, ... 152 — +1 per frame, monotonic across all 51
+24   4 x u16            (18345, 25689, 28331, 32322), (19879, 26710, 29866, 32832),
                         (18853, 26199, 28587, 32323) — meaning [UNKNOWN]
```

`[VERIFIED]`

50 complete frames were recovered from that capture. Frame 0 versus frame 1: sampled mean
`|diff|` = 1,022 with only **3.8%** of samples identical. Distinct acquisitions, not one
repeated buffer. `[VERIFIED]`

### Withdrawn: the 65,536-byte "block" model

The earlier reading — "each 65,536-byte block = 32,744 sample slots + a 48-byte trailer at
byte 65,488, so a block is 25.58 rows, and blocks are independent acquisitions that cannot
be concatenated" — is **withdrawn**. It measured the URB size of a handshake-then-read
client, not the device's framing. Evidence for the withdrawal: `[VERIFIED]`

- With pending bulk URBs, the same magics (`baabedfe`, `efbeadde`, `0xDADDF00D`, the
  `u16 51, 51` pair) appear once per 1,843,232 bytes, not once per 65,536.
- The counter in that record advances once per **frame**, not once per 65,536-byte URB.
- The spacing is exactly one 1280x720 16-bit frame plus 32 bytes, with no remainder. The
  "25.58 rows, not a whole number of rows" observation was an artefact of cutting the
  stream at URB boundaries.

The autocorrelation result (row stride 1280) is unaffected and stands.

## 5.4 EP 0x84 — the 12-bit field

**Frame size: 202,784 bytes.** With bulk reads kept pending (5.5), the stream resolves into
435 frames whose frame records are spaced by exactly **202,784 = 202,752 + 32**. 435 of the
441 record-to-record gaps in an 88,604,672-byte capture hold that value; the exceptions are
four records 32 bytes apart at the start and two partial frames at the end. `[VERIFIED]`

Frame record (32 bytes), same shape as EP 0x83's:

```
+0    ba ab ed fe        magic
+4    u16 34, u16 34     (EP 0x83 carries 51, 51 in this slot)
+8    ef be ad de        magic (0xDEADBEEF)
+12   u32 0xDADDF00D
+16   u32 0
+20   u32 counter        224399 -> 224851; +1 in 420 of 434 transitions, +2 in 12, +3 in 1
+24   u32                advances by exactly 8,388,609 = 2^23 + 1 per frame in 347 of 434
                         transitions, with wrap discontinuities in the rest. Meaning
                         [UNKNOWN]; it is timestamp-like.
+28   u16 288            6 distinct values across 435 frames
+30   u16                9 distinct values across 435 frames
```

`[VERIFIED]`

Payload = 202,752 bytes = 101,376 u16 samples, split as:

- **Header: the first 696 bytes (348 samples) are byte-identical across all 435 frames.**
  Sample 0 is `0x0000`; the rest are `0x0FFF` with a handful slightly below (4091, 4031,
  4094, 3839, 3551, 3519, 2303, 1983). `[VERIFIED]`
- **Image region: 202,056 bytes = 101,028 samples.** `[VERIFIED]`

Field statistics over the payload:

```
values above 4095: 2 of 101,376      -> 16-bit containers holding 12-bit values
values equal to 4095 (0x0FFF): 339, the same count in all 200 frames sampled,
                                 and every one of them lies inside the 696-byte header
mean 2,066.7                          body values tightly clustered
```

`[VERIFIED]`

Consecutive frames differ in 99.4% of sampled values; frames 15 apart differ in 89.5%. This
is live data, not a repeated buffer. `[VERIFIED]`

### Withdrawn: the 65,536-byte block reading of EP 0x84

The earlier description — a 65,536-byte block with a header beginning at +4, containing
`u16 1312` as an explicit field — is **withdrawn**. It was a URB-sized slice of the
202,784-byte frame above, cut at an arbitrary point. `[VERIFIED]`

### Geometry: not established

Autocorrelation of the image region finds essentially no structure:

| Lag | Mean abs difference |
|---|---|
| 352 | 31.11 |
| 704 | 29.00 |
| 1056 | 31.76 |
| 1408 | 28.90 |
| 2112 | 30.99 |
| random pair | 35.4 |

For contrast, the same measurement on EP 0x83 gives **1,012 at the known stride 1280 against
a random-pair baseline of 21,100** — a 95% drop. Here the best minimum is 18% below
baseline. The 352 / 704 / 1408 / 2112 family is harmonic, and 704 × 144 = 101,376 matches
the payload sample count exactly, so **704 is the leading candidate stride** — but the
evidence is far too weak to claim it. `[INFERRED]`; treat the geometry as `[UNKNOWN]`.

Interpretation as **depth / range data** remains `[INFERRED]`: the 12-bit sentinel, the
tight clustering and the vendor SDK's point-cloud API support it, and nothing confirms it.

**The mapping from these numbers to metres is not known.** Do not attempt to convert them
to distances yet. `[UNKNOWN]`

## 5.5 Throughput

**Handshake-then-read** — one synchronous read per endpoint after each trigger: 145 cycles
in 40.4 s = 8,126,464 bytes = **197 KB/s** on EP 0x83. `[VERIFIED]`

**Pending-URB client** — a looping reader per endpoint, started *before* the control
sequence and left running: `[CAPTURED]`

| Control pattern kept running | Frames of 1,843,232 B | MB/s | fps |
|---|---|---|---|
| Last 100 transfers of the 417, looped | 154.7 | 21.03 | 11.4 |
| 27 unique tail OUTs, no INs, no `0xb007` | 100.1 | 18.42 | 10.0 |
| Full 417-transfer sequence, looped | 52.9 | 5.13 | 2.8 |
| 30 unique OUTs **including** `0xb007` writes | 7.4 | 1.37 | 0.6 |
| All 138 OUTs in original order, no INs | 0.0 | 0.00 | 0.0 |
| One `3d40b0070180` repeated 7,273 times | 0.0 | 0.00 | 0.0 |
| No control traffic at all | 0.07 | 0.01 | 0.0 |

EP 0x84 streamed concurrently in the same runs (88.6 MB in one 62 s session). Its frame
spacing has **not** been established. `[UNKNOWN]`

The vendor SDK delivered 141 RGB frames in a 45 s session (~3.1 fps). `[CAPTURED]` The
no-SDK client now exceeds that. **The gap was never the bus and never a missing command —
it was that no URB was pending when the device's buffer filled.**
