# 5. Data streams

All sensor data arrives on the four bulk IN endpoints. There is no bulk OUT.

## 5.1 Endpoint behaviour

Measured with a no-SDK libusb client after replaying the vendor start-up sequence:

| Endpoint | Bytes per trigger cycle | Content |
|---|---|---|
| `0x81` | 1,024 | tracking-class records (5.2) |
| `0x82` | 0 | nothing, in every capture attempted |
| `0x83` | 65,536 | 1280-wide 16-bit image samples (5.3) |
| `0x84` | 65,536 | 12-bit field with `0x0FFF` invalid sentinel (5.4) |

`[VERIFIED]` — reproduced across repeated trigger cycles.

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

### Block trailer

Each 65,536-byte block ends with a 48-byte record at offset 65,488:

```
+65488  ba ab ed fe        magic
+65492  u16 51, u16 51
+65496  ef be ad de        magic (0xDEADBEEF)
+65504  u32 0xDADDF00D
+65508  u32 0
+65512  u32 counter        3759, 3760, 3761 in three consecutive blocks -> +1 per block
+65516  12 x u16           values ~6,000-10,000, varying
```

`[VERIFIED]`

The counter incrementing by exactly 1 per block means **each block is one numbered
acquisition unit**, not an arbitrary slice. `[VERIFIED]`

So a block is 32,744 sample slots (bytes 0..65,487) plus a 24-slot / 48-byte record
(bytes 65,488..65,535). 32,744 / 1280 = **25.58 rows**, so a block does not contain a
whole number of rows. `[VERIFIED]` arithmetic.

### Blocks are independent acquisitions

Consecutive blocks are **not** consecutive slices of one frame: the difference across a
block boundary (11,331) is an order of magnitude larger than the within-row difference
(1,112). `[VERIFIED]`

This is important: you cannot concatenate blocks and get a taller image. Each block is a
separate acquisition.

## 5.4 EP 0x84 — the 12-bit field

One 65,536-byte block per trigger cycle. `[VERIFIED]`

Header region:

```
+0    u32            varying
+4    ba ab ed fe    magic
+8    u16 34, u16 34
+12   ef be ad de    magic
+16   u32 0xDADDF00D
+20   u32 0
+24   u32            varying
+28   u16 0, u16 22
+32   u16 1312, u16 0     <- 1312 appears as an explicit field value
+36   ... 0x0FFF repeated  <- invalid / no-data entries
```

`[VERIFIED]`

Body statistics (offsets 64..65487, 32,712 u16 values):

```
min 0   max 46,532   mean 2,051.5
values equal to 4095 (0x0FFF): 325
values above 4095: 2
most common values: 2017, 2021, 2023, 2025, 2026, 2027, 2029, 2030, 2032, 2033
```

`[VERIFIED]`

The body is a tightly clustered field (adjacent values differ by ~5) with `0x0FFF` used
as an explicit "no data" sentinel. `[VERIFIED]`

Interpretation as **depth / range data**: `[INFERRED]`. Supporting: the 12-bit sentinel,
the tight spatial smoothness, and the presence of a point-cloud API in the vendor SDK.
Contradicting or at least unresolved: the field is **not** uniformly 12-bit (a few
values exceed 4095), and autocorrelation shows no clean 1280 stride here (lag 1 → 5.4,
lag 1280 → 8.5), so its geometry is not established.

**The mapping from these numbers to metres is not known.** Do not attempt to convert
them to distances yet. `[UNKNOWN]`

## 5.5 Throughput

Re-triggering the control handshake in a loop: **145 cycles in 40.4 s = 8,126,464 bytes
= 197 KB/s** on EP 0x83. `[VERIFIED]`

For comparison, a 1280×720 16-bit frame is 1,843,200 bytes ≈ 28 blocks. At 197 KB/s the
observed rate is about **6.5 blocks' worth per second**, i.e. roughly a quarter of one
frame per second if blocks were slices — which they are not (5.3).

The vendor SDK delivered 141 RGB frames in a 45-second session (~3.1 fps of full
1280×720 frames). `[CAPTURED]` The device is therefore capable of far more than the
no-SDK client currently extracts; the gap is the streaming trigger, not the bus.
