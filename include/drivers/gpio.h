#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define IS_GPIO_PORT(port) ( \
    ( (port) == GPIOA ) || \
    ( (port) == GPIOB ) || \
    ( (port) == GPIOC ) || \
    ( (port) == GPIOH )    \
)

#define IS_GPIO_PIN(pin) ( !(pin) && ( (pin) <= PIN15 ) && !( (pin) & (pin - 1U) ) )

#define IS_GPIO_VALID(port, pin) ( \
    ( ( (port) == GPIOA ) && ( (pin) >= PIN0  && (pin) <= PIN15 ) ) || \
    ( ( (port) == GPIOB ) && ( (pin) >= PIN0  && (pin) <= PIN7  ) ) || \
    ( ( (port) == GPIOC ) && ( (pin) == PIN14 || (pin) == PIN15 ) ) || \
    ( ( (port) == GPIOH ) && ( (pin) == PIN3                    ) )    \
)

#define IS_GPIO_MODE(mode)    ( ( (mode) >= GPIO_MODE_INPUT )     && ( (mode) <= GPIO_MODE_ANALOG      ) )
#define IS_GPIO_OUTPUT(type)  ( ( (type) == GPIO_OTYPE_PUSHPULL ) && ( (type) == GPIO_OTYPE_OPENDRAIN  ) )
#define IS_GPIO_SPEED(speed)  ( ( (speed) >= GPIO_OSPEED_LOW )    && ( (speed) <= GPIO_OSPEED_VERYHIGH ) )
#define IS_GPIO_AF(alternate) ( ( (alternate) >= AF0 )            && ( (alternate) <= AF15             ) )

#define IS_GPIO_VALUE(value) ( ( (value) == GPIO_RESET ) || ( (value) == GPIO_SET ) )

#define IS_GPIO_MASK(mask) ( (mask) && !( (mask) & ~MASK_GPIO_LOCATIONS ) )

#define GPIO_NUMBER 16U
#define MASK_GPIO_LOCATIONS 0x0000FFFF

#define PIN0  (1 << 0)
#define PIN1  (1 << 1)
#define PIN2  (1 << 2)
#define PIN3  (1 << 3)
#define PIN4  (1 << 4)
#define PIN5  (1 << 5)
#define PIN6  (1 << 6)
#define PIN7  (1 << 7)
#define PIN8  (1 << 8)
#define PIN9  (1 << 9)
#define PIN10 (1 << 10)
#define PIN11 (1 << 11)
#define PIN12 (1 << 12)
#define PIN13 (1 << 13)
#define PIN14 (1 << 14)
#define PIN15 (1 << 15)

#define PA0  PIN0
#define PA1  PIN1
#define PA2  PIN2
#define PA3  PIN3
#define PA4  PIN4
#define PA5  PIN5
#define PA6  PIN6
#define PA7  PIN7
#define PA8  PIN8
#define PA9  PIN9
#define PA10 PIN10
#define PA11 PIN11
#define PA12 PIN12
#define PA13 PIN13
#define PA14 PIN14
#define PA15 PIN15

#define PB0  PIN0
#define PB1  PIN1
#define PB2  PIN2
#define PB3  PIN3
#define PB4  PIN4
#define PB5  PIN5
#define PB6  PIN6
#define PB7  PIN7

#define PC14 PIN14
#define PC15 PIN15

#define PH3  PIN3

#define GPIO_RESET 0U
#define GPIO_SET   1U

#define GPIO_MODE_INPUT  0U
#define GPIO_MODE_OUTPUT 1U
#define GPIO_MODE_AF     2U
#define GPIO_MODE_ANALOG 3U

#define GPIO_OTYPE_PUSHPULL  0U
#define GPIO_OTYPE_OPENDRAIN 1U

#define GPIO_OSPEED_LOW      0U
#define GPIO_OSPEED_MEDIUM   1U
#define GPIO_OSPEED_HIGH     2U
#define GPIO_OSPEED_VERYHIGH 3U

#define GPIO_PUPD_NONE     0U
#define GPIO_PUPD_PULLUP   1U
#define GPIO_PUPD_PULLDOWN 2U

