# 16. The time base: what the three endpoints actually stamp

Phase 1 of `docs/15-shipping-plan.md`. Question: can RGB frames, mono frames and IMU
samples be put on one clock?

Measured with `meta2lib examples/meta2_capture_live.c … gate tries=5 probe=4 clock`,
12 s windows, all four endpoints, warm mask `0x7e`, fast sustain. Two sessions are
quoted throughout because the difference between them is itself the finding — and they
are **not the same kind of session**:

| | session A | session B |
|---|---|---|
| reader queue | 1 | 8 |
| gate | **accepted**, attempt 2 of 5 | **rejected on all 5 attempts** (coverage 23.2 / 2.5 / 7.5 / 2.6 %) |
| state | healthy | starved |
| mono fragments/s per tag | 11,669 | 496 |
| mono complete frames | 41.7 % | 75.8 % |
| mux records | 4,215 | 384 |

Session B is the last attempt, which the tool analyses rather than discards. Its
numbers are therefore a **starved-session** measurement. That turns out to strengthen
§16.1 rather than weaken it: the quantity that mattered did not change between a
healthy and a starved session. Session A's own accepted verdict was coverage 111.6 %,
i.e. its mux span exceeded its window — see §16.4.

---

## 16.1 The mono fragment timestamp is a sample counter, not a wall clock

Field: u32 at fragment `+4084` (fragment starts at the `baabedfe` magic; the 12-byte
`MONO_MAGIC` begins 8 bytes earlier, which is why `src/mono.c` backs up by 8).

Measured on **neighbour pairs only** — consecutive fragments whose u16 counter at
`+12` differs by exactly 1. Such a pair cannot straddle a reorder, so its delta is a
real inter-fragment interval and needs no wrap correction.

| | session A | session B |
|---|---|---|
| fragments per tag | 140,067 | 5,953 |
| neighbour pairs | 137,029 (97.8 %) | 5,879 (98.8 %) |
| delta p10 / median / p90 | 8,913 / **9,204** / 9,205 | 8,913 / **9,204** / 9,205 |

The delta distribution is **identical in a healthy session and a starved one whose
fragment rates differ by 23.5×**. A wall clock would give a delta proportional to the
rate; this one does not move at all, and it does not move between session states
either. The field advances by a fixed ≈9,204 ticks per fragment delivered.

Consequence, and it is the load-bearing one: **mono timestamps order samples and
measure gaps in sample units, but they do not tie mono to real time by themselves.**
`9,204 × fragments/s` is 107.40 MHz in session A and 4.57 MHz in session B — a number
that describes how fast the host happened to be drained, not a device frequency.

**This withdraws the 336.29 MHz figure** recorded during the dropped-frame work
(`scratch/mono_clock.py`). That script computed `ts[last] - ts[first]` over the host
window, which is exactly `9,204 × delivered fragment rate`. It reproduced cleanly
across tags at the time, which is why it looked like a clock, but it is a throughput
measurement wearing a clock's clothes. 336.29 MHz was one session's drain rate.

## 16.2 The two mono cameras are not simultaneous — and that is fine

Match tag `0x44` (wearer's left) against tag `0x55` (wearer's right) at equal
reconstructed counters:

| | session A | session B |
|---|---|---|
| matched pairs | 3,905 | 3,465 |
| B ahead / behind / equal | 3,900 / 5 / **0** | 3,462 / 3 / **0** |
| B − A median | 586,665 ticks | 588,961 ticks |
| median ÷ 9,204 | 63.74 | **63.99** |

Never equal, ahead in 99.87 % of pairs, and the offset is **64 fragment intervals**
to within 0.2 %. That is a fixed pipeline skew, not jitter.

So mono stereo is usable, but a fusion layer must apply a constant −64-fragment
correction to align the two cameras. Expressed in samples: 64 fragments × 4,064 data
bytes = 260,096 B = 130,048 samples ≈ 173 image rows of 752.

## 16.3 RGB has no timestamp in its record header

Every 4-byte-aligned slot of the 32-byte EP `0x83` header, on adjacent record pairs
exactly `1,843,232` B apart (session A: 611 frames, 333 adjacent pairs):

