# 17. IMU calibration, and the tick rate that goes with it

Coached physical session, 2026-10-25, one continuous 400 s capture. This closes
shipping-plan item 4 (docs/15) and supersedes the tick-rate bracket in docs/16.

Capture: `meta2lib/examples/meta2_imu_log.c` through `meta2_stream_start()`
(`mask=0x7e mux=0x1b warm=0x7e/4s sustain=fast queue=8 read=65536
depth=unserviced gate=10 attempts=9 health=OK`), 96,137 mux records, coached by
`metavision/re/gyro_coach.py`. Files: `metavision/re/gyro_cal.csv`,
`metavision/re/gyro_marks.txt`. Analysis: `tools/gyro_calibration.py`.

---

## 17.1 Method

Nine coached steps, each marked by the coach with host-clock window edges:
`REST0`, then 360-degree turns `Y1 Y2` (vertical axis), `R1 R2` (front-back),
`P1 P2` (left-right), then `REST1`. Slow turns got an 8 s window, sustained turns
14 s. Windows are deliberately generous; nothing is derived from their edges
except the quiet windows used for bias.

**Scale comes from the magnitude of the integrated vector, not from the largest
component.** A 360-degree turn about any fixed axis integrates to a vector of
magnitude 360 degrees. Picking the dominant axis fails on this data because a
standing person's head turn is never pure: `R1` on IMU0 put -4339 counts·s on `gx`
and -3775 on `gz`, nearly tied. The vector magnitude is 5979 and is stable across
all six turns.

`B = SUM (count - bias) * dt_host` over one turn, `scale = 360 / |B|`.

---

## 17.2 Gyro bias `[MEASURED]`

Mean over the two quiet windows (1,909 and 1,935 samples per IMU):

| IMU | gx | gy | gz |
|---|---|---|---|
| IMU0 (tag 119) | +1.04 | -0.08 | +0.53 |
| IMU1 (tag 102) | +7.55 | +0.04 | -13.81 |

IMU1's bias is an order of magnitude larger than IMU0's. No sample in the whole
session came near i16 saturation (0 samples at or near ±32767), so the turns were
well inside range.

---

## 17.3 Gyro scale `[MEASURED]`

| step | coached axis | IMU0 integral | IMU1 integral | scale IMU0 | scale IMU1 |
|---|---|---|---|---|---|
| Y1 | vertical | 5840.4 | 5829.3 | 0.061639 | 0.061757 |
| Y2 | vertical | 5843.0 | 5809.2 | 0.061612 | 0.061971 |
| R1 | front-back | 5979.3 | 5945.9 | 0.060208 | 0.060546 |
| R2 | front-back | 5949.0 | 5934.6 | 0.060514 | 0.060661 |
| P1 | left-right | 5764.5 | 5720.1 | 0.062451 | 0.062936 |
| P2 | left-right | 5943.9 | 5943.3 | 0.060566 | 0.060573 |

Twelve turn integrals span 5720 .. 5979 - a 4.5% spread across three axes, two
speeds and both IMUs.

**Gyro scale = 0.0613 deg/s per count** (mean 0.061286, range 0.060208-0.062936),
i.e. **16.32 counts per deg/s**.

`[INFERRED, strong]` The part is configured for **±2000 deg/s**. That range's
nominal LSB size is 2000/32768 = 0.061035 deg/s per count, and the measurement is
+0.41% from it. The implied full scale at i16 saturation is 2008 deg/s. The
neighbouring standard ranges are excluded outright: ±1000 deg/s would be 101% off,
±2500 deg/s 20% off.

---

## 17.4 Tick rate: 117,821,900 Hz `[MEASURED]`

Over the whole 400 s session, per IMU, using the trailer timestamp of each
delivered record against the host clock:

| stream | host seconds | trailer span | ticks per host second |
|---|---|---|---|
| IMU0 | 399.975 | 47,125,741,018 | **1.178219e8** |
| IMU1 | 399.989 | 47,127,476,822 | **1.178218e8** |

The two independent streams agree to **0.0001%**. All 18 sub-windows (9 coached
steps × 2 IMUs) gave 1.1779e8 .. 1.1784e8 - within 0.05%. Timestamp deltas were
monotonic: 0 negative deltas in 47,738 and 48,397 consecutive pairs.

