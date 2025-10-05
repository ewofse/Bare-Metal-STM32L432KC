#ifndef M4_SYSTICK_H 
#define M4_SYSTICK_H 

#include <stdint.h>

typedef struct {
    uint32_t CSR;
    uint32_t RVR;
    uint32_t CVR;
    uint32_t CALIB;
} SYSTICK_REG_BLOCKS;

/* SysTick registers as structs */

#define SYSTICK ( (SYSTICK_REG_BLOCKS volatile *) 0xE000E010 )

/* SysTick control and status register macros */

#define SYST_CSR_ENABLE_MASK    (1 << 0)
#define SYST_CSR_TICKINT_MASK   (1 << 1)
#define SYST_CSR_CLKSOURCE_MASK (1 << 2)
#define SYST_CSR_COUNTFLAG_MASK (1 << 16)

/* SysTick reload value register macros */

#define SYST_RVR_RELOAD_MASK 0x00FFFFFF

/* SysTick current value register macros */

#define SYST_CVR_CURRENT_MASK 0x00FFFFFF

/* SysTick calibration value register macros */

#define SYST_CVR_TENMS_MASK (1 << 23)
#define SYST_CVR_SKEW_MASK  (1 << 30)
#define SYST_CVR_NOREF_MASK (1 << 31)

#endif

