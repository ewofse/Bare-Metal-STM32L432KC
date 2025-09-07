#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#define MASK_RCC_AHB2ENR_GPIOAEN (1 << 0) 
#define MASK_RCC_AHB2ENR_GPIOBEN (1 << 1) 
#define MASK_RCC_AHB2ENR_GPIOCEN (1 << 2) 
#define MASK_RCC_AHB2ENR_GPIODEN (1 << 3) 
#define MASK_RCC_AHB2ENR_GPIOEEN (1 << 4) 
#define MASK_RCC_AHB2ENR_GPIOHEN (1 << 7)

#define MASK_RCC_APB2ENR_USART1EN  (1 << 14)
#define MASK_RCC_APB1ENR1_USART2EN (1 << 17)
#define MASK_RCC_APB1ENR1_USART3EN (1 << 18)

#define MASK_RCC_APB2ENR_TIM1EN (1 << 11)

#define ADDRESS_BASE_RCC 0x40021000

#define RCC ( (RCC_t *) (ADDRESS_BASE_RCC) )

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
} RCC_t;

#endif

