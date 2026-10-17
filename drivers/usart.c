#include "usart.h"
#include "gpio.h"
#include "interrupt.h"
#include <m4/nvic.h>
#include <stm32l432kc/usart.h>
#include <stm32l432kc/rcc.h>
#include <stm32l432kc/gpio.h>
#include <util/cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#define NUM_USART_PERIPHERALS 2

#ifndef NUM_USART_CALLBACKS
#define NUM_USART_CALLBACKS 5
#endif

#define USART1_IRQ 37
#define USART1_IRQ_PRI 15 
#define USART2_IRQ 38
#define USART2_IRQ_PRI 15

#define NUM_RX_PINS 4
#define NUM_TX_PINS 3 

uint8_t const rx_pin_LUT[NUM_RX_PINS] = {
	GPIO_PIN_10,
	GPIO_PIN_7,
	GPIO_PIN_3,
	GPIO_PIN_15
};

uint8_t const tx_pin_LUT[NUM_TX_PINS] = {
	GPIO_PIN_9,
	GPIO_PIN_6,
	GPIO_PIN_2
};

static void ( *callback[NUM_USART_PERIPHERALS][NUM_USART_CALLBACKS] )(void);
static uint32_t num_callbacks[NUM_USART_PERIPHERALS];

static cbuffer_t usart_rx_fifo[NUM_USART_PERIPHERALS];
static cbuffer_t usart_tx_fifo[NUM_USART_PERIPHERALS];

static void read_rx_data(usart_t * regs);
static void write_tx_data(usart_t * regs);

/* Read incoming RX data and place into RX FIFO */

static void read_rx_data(usart_t * regs) {
    uint8_t index = regs == USART2;

    uint8_t data = (uint8_t) regs->RDR;
    cbuffer_write( &usart_rx_fifo[index], data );
}

/* Output TX FIFO data if there is no outgoing data */

static void write_tx_data(usart_t * regs) {
    uint8_t index = regs == USART2;

    uint8_t data;

    if ( cbuffer_read( &usart_tx_fifo[index], &data ) ) {
        regs->TDR = data;
    }

    if ( cbuffer_empty( &usart_tx_fifo[index] ) ) {
        regs->CR1 &= ~USART_CR1_TXEIE_MASK;
    }
}

/* Setup the USART */

void configure_usart(usart_handle_t * handler) {
    usart_t * usart = handler->regs;
    usart_config_t opts = handler->opts;

    /* Clock enable, IRQ, and pin setup */

    if (usart == USART1) {
        RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_MASK;
        RCC->CCIPR |= RCC_CCIPR_USART1SEL(0);
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN(1);

        /* IRQ enable and priority */

        NVIC->ISER[1] = NVIC_ISER_SETENA(1, USART1_IRQ - 32);

        NVIC->IPR[9] = 
            (NVIC->IPR[9] & ~NVIC_IPR9_PRI_37_MASK) 
          | NVIC_IPR9_PRI_37(USART1_IRQ_PRI);
    } else {
        RCC->CCIPR &= ~RCC_CCIPR_USART2SEL_MASK;
        RCC->CCIPR |= RCC_CCIPR_USART2SEL(0);
        RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN(1);

        /* IRQ enable and priority */

        NVIC->ISER[1] = NVIC_ISER_SETENA(1, USART2_IRQ - 32);

        NVIC->IPR[9] = 
            (NVIC->IPR[9] & ~NVIC_IPR9_PRI_38_MASK) 
          | NVIC_IPR9_PRI_38(USART2_IRQ_PRI);
    }

    /* Pin configurations */
    
    // USART1 can be on either ports A or B, USART2 is only A
    if (opts.rx_pin == USART1_RX_PIN_PB7 && opts.tx_pin == USART1_TX_PIN_PB6) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);
    } else if (opts.rx_pin == USART1_RX_PIN_PB7 
            || opts.tx_pin == USART1_TX_PIN_PB6) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN(1);
    } else {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN(1);
    }

    usart->CR1 |= 
          USART_CR1_RXNEIE(1) 
        | USART_CR1_TE(1) 
        | USART_CR1_RE(1);

	/* RX pin selection */

	if (opts.rx_pin != USART_RX_PIN_NONE) {
		gpio_t * gpio = (opts.rx_pin != USART1_RX_PIN_PB7) ? GPIOA : GPIOB;
		uint8_t af_index = opts.rx_pin == USART1_RX_PIN_PA10 ||
						   opts.rx_pin == USART2_RX_PIN_PA15;
		uint8_t pin = rx_pin_LUT[opts.rx_pin];
        uint8_t af = (opts.rx_pin == USART2_RX_PIN_PA15) ? \
            GPIO_AFSEL_AF3 : GPIO_AFSEL_AF7;

		gpio->MODER &= ~GPIO_MODER_MODE_MASK(pin);
		gpio->MODER |= GPIO_MODER_MODE(GPIO_MODE_ALTERNATE, pin);
		gpio->AFR[af_index] &= ~GPIO_AFR_AFSEL_MASK(pin);
		gpio->AFR[af_index] |= GPIO_AFR_AFSEL(af, pin);
	} else {
		usart->CR1 &= ~(USART_CR1_RE_MASK | USART_CR1_RXNEIE_MASK);
	}

	/* TX pin selection */

	if (opts.tx_pin != USART_TX_PIN_NONE) {
		gpio_t * gpio = (opts.tx_pin != USART1_TX_PIN_PB6) ? GPIOA : GPIOB;
		uint8_t af_index = opts.tx_pin == USART1_TX_PIN_PA9;
		uint8_t pin = tx_pin_LUT[opts.tx_pin];
        uint8_t af = GPIO_AFSEL_AF7;

		gpio->MODER &= ~GPIO_MODER_MODE_MASK(pin);
		gpio->MODER |= GPIO_MODER_MODE(GPIO_MODE_ALTERNATE, pin);
		gpio->AFR[af_index] &= ~GPIO_AFR_AFSEL_MASK(pin);
		gpio->AFR[af_index] |= GPIO_AFR_AFSEL(af, pin);
	} else {
		usart->CR1 &= ~USART_CR1_TE_MASK;
	}

    /* Packet setup */

    usart->CR1 &= ~(USART_CR1_M1_MASK | USART_CR1_M0_MASK);
    usart->CR1 |= 
          USART_CR1_M1(opts.word >> 1)
        | USART_CR1_M0(opts.word & 1);

    usart->CR2 &= ~USART_CR2_STOP_MASK;
    usart->CR2 |= USART_CR2_STOP(opts.stop);

    usart->CR1 &= ~USART_CR1_OVER8_MASK;

    // Baud rate needs the system clock to calculate USART divider 
    usart->BRR = (uint32_t) (64000000 / opts.baud_rate);

    /* DMA options */

    usart->CR3 &= ~(USART_CR3_DMAT_MASK | USART_CR3_DMAR_MASK);
    usart->CR3 |= 
          USART_CR3_DMAT(opts.dma >> 1) 
        | USART_CR3_DMAR(opts.dma & 1);

    usart->CR1 |= USART_CR1_UE(1);

    return;
}

