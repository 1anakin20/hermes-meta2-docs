# 18. Which way the IMUs actually point

Coached physical session, 2026-10-25, six gravity poses. This closes the `[OPEN]`
in docs/17 §17.6: the accelerometer axes are now tied to the headset frame.

Capture: `meta2lib/examples/meta2_imu_log.c` under `metavision/re/axis_coach.py`,
129,018 IMU samples over 544 s, live graphs so each pose could be confirmed before
moving on. Files: `metavision/re/axis_cal.csv`, `metavision/re/axis_poses.json`,
`metavision/re/axis_results.txt`. Analysis: `tools/axis_calibration.py`,
coaching page `tools/axis_coach.py`.

Headset frame, right-handed, used throughout this repo:

```
+X  forward, out through the screens
+Y  toward the wearer's left
+Z  toward the crown
```

---

## 18.1 Method

Six poses, each resting, each with a known up vector: screens down, screens up,
left side down, right side down, crown down, crown up. At rest the accelerometer
reads +1 g along whichever axis points up, so `m = k * R * u + b`, where `R` maps
headset directions into sensor coordinates, `k` is counts per g, and `b` is the
sensor bias.

Opposite poses are differenced, which removes `b` exactly:

```
k * R[:,j] = ( m(+e_j) - m(-e_j) ) / 2          b_j = ( m(+e_j) + m(-e_j) ) / 2
```

Six poses over-determine three axes, so the session grades itself (§18.5).

Each pose was a 2 s window. Within-window standard deviation was 37-148 counts on
a ~16,400-count signal, i.e. 0.2-0.9%: the poses themselves were steady, and none
of the scatter below comes from the headset moving.

---

## 18.2 The headline: the chips are not axis-aligned `[MEASURED, high confidence]`

Neither IMU has an axis pointing along the headset's forward or left direction.
Each sensor axis is roughly 45 degrees off. Expressed as headset directions in
sensor coordinates (columns of `R`, unit vectors):

```
IMU0                                   IMU1
headset X  -> ax -0.655 ay +0.114 az -0.747     ax -0.729 ay -0.080 az -0.679
headset Y  -> ax -0.702 ay -0.166 az +0.693     ax +0.712 ay -0.288 az -0.640
headset Z  -> ax -0.005 ay +0.952 az +0.306     ax -0.030 ay -0.948 az +0.316
```

And the same map read the other way, sensor axes in the headset frame (rows of
`R`), which is what a driver needs in order to rotate IMU samples into headset
coordinates:

```
IMU0
ax = -0.661 X - 0.702 Y - 0.005 Z    in the X-Y plane, 133 deg from +X
ay = +0.115 X - 0.166 Y + 0.944 Z    12 deg from +Z
az = -0.753 X + 0.692 Y + 0.304 Z    135 deg from +X, 18 deg above the X-Y plane

IMU1
ax = -0.737 X + 0.710 Y - 0.029 Z    in the X-Y plane, 136 deg from +X
ay = -0.081 X - 0.287 Y - 0.942 Z    162 deg from +Z, i.e. 18 deg from -Z
az = -0.686 X - 0.638 Y + 0.314 Z    134 deg from +X, 19 deg above the X-Y plane
```

So, in words:

- `ay` is the vertical axis on both chips, and the two chips disagree about its
  sign: IMU0 `ay` points at the crown, IMU1 `ay` points at the wearer's feet.
  This is the mirrored pair already seen in docs/17 §17.5, now measured rather
  than inferred.
- `ax` lies in the headset X-Y plane on both chips (90 deg and 92 deg from `Z`),
  pointing backward and sideways at ~45 degrees. IMU0 `ax` points backward and
  toward the wearer's right; IMU1 `ax` points backward and toward the wearer's
  left.
- `az` is the third axis of each chip and is orthogonal to the other two.

A 45-degree mount is a normal design choice - it splits any axis-aligned motion
across two axes instead of saturating one - so this is not a surprise, but it does
mean any code that assumes `ax` is forward will be wrong by 45 degrees.

---

## 18.3 The 18-degree cant `[MEASURED, cause unresolved]`

`az` is not quite in the headset X-Y plane: it tilts up by 18-19 degrees on both
chips, and `ay` is 12-18 degrees off vertical. The two chips agree with each other
to within a degree on this.

That agreement is not proof. The two IMUs are mirror-mounted, so a genuine
symmetric cant and a common pose error both show up identically in both chips.
The likely pose error is resting geometry: the headset is not a box, so "crown on
the table" does not put `+Z` exactly vertical. Nothing in this session can tell
those two explanations apart.

What is solid regardless: the in-plane 45-degree rotation, and which sensor axis
is vertical.

### 18.3.1 The face test, and why it could not settle the cant `[MEASURED, negative result]`

`tools/face_coach.py` was built to stop assuming headset axes and measure the
housing instead: rest the device on a face, flip it, difference the pair. The
operator offered three faces - the two temple arms, the top of the headband, the
back of the headband. Session: 194,022 IMU samples, gate-certified on attempt 2
of 10, both chips reading the same geometry.

| measured angle | IMU0 | IMU1 |
|---|---|---|
| temple-arm rest vs top-of-band rest | 0.9 deg | 0.9 deg |
| temple-arm rest vs back-of-headband | 100.1 deg | 100.2 deg |
| top-of-band rest vs back-of-headband | 101.0 deg | 101.1 deg |

