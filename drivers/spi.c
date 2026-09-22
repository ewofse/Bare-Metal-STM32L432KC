#include "spi.h"
#include "interrupt.h"
#include <m4/nvic.h>
#include <stm32l432kc/usart.h>
#include <stm32l432kc/rcc.h>
#include <stm32l432kc/gpio.h>
#include <util/cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#define NUM_SPI_PERIPHERALS 2

#ifndef NUM_SPI_CALLBACKS
#define NUM_SPI_CALLBACKS 5
#endif

#define SPI1_IRQ
#define SPI1_IRQ_PRI 15
#define SPI3_IRQ
#define SPI3_IRQ_PRI 15

static void ( *callback[NUM_SPI_PERIPHERALS][NUM_SPI_CALLBACKS] )(void);
static uint32_t num_callbacks[NUM_SPI_PERIPHERALS];

static cbuffer_t spi_rx_fifo[NUM_SPI_PERIPHERALS];
static cbuffer_t spi_tx_fifo[NUM_SPI_PERIPHERALS];

static void assert_nss(spi_handle_t * handler);
static void deassert_nss(spi_handle_t * handler);

static void write_tx_data(spi_t * regs);
static void read_rx_data(spi_t * regs);

/* Set CS low to begin transfer */

static void assert_nss(spi_handle_t * handler) {
    ;
}

/* Set CS high to end transfer */

static void deassert_nss(spi_handle_t * handler) {
    ;
}

/* Output TX FIFO data if there is no outgoing data */

static void write_tx_data(spi_t * regs) {
    uint8_t index = regs == SPI1;

    uint8_t data;

    if ( cbuffer_read( &spi_tx_fifo[index], &data ) ) {
        regs->DR = data;
    }

    if ( cbuffer_empty( &spi_tx_fifo[index] ) ) {
        regs->CR2 &= ~SPI_CR2_TXEIE_MASK;
    }
}

/* Read incoming RX data and place into RX FIFO */

static void read_rx_data(spi_t * regs) {
    uint8_t index = regs == SPI1;

    uint8_t data = (uint8_t) regs->DR;
    cbuffer_write( &spi_rx_fifo[index], data );
}

/* Setup SPI peripheral */

void configure_spi(spi_handle_t * handler) {
    spi_t * spi = handler->regs;
    spi_config_t opts = handler->opts;

    // Clock setup
    // IRQ enable and priority
    // Pin setup

    // SPI interrupt enable
    
    // SPI options - device type, mode, dir, baud rate, frame format, data dir, data size

    // DMA options

    // Enable peripheral
}

/* Read a payload from SPI RX FIFO */

_Bool spi_read(spi_handle_t * handler, uint8_t * buf, uint32_t len) {
    spi_t * spi = handler->regs;

    uint8_t index = spi == SPI1;

    if ( cbuffer_empty( &spi_rx_fifo[index] ) ) {
        return false;
    }

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    for (uint32_t i = 0; i < len; i++) {
        cbuffer_read( &spi_rx_fifo[index], buf++ );
    }

    set_primask(primask);

    if (spi->CR1 & SPI_CR1_MSTR_MASK && spi->CR1 & SPI_CR1_SSM_MASK) {
       deassert_nss(handler); 
    }

    return true;
}

/* Write a payload to SPI TX FIFO */

_Bool spi_write(spi_handle_t * handler, uint8_t const * data, uint32_t len) {
    spi_t * spi = handler->regs;

    uint8_t index = spi == SPI1;

    if ( cbuffer_full( &spi_tx_fifo[index] ) ) {
        return false;
    }

    if (spi->CR1 & SPI_CR1_MSTR_MASK && spi->CR1 & SPI_CR1_SSM_MASK) {
       assert_nss(handler); 
    }

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    for (uint32_t i = 0; i < len; i++) {
        cbuffer_write( &spi_tx_fifo[index], *(data++) );
    }

    set_primask(primask);

    spi->CR2 |= SPI_CR2_TXEIE(1);

    return true;
}

/* Add a callback function to IRQ */

_Bool register_spi_callback( spi_handle_t * handler, void (*cb)(void) ) {
    spi_t * spi = handler->regs;

    uint8_t index = spi == SPI1;

    if ( num_callbacks[index] == NUM_SPI_CALLBACKS ) {
        return false;
    }

    callback[index][ num_callbacks[index]++ ] = cb;

    return true;
}

/* SPI1 ISR */

void __attribute__( (interrupt) ) SPI1_Handler(void) {
    if (SPI1->SR & SPI_SR_RXNE_MASK) {
        read_rx_data(SPI1);
    }
    
    if (SPI1->SR & SPI_SR_TXE_MASK 
        && SPI1->CR2 & SPI_CR2_TXEIE_MASK) {
        write_tx_data(SPI1);
    }

    for (uint32_t i = 0; i < num_callbacks[0]; i++) {
        callback[0][i]();
    }
}

/* SPI3 ISR */

void __attribute__( (interrupt) ) SPI3_Handler(void) {
    if (SPI3->SR & SPI_SR_RXNE_MASK) {
        read_rx_data(SPI3);
    }
    
    if (SPI3->SR & SPI_SR_TXE_MASK 
        && SPI3->CR2 & SPI_CR2_TXEIE_MASK) {
        write_tx_data(SPI3);
    }

    for (uint32_t i = 0; i < num_callbacks[1]; i++) {
        callback[1][i]();
    }
}

