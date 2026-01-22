#include "usart.h"
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

static void ( *callback[NUM_USART_PERIPHERALS][NUM_USART_CALLBACKS] )(void);
static uint32_t num_callbacks[NUM_USART_PERIPHERALS];

static cbuffer_t usart_rx_fifo[NUM_USART_PERIPHERALS];
static cbuffer_t usart_tx_fifo[NUM_USART_PERIPHERALS];

static void write_tx_data(usart_t * regs);
static void read_rx_data(usart_t * regs);

/* Output TX FIFO data if there is no outgoing data */

static void write_tx_data(usart_t * regs) {
    uint8_t index = (regs == USART1) ? 0 : 1;

    uint8_t data;

    if ( cbuffer_read( &usart_tx_fifo[index], &data ) ) {
        regs->TDR = data;
    }

    if ( cbuffer_empty( &usart_tx_fifo[index] ) ) {
        regs->CR1 &= ~USART_CR1_TXEIE_MASK;
    }
}

/* Read incoming RX data and place into RX FIFO */

static void read_rx_data(usart_t * regs) {
    uint8_t index = (regs == USART1) ? 0 : 1;

    uint8_t data = (uint8_t) regs->RDR;
    cbuffer_write( &usart_rx_fifo[index], data );
}

/* Setup the USART */

void configure_usart(usart_handle_t * handler) {
    usart_t * usart = handler->regs;
    usart_config_t opts = handler->opts;

    /* Clock enable, IRQ, and pin setup */

    if (usart == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN(1);

        /* IRQ enable and priority */

        NVIC->ISER1 = NVIC_ISER_SETENA(1, USART1_IRQ - 32);

        NVIC->IPR9 = 
            (NVIC->IPR9 & ~NVIC_IPR9_PRI_37_MASK) 
          | NVIC_IPR9_PRI_37(USART1_IRQ_PRI);
    } else {
        RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN(1);

        /* IRQ enable and priority */

        NVIC->ISER1 = NVIC_ISER_SETENA(1, USART2_IRQ - 32);

        NVIC->IPR9 = 
            (NVIC->IPR9 & ~NVIC_IPR9_PRI_38_MASK) 
          | NVIC_IPR9_PRI_38(USART2_IRQ_PRI);

    }

    /* Pin configurations */
    
    // USART1 can be on either ports A or B, USART2 is only A
    if (opts.rx_pin == USART_RX_PIN_PB7 && opts.tx_pin == USART_TX_PIN_PB6) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);
    } else if (opts.rx_pin == USART_RX_PIN_PB7 
            || opts.tx_pin == USART_TX_PIN_PB6) {
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

    switch (opts.rx_pin) {
        case USART_RX_PIN_PA3:
            GPIOA->MODER &= ~GPIO_MODER_MODE3_MASK;
            GPIOA->MODER |= GPIO_MODER_MODE3(2);

            GPIOA->AFR[0] &= ~GPIO_AFR_AFSEL3_MASK;
            GPIOA->AFR[0] |= GPIO_AFR_AFSEL3(7);

            break;

        case USART_RX_PIN_PA10:
            GPIOA->MODER &= ~GPIO_MODER_MODE10_MASK;
            GPIOA->MODER |= GPIO_MODER_MODE10(2);

            GPIOA->AFR[0] &= ~GPIO_AFR_AFSEL10_MASK;
            GPIOA->AFR[0] |= GPIO_AFR_AFSEL10(7);

            break;

        case USART_RX_PIN_PA15:
            GPIOA->MODER &= ~GPIO_MODER_MODE15_MASK;
            GPIOA->MODER |= GPIO_MODER_MODE15(2);

            GPIOA->AFR[1] &= ~GPIO_AFR_AFSEL15_MASK;
            GPIOA->AFR[1] |= GPIO_AFR_AFSEL15(3);

            break;

        case USART_RX_PIN_PB7:
            GPIOB->MODER &= ~GPIO_MODER_MODE7_MASK;
            GPIOB->MODER |= GPIO_MODER_MODE7(2);

            GPIOB->AFR[0] &= ~GPIO_AFR_AFSEL7_MASK;
            GPIOB->AFR[0] |= GPIO_AFR_AFSEL7(7);

            break;

        case USART_RX_PIN_NONE:
            usart->CR1 &= ~(USART_CR1_RE_MASK | USART_CR1_RXNEIE_MASK);
            
            break;
    };

    /* TX pin selection */

    switch (opts.tx_pin) {
        case USART_TX_PIN_PA2:
            GPIOA->MODER &= ~GPIO_MODER_MODE2_MASK;
            GPIOA->MODER |= GPIO_MODER_MODE2(2);

            GPIOA->AFR[0] &= ~GPIO_AFR_AFSEL2_MASK;
            GPIOA->AFR[0] |= GPIO_AFR_AFSEL2(7);

            break;

        case USART_TX_PIN_PA9:
            GPIOA->MODER &= ~GPIO_MODER_MODE9_MASK;
            GPIOA->MODER |= GPIO_MODER_MODE9(2);

            GPIOA->AFR[1] &= ~GPIO_AFR_AFSEL9_MASK;
            GPIOA->AFR[1] |= GPIO_AFR_AFSEL9(7);

            break;

        case USART_TX_PIN_PB6:
            GPIOB->MODER &= ~GPIO_MODER_MODE6_MASK;
            GPIOB->MODER |= GPIO_MODER_MODE6(2);

            GPIOB->AFR[0] &= ~GPIO_AFR_AFSEL6_MASK;
            GPIOB->AFR[0] |= GPIO_AFR_AFSEL6(7);
            
            break;

        case USART_TX_PIN_NONE:
            usart->CR1 &= ~USART_CR1_TE_MASK;

            break;
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

    usart->CR1 |= USART_CR1_UE(1);

    return;
}

/* Read a character from the USART RX FIFO */

_Bool usart_getchar(usart_t * regs, char * c) {
    uint8_t index = (regs == USART1) ? 0 : 1;

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

_Bool usart_putchar(usart_t * regs, char c) {
    uint8_t index = (regs == USART1) ? 0 : 1;

    if ( cbuffer_full( &usart_tx_fifo[index] ) ) {
        return false;
    }

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    cbuffer_write( &usart_tx_fifo[index], (uint8_t) c );

    set_primask(primask);

    regs->CR1 |= USART_CR1_TXEIE(1);

    return true;
}

/* Add a callback function to IRQ */

_Bool register_usart_callback( usart_t * regs, void (*cb)(void) ) {
    uint8_t index = (regs == USART1) ? 0 : 1;

    if ( num_callbacks[index] == NUM_USART_CALLBACKS ) {
        return false;
    }
    
    callback[index][ num_callbacks[index]++ ] = cb;
    
    return true;
}

/* USART1 ISR */

void __attribute__( (interrupt) ) USART1_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR1 = NVIC_ICPR_CLRPEND(1, USART1_IRQ - 32);

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
    // Clear pending IRQ
    NVIC->ICPR1 = NVIC_ICPR_CLRPEND(1, USART2_IRQ - 32);

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

