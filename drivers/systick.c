#include "systick.h"
#include <stdint.h>
#include <stdbool.h>
#include "../M4/systick.h"

#ifndef SYSTICK_FREQ_HZ
#define SYSTICK_FREQ_HZ 1
#endif

#ifndef EXT_CLK_FREQ_HZ
#define EXT_CLK_FREQ_HZ 2000000 
#endif

#define SYSTICK_TOP (EXT_CLK_FREQ_HZ / SYSTICK_FREQ_HZ - 1)

void configure_systick(void) {
    SYSTICK->RVR = SYSTICK_TOP; 
    SYSTICK->CVR = 0;
    SYSTICK->CSR = SYST_CSR_ENABLE(1) | SYST_CSR_CLKSOURCE(1);
}

_Bool systick_has_fired(void) {
    return SYSTICK->CSR & SYST_CSR_COUNTFLAG_MASK;
}

