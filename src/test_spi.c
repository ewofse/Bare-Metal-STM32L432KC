#include "spi.h"
#include "gpio.h"
#include "usart.h"
#include "systick.h"
#include "interrupt.h"
#include <printf.h>
#include <stdbool.h>
#include <stdint.h>

#define USART_BAUD_RATE 115200

int (* _stdout_putchar)(char c);

void send_spi_data_1hz(void);

_Bool volatile send_data;

void main(void) {
	disable_irq();

	configure_systick();	

	register_systick_callback(send_spi_data_1hz);

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

	spi_nss_pin_t spi3_nss_pin = {
		.port = SPI_NSS_PIN_NONE,
	};	

	spi_config_t spi3_config = {
		.nss_pin = spi3_nss_pin,
		.miso_pin = SPI3_MISO_PIN_PB4,
		.mosi_pin = SPI3_MOSI_PIN_PB5,
		.sck_pin = SPI3_SCK_PIN_PB3,
		.device_type = SPI_SLAVE,
		.dir = SPI_DIR_FULL_DUPLEX,
		.mode = SPI_MODE_0,
		.frame_format = SPI_MOTOROLA,
		.data_size = SPI_DATA_8_BIT,
		.baud_rate = SPI_BAUD_FCLK_64,
		.data_dir = SPI_MSB_FIRST,
		.dma = SPI_DMA_NONE
	};

	spi_handle_t spi3_handler = {
		.regs = SPI3,
		.opts = spi3_config
	};	

	configure_spi(&spi3_handler);

	spi_nss_pin_t spi1_nss_pin = {
		.port = SPI_NSS_PIN_NONE,
	};
	
	spi_config_t spi1_config = {
		.nss_pin = spi1_nss_pin,
		.miso_pin = SPI1_MISO_PIN_PA6,
		.mosi_pin = SPI1_MOSI_PIN_PA7,
		.sck_pin = SPI1_SCK_PIN_PA1,
		.device_type = SPI_MASTER,
		.dir = SPI_DIR_FULL_DUPLEX,
		.mode = SPI_MODE_0,
		.frame_format = SPI_MOTOROLA,
		.data_size = SPI_DATA_8_BIT,
		.baud_rate = SPI_BAUD_FCLK_64,
		.data_dir = SPI_MSB_FIRST,
		.dma = SPI_DMA_NONE
	};

	spi_handle_t spi1_handler = {
		.regs = SPI1,
		.opts = spi1_config	
	};

	configure_spi(&spi1_handler);

	enable_irq();

    _stdout_putchar = usart_putchar_stdout;

	while (true) {
		uint8_t len = 3;
		uint8_t data[3] = {0x12, 0x34, 0x56};
		uint8_t returned_data[3];

		wait_for_interrupt();	

		if (send_data) {
			send_data = false;
			spi_write(&spi1_handler, data, len);
		}

		if ( spi_read(&spi3_handler, returned_data, len) ) {
			printf( "%x\r\n", returned_data[0] );
			printf( "%x\r\n", returned_data[1] );
			printf( "%x\r\n", returned_data[2] );
		}
	}
}

void send_spi_data_1hz(void) {
	static uint16_t cnt;

	cnt = (cnt == 999) ? 0 : cnt + 1;

	if (cnt == 0) {
		send_data = true;		
	}
}

