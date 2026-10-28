#include "spi.h"
#include "gpio.h"
#include "usart.h"
#include "systick.h"
#include "interrupt.h"
#include <printf.h>
#include <stdbool.h>
#include <stdint.h>

#define USART_BAUD_RATE 115200
#define SPI_DUMMY_WRITE 0x00

int (* _stdout_putchar)(char c);

void setup_usart(void);

void test_spi_simplex(void);
void test_spi_full_duplex(void);

void send_spi_data_1hz(void);

_Bool volatile send_data;

void main(void) {
	// test_spi_simplex();
	test_spi_full_duplex();
}

void send_spi_data_1hz(void) {
	static uint16_t cnt;

	cnt = (cnt == 999) ? 0 : cnt + 1;

	if (cnt == 0) {
		send_data = true;		
	}
}

void setup_usart(void) {
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

    _stdout_putchar = usart_putchar_stdout;
}

void test_spi_full_duplex(void) {
	disable_irq();

	configure_systick();	
	register_systick_callback(send_spi_data_1hz);

	setup_usart();

	spi_config_t spi3_config = {
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
	
	spi_device_t spi3_device = {
		.bus = &spi3_handler,
		.port = GPIOA,
		.pin = GPIO_PIN_0
	};

	configure_spi(&spi3_handler);
	register_spi_device(&spi3_device);
	
	spi_config_t spi1_config = {
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

	spi_device_t spi1_device = {
		.bus = &spi1_handler,
		.port = GPIOA,
		.pin = GPIO_PIN_1
	};

	configure_spi(&spi1_handler);
	register_spi_device(&spi1_device);

	enable_irq();

	while (true) {
		uint8_t master_read_data[3];
		uint8_t master_write_data[5] = {
			0xCC, 
			0x01, 
			SPI_DUMMY_WRITE,
			SPI_DUMMY_WRITE,
			SPI_DUMMY_WRITE
		};

		uint8_t slave_read_data[2];
		uint8_t slave_write_data[2] = {0xAB, 0xCD};

		wait_for_interrupt();	

		if (!send_data) {
			continue;
		}

		send_data = false;
		spi_write(&spi1_device, master_write_data, 5);

		if ( spi_read(&spi3_device, slave_read_data, 2) ) {
			spi_write(&spi3_device, slave_write_data, 2);
		}

		if ( spi_read(&spi1_device, master_read_data, 3) ) {
			printf( "%x\r\n", master_read_data[0] );
			printf( "%x\r\n", master_read_data[1] );
			printf( "%x\r\n", master_read_data[2] );
		}
	}
}

