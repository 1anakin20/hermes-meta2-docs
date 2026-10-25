# 14. Project state and handoff — resume point for the Meta 2 RE project

Written 2026-10-25, at the end of the ToF investigation branch. Read this first in any new
session. It is the index; the detail lives in the numbered documents and in the evidence file.

Project identity, unchanged and non-negotiable: this is the **Meta 2 AR headset / MetaVision
SDK 2.7.0.38**. It is not Facebook, Meta Platforms, or Oculus work, and none of the findings
should be framed that way.

---

## 1. Where everything lives

| What | Where |
|---|---|
| Library (the deliverable) | `/home/hermes/work/meta2lib` — GitHub `1anakin20/meta2lib` |
| This documentation / evidence | `/home/hermes/work/meta2-docs` — GitHub `1anakin20/hermes-meta2-docs` |
| Working dir, probes, scripts | `/home/hermes/work/metavision` (`re/` = experiments, `sdk/` = extracted SDK, `vm/` = Windows VM, `serve/` = HTTP exchange server) |
| Extracted vendor SDK | `/home/hermes/work/metavision/sdk/Meta/Meta SDK2 Beta` |
| Ghidra corpus | `re/ghidra_out/` (published as `artifacts/royale_decompiled.c`, `royale_function_inventory.tsv`, `devstream_decompiled.c`) |
| Windows guided probe packages | `re/meta2_win_probe_v*.zip`, served from `serve/` on `:8091` |
| Result uploads from the physical PC | `/home/hermes/work/metavision/incoming/` |

Device: `2cfa:00f3`, "Meta2", Cypress FX3, SuperSpeed required. On server3 it attaches as a
bulk device; the Windows VM path is `vm.sh` + QMP `id=meta2usb` (cold-attach at boot;
`device_del` releases it live for host-side libusb work).

---

## 2. What is DONE and shippable today

`meta2lib` (C11 + system libusb, nothing vendored) already implements the device side:

| Endpoint | Content | Measured rate | State |
|---|---|---|---|
| `0x81` | Multiplexor, fixed 256-byte records: IMU0, IMU1, microphone audio, an undocumented `0xAA` record | ~57 records/s | decoded |
| `0x82` | Two 752×480 10-bit mono cameras, interleaved as 4,096-byte fragments (`0x44` wearer's left, `0x55` wearer's right) | 36 fps each in the full-throughput run | exact-frame assembly implemented |
| `0x83` | YUV422 1280×720 colour camera | 30 fps | decoded, record-delimited |
| `0x84` | 352×288 16-bit ToF (row 0 = 4095 sentinel row) | ~300 fps | framing solved, **no scene information** |

Aggregate 163 MB/s across all four. `ctest` is 6/6 green. `meta2::frame` is pure parsing
(testable with no headset attached); `meta2::transport` is the libusb side.

**The active track from here is: ship this as the tracking front end.** Mono at 36 fps × 2 plus
RGB at 30 fps plus dual IMU is a legitimate VIO input set.

---

## 3. What the ToF branch proved (do not re-derive these)

Full detail in `docs/12-tof-investigation.md` §12.1–§12.46 and `docs/EVIDENCE.md`. The load-bearing
conclusions:

- **Transport and protocol are solved.** `bRequest=0xC0`, OUT `0x40` / IN `0xC0`, payload grammar
  `[0x3D][op][addr16BE][data]`, `wIndex==wLength==payload length` on OUT. Arm with the interleaved
  sequence including the paired INs; `libusb_reset_device` is the deterministic reset; a 4-command
  strobe sustains streaming.
- **Endpoint→sensor map is solved** (`0x81` mux, `0x82` mono pair, `0x83` RGB, `0x84` ToF), as is
  EP `0x84` framing: 32-byte descriptor + 101,376 samples, magic slots `DEAD/F00D/DADD/ABBA/FEED/BEEF`,
  resynchronise on `0xDEAD`, geometry 352×288 from the `0xa886` read-back, intrinsics
  `fu 151.9015 fv 151.8631 u0 177.1966 v0 142.2995 k1 0.1575959 k2 -0.1942623 k3 0.04948911`, height 287.
- **The imager is identified**: PMD Royale 2.3.1 HAL → SAQ bridge → M2450/M2452. Ghidra-derived
  modulation frequencies **30 / 60 / 20 / 99.5 MHz** → unambiguous ranges 4.9965 / 2.4983 / 7.4948 /
  1.5055 m. The Royale register space is the same 16-bit space as our `0xC0` primitive (measured).