#define AF0  0U
#define AF1  1U
#define AF2  2U
#define AF3  3U
#define AF4  4U
#define AF5  5U
#define AF6  6U
#define AF7  7U
#define AF8  8U
#define AF9  9U
#define AF10 10U
#define AF11 11U
#define AF12 12U
#define AF13 13U
#define AF14 14U
#define AF15 15U

#define AF_PA0_TIM2_CH1          AF1
#define AF_PA0_USART2_CTS        AF7
#define AF_PA0_COMP1_OUT         AF12
#define AF_PA0_SAI1_EXTCLK       AF13
#define AF_PA0_TIM2_ETR          AF14
#define AF_PA0_EVENTOUT          AF15

#define AF_PA1_TIM2_CH2          AF1
#define AF_PA1_I2C1_SMBA         AF4
#define AF_PA1_SPI1_SCK          AF5
#define AF_PA1_USART2_RTS_DE     AF7
#define AF_PA1_TIM15_CH1N        AF14
#define AF_PA1_EVENTOUT          AF15

#define AF_PA2_TIM2_CH3          AF1
#define AF_PA2_USART2_TX         AF7
#define AF_PA2_LPUART1_TX        AF8
#define AF_PA2_QUADSPI_BK1_NCS   AF10
#define AF_PA2_COMP2_OUT         AF12
#define AF_PA2_TIM15_CH1         AF14
#define AF_PA2_EVENTOUT          AF15

#define AF_PA3_TIM2_CH4          AF1
#define AF_PA3_USART2_RX         AF7
#define AF_PA3_LPUART1_RX        AF8
#define AF_PA3_QUADSPI_CLK       AF10
#define AF_PA3_SAI1_MCLK_A       AF13
#define AF_PA3_TIM15_CH2         AF14
#define AF_PA3_EVENTOUT          AF15

#define AF_PA4_SPI1_NSS          AF5
#define AF_PA4_SPI3_NSS          AF6
#define AF_PA4_USART2_CK         AF7
#define AF_PA4_SAI1_FS_B         AF13
#define AF_PA4_LPTIM2_OUT        AF14
#define AF_PA4_EVENTOUT          AF15

#define AF_PA5_TIM2_CH1          AF1
#define AF_PA5_TIM2_ETR          AF2
#define AF_PA5_SPI1_SCK          AF5
#define AF_PA5_LPTIM2_ETR        AF14
#define AF_PA5_EVENTOUT          AF15

#define AF_PA6_TIM1_BKIN         AF1
#define AF_PA6_SPI1_MISO         AF5
#define AF_PA6_COMP1_OUT         AF6
#define AF_PA6_USART3_CTS        AF7
#define AF_PA6_LPUART1_CTS       AF8
#define AF_PA6_QUADSPI_BK1_IO3   AF10
#define AF_PA6_TIM1_BKIN_COMP2   AF12
#define AF_PA6_TIM16_CH1         AF15
#define AF_PA6_EVENTOUT          AF15

#define AF_PA7_TIM1_CH1N         AF1
#define AF_PA7_I2C3_SCL          AF4
#define AF_PA7_SPI1_MOSI         AF5
#define AF_PA7_QUADSPI_BK1_IO2   AF10
#define AF_PA7_COMP2_OUT         AF12
#define AF_PA7_EVENTOUT          AF15

#define AF_PA8_MCO               AF0
#define AF_PA8_TIM1_CH1          AF1
#define AF_PA8_USART1_CK         AF7
#define AF_PA8_SWPMI1_IO         AF12
#define AF_PA8_SAI1_SCK_A        AF13
#define AF_PA8_LPTIM2_OUT        AF14
#define AF_PA8_EVENTOUT          AF15

#define AF_PA9_TIM1_CH2          AF1
#define AF_PA9_I2C1_SCL          AF4
#define AF_PA9_USART1_TX         AF7
#define AF_PA9_SAI1_FS_A         AF13
#define AF_PA9_TIM15_BKIN        AF14
#define AF_PA9_EVENTOUT          AF15

