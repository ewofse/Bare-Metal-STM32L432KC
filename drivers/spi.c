#include "spi.h"
#include "gpio.h"
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

#define SPI1_IRQ 35
#define SPI1_IRQ_PRI 15
#define SPI3_IRQ 51
#define SPI3_IRQ_PRI 15

#define NUM_MISO_PINS 4
#define NUM_MOSI_PINS 4
#define NUM_SCK_PINS 4

uint8_t const miso_pin_LUT[NUM_MISO_PINS] = {
	GPIO_PIN_6,
	GPIO_PIN_11,
	GPIO_PIN_4,
	GPIO_PIN_4
};

uint8_t const mosi_pin_LUT[NUM_MOSI_PINS] = {
	GPIO_PIN_7,
	GPIO_PIN_12,
	GPIO_PIN_5,
	GPIO_PIN_5
};

uint8_t const sck_pin_LUT[NUM_SCK_PINS] = {
	GPIO_PIN_1,
	GPIO_PIN_5,
	GPIO_PIN_3,
	GPIO_PIN_3
};

static void ( *callback[NUM_SPI_PERIPHERALS][NUM_SPI_CALLBACKS] )(void);
static uint32_t num_callbacks[NUM_SPI_PERIPHERALS];

static cbuffer_t spi_rx_fifo[NUM_SPI_PERIPHERALS];
static cbuffer_t spi_tx_fifo[NUM_SPI_PERIPHERALS];

static void write_tx_data(spi_t * regs);
static void read_rx_data(spi_t * regs);

