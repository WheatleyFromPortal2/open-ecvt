// dcu/src/utils/utils.c
#include "utils.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"

#define VOLTS_PER_COUNT (3.3f / 4096.0f)

// ADC
float adc_to_voltage(uint16_t raw) { 
    return raw * VOLTS_PER_COUNT; 
}

float read_cpu_temp(void) {
    adc_select_input(4); // 4 is the built-in temp sensor
    uint16_t raw = adc_read();
    float voltage = adc_to_voltage(raw);
    return 27.0f - (voltage - 0.706f) / 0.001721f;
}

// LED
void led_init(void) {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

void led_on(void) { 
    gpio_put(PICO_DEFAULT_LED_PIN, 1); 
}

void led_off(void) { 
    gpio_put(PICO_DEFAULT_LED_PIN, 0); 
}

void led_toggle(void) {
  gpio_put(PICO_DEFAULT_LED_PIN, !gpio_get(PICO_DEFAULT_LED_PIN));
}

// timing
uint32_t millis(void) { 
    return to_ms_since_boot(get_absolute_time()); 
}
