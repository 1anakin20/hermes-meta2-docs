# 3. Vendor control protocol

Everything the host says to the device goes through EP0 control transfers. There is no
bulk OUT endpoint (see 2.3).

This protocol is the closed part of the device. The transport is standard; the grammar
below is what had to be reverse-engineered.

## 3.1 Transfer shape

**Most** vendor transfers use **`bRequest = 0xC0`**, but not all. A full census of one live
vendor-driver session (`arm_full2.txt`) found **138 vendor OUTs on four different request
codes**:

| `bRequest` | OUTs | INs | what it does |
|---|---|---|---|
| `0xC0` | 134 | 274 | the `3D \| op \| addr16BE \| data` register grammar below |
| `0xB8` | 2 | 4 | OUT `wValue=1 wIndex=5 wLength=5 data=0000030020`; the paired IN asks for **33 bytes**. Not a `3D` payload. `[CAPTURED]` |
| `0xC1` | 1 | 2 | OUT `wValue=0x00FD wIndex=0 wLength=0` (no data stage). Its IN returns a **zero-length response even with no preceding OUT** — the only vendor IN observed that does not stall cold. `[CAPTURED]` |
| `0xC2` | 1 | 2 | OUT `wValue=4 wIndex=8 wLength=8 data=6877696e666f2e62` = ASCII `hwinfob`. `[CAPTURED]` |

**Correction:** earlier revisions of this document stated that every vendor transfer uses
`bRequest = 0xC0`. That was an artefact of filtering captures on `bRequest == 0xC0`. Every arm
sequence we had replayed therefore omitted 4 of the 138 vendor OUTs. `[CORRECTED]`

**But those four must not be folded into an arm sequence.** `[VERIFIED]` IR-31 held the device,
the readers and the sustaining strobe fixed and changed only how the arm was sent. The same 138
OUTs with the same payloads produced **3.27 / 2.66 / 2.0 MB/s** on EPs `0x82` / `0x83` / `0x84`
when the four were sent on their captured request codes (`0xB8`, `0xC1`, `0xC2`), and
**57.7 / 56.1 / 60.5 MB/s** when every OUT was forced to `bRequest 0xC0`. Read against the
driver's own request constants, `0xC1`/`wValue 253` is the firmware-version query (it answers
`00 0106` = FX3 1.6) and `0xC2`/`wValue 4` with payload `6877696e666f2e62` is the device-file
address lookup for `hwinfo.bin`. They are real traffic the vendor driver sends, and they are not
part of arming. **The arming sequence is the 134 `bRequest 0xC0` register transfers.** See
`EVIDENCE.md` §15.

Direction is carried entirely by `bmRequestType`.

| `bmRequestType` | Direction | Role |
|---|---|---|
| `0x40` | host -> device (OUT) | command / write |
| `0xC0` | device -> host (IN) | response / read |

`wValue` selects the **command class**. `wIndex` and `wLength` are set as follows,
measured over a full vendor-software start-up sequence:

| Transfer | `wIndex` | `wLength` | Exceptions |
|---|---|---|---|
| OUT | equals `wLength` = payload length | payload length | **0 of 138** |
| IN | always `1` | number of response bytes requested | **0 of 279** |

`[VERIFIED]` — 138 OUT and 279 IN transfers from one captured start-up sequence
(`ctrl_seq_full.json`).

> A common wrong guess, worth stating: `wIndex` on an OUT is **not** zero and **not** a
> register address. It is the payload length. An OUT sent with `wIndex = 0` and a
> non-empty payload is not what the device's own software sends.

## 3.2 The handshake: every OUT is followed by exactly two INs

Grouping the captured sequence by OUT transfers:

```
INs following each OUT:  2 INs -> 137 OUTs
                         5 INs ->   1 OUT   (the identity/serial command, class 0x0002)
```

`[VERIFIED]`

So a transaction is:

```
OUT   bmRequestType=0x40  bRequest=0xC0  wValue=<class>  wIndex=<len>  wLength=<len>  data
IN    bmRequestType=0xC0  bRequest=0xC0  wValue=<class>  wIndex=1      wLength=<R>    response
IN    bmRequestType=0xC0  bRequest=0xC0  wValue=<class>  wIndex=1      wLength=1      completion
```

