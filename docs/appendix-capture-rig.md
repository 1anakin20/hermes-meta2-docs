# Appendix A. The capture rig

How Path A (passive capture of the vendor software) was built, so the work in these
documents can be recreated independently.

Host-specific details (machine names, LAN addresses, credentials) are replaced with
placeholders. Nothing else is altered — the commands are the ones actually used.

## A.1 Why a Windows VM at all

The Meta SDK 2.7.0.38 is Windows-only, and the goal of Path A is to make the *vendor's
own software* drive the device so its real command sequence can be observed untouched.
That requires Windows.

**Windows 10 version 1809 (build 17763)** was chosen deliberately: the SDK behaves poorly
on later Windows 10/11 builds. `[CAPTURED]` — this is a practical choice, not a documented
compatibility matrix. If you pick a newer build and the SDK misbehaves, that is the most
likely reason.

## A.2 Host requirements

- Linux with KVM. Used here: Debian 13, kernel 6.12.x, QEMU 10.0.
- A **USB 3 (SuperSpeed) port on an `xhci_hcd` controller**. The device is only fully
  functional at SuperSpeed (see 02 §2.4). Plug it into a rear motherboard USB 3 port, not
  a front-panel header or a USB 2 hub.
- `qemu-system-x86_64`, OVMF (`ovmf` package), `dumpcap`/`tshark` (`wireshark-common`),
  `websockify` if you want browser access to the guest display.
- Root, or a udev rule plus group membership, for `/dev/bus/usb/*` and `/dev/usbmon*`.

## A.3 The QEMU command

The launcher used, reduced to the parts that matter for reproduction:

```sh
qemu-system-x86_64 \
  -name meta2win -enable-kvm -cpu host -m 16G -smp 6 \
  -drive if=pflash,format=raw,readonly=on,file=/usr/share/ovmf/OVMF.fd \
  -drive if=pflash,format=raw,file=OVMF_VARS.fd \
  -drive file=win1809.qcow2,format=qcow2,if=none,id=disk0 -device ide-hd,drive=disk0 \
  -device e1000,netdev=net0 \
  -netdev user,id=net0,hostfwd=tcp::2222-:22,hostfwd=tcp::3389-:3389 \
  -device qemu-xhci,id=xhci \
  -device usb-host,id=meta2usb,vendorid=0x2cfa,bus=xhci.0 \
  -chardev socket,id=qga,path=/tmp/meta2vm-qga.sock,server=on,wait=off \
  -device virtio-serial-pci,id=serial0 \
  -device virtserialport,chardev=qga,name=org.qemu.guest_agent.0,id=port0,bus=serial0.0 \
  -fsdev local,id=share,path=<workspace>,security_model=mapped-xattr \
  -device virtio-9p-pci,fsdev=share,mount_tag=hostshare \
  -vnc 0.0.0.0:9009 \
  -qmp unix:/tmp/meta2vm.qmp,server=on,wait=off
```

Decisions that were load-bearing:

| Choice | Why |
|---|---|
| **SATA/AHCI disk** (`ide-hd`), not virtio-blk | Windows has it built in. No driver injection needed during install. |
| **e1000 NIC**, not virtio-net | Built into Windows 10; RDP and SSH work immediately after install. |
| **Two OVMF pflash drives** (code read-only + writable `OVMF_VARS.fd`) | Without the writable variable store OVMF hangs on a black screen before the first frame. `[VERIFIED]` |
| **`id=meta2usb` on the USB device** | Without an explicit id, QMP cannot hot-unplug it. With one, `device_del` hands the device to the host while the VM keeps running — which is what makes Path B possible without a reboot. `[VERIFIED]` |
| **VNC, not SPICE** | Mutually exclusive in QEMU; VNC was chosen so noVNC works in a browser. |
| **9p share** | Lets you push the SDK and the reader into the guest without a network transfer. |

**Cold attach beats hotplug here.** Launching with `-device usb-host,...` already present
worked reliably; hotplugging an already-opened device via QMP hit permission problems on
this host. Start the VM with the device attached. `[CAPTURED]`

## A.4 Windows install

The install was done **manually through the VNC console** (browser access via
`websockify 0.0.0.0:6080 -> VNC 5900+9009`). An `autounattend.xml` answer disk was
prepared but did not take effect; the manual path is what actually produced the install.
`[CAPTURED]` — do not count on unattended install working.

After install, in the guest:

1. Enable the OpenSSH server (Settings → Optional Features → OpenSSH Server), or use RDP
   on the forwarded port 3389.
2. Confirm `ssh -p 2222 <user>@127.0.0.1` from the host reaches the guest.

## A.5 Installing the SDK

Meta SDK 2.7.0.38 installer, run in the guest. The installer's `bin\` directory contains
the DLLs that matter for this documentation:

