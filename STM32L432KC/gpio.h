#ifndef STM32L432KC_GPIO_H
#define STM32L432KC_GPIO_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

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
} GPIO_REG_BLOCKS;

/* GPIO registers as structs */

#define GPIOA ( (GPIO_REG_BLOCKS volatile *) 0x48000000 )
#define GPIOB ( (GPIO_REG_BLOCKS volatile *) 0x48000400 )
#define GPIOC ( (GPIO_REG_BLOCKS volatile *) 0x48000800 )
#define GPIOH ( (GPIO_REG_BLOCKS volatile *) 0x48001C00 )

/* GPIO pin 0 macros */

#define GPIO_MODER_MODE0(v) ( ( (v) & 0x3 ) << 0 )
#define GPIO_MODER_MODE0_MASK GPIO_MODER_MODE0(ALL1)
#define GPIO_OTYPER_OT0(v) ( ( (v) & 0x1 ) << 0 )
#define GPIO_OTYPER_OT0_MASK GPIO_OTYPER_OT0(ALL1)
#define GPIO_OSPEEDR_OSPEED0(v) ( ( (v) & 0x3 ) << 0 )
#define GPIO_OSPEEDR_OSPEED0_MASK GPIO_OSPEEDR_OSPEED0(ALL1)
#define GPIO_PUPDR_PUPD0(v) ( ( (v) & 0x3 ) << 0 )
#define GPIO_PUPDR_PUPD0_MASK GPIO_PUPDR_PUPD0(ALL1)
#define GPIO_AFR_AFSEL0(v) ( ( (v) & 0xF ) << 0 )
#define GPIO_AFR_AFSEL0_MASK GPIO_AFR_AFSEL0(ALL1)

#define GPIO_IDR_ID0_MASK (0x1 << 0)
#define GPIO_ODR_OD0(v) ( ( (v) & 0x1 ) << 0 )
#define GPIO_ODR_OD0_MASK GPIO_ODR_OD0(ALL1)
#define GPIO_BSRR_BS0(v) ( ( (v) & 0x1 ) << 0 )
#define GPIO_BSRR_BR0(v) ( ( (v) & 0x1 ) << 16 )
#define GPIO_BRR_BR0(v) ( ( (v) & 0x1 ) << 0 )

/* GPIO pin 1 macros */

#define GPIO_MODER_MODE1(v) ( ( (v) & 0x3 ) << 2 )
#define GPIO_MODER_MODE1_MASK GPIO_MODER_MODE1(ALL1)
#define GPIO_OTYPER_OT1(v) ( ( (v) & 0x1 ) << 1 )
#define GPIO_OTYPER_OT1_MASK GPIO_OTYPER_OT1(ALL1)
#define GPIO_OSPEEDR_OSPEED1(v) ( ( (v) & 0x3 ) << 2 )
#define GPIO_OSPEEDR_OSPEED1_MASK GPIO_OSPEEDR_OSPEED1(ALL1)
#define GPIO_PUPDR_PUPD1(v) ( ( (v) & 0x3 ) << 2 )
#define GPIO_PUPDR_PUPD1_MASK GPIO_PUPDR_PUPD1(ALL1)
#define GPIO_AFR_AFSEL1(v) ( ( (v) & 0xF ) << 4 )
#define GPIO_AFR_AFSEL1_MASK GPIO_AFR_AFSEL1(ALL1)

#define GPIO_IDR_ID1_MASK (0x1 << 1)
#define GPIO_ODR_OD1(v) ( ( (v) & 0x1 ) << 1 )
#define GPIO_ODR_OD1_MASK GPIO_ODR_OD1(ALL1)
#define GPIO_BSRR_BS1(v) ( ( (v) & 0x1 ) << 1 )
#define GPIO_BSRR_BR1(v) ( ( (v) & 0x1 ) << 17 )
#define GPIO_BRR_BR1(v) ( ( (v) & 0x1 ) << 1 )

