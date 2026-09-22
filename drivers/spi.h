#ifndef SPI_H
#define SPI_H

#include <stm32l432kc/spi.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SPI1_MISO_PIN_PA6,
    SPI1_MISO_PIN_PA11,
    SPI_MISO_PIN_PB4,
} spi_miso_pin;

typedef enum {
    SPI1_MOSI_PIN_PA7,
    SPI1_MOSI_PIN_PA12,
    SPI1_MOSI_PIN_PB5,
    SPI3_MOSI_PIN_PB3
} spi_mosi_pin;

typedef enum {
    SPI1_SCK_PIN_PA1,
    SPI1_SCK_PIN_PA5,
    SPI_SCK_PIN_PB3,
} spi_sck_pin;

typedef enum {
    SPI_MODE_UNIDIRECTIONAL,
    SPI_MODE_BIDIRECTIONAL,
    SPI_MODE_RX_ONLY
} spi_dir;

typedef enum {
    SPI_SLAVE,
    SPI_MASTER
} spi_device_type;

typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} spi_mode;

typedef enum {
    SPI_MOTOROLA,
    SPI_TI
} spi_frame_format;

typedef enum {
    SPI_DATA_4_BIT = 3,
    SPI_DATA_5_BIT,
    SPI_DATA_6_BIT,
    SPI_DATA_7_BIT,
    SPI_DATA_8_BIT,
    SPI_DATA_9_BIT,
    SPI_DATA_10_BIT,
    SPI_DATA_11_BIT,
    SPI_DATA_12_BIT,
    SPI_DATA_13_BIT,
    SPI_DATA_14_BIT,
    SPI_DATA_15_BIT,
    SPI_DATA_16_BIT
} spi_data_size;

typedef enum {
    SPI_BAUD_FCLK_2,
    SPI_BAUD_FCLK_4,
    SPI_BAUD_FCLK_8,
    SPI_BAUD_FCLK_16,
    SPI_BAUD_FCLK_32,
    SPI_BAUD_FCLK_64,
    SPI_BAUD_FCLK_128,
    SPI_BAUD_FCLK_256
} spi_baud_rate;

typedef enum {
    SPI_MSB_FIRST,
    SPI_LSB_FIRST
} spi_data_dir;

typedef enum {
    SPI_DMA_NONE,
    SPI_DMA_RX,
    SPI_DMA_TX,
    SPI_DMA_RXTX
} spi_dma;

typedef SPI_REG_BLOCKS volatile spi_t;

// User can either choose SSM mode or not
// SSM mode is manual control of NSS pin through software - any GPIO pin can be used for CS pin on the SPI bus
// SSM disabled is automatic control done by hardware - strict NSS GPIO pin must be used

typedef struct {
    // pin number
    // GPIO port
    // SSM enabled or disabled
    uint8_t gpio_num;
    uint8_t gpio_port;
    _Bool smm;
} spi_nss_pin_t;

typedef struct {
    spi_nss_pin_t nss_pin;
    spi_miso_pin miso_pin;
    spi_mosi_pin mosi_pin;
    spi_sck_pin sck_pin;
    spi_device_type device_type;
    spi_dir dir;
    spi_mode mode;
    spi_frame_format frame_format;
    spi_data_size data_size;
    spi_baud_rate baud_rate;
    spi_data_dir data_dir;
    spi_dma dma;
} spi_config_t;

typedef struct {
    spi_t * regs;
    spi_config_t opts;
} spi_handle_t;

void configure_spi(spi_handle_t * handler);
_Bool spi_read(spi_handle_t * handler, uint8_t * buf, uint32_t len);
_Bool spi_write(spi_handle_t * handler, uint8_t const * buf, uint32_t len);
_Bool register_spi_callback( spi_handle_t * handler, void (*cb)(void) );

#endif