| offset | first value | median delta | range | verdict |
|---|---|---|---|---|
| +4 | 3,342,387 | 0 | [0, 0] | constant per session |
| +8 | 3,735,928,559 | 0 | [0, 0] | constant per session |
| +12 | 3,671,977,997 | 0 | [0, 0] | constant per session |
| +16 | 0 | 0 | [0, 0] | zero |
| +20 | 36,573 | **1** | [1, 1] | frame counter |
| +24 | 427,890,053 | 133,827,327 | [253, 4,294,967,291] | no stable delta |
| +28 | 427,761,285 | 4,160,684,293 | [64,769, 4,294,967,295] | no stable delta |

Session B (starved) gives the same picture (`+4/+8/+12` constant, `+20` counter, `+24/+28`
spanning the whole u32), so the absence of an RGB timestamp is not an artifact of session state. The `+24`/`+28` pair was also read as one 64-bit value, in
case RGB carried its clock the way the mux record does; the apparent u64 fields at
`+8`, `+16`, `+20`, `+24` are arithmetic artifacts of combining adjacent u32s (the
`+16` u64 delta is exactly 2³², i.e. the counter crossing into the high word), not
64-bit fields.

**Conclusion as measured: no timestamp in the RGB record HEADER.** RGB frames can be ordered by
the `+20` counter and nothing else. Any RGB↔IMU alignment must come from host arrival
time plus the assumption that the counter is gap-free — and it is not gap-free:
RGB exact-gap framing is 60–77 % in the all-four recipe (`docs/10` §10.5), so the
counter skips.

This is the answer to the Phase 1 question, and it is a negative one: **there is no
single device clock that covers RGB.**

### 16.3.1 That conclusion is withdrawn — the driver puts the timestamp in the trailer

`docs/09-driver-decompiled.md`, from `Meta.Driver.EndPointDataProcessors/DataScanner.cs`, defines a
**32-byte trailer present on all endpoints**, and the driver names a 64-bit timestamp inside it:

```
+0  TimeStampHi         +4  TimeStampLow
+8  SentinelHi          +12 SentinelLow
+16 FixedSentinelHi     +20 FixedSentinelLow
+24 PacketInformationHi +28 PacketInformationLow
IsHeader  = (PacketInformationLow & 0x01000000) != 0
PacketNum = PacketInformationLow & 0xFFFFFF
```

`FindTrailerIndex` searches `EF BE AD DE 0D F0 DD DA 00 00 00 00` and returns `i − 16`, and
`RGBEndPointDataProcessor` **finalises a frame when it reaches a trailer** — the trailer follows the
image data. So RGB does have a per-frame device timestamp; §16.3 swept only the 32 bytes at the
*start* of the record. Same driver source gives the mono header its own timestamp-like field at
`h+4` (observed `0xD0B254DF`).

`[VERIFIED]` that the driver defines these fields.

### 16.3.2 Where the trailer actually sits, measured on saved captures

`scratch/trailer_scan.py` and `scratch/trailer_ts.py` over `burst83.bin`, `ir17_ep83.bin`,
`probe2_ep83.bin`, `probe_arm_strobe_ep82.bin`: in **all 122** `baabedfe` hits the driver's trailer
pattern sits exactly **8 bytes after** the magic - never at the end of the record. The driver returns
`i - 16`, so its 32-byte block starts 8 bytes *before* the magic:

```
magic-8   TimeStampHi        TimeStampLow     <- the 64-bit timestamp
magic-4   SentinelHi         SentinelLow      <- SentinelHi IS the baabedfe magic; SentinelLow IS the tag pair
magic+0   ba ab ed fe        tag u16 x2       <- what this project has been calling the record header
magic+8   EF BE AD DE 0D F0 DD DA 00 00 00 00
magic+20  PacketInformationHi   PacketInformationLow
magic+28  samples begin
```

The block is a **boundary**: it closes the previous frame and heads the next, which is why the driver
finalises a frame on reaching it. What has been treated as the record header magic is the middle of
the trailer.

**RGB does have a device timestamp.** `probe2_ep83.bin`, 25 records, byte distance between magics
exactly 1,843,232 in all 24 gaps (100% complete frames, `probe2.log`: 12.0 s, 3.94 MB/s, 13 timeouts):

```
ts deltas:  min 3,927,220   median 3,927,221   max 3,927,227   negative 0/24
PacketNum:  38929, 38930, 38931, 38932 ...     +1 per record
isHdr:      0 in every record;  FixedSentinels deadbeef / daddf00d in every record
```

