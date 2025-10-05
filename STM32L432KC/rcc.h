#ifndef STM32L432KC_RCC_H
#define STM32L432KC_RCC_H

#include <stdint.h>

typedef struct {
	uint32_t volatile CR;
	uint32_t volatile ICSCR;
	uint32_t volatile CFGR;
	uint32_t volatile PLLCFGR;
	uint32_t volatile PLLSAI1CFGR;
	uint32_t volatile RESERVED0;
	uint32_t volatile CIER;
	uint32_t volatile CIFR;
	uint32_t volatile CICR;
	uint32_t volatile RESERVED1;
	uint32_t volatile AHB1RSTR;
	uint32_t volatile AHB2RSTR;
	uint32_t volatile AHB3RSTR;
	uint32_t volatile RESERVED2;
	uint32_t volatile APB1STR1;
	uint32_t volatile APB1STR2;
	uint32_t volatile APB2RSTR;
	uint32_t volatile RESERVED3;
	uint32_t volatile AHB1ENR;
	uint32_t volatile AHB2ENR;
	uint32_t volatile AHB3ENR;
	uint32_t volatile RESERVED4;
	uint32_t volatile APB1ENR1;
	uint32_t volatile APB1NER2;
	uint32_t volatile APB2ENR;
	uint32_t volatile RESERVED5;
	uint32_t volatile AHB1SMENR;
	uint32_t volatile AHB2SMENR;
	uint32_t volatile AHB3SMENR;
	uint32_t volatile RESERVED6;
	uint32_t volatile APB1SMENR1;
	uint32_t volatile APB1SMENR2;
	uint32_t volatile APB2SMENR;
	uint32_t volatile RESERVED7;
	uint32_t volatile CCIPR;
	uint32_t volatile RESERVED8;
	uint32_t volatile BDCR;
	uint32_t volatile CSR;
	uint32_t volatile CRRCR;
	uint32_t volatile CCIPR2;
} RCC_REG_BLOCKS;

/* RCC registers as structs */

#define RCC ( (RCC_REG_BLOCKS volatile *) 0x40021000 )

/* RCC AHB1RSTR register macros */

#define RCC_AHB1RSTR_DMA1RST_MASK  (1 << 0)
#define RCC_AHB1RSTR_DMA2RST_MASK  (1 << 1)
#define RCC_AHB1RSTR_FLASHRST_MASK (1 << 6)
#define RCC_AHB1RSTR_CRCRST_MASK   (1 << 12)
#define RCC_AHB1RSTR_TSCRST_MASK   (1 << 16)

/* RCC AHB2RSTR register macros */

#define RCC_AHB2RSTR_GPIOARST_MASK (1 << 0)
#define RCC_AHB2RSTR_GPIOBRST_MASK (1 << 1)
#define RCC_AHB2RSTR_GPIOCRST_MASK (1 << 2)
#define RCC_AHB2RSTR_GPIOHRST_MASK (1 << 7)
#define RCC_AHB2RSTR_ADCRST_MASK   (1 << 13)
#define RCC_AHB2RSTR_AESRST_MASK   (1 << 16)
#define RCC_AHB2RSTR_RNGRST_MASK   (1 << 18)

/* RCC AHB3RSTR register macros */

#define RCC_AHB3RSTR_QSPIRST_MASK  (1 << 8)

/* RCC APB1RSTR register macros */

#define RCC_APB1RSTR_TIM2RST_MASK   (1 << 0)
#define RCC_APB1RSTR_TIM3RST_MASK   (1 << 1)
#define RCC_APB1RSTR_TIM6RST_MASK   (1 << 4)
#define RCC_APB1RSTR_TIM7RST_MASK   (1 << 5)
#define RCC_APB1RSTR_SPI2RST_MASK   (1 << 14)
#define RCC_APB1RSTR_SPI3RST_MASK   (1 << 15)
#define RCC_APB1RSTR_USART2RST_MASK (1 << 17)
#define RCC_APB1RSTR_I2C1RST_MASK   (1 << 21)
#define RCC_APB1RSTR_I2C3RST_MASK   (1 << 23)
#define RCC_APB1RSTR_CRSRST_MASK    (1 << 24)
#define RCC_APB1RSTR_CAN1RST_MASK   (1 << 25)
#define RCC_APB1RSTR_USBFSRST_MASK  (1 << 26)
#define RCC_APB1RSTR_PWRRST_MASK    (1 << 28)
#define RCC_APB1RSTR_DAC1RST_MASK   (1 << 29)
#define RCC_APB1RSTR_OPAMPRST_MASK  (1 << 30)
#define RCC_APB1RSTR_LPTIM1RST_MASK (1 << 31)

