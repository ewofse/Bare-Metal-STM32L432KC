#include "watchdog.h"
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

// IWDG prescaler LUT
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

void configure_independent_watchdog(void) {
    // Enable LSI clock
    RCC->CSR |= RCC_CSR_LSION(1);
    while ( !(RCC->CSR & RCC_CSR_LSIRDY_MASK) );

    // Wait for the watchdog to be ready to update the prescaler and reload value
    while ( IWDG->SR & (IWDG_SR_PVU_MASK | IWDG_SR_RVU_MASK) );

    // Set the watchdog key to enable write access
    IWDG->KR = IWDG_KR_KEY(0x5555);
    
    // Set prescaler and counter reload value
    IWDG->PR = IWDG_PR_PR(IWDG_PR);
    IWDG->RLR = IWDG_RLR_RL(IWDG_TOP);

    // Begin down counting
    IWDG->KR = IWDG_KR_KEY(0xCCCC);
}

void feed_the_independent_watchdog(void) {
    // Write to key register for hardware to reload counter
    IWDG->KR = IWDG_KR_KEY(0xAAAA);
}

void configure_window_watchdog(void) {
    // Clear the pending interrupt
    WWDG->SR = WWDG_SR_EWIF(0);

    // Enable interrupt and set prescaler and window
    WWDG->CFR = WWDG_CFR_EWI(1) | WWDG_CFR_WDGTB(WWDG_PR) | WWDG_CFR_W(WWDG_W);

    // Enable the watchdog and set reload top value
    WWDG->CR = WWDG_CR_WDGA(1) | WWDG_CR_T(0x40 | WWDG_T);
}

void feed_the_window_watchdog(void) {
    // Reload down counter
    WWDG->CR |= WWDG_CR_T(0x40 | WWDG_T);
}

_Bool register_window_watchdog_callback( void (*cb)(void) ) {
    if (num_callbacks == NUM_WWDG_CALLBACKS) {
        return false;
    } 

    callback[num_callbacks++] = cb;

    return true;
}

void __attribute__( (interrupt) ) WWDG_Handler(void) {
    for (uint32_t i = 0; i < num_callbacks; i++) {
        callback[i]();
    }
} 