- **Illumination is real and register-only.** IR emitter on when armed (pooled blinded test, Fisher
  one-sided `p = 4.8e-6`). A healthy SDK session calls **no** `SetExposure` / `ConfigureLed` /
  `SetAnalogGain` — illumination lives entirely in the `0xa88x` / `0xb0xx` writes.
- **Our host arm is byte-for-byte the vendor's.** IR-83 (the `meta2_host_impl.dll` semantic proxy on
  the physical PC) matched 46 of 47 vendor `WriteI2C` payloads exactly, and every arm write has a
  vendor counterpart. `SetGPIO(12/13)` and the SPI reads map to arm entries we already replay.
- **All device commands occur in the first 8.1 s and the last 2.4 s.** Zero commands during seven
  minutes of full-rate streaming. There is no mid-stream control traffic to hunt for.
- **Depth has never been observed in any path**: host-only arm gives a scene-independent pattern
  (mean 2037, sd 142, split-half r = 0.995, cross-reset r = 0.957); the physical SDK produced zero
  points for walls and a fixed 2.4465 m shell only when cameras were covered (IR-74); a full healthy
  SDK run produced `pc_nz = 0` for every poll (IR-82).
- **EP `0x84` is not raw multi-phase data** (IR-65: no period-2/4/8 structure, no spatial coherence).
- **`0xb800–0xb9ff` is writable RAM but does not govern EP `0x84`** (IR-63, IR-68).

Withdrawn claims — do not resurrect any of these: the "VM artifact" explanation for the fixed shell
(withdrawn by IR-74); "13 wide writes were truncated" (a tshark decimal-parsed-as-hex tooling
artifact, corrected by IR-79); the `0xB8` cursor / illumination-control reading; the "18 % autocorrelation
at lag 704" geometry argument; the `1312` header field; the 27.7 fps RGB ceiling; the modPLL polarity
reading in `f1c8afe` (corrected: `0x9802` bit `0x04` **set** means NOT locked).

---

## 4. Where the ToF work stopped — and the exact resume point

**Status: PAUSED by user decision on 2026-10-25, not closed.** The work is preserved and worth
returning to.

The branch ended on a finding, not a dead end. `re/ctrl_seq_full.json` contains **five control OUT
transfers whose data stage was never captured** (usbmon records setup packets, not the data stage of
large control writes):

```
#201  wValue=3  wIndex=2336  wLength=2336  payload = (empty)
#204  wValue=3  wIndex=608   wLength=608   payload = (empty)
#207  wValue=3  wIndex=608   wLength=608   payload = (empty)
#210  wValue=3  wIndex=608   wLength=608   payload = (empty)
#213  wValue=3  wIndex=338   wLength=338   payload = (empty)
```

4,498 bytes the vendor sent and we never recorded — and `harness.send()` does
`bytes.fromhex(cmd["payload"])`, so **every host-side experiment in this project replayed those five
transfers with an empty data stage.** Their position in the transcript is exactly where IR-83 shows
the vendor's `WriteI2C(reg=0xb800)` and the `ReadFromSPIMemory(dev=8, addr=0x30000)` pair, and
`2336 = 0x920` is a program-image-sized transfer.

`[INFERRED, leading hypothesis]` these are the imager program upload and/or the per-unit calibration
blob. Without them the device would sit in a default mode: endpoint configured, modPLL locked
(`0x9802 = 0x0001`, bit `0x04` clear), `0xb0ad = 0x0a12` correct for the imager, `0xc40f = 0x0000`
no iSM fault, emitter driven — and a placeholder on EP `0x84`. That one gap accounts for every
surprising measurement in §12.20–§12.45.

**Resume instrument: v10, already built and served.** `re/proxy_gen3.py` generates the
`meta2_host_impl.dll` proxy (2896/2896 exports identical to vendor) plus **import-table hooks on the
genuine module** — `CreateFileA`, `DeviceIoControl`, `ReadFile`, `WriteFile` — which dump every
control transfer in full in both directions (buffers ≤ 4096 B; bulk camera reads skipped; no IN dump
for overlapped calls). Package `meta2_win_probe_v10.zip`, 594,788 B, sha256
`18aa2d49004dafe0a7386352528953ff3903afdcd49b91f3a89f4606ec877653`. Default run 120 s.

