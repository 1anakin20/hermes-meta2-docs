# 6. Writing your own reader

Target language: **C or C++ over libusb-1.0**. The transport is plain libusb; no vendor
driver, no vendor SDK, no Windows required.

## 6.1 What you can build today, and what you cannot

| Goal | Status |
|---|---|
| Detect and open the device | works `[VERIFIED]` |
| Read the unit identity string | works `[VERIFIED]` |
| Read any register in the observed range | works `[VERIFIED]` |
| Write registers the vendor software writes | works `[VERIFIED]` |
| Get one 64 KB camera block per trigger | works `[VERIFIED]` |
| Get a continuous full-frame camera stream | **does not work yet** `[UNKNOWN]` |
| Get raw IMU | not located `[UNKNOWN]` |
| Get audio, buttons, temperature | not located on the wire `[UNKNOWN]` |

Be honest with yourself about that last group. The vendor SDK's type system proves those
data types exist; it does not tell you which bytes carry them.

## 6.2 Build

```sh
sudo apt install libusb-1.0-0-dev pkg-config
cc -O2 -Wall -o meta2_probe examples/meta2_probe.c $(pkg-config --cflags --libs libusb-1.0)
```

`examples/meta2_probe.c` compiles clean under `-Wall -Wextra` with libusb-1.0 on Debian
13 (gcc 14, libusb 1.0.28). `[VERIFIED]`

## 6.3 Verified output of the worked example

Run against a real Meta 2 on Linux, no SDK present:

```
opened 2cfa:00f3

identity (class 0x0002):
  56 bytes returned
  ......<unit-serial>.................................

register reads:
  0xb007 = 01 80
  0xa880 = 00 00
  0xa881 = 00 01
  0x0204 = 00 01
  0x9813 = 13 ff
  0x981b = 76 08
  0xa882 = 02 80 10 57 00 00 00 04
  0xb062 = a3 c3 55 68 00 00 00 00 00 00 00 00 aa aa 03 2a
  0xc2bc = 00 4e 00 00 20 00 00 00 07 f1 00 00 00 0a 00 01 07 f1 00 00 00 4e 00 01 07 f1 00 00 00 82 00 01 07 f1 03 b7 00 c6 00 01

write + read-back 0xb007:
  wrote 0180, read back 0180
```

`[VERIFIED]` — this is literal program output, not an illustration.

The `Pipe error` lines the run also emits are expected: they come from the trailing
1-byte completion INs after some transactions, which stall when the device has nothing
left to return. They are harmless. Handle them as "no more responses", not as failure.
`[VERIFIED]`

## 6.4 The four rules that actually matter

**1. `bRequest` is `0xC0` for the register grammar, but it is not the only vendor request.**
Direction comes from `bmRequestType`: `0x40` out, `0xC0` in. A live vendor-driver session uses
134 OUTs on `0xC0` and 4 more on `0xB8`, `0xC1` and `0xC2`; a reader that filters on
`bRequest == 0xC0` silently drops those four. See `03-control-protocol.md` §3.1. `[VERIFIED]`

**2. On an OUT, `wIndex` equals the payload length.** Not zero, not an address. 138 of
138 observed transfers. `[VERIFIED]`

**3. On an IN, `wIndex` is always `1`.** 279 of 279 observed. `[VERIFIED]`

**4. Never issue a vendor IN cold.** A vendor IN with no preceding OUT stalls — every
attempt returned a pipe error. The OUT arms the response. If you want to read a register,
send the read request (which *is* an OUT) first. `[VERIFIED]`

## 6.5 Register access, minimal and correct

```c
/* read N bytes of a register window */
uint8_t req[44], rsp[64];
req[0] = 0x3D; req[1] = 0x21;                 /* tag, op = READ */
req[2] = addr >> 8; req[3] = addr & 0xFF;     /* BIG ENDIAN address */
memset(req + 4, 0xFF, N);                     /* N-byte width mask */

libusb_control_transfer(h, 0x40, 0xC0, 3, 4 + N, req, 4 + N, 1500);
int n = libusb_control_transfer(h, 0xC0, 0xC0, 3, 1, rsp, N + 1, 1500);
/* rsp[0] = status, rsp[1..N] = value */
libusb_control_transfer(h, 0xC0, 0xC0, 3, 1, rsp, 1, 600);   /* completion */
```

