/* win_probe.c - stage-by-stage transport probe for 2cfa:00f3.
 *
 * Built for Windows (mingw) and Linux from the same source. It answers, in
 * order, whether the failure is: enumeration, interface claim, control
 * transfers, bulk before arming, bulk after arming, or throughput.
 *
 *   build (Windows):
 *     x86_64-w64-mingw32-gcc -Wall -o win_probe.exe win_probe.c \
 *       -I<include> -I<libusb include> <libmeta2_transport.a> <libusb-1.0.a> \
 *       -lsetupapi -lwinusb -lcfgmgr32 -ladvapi32 -luser32 -lole32 -lkernel32
 *   build (Linux):
 *     gcc -Wall -o win_probe win_probe.c -I<include> $(pkg-config --cflags --libs libusb-1.0) \
 *       <libmeta2_transport.a> -lpthread
 *
 * Run with arm_capture.txt in the same directory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libusb-1.0/libusb.h>
#include "meta2/transport.h"
#include "meta2/os.h"

static const int EPS[] = { 0x81, 0x82, 0x83, 0x84 };

static const char *speed_name(int s)
{
    switch (s) {
    case LIBUSB_SPEED_LOW:       return "LOW 1.5 Mb/s";
    case LIBUSB_SPEED_FULL:      return "FULL 12 Mb/s";
    case LIBUSB_SPEED_HIGH:      return "HIGH 480 Mb/s";
    case LIBUSB_SPEED_SUPER:     return "SUPER 5 Gb/s";
    case LIBUSB_SPEED_SUPER_PLUS:return "SUPER+ 10 Gb/s";
    default:                     return "unknown";
    }
}

/* Every 2cfa:00f3 node Windows/Linux currently knows about, with the physical
   port chain. Two instances of one VID/PID is worth seeing explicitly. */
static void list_candidates(libusb_context *ctx)
{
    libusb_device **list = NULL;
    int n = libusb_get_device_list(ctx, &list);
    int found = 0;
    for (int i = 0; i < n; i++) {
        struct libusb_device_descriptor d;
        if (libusb_get_device_descriptor(list[i], &d) != 0) continue;
        if (d.idVendor != 0x2cfa || d.idProduct != 0x00f3) continue;
        uint8_t ports[8] = {0};
        int pn = libusb_get_port_numbers(list[i], ports, 8);
        printf("  candidate: bus %d address %d speed %s  class %02x ports:",
               libusb_get_bus_number(list[i]), libusb_get_device_address(list[i]),
               speed_name(libusb_get_device_speed(list[i])), d.bDeviceClass);
        for (int p = 0; p < pn; p++) printf(" %d", ports[p]);
        printf("\n");
        found++;
    }
    libusb_free_device_list(list, 1);
    if (!found) printf("  no 2cfa:00f3 node found at all\n");
}

static void bulk_try(libusb_device_handle *h, const char *stage)
{
    static const int SIZES[] = { 1024, 65536 };
    for (unsigned i = 0; i < sizeof(EPS)/sizeof(EPS[0]); i++) {
        for (unsigned s = 0; s < sizeof(SIZES)/sizeof(SIZES[0]); s++) {
            int sz = SIZES[s];
            unsigned char *b = malloc((size_t)sz);
            int got = 0, rc = LIBUSB_ERROR_OTHER;
            rc = libusb_bulk_transfer(h, (unsigned char)EPS[i], b, sz, &got, 3000);
            printf("  %s EP 0x%02x size=%6d: rc=%d (%s) bytes=%d\n", stage, EPS[i], sz,
                   rc, libusb_strerror(rc), got);
            free(b);
            if (got > 0) break;
        }
    }
}

/* The arm, read the way meta2_capture_live reads arm_capture.txt:
     O <wValue> <wIndex> <hex payload>
     I <wValue> <in_len>                (wIndex fixed to 1)
   Returns -1 if the command file is missing. */
static int run_arm(libusb_device_handle *h, int *ok_out, int *fail_out)
{
    FILE *f = fopen("arm_capture.txt", "rb");
    if (!f) return -1;
    int ok = 0, fail = 0;
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
    *ok_out = ok; *fail_out = fail;
    return 0;
}

