#include "led.h"

void main(void) {
    configure_led();

    while (1) {
        toggle_led();

        for (unsigned volatile i = 0; i < 200000; i++);
    }
}

