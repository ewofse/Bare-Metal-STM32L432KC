#ifndef STM32L432KC_CRS_H
#define STM32L432KC_CRS_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CR;
    uint32_t CFGR;
    uint32_t ISR;
    uint32_t ICR;
} CRS_REG_BLOCKS;

/* CRS registers as structs */

#define CRS ( (CRS_REG_BLOCKS * volatile) 0x40006000 )

/* CRS CR register macros */

#define CRS_CR_SYNCOKIE(v) ( ( (v) & 0x1 ) << 0 )
#define CRS_CR_SYNCOKIE_MASK CRS_CR_SYNCOKIE(ALL1)
#define CRS_CR_SYNCWARNIE(v) ( ( (v) & 0x1 ) << 1 )
#define CRS_CR_SYNCWARNIE_MASK CRS_CR_SYNCWARNIE(ALL1)
#define CRS_CR_ERRIE(v) ( ( (v) & 0x1 ) << 2 )
#define CRS_CR_ERRIE_MASK CRS_CR_ERRIE(ALL1)
#define CRS_CR_ESYNCIE(v) ( ( (v) & 0x1 ) << 3 )
#define CRS_CR_ESYNCIE_MASK CRS_CR_ESYNCIE(ALL1)
#define CRS_CR_CEN(v) ( ( (v) & 0x1 ) << 5 )
#define CRS_CR_CEN_MASK CRS_CR_CEN(ALL1)
#define CRS_CR_AUTOTRIMEN(v) ( ( (v) & 0x1 ) << 6 )
#define CRS_CR_AUTOTRIMEN_MASK CRS_CR_AUTOTRIMEN(ALL1)
#define CRS_CR_SWSYNC(v) ( ( (v) & 0x1 ) << 7 )
#define CRS_CR_SWSYNC_MASK CRS_CR_SWSYNC(ALL1)
#define CRS_CR_TRIM(v) ( ( (v) & 0x3F ) << 8 )
#define CRS_CR_TRIM_MASK CRS_CR_TRIM(ALL1)

/* CRS CFGR register macros */

#define CRS_CFGR_RELOAD(v) ( ( (v) & 0xFFFF ) << 0 )
#define CRS_CFGR_RELOAD_MASK CRS_CFGR_RELOAD(ALL1)
#define CRS_CFGR_FELIM(v) ( ( (v) & 0xFF ) << 16 )
#define CRS_CFGR_FELIM_MASK CRS_CFGR_FELIM(ALL1)
#define CRS_CFGR_SYNCDIV(v) ( ( (v) & 0x7 ) << 24 )
#define CRS_CFGR_SYNCDIV_MASK CRS_CFGR_SYNCDIV(ALL1)
#define CRS_CFGR_SYNCSRC(v) ( ( (v) & 0x3 ) << 28 )
#define CRS_CFGR_SYNCSRC_MASK CRS_CFGR_SYNCSRC(ALL1)
#define CRS_CFGR_SYNCPOL(v) ( ( (v) & 0x1 ) << 31 )
#define CRS_CFGR_SYNCPOL_MASK CRS_CFGR_SYNCPOL(ALL1)

/* CRS ISR register macros */

#define CRS_ISR_SYNCOKF(v) ( ( (v) & 0x1 ) << 0 )
#define CRS_ISR_SYNCOKF_MASK CRS_ISR_SYNCOKF(ALL1)
#define CRS_ISR_SYNCWARNF(v) ( ( (v) & 0x1 ) << 1 )
#define CRS_ISR_SYNCWARNF_MASK CRS_ISR_SYNCWARNF(ALL1)
#define CRS_ISR_ERRF(v) ( ( (v) & 0x1 ) << 2 )
#define CRS_ISR_ERRF_MASK CRS_ISR_ERRF(ALL1)
#define CRS_ISR_ESYNCF(v) ( ( (v) & 0x1 ) << 3 )
#define CRS_ISR_ESYNCF_MASK CRS_ISR_ESYNCF(ALL1)
#define CRS_ISR_SYNCERR(v) ( ( (v) & 0x1 ) << 8 )
#define CRS_ISR_SYNCERR_MASK CRS_ISR_SYNCERR(ALL1)
#define CRS_ISR_SYNCMISS(v) ( ( (v) & 0x1 ) << 9 )
#define CRS_ISR_SYNCMISS CRS_ISR_SYNCMISS(ALL1)
#define CRS_ISR_TRIMOVF(v) ( ( (v) & 0x1 ) << 10 )
#define CRS_ISR_TRIMOVF CRS_ISR_TRIMOVF(ALL1)
#define CRS_ISR_FEDIR(v) ( ( (v) & 0x1 ) << 15 )
#define CRS_ISR_FEDIR_MASK CRS_ISR_FEDIR(ALL1)
#define CRS_ISR_FECAP(v) ( ( (v) & 0xFFFF ) << 16 )
#define CRS_ISR_FECAP_MASK CRS_ISR_FECAP(ALL1)

/* CRS ICR register macros */

#define CRS_ICR_SYNCOKC(v) ( ( (v) & 0x1 ) << 0 )
#define CRS_ICR_SYNCOKC_MASK CRS_ICR_SYNCOK(ALL1)
#define CRS_ICR_SYNCWARNC(v) ( ( (v) & 0x1 ) << 1 )
#define CRS_ICR_SYNCWARNC_MASK CRS_ICR_SYNCWARN(ALL1)
#define CRS_ICR_ERRC(v) ( ( (v) & 0x1 ) << 2 )
#define CRS_ICR_ERRC_MASK CRS_ICR_ERRC(ALL1)
#define CRS_ICR_ESYNCC(v) ( ( (v) & 0x1 ) << 3 )
#define CRS_ICR_ESYNCC_MASK CRS_ICR_ESYNCC(ALL1)

#endif

