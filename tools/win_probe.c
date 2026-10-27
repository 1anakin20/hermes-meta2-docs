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

static void bulk_try_sizes(libusb_device_handle *h, const char *stage,
                           const int *SIZES, int nsz)
{
    for (unsigned i = 0; i < sizeof(EPS)/sizeof(EPS[0]); i++) {
        for (int s = 0; s < nsz; s++) {
            int sz = SIZES[s];
            unsigned char *b = malloc((size_t)sz);
            int got = 0, rc = LIBUSB_ERROR_OTHER;
            double t0 = meta2_time_us();
            rc = libusb_bulk_transfer(h, (unsigned char)EPS[i], b, sz, &got, 3000);
            double el = (meta2_time_us() - t0) / 1000.0;   /* ms actually waited */
            printf("  %s EP 0x%02x size=%6d: rc=%d (%s) bytes=%d waited=%.0f of 3000 ms\n",
                   stage, EPS[i], sz, rc, libusb_strerror(rc), got, el);
            free(b);
            if (got > 0) break;
        }
    }
}

static void bulk_try(libusb_device_handle *h, const char *stage)
{
    static const int SIZES[] = { 1024, 65536 };
    bulk_try_sizes(h, stage, SIZES, 2);
}

/* The arm, read the way meta2_capture_live reads arm_capture.txt:
     O <wValue> <wIndex> <hex payload>
     I <wValue> <in_len>                (wIndex fixed to 1)
   Returns -1 if the command file is missing. */
/* An empty value means unset: PowerShell can leave a variable set to "". */
static int flag(const char *name) {
    const char *v = getenv(name);
    return v && *v;
}

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

/* Stage 6 support: the Linux recipe at raw libusb level. IN requests are already
   outstanding on all four endpoints before the arm lands, and every completion is
   resubmitted immediately, so an endpoint is never left unserviced. On Linux a
   single blocking URB does exactly this; on Windows each read is aborted, so the
   question is whether continuous servicing is what makes the device produce. */
struct pend { struct libusb_transfer *t; unsigned char *buf; int ep; double t0;
              long long bytes; int completions; int timeouts; int first_ms; };
static struct pend P[4];
static volatile int pend_stop;

static void LIBUSB_CALL pend_cb(struct libusb_transfer *t)
{
    struct pend *p = (struct pend *)t->user_data;
    p->completions++;
    if (t->status == LIBUSB_TRANSFER_COMPLETED) {
        p->bytes += t->actual_length;
        if (t->actual_length > 0 && p->first_ms < 0)
            p->first_ms = (int)((meta2_time_us() - p->t0) / 1000.0);
    } else if (t->status == LIBUSB_TRANSFER_TIMED_OUT) {
        p->timeouts++;
    }
    if (!pend_stop) { if (libusb_submit_transfer(t) != 0) p->timeouts++; }  /* keep IN queued */
}

/* LIB_OPEN=1  - open the way meta2lib does: meta2_open(), which on Windows sends
   a real SET_CONFIGURATION control request to the device (libusb's
   winusb_set_configuration() at windows_winusb.c:2126). The raw path never does.
   LIB_RESET=1 - then do the reset + close + 2 s + reopen cycle that
   meta2_capture_live does at its start. */
