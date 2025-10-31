#include "led.h"
#include "systick.h"

void main(void) {
    configure_systick();
    configure_led();

    while (1) {
        while ( !systick_has_fired() );

        toggle_led();
    }
}

