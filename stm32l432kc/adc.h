#ifndef STM32L432KC_ADC_H
#define STM32L432KC_ADC_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t ISR;
    uint32_t IER;
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CFGR2;
    uint32_t SMPR1;
    uint32_t SMPR2;
    uint32_t RESERVED0;
    uint32_t TR1;
    uint32_t TR2;
    uint32_t TR3;
    uint32_t RESERVED1;
    uint32_t SQR1;
    uint32_t SQR2;
    uint32_t SQR3;
    uint32_t SQR4;
    uint32_t DR;
    uint32_t RESERVED2[2];
    uint32_t JSQR;
    uint32_t RESERVED3[4];
    uint32_t OFR1;
    uint32_t OFR2;
    uint32_t OFR3;
    uint32_t OFR4;
    uint32_t RESERVED4[4];
    uint32_t JDR1;
    uint32_t JDR2;
    uint32_t JDR3;
    uint32_t JDR4;
    uint32_t RESERVED5[5];
    uint32_t AWD2CR;
    uint32_t AWD3CR;
    uint32_t RESERVED6[2];
    uint32_t DIFSEL;
    uint32_t CALFACT;
} ADC_REG_BLOCKS;

typedef struct {
    uint32_t CSR;
    uint32_t RESERVED;
    uint32_t CCR;
    uint32_t CDR;
} ADC_COMMON_REG_BLOCKS;

/* ADC registers as structs */

#define ADC1 ( (ADC_REG_BLOCKS volatile *) 0x50040000 )
#define ADC2 ( (ADC_REG_BLOCKS volatile *) 0x50040100 )
#define ADC_COMMON ( (ADC_COMMON_REG_BLOCKS volatile * ) 0x50043000 )

/* ADC ISR register macros */

#define ADC_ISR_ADRDY(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_ISR_ADRDY_MASK ADC_ISR_ADRDY(ALL1)


#endif

