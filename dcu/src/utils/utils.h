// dcu/src/utils/utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

// ADC
float adc_to_voltage(uint16_t raw);
float read_cpu_temp(void); // return CPU temp in celsius

// LED
void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

// timing
uint32_t millis(void);

#endif
