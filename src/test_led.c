#include "led.h"
#include <stdbool.h>

void main(void) {
    configure_led();

    while (true) {
        toggle_led();

        for (unsigned volatile i = 0; i < 200000; i++);
    }
}

