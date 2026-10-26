# 20. Running `meta2lib` on Windows

Status of the Windows side, and the one thing that currently blocks it.

Everything marked `[MEASURED]` was run and its output kept. Everything marked
`[INFERRED]` is reasoning from that evidence. `[UNVERIFIED]` means it is a plan
that has not been executed anywhere.

---

## 20.1 What the device needs before any program can open it

`[MEASURED]` from `lsusb -v -d 2cfa:00f3`:

| property | value |
|---|---|
| `idVendor` / `idProduct` | `0x2cfa` / `0x00f3` |
| interfaces | one |
| `bInterfaceClass` | `0xFF` (vendor-specific) |
| `bInterfaceSubClass` / `bInterfaceProtocol` | `0x00` / `0x00` |
| endpoints | four bulk-IN, **no bulk OUT** |
| link speed | SuperSpeed, 5 Gbps |

`[MEASURED]` The device does **not** implement Microsoft OS descriptors.
`scratch/msos_probe.c`:

```
string 0xEE: FAILED LIBUSB_ERROR_PIPE
MS OS compat ID: FAILED LIBUSB_ERROR_PIPE
MS OS 2.0 compat ID: FAILED LIBUSB_ERROR_PIPE
iProduct: Meta2
```

The ordinary string descriptors answer normally, so the control endpoint works;
the STALLs are specific to the MS OS feature.

That matters because MS OS descriptors are the mechanism by which a
vendor-specific device gets WinUSB installed by Windows with no INF, no catalog
and no signature prompt. This device does not have them.

`[INFERRED]` No in-box Windows driver matches a single vendor-specific
interface, so on a machine that has never had the Meta SDK the device arrives
with no driver at all. A driver package has to be supplied.

`[INFERRED]` Because there is one interface, the function driver binds to the
device directly. `usbccgp`, which exists to split composite devices into
per-interface children, is not involved.

---

## 20.2 The driver package we wrote

`meta2lib/driver/meta2.inf`. It installs **Microsoft's own `WinUSB.sys`** as the
function driver for `USB\VID_2CFA&PID_00F3`.

It ships no binary. Every file it installs is already inside Windows and already
signed by Microsoft, so nothing of ours runs in kernel space.

Shape:

- `Class = USB`, `ClassGuid = {36fc9e60-c465-11cf-8056-4445bc7c5199}`
- `AddService = WinUSB, 0x00000002, ...` — the `0x2` is
  `SPSVCINST_ASSOCSERVICE`, the flag that actually associates the service with
  the device node. Without it WinUSB is installed as a service and is not the
  device's function driver.
- `ServiceBinary = %12%\WinUSB.sys` — the in-box driver.
- `DeviceInterfaceGUIDs = {c0ee1632-92f8-44a1-bcff-6013a2369925}`, fixed so a
  native WinUSB client can open the device by GUID. `libusb` does not need it.
- `PnpLockdown = 1` so a class driver cannot silently take the interface back.
- No `CatalogFile` line. A catalog signs the binaries a package installs; this
  package installs none of its own. Referencing a catalog that is not shipped
  fails the install outright, which is worse than a warning.

---

## 20.3 The blocker: an unsigned INF is refused, not warned about

`[MEASURED]` Windows 10 1809 x64 guest, test signing off (`bcdedit /enum`
reports no `testsigning` entry), administrator shell:

```
pnputil /add-driver meta2.inf /install
Microsoft PnP Utility

Adding driver package:  meta2.inf
Failed to add driver package: The third-party INF does not contain digital
signature information.

Total driver packages:  1
Added driver packages:  0
```

`[MEASURED]` Two third-party packages already in that guest's driver store, for
comparison:

```
Original Name:  metasaq.inf     Provider: Meta Company
                Signer Name: Meta Company
Original Name:  usbpcap.inf     Provider: USBPcap
                Signer Name: Microsoft Windows Hardware Compatibility Publisher
```

Both went through a signing route. 64-bit Windows will not stage a third-party
INF without a signed catalog, and a catalog cannot be produced without a
code-signing certificate.

`[INFERRED]` The plan of "ship an unsigned INF and tell users the warning is
harmless" does not work on x64 Windows. There is no warning to accept.

---

## 20.4 The routes that could replace it

Ranked by how much is known. None has been executed.

1. **A real code-signing certificate.** Sign a catalog that covers `meta2.inf`,
   then `pnputil /add-driver meta2.inf /install` succeeds with no user action.
   This is the only route that ends with an install a normal user can do.
   Cost and enrolment are outside the repository. `[UNVERIFIED]`
