#include "watchdog.h"
#include <m4/nvic.h>
#include <stm32l432kc/iwdg.h>
#include <stm32l432kc/wwdg.h>
#include <stm32l432kc/rcc.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef IWDG_FREQ_HZ
#define IWDG_FREQ_HZ 1000
#endif

#ifndef IWDG_PR
#define IWDG_PR 0 
#endif

#define IWDG_EXT_FREQ_HZ ( 32000 / IWDG_PR_PR_LUT[IWDG_PR] )

#define IWDG_TOP (IWDG_EXT_FREQ_HZ / IWDG_FREQ_HZ - 1)

#ifndef WWDG_PR
#define WWDG_PR 0
#endif

// Value of T[5:0] - T[6] will always be reloaded with value of 1
#ifndef WWDG_T
#define WWDG_T 63 
#endif

#ifndef WWDG_W
#define WWDG_W 63
#endif

#ifndef NUM_WWDG_CALLBACKS
#define NUM_WWDG_CALLBACKS 5
#endif

#define WWDG_IRQ 0
#define WWDG_IRQ_PRI 7

static uint16_t const IWDG_PR_PR_LUT[8] = {
    4,
    8,
    16,
    32,
    64,
    128,
    256,
    256
};

static void ( *callback[NUM_WWDG_CALLBACKS] )(void);
static uint32_t num_callbacks;

/* Set IWDG timeout period */

void configure_independent_watchdog(void) {
    // LSI clock must be used for IWDG (32 kHz)
    RCC->CSR |= RCC_CSR_LSION(1);
    while ( !(RCC->CSR & RCC_CSR_LSIRDY_MASK) );

    /* Update prescaler and reload value */

    while ( IWDG->SR & (IWDG_SR_PVU_MASK | IWDG_SR_RVU_MASK) );

    IWDG->KR = IWDG_KR_KEY(0x5555);
    
    IWDG->PR = IWDG_PR_PR(IWDG_PR);
    IWDG->RLR = IWDG_RLR_RL(IWDG_TOP);

    IWDG->KR = IWDG_KR_KEY(0xCCCC);
}

/* Reload IWDG counter */

void feed_the_independent_watchdog(void) {
    IWDG->KR = IWDG_KR_KEY(0xAAAA);
}

/* Setup WWDG window timeout period */

void configure_window_watchdog(void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_WWDGEN(1);

    NVIC->ISER[0] = NVIC_ISER_SETENA(1, WWDG_IRQ);

    WWDG->SR = WWDG_SR_EWIF(0);
    
    WWDG->CFR = 
        WWDG_CFR_EWI(1) 
      | WWDG_CFR_WDGTB(WWDG_PR) 
      | WWDG_CFR_W(WWDG_W);
    
    WWDG->CR = 
        WWDG_CR_WDGA(1)
      | WWDG_CR_T(0x40 | WWDG_T);

    NVIC->IPR[0] = 
        (NVIC->IPR[0] & ~NVIC_IPR0_PRI_0_MASK) 
      | NVIC_IPR0_PRI_0(WWDG_IRQ_PRI);
}

/* Reload WWDG counter */

void feed_the_window_watchdog(void) {
    WWDG->CR |= WWDG_CR_T(0x40 | WWDG_T);
}

/* Add callback to WWDG ISR */

_Bool register_window_watchdog_callback( void (*cb)(void) ) {
    if (num_callbacks == NUM_WWDG_CALLBACKS) {
        return false;
    } 

    callback[num_callbacks++] = cb;

    return true;
}

/* WWDG ISR */

void __attribute__( (interrupt) ) WWDG_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, 0);

    for (uint32_t i = 0; i < num_callbacks; i++) {
        callback[i]();
    }
} 

