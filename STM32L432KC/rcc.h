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

/* RCC AHB2 register macros */

#define RCC_AHB2ENR_GPIOAEN_MASK (1 << 0)
#define RCC_AHB2ENR_GPIOBEN_MASK (1 << 1)
#define RCC_AHB2ENR_GPIOCEN_MASK (1 << 2)
#define RCC_AHB2ENR_GPIOHEN_MASK (1 << 7)

#define RCC_AHB2ENR_ADCEN_MASK   (1 << 13)

#define RCC_AHB2ENR_AESEN_MASK   (1 << 16)

#define RCC_AHB2ENR_RNGEN_MASK   (1 << 18)

#endif