For register reads, `R = 1 + N` where `N` is the requested register width (70/70
observed). For commands with no data response, `R = 1`. `[VERIFIED]`

**The critical rule:** a vendor IN issued **without a preceding OUT stalls**. Every such
attempt returned a pipe error (`Errno 32`, EPIPE / STALL). The response side of EP0 is
armed by the OUT; it is not a free polling port. `[VERIFIED]`

This is why blind status polling against this device fails, and why a client that
"just wants to read a register" must issue the OUT first even when it does not want to
change anything.

## 3.3 Command classes

`wValue` values observed, with what they do:

| `wValue` | OUT count | IN count | What is known |
|---|---|---|---|
| `0x0001` | 2 | 4 | OUT payload `00 00 03 00 20` (5 B). Response requested 51 B, device returned 2 B (`00 01`). Meaning `[UNKNOWN]`. |
| `0x0002` | 1 | 5 | **Identity block.** Returns the unit string `<unit-serial>`. See 1.3. `[VERIFIED]` |
| `0x0003` | 122 | 244 | **Register access** (section 3.4). The dominant class. |
| `0x0004` | 5 | 10 | 2-byte opcodes `0c00`, `0d00`, `0c01`, `0d01`, plus one 8-byte payload carrying ASCII `hwinfob`. Responses 1 B (`06` for the ASCII one). Meaning `[UNKNOWN]`. |
| `0x0005` | 1 | 2 | OUT `0074` (2 B) -> response `00 5a 56 96 11`. Meaning `[UNKNOWN]`. |
| `0x0006` | 3 | 6 | OUT 6 B: `00 04 00 00 00 40`, `00 04 00 00 00 7e`, `00 04 00 00 00 00`. Responses 1 B. Meaning `[UNKNOWN]`. |
| `0x0007` | 1 | 2 | OUT with **zero-length** payload -> response 3 B `00 01 3d`. Meaning `[UNKNOWN]`. |
| `0x0009` | 2 | 4 | OUT 4 B: `00 00 00 1b`, `00 00 00 00`. Responses 1 B. Meaning `[UNKNOWN]`. |
| `0x00FD` | 1 | 2 | OUT zero-length -> response 1 B `05`. Meaning `[UNKNOWN]`. |

`[VERIFIED]` for the counts and byte values; `[UNKNOWN]` for the semantics of every
class except `0x0002` and `0x0003`.

Note that classes `0x0007` and `0x00FD` have OUT transfers with `wLength = 0`. These are
the only OUTs in the capture with no payload, and they are also the OUTs whose payload
was not recoverable from the passive capture — so "zero-length" may be a capture gap
rather than a real zero-length command. `[UNCERTAIN]`

### 3.3.1 The request codes are named in the vendor driver

`Meta.Driver.dll`, class `Meta.Driver.Devices.Meta2CommandConstants`, names the request
codes directly. `[CAPTURED]` from the IL disassembly (`ikdasm`); the responses were then
read live on 2026-10-23 (`re/ir33_register_dump.py`, `re/ir34_request_families.py`).

| Constant | `bRequest` | Named values | Live behaviour |
|---|---|---|---|
| `REQUEST_CODE_BASE` | `0xB0` | `1 = GET_DEVICE_TYPE` | answers `03` for every value tried (1, 2, 4, 5, 6, 7, 9, 0xFD) |
| `REQUEST_CODE_STD` | `0xC0` | `2` memory read · `3` register access · `5` FPGA firmware date · `6` endpoint feed · `7` firmware version · `9` multiplexor feed | all in use in the arm |
| `REQUEST_CODE_GEO` | `0xB9` | `4 = GEO_FIRMWARE_VERSION` | bare (no payload): value 1 → `00 000e0000`, value 2 → `00 200f0000`, values 4–9 and 0xFD stall. With its own payload `[4, 2]` it answers the GEO version — see `09-driver-decompiled.md`. |
| `REQUEST_CODE_USB` | `0xC1` | `253 = USB_FIRMWARE_VERSION` | `00 0106` |
| `REQUEST_CODE_FILE` | `0xC2` | `4 = FILE_COMMAND` | `hwinfo.b` → `00 0000ff00` |

