# 13. EP 0x81 multiplexor record format (experiment E3)

Everything here was measured on `2cfa:00f3` with the harness in `meta2lib/tools/`
and cross-checked against the decompiled vendor driver.

## 13.1 Record layout — exact

Every EP 0x81 record is **256 bytes**, spacing measured at exactly 256 in
22,584 consecutive records.

| offset | size | content |
|---|---|---|
| `+0..7` | 8 | magic `00 00 00 00 ab ba ed fe` |
| `+8..11` | 4 | tag as u16, repeated: `tag, 00, tag, 00` |
| `+12..15` | 4 | u32 payload length — `44` for IMU records, `176` for MICS |
| `+16..19` | 4 | per-tag field (`45 00 00 ea` for IMU, `00 00 00 00` for MICS) |
| `+20..27` | 8 | u64 LE device timestamp |
| `+28..239` | 212 | payload region (see 13.3) |
| `+240..251` | 12 | trailer sentinel `efbeadde 0df0ddda 00000000` |
| `+252..255` | 4 | u32 packet counter, monotonic `+1` across all tags |

The magic is `ab ba ed fe` — 171, 186, 237, 254. It is easy to mis-transcribe as
`ab be ed fe`; that mistake produces zero header hits and looks like the endpoint
carries no records at all.

## 13.2 Tag mapping — corrected against the vendor code

`DataScanner.IsIMU0Header` tests **119** and `IsIMU1Header` tests **102**. Earlier
notes in this project had them the other way round; the vendor code is authoritative.

| tag | hex | vendor name |
|---|---|---|
| 119 | `0x77` | IMU0 |
| 102 | `0x66` | IMU1 |
| 136 | `0x88` | MICS |
| 153 | `0x99` | BUTTONS |

Multiplexor feed mask bits (`MultiplexorEndPointStateController`): IMU0 = 1,
IMU1 = 2, Mics = 4, Buttons = 8.

## 13.3 The "212 unmapped bytes" are a slot table, not mystery data

The payload region is a fixed 212 bytes whose contents depend on the tag.

**IMU record:** 16-byte IMU block, then **45 four-byte slots** of the form
`[slot index 0..44, ch1, ch2, ch3]`, then a 16-byte tail (`u32 146`, u32 timestamp,
`ba ab ed fe`, tag repeated). In every record of every capture so far, all 45 slots
read `[index, ff, ff, ff]` — the slot index increments 0..44 identically in every
record and the three channel bytes are always the `0xff` invalid marker.

**MICS record:** 176 bytes of audio, then 5 empty slots, then the same 16-byte tail.

So the unmapped region is an unfilled slot table. It is not a hidden sensor channel.
Whether those slots ever populate under some other enable state is **not established**.

## 13.4 Microphones do stream — the earlier negative result was an artifact

An earlier screening concluded that mux mask `0x1f` produced no microphone data.
That was wrong, and the reason is the endpoint's stall behaviour:

- With **only** an EP 0x81 reader attached, the endpoint flushes a fixed backlog of
  about **645 records** and then goes completely silent, no matter how many sustaining
  commands are sent (762 strobes produced nothing further).
- With **all four endpoints drained**, EP 0x81 sustains: 22,585 records in 36 s
  (627/s), 11,869 in 20 s (593/s), 8,547 in 15 s (570/s).

Any experiment that reads EP 0x81 alone is measuring a backlog, not a live stream.

## 13.5 Microphone sample format

Each 176-byte audio block is 44 groups of 4 bytes. The **low byte of every group is
always `0x00`** (verified over 149,028 groups), so a sample is a 24-bit signed
little-endian value in bytes 1..3:

```
sample = b1 | b2<<8 | b3<<16      (sign-extend from 24 bits)
```

Every group is **duplicated in an identical pair** — verified in 3,387 of 3,387
records — so a record carries 22 unique samples.

Sample values observed: quiet baseline std 82,546, peak-to-peak 728,800 of the
16,777,215 full-scale range.

## 13.6 Microphone sample rate — measured, with one unexplained discrepancy

A 1 kHz tone hard-gated at 10 Hz was played on the headset. The gate is visible in
the data as a clean square-wave envelope, and its period was measured three ways:

- envelope autocorrelation: peaks at 842, 1,683, 2,524, 3,363 samples (multiples of 841.5)
- envelope spectrum: 0.001190 cycles/sample → 840.5 samples per gate period
- record arrival rate: 370.5 MICS records/s × 22 samples = 8,150 samples/s

A 100 ms gate period of 840.5 samples gives **8,405 samples/s**, consistent with the
arrival-rate figure to within 3 %.

**Unresolved:** the 1 kHz carrier does not appear at 1 kHz in that stream. At an
8,405 samples/s rate the tone should have period 8.4 samples; the measured carrier
period is 34.9 samples, i.e. **240.6 Hz**, a factor of 4.15 low. The 1 kHz bin holds
0.014 relative amplitude and 2 kHz holds 0.004. Splitting the stream into 1, 2, 3, 4,
6, 11 and 22 interleaved phases shows 240.6 Hz in every phase, so it is not channel
interleaving. 240.6 Hz is also 4 × 60 Hz, and 48.8 Hz is present too, which is
consistent with mains-related pickup rather than the played tone.