int main(void)
{
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) { printf("libusb_init failed\n"); return 1; }

    const struct libusb_version *v = libusb_get_version();
    printf("libusb version: %d.%d.%d\n", v->major, v->minor, v->micro);
    printf("--- candidates on the bus\n");
    list_candidates(ctx);

    libusb_device_handle *h = libusb_open_device_with_vid_pid(ctx, 0x2cfa, 0x00f3);
    if (!h) { printf("open failed\n"); libusb_exit(ctx); return 1; }
    libusb_device *dev = libusb_get_device(h);
    printf("opened: bus %d address %d speed %s\n",
           libusb_get_bus_number(dev), libusb_get_device_address(dev),
           speed_name(libusb_get_device_speed(dev)));

    struct libusb_device_descriptor dd;
    libusb_get_device_descriptor(dev, &dd);
    printf("bcdUSB %04x device class %02x bNumConfigurations %d\n",
           dd.bcdUSB, dd.bDeviceClass, dd.bNumConfigurations);

    struct libusb_config_descriptor *cfg = NULL;
    if (libusb_get_active_config_descriptor(dev, &cfg) == 0 && cfg) {
        printf("active config: value %d bmAttributes %02x MaxPower %d mA interfaces %d\n",
               cfg->bConfigurationValue, cfg->bmAttributes, cfg->MaxPower, cfg->bNumInterfaces);
        for (int i = 0; i < cfg->bNumInterfaces; i++) {
            const struct libusb_interface_descriptor *id = &cfg->interface[i].altsetting[0];
            printf("  interface %d class %02x subclass %02x protocol %02x eps %d\n",
                   id->bInterfaceNumber, id->bInterfaceClass, id->bInterfaceSubClass,
                   id->bInterfaceProtocol, id->bNumEndpoints);
            for (int e = 0; e < id->bNumEndpoints; e++) {
                const struct libusb_endpoint_descriptor *ep = &id->endpoint[e];
                printf("    ep %02x attr %02x maxpacket %u (burst %u) interval %u\n",
                       ep->bEndpointAddress, ep->bmAttributes,
                       (unsigned)(ep->wMaxPacketSize & 0x07ff),
                       (unsigned)((ep->wMaxPacketSize >> 11) & 0x3),
                       ep->bInterval);
            }
        }
        libusb_free_config_descriptor(cfg);
    } else {
        printf("no active configuration descriptor\n");
    }

    int rc = libusb_claim_interface(h, 0);
    printf("claim_interface 0: %d (%s)\n", rc, libusb_strerror(rc));

    /* Stage 1: a control read the arm sequence itself uses. If this answers,
       the device is talking and the control endpoint is fine. */
    unsigned char one = 0;
    int n = meta2_send_control(h, 0, 3, 1, &one, 0, 1);
    printf("vendor control read (wValue=3 in_len=1): rc=%d value=%02x\n", n, one);

    if (!getenv("SKIP_PRE")) {
        printf("bulk before arm:\n");
        bulk_try(h, "pre-arm ");
    }

    /* Stage 2: the full arm, read the same way meta2_capture_live reads it:
       O <wValue> <wIndex> <hex payload>
       I <wValue> <in_len>                (wIndex fixed to 1) */
    int ok = 0, fail = 0;
    double t0 = meta2_time_us();
    run_arm(h, &ok, &fail);
    printf("arm ok=%d fail=%d (%.2f s)\n", ok, fail, (meta2_time_us() - t0) / 1e6);

    printf("bulk after arm:\n");
    bulk_try(h, "post-arm");

    /* Stage 3: sustained, one endpoint at a time. Distinguishes "never any
       data" from "data but not enough". */
    for (unsigned i = 0; i < sizeof(EPS)/sizeof(EPS[0]); i++) {
        int sz = 4096;
        unsigned char *b = malloc((size_t)sz);
        long long bytes = 0; int reads = 0, timeouts = 0, errs = 0; int errcode = 0;
        double start = meta2_time_us();
        while (meta2_time_us() - start < 5000000.0) {
            int got = 0;
            int r = libusb_bulk_transfer(h, (unsigned char)EPS[i], b, sz, &got, 1000);
            if (r == 0) { bytes += got; reads++; }
            else if (r == LIBUSB_ERROR_TIMEOUT) timeouts++;
            else { errs++; errcode = r; break; }
        }
        double el = (meta2_time_us() - start) / 1e6;
        printf("  sustained EP 0x%02x size=%5d: %.2f MB/s reads=%d timeouts=%d errs=%d%s\n",
               EPS[i], sz, bytes / el / 1e6, reads, timeouts, errs,
               errs ? libusb_strerror(errcode) : "");
        free(b);
    }

    /* Stage 4: what a port reset does here. meta2_stream_start() re-arms after
       one, and its behaviour differs between Linux and WinUSB. */
    int rr = libusb_reset_device(h);
    printf("libusb_reset_device: %d (%s)\n", rr, libusb_strerror(rr));
    printf("after reset, control read: rc=%d\n",
           meta2_send_control(h, 0, 3, 1, &one, 0, 1));
    printf("bulk after reset (no re-arm):\n");
    bulk_try(h, "reset   ");

    /* Stage 5: close and reopen, then arm again. WinUSB cannot do a device
       reset (see the comment in libusb's windows_winusb.c), so this is the
       nearest thing to the port reset meta2_stream_start() relies on. If bulk
       data appears here and not above, the library's recovery step is what has
       to change on Windows. */
    libusb_close(h);
    meta2_sleep_us(1500000);
    h = libusb_open_device_with_vid_pid(ctx, 0x2cfa, 0x00f3);
    if (!h) {
        printf("reopen failed - the node may need Windows to rediscover it\n");
        libusb_exit(ctx);
        return 0;
    }
    printf("reopened: bus %d address %d speed %s\n",
           libusb_get_bus_number(libusb_get_device(h)),
           libusb_get_device_address(libusb_get_device(h)),
           speed_name(libusb_get_device_speed(libusb_get_device(h))));
    printf("claim after reopen: %d (%s)\n", libusb_claim_interface(h, 0),
           libusb_strerror(libusb_claim_interface(h, 0)));
    ok = fail = 0; t0 = meta2_time_us();
    if (run_arm(h, &ok, &fail) == 0)
        printf("arm after reopen ok=%d fail=%d (%.2f s)\n", ok, fail,
               (meta2_time_us() - t0) / 1e6);
    else
        printf("no arm_capture.txt next to the exe\n");
    printf("bulk after reopen + arm:\n");
    bulk_try(h, "reopen  ");

    libusb_close(h);
    libusb_exit(ctx);
    return 0;
}
