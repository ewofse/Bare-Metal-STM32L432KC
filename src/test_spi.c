#include "led.h"
#include "spi.h"
#include "gpio.h"
#include "systick.h"
#include "interrupt.h"
#include <stdbool.h>

void send_spi_data_1hz(void);

_Bool send_data;

void main(void) {
	disable_irq();

	configure_systick();	

	register_systick_callback(send_spi_data_1hz);

	configure_led();

	spi_nss_pin_t nss_pin = {
		.port = GPIOA,
		.pin = GPIO_PIN_3
	};
	
	// Using SPI loopback mode to receive sent data
	spi_config_t spi1_config = {
		.nss_pin = nss_pin,
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

	while (true) {
		uint8_t len = 3;
		uint8_t returned_data[3];

		wait_for_interrupt();	
	
		if (send_data) {
			send_data = false;

			uint8_t data[3] = {0x12, 0x34, 0x56};

			spi_write(&spi1_handler, data, len);
		}

		if ( spi_read(&spi1_handler, returned_data, len) ) {
			if (
				returned_data[0] == 0x12 && \
				returned_data[1] == 0x34 && \
				returned_data[2] == 0x56
			) {
				toggle_led();
			}
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