This is stated as unresolved rather than smoothed over.

## 13.7 Microphone occlusion — inconclusive

One continuous 36 s capture, coached: tone playing uncovered, tone playing with a
finger pressed over the front faceplate, then uncovered with the tone stopped.

| phase | std | mean abs | peak-to-peak |
|---|---|---|---|
| A tone, uncovered | 100,846 | 74,482 | 5,649,776 |
| B tone + finger covering | 89,545 | 71,571 | 764,960 |
| C uncovered, tone stopped | 95,842 | 73,988 | 2,652,016 |

Standard deviation barely moves (11 %), while peak-to-peak drops 7× under the finger.
The physical microphone location on the headset is unknown, so covering the faceplate
centre is not a controlled occlusion. **This test neither proves nor disproves that
the payload is acoustic.** Microphone work is deprioritised for the first version of
the custom SDK.

## 13.8 IMU left/right signature

Both accelerometers measure gravity at a scale of about 16384 counts, with **opposite
Y signs**:

| tag | mean ax | mean ay | mean az |
|---|---|---|---|
| IMU0 (119) | 3,884 | **+13,014** | 9,976 |
| IMU1 (102) | 4,995 | **−12,736** | 9,257 |

Magnitude ≈ 16,850 and ≈ 16,517 counts. The mirrored Y axis is the left/right
mounting signature, and it gives the same kind of independent side assignment that
the RGB-bridge test gave for the mono cameras. It has **not** yet been confirmed
against the calibration file's `accelerometer_left` / `accelerometer_right` blocks.

## 13.9 Buttons — mapped in the driver, never yet observed on the wire

`ButtonType` is `None=0, Video=1, VolumeUp=2, VolumeDown=4, Power=8`; `ButtonState`
is `Release=0, ShortPress=1, LongPress=3`. Tag 153 (BUTTONS) has never appeared in
any capture, including captures with mux bit 3 (Buttons) set. Button records are
presumably event-driven, so a press experiment is the way to see them. The operator
has independently reported that holding the left-arm light button toggles the HDMI
display off and on with an audible "bloop", which is consistent with a Power-type
button existing and being handled by the headset's own SoC rather than by USB.

## 13.10 A fifth record type: tag `0xAA` (170)

This was found by *building* the C parser (E9), not by planning E3. Once a parser
accepted only the four documented tags, one 256-byte block in an otherwise perfectly
framed capture was silently skipped. Scanning every EP 0x81 capture on disk found it
in ten of them:

| capture | bytes | records | `0xAA` records | mean counter spacing |
|---|---|---|---|---|
| `ep81.bin` | 7,545,344 | 29,475 | 11 | 2,656 |
| `conc_ep81.bin` | 1,802,752 | 7,042 | 3 | 2,648 |
| `occl_uncover_ep81.bin` | 2,280,448 | 8,908 | 4 | 2,623 |
| `e3mic_occl_ep81.bin` | 5,781,760 | 22,585 | 1 | – |
| `occl_cover_left_ep81.bin` | 1,388,800 | 5,425 | 1 | – |
| `occl_cover_right_ep81.bin` | 1,395,456 | 5,452 | 1 | – |
| `probe3_ep81.bin` | 1,377,024 | 5,379 | 1 | – |
| `probe7_ep81.bin` | 684,800 | 2,677 | 1 | – |
| `e3mic_tone_ep81.bin` | 165,376 | 646 | 1 | – |
| `e4b_ep81.bin` | 33,536 | 131 | 1 | – |

25 records total, and every one has the same shape:

| field | value |
|---|---|
| header tag at `+8` / `+10` | 170, repeated |
| payload length at `+12` | **0** |
| per-tag field at `+16` | 0 |
| timestamp at `+20` | **0** |
| trailer sentinel at `+240` | valid |
| packet counter at `+252` | normal, in sequence |
| payload `+0..11` | three u32: `a` in 35..40, `b` in 48..52, `c` in 407..519 |
| payload `+12..195` | 46 slots `[index, ff, ff, ff]` |
| tail `+196..199` | u32, varies widely (2 … 897) |
| tail `+200..203` | u32 timestamp, non-zero |
| tail `+208..211` | tag u16 repeated = **102**, not 170 |

It is periodic, not random: consecutive `0xAA` records are 2,623–2,656 counters apart
across four captures that contain several of them, and their tail timestamps are
390–395 million clock units apart, which at the ~120.8 MHz clock in §13.7 is about
3.2 s. The third payload u32 drifts upward by roughly 1 per record
(452, 454, 455, 455, 456, 456, 457, 458 …).

**What it is: unknown.** It is not in the vendor driver. `DataScanner` tests only
119, 102, 136 and 153, so the vendor's own scanner does not recognise this record
either; it would fall through the same way ours initially did. The tail tag being 102
rather than 170 suggests it is emitted by whatever produces the IMU1 stream, but that
is inference, not evidence.

