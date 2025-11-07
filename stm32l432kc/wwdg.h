#ifndef STM32L432KC_WWDG_H
#define STM32L432KC_WWDG_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CR;
    uint32_t CFR;
    uint32_t SR;
} WWDG_REG_BLOCKS;

/* WWDG registers as structs */

#define WWDG ( (WWDG_REG_BLOCKS volatile *) 0x40002C00 )

/* WWDG CR register macros */

#define WWDG_CR_T(v) ( ( (v) & 0x7F ) << 0 )
#define WWDG_CR_T_MASK WWDG_CR_T(ALL1)
#define WWDG_CR_WDGA(v) ( ( (v) & 0x1 ) << 7 )
#define WWDG_CR_WDGA_MASK WWDG_CR_WDGA(ALL1)

/* WWDG CFR register macros */

#define WWDG_CFR_W(v) ( ( (v) & 0x3F ) << 0 )
#define WWDG_CFR_W_MASK WWDG_CFG_W(ALL1)
#define WWDG_CFR_WDGTB(v) ( ( (v) & 0x3 ) << 7)
#define WWDG_CFR_WDGTB_MASK WWDG_CFR_WDGTB(ALL1)
#define WWDG_CFR_EWI(v) ( ( (v) & 0x1 ) << 9 )
#define WWDG_CFR_EWI_MASK WWDG_CFR_EWI(ALL1)

/* WWDG SR register macros */

#define WWDG_SR_EWIF(v) ( ( (v) & 0x1 ) << 0 )
#define WWDG_SR_EWIF_MASK WWDG_SR_EWIF(ALL1)

#endif

