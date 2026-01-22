#ifndef USART_H
#define USART_H

#include <stm32l432kc/usart.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum { 
    USART_RX_PIN_NONE,
    USART_RX_PIN_PA3,
    USART_RX_PIN_PA10,
    USART_RX_PIN_PA15,
    USART_RX_PIN_PB7
} usart_rx_pin;

typedef enum {
    USART_TX_PIN_NONE,
    USART_TX_PIN_PA2,
    USART_TX_PIN_PA9,
    USART_TX_PIN_PB6
} usart_tx_pin;

typedef enum {
    USART_MODE_RX,
    USART_MODE_TX,
    USART_MODE_RXTX
} usart_mode;

typedef enum {
    USART_WORD_8N1,
    USART_WORD_9N1,
    USART_WORD_7N1
} usart_word;

typedef enum {
    USART_STOP_ONE,
    USART_STOP_HALF,
    USART_STOP_TWO,
    USART_STOP_ONEHALF
} usart_stop;

typedef USART_REG_BLOCKS volatile usart_t;

typedef struct {
    uint32_t baud_rate;
    usart_rx_pin rx_pin : 4;
    usart_tx_pin tx_pin : 4;
    usart_mode mode     : 2;
    usart_word word     : 2;
    usart_stop stop     : 2;
} usart_config_t;

typedef struct {
    usart_t * regs;
    usart_config_t opts;
} usart_handle_t;

void configure_usart(usart_handle_t * handler);
_Bool usart_getchar(usart_t * regs, char * c);
_Bool usart_putchar(usart_t * regs, char c);
_Bool register_usart_callback( usart_t * regs, void (*cb)(void) );
uint32_t get_irq_status_for_usart(usart_t * regs);

#endif