/* GPIO pin 2 macros */

#define GPIO_MODER_MODE2(v) ( ( (v) & 0x3 ) << 4 )
#define GPIO_MODER_MODE2_MASK GPIO_MODER_MODE2(ALL1)
#define GPIO_OTYPER_OT2(v) ( ( (v) & 0x1 ) << 2 )
#define GPIO_OTYPER_OT2_MASK GPIO_OTYPER_OT2(ALL1)
#define GPIO_OSPEEDR_OSPEED2(v) ( ( (v) & 0x3 ) << 4 )
#define GPIO_OSPEEDR_OSPEED2_MASK GPIO_OSPEEDR_OSPEED2(ALL1)
#define GPIO_PUPDR_PUPD2(v) ( ( (v) & 0x3 ) << 4 )
#define GPIO_PUPDR_PUPD2_MASK GPIO_PUPDR_PUPD2(ALL1)
#define GPIO_AFR_AFSEL2(v) ( ( (v) & 0xF ) << 8 )
#define GPIO_AFR_AFSEL2_MASK GPIO_AFR_AFSEL2(ALL1)

#define GPIO_IDR_ID2_MASK (0x1 << 2)
#define GPIO_ODR_OD2(v) ( ( (v) & 0x1 ) << 2 )
#define GPIO_ODR_OD2_MASK GPIO_ODR_OD2(ALL1)
#define GPIO_BSRR_BS2(v) ( ( (v) & 0x1 ) << 2 )
#define GPIO_BSRR_BR2(v) ( ( (v) & 0x1 ) << 18 )
#define GPIO_BRR_BR2(v) ( ( (v) & 0x1 ) << 2 )

/* GPIO pin 3 macros */

#define GPIO_MODER_MODE3(v) ( ( (v) & 0x3 ) << 6 )
#define GPIO_MODER_MODE3_MASK GPIO_MODER_MODE3(ALL1)
#define GPIO_OTYPER_OT3(v) ( ( (v) & 0x1 ) << 3 )
#define GPIO_OTYPER_OT3_MASK GPIO_OTYPER_OT3(ALL1)
#define GPIO_OSPEEDR_OSPEED3(v) ( ( (v) & 0x3 ) << 6 )
#define GPIO_OSPEEDR_OSPEED3_MASK GPIO_OSPEEDR_OSPEED3(ALL1)
#define GPIO_PUPDR_PUPD3(v) ( ( (v) & 0x3 ) << 6 )
#define GPIO_PUPDR_PUPD3_MASK GPIO_PUPDR_PUPD3(ALL1)
#define GPIO_AFR_AFSEL3(v) ( ( (v) & 0xF ) << 12 )
#define GPIO_AFR_AFSEL3_MASK GPIO_AFR_AFSEL3(ALL1)

#define GPIO_IDR_ID3_MASK (0x1 << 3)
#define GPIO_ODR_OD3(v) ( ( (v) & 0x1 ) << 3 )
#define GPIO_ODR_OD3_MASK GPIO_ODR_OD3(ALL1)
#define GPIO_BSRR_BS3(v) ( ( (v) & 0x1 ) << 3 )
#define GPIO_BSRR_BR3(v) ( ( (v) & 0x1 ) << 19 )
#define GPIO_BRR_BR3(v) ( ( (v) & 0x1 ) << 3 )

/* GPIO pin 4 macros */

