/* scratch/msos_probe.c
 *
 * Does the device implement Microsoft OS descriptors? If it answers string index
 * 0xEE, Windows 10/11 installs WinUSB by itself with no INF, no catalog and no
 * signature warning - which is how most vendor-specific devices get WinUSB on a
 * clean machine. If it does not, an INF (and therefore a signature) is mandatory.
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>

static void hex(const char *tag, unsigned char *b, int n)
{
    printf("%s: %d bytes:", tag, n);
    for (int i = 0; i < n && i < 80; i++) printf(" %02x", b[i]);
    printf("\n");
}

int main(void)
{
    libusb_init(NULL);
    libusb_device_handle *h = libusb_open_device_with_vid_pid(NULL, 0x2cfa, 0x00f3);
    if (!h) { printf("device not present\n"); return 1; }

    unsigned char b[512];
    int n;

    /* The MS OS descriptor magic string: index 0xEE. */
    n = libusb_get_string_descriptor(h, 0xEE, 0x409, b, sizeof b);
    if (n < 0) {
        printf("string 0xEE: FAILED %s\n", libusb_error_name(n));
    } else {
        hex("string 0xEE", b, n);
        if (n >= 16)
            printf("signature bytes 14..15: %c%c  (MSFT100 means MS OS descriptors)\n",
                   b[14], b[15]);
    }

    /* MS OS descriptor v1: GET_DESCRIPTOR, bRequest 0x20, wIndex 0x0007. */
    n = libusb_control_transfer(h, 0x80, 0x20, 0x0007, 0x0000, b, sizeof b, 2000);
    if (n < 0) printf("MS OS compat ID: FAILED %s\n", libusb_error_name(n));
    else       hex("MS OS compat ID", b, n);

    /* MS OS descriptor v2: bRequest 0x20, wIndex 0x0008. */
    n = libusb_control_transfer(h, 0x80, 0x20, 0x0008, 0x0000, b, sizeof b, 2000);
    if (n < 0) printf("MS OS 2.0 compat ID: FAILED %s\n", libusb_error_name(n));
    else       hex("MS OS 2.0 compat ID", b, n);

    /* What the standard string descriptors say, for the record. */
    if (libusb_get_string_descriptor_ascii(h, 0x02, b, sizeof b) > 0)
        printf("iProduct: %s\n", (char *)b);

    libusb_close(h);
    libusb_exit(NULL);
    return 0;
}
