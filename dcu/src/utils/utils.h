// dcu/src/utils/utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

// ADC
void adc_utils_init(void);
float adc_to_voltage(uint16_t raw);
int16_t read_cpu_temp(void); // return CPU temp in celsius

// LED
bool get_led(void);
void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

// timing
uint32_t millis(void);
void reboot(void);
void bootsel(void);

#endif