The practical consequence for a driver: **do not filter records by a known-tag
whitelist and assume the rest is padding.** A skipped record shows up as a 512-byte
gap between two otherwise 256-byte-apart records, which is exactly how this was
noticed.

## 13.11 Packet counter: +1 per record, but mic records share values

The earlier statement that the counter "advances by exactly 1 per record" was measured
on backlog-only captures, where it held 645/645. In a healthy sustained capture it is
not that clean:

| capture | steps | `+1` | repeated (`+0`) | skipped |
|---|---|---|---|---|
| `e3a_ep81.bin` (backlog) | 644 | 644 | 0 | 0 |
| `e3mic_occl_ep81.bin` (healthy) | 22,584 | 22,573 | 11 | 0 |
| `ep81.bin` | 29,470 | 29,157 | 311 | 2 |

In the healthy capture, **every one of the 11 repeats involves a MICS record** — the
tag pairs observed were `(136,102)`, `(136,119)` and `(136,136)`, and 6 of the 11 also
share a header timestamp. That matches §13.7's finding that microphone records arrive
in pairs. So the rule is: the counter advances by 1 per record, and a microphone
record sometimes carries the same counter as its neighbour. Treat the counter as an
ordering aid, not as a gap detector.

## 13.12 Framing: do not assume 256-byte alignment from byte 0

`ep81.bin` starts 240 bytes into a record — its first header is at offset 240, not 0,
because the capture began partway through a URB. Records are then 256 bytes apart
relative to that offset. A parser that indexes by `offset % 256` misreads the whole
file. Header magic search with tag and trailer validation (as in `meta2_mux_find`) is
the correct framing method; it also rejects the four stray magic hits that appear in
that file at spacings of 16 and 252.

## 13.11 EP 0x81 runs in three modes, and the timestamp span tells them apart (2026-10-25)

Nine runs of the all-four-endpoint recipe from `docs/10` §10.5 (queue 8, read_size 65536, mask
`0x7e`, mux `0x1b`, warm `0x7e`, fast sustain, 8 s windows). `meta2_mux_find` framing; **zero**
records byte-identical to the previous one in any run, so the high-rate modes are not re-sent
packets. `[VERIFIED]`

| records | IMU0/s | IMU1/s | counter span | timestamp span | ticks/record |
|---|---|---|---|---|---|
| 2403 | 147.4 | 150.5 | 1431 | 1478.3 M = 183.3 MHz | 615 k |
| 2984 | 183.5 | 189.3 | **2** | 0.59 M = 0.07 MHz | 199 |
| 3043 | 188.4 | 191.8 | **1** | 0.59 M = 0.07 MHz | 195 |
| 2120 | 130.4 | 130.7 | 1464 | 1499.1 M = 184.7 MHz | 707 k |
| 2139 | 130.3 | 132.0 | 1325 | 1502.3 M = 184.3 MHz | 703 k |
| 2750 | 168.5 | 170.7 | 1447 | 1476.6 M = 182.1 MHz | 537 k |
| 377 | 23.1 | 23.8 | 376 (monotonic) | 56.9 M = 7.08 MHz | 151 k |
| 377 | 23.4 | 23.7 | 376 (monotonic) | 56.4 M = 7.05 MHz | 150 k |
| 379 | 23.4 | 23.7 | 378 (monotonic) | 56.9 M = 7.08 MHz | 151 k |

IMU0 and IMU1 counts are within 2% of each other in **every** run, so a slow run is not a dropped
tag — both sensors slow together. `[VERIFIED]`

Three modes:

1. **Healthy** — 2100–2750 records, timestamp span 182–185 MHz × the window. Read as a ~183 MHz
   device clock, the span covers 8.0–8.2 s, i.e. the whole window. IMU rate **~130–171 Hz per
   sensor**. This is the mode a tracking front end needs.
2. **Starved** — 377–379 records, counter strictly +1, timestamp span 7.05–7.08 MHz. At 183 MHz
   that is 0.31 s of samples delivered into an 8 s window: the endpoint got ~4% of its data.
3. **Frozen** — ~3000 records, counter span 1–2, timestamp span 0.07 MHz = 3.2 ms of samples.
   Thousands of distinct records that all carry almost the same timestamp and counter. `[OPEN]` what
   produces this; it is not duplication (0 identical records) and it is not a plausible sample rate.

**The clock.** Mode 1 gives 182.1–184.7 MHz across four independent runs, agreeing to 1.4%, and it
lands inside the 172–205 MHz band that `docs/15` §3 inferred from captures where EP `0x83`/`0x84`
also stream. `[INFERRED]` that ~183 MHz is the device clock and that modes 2 and 3 are the endpoint
delivering a fraction of a window rather than a slower clock — modes 2 and 3 are self-consistent at
any clock, so the clock value is not independently pinned by them. The `~120.8 MHz` figure in §13.7
and the `~1.2e8` comment in `include/meta2/mux.h` are both superseded.

**Health gate for a tracking session:** do not count bytes — divide the mux timestamp span by the
window. A span near 183 MHz × window means the IMU stream is real; anything near 7 MHz or 0.07 MHz
means the session is starved and should be re-armed. Byte counts alone cannot tell mode 3 from mode 1.
