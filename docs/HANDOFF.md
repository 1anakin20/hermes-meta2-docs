# Handoff — continuing the Meta 2 reverse-engineering project

Written 2026-10-16. This file is the resume point for the next session, human or agent.
Read it, then go to the document named in "Next actions".

---

## 1. What the project is

**Ultimate goal:** a custom cross-platform library — **C/C++ over libusb** — that talks to
every Meta 2 sensor and camera directly, with no Meta SDK, no Windows requirement, and
better performance and currency than the vendor's software.

**Current phase:** understand the device completely enough to build that library. The
protocol layer is cracked; the streaming trigger is not.

**The device is Meta (Metavision Inc.), USB `2cfa:00f3`. It has nothing to do with
Facebook/Meta Platforms or Oculus.** Never describe it as an Oculus/Facebook device, and
never assume Facebook-era SDK knowledge applies to it.

---

## 2. Where everything lives

| Thing | Location |
|---|---|
| Documentation (this repo) | `github.com/1anakin20/hermes-meta2-docs`, public, branch `main` |
| Working artifacts (not in the repo) | `<workspace>/re/` on the RE host — raw captures, pcapng, extracted streams, probe scripts |
| VM + launcher | `<workspace>/vm/` — `vm.sh` (modes: `install`, normal, `usb`, `stop`), `qmp.sh` |
| Reader source | `<workspace>/reader/MetaReader.cs` |
| SDK (extracted) | `<workspace>/sdk/Meta/Meta SDK2 Beta/bin/` |
| HTTP file delivery | `python3 -m http.server` on port `8090` from `<workspace>/verify` — **required**: the agent client's file download is broken, so files reach the user only over HTTP |

Credentials, hostnames, LAN addresses and SSH endpoints are deliberately absent from this
repo. They live only in the operator's own environment.

---

## 3. What is already established — do not re-derive it

These are `[VERIFIED]` against a live device. Re-confirming them wastes a session.

- **Transport is plain WinUSB/libusb.** `cyapi.dll` is Cypress's FX3 host API. There is no
  proprietary kernel driver to reimplement.
- **Enumeration works from Linux with no vendor software.** `2cfa:00f3`, one vendor-class
  interface, 4 bulk IN endpoints @1024, `bMaxBurst 15`, EP0 max packet 512.
- **Vendor control grammar.** `bRequest = 0xC0` always. OUT: `bmRequestType 0x40`,
  `wIndex == wLength == payload length` (138/138). IN: `bmRequestType 0xC0`, `wIndex = 1`
  (279/279). Every OUT is followed by exactly two INs (137/138; the identity command gets
  five).
- **A vendor IN without a preceding OUT always stalls.** The OUT arms the response. This is
  the single most important rule for writing a client.
- **Register access.** Payload `3D | op | addr(u16 BE) | data`. `op 0x21` = read, data is an
  `N`-byte `0xFF` mask, response is `1 status byte + N value bytes` (70/70). Write ops seen:
  `0x40, 0x20, 0x60, 0xA0, 0xC0, 0xE0`. `op` does **not** encode length.
- **A wide read is not a byte window.** For `0xc2bc` the span base is 4 bytes *below* the
  requested address. The old "contiguous byte-addressable" model is **withdrawn** — see
  03 §3.5. Do not reintroduce it.
- **Identity string** is readable via `wValue=0x0002` even though `iSerial = 0`. Format:
  17 ASCII chars starting `META2D`. The test unit's actual value is redacted repo-wide.
- **EP 0x83 is 1280-wide 16-bit image data.** Row stride 1280 proven by autocorrelation
  (lag 1 → 1096, lag 1280 → 1342, lag 1312 → 4202, lag 2048 → 14089). Each 65,536-byte
  block = 32,744 sample slots + a 24-slot trailer at byte 65,488, with a per-block counter
  incrementing by 1. Blocks are independent acquisitions, **not** consecutive slices.
- **EP 0x81** delivers 256-byte records: tag `45 00 00 ea`, 45-slot table (`0x00..0x2C`,
  `0xFFFFFF` = absent), magics `baabedfe`/`efbeadde`/`abbaedfe`, sentinel `0xDADDF00D`.
  All 45 slots were absent in all 29,462 records analysed.
- **EP 0x84** is a 12-bit field with `0x0FFF` = no data, body values clustered 2017–2033.
  Depth interpretation is `[INFERRED]`, units unknown.
- **EP 0x82 returns nothing**, despite having the largest requested URBs.
- **Throughput achieved without the SDK:** 145 trigger cycles / 40.4 s = 8,126,464 B =
  197 KB/s on EP 0x83.

Details, numbers and evidence: `03-control-protocol.md`, `04-register-map.md`,
`05-data-streams.md`, `EVIDENCE.md`.

---

## 4. The blocking problem

**One trigger cycle yields one 64 KB burst per endpoint. Continuous full-frame streaming
has not been achieved.** The vendor SDK produced 141 full 1280×720 frames in 45 s from the
same device, so the capability exists.