**Useful.** The temple-arm rest and the top-of-band rest give the *same*
direction to 0.9 deg: they are one reference, not two, so the three faces do not
form a triad and cannot define a frame between them. The back-of-headband normal
sits 100-101 deg from that direction on both chips, so the rear pad is raked
about 10 deg off perpendicular to the crown plane - a housing property, because
it reproduces across two independently mounted dies.

**Fatal for the cant question.** Pair differencing assumes a flip is an exact
180 deg reversal, and it was not. Each pair estimates the bias independently as
`(m(+) + m(-))/2`, and exact flips must give the same bias from every pair:

| pair | IMU0 bias (counts) | IMU1 bias (counts) |
|---|---|---|
| temple arms | -1633, +697, -128 | -460, -398, -835 |
| top of band | -1438, +607, +19 | -283, -310, -659 |
| back of headband | +137, +2701, +1545 | +439, -2164, +1681 |

Disagreement of 1770 / 2094 / 1673 counts on IMU0 and 899 / 1854 / 2516 on IMU1.
At 16,400 counts/g that says each rest-and-flip pair was off a true reversal by
6 to 11 deg: the headset does not settle in a well-defined orientation on these
faces.

So the 6.7 deg anomaly in 18.2 is the same size as the error of the method that
would test it. This experiment cannot separate "sloppy poses" from
"non-orthogonal housing", and re-running the same method will not either - the
accuracy floor of gravity poses on this device is several degrees wide. `[OPEN]`
the cant needs a non-gravity reference: the camera optical axis, which is the
`g_pmd_cad` calibration-region parse in docs/08, not another coached session.

---

## 18.4 Cross-check against the gyro session `[MEASURED]`

docs/17 §17.6 fitted a relative map from the coached turns and got
`IMU1.x = +IMU0.z`, `IMU1.y = -IMU0.y`, `IMU1.z = +IMU0.x`. That was a completely
independent experiment - gyro vectors from rotations, not gravity.

Comparing the two maps axis by axis (cosine between the accel-measured direction
and the gyro-predicted one):

```
IMU1 ax  +0.950
IMU1 ay  +0.892
IMU1 az  +0.945
```

Two different physical effects, two different sessions, agreement to 10-18 degrees.
The gyro turns were impure, so that is as tight as that experiment can be.

It also explains a number that was previously unexplained: the best permutation
fit in §17.6 had residual 0.376 while the next candidate sat at 0.975. The true
map is not a signed permutation at all, so 0.376 was the cost of forcing one, not
measurement noise.

---

## 18.5 Scale and bias `[MEASURED]`

Pair-differenced, each headset axis measures 1 g to within 1.0%:

```
IMU0  k = 16,430 counts/g   column norms 16,575  16,428  16,286   det(R) = +0.989
IMU1  k = 16,506 counts/g   column norms 16,674  16,443  16,400   det(R) = +0.990
```

`k` against the nominal LSB size for a +/-2 g range (16,384 counts/g) is +0.3% and
+0.7%. docs/17 had the +/-2 g range as `[INFERRED, moderate]`; this is the first
measurement that supports it, and no other full scale (1, 4, 8, 16 g) is within
100%.

Bias, from the same pose pairs:

```
IMU0  ax -964.9  ay  +93.5  az +296.4    |b| = 1,014 counts = 0.062 g
IMU1  ax  +88.0  ay +242.9  az -280.5    |b| =   381 counts = 0.023 g
```

IMU0's bias is 0.06 g and mostly on `ax`. That matters for how the data looks:
raw per-pose `|a|` scatters from 15,429 to 17,437 counts, a 6.1% spread, which is
exactly what a 1,014-count bias does to a 1 g reading at six different
orientations. After bias removal the spread is 2.8%. A magnitude check that ignores
bias will therefore flag a perfectly good session as bad.

---

## 18.6 The first verdict was wrong, and why it is worth writing down

The coach initially reported both IMUs `INCONSISTENT`. The data was fine. The test
was wrong in two ways, both inherited from the gyro analysis rather than measured:

1. It required each sensor axis to line up with some headset axis - a signed
   permutation - because §17.6 had fitted one. A 45-degree mount passes every
   physical check and fails that test. The check has been replaced with
   orthogonality: the three headset directions must be 90 degrees apart in sensor
   space, whatever orientation the chip happens to be in.
2. It compared raw per-pose `|a|` against `k`, with no bias term, so IMU0's real
   0.06 g bias read as a botched pose.

The current self-grading is four checks, and the synthetic tests in
`tools/axis_calibration.py` confirm each one fires:

| check | threshold | clean 45 deg mount | one pose pair swapped | one pose mislabelled |
|---|---|---|---|---|
| every headset axis measures the same 1 g | 4% | 0.5% pass | 0.5% pass | 23.9% fail |
| headset axes are 90 deg apart in sensor space | 10 deg | 0.8 deg pass | 0.8 deg pass | 90.0 deg fail |
| per-pose `|a|` after bias removal | 5% | 0.5% pass | 0.5% pass | 24.8% fail |
| `det(R) = +1` | 0.15 | +1.000 pass | -1.000 fail | 0.000 fail |

The determinant check is the one that catches a swapped pose pair. Swapping the two
poses of one axis negates that column, which leaves 1 g agreement, orthogonality
and magnitudes all untouched - it only turns the frame left-handed. Without check
4 a swapped pair passes silently and one axis comes out backwards.

On the real session both IMUs grade `CONSISTENT`: 1 g agrees to 0.9% and 1.0%,
worst angle 6.7 deg off 90, magnitudes to 2.8% and 3.0% after bias removal,
`det` +0.989 and +0.990.
