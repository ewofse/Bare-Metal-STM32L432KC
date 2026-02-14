#include "led.h"
#include "usart.h"
#include "interrupt.h"
#include <stdbool.h>

#define USART_BAUD_RATE 115200

void main(void) {
    disable_irq();

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

    enable_irq();

    while (true) {
        wait_for_interrupt();

        char data;

        if ( usart_getchar(USART2, &data) ) {
            usart_putchar(USART2, data);
            toggle_led();
        }
    }
}

