# Meta 2 — device documentation

Reverse-engineered documentation for the **Meta 2 AR headset** by **Meta (Metavision
Inc.)**, written so that a programmer can understand the device, talk to it directly,
and build their own software for it.

> **Not related to Facebook/Meta Platforms or Oculus.** The vendor is Meta
> (Metavision Inc.), a separate AR headset maker. Its USB identity is
> `idVendor 0x2CFA "USB Design By Meta"`, `idProduct 0x00F3 "Meta2"`. The name
> collision is unfortunate; the device has nothing to do with Facebook hardware.

## Status

The device is understood down to the wire level: USB identity, endpoint map, the
vendor control protocol, a register map with live read-backs, and the framing of the
bulk data streams. A no-SDK client (plain libusb, Linux, no Meta SDK, no Windows, no
vendor driver) has been demonstrated reading the device.

**Not yet solved:** the command that switches the device from single-burst output to
continuous full-frame streaming. See [docs/07-open-questions.md](docs/07-open-questions.md).

## What this repo is

Documentation only. A separate library repo is planned once the device is fully
understood. Code appears here only where it is needed to make a mechanism unambiguous.

## Confidence convention

Every claim in these docs carries a marker. If a claim cannot be made accurate, it is
labelled rather than smoothed over.

| Marker | Meaning |
|---|---|
| `[VERIFIED]` | Reproduced directly against a live device, or computed from a capture with the numbers shown. |
| `[CAPTURED]` | Observed in a specific capture. Reproducible from the named artifact, but not independently reconfirmed. |
| `[INFERRED]` | A consistent interpretation of verified observations. Not proven. Do not build on it without checking. |
| `[UNKNOWN]` | Not determined. Stated explicitly rather than guessed. |

Where a section mixes confidence levels, each claim is marked individually.

## Document map

| Document | Contents |
|---|---|
| [docs/01-device.md](docs/01-device.md) | What the device is, its internal architecture, its identity, the SuperSpeed requirement. |
| [docs/02-usb-interface.md](docs/02-usb-interface.md) | Full USB descriptors, endpoint table, claiming the device, Linux/Windows driver notes. |
| [docs/03-control-protocol.md](docs/03-control-protocol.md) | The vendor control protocol: transfer framing, the OUT->IN->IN handshake, command classes, register grammar. |
| [docs/04-register-map.md](docs/04-register-map.md) | Registers read live from the device, with values and read-back counts. |
| [docs/05-data-streams.md](docs/05-data-streams.md) | The four bulk endpoints, their record layouts, the camera stream, measured rates. |
| [docs/06-writing-a-reader.md](docs/06-writing-a-reader.md) | How to build your own reader in C/C++ with libusb; worked example; pitfalls. |
| [docs/07-open-questions.md](docs/07-open-questions.md) | What is not known, and the concrete experiment that would answer each item. |
| [docs/EVIDENCE.md](docs/EVIDENCE.md) | How each claim was produced, the artifacts, and reproduction commands. |
| [docs/appendix-capture-rig.md](docs/appendix-capture-rig.md) | The full capture rig: QEMU + Windows 10 1809 + SDK + USB passthrough, and how to reproduce the capture. |

## Continuing this project

This repository documents **how the device works**. It is not a lab notebook: run-by-run
experiment narration and session handoff notes are kept outside it, so everything published
here is meant to be read, checked and reused rather than followed chronologically.

For the protocol stated as a specification, see the companion datasheet
(`meta2-datasheet`). For working code, see `meta2lib`.

## Reading order

If you want to use the device: 02 -> 03 -> 05 -> 06.
If you want to understand it: 01 -> 05 -> 04 -> 07.

## Legal and safety notes

- This documentation was produced by observing USB traffic to a device the authors own
  and by reading a publicly distributed SDK installer. It is written for
  interoperability and research.
- Writing vendor commands to an undocumented register interface can put the device in a
  state only its own firmware can undo. The register writes documented here are the ones
  observed from the vendor's own software, replayed verbatim. Writes invented from
  scratch are not documented here for that reason.
- The device firmware and the vendor's SDK remain the vendor's property. This repo
  documents observed behaviour; it does not contain vendor code.