Mono, same scan: ts deltas median 1,963,229 - **2.0003x smaller than RGB's** - and PacketNum
interleaves two sequences (500772, 534470, 500773, 534471), i.e. the two cameras. `[INFERRED]` a
shared time base with a 2:1 relationship; unconfirmed.

These are **device-side bytes**, not host-added: they were read from raw bulk-IN transfers by our own
libusb code with no Meta driver in the process, and a C# `DataScanner.cs` cannot inject bytes into a
bulk transfer another process reads from the endpoint.

Still `[OPEN]` the tick-to-second scale. `probe2.log` gives 25 RGB frames in 12.0 s = 2.08 fps, which
would put the clock at 8.18 MHz - but that assumes frames were evenly spaced in real time in a run
that delivered 3.94 MB/s with 13 timeouts. A 26 MHz unit (see §16.5) would mean 151 ms per frame =
6.6 fps, contradicting every RGB rate measured in normal runs (28-52 fps); 120.8 MHz gives 30.8 fps
and 183 MHz gives 46.6 fps, which bracket the measured range.

Note the shape: mono advances a fixed 9,204 ticks per fragment, RGB a fixed 3,927,221 per frame, both
invariant to throughput. That is still counter-like, not clock-like. `[OPEN]`.

## 16.5 The mux timestamp is neither clock nor counter

EP `0x81`'s u64 at record `+20`:

| | session A | session B |
|---|---|---|
| records | 4,215 | 384 |
| max − min | 1,734,946,586 | 57,072,886 |
| per record | 411,613 | 148,627 |
| (max−min)/window | 144.53 MHz | 4.76 MHz |
| ts[last] − ts[first] | 581,809 | 57,072,886 |

Not a wall clock (span/window varies 30×). Not a fixed per-record increment either
(411,613 vs 148,627). And in session A the last record's timestamp is *below* the
first record's by a factor of ~3,000 while max−min is 1.7×10⁹ — the timestamps are
not monotonic down the stream.

The likely explanation, **unproven**: the mux interleaves tags (`119` IMU0, `102`
IMU1, `136` MICS, `153` BUTTONS, `170` NULL_AA) and each tag carries its own
timestamp base, so a max−min across all tags mixes domains. `src/health.c` already
has to exclude `NULL_AA` (timestamp always 0) for the same reason. **The next
measurement is per-tag mux clocks**, which has not been done.

Until that is done, the gate's `182–184 MHz` remains a reliable *health signature*
(it separated healthy from starved in every validation run, `docs/10` §10.8) but it
is not yet established as a device frequency, and no ratio to the mono tick domain
can be computed.

## 16.5 A transport fact that invalidates naive timestamp work

The queued reader keeps `queue` bulk transfers outstanding and they complete in
whatever order the host controller finishes them, so the ring holds **blocks of
`read_size / 4096` fragments out of order** — 16 blocks at `read_size = 65536`.

Evidence: session A's mono counters were contiguous in 97.8 % of adjacent pairs and
the first three attempts at this measurement reported 556–1,060 "u32 wraps" that were
reorder artifacts, not wraps. Counter reconstruction that assumes buffer order
inflates by 65,536 at every out-of-order boundary.

Any timestamp analysis in this library must either use queue 1 or sort on a
reconstructed counter. This is a caveat on `meta2_reader_start_async()` and on
`meta2_mono_feed()`, which resynchronises on descriptors and therefore tolerates the
reordering rather than detecting it.

## 16.6 What Phase 1 can now be told to do

Settled:
- Mono fragment timestamp exists, is stable, and is a **sample-domain** counter
  (9,204 ticks/fragment).
- Mono A/B skew is a **constant 64 fragments**.
- RGB has **no** device timestamp.

Open, in priority order:
1. Per-tag mux clocks on EP `0x81` — is there one device time domain or five?
2. The mono fragment→sample→frame mapping in device time: 9,204 ticks per fragment
   is exact, but the tick→second scale is unknown, so mono gaps are currently
   measurable only in fragments.
3. Whether the `+24`/`+28` RGB header fields mean anything at all (they are the only
   unexplained bytes in the record).

What this changes in the shipping plan: **tight RGB+IMU fusion is not available from
device timestamps.** A VIO pipeline built on this library would align IMU to mono
(in the mono sample domain, with the 64-fragment correction) and treat RGB as an
ordered but loosely-clocked stream. That is a real limitation to state in the README,
not to paper over with host arrival time.
