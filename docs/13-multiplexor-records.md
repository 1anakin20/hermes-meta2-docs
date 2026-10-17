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
