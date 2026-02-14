#include "watchdog.h"
#include "led.h"
#include "interrupt.h"
#include <stdint.h>
#include <stdbool.h>

void flash_led_blocking(void);

void main(void) {
    while (true) {
        continue;
    }
}

void flash_led_blocking(void) {
    return;
}