**IR-84 decision rule.** Run v10 on the physical PC (self-test must print `WIRE HOOK OK`), read the
`DEVIO` blocks:
- If those five transfers carry real program/calibration bytes → replay the arm **with** them on the
  Linux box and test the one metric that has been the target all along: EP `0x84` statistics between
  a hand at 10 cm and a hand at 1 m. If they change, ToF is alive and we were one payload short.
- If they are empty or trivial on the wire too → the remaining hypotheses are "module degraded" or
  "SDK2 Beta depth is a stub", and ToF stays out of the library.

Ranked alternatives if that fails: per-unit calibration gating (`ReadUnitSerialNumber`,
`GetVersionInfo`, SPI reads at `0x30000` — we replay the reads and discard the answers); depth
computed inside the FPGA with EP `0x84` as a result stream; hardware/SDK stub.

---

## 5. Open questions on the tracking path (the new main line)

1. **Is EP `0x82` A/B a usable stereo pair?** `[VERIFIED]` both sub-streams correlate with EP `0x83`
   (0.472 / 0.252 against a 0.04–0.07 shuffled baseline), but A and B correlate only weakly with each
   other — "not two views of one scene at a small disparity". That is consistent with time-interleaved
   acquisition (A and B are different instants), which would break naive disparity. Resolve before
   promising metric scale from stereo.
2. **Timestamps.** EP `0x81` records have u32 fields at +4 and +212 consistent with µs
   `[INFERRED]`. Mono fragments need a reliable frame-time assignment for VIO. Establish the clock
   and its relation to the IMU clock.
3. **Which chroma slot is U and which is V** in the EP `0x83` YUV422 stream (currently a coin flip).
4. **The `0xAA` mux record** — decoded structurally, meaning unknown.
5. **Mux mask bit 4** and the microphone channel layout.
6. **Camera intrinsics/extrinsics for the mono pair and RGB.** Depth intrinsics are extracted; the
   mono/RGB calibration is in the SDK's calibration data (`g_pmd_cad` region) and has not been
   extracted cleanly. Without extrinsics you cannot do stereo or camera-to-IMU fusion.
7. **SuperSpeed is a hard gate**, not a preference: `meta2_host_impl.dll` tests byte `+0x979` on the
   device object at `0x180025dd5` and errors out on a non-SuperSpeed link. Full stream bandwidth is
   ~160 MB/s, impossible over USB 2.0.

---

## 6. Standing constraints (they survive the branch change)

- GitHub operations are **read-only** unless the user authorizes each specific write.
- Never touch the FX3 SPI-flash / firmware-update path (`MetaSAQ.FirmwareUpdate.exe`,
  `firmware-update.exe`). `MetaSAQ_FX3.spt` is read-only reference.
- Never probe the user's physical devices directly; for the headset, tell the user what to run and
  wait for results. File transfer to the headset is scp/rsync only.
- Single-run experimental results are **directional evidence, not truth**. Every claim in these
  documents is tiered `[VERIFIED]` / `[MEASURED]` / `[CAPTURED]` / `[INFERRED]` — keep doing that,
  and record withdrawals in `docs/EVIDENCE.md` rather than editing history silently.
- Physical tests are gated on the user pressing start on the coaching page; never auto-start.
- Windows-side tools must be self-contained and log everything, because the analysis box is not
  connected to the test desktop.
- File exchange with the test PC: HTTP server `serve/serve.py` on `:8091` (downloads at `/`,
  uploads via `PUT /upload/<name>`, 2 GB cap, streaming with truncation detection;
  `send_results.ps1` splits core vs media zips and prints progress + MB/s).

---

## 7. Suggested next steps for the main line

1. Decide the tracking architecture: dual mono 36 fps + IMU as the VIO input, RGB as the appearance
   / relocalisation stream, ToF excluded for now.
2. Resolve open question 1 (is the mono pair a real stereo pair, and at what relative timing). This
   determines whether metric scale comes from stereo at all.
3. Extract mono/RGB intrinsics and camera-to-IMU extrinsics from the SDK calibration data.
4. Add to `meta2lib` only what is protocol-shaped: frame timestamps, a documented arm-file format,
   and a stable capture API. SLAM, rectification and rendering stay out of the library (see its
   README's "what this library is, and is not").
5. Keep the ToF door open with §4's IR-84 rule; it is one 2-minute run away from a decisive answer.
