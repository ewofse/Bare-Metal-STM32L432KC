#include "led.h"
#include "systick.h"
#include <stdbool.h>

void main(void) {
    configure_systick();
    configure_led();

    while (true) {
        while ( !systick_has_fired() );

        toggle_led();
    }
}