`0xB8` is used on the wire (twice per arm) but is **not** named in this class. `[VERIFIED]`

Two of these attach names to values already recorded above: `0xC0/7 → 00 013d` is the ARM
firmware version and `0xC1/0xFD → 00 0106` is the USB/FX3-side firmware version. The
decodings themselves are established in `09-driver-decompiled.md` (ARM 1.61, FPGA built
2018-01-10 22:39:13 UTC, FX3 1.6, GEO 1.25); the constant names corroborate them but add
nothing on their own, and `bcdDevice` still reads `0.00`.

`0xB9` had never been probed beyond its single named command (`/4` with `[4, 2]`). Bare it
answers at two other values, so there is a second command channel beyond the `0xC0` register
grammar with more than the one command the driver uses. `[VERIFIED]`

### 3.3.2 The `0xB8` response names the ToF sensor

`0xB8` / `wValue 1` / payload `00 00 03 00 20` returns 33 bytes:

```
00 50 4d 44 54 45 43 03 00 b6 40 73 ec 43 3f 04 00
50 4d 44 53 43 4c 00 04 3f 3f 00 02 00 01 00 00
    ----PMDTEC----                       ----PMDSCL----
```

`[CAPTURED]`. The record structure is not resolved — `[UNKNOWN]`. What is not unknown is
the name: **PMD** is the photonic-mixer-device class of ToF sensor, and the device's own
calibration file declares frame index 9 as `g_pmd_cad` (see `11-device-files.md` §11.4).
So this is the depth-sensor module table, and `0xB8` is the command family that reaches
it. `[INFERRED]`

`0xB8` answers status-only (`06` or `05`) when the OUT carries **no** payload, and its
data IN stalls when the OUT carries the vendor payload outside the arm sequence. See
§16 of `EVIDENCE.md` before sending `0xB8` transfers in an experiment.

## 3.4 Register grammar (class `0x0003`)

Payload layout:

```
byte 0     0x3D          fixed tag
byte 1     op
bytes 2-3  address       u16, BIG ENDIAN
bytes 4..  data
```

`[VERIFIED]` — the address field is big-endian. Confirmed by round-trip: writing
`3d 40 b0 07 01 80` and then reading `3d 21 b0 07 FF FF` returns `01 80`.

**Evidence correction.** That round-trip was never evidence from the passive capture: the
trace contains 279 vendor IN transfers and **none of them carries payload data**
(`tshark -Y "usb.bmRequestType==0xc0 && usb.data_payload"` returns 0 frames). The
round-trip is evidence from our own live probe — `data/vendor_in_responses.json`, where
reading `0xb062` returns exactly the 22 bytes the vendor had written there — reproduced
independently by `re/replay_reads.py`, which reads `0xb007` back as `0180`. `[VERIFIED]`

### Operations

| `op` | Role | Occurrences | Data lengths observed |
|---|---|---|---|
| `0x21` | **READ** | 70 | 2, 4, 8, 10, 12, 16, 18, 20, 40 |
| `0x40` | WRITE | 32 | 2, 18 |
| `0x20` | WRITE | 2 | 16 |
| `0x60` | WRITE | 3 | 4, 20 |
| `0xA0` | WRITE | 3 | 8, 40 |
| `0xC0` | WRITE | 5 | 10 |
| `0xE0` | WRITE | 1 | 12 |

`[VERIFIED]` for the counts and lengths.

**`op` does not encode the data length.** `0x40` appears with both 2-byte and 18-byte
data; `0x21` appears with nine different lengths. Whatever `op` means, it is not a
length field. `[VERIFIED]` that the mapping is not 1:1; `[UNKNOWN]` what `op` actually
distinguishes.

### Reading a register

A read is issued as a **mask**: the data field is `N` copies of `0xFF`, and the device
returns `N` value bytes preceded by one status byte.

```
OUT  3D 21 <addr:u16 BE> FF FF ... FF        (N bytes of FF)
IN   <status:u8> <value:N bytes>
```

Response length was `N + 1` in **70 of 70** reads. `[VERIFIED]`

**A read is only honored at the step the vendor's own sequence uses it.** This is the
single most important constraint on register access and it is easy to get wrong:

