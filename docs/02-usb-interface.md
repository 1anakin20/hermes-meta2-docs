# 2. USB interface

All descriptors below were read live from a Meta 2 attached to a Linux host
(`lsusb -v -d 2cfa:00f3`). `[VERIFIED]`

## 2.1 Device descriptor

```
bLength                18
bDescriptorType        1
bcdUSB                 3.00
bDeviceClass           0        (interface-specific)
bDeviceSubClass        0
bDeviceProtocol        0
bMaxPacketSize0        9        -> 512 bytes (USB3 encodes EP0 size as a power of 2)
idVendor               0x2cfa   USB Design By Meta
idProduct              0x00f3   Meta2
bcdDevice              0.00
iManufacturer          1        "USB Design By Meta"
iProduct               2        "Meta2"
iSerial                0        (none)
bNumConfigurations     1
```

**`bMaxPacketSize0 = 9` is not 9 bytes.** On USB 3.0 this field is an exponent:
2^9 = **512-byte** control packets. A host implementation that allocates an 9-byte
control buffer will silently truncate control responses. `[VERIFIED]` descriptor value;
`[VERIFIED]` interpretation (USB 3.0 spec encoding).

## 2.2 Configuration / interface

```
Configuration Descriptor
  bLength                 9
  bDescriptorType         2
  wTotalLength            0x0046
  bNumInterfaces          1
  bConfigurationValue     1
  iConfiguration          0
  bmAttributes            0x80   (Bus Powered)
  MaxPower                64mA

Interface Descriptor
  bInterfaceNumber        0
  bAlternateSetting       0
  bNumEndpoints           4
  bInterfaceClass         255    Vendor Specific Class
  bInterfaceSubClass      0
  bInterfaceProtocol      0
  iInterface              0
```

One interface, one alternate setting, vendor class `0xFF`. There is no standard-class
fallback: nothing here is a CDC, UVC, HID or mass-storage device. A generic host driver
will do nothing with it. `[VERIFIED]`

## 2.3 Endpoints

All four are bulk IN. Identical geometry.

| Endpoint | Address | Type | `wMaxPacketSize` | `bMaxBurst` | `bInterval` |
|---|---|---|---|---|---|
| EP 1 IN | `0x81` | Bulk | `0x0400` (1024) | 15 | 0 |
| EP 2 IN | `0x82` | Bulk | `0x0400` (1024) | 15 | 0 |
| EP 3 IN | `0x83` | Bulk | `0x0400` (1024) | 15 | 0 |
| EP 4 IN | `0x84` | Bulk | `0x0400` (1024) | 15 | 0 |

`[VERIFIED]`

Notes that matter in practice:

- **Bulk OUT does not exist.** There is no bulk OUT endpoint. Everything the host sends
  goes through EP0 control transfers. This bounds how much you can send: control
  transfers, not streams. `[VERIFIED]`
- `bMaxBurst 15` means one SuperSpeed service period can carry 15 × 1024 = 15360 bytes.
  The vendor software requests URBs far larger than that (16 KB on EP 0x81, 131–262 KB
  on EPs 0x82–0x84); the host controller splits them. `[VERIFIED]` descriptor value;
  `[CAPTURED]` the URB sizes.
- Nothing ever came back on EP 0x82 in any capture we made. `[CAPTURED]`

## 2.4 BOS / device capabilities

```
Binary Object Store Descriptor
  wTotalLength            0x0016
  bNumDeviceCaps          2

USB 2.0 Extension
  bmAttributes            0x00000000   (LPM not advertised)

SuperSpeed USB Device Capability
  bmAttributes            0x00
  wSpeedsSupported        0x000e   FS + HS + SS
  bFunctionalitySupport   3        fully functional only at SuperSpeed
  bU1DevExitLat           0 us
  bU2DevExitLat           0 us

Device Status: 0x000c  (Bus Powered, U1 Enabled, U2 Enabled)
```

`bFunctionalitySupport = 3` is the single most important line in this document for
someone whose reader is not working: **the device is only fully functional at
SuperSpeed.** If your host port is USB 2, or a USB 3 port negotiating down, the device
will enumerate and answer control transfers but will not stream. `[VERIFIED]`

## 2.5 Claiming the device — Linux

The device binds to no kernel driver by default (`driver=none` was observed on a plain
Debian 6.12 host with the device attached). `[CAPTURED]`

```c
dev = /* libusb_open of 2cfa:00f3 */;
libusb_set_configuration(dev, 1);
libusb_claim_interface(dev, 0);
```

If a driver is bound, detach it first:

```c
if (libusb_kernel_driver_active(dev, 0) == 1)
    libusb_detach_kernel_driver(dev, 0);
```

Permissions: either run as root, or add a udev rule. A rule that was used and worked:

```
# /etc/udev/rules.d/99-meta2-usb.rules
ATTR{idVendor}=="2cfa", ATTR{idProduct}=="00f3", MODE="0660", GROUP="plugdev"
```

`[VERIFIED]` that a udev rule of this shape made the device readable without root.

## 2.6 Claiming the device — Windows

The vendor's own software uses **WinUSB** (via Cypress's `cyapi.dll`, which takes a
WinUSB device GUID). `[CAPTURED]`

That means a custom Windows client needs no vendor driver either — it needs a WinUSB
binding on interface 0. Two ways:

1. Install a WinUSB driver for the interface (Zadig, or an INF with the WinUSB
   `DeviceInterfaceGUID`), then use `WinUsb_ControlTransfer` / `WinUsb_ReadPipe`.
2. Use libusb-1.0's Windows backend, which is WinUSB underneath.

`[INFERRED]` from the vendor's own transport choice plus the standard-class-free
interface; not tested on Windows in this project.

## 2.7 Known host-side pitfall

On one host in this project, libusb enumerated **zero** devices and raw `usbfs` ioctls
returned `ENOTTY` (`Inappropriate ioctl for device`), while the device was plainly
visible in `lsusb`. The cause was the environment: no usable `usbfs` mount in that
container, and the device was being held by a QEMU virtual machine that had it passed
through. `[CAPTURED]`

If `lsusb` shows the device but libusb cannot open it, check in this order:

1. Is another process holding it? A VM with USB passthrough claims the device
   exclusively. `lsusb -t` and the process list will show it.
2. Is the container/host missing `usbfs`? `mount | grep usb` — a container without it
   cannot do raw USB at all.
3. Permissions.

Do not conclude the device needs a special driver from a failure like this. It does not.
