# 10. Enable masks, reader back-pressure, and mono framing

Everything here was measured on 2026-10-16 with `re/capture_mask.py`, which arms with the
full 417-transfer sequence, starts a reader thread per chosen endpoint **before** any control
traffic, then loops a 4-command sustaining set with the masks substituted. Framing quality is
reported as the fraction of trailer-to-trailer gaps that are exactly one frame.

## 10.1 The enable mask is real and it gates cameras

The endpoint feed is `0xC0` / value 6 with `[0, 4, 0, 0, 0, mask]`;
`Mono0 = 2, Mono1 = 4, ToF = 8, Multiplexor = 16, RGB = 32, STD = 64`. Screening, 8 s per
mask, readers pending on all four endpoints:

| mask | enabled | EP 0x81 | EP 0x82 | EP 0x83 | EP 0x84 |
|---|---|---|---|---|---|
| `0x7e` | everything | 0.06 MB/s | **112.5 MB/s** | **108.8 MB/s** | **74.0 MB/s** |
| `0x66` | mono + STD | 0.02 | **74.5** | 52.3 | 9.0 |
| `0x60` | RGB + STD | 0.02 | 4.6 | 4.8 | 4.0 |
| `0x48` | ToF + STD | 0.02 | 5.8 | 4.8 | **65.1** |
| `0x50` | mux + STD | 0.02 | 4.8 | 4.8 | 9.1 |

`[VERIFIED]` The mask selects which camera streams fast. With `0x48` and a reader on EP 0x84
only, ToF delivered **63.45 MB/s, 4,692 complete frames in 15 s = 313 fps, 99.9% of gaps
exactly one frame** — the cleanest capture of any endpoint in the project.

`[UNKNOWN]` why `0x60` (RGB only) is *slower* on EP 0x83 than `0x66` (mono only) is. The
mask clearly gates something, but the rate allocation is not a simple "enabled ⇒ fast".

## 10.2 Mono needs pending readers on all four endpoints

Same mask (`0x66`), different reader sets, 8–15 s:

| readers pending | EP 0x82 rate | complete mono frames |
|---|---|---|
| `{0x82}` | 0.13 MB/s | 0% |
| `{0x81, 0x82}` | 0.06 MB/s | 0% |
| `{0x82, 0x83}` | 0.16 MB/s | 0% |
| `{0x81, 0x82, 0x84}` | 27.7 MB/s | 7.8% |
| `{0x81, 0x82, 0x83, 0x84}` | 49–74 MB/s | 71–77% |

`[VERIFIED]` EP 0x82 collapses to near-zero when the other endpoints have no reader, even
though the mask enables only the mono cameras. The device writes to endpoints whether or not
anyone is draining them, and an undrained endpoint back-pressures the mono stream. A reader
must keep a URB pending on **every** bulk IN endpoint, including ones whose data it discards.
`[INFERRED]` a shared FIFO or a single FPGA DMA engine behind all four endpoints.

## 10.3 Device state is hysteretic across `libusb_reset_device`

Identical configuration, two runs, same day: **74 MB/s** and **2.12 MB/s** on EP 0x82. Both
did the port reset, both re-armed with the full 417-transfer sequence (`ok=279 fail=138`
every time). The reset does **not** restore a known state.

What does control it is the mask the device was last left in. Adding a warm-up phase in the
same process, before the measured phase:

| warm-up mask | measured mask | EP 0x82 rate | complete mono frames | EP 0x83 | EP 0x84 |
|---|---|---|---|---|---|
| `0x7e` (everything on) | `0x66` | 54.2 MB/s | **7.6%** | 80.4 MB/s, 99.8% | 87.5 MB/s, 99.6% |
| `0x00` (everything off) | `0x66` | 49.1 MB/s | **71.3%** | 34.8 MB/s, 99.6% | 6.0 MB/s, 98.9% |

`[VERIFIED]` Warming with everything off and then measuring with mono-only produces mono
frames that are complete 71% of the time; warming with everything on produces the same byte
rate with frames complete only 7% of the time. `[UNKNOWN]` the mechanism — plausibly the
FPGA keeps a per-camera readout configuration latched that a USB port reset does not clear.

**Practical rule:** warm the device with the mask you intend to measure, or with `0x00`, and
never trust a single run's rate. Always report framing quality alongside the byte rate.

## 10.4 The mono trailer is not a frame delimiter

EP 0x82 emits its trailer (`efbeadde 0df0ddda 00000000`) at roughly **62 Hz per camera**
while complete 752 × 480 frames arrive at **27–44 fps**. Only 7–77% of trailer-to-trailer
gaps are exactly 721,952 B, depending on device state; the rest are partial acquisitions
(195,072 / 227,584 / 260,096 / 292,608 / 325,120 B, all multiples of 32,512 B = 8 fragments).

Consequences, all `[VERIFIED]`:

- The **concatenate-and-cut** model (strip every trailer, cut every 721,920 B) splices two
  acquisitions into one frame. That is what produces the horizontal slice-shift — tearing —
  in rendered mono video. It is not data loss: the fragment counter at mono header +28
  increments by exactly 1 across all 205,640 fragments per camera in `cap_four_ep82.bin`,
  with zero drops.
- The **exact-frame** model (keep only chunks whose gap is exactly 721,952 B) produces
  frames with no tearing. `re/make_mono_exact.py` implements it. On `screen_66_ep82.bin` it
  yields 435 complete frames per camera in 10 s = **44 fps**; on `cap_cold_ep82.bin`, 405 in
  15 s = **27 fps**.
- The vendor driver has the same exposure to this. Its `FindTrailerIndex` searches the
  identical 12-byte pattern, `Mono0EndPointDataConstructor` allocates
  `GrayScale16Image(752, 480)` = 721,920 B, and `BaseImageEndPointDataConstructor.AddData`
  logs *"Fragment data is too short for finalizing image"* and sets `IsComplete = false`
  whenever a chunk is short. So the SDK also gets incomplete mono frames unless the device
  is in a state where the trailer period matches the frame period. `[VERIFIED]` from source;
  `[INFERRED]` that the SDK reaches that state through configuration we have not replicated.
- 752 is the correct raster width: a lag scan over 4.3 M samples ranks **lag 752** first
  (mean |diff| 11.92, ratio 0.051 against a permutation baseline). `[VERIFIED]`

## 10.5 Microphones still do not appear

Setting the multiplexor mask to `0x1f` (adding bit 2 = Mics) produced **no** `0x88` records:
645 multiplexor records in `cap_mux2_ep81.bin` carry tags `102` (323) and `119` (321) only.
Buttons (`153`) are absent too, even though bit 3 was already set in the old `0x1b` mask.
`[VERIFIED]` negative result. `[UNKNOWN]` whether mics need an additional command, only
stream when the vendor app requests audio, or are not routed through EP 0x81 at all.
