# Register map

Every entry below was obtained by issuing the register read against a live Meta 2
over plain libusb and reading the response back. **No entry here is a guess.**

Confidence: all rows are `[VERIFIED]` as *observed values*. What the registers *mean*
is `[UNKNOWN]` unless stated.

## How a register read works

```
OUT  bmRequestType=0x40 bRequest=0xC0 wValue=3 wIndex=4+N wLength=4+N
     payload = 3D 21 <addr:u16 BE> <FF x N>
IN   bmRequestType=0xC0 bRequest=0xC0 wValue=3 wIndex=1 wLength=N+1
     response = <status:u8> <value:N bytes>
IN   bmRequestType=0xC0 bRequest=0xC0 wValue=3 wIndex=1 wLength=1
     response = <status:u8>
```

The `N` trailing `0xFF` bytes are a *request mask*: they say how many bytes of the
register window to return. Across 70 reads the response length was exactly `N+1`
(70/70). `[VERIFIED]`

Two caveats that matter before you use this table:

- A wide read returns a device-chosen span, not the byte window `[addr, addr+N)`. For
  `0xc2bc` the span base sits four bytes *below* the requested address. See
  [03-control-protocol.md](03-control-protocol.md) section 3.5. `[VERIFIED]`
- Different addresses can alias the same content (`0xb04f..0xb053` and `0xc35e` return
  the same ten bytes). `[VERIFIED]`

The `Width read` column is the mask length used, not a property of the register. The
device answers any width at any tested address.

## Observed registers

| Address | Width read | Value(s) observed | Changes between reads | Reads |
|---|---|---|---|---|
| `0x0204` | 2 B | `0000 / 0001` | yes | 3 |
| `0x9802` | 2 B | `0001` | no | 1 |
| `0x9813` | 2 B | `13ff` | no | 1 |
| `0x981b` | 2 B | `7608` | no | 1 |
| `0xa880` | 2 B | `0000` | no | 2 |
| `0xa881` | 2 B | `0001` | no | 3 |
| `0xa882` | 8 B | `02801057 / 0280105700000004` | yes | 2 |
| `0xa886` | 8 B | `0000015f00010120` | no | 1 |
| `0xa88c` | 2 B | `4000` | no | 1 |
| `0xa88d` | 2 B | `0004` | no | 1 |
| `0xa88f` | 2 B | `031e` | no | 1 |
| `0xa892` | 2 B | `001d / 0311` | yes | 2 |
| `0xa893` | 18 B | `224113b203bb204113b103bb4459c4ec0bce` | no | 1 |
| `0xb007` | 2 B | `0040 / 0180 / 0700` | yes | 4 |
| `0xb00c` | 2 B | `0647` | no | 1 |
| `0xb00e` | 20 B | `1515151515151515151515151315151315150415` | no | 1 |
| `0xb014` | 2 B | `1a15` | no | 1 |
| `0xb04f` | 2 B | `5529` | no | 1 |
| `0xb050` | 2 B | `5555` | no | 1 |
| `0xb051` | 2 B | `4e15` | no | 1 |
| `0xb052` | 2 B | `c71b` | no | 1 |
| `0xb053` | 2 B | `0000` | no | 1 |
| `0xb062` | 16 B | `a3c355680000000000000000aaaa032a` | no | 1 |
| `0xb086` | 2 B | `1513` | no | 1 |
| `0xb09e` | 2 B | `0670` | no | 3 |
| `0xb09f` | 2 B | `6665` | no | 2 |
| `0xb0a0` | 2 B | `056c` | no | 2 |
| `0xb0a1` | 2 B | `089c` | no | 2 |
| `0xb0ad` | 2 B | `0a12` | no | 1 |
| `0xb0ae` | 2 B | `ef00 / ef02` | yes | 2 |
| `0xbff8` | 16 B | `0800072b080008000800080008000a2a` | no | 1 |
| `0xc035` | 2 B | `0001` | no | 1 |
| `0xc036` | 2 B | `8000` | no | 2 |
| `0xc2bc` | 40 B | `004e00002000000008d30000000a000108d30000004e000108d3000000820...` | no | 1 |
| `0xc2c0` | 2 B | `07f1` | no | 1 |
| `0xc2c4` | 2 B | `07f1` | no | 1 |
| `0xc2c8` | 2 B | `07f1` | no | 1 |
| `0xc2cc` | 4 B | `07f103b7` | no | 1 |
| `0xc352` | 12 B | `68391b4f03e880453d71060a` | no | 1 |
| `0xc35e` | 10 B | `552955554e15c71b0000` | no | 1 |
| `0xc363` | 10 B | `552955554e15c71b0000 / 5529e83234f457120002` | yes | 2 |
| `0xc368` | 10 B | `552955554e15c71b0000` | no | 1 |
| `0xc36d` | 10 B | `552955554e15c71b0000` | no | 1 |
| `0xc400` | 2 B | `0000` | no | 2 |
| `0xc401` | 2 B | `0001 / 0002` | yes | 2 |
| `0xc402` | 2 B | `0000 / 0040` | yes | 2 |
| `0xc40d` | 2 B | `8012` | no | 1 |
| `0xc40f` | 2 B | `0000` | no | 2 |

Total distinct registers read: **48**.

Registers whose value changed between reads in one session: `0x0204`, `0xa882`, `0xa892`, `0xb007`, `0xb0ae`, `0xc363`, `0xc401`, `0xc402`.

These are the candidates for status/telemetry registers. `[INFERRED]`

## Address clusters

Observed register addresses fall into bands: `0x0204`, `0x98xx`, `0xa88x-0xa89x`,
`0xb00x-0xb06x`, `0xb08x-0xb0ax`, `0xbff8`, `0xc03x`, `0xc2bx-0xc40x`.

These are registers on the far side of the Cypress FX3 bridge, not USB descriptors.
`[INFERRED]` — the FX3 is a USB-to-anything bridge; the register space belongs to whatever
it talks to, and we have not identified that target.

## What is NOT known

- The unit/scale of any register value.
- Which register enables which sensor stream (the central open problem).
- Whether writes persist across power cycles.
- Whether the register space is FX3-side RAM or a remote SoC's address space.