Already ruled out by experiment: IN-only polling (0 bytes), each OUT individually (0), a
single OUT+IN pair (0), the `wValue=0x0004` `0c00/0d00/0c01/0d01` quad alone (0), one huge
bulk URB with a long timeout (65,536 then nothing). The **full interleaved 417-transfer
sequence** is what produces a burst.

Ranked next actions, highest value first:

1. **Active interception of the vendor software while it is already streaming steadily.**
   A WinUSB shim in the VM that logs every transfer `cyapi.dll` makes, *including payloads*.
   Our passive capture lost 7 of 138 OUT payloads and all control-IN payloads. This is the
   highest-value single experiment in the project.
2. **Test concurrent control + bulk.** Replay the handshake *while* bulk reads are blocked
   on the endpoints, rather than handshake-then-read. The vendor software polls continuously
   throughout a stream; our client does not.
3. **Differential register probing.** Read the whole observed address range, then change one
   physical condition (cover cameras, tilt, warm up), read again. Moving addresses are
   sensor registers. This is cheap and would likely locate raw IMU.
4. **Span-base experiment.** Write a recognisable pattern across a 64-byte range, read at
   many addresses/widths, map where it lands. Settles 03 §3.5.
5. **EP 0x84 units.** Headset at a measured distance from a flat wall; regress body values
   against distance.
6. **EP 0x81 semantics.** Capture while actively tracking a textured scene in motion so the
   45 slots populate.

Full detail and the experiment for each: `07-open-questions.md`.

---

## 5. Environment notes that will bite you

- **The device must be on a SuperSpeed port.** `bFunctionalitySupport = 3`. On USB 2 it
  enumerates and answers control transfers but never streams.
- **Only one thing can hold the device at a time.** The VM's QEMU holds it exclusively.
  Hand it over with `device_del {"id":"meta2usb"}` and take it back with `device_add` —
  no VM restart needed, because `vm.sh` gives the device an explicit id.
- **The reader only streams in a foreground, blocking session.** `start /b`, backgrounded
  SSH and detached console launches produce zero frames while appearing to succeed. Three
  separate 0-frame runs were misdiagnosed as a broken reader before this was found.
- **`pgrep -f qemu-system-x86_64` gives false positives** (it matches its own wrapper).
  Use `ps -eo pid,comm | awk '$2 ~ /^qemu/'`.
- **If libusb enumerates 0 devices on the host**, the cause is a VM holding the device or a
  container without `usbfs` — not a driver problem. Check before theorising.
- **tshark 4.4 field-name traps** are listed in `EVIDENCE.md` §3. Read them first; they cost
  hours otherwise. `frame.raw` invalid; `-c` truncates before `-Y`; control payloads are in
  `Data Fragment` not `usb.capdata`; URB ids are reused by the kernel so never pair
  SUBMIT/COMPLETE by URB id.
- **Raw usbmon binary traces use the 48-byte API0 header** on kernel 6.12, not 56 or 64.
- **`web_search` is currently returning zero results** on the operator's configured backend.
  Until that is fixed, no external hardware specification can be cited. Say so rather than
  inventing specs.

---

## 6. Documentation rules for whoever continues

These are the operator's standing requirements, not suggestions.

1. **Every claim carries a confidence marker**: `[VERIFIED]` / `[CAPTURED]` / `[INFERRED]` /
   `[UNKNOWN]`. Mark per claim, not per document.
2. **If something cannot be made accurate, say so in the document.** A labelled unknown is
   correct; a plausible-sounding guess is a defect.
3. **Write for programmers.** Precise, straight to the point, numbers included so a reader
   can check them.
4. **Code in the docs must compile, and be run if it claims to work.** `examples/
   meta2_probe.c` compiles clean under `-Wall -Wextra` and its quoted output is literal
   program output. Keep it that way.
5. **When a claim is disproven, withdraw it explicitly** and record the disproof. See the
   register-window model in 03 §3.5 — do not quietly delete a wrong claim.
6. **Never invent hardware specifications.** Everything in this repo is device-derived
   because no external spec source has been available. If you obtain one, reconcile it
   against `01-device.md` §1.6 and mark which claims it confirms.
7. **Keep the unit serial redacted.** `<unit-serial>` is the placeholder. Do not reintroduce
   the literal value into docs or committed data.
8. **No credentials, hostnames, LAN addresses, SSH endpoints or key paths in this repo.**
9. **GitHub writes are per-action authorised.** Pushes to this repo are authorised; force
   pushes, deletions, and any other repo mutation require explicit authorisation each time.

---

## 7. Open administrative items

- Commit authorship is `Hermes Agent <hermes@localhost>`. The operator may want it changed.
- The repo history was rewritten to a single commit to remove the serial from history. The
  old commit may still be served by GitHub by direct SHA until it is garbage-collected.
- The large raw captures (21.7 MB pcapng, 7.5 MB EP 0x81 stream, 8.1 MB EP 0x83 burst) are
  intentionally **not** published; derived statistics are quoted inline with their counts.
- The Meta 2 reports `bcdDevice 0.00` — **the firmware version is unknown**. Any result in
  these docs is tied to an unidentified firmware build. Flag this when a result fails to
  reproduce.