/* Read a character from the USART RX FIFO */

_Bool usart_getchar(usart_handle_t * handler, char * c) {
    usart_t * usart = handler->regs;

    uint8_t index = usart == USART2;

    if ( cbuffer_empty( &usart_rx_fifo[index] ) ) {
        return false;
    }

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    cbuffer_read( &usart_rx_fifo[index], (uint8_t *) c );

    set_primask(primask);

    return true;
}

/* Write a character to USART TX FIFO */

_Bool usart_putchar(usart_handle_t * handler, char c) {
    usart_t * usart = handler->regs;

    uint8_t index = usart == USART2;

    if ( cbuffer_full( &usart_tx_fifo[index] ) ) {
        return false;
    }

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    cbuffer_write( &usart_tx_fifo[index], (uint8_t) c );

    set_primask(primask);

    usart->CR1 |= USART_CR1_TXEIE(1);

    return true;
}

/* Add a callback function to IRQ */

_Bool register_usart_callback( usart_handle_t * handler, void (*cb)(void) ) {
    usart_t * usart = handler->regs;

    uint8_t index = usart == USART2;

    if ( num_callbacks[index] == NUM_USART_CALLBACKS ) {
        return false;
    }
    
    callback[index][ num_callbacks[index]++ ] = cb;
    
    return true;
}

/* USART1 ISR */

void __attribute__( (interrupt) ) USART1_Handler(void) {
    if (USART1->ISR & USART_ISR_RXNE_MASK) {
        read_rx_data(USART1);
    }
    
    if (USART1->ISR & USART_ISR_TXE_MASK 
        && USART1->CR1 & USART_CR1_TXEIE_MASK) {
        write_tx_data(USART1);
    }

    for (uint32_t i = 0; i < num_callbacks[0]; i++) {
        callback[0][i]();
    }
}

/* USART2 ISR */

void __attribute__( (interrupt) ) USART2_Handler(void) {
    if (USART2->ISR & USART_ISR_RXNE_MASK) {
        read_rx_data(USART2);
    }
    
    if (USART2->ISR & USART_ISR_TXE_MASK 
        && USART2->CR1 & USART_CR1_TXEIE_MASK) {
        write_tx_data(USART2);
    }

    for (uint32_t i = 0; i < num_callbacks[1]; i++) {
        callback[1][i]();
    }
}

/* STDOUT USART for printf */

int usart_getchar_stdin(char * c) {
    usart_handle_t handler = {
        .opts = {0},
        .regs = USART2
    };

    return usart_getchar(&handler, c);
}

int usart_putchar_stdout(char c) {
    while ( !(USART2->ISR & USART_ISR_TXE_MASK) ); 

    USART2->TDR = c;

    return 1;
}

