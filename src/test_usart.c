#include "systick.h"
#include "led.h"
#include "usart.h"
#include "interrupt.h"

void print_char_1s(void);

void main(void) {

    disable_irq();

    configure_systick();
    configure_led();

    usart_config_t usart2_config = {
        .baud_rate = 115200,
        .rx_pin = USART_RX_PIN_PA15,
        .tx_pin = USART_TX_PIN_PA2,
        .mode = USART_MODE_RXTX,
        .word = USART_WORD_8N1,
        .stop = USART_STOP_ONE 
    };

    usart_handle_t usart2_handle = {
        .regs = USART2,
        .opts = usart2_config 
    };

    configure_usart(&usart2_handle);

    register_systick_callback(print_char_1s);

    enable_irq();

    while (1) {
        wait_for_interrupt();

        char data;

        if ( usart_getchar(USART2, &data) && data == 'W' ) {
            data = 0;
            toggle_led();
        }
    }
}

void print_char_1s(void) {
    if ( !( get_system_time() % 1000 ) ) {
        usart_putchar(USART2, 'E');
    }
}