#define GPIO_MODER_MODE4(v) ( ( (v) & 0x3 ) << 8 )
#define GPIO_MODER_MODE4_MASK GPIO_MODER_MODE4(ALL1)
#define GPIO_OTYPER_OT4(v) ( ( (v) & 0x1 ) << 4 )
#define GPIO_OTYPER_OT4_MASK GPIO_OTYPER_OT4(ALL1)
#define GPIO_OSPEEDR_OSPEED4(v) ( ( (v) & 0x3 ) << 8 )
#define GPIO_OSPEEDR_OSPEED4_MASK GPIO_OSPEEDR_OSPEED4(ALL1)
#define GPIO_PUPDR_PUPD4(v) ( ( (v) & 0x3 ) << 8 )
#define GPIO_PUPDR_PUPD4_MASK GPIO_PUPDR_PUPD4(ALL1)
#define GPIO_AFR_AFSEL4(v) ( ( (v) & 0xF ) << 16 )
#define GPIO_AFR_AFSEL4_MASK GPIO_AFR_AFSEL4(ALL1)

#define GPIO_IDR_ID4_MASK (0x1 << 4)
#define GPIO_ODR_OD4(v) ( ( (v) & 0x1 ) << 4 )
#define GPIO_ODR_OD4_MASK GPIO_ODR_OD4(ALL1)
#define GPIO_BSRR_BS4(v) ( ( (v) & 0x1 ) << 4 )
#define GPIO_BSRR_BR4(v) ( ( (v) & 0x1 ) << 20 )
#define GPIO_BRR_BR4(v) ( ( (v) & 0x1 ) << 4 )

/* GPIO pin 5 macros */

#define GPIO_MODER_MODE5(v) ( ( (v) & 0x3 ) << 10 )
#define GPIO_MODER_MODE5_MASK GPIO_MODER_MODE5(ALL1)
#define GPIO_OTYPER_OT5(v) ( ( (v) & 0x1 ) << 5 )
#define GPIO_OTYPER_OT5_MASK GPIO_OTYPER_OT5(ALL1)
#define GPIO_OSPEEDR_OSPEED5(v) ( ( (v) & 0x3 ) << 10 )
#define GPIO_OSPEEDR_OSPEED5_MASK GPIO_OSPEEDR_OSPEED5(ALL1)
#define GPIO_PUPDR_PUPD5(v) ( ( (v) & 0x3 ) << 10 )
#define GPIO_PUPDR_PUPD5_MASK GPIO_PUPDR_PUPD5(ALL1)
#define GPIO_AFR_AFSEL5(v) ( ( (v) & 0xF ) << 20 )
#define GPIO_AFR_AFSEL5_MASK GPIO_AFR_AFSEL5(ALL1)

#define GPIO_IDR_ID5_MASK (0x1 << 5)
#define GPIO_ODR_OD5(v) ( ( (v) & 0x1 ) << 5 )
#define GPIO_ODR_OD5_MASK GPIO_ODR_OD5(ALL1)
#define GPIO_BSRR_BS5(v) ( ( (v) & 0x1 ) << 5 )
#define GPIO_BSRR_BR5(v) ( ( (v) & 0x1 ) << 21 )
#define GPIO_BRR_BR5(v) ( ( (v) & 0x1 ) << 5 )

/* GPIO pin 6 macros */

#define GPIO_MODER_MODE6(v) ( ( (v) & 0x3 ) << 12 )
#define GPIO_MODER_MODE6_MASK GPIO_MODER_MODE6(ALL1)
#define GPIO_OTYPER_OT6(v) ( ( (v) & 0x1 ) << 6 )
#define GPIO_OTYPER_OT6_MASK GPIO_OTYPER_OT6(ALL1)
#define GPIO_OSPEEDR_OSPEED6(v) ( ( (v) & 0x3 ) << 12 )
#define GPIO_OSPEEDR_OSPEED6_MASK GPIO_OSPEEDR_OSPEED6(ALL1)
#define GPIO_PUPDR_PUPD6(v) ( ( (v) & 0x3 ) << 12 )
#define GPIO_PUPDR_PUPD6_MASK GPIO_PUPDR_PUPD6(ALL1)
#define GPIO_AFR_AFSEL6(v) ( ( (v) & 0xF ) << 24 )
#define GPIO_AFR_AFSEL6_MASK GPIO_AFR_AFSEL6(ALL1)

