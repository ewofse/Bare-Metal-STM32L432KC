#ifndef M4_SYSTICK_H 
#define M4_SYSTICK_H 

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CSR;
    uint32_t RVR;
    uint32_t CVR;
    uint32_t CALIB;
} SYSTICK_REG_BLOCKS;

/* SysTick registers as structs */

#define SYSTICK ( (SYSTICK_REG_BLOCKS volatile *) 0xE000E010 )

/* SysTick control and status register macros */

#define SYST_CSR_ENABLE(v) ( ( (v) & 0x1 ) << 0 )
#define SYST_CSR_ENABLE_MASK SYST_CST_ENABLE(ALL1)
#define SYST_CSR_TICKINT(v) ( ( (v) & 0x1 ) << 1 )
#define SYST_CSR_TICKINT_MASK SYST_CSR_TICKINT(ALL1)
#define SYST_CSR_CLKSOURCE(v) ( ( (v) & 0x1 ) << 2 )
#define SYST_CSR_CLKSOURCE_MASK SYST_CSR_CLKSOURCE(ALL1)
#define SYST_CSR_COUNTFLAG(v) ( ( (v) & 0x1 ) << 16 )
#define SYST_CSR_COUNTFLAG_MASK SYST_CSR_COUNTFLAG(ALL1)

/* SysTick reload value register macros */

#define SYST_RVR_RELOAD(v) ( ( (v) & 0x00FFFFFF ) << 0 )
#define SYST_RVR_RELOAD_MASK SYST_RVR_RELOAD(ALL1) 

/* SysTick current value register macros */

#define SYST_CVR_CURRENT(v) ( ( (v) & 0x00FFFFFF ) << 0 )
#define SYST_CVR_CURRENT_MASK SYST_CVR_CURRENT(ALL1) 

/* SysTick calibration value register macros */

#define SYST_CALIB_TENMS(v) ( ( (v) & 0x1 ) << 23 )
#define SYST_CALIB_TENMS_MASK SYST_CALIB_TENMS(ALL1)
#define SYST_CALIB_SKEW(v) ( ( (v) & 0x1 ) << 30 )
#define SYST_CALIB_SKEW_MASK SYST_CALIB_SKEW(ALL1)
#define SYST_CALIB_NOREF(v) ( ( (v) & 0x1 ) << 31 )
#define SYST_CALIB_NOREF_MASK SYST_CALIB_NOREF(ALL1)

#endif