static gpio_handle_t nss_gpio_handler;

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


    /* Clock enable, IRQ, and pin setup */

    if (spi == SPI1) {
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN(1);

        /* IRQ enable and priority */

        NVIC->ISER[1] = NVIC_ISER_SETENA(1, SPI1_IRQ - 32);

        NVIC->IPR[8] = 
            (NVIC->IPR[8] & ~NVIC_IPR8_PRI_35_MASK) 
          | NVIC_IPR8_PRI_35(SPI1_IRQ_PRI);
    } else {
        RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN(1);

        /* IRQ enable and priority */

        NVIC->ISER[1] = NVIC_ISER_SETENA(1, SPI3_IRQ - 32);

        NVIC->IPR[12] = 
            (NVIC->IPR[12] & ~NVIC_IPR12_PRI_51_MASK) 
          | NVIC_IPR12_PRI_51(SPI3_IRQ_PRI);
    }

    /* Pin configurations */
    
    // SPI1 can be either on ports A or B, SPI3 is only B 

	_Bool spi1_port_b = \
		opts.miso_pin == SPI1_MISO_PIN_PB4 || \
		opts.mosi_pin == SPI1_MOSI_PIN_PB5 || \
		opts.sck_pin == SPI1_SCK_PIN_PB3;

	RCC->AHB2ENR |= 1 << (spi == SPI3 || spi1_port_b);

	uint8_t af = (spi == SPI1) ? GPIO_AFR_AF5 : GPIO_AFR_AF6;

	/* MISO pin selections */

	if (opts.miso_pin != SPI_MISO_PIN_NONE) {
		gpio_t * gpio = (opts.miso_pin >= SPI1_MISO_PIN_PB4) ? GPIOB : GPIOA;
		uint8_t af_index = opts.miso_pin == SPI1_MISO_PIN_PA11;
		uint8_t pin = miso_pin_LUT[opts.miso_pin];

		gpio->MODER &= ~GPIO_MODER_MODE_MASK(pin);
		gpio->MODER |= GPIO_MODER_MODE(GPIO_MODE_ALTERNATE, pin);
		gpio->AFR[af_index] &= ~GPIO_AFR_AFSEL_MASK(pin);
		gpio->AFR[af_index] |= GPIO_AFR_AFSEL(af, pin);
	}

	/* MOSI pin selections */

	if (opts.mosi_pin != SPI_MOSI_PIN_NONE) {
		gpio_t * gpio = (opts.mosi_pin >= SPI1_MOSI_PIN_PB5) ? GPIOB : GPIOA;
		uint8_t af_index = opts.mosi_pin == SPI1_MOSI_PIN_PA12;
		uint8_t pin = mosi_pin_LUT[opts.mosi_pin];

		gpio->MODER &= ~GPIO_MODER_MODE_MASK(pin);
		gpio->MODER |= GPIO_MODER_MODE(GPIO_MODE_ALTERNATE, pin);
		gpio->AFR[af_index] &= ~GPIO_AFR_AFSEL_MASK(pin);
		gpio->AFR[af_index] |= GPIO_AFR_AFSEL(af, pin);
	}

	/* SCK pin selections */

	gpio_t * sck_gpio = (opts.sck_pin >= SPI1_SCK_PIN_PB3) ? GPIOA : GPIOB;
	uint8_t sck_pin = sck_pin_LUT[opts.sck_pin];
	uint8_t sck_af_index = 0;

	sck_gpio->MODER &= ~GPIO_MODER_MODE_MASK(sck_pin);
	sck_gpio->MODER |= GPIO_MODER_MODE(GPIO_MODE_ALTERNATE, sck_pin);
	sck_gpio->AFR[sck_af_index] &= ~GPIO_AFR_AFSEL_MASK(sck_pin);
	sck_gpio->AFR[sck_af_index] |= GPIO_AFR_AFSEL(af, sck_pin);

	/* NSS pin selection */

	nss_gpio_handler.regs = opts.nss_pin.port;
	nss_gpio_handler.opts.pin = opts.nss_pin.pin;
	nss_gpio_handler.opts.mode = opts.device_type == SPI_SLAVE;
	nss_gpio_handler.opts.pupd = GPIO_PUPD_NONE;

	if (nss_gpio_handler.opts.mode == GPIO_MODE_OUTPUT) {
		nss_gpio_handler.opts.otype = GPIO_OTYPE_PUSHPULL;
		nss_gpio_handler.opts.ospeed = GPIO_OSPEED_HIGH;
	}

	configure_gpio(&nss_gpio_handler);

	/* SPI options */
	
	// SPI mode and configurations
	spi->CR1 = 
		  SPI_CR1_BIDIMODE( ~(opts.dir >> 1) & (opts.dir & 1) )
		| SPI_CR1_BIDIOE(0)
		| SPI_CR1_CRCEN(0)
		| SPI_CR1_CRCNEXT(0)
		| SPI_CR1_CRCL(0)
		| SPI_CR1_RXONLY( (opts.dir >> 1) & (opts.dir & 1) )
		| SPI_CR1_SSM(1)
		| SPI_CR1_SSI(1)
		| SPI_CR1_LSBFIRST(opts.data_dir)
		| SPI_CR1_SPE(0)
		| SPI_CR1_BR(opts.baud_rate)
		| SPI_CR1_MSTR(opts.device_type)
		| SPI_CR1_CPOL(opts.mode >> 1)
		| SPI_CR1_CPHA(opts.mode & 1);

	// IRQ and DMA enable 
	spi->CR2 = 
		  SPI_CR2_LDMA_TX(0)
		| SPI_CR2_LDMA_RX(0)
		| SPI_CR2_FRXTH(0)
		| SPI_CR2_DS(opts.data_size)
		| SPI_CR2_TXEIE(1)
		| SPI_CR2_RXNEIE(1)
		| SPI_CR2_ERRIE(0)
		| SPI_CR2_FRF(opts.frame_format)
		| SPI_CR2_NSSP(0)
		| SPI_CR2_SSOE(0)
		| SPI_CR2_TXDMAEN(opts.dma >> 1)
		| SPI_CR2_RXDMAEN(opts.dma & 1);

    // Enable peripheral
	spi->CR1 |= SPI_CR1_SPE(1);
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

    if (spi->CR1 & SPI_CR1_MSTR_MASK) {
		spi->CR1 |= SPI_CR1_SSI(1);

		if (nss_gpio_handler.regs != SPI_NSS_PIN_NONE) {
			set_gpio(&nss_gpio_handler);
		}
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

    if (spi->CR1 & SPI_CR1_MSTR_MASK) {
		spi->CR1 &= ~SPI_CR1_SSI_MASK;

		if (nss_gpio_handler.regs != SPI_NSS_PIN_NONE) {
			reset_gpio(&nss_gpio_handler);
		}
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

