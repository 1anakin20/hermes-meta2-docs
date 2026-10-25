#!/usr/bin/env python3
"""Resolve Ghidra's export-thunk stubs to their real bodies, offline.

Ghidra names the 5-byte export jump stubs straight from the PE export table, so a "function"
called `pllSettings @ 1800059d4 (5 bytes)` is a trampoline, not the code. Ghidra 12.2's Java API
would not let the post-script follow them, so this does it from the raw bytes instead and appends
the real bodies to ghidra_targets.txt for the next headless pass.

Handles the three shapes MSVC x64 actually emits here:
  E9 rel32                      jmp rel32
  FF 25 rel32                   jmp [rip+disp]  (CFG / guard-check call table -> read the qword)
  48 B9 imm64 ; FF E1           movabs rcX, target ; jmp rcX   (CFG-fguard thunk)
"""
import struct
import sys

DLL = "/home/hermes/work/metavision/sdk/Meta/Meta SDK2 Beta/bin/royale.2.3.1.dll"
INV = "/home/hermes/work/metavision/re/ghidra_out/inventory_royale.2.3.1.dll.tsv"
OUT = "/home/hermes/work/metavision/re/ghidra_targets.txt"


def sections(d):
    pe = struct.unpack_from("<I", d, 0x3c)[0]
    opt = pe + 24
    imgbase = struct.unpack_from("<Q", d, opt + 24)[0]
    nsec = struct.unpack_from("<H", d, pe + 6)[0]
    szopt = struct.unpack_from("<H", d, pe + 20)[0]
    sec = opt + szopt
    out = []
    for i in range(nsec):
        o = sec + i * 40
        name = d[o:o + 8].rstrip(b"\0").decode(errors="replace")
        vsz, va, rsz, ro = struct.unpack_from("<IIII", d, o + 8)
        out.append((name, imgbase + va, vsz, rsz, ro))
    return out


def main():
    d = open(DLL, "rb").read()
    secs = sections(d)

    def va2off(va):
        for name, sva, vsz, rsz, ro in secs:
            if sva <= va < sva + max(vsz, rsz):
                return ro + (va - sva)
        return None

    funcs = {}
    for line in open(INV):
        p = line.rstrip("\n").split("\t")
        if len(p) < 3:
            continue
        funcs[int(p[0], 16)] = (int(p[1]), p[2])

    resolved = {}
    unresolved = 0
    for va, (size, name) in funcs.items():
        if size > 16 or name.startswith("FUN_"):
            continue
        off = va2off(va)
        if off is None:
            continue
        code = d[off:off + 16]
        target = None
        if code[0] == 0xE9:
            target = va + 5 + struct.unpack_from("<i", code, 1)[0]
        elif code[0] == 0xEB:
            target = va + 2 + struct.unpack_from("<b", code, 1)[0]
        elif code[0] == 0xFF and code[1] == 0x25:
            ptrva = va + 6 + struct.unpack_from("<i", code, 2)[0]
            po = va2off(ptrva)
            if po is not None:
                target = struct.unpack_from("<Q", d, po)[0]
        elif code[0] == 0x48 and code[1] == 0xB9 and code[8] == 0xFF and code[9] == 0xE1:
            target = struct.unpack_from("<Q", code, 2)[0]
        elif code[0] == 0x48 and code[1] == 0xB8 and code[8] == 0xFF and code[9] == 0xE0:
            target = struct.unpack_from("<Q", code, 2)[0]
        if target is None:
            unresolved += 1
            continue
        # snap to a known function entry if one starts at/just after the target
        t = target
        if t not in funcs:
            for cand in range(target, target + 32):
                if cand in funcs:
                    t = cand
                    break
        if t in funcs and funcs[t][0] > 16:
            resolved[va] = (name, t, funcs[t][1], funcs[t][0])

    existing = set()
    try:
        for line in open(OUT):
            line = line.strip()
            if line and not line.startswith("#"):
                existing.add(int(line.split()[0], 16))
    except FileNotFoundError:
        pass

    added = 0
    with open(OUT, "a") as f:
        for va, (name, t, tname, tsize) in sorted(resolved.items()):
            if t in existing:
                continue
            f.write(f"0x{t:x}  # body of thunk {name} @ 0x{va:x} -> {tname} ({tsize} B)\n")
            added += 1

    print(f"thunks scanned: {sum(1 for v in funcs.values() if v[0] <= 16)}")
    print(f"resolved to real bodies: {len(resolved)}  unresolved shapes: {unresolved}")
    print(f"new target addresses appended: {added}")
    interesting = [(n, t, tn) for va, (n, t, tn, sz) in resolved.items()
                   if any(k in n.lower() for k in ("pll", "usecase", "bridge", "moduleconfig",
                                                   "imagerregister", "imagerburst", "exposure",
                                                   "gain", "gpio", "i2c"))]
    print(f"interesting resolved ({len(interesting)}):")
    for n, t, tn in sorted(interesting)[:40]:
        print(f"  {n:44s} -> 0x{t:x}  {tn}")


if __name__ == "__main__":
    main()
