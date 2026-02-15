#include "watchdog.h"
#include "systick.h"
#include "usart.h"
#include "led.h"
#include "interrupt.h"
#include <stdint.h>
#include <stdbool.h>

#define USART_BAUD_RATE 115200

void flash_led_blocking(void);
void print_watchdog_warning(void);

void main(void) {
    disable_irq();

    configure_window_watchdog();
    configure_systick();
    configure_led();

    usart_config_t usart2_config = {
        .baud_rate = USART_BAUD_RATE,
        .rx_pin = USART_RX_PIN_PA15,
        .tx_pin = USART_TX_PIN_PA2,
        .mode = USART_MODE_RXTX,
        .word = USART_WORD_8N1,
        .stop = USART_STOP_ONE,
        .dma = USART_DMA_NONE
    };

    usart_handle_t usart2_handle = {
        .regs = USART2,
        .opts = usart2_config 
    };

    configure_usart(&usart2_handle);

    register_systick_callback(flash_led_blocking);
    register_window_watchdog_callback(print_watchdog_warning);

    enable_irq();

    while (true) {
        wait_for_interrupt();

        feed_the_window_watchdog();
    }
}

void flash_led_blocking(void) {
    static enum {
        ON,
        OFF
    } state;

    static uint32_t cntr;
    static uint8_t num_loops;

    cntr = (cntr == 999) ? 0 : cntr + 1;

    switch (state) {
        case (ON):
            if (cntr >= 250) {
                state = OFF;
                turn_off_led();
            }

            break;

        case (OFF):
            if (cntr >= 999) {
                state = ON;
                turn_on_led();

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

void print_watchdog_warning(void) {
    //static char msg[] = "Resetting...\n\r";

    //for (char * p = msg; *p != 0; p++) {
        //usart_putchar(USART2, *p);
    //}
    usart_putchar(USART2, 'a');
}