#define AF_PA10_TIM1_CH3         AF1
#define AF_PA10_I2C1_SDA         AF4
#define AF_PA10_USART1_RX        AF7
#define AF_PA10_USB_CRS_SYNC     AF10
#define AF_PA10_SAI1_SD_A        AF13
#define AF_PA10_EVENTOUT         AF15

#define AF_PA11_TIM1_CH4         AF1
#define AF_PA11_TIM1_BKIN2       AF2
#define AF_PA11_SPI1_MISO        AF5
#define AF_PA11_COMP1_OUT        AF6
#define AF_PA11_USART1_CTS       AF7
#define AF_PA11_CAN1_RX          AF9
#define AF_PA11_USB_DM           AF10
#define AF_PA11_TIM1_BKIN2_COMP1 AF12
#define AF_PA11_EVENTOUT         AF15

#define AF_PA12_TIM1_ETR         AF1
#define AF_PA12_SPI1_MOSI        AF5
#define AF_PA12_USART1_RTS_DE    AF7
#define AF_PA12_CAN1_TX          AF9
#define AF_PA12_USB_DP           AF10
#define AF_PA12_EVENTOUT         AF15

#define AF_PA13_JTMS_SWDIO       AF0
#define AF_PA13_IR_OUT           AF1
#define AF_PA13_USB_NOE          AF10
#define AF_PA13_SWPMI1_TX        AF12
#define AF_PA13_SAI1_SD_B        AF13
#define AF_PA13_EVENTOUT         AF15

#define AF_PA14_JTCK_SWCLK       AF0
#define AF_PA14_LPTIM1_OUT       AF1
#define AF_PA14_I2C1_SMBA        AF4
#define AF_PA14_SWPMI1_RX        AF12
#define AF_PA14_SAI1_FS_B        AF13
#define AF_PA14_EVENTOUT         AF15

#define AF_PA15_JTDI             AF0
#define AF_PA15_TIM2_CH1         AF1
#define AF_PA15_TIM2_ETR         AF2
#define AF_PA15_USART2_RX        AF3
#define AF_PA15_SPI1_NSS         AF5
#define AF_PA15_SPI3_NSS         AF6
#define AF_PA15_USART3_RTS_DE    AF7
#define AF_PA15_TSC_G3_IO1       AF9
#define AF_PA15_SWPMI1_SUSPEND   AF12
#define AF_PA15_EVENTOUT         AF15

#define AF_PB0_TIM1_CH2N         AF1
#define AF_PB0_SPI1_NSS          AF5
#define AF_PB0_USART3_CK         AF7
#define AF_PB0_QUADSPI_BK1_IO1   AF10
#define AF_PB0_COMP1_OUT         AF12
#define AF_PB0_SAI1_EXTCLK       AF13
#define AF_PB0_EVENTOUT          AF15

#define AF_PB1_TIM1_CH3N         AF1
#define AF_PB1_USART3_RTS_DE     AF7
#define AF_PB1_LPUART1_RTS_DE    AF8
#define AF_PB1_QUADSPI_BK1_IO0   AF10
#define AF_PB1_LPTIM2_IN1        AF14
#define AF_PB1_EVENTOUT          AF15

#define AF_PB3_JTDO_TRACESWO     AF0
#define AF_PB3_TIM2_CH2          AF1
#define AF_PB3_SPI1_SCK          AF5
#define AF_PB3_SPI3_SCK          AF6
#define AF_PB3_USART1_RTS_DE     AF7
#define AF_PB3_SAI1_SCK_B        AF13
#define AF_PB3_EVENTOUT          AF15

#define AF_PB4_NJTRST            AF0
#define AF_PB4_I2C3_SDA          AF4
#define AF_PB4_SPI1_MISO         AF5
#define AF_PB4_SPI3_MISO         AF6
#define AF_PB4_USART1_CTS        AF7
#define AF_PB4_TSC_G2_IO1        AF9
#define AF_PB4_SAI1_MCLK_B       AF13
#define AF_PB4_EVENTOUT          AF15