static void pending_stage(libusb_context *ctx, int seconds, int sz)
{
    libusb_context *ec = ctx;
    libusb_device_handle *h;
    if (flag("LIB_OPEN")) {
        void *hh = NULL;
        int orc = meta2_open(&hh);
        if (orc) { printf("  meta2_open failed: %d\n", orc); return; }
        h = (libusb_device_handle *)hh;
        ec = (libusb_context *)meta2_context();
        printf("  meta2_open ok (SET_CONFIGURATION sent); events on meta2 context\n");
        if (flag("LIB_RESET")) {
            printf("  meta2_reset: %d (%s)\n", meta2_reset(h),
                   libusb_strerror(meta2_reset(h)));
            meta2_close(h);
            meta2_sleep_us(2000000);
            if (meta2_open(&hh)) { printf("  reopen failed\n"); return; }
            h = (libusb_device_handle *)hh;
            ec = (libusb_context *)meta2_context();
            printf("  reopened\n");
        }
    } else {
        h = libusb_open_device_with_vid_pid(ctx, 0x2cfa, 0x00f3);
        if (!h) { printf("  pending stage: open failed\n"); return; }
        if (flag("SETCONF")) {
            int sc = libusb_set_configuration(h, 1);
            printf("  SET_CONFIGURATION added, nothing else changed: rc=%d (%s)\n",
                   sc, libusb_strerror(sc));
        }
        if (flag("RAWRESET")) {          /* the reset cycle alone, nothing else */
            int rr = libusb_reset_device(h);
            printf("  raw reset: %d (%s)\n", rr, libusb_strerror(rr));
            libusb_release_interface(h, 0);
            libusb_close(h);
            meta2_sleep_us(2000000);
            h = libusb_open_device_with_vid_pid(ctx, 0x2cfa, 0x00f3);
            if (!h) { printf("  raw reopen failed\n"); return; }
            printf("  raw reopened\n");
        }
        printf("  claim: %d (%s)\n", libusb_claim_interface(h, 0),
               libusb_strerror(libusb_claim_interface(h, 0)));
    }

    for (unsigned i = 0; i < 4; i++) {
        P[i].ep = EPS[i];
        P[i].bytes = 0; P[i].completions = 0; P[i].timeouts = 0; P[i].first_ms = -1;
        P[i].buf = malloc((size_t)sz);
        P[i].t = libusb_alloc_transfer(0);
        libusb_fill_bulk_transfer(P[i].t, h, (unsigned char)EPS[i], P[i].buf, sz,
                                  pend_cb, &P[i], 10000);   /* outlast the 8 s arm */
    }
    double t0 = meta2_time_us();
    for (int i = 0; i < 4; i++) P[i].t0 = t0;
    int submitted = 0;
    for (int i = 0; i < 4; i++) if (libusb_submit_transfer(P[i].t) == 0) submitted++;
    printf("  submitted %d of 4 IN requests BEFORE any control traffic\n", submitted);

    int ok = 0, fail = 0;
    run_arm(h, &ok, &fail);
    printf("  arm (with IN pending) ok=%d fail=%d (%.2f s)\n", ok, fail,
           (meta2_time_us() - t0) / 1e6);

    double end = meta2_time_us() + seconds * 1000000.0;
    while (meta2_time_us() < end) {
        struct timeval tv = { 0, 100000 };
        libusb_handle_events_timeout_completed(ec, &tv, NULL);
    }
    pend_stop = 1;
    for (int i = 0; i < 4; i++) {
        libusb_cancel_transfer(P[i].t);
        struct timeval tv = { 0, 200000 };
        libusb_handle_events_timeout_completed(ec, &tv, NULL);
    }
    for (int i = 0; i < 4; i++) {
        printf("  pending EP 0x%02x: %lld B completions=%d timeouts=%d first_data=%s\n",
               P[i].ep, P[i].bytes, P[i].completions, P[i].timeouts,
               P[i].first_ms < 0 ? "none" : "yes");
        if (P[i].first_ms >= 0) printf("    first data after %d ms\n", P[i].first_ms);
        libusb_free_transfer(P[i].t);
        free(P[i].buf);
    }
    libusb_close(h);
}

int main(void)
{
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) { printf("libusb_init failed\n"); return 1; }

    const struct libusb_version *v = libusb_get_version();
    printf("libusb version: %d.%d.%d\n", v->major, v->minor, v->micro);
    printf("--- candidates on the bus\n");
    list_candidates(ctx);

    /* ONLY_PENDING=1: skip every earlier stage and go straight to the
       pending-before-arm test, in a fresh process. Without this, that stage runs
       after several arms and several successful reads, so its result could be
       hysteresis from the earlier stages rather than a startup property. */
    if (flag("ONLY_PENDING")) {
        printf("ONLY_PENDING: straight to pending-before-arm, nothing before it\n");
        pending_stage(ctx, 20, 65536);
        libusb_exit(ctx);
        return 0;
    }

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

    if (!flag("SKIP_PRE")) {
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

    /* The loop above stops at the first success, so a 65536-byte URB has never
       been tried after an arm on Windows. The library reads 65536. Try it alone. */
    printf("bulk after arm, 65536-byte URB only:\n");
    static const int BIG[] = { 65536 };
    bulk_try_sizes(h, "post-big", BIG, 1);

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

    /* Stage 6: the Linux recipe, on a clean handle, with IN requests kept
       continuously outstanding. Run last so no earlier stage's aborts are in
       the way. */
    printf("--- pending-before-arm, 65536-byte URBs (what the library does)\n");
    meta2_sleep_us(1500000);
    pending_stage(ctx, 12, 65536);

    printf("--- pending-before-arm, 1024-byte URBs (the size that just worked)\n");
    meta2_sleep_us(1500000);
    pending_stage(ctx, 12, 1024);

    libusb_exit(ctx);
    return 0;
}
