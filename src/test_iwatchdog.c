#include "watchdog.h"
#include "led.h"
#include "interrupt.h"
#include <stdint.h>
#include <stdbool.h>

void flash_led_blocking(void);

void main(void) {
    disable_irq();

    configure_led();
    configure_independent_watchdog();

    enable_irq();

    while (true) {
        flash_led_blocking();

        feed_the_independent_watchdog();
    }
}

void flash_led_blocking(void) {
    static enum {
        ON,
        OFF
    } state;

    static uint32_t cntr;
    static uint8_t num_loops;

    cntr = (cntr == 199999) ? 0 : cntr + 1;

    switch (state) {
        case (ON):
            if (cntr >= 50000) {
                state = OFF;
                turn_on_led();
            }

            break;

        case (OFF):
            if (cntr >= 199999) {
                state = ON;
                turn_off_led();

                num_loops++;
            }

            break;

        default:
            state = OFF;
            break;
    };

    if (num_loops >= 5) {
        while (true);
    }
}