Response length is `N + 1` in 70 of 70 observed reads. `[VERIFIED]`

## 6.6 Reading the camera — the shape that actually works

**Start the bulk readers first, then run control traffic.** This is the single most
important thing in this document. A client that replays the command sequence and *then*
reads gets one 65,536-byte URB per endpoint and concludes the device cannot stream. A
client that keeps a looping reader on each endpoint and runs control traffic around it gets
whole frames at 10 fps or more. `[VERIFIED]`

```
reader thread per endpoint:  loop { read(EP, 262144, timeout) }   <- started first
main thread:                 loop { send the control subset }      <- data flows only here
```

Rules that follow from the measurements: `[VERIFIED]`

- **One process, one thread per endpoint.** Two processes cannot both claim interface 0;
  the second bulk reader dies with `LIBUSB_ERROR_BUSY`. Threads inside one process work.
- **Data stops when control traffic stops.** The device is not free-running once armed;
  keep the control subset looping for the whole session.
- A bulk read timeout between frames is normal. Treat it as "no frame yet", not as an
  error.

Frames on EP 0x83 are delimited by the 32-byte record in 5.3. To render one:

```c
/* frame = 1280*720*2 = 1,843,200 bytes of little-endian u16, followed by a
   32-byte record beginning ba ab ed fe */
uint16_t *px = (uint16_t *)frame;
for (int i = 0; i < 1280 * 720; i++) {
    int row = i / 1280, col = i % 1280;
    out[row * 1280 + col] = px[i] >> 8;      /* 16-bit -> 8-bit for display */
}
```

**Stated precisely:** this snippet follows the framing established in 5.3, but it was not
compiled and run as part of a worked example the way `examples/meta2_probe.c` was. Treat it
as the documented shape, not as verified program output. `[INFERRED]`

**Withdrawn:** the earlier "65,536-byte block = 32,744 sample slots + 48-byte trailer =
25.58 rows, blocks are independent acquisitions you cannot concatenate" description. It
measured URB size, not device framing. See 5.3.

## 6.7 Pitfalls, each one learned the hard way

| Pitfall | What happens | Fix |
|---|---|---|
| USB 2 port | device enumerates, answers control, never streams | use a SuperSpeed port; `bFunctionalitySupport = 3` |
| Assuming `bMaxPacketSize0 = 9` means 9 bytes | control responses truncated | it is 2^9 = 512 on USB 3 |
| Polling vendor INs without an OUT | every read stalls (`LIBUSB_ERROR_PIPE`) | always send the OUT first |
| Assuming a wide read is a byte window | wrong sub-field offsets | confirm the span base per address (3.5) |
| Assuming URB boundaries align with EP 0x81 records | garbage framing | resynchronise on the `45 00 00 ea` tag |
| Trusting URB sizes to infer the endpoint map | wrong endpoint map | EP 0x82 has the biggest URBs and returns nothing |
| Another process holding the device | libusb cannot open it | check for a VM with USB passthrough before blaming drivers |
| Two bulk readers in two processes | second one fails with `LIBUSB_ERROR_BUSY` | one process, one thread per endpoint |
| Handshake, then read | 65,536 bytes and silence; looks like the device cannot stream | keep readers pending *during* control traffic |
| Stop the control traffic mid-session | the stream dies within seconds | keep the control subset looping |
| Concluding "needs a proprietary driver" from a failed open | dead end | the device binds no kernel driver; it is a host-environment problem |

## 6.8 Reproducing the captures

See [EVIDENCE.md](EVIDENCE.md). The short version: capture on `usbmon` while the vendor
software streams, then replay the extracted sequence from a no-SDK client.
