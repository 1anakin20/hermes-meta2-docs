/*
 * meta2_probe.c - minimal Meta 2 client, no vendor SDK.
 *
 * Does only things that have been verified against a real device:
 *   1. enumerate and open 2cfa:00f3
 *   2. read the unit identity string (class 0x0002)
 *   3. read a register (class 0x0003, op 0x21)
 *   4. write a register (class 0x0003, op 0x40) and read it back
 *
 * It deliberately does NOT try to stream sensor data: the command that enables
 * continuous streaming is not known (docs/07-open-questions.md).
 *
 * Build:  cc -O2 -Wall -o meta2_probe meta2_probe.c $(pkg-config --libs libusb-1.0)
 * Run:    sudo ./meta2_probe            (or use a udev rule, docs/02-usb-interface.md)
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define VID 0x2CFA
#define PID 0x00F3
#define VENDOR_REQ 0xC0          /* every vendor transfer uses this bRequest */
#define DIR_OUT 0x40             /* bmRequestType: vendor | OUT | device recipient */
#define DIR_IN  0xC0             /* bmRequestType: vendor | IN  | device recipient */

static int vendor_out(libusb_device_handle *h, uint16_t wValue,
                      const uint8_t *data, int len)
{
    /* wIndex == wLength == payload length. Verified on 138/138 transfers. */
    int r = libusb_control_transfer(h, DIR_OUT, VENDOR_REQ, wValue,
                                    (uint16_t)len, (unsigned char *)data,
                                    (uint16_t)len, 1500);
    if (r < 0) fprintf(stderr, "  OUT class=0x%04x len=%d failed: %s\n",
                       wValue, len, libusb_strerror(r));
    return r;
}

/* A vendor IN is only valid after a matching OUT; the response endpoint is armed by
 * the OUT and stalls otherwise. Verified: every un-armed attempt returned LIBUSB_ERROR_PIPE. */
static int vendor_in(libusb_device_handle *h, uint16_t wValue,
                     uint8_t *buf, int len)
{
    int r = libusb_control_transfer(h, DIR_IN, VENDOR_REQ, wValue,
                                    1 /* wIndex is always 1 on IN */, buf,
                                    (uint16_t)len, 1500);
    if (r < 0) fprintf(stderr, "  IN class=0x%04x len=%d failed: %s\n",
                      wValue, len, libusb_strerror(r));
    return r;
}

/* Register read: data field is N bytes of 0xFF acting as a width mask.
 * Response is 1 status byte + N value bytes (verified 70/70). */
static int reg_read(libusb_device_handle *h, uint16_t addr, uint8_t *out, int n)
{
    uint8_t req[4 + 40];
    uint8_t rsp[64];
    if (n < 1 || n > (int)sizeof(req) - 4) return -1;

    req[0] = 0x3D;
    req[1] = 0x21;                       /* op = READ */
    req[2] = (uint8_t)(addr >> 8);       /* address is BIG ENDIAN */
    req[3] = (uint8_t)(addr & 0xFF);
    memset(req + 4, 0xFF, n);

    if (vendor_out(h, 3, req, 4 + n) < 0) return -1;

    int r = vendor_in(h, 3, rsp, n + 1);
    if (r < n + 1) return -1;

    /* rsp[0] is the status byte; the register value follows. */
    if (rsp[0] != 0) fprintf(stderr, "  note: status byte 0x%02x for 0x%04x\n", rsp[0], addr);
    memcpy(out, rsp + 1, n);

    /* Second IN completes the transaction (every OUT is followed by two INs). */
    vendor_in(h, 3, rsp, 1);
    return 0;
}

