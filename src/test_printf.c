#include "systick.h"
#include "usart.h"
#include "interrupt.h"
#include <printf.h>
#include <stdint.h>
#include <stdbool.h>

#define USART_BAUD_RATE 115200

int (* _stdout_putchar)(char c);

void printf_periodic(void);

void main(void) {
    disable_irq();

    configure_systick();

    register_systick_callback(printf_periodic);

    usart_config_t usart2_config = {
        .baud_rate = USART_BAUD_RATE,
        .rx_pin = USART2_RX_PIN_PA15,
        .tx_pin = USART2_TX_PIN_PA2,
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

    _stdout_putchar = usart_putchar_stdout;

    while (true) {
        wait_for_interrupt();
    }
}

void printf_periodic(void) {
    static uint16_t cntr;

    cntr = (cntr == 1000) ? 0 : cntr + 1;

    if (cntr == 1000) {
        printf("Hello World\r\n");
    }
}