#define GPIO_IDR_ID6_MASK (0x1 << 6)
#define GPIO_ODR_OD6(v) ( ( (v) & 0x1 ) << 6 )
#define GPIO_ODR_OD6_MASK GPIO_ODR_OD6(ALL1)
#define GPIO_BSRR_BS6(v) ( ( (v) & 0x1 ) << 6 )
#define GPIO_BSRR_BR6(v) ( ( (v) & 0x1 ) << 22 )
#define GPIO_BRR_BR6(v) ( ( (v) & 0x1 ) << 6 )

/* GPIO pin 7 macros */

#define GPIO_MODER_MODE7(v) ( ( (v) & 0x3 ) << 14 )
#define GPIO_MODER_MODE7_MASK GPIO_MODER_MODE7(ALL1)
#define GPIO_OTYPER_OT7(v) ( ( (v) & 0x1 ) << 7 )
#define GPIO_OTYPER_OT7_MASK GPIO_OTYPER_OT7(ALL1)
#define GPIO_OSPEEDR_OSPEED7(v) ( ( (v) & 0x3 ) << 14 )
#define GPIO_OSPEEDR_OSPEED7_MASK GPIO_OSPEEDR_OSPEED7(ALL1)
#define GPIO_PUPDR_PUPD7(v) ( ( (v) & 0x3 ) << 14 )
#define GPIO_PUPDR_PUPD7_MASK GPIO_PUPDR_PUPD7(ALL1)
#define GPIO_AFR_AFSEL7(v) ( ( (v) & 0xF ) << 28 )
#define GPIO_AFR_AFSEL7_MASK GPIO_AFR_AFSEL7(ALL1)

#define GPIO_IDR_ID7_MASK (0x1 << 7)
#define GPIO_ODR_OD7(v) ( ( (v) & 0x1 ) << 7 )
#define GPIO_ODR_OD7_MASK GPIO_ODR_OD7(ALL1)
#define GPIO_BSRR_BS7(v) ( ( (v) & 0x1 ) << 7 )
#define GPIO_BSRR_BR7(v) ( ( (v) & 0x1 ) << 23 )
#define GPIO_BRR_BR7(v) ( ( (v) & 0x1 ) << 7 )

/* GPIO pin 8 macros */

#define GPIO_MODER_MODE8(v) ( ( (v) & 0x3 ) << 16 )
#define GPIO_MODER_MODE8_MASK GPIO_MODER_MODE8(ALL1)
#define GPIO_OTYPER_OT8(v) ( ( (v) & 0x1 ) << 8 )
#define GPIO_OTYPER_OT8_MASK GPIO_OTYPER_OT8(ALL1)
#define GPIO_OSPEEDR_OSPEED8(v) ( ( (v) & 0x3 ) << 16 )
#define GPIO_OSPEEDR_OSPEED8_MASK GPIO_OSPEEDR_OSPEED8(ALL1)
#define GPIO_PUPDR_PUPD8(v) ( ( (v) & 0x3 ) << 16 )
#define GPIO_PUPDR_PUPD8_MASK GPIO_PUPDR_PUPD8(ALL1)
#define GPIO_AFR_AFSEL8(v) ( ( (v) & 0xF ) << 0 )
#define GPIO_AFR_AFSEL8_MASK GPIO_AFR_AFSEL8(ALL1)

#define GPIO_IDR_ID8_MASK (0x1 << 8)
#define GPIO_ODR_OD8(v) ( ( (v) & 0x1 ) << 8 )
#define GPIO_ODR_OD8_MASK GPIO_ODR_OD8(ALL1)
#define GPIO_BSRR_BS8(v) ( ( (v) & 0x1 ) << 8 )
#define GPIO_BSRR_BR8(v) ( ( (v) & 0x1 ) << 24 )
#define GPIO_BRR_BR8(v) ( ( (v) & 0x1 ) << 8 )

