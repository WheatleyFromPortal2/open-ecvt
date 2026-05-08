#include "pico/stdlib.h"
#include <stdio.h>
#include "utils/utils.h"

int main(void) {
    stdio_init_all();

    // disable automatic \r\n translation
    stdio_set_translate_crlf(&stdio_usb, false);

    led_init();
    adc_utils_init();

    // wait until USB connection is actually open
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("eCVT DCU starting...\n");
    printf("hello world from Pico!\n");

    unsigned long count = 0;
    while (true) {
        printf("alive: %lu\n", count++);
        printf("temp: %d\n", read_cpu_temp());
        printf("millis: %u\n", millis());
        led_toggle();
        sleep_ms(1000);
    }
}