/* RCC APB2RSTR register macros */

#define RCC_APB2RSTR_SYSCFGRST_MASK (1 << 0)
#define RCC_APB2RSTR_TIM1RST_MASK   (1 << 11)
#define RCC_APB2RSTR_SPI1RST_MASK   (1 << 12)
#define RCC_APB2RSTR_USART1RST_MASK (1 << 14)
#define RCC_APB2RSTR_TIM15RST_MASK  (1 << 15)
#define RCC_APB2RSTR_TIM16RST_MASK  (1 << 16)
#define RCC_APB2RSTR_SAI1RST_MASK   (1 << 21)
#define RCC_APB2RSTR_DFSDM1RST_MASK (1 << 24)

/* RCC AHB1ENR register macros */

#define RCC_AHB1ENR_DMA1EN_MASK  (1 << 0)
#define RCC_AHB1ENR_DMA2EN_MASK  (1 << 1)
#define RCC_AHB1ENR_FLASHEN_MASK (1 << 6)
#define RCC_AHB1ENR_CRCEN_MASK   (1 << 12)
#define RCC_AHB1ENR_TSCEN_MASK   (1 << 16)

/* RCC AHB2ENR register macros */

#define RCC_AHB2ENR_GPIOAEN_MASK (1 << 0)
#define RCC_AHB2ENR_GPIOBEN_MASK (1 << 1)
#define RCC_AHB2ENR_GPIOCEN_MASK (1 << 2)
#define RCC_AHB2ENR_GPIOHEN_MASK (1 << 7)
#define RCC_AHB2ENR_ADCEN_MASK   (1 << 13)
#define RCC_AHB2ENR_AESEN_MASK   (1 << 16)
#define RCC_AHB2ENR_RNGEN_MASK   (1 << 18)

/* RCC AHB3ENR register macros */

#define RCC_AHB3ENR_QSPIEN_MASK  (1 << 8)

/* RCC APB1ENR register macros */

#define RCC_APB1ENR_TIM2EN_MASK   (1 << 0)
#define RCC_APB1ENR_TIM3EN_MASK   (1 << 1)
#define RCC_APB1ENR_TIM6EN_MASK   (1 << 4)
#define RCC_APB1ENR_TIM7EN_MASK   (1 << 5)
#define RCC_APB1ENR_RTCAPBEN_MASK (1 << 10)
#define RCC_APB1ENR_WWDGEN_MASK   (1 << 11)
#define RCC_APB1ENR_SPI2EN_MASK   (1 << 14)
#define RCC_APB1ENR_SPI3EN_MASK   (1 << 15)
#define RCC_APB1ENR_USART2EN_MASK (1 << 17)
#define RCC_APB1ENR_I2C1EN_MASK   (1 << 21)
#define RCC_APB1ENR_I2C3EN_MASK   (1 << 23)
#define RCC_APB1ENR_CRSEN_MASK    (1 << 24)
#define RCC_APB1ENR_CAN1EN_MASK   (1 << 25)
#define RCC_APB1ENR_USBFSEN_MASK  (1 << 26) 
#define RCC_APB1ENR_PWREN_MASK    (1 << 28)
#define RCC_APB1ENR_DAC1EN_MASK   (1 << 29)
#define RCC_APB1ENR_OPAMPEN_MASK  (1 << 30)
#define RCC_APB1ENR_LPTIM1EN_MASK (1 << 31) 

/* RCC APB2ENR register macros */

#define RCC_APB2ENR_SYSCFGEN_MASK (1 << 0)
#define RCC_APB2ENR_FWEN_MASK     (1 << 7)
#define RCC_APB2ENR_TIMEN_MASK    (1 << 11)
#define RCC_APB2ENR_SPI1EN_MASK   (1 << 12)
#define RCC_APB2ENR_USART1EN_MASK (1 << 14)
#define RCC_APB2ENR_TIM15EN_MASK  (1 << 16)
#define RCC_APB2ENR_TIM16EN_MASK  (1 << 17)
#define RCC_APB2ENR_SAI2EN_MASK   (1 << 21)

#endif