/* GPIO pin 9 macros */

#define GPIO_MODER_MODE9(v) ( ( (v) & 0x3 ) << 18 )
#define GPIO_MODER_MODE9_MASK GPIO_MODER_MODE9(ALL1)
#define GPIO_OTYPER_OT9(v) ( ( (v) & 0x1 ) << 9 )
#define GPIO_OTYPER_OT9_MASK GPIO_OTYPER_OT9(ALL1)
#define GPIO_OSPEEDR_OSPEED9(v) ( ( (v) & 0x3 ) << 18 )
#define GPIO_OSPEEDR_OSPEED9_MASK GPIO_OSPEEDR_OSPEED9(ALL1)
#define GPIO_PUPDR_PUPD9(v) ( ( (v) & 0x3 ) << 18 )
#define GPIO_PUPDR_PUPD9_MASK GPIO_PUPDR_PUPD9(ALL1)
#define GPIO_AFR_AFSEL9(v) ( ( (v) & 0xF ) << 4 )
#define GPIO_AFR_AFSEL9_MASK GPIO_AFR_AFSEL9(ALL1)

#define GPIO_IDR_ID9_MASK (0x1 << 9)
#define GPIO_ODR_OD9(v) ( ( (v) & 0x1 ) << 9 )
#define GPIO_ODR_OD9_MASK GPIO_ODR_OD9(ALL1)
#define GPIO_BSRR_BS9(v) ( ( (v) & 0x1 ) << 9 )
#define GPIO_BSRR_BR9(v) ( ( (v) & 0x1 ) << 25 )
#define GPIO_BRR_BR9(v) ( ( (v) & 0x1 ) << 9 )

/* GPIO pin 10 macros */

#define GPIO_MODER_MODE10(v) ( ( (v) & 0x3 ) << 20 )
#define GPIO_MODER_MODE10_MASK GPIO_MODER_MODE10(ALL1)
#define GPIO_OTYPER_OT10(v) ( ( (v) & 0x1 ) << 10 )
#define GPIO_OTYPER_OT10_MASK GPIO_OTYPER_OT10(ALL1)
#define GPIO_OSPEEDR_OSPEED10(v) ( ( (v) & 0x3 ) << 20 )
#define GPIO_OSPEEDR_OSPEED10_MASK GPIO_OSPEEDR_OSPEED10(ALL1)
#define GPIO_PUPDR_PUPD10(v) ( ( (v) & 0x3 ) << 20 )
#define GPIO_PUPDR_PUPD10_MASK GPIO_PUPDR_PUPD10(ALL1)
#define GPIO_AFR_AFSEL10(v) ( ( (v) & 0xF ) << 8 )
#define GPIO_AFR_AFSEL10_MASK GPIO_AFR_AFSEL10(ALL1)

#define GPIO_IDR_ID10_MASK (0x1 << 10)
#define GPIO_ODR_OD10(v) ( ( (v) & 0x1 ) << 10 )
#define GPIO_ODR_OD10_MASK GPIO_ODR_OD10(ALL1)
#define GPIO_BSRR_BS10(v) ( ( (v) & 0x1 ) << 10 )
#define GPIO_BSRR_BR10(v) ( ( (v) & 0x1 ) << 26 )
#define GPIO_BRR_BR10(v) ( ( (v) & 0x1 ) << 10 )

/* GPIO pin 11 macros */