2. **Microsoft attestation signing.** The USBPcap entry above shows what its
   output looks like in the driver store: `Signer Name: Microsoft Windows
   Hardware Compatibility Publisher`. Requires a Partner Center account and a
   submission. `[UNVERIFIED]`
3. **Test signing** (`bcdedit /set testsigning on`). Accepts unsigned packages.
   It is not a warning: it changes the boot configuration, puts a watermark on
   the desktop, and is a permanent property of the machine. Not acceptable for a
   tool handed to other people. `[UNVERIFIED]`
4. **Zadig.** The fallback this whole approach was meant to remove. Whether it
   sidesteps the catalog requirement, and how, has not been verified here.
   `[UNVERIFIED]`

`[UNVERIFIED]` `ReplaceDevice` as an INF directive to win against a Windows
Update rebind. It is deliberately absent rather than guessed at, because an
unrecognised directive can fail the whole INF.

Evidence gathered: `C:\Windows\INF` on that guest holds 662 `.inf` files and
`findstr /s /i /m ReplaceDevice` matches none of them. The same command does
work on that tree - `AddService` matches `oem2.inf` and `oem3.inf`. So the
negative result is real but narrow: it covers the class INFs in `C:\Windows\INF`,
not the driver packages in the DriverStore, which this guest does not expose at
the path searched. The directive's syntax was not confirmed either way, because
the search backend was returning no results (see 20.7).

---

## 20.5 The Meta SDK assumption, and how to undo the install

`[MEASURED]` from the vendor's own package, `metavision/driver/MetaSAQ.inf`:

- it matches the same hardware ID: `%VID_2CFA&PID_00F3.DeviceDesc%=CyUsb3, USB\VID_2CFA&PID_00F3`
- it registers its own device class, "AR Experience Devices",
  `ClassGUID {bb0697e3-404c-42be-8de0-85710015bd26}`
- it installs a kernel driver of its own, `METAUSB3.sys`, service `CYUSB3`,
  KMDF 1.11, with a `WdfCoInstaller01011.dll` co-installer
- it publishes `DriverGUID {5aa8bb92-30a4-449d-b94e-5b995e862939}`

`[INFERRED]` Our INF and the vendor's INF compete for the same hardware ID, in
different classes. **Install ours on a machine that has never had the Meta SDK.**
That is the assumption the whole driver story rests on, and it is the assumption
the install instructions have to state out loud.

Reverting, once an install exists, `[UNVERIFIED]`: find the published name with
`pnputil /enum-drivers`, then `pnputil /delete-driver oemN.inf /uninstall`,
then unplug and replant the device so Windows re-runs driver selection.

---

## 20.6 The library itself cross-compiles

`[MEASURED]` On Linux, with `mingw-w64` and libusb 1.0.28 built static for
`x86_64-w64-mingw32`:

```
cmake -S . -B build-win \
      -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw64.cmake \
      -DMETA2_LIBUSB_ROOT=<prefix with include/libusb-1.0 + lib/libusb-1.0.a>
cmake --build build-win
```

- 27 targets built, 24 Windows executables
- `file` on one: `PE32+ executable for MS Windows 5.02 (console), x86-64`
- imports of `meta2_capture_live.exe`: `KERNEL32.dll`, `msvcrt.dll` only
- no undefined symbols in the linked executable

`[MEASURED]` `nm -u` on libusb's `windows_winusb.o` shows no `SetupDi*` or
`WinUsb*` undefined symbols — only `__imp_LoadLibraryA` and
`__imp_GetProcAddress`. libusb 1.0.28 loads the SetupAPI and WinUSB entry
points at runtime, so the absence of a static SetupAPI import is expected and
not a missing dependency.

`[MEASURED]` `pthread` is gone from the public interface. `include/meta2/os.h`
carries opaque `meta2_mutex_t` / `meta2_thread_t`, `src/os.c` holds both
implementations, and a compile-time size check fails the build if the reserved
storage is smaller than the real OS object on either side.

`[OPEN]` None of these Windows binaries has been executed yet. They compile and
link; that is not the same as working, and the driver blocker above is exactly
why they cannot be run against the device yet.

---

## 20.7 Open items

1. A signing route for `meta2.inf` — the blocker, and a decision with cost.
2. Run a cross-built harness on real Windows with the headset attached, and
   re-tune `meta2_stream_start()` for the Windows host. The startup recipe is
   empirical and the hysteresis is not understood; a different host controller
   and driver stack may need different gate settings.
3. Whether Windows Update rebinds `USB\VID_2CFA&PID_00F3` on Windows 11, and
   what actually wins if it does.
4. The GUI, which is the end goal, is not started.
5. `ReplaceDevice` syntax, and whether it is even the right mechanism against a
   Windows 11 rebind. Not confirmable from this environment while the search
   backend returns nothing.
