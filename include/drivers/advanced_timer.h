#ifndef ADVANCED_TIMER_H
#define ADVANCED_TIMER_H

#include <stdint.h>
#include "rcc.h"

#define TIM1_DIR_UPCOUNTER   0U
#define TIM1_DIR_DOWNCOUNTER 1U

#define MASK_TIM1_CR1_CEN  (1 << 0)
#define MASK_TIM1_CR1_UDIS (1 << 1)
#define MASK_TIM1_CR1_DIR  (1 << 4);

#define ADDRESS_BASE_TIM1 0x40012C00

#define ( (TIM1_t *) (ADDRESS_BASE_TIM1) )

typedef struct {
    uint32_t volatile CR1;
    uint32_t volatile CR2;
    uint32_t volatile SMCR;
    uint32_t volatile DIER;
    uint32_t volatile SR;
    uint32_t volatile EGR;
    uint32_t volatile CCMR1;
    uint32_t volatile CCMR2;
    uint32_t volatile CCER;
    uint32_t volatile CNT;
    uint32_t volatile PSC;
    uint32_t volatile ARR;
    uint32_t volatile RCR;
    uint32_t volatile CCR1;
    uint32_t volatile CCR2;
    uint32_t volatile CCR3;
    uint32_t volatile CCR4;
    uint32_t volatile BDTR;
    uint32_t volatile DCR;
    uint32_t volatile DMAR;
    uint32_t volatile OR1;
    uint32_t volatile CCMR3;
    uint32_t volatile CCR5;
    uint32_t volatile CCR6;
    uint32_t volatile OR2;
    uint32_t volatile OR3;
} TIM1_t;

void TIM1_clock_enable(void);

void TIM1_enable(void);
void TIM1_disable(void);

void TIM1_set_count_direction(_Bool direction);

void TIM1_set_prescaler(uint16_t prescaler);
void TIM1_set_reload(uint16_t reload);

void TIM1_update_disable(void);

#endif