#define GPIO_MODER_MODE11(v) ( ( (v) & 0x3 ) << 22 )
#define GPIO_MODER_MODE11_MASK GPIO_MODER_MODE11(ALL1)
#define GPIO_OTYPER_OT11(v) ( ( (v) & 0x1 ) << 11 )
#define GPIO_OTYPER_OT11_MASK GPIO_OTYPER_OT11(ALL1)
#define GPIO_OSPEEDR_OSPEED11(v) ( ( (v) & 0x3 ) << 22 )
#define GPIO_OSPEEDR_OSPEED11_MASK GPIO_OSPEEDR_OSPEED11(ALL1)
#define GPIO_PUPDR_PUPD11(v) ( ( (v) & 0x3 ) << 22 )
#define GPIO_PUPDR_PUPD11_MASK GPIO_PUPDR_PUPD11(ALL1)
#define GPIO_AFR_AFSEL11(v) ( ( (v) & 0xF ) << 12 )
#define GPIO_AFR_AFSEL11_MASK GPIO_AFR_AFSEL11(ALL1)

#define GPIO_IDR_ID11_MASK (0x1 << 11)
#define GPIO_ODR_OD11(v) ( ( (v) & 0x1 ) << 11 )
#define GPIO_ODR_OD11_MASK GPIO_ODR_OD11(ALL1)
#define GPIO_BSRR_BS11(v) ( ( (v) & 0x1 ) << 11 )
#define GPIO_BSRR_BR11(v) ( ( (v) & 0x1 ) << 27 )
#define GPIO_BRR_BR11(v) ( ( (v) & 0x1 ) << 11 )

/* GPIO pin 12 macros */

#define GPIO_MODER_MODE12(v) ( ( (v) & 0x3 ) << 24 )
#define GPIO_MODER_MODE12_MASK GPIO_MODER_MODE12(ALL1)
#define GPIO_OTYPER_OT12(v) ( ( (v) & 0x1 ) << 12 )
#define GPIO_OTYPER_OT12_MASK GPIO_OTYPER_OT12(ALL1)
#define GPIO_OSPEEDR_OSPEED12(v) ( ( (v) & 0x3 ) << 24 )
#define GPIO_OSPEEDR_OSPEED12_MASK GPIO_OSPEEDR_OSPEED12(ALL1)
#define GPIO_PUPDR_PUPD12(v) ( ( (v) & 0x3 ) << 24 )
#define GPIO_PUPDR_PUPD12_MASK GPIO_PUPDR_PUPD12(ALL1)
#define GPIO_AFR_AFSEL12(v) ( ( (v) & 0xF ) << 16 )
#define GPIO_AFR_AFSEL12_MASK GPIO_AFR_AFSEL12(ALL1)

#define GPIO_IDR_ID12_MASK (0x1 << 12)
#define GPIO_ODR_OD12(v) ( ( (v) & 0x1 ) << 12 )
#define GPIO_ODR_OD12_MASK GPIO_ODR_OD12(ALL1)
#define GPIO_BSRR_BS12(v) ( ( (v) & 0x1 ) << 12 )
#define GPIO_BSRR_BR12(v) ( ( (v) & 0x1 ) << 28 )
#define GPIO_BRR_BR12(v) ( ( (v) & 0x1 ) << 12 )

/* GPIO pin 13 macros */

#define GPIO_MODER_MODE13(v) ( ( (v) & 0x3 ) << 26 )
#define GPIO_MODER_MODE13_MASK GPIO_MODER_MODE13(ALL1)
#define GPIO_OTYPER_OT13(v) ( ( (v) & 0x1 ) << 13 )
#define GPIO_OTYPER_OT13_MASK GPIO_OTYPER_OT13(ALL1)
#define GPIO_OSPEEDR_OSPEED13(v) ( ( (v) & 0x3 ) << 26 )
#define GPIO_OSPEEDR_OSPEED13_MASK GPIO_OSPEEDR_OSPEED13(ALL1)
#define GPIO_PUPDR_PUPD13(v) ( ( (v) & 0x3 ) << 26 )
#define GPIO_PUPDR_PUPD13_MASK GPIO_PUPDR_PUPD13(ALL1)
#define GPIO_AFR_AFSEL13(v) ( ( (v) & 0xF ) << 20 )
#define GPIO_AFR_AFSEL13_MASK GPIO_AFR_AFSEL13(ALL1)