| how the read was issued | result |
|---|---|
| replay `ctrl_seq_full.json` transfer-for-transfer, answering each IN with the vendor's `wValue`/`wLength` | **70 reads served** with `00` + value |
| the identical read commands re-issued after the sequence completes | 98 of 98 return a **1-byte status only**, never the value |
| 376 addresses in ten ranges queried after the sequence, 2-byte mask | **0 readable** |
| the 34 written addresses queried as a batch, unarmed *or* during a live streaming window | status `07` + zeros for 33 of 34 |

`[VERIFIED]` (`re/replay_reads.py`, `re/replay_reread.py`, `re/reg_scan.py`,
`re/reg_read.py`, `re/reg_read_streaming.py`). The control endpoint behaves as a fixed
script, not a register bus. Whether another command shape unlocks arbitrary reads is
`[UNKNOWN]`; do not build a reader that assumes registers are queryable.

The leading status byte was `0x00` for the overwhelming majority of reads. `0x07` was
observed on an early read of `0xb007`. What the status codes mean is `[UNKNOWN]`.

A read of a register that was just written returns the written value, e.g. write
`0xb062 = a3c35568 00000000 00000000 aaaa032a` then read it back with a 16-byte mask
returns exactly those 16 bytes. `[VERIFIED]`

### Writing a register

```
OUT  3D <op> <addr:u16 BE> <data...>
```

All 138 OUT transfers of the captured vendor sequence were accepted by the device with
zero errors when replayed verbatim from a no-SDK client. `[VERIFIED]`

## 3.5 Reading a span: the base offset is NOT the address you asked for

This is a trap. It is tempting to model the register space as a flat byte window where
`read(addr, N)` returns bytes `[addr, addr+N)`. **That model is wrong.**

Evidence, all from live reads on one device in one session:

```
read 0xc2bc  2 B  -> 004e
read 0xc2c0  2 B  -> 07f1
read 0xc2c4  2 B  -> 07f1
read 0xc2c8  2 B  -> 07f1
read 0xc2cc  2 B  -> 07f1
read 0xc2bc 40 B  -> 004e0000 20000000 | 07f10000 000a0001 | 07f10000 004e0001
                    | 07f10000 00820001 | 07f103b7 00c60001
read 0xc2c0 16 B  -> 07f10000 000a0001 | 07f10000 004e0001
```

`[VERIFIED]`

In the 40-byte span returned for `0xc2bc`, the value that a direct read of `0xc2c0`
returns appears at span offset **8**, not offset 4. `0xc2c4`, `0xc2c8` and `0xc2cc`
appear at offsets 16, 24 and 32. The implied span base is therefore `0xc2b8` - four
bytes *below* the requested address. `[VERIFIED]` for this case.

A flat byte model would put `0xc2c0` at offset 4; a word-addressed model would put it at
offset 4 as well. Neither matches. The offset rule is not determined. `[UNKNOWN]`

**Practical rule:** read each register at the address you want, at the width you want,
and treat a wide read as returning a device-chosen span, not a window you control. Do not
compute sub-field offsets out of a wide read until you have confirmed the base for that
address.

### Aliasing

Reading `0xb04f`, `0xb050`, `0xb051`, `0xb052`, `0xb053` as five 2-byte reads returns
`5529`, `5555`, `4e15`, `c71b`, `0000`. Reading `0xc35e` with a 10-byte mask returns
`552955554e15c71b0000` - the same ten bytes from a completely different address.
`[VERIFIED]`

Two addresses exposing the same content is **aliasing**, and it is a separate phenomenon
from span offsets. It is also a warning: the same data may be reachable from several
places, and whether writing one alias writes the other is `[UNKNOWN]`.

### What is safe to assume

- Any address in the observed range can be read at any width; the device answers.
  `[VERIFIED]` for the addresses tested.
- A read of a just-written address returns the written value at the matching width.
  `[VERIFIED]` (e.g. `0xb007`, `0xb062`).
- Writes to an address show up inside later wide reads that cover it. `[VERIFIED]`
  (`0xc2c0`/`0xc2c4`/`0xc2c8`/`0xc2cc`, written by the vendor software, appear inside the
  `0xc2bc` span read and have replaced the values that software originally wrote there).