#define AF_PB5_LPTIM1_IN1        AF1
#define AF_PB5_I2C1_SMBA         AF4
#define AF_PB5_SPI1_MOSI         AF5
#define AF_PB5_SPI3_MOSI         AF6
#define AF_PB5_USART1_CK         AF7
#define AF_PB5_TSC_G2_IO2        AF9
#define AF_PB5_COMP2_OUT         AF12
#define AF_PB5_SAI1_SD_B         AF13
#define AF_PB5_TIM16_BKIN        AF14
#define AF_PB5_EVENTOUT          AF15

#define AF_PB6_LPTIM1_ETR        AF1
#define AF_PB6_I2C1_SCL          AF4
#define AF_PB6_USART1_TX         AF7
#define AF_PB6_TSC_G2_IO3        AF9
#define AF_PB6_SAI1_FS_B         AF13
#define AF_PB6_TIM16_CH1N        AF14
#define AF_PB6_EVENTOUT          AF15

#define AF_PB7_LPTIM1_IN2        AF1
#define AF_PB7_I2C1_SDA          AF4
#define AF_PB7_USART1_RX         AF7
#define AF_PB7_TSC_G2_IO4        AF9
#define AF_PB7_EVENTOUT          AF15

#define AF_PC14_EVENTOUT         AF15

#define AF_PC15_EVENTOUT         AF15

#define AF_PH3_EVENTOUT          AF15

#define MASK_RCC_AHPB2ENR_GPIOAEN (1 << 0)
#define MASK_RCC_AHPB2ENR_GPIOBEN (1 << 1)
#define MASK_RCC_AHPB2ENR_GPIOCEN (1 << 2)
#define MASK_RCC_AHPB2ENR_GPIOHEN (1 << 7)

#define ADDRESS_BASE_GPIOA 0x48000000
#define ADDRESS_BASE_GPIOB 0x48000400
#define ADDRESS_BASE_GPIOC 0x48000800
#define ADDRESS_BASE_GPIOH 0x48001C00

#define GPIOA ( (GPIO_t *) (ADDRESS_BASE_GPIOA) )
#define GPIOB ( (GPIO_t *) (ADDRESS_BASE_GPIOB) )
#define GPIOC ( (GPIO_t *) (ADDRESS_BASE_GPIOC) )
#define GPIOH ( (GPIO_t *) (ADDRESS_BASE_GPIOH) )

typedef struct {
    uint32_t volatile MODER;
    uint32_t volatile OTYPER;
    uint32_t volatile OSPEEDR;
    uint32_t volatile PUPDR;
    uint32_t volatile IDR;
    uint32_t volatile ODR;
    uint32_t volatile BSRR;
    uint32_t volatile LCKR;
    uint32_t volatile AFR[2];
    uint32_t volatile BRR;
} GPIO_t;

typedef struct {
   uint8_t pin;
   uint8_t mode;
   uint8_t output_type;
   uint8_t output_speed;
   uint8_t resistor;
   uint8_t resistor;
} GPIO_config_t;

void GPIOA_clock_enable(void);
void GPIOB_clock_enable(void);
void GPIOC_clock_enable(void);
void GPIOH_clock_enable(void);

uint8_t GPIO_get_position(uint16_t pin);

static void GPIO_set_mode(GPIO_t * port, uint16_t pin, uint8_t mode);
static void GPIO_set_output_type(GPIO_t * port, uint16_t pin, uint8_t output_type);
static void GPIO_set_output_speed(GPIO_t * port, uint16_t pin, uint8_t output_speed);
static void GPIO_set_resistor(GPIO_t * port, uint16_t pin, uint8_t resistor);
static void GPIO_set_alternate(GPIO_t * port, uint16_t pin, uint8_t alterante);

void GPIO_config(GPIO_t * port, GPIO_config_t config);
void GPIO_reset(GPIO_t * port, uint16_t pin);
void GPIO_lock(GPIO_t * port, uint16_t pins);
void GPIO_set(GPIO_t * port, uint16_t pin);
void GPIO_clear(GPIO_t * port, uint16_t pin);
void GPIO_toggle(GPIO_t * port, uint16_t pin);
_Bool GPIO_read(GPIO_t * port, uint16_t pin);

#endif