| DLL | Role |
|---|---|
| `meta_core_api.dll` | Public C API facade. **Contains no USB imports** — it is not the transport. `[CAPTURED]` |
| `cyapi.dll` | Cypress FX3 host API. This *is* the transport (WinUSB). `[CAPTURED]` |
| `meta2_host_itf.dll`, `meta2_host_impl.dll` | Protocol layer. Exports are ordinal-only, so static analysis has to go through strings and mangled symbols. `[CAPTURED]` |

## A.6 The reader program

A ~180-line C# program calling `meta_core_api.dll` with `Cdecl`. Signatures were taken
verbatim from the SDK's own Unity interop layer (`SystemInterop.cs`, `SlamInterop.cs`,
`DeviceStatusSnapshot.cs`) rather than guessed.

Build inside the guest with the .NET Framework compiler that ships with Windows:

```
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe /nologo /platform:x64 /out:MetaReader.exe MetaReader.cs
```

Copy the SDK's `bin\*.dll` next to the exe. Run:

```
MetaReader.exe <outDir> <seconds>
```

It writes RGB frames, point-cloud `.ply` files, `pose.csv` and `status.csv`.

**The pitfall that wasted the most time in this project:** the reader only streams when
launched **in the foreground of a blocking session**. `start /b`, backgrounded SSH, and
detached console launches all return immediately and produce **zero frames** while looking
like they succeeded. `[VERIFIED]` — three separate 0-frame runs were misdiagnosed as a
broken reader before this was identified. Run it as:

```sh
ssh -p 2222 <user>@127.0.0.1 'C:\MetaReader\MetaReader.exe C:\MetaReader\OUT 40 >nul 2>&1'
```

as a **foreground** command, and let it block for the full duration.

## A.7 Finding the right usbmon device

`/dev/usbmonN` is per-controller, not per-device. Find which monitor covers the port the
headset is on:

```sh
# which controller owns the bus the device appears on
lsusb                                   # note the bus number, e.g. Bus 004
cat /sys/bus/usb/devices/usb*/busnum    # map bus numbers to controllers
readlink -f /sys/bus/usb/devices/usb4/device:usb4/driver
# -> .../0000:07:00.0  (the XHCI controller)
# that controller is covered by usbmon3 and usbmon4
```

`[VERIFIED]` on this host; the exact numbering is host-specific. Verify rather than
assuming `usbmon0`.

Permissions: `chmod 666 /dev/usbmon*` for a quick test, or a udev rule.

## A.8 Capturing

Start the capture first, then start the reader:

```sh
# 1. capture the two monitors covering the device's controller
dumpcap -i usbmon3 -i usbmon4 -a duration:45 -w /tmp/meta2_trace.pcapng

# 2. while that runs, in a separate foreground terminal:
ssh -p 2222 <user>@127.0.0.1 'C:\MetaReader\MetaReader.exe C:\MetaReader\OUT 40 >nul 2>&1'
```

Expected result of a correct overlap run: a pcapng of ~21 MB containing ~147,000 USB
frames, of which ~1,000 are control transfers on the device and ~29,000 are bulk IN
completions on EP 0x81. `[CAPTURED]`

If the capture is empty or near-empty, the overwhelmingly likely cause is that **the
reader is not actually streaming** (A.6), not that usbmon is broken. Confirm frame output
from the reader before debugging the capture.

Extraction gotchas are listed in `EVIDENCE.md` §3 — the tshark 4.4 field-name issues are
substantial and will cost you an hour if you don't read them first.

## A.9 Handing the device to the host for Path B

With the VM running:

```sh
# remove from the guest
printf '{"execute":"qmp_capabilities"}\n{"execute":"device_del","arguments":{"id":"meta2usb"}}\n' \
  | socat - UNIX-CONNECT:/tmp/meta2vm.qmp

# confirm it is free on the host
lsusb | grep 2cfa
ls -l /dev/bus/usb/<bus>/<addr>

# ... run host-side libusb work ...

# give it back
printf '{"execute":"qmp_capabilities"}\n{"execute":"device_add","arguments":{"driver":"usb-host","hostbus":<bus>,"hostaddr":<addr>,"id":"meta2usb","bus":"xhci.0"}}\n' \
  | socat - UNIX-CONNECT:/tmp/meta2vm.qmp
```

`[VERIFIED]` — this is how the no-SDK client in `examples/` was run against the device
without shutting the VM down.

## A.10 Things that look like device problems but are not

| Symptom | Actual cause |
|---|---|
| `pgrep -f qemu-system-x86_64` says the VM is running, but nothing works | `pgrep -f` matched its own wrapper shell. Use `ps -eo pid,comm | awk '$2 ~ /^qemu/'`. `[VERIFIED]` |
| Reader produces 0 frames | It was never actually launched (A.6). `[VERIFIED]` |
| usbmon captures 0 bytes | Reader wasn't streaming. `[VERIFIED]` |
| libusb enumerates 0 devices on the host | QEMU holds the device, or the container has no `usbfs`. Not a driver problem. `[VERIFIED]` |
| Device answers control transfers but never streams | USB 2 port. See 02 §2.4. `[VERIFIED]` |