## 3.6 Replaying the vendor start-up sequence

The captured start-up sequence is **417 control transfers: 138 OUT + 279 IN**, in a
strict interleaved order. `[VERIFIED]`

Replaying it verbatim from a no-SDK client: all 138 OUTs accepted, 141 IN responses read
live, no errors. `[VERIFIED]`

The sequence is reproduced in `data/ctrl_seq_full.json` and is the input to the worked
example in `docs/06-writing-a-reader.md`.

**Important negative result:** replaying the sequence gets the device into a state where
it will produce data, but it does **not** by itself produce a continuous stream. See
5.5 and 7.1. `[VERIFIED]`

## 3.7 The vendor driver's own command vocabulary

`Meta.Driver.dll` carries the protocol constants as literal fields in
`Meta.Driver.Core.Meta2CommandConstants` and `Meta.Driver.Core.Meta2DriverConstants`.
Read directly from the IL (`re/dotnet/Meta.Driver.il`). `[VERIFIED]` as source-of-truth
for what the vendor driver *defines*; separately noted below for what it actually *uses*.

```
REQUEST_CODE_BASE              0xB0
REQUEST_CODE_STD               0xC0     <- the code every transfer in our arm uses
REQUEST_CODE_USB               0xC1     <- seen live (0xC1/0xFD answered 000106)
REQUEST_CODE_GEO               0xB9     <- never observed on the wire
REQUEST_FILE_COMMAND           0xC2     <- never observed as a bRequest in our arm

REQUEST_VALUE_FIRMWARE_VERSION       0x07
REQUEST_VALUE_FPGA_FIRMWARE_DATE     0x05
REQUEST_VALUE_GEO_FIRMWARE_VERSION   0x04
REQUEST_VALUE_USB_FIRMWARE_VERSION   0xFD  <- seen live
REQUEST_FILE_VALUE                   0x04  <- our device-file reads (wValue 4)
REQUEST_CONTINUE_FILE_VALUE          0x02
REQUEST_ENDPOINT_FEED_VALUE          0x06  <- our enable-mask request
REQUEST_MULTIPLEXOR_FEED_VALUE       0x09  <- our multiplexor request
MISC_EOF                             0xFF

SINGLE_TRANSFER_LENGTH  0x26 (38)
TRAILER_LENGTH          0x20 (32)   <- matches the observed 32-byte frame trailer
HEADER_LENGTH           0x1C (28)
VENDOR_ID 0x2CFA  PRODUCT_ID 0x00F3
REQUEST_VENDOR 0x40  DIRECTION_TO_DEVICE 0x00  DIRECTION_FROM_DEVICE 0x80
```

Two **separate** enable-bit layouts, which is why one mask cannot enable everything:

```
multiplexor feed (0xC0 / wValue 9, 4 bytes):   IMU0 0x01  IMU1 0x02  MICS 0x04  BUTTONS 0x08
camera feed      (0xC0 / wValue 6, 6 bytes):   MONO0 0x02 MONO1 0x04 TOF 0x08
                                               MULTIPLEXOR 0x10  RGB 0x20  STD 0x40
```

The live arm uses `wValue 6 = 00 04 00 00 00 7E` (MONO0|MONO1|TOF|MULTIPLEXOR|RGB|STD) and
`wValue 9 = 00 00 00 1B` (IMU0|IMU1|BUTTONS|0x10). `[VERIFIED]` from `data/ctrl_seq_full.json`.
`0x7E` is exactly "everything on the camera feed", and `0x48` (STD|TOF) is the ToF-only mask
used in IR-29. `[VERIFIED]`

`REQUEST_CODE_BASE` (0xB0), `REQUEST_CODE_GEO` (0xB9), `REQUEST_FILE_COMMAND` (0xC2) and the
firmware-version values `0x07`/`0x05`/`0x04` are **defined but never referenced** anywhere in
`Meta.Driver.il` — the only occurrences are the field definitions themselves. `[VERIFIED]`
They are therefore unprobed request codes, not known-good ones; treat them as leads, and note
that unpaired control reads have previously wedged the control channel (see EVIDENCE on the
IR-46/47 incident).