#define GPIO_IDR_ID13_MASK (0x1 << 13)
#define GPIO_ODR_OD13(v) ( ( (v) & 0x1 ) << 13 )
#define GPIO_ODR_OD13_MASK GPIO_ODR_OD13(ALL1)
#define GPIO_BSRR_BS13(v) ( ( (v) & 0x1 ) << 13 )
#define GPIO_BSRR_BR13(v) ( ( (v) & 0x1 ) << 29 )
#define GPIO_BRR_BR13(v) ( ( (v) & 0x1 ) << 13 )

/* GPIO pin 14 macros */

#define GPIO_MODER_MODE14(v) ( ( (v) & 0x3 ) << 28 )
#define GPIO_MODER_MODE14_MASK GPIO_MODER_MODE14(ALL1)
#define GPIO_OTYPER_OT14(v) ( ( (v) & 0x1 ) << 14 )
#define GPIO_OTYPER_OT14_MASK GPIO_OTYPER_OT14(ALL1)
#define GPIO_OSPEEDR_OSPEED14(v) ( ( (v) & 0x3 ) << 28 )
#define GPIO_OSPEEDR_OSPEED14_MASK GPIO_OSPEEDR_OSPEED14(ALL1)
#define GPIO_PUPDR_PUPD14(v) ( ( (v) & 0x3 ) << 28 )
#define GPIO_PUPDR_PUPD14_MASK GPIO_PUPDR_PUPD14(ALL1)
#define GPIO_AFR_AFSEL14(v) ( ( (v) & 0xF ) << 24 )
#define GPIO_AFR_AFSEL14_MASK GPIO_AFR_AFSEL14(ALL1)

#define GPIO_IDR_ID14_MASK (0x1 << 14)
#define GPIO_ODR_OD14(v) ( ( (v) & 0x1 ) << 14 )
#define GPIO_ODR_OD14_MASK GPIO_ODR_OD14(ALL1)
#define GPIO_BSRR_BS14(v) ( ( (v) & 0x1 ) << 14 )
#define GPIO_BSRR_BR14(v) ( ( (v) & 0x1 ) << 30 )
#define GPIO_BRR_BR14(v) ( ( (v) & 0x1 ) << 14 )

/* GPIO pin 15 macros */

#define GPIO_MODER_MODE15(v) ( ( (v) & 0x3 ) << 30 )
#define GPIO_MODER_MODE15_MASK GPIO_MODER_MODE15(ALL1)
#define GPIO_OTYPER_OT15(v) ( ( (v) & 0x1 ) << 15 )
#define GPIO_OTYPER_OT15_MASK GPIO_OTYPER_OT15(ALL1)
#define GPIO_OSPEEDR_OSPEED15(v) ( ( (v) & 0x3 ) << 30 )
#define GPIO_OSPEEDR_OSPEED15_MASK GPIO_OSPEEDR_OSPEED15(ALL1)
#define GPIO_PUPDR_PUPD15(v) ( ( (v) & 0x3 ) << 30 )
#define GPIO_PUPDR_PUPD15_MASK GPIO_PUPDR_PUPD15(ALL1)
#define GPIO_AFR_AFSEL15(v) ( ( (v) & 0xF ) << 28 )
#define GPIO_AFR_AFSEL15_MASK GPIO_AFR_AFSEL15(ALL1)

#define GPIO_IDR_ID15_MASK (0x1 << 15)
#define GPIO_ODR_OD15(v) ( ( (v) & 0x1 ) << 15 )
#define GPIO_ODR_OD15_MASK GPIO_ODR_OD15(ALL1)
#define GPIO_BSRR_BS15(v) ( ( (v) & 0x1 ) << 15 )
#define GPIO_BSRR_BR15(v) ( ( (v) & 0x1 ) << 31 )
#define GPIO_BRR_BR15(v) ( ( (v) & 0x1 ) << 15 )

#endif

