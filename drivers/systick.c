#include "systick.h"
#include "interrupt.h"
#include <m4/systick.h>
#include <m4/scb.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef SYSTICK_FREQ_HZ
#define SYSTICK_FREQ_HZ 2000
#endif

#ifndef EXT_CLK_FREQ_HZ
#define EXT_CLK_FREQ_HZ 2000000 
#endif

#define SYSTICK_TOP (EXT_CLK_FREQ_HZ / SYSTICK_FREQ_HZ - 1)

#ifndef NUM_SYSTICK_CALLBACKS
#define NUM_SYSTICK_CALLBACKS 5
#endif

static void ( *callback[NUM_SYSTICK_CALLBACKS] )(void);
static uint32_t num_callbacks;
static uint64_t volatile tick_counter;
static _Bool volatile systick_fired_flag;

void configure_systick(void) {
    SYSTICK->RVR = SYSTICK_TOP; 
    SYSTICK->CVR = 0;
    
    SYSTICK->CSR = 
        SYST_CSR_ENABLE(1) 
      | SYST_CSR_TICKINT(1) 
      | SYST_CSR_CLKSOURCE(1);

    SCB->SHPR3 = (SCB->SHPR3 & ~SCB_SHPR3_PRI_15_MASK) | SCB_SHPR3_PRI_15(0);
}

_Bool systick_has_fired(void) {
    _Bool retval = systick_fired_flag;
    systick_fired_flag = false;

    return retval;
}

_Bool register_systick_callback( void (*cb)(void) ) {
    if (num_callbacks == NUM_SYSTICK_CALLBACKS) {
        return false;
    }

    callback[num_callbacks++] = cb;

    return true;
}

uint64_t get_system_time(void) {
    return tick_counter;
}

void __attribute__( (interrupt) ) SYSTICK_Handler(void) {
    systick_fired_flag = true;

    uint32_t primask;

    get_primask(&primask);
    disable_irq();

    tick_counter++;

    set_primask(primask);

    for (uint32_t i = 0; i < num_callbacks; i++) {
        callback[i]();
    }
}

