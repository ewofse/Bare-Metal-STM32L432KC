#include "systick.h"
#include "led.h"
#include "interrupt.h"
#include <stdbool.h>

void toggle_led_500ms(void);

void main(void) {
    disable_irq();

    configure_systick();
    configure_led();

    register_systick_callback(toggle_led_500ms);
    
    enable_irq();

    while (true) {
        wait_for_interrupt();
    }
}

void toggle_led_500ms(void) {
    if ( !( get_system_time() % 500 ) ) {
        toggle_led();
    }
}

