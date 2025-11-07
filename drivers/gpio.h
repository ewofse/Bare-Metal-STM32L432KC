#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

_Bool register_gpio_callback( void (*cb)(void), uint8_t pin );
_Bool get_irq_status_for_pin(uint8_t pin);

#endif

