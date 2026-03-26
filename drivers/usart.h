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

typedef enum {
    USART_DMA_NONE,
    USART_DMA_RX,
    USART_DMA_TX,
    USART_DMA_RXTX
} usart_dma;

typedef USART_REG_BLOCKS volatile usart_t;

typedef struct {
    uint32_t baud_rate;
    usart_rx_pin rx_pin;
    usart_tx_pin tx_pin;
    usart_mode mode;
    usart_word word;
    usart_stop stop;
    usart_dma dma;
} usart_config_t;

typedef struct {
    usart_t * regs;
    usart_config_t opts;
} usart_handle_t;

void configure_usart(usart_handle_t * handler);
_Bool usart_getchar(usart_handle_t * handler, char * c);
_Bool usart_putchar(usart_handle_t * handler, char c);
_Bool register_usart_callback( usart_handle_t * handler, void (*cb)(void) );

/* STDOUT compliant */

int usart_getchar_stdin(char * c);
int usart_putchar_stdout(char c);

#endif