static int reg_write(libusb_device_handle *h, uint16_t addr, uint8_t op,
                     const uint8_t *data, int n)
{
    uint8_t req[4 + 40];
    uint8_t rsp[4];
    if (n < 1 || n > (int)sizeof(req) - 4) return -1;

    req[0] = 0x3D;
    req[1] = op;                         /* 0x40, 0x20, 0x60, 0xA0, 0xC0, 0xE0 all seen */
    req[2] = (uint8_t)(addr >> 8);
    req[3] = (uint8_t)(addr & 0xFF);
    memcpy(req + 4, data, n);

    if (vendor_out(h, 3, req, 4 + n) < 0) return -1;
    vendor_in(h, 3, rsp, 1);            /* data IN */
    vendor_in(h, 3, rsp, 1);            /* completion IN */
    return 0;
}

int main(void)
{
    libusb_context *ctx = NULL;
    libusb_device_handle *h = NULL;
    int r;

    r = libusb_init(&ctx);
    if (r < 0) { fprintf(stderr, "libusb_init: %s\n", libusb_strerror(r)); return 1; }

    h = libusb_open_device_with_vid_pid(ctx, VID, PID);
    if (!h) {
        fprintf(stderr,
            "2cfa:00f3 not found or not openable.\n"
            "  - is it on a USB 3 port? the device is only functional at SuperSpeed\n"
            "  - is a VM holding it? passthrough claims it exclusively\n"
            "  - permissions? run as root or add a udev rule\n");
        libusb_exit(ctx);
        return 1;
    }

    /* The device binds no kernel driver by default, but be defensive. */
    if (libusb_kernel_driver_active(h, 0) == 1)
        libusb_detach_kernel_driver(h, 0);

    r = libusb_set_configuration(h, 1);
    if (r < 0) fprintf(stderr, "set_configuration: %s\n", libusb_strerror(r));
    r = libusb_claim_interface(h, 0);
    if (r < 0) { fprintf(stderr, "claim_interface: %s\n", libusb_strerror(r));
                 libusb_close(h); libusb_exit(ctx); return 1; }

    printf("opened 2cfa:00f3\n");

    /* --- 1. identity string, class 0x0002 --- */
    {
        uint8_t out[64];
        uint8_t in[56];
        memset(out, 0x00, sizeof out);
        out[0] = 0x13; out[1] = 0x00; out[2] = 0xFF;   /* as sent by the vendor software */

        printf("\nidentity (class 0x0002):\n");
        if (vendor_out(h, 2, out, 64) >= 0) {
            int n = vendor_in(h, 2, in, sizeof in);
            if (n > 0) {
                printf("  %d bytes returned\n  ", n);
                for (int i = 0; i < n; i++)
                    putchar((in[i] >= 32 && in[i] < 127) ? in[i] : '.');
                printf("\n");
            }
            for (int i = 0; i < 4; i++) vendor_in(h, 2, in, 1);  /* remaining INs */
        }
    }

    /* --- 2. read registers that are known to respond --- */
    printf("\nregister reads:\n");
    struct { uint16_t addr; int n; } probes[] = {
        {0xb007, 2}, {0xa880, 2}, {0xa881, 2}, {0x0204, 2},
        {0x9813, 2}, {0x981b, 2}, {0xa882, 8}, {0xb062, 16}, {0xc2bc, 40},
    };
    for (unsigned i = 0; i < sizeof probes / sizeof probes[0]; i++) {
        uint8_t v[40];
        if (reg_read(h, probes[i].addr, v, probes[i].n) == 0) {
            printf("  0x%04x =", probes[i].addr);
            for (int k = 0; k < probes[i].n; k++) printf(" %02x", v[k]);
            printf("\n");
        }
    }

    /* --- 3. write then read back. Values below are ones the vendor software itself
           writes; do not substitute invented values. --- */
    printf("\nwrite + read-back 0xb007:\n");
    {
        uint8_t d[2] = {0x01, 0x80};
        uint8_t v[2];
        if (reg_write(h, 0xb007, 0x40, d, 2) == 0 && reg_read(h, 0xb007, v, 2) == 0)
            printf("  wrote 0180, read back %02x%02x\n", v[0], v[1]);
    }

    libusb_release_interface(h, 0);
    libusb_close(h);
    libusb_exit(ctx);
    return 0;
}
