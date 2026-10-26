/*
 * win_probe - stage-by-stage check of the Windows transport.
 *
 * meta2_capture_live on Windows arms the device (272 ok / 135 fail, the same
 * shape Linux reports for a healthy arm) but every bulk IN read times out and
 * 0 bytes arrive. This separates the stages so the failure can be located:
 *   1. what the guest's USB stack actually sees in the descriptors
 *   2. whether a vendor control transfer answers
 *   3. whether a bulk IN transfer answers before any arming
 *   4. whether a bulk IN transfer answers after the full arm + sustain
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meta2/transport.h"
#include "meta2/os.h"

static const int EPS[] = { 0x81, 0x82, 0x83, 0x84 };

static void bulk_try(libusb_device_handle *h, const char *stage)
{
    static const int SIZES[] = { 256, 65536 };
    for (unsigned i = 0; i < sizeof(EPS)/sizeof(EPS[0]); i++) {
        for (unsigned s = 0; s < sizeof(SIZES)/sizeof(SIZES[0]); s++) {
            int sz = SIZES[s];
            unsigned char *b = malloc((size_t)sz);
            int got = 0, rc = LIBUSB_ERROR_OTHER;
            for (int t = 0; t < 2 && got == 0; t++) {
                rc = libusb_bulk_transfer(h, (unsigned char)EPS[i], b, sz, &got, 3000);
            }
            printf("  %s EP 0x%02x size=%6d: rc=%d (%s) bytes=%d\n", stage, EPS[i], sz,
                   rc, libusb_strerror(rc), got);
            free(b);
            if (got > 0) break;   /* something is moving on this endpoint */
        }
    }
}

int main(void)
{
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx)) { printf("libusb_init failed\n"); return 1; }
    libusb_device_handle *h = libusb_open_device_with_vid_pid(ctx, 0x2cfa, 0x00f3);
    if (!h) { printf("open failed: no such device visible to Windows\n"); return 1; }
    libusb_device *dev = libusb_get_device(h);

    struct libusb_device_descriptor dd;
    libusb_get_device_descriptor(dev, &dd);
    printf("device: %04x:%04x bcdUSB=%04x class=%02x ifaces=%d\n",
           dd.idVendor, dd.idProduct, dd.bcdUSB, dd.bDeviceClass, dd.bNumConfigurations);

    struct libusb_config_descriptor *cfg = NULL;
    if (libusb_get_active_config_descriptor(dev, &cfg) == 0 && cfg) {
        printf("config: value=%d selfPowered=%d remoteWakeup=%d interfaces=%d\n",
               cfg->bConfigurationValue, cfg->bmAttributes & 1,
               (cfg->bmAttributes >> 5) & 1, cfg->bNumInterfaces);
        for (int i = 0; i < cfg->bNumInterfaces; i++) {
            const struct libusb_interface_descriptor *id = &cfg->interface[i].altsetting[0];
            printf("  iface %d: class=%02x subclass=%02x protocol=%02x eps=%d\n",
                   id->bInterfaceNumber, id->bInterfaceClass, id->bInterfaceSubClass,
                   id->bInterfaceProtocol, id->bNumEndpoints);
            for (int e = 0; e < id->bNumEndpoints; e++) {
                const struct libusb_endpoint_descriptor *ep = &id->endpoint[e];
                printf("    ep 0x%02x attr=%02x maxpacket=%d\n",
                       ep->bEndpointAddress, ep->bmAttributes & 3, ep->wMaxPacketSize);
            }
        }
        libusb_free_config_descriptor(cfg);
    } else {
        printf("libusb_get_configuration failed\n");
    }

    int rc = libusb_claim_interface(h, 0);
    printf("claim_interface(0): %d (%s)\n", rc, libusb_strerror(rc));

    /* Stage 2: one vendor control read, copied from the arm sequence ("I 3 1"). */
    int n = meta2_send_control(h, 0, 3, 1, NULL, 0, 1);
    printf("vendor control read (wValue=3 in_len=1): %d\n", n);

    /* Stage 3: bulk before any arming. Expected to time out - that is the baseline.
       SKIP_PRE=1 skips it, so the arm+read phase can be observed under usbmon. */
    if (!getenv("SKIP_PRE")) {
        printf("bulk before arm:\n");
        bulk_try(h, "pre-arm ");
    }

    /* Stage 4: full arm from the same command file Linux uses, then bulk again.
       Line format, as meta2_capture_live reads it:
         O <wValue> <wIndex> <hex payload>
         I <wValue> <in_len>            (wIndex is fixed to 1) */
    FILE *f = fopen("arm_capture.txt", "rb");
    if (!f) { printf("no arm_capture.txt next to the exe\n"); return 2; }
    int ok = 0, fail = 0;
    double t0 = meta2_time_us();
    char line[512];
    while (fgets(line, sizeof line, f)) {
        int wv = 0, wi = 0, len = 0;
        char hex[256];
        unsigned char payload[256];
        if (line[0] == 'O') {
            if (sscanf(line, "O %d %d %255s", &wv, &wi, hex) != 3) continue;
            len = (int)strlen(hex) / 2;
            if (len > 256) len = 256;
            for (int i = 0; i < len; i++) sscanf(hex + 2*i, "%2hhx", &payload[i]);
            if (meta2_send_control(h, 1, wv, wi, payload, len, len ? len : 1) >= 0) ok++;
            else fail++;
        } else if (line[0] == 'I') {
            if (sscanf(line, "I %d %d", &wv, &len) != 2) continue;
            if (meta2_send_control(h, 0, wv, 1, NULL, 0, len) >= 0) ok++;
            else fail++;
        }
    }
    fclose(f);
    printf("arm ok=%d fail=%d (%.2f s)\n", ok, fail, (meta2_time_us() - t0) / 1e6);

    printf("bulk after arm:\n");
    bulk_try(h, "post-arm");

    /* Stage 5: sustained SEQUENTIAL read of one endpoint at a time. capture_live
       reads all four at once and gets nothing here; this asks whether the pipe
       carries data at all when only one endpoint is outstanding. */
    static const int RS[] = { 1024, 8192 };
    for (unsigned i = 0; i < sizeof(EPS)/sizeof(EPS[0]); i++) {
        for (unsigned s = 0; s < sizeof(RS)/sizeof(RS[0]); s++) {
            int sz = RS[s];
            unsigned char *b = malloc((size_t)sz);
            long long bytes = 0; int reads = 0, timeouts = 0, errs = 0;
            double t0 = meta2_time_us();
            while (meta2_time_us() - t0 < 5000000.0) {
                int got = 0;
                int rc = libusb_bulk_transfer(h, (unsigned char)EPS[i], b, sz, &got, 1000);
                if (rc == 0) { bytes += got; reads++; }
                else if (rc == LIBUSB_ERROR_TIMEOUT) timeouts++;
                else { errs++; break; }
            }
            double el = (meta2_time_us() - t0) / 1e6;
            printf("  sustained EP 0x%02x size=%5d: %.2f MB/s  reads=%d timeouts=%d errs=%d\n",
                   EPS[i], sz, bytes / el / 1e6, reads, timeouts, errs);
            free(b);
        }
    }

    libusb_close(h);
    libusb_exit(ctx);
    return 0;
}
