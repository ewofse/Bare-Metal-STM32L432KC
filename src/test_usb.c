#include "usb.h"
#include "interrupt.h"
#include <stdbool.h>

void main(void) {
    disable_irq();

    configure_usb();

    enable_irq();

    while (true) {
        char data;

        if ( usb_getchar(&data) ) {
            usb_putchar(data);
        }
    }
}

