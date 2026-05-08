#include "pico/stdlib.h"
#include <stdio.h>
#include "utils/utils.h"

int main(void) {
    stdio_init_all();

    led_init();

    // wait until USB connection is actually open
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("eCVT DCU starting...\n");
    printf("hello world from Pico!\n");

    unsigned long count = 0;
    while (true) {
        printf("alive: %lu\n", count++);
        led_toggle();
        sleep_ms(1000);
    }
}