**The cross-check that pins it.** These cadences were measured independently in
docs/16 and are constant across every capture ever taken:

```
3,927,221 ticks/frame (EP 0x83 RGB)  / 117,821,900 = 30.0013 frames/s
1,963,229 ticks/frame (EP 0x82 mono) / 117,821,900 = 60.0143 frames/s
```

Those are the delivered rates measured independently in docs/10 §10.9: RGB
55.2 MB/s ÷ 1,843,232 B = 29.95 records/s, and 59.7 complete mono frames/s per
camera. Three independent measurements land on the same clock, and it makes both
cameras come out at exact integers.

**This supersedes the 162-205 MHz bracket in docs/16 §16.11 and the 183 MHz gate
constant.** At 183 MHz the same cadences would mean 21.5 fps RGB and 93.2 fps
mono, which no capture has ever delivered. The 162-205 bracket came from short
windows and from the gate's median-delta estimator; §17.5 of docs/16 explains why
the median estimator over-reads.

`[OPEN]` Whether the oscillator itself runs at 117.8 MHz, or runs faster and is
gated by production. The clock is production-coupled - a host-side 3.000 s stall
removed 500,101,379 ticks from the delivered span (docs/16 §16.11) - so a faster
but gated oscillator is not excluded. It does not matter for the library: 117.82
MHz is the value that converts cadence to seconds consistently across all three
endpoints. It is in the library as `META2_TICKS_PER_S`.

---

## 17.5 Accelerometer scale and the gravity anchor `[MEASURED]`

At rest, headset held upright, mean over the two quiet windows:

| IMU | ax | ay | az | magnitude |
|---|---|---|---|---|
| IMU0 | -2546.5 | **+15961.5** | +4820.0 | 16,867 |
| IMU1 | -876.4 | **-16028.0** | +3453.6 | 16,419 |

Gravity appears as **+y on IMU0 and -y on IMU1** - the two IMUs face opposite
ways. Magnitudes 16,867 and 16,419 counts for 1 g.

`[INFERRED, moderate]` Accelerometer full scale is **±2 g** (16,384 counts per g).
The measured magnitudes are 1.03 g and 1.00 g, and the 2.7% spread between them is
consistent with the headset not being perfectly upright rather than with a second
range. This one is weaker than the gyro result: it rests on 1 g being exactly
16,384 counts, which is a guess about the part's configuration, not a second
calibration. A coached "point the y axis straight down, then straight up" step
would settle it and is not yet done.

---

## 17.6 How IMU0's axes map onto IMU1's `[MEASURED, moderate confidence]`

Fitting the best signed permutation between the six turn vectors:

```
IMU1.x = + IMU0.z
IMU1.y = - IMU0.y
IMU1.z = + IMU0.x
```

Determinant +1 (a proper rotation, not a mirror). Relative residual 0.376; the
next-best candidate of the 48 fits 0.975 and the worst 1.968, so the mapping is
well separated from its alternatives but not tight.

Two caveats, both settled later by docs/18:

- The 0.376 residual was not only impure turns. The fit was constrained to signed
  permutations, and the chips turned out to be mounted ~45 degrees off the headset
  frame, so no permutation is correct. The relative map is still the right
  relationship between the two IMUs - docs/18 §18.4 confirms it to 10-18 degrees
  from an independent gravity measurement - but it is an approximation of a
  rotation, not the rotation.
- Do not read this as an absolute map. It never was one.

`[CLOSED by docs/18]` the alignment to the headset frame: `ay` is vertical on both
chips (IMU0 `+Z`, IMU1 `-Z`), and `ax`/`az` sit at ~45 degrees in the X-Y plane.

---

## 17.7 What this closes

- Shipping-plan item 4 is done: gyro counts now convert to deg/s.
- The tick rate is no longer `[OPEN]`: `META2_TICKS_PER_S = 117,821,900`.
- RGB is 30.00 fps and mono is 60.01 fps in device time, which reframes the
  dropped-frame work: a delivered 29.95 records/s against a 30.00 fps emission is
  a 0.2% shortfall in that session, not a 40% one.
- The health gate keeps its 183 MHz constant deliberately - see the comment in
  `include/meta2/health.h`. It is a proxy for the median-delta estimator, not a
  clock claim, and retuning it without re-measuring the estimator would move the
  gate blind.
