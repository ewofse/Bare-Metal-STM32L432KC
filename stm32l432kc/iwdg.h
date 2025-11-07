#ifndef STM32L432KC_IWDG_H
#define STM32L432KC_IWDG_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t KR;
    uint32_t PR;
    uint32_t RLR;
    uint32_t SR;
    uint32_t WINR;
} IWDG_REG_BLOCKS;

/* IWDG registers as structs */

#define IWDG ( (IWDG_REG_BLOCKS volatile *) 0x40003000 )

/* IWDG KR register macros */

#define IWDG_KR_KEY(v) ( ( (v) & 0xFFFF ) << 0 )
#define IWDG_KR_KEY_MASK IWDG_KR_KEY(ALL1)

/* IWDG PR register as marcos */

#define IWDG_PR_PR(v) ( ( (v) & 0x3 ) << 0 )
#define IWDG_PR_PR_MASK IWDG_PR_PR(ALL1)

/* IWDG RLR register macros */

#define IWDG_RLR_RL(v) ( ( (v) & 0xFFF ) << 0 )
#define IWDG_RLR_RL_MASK IWDG_RLR_RL(ALL1)

/* IWDG SR register macros */

#define IWDG_SR_PVU(v) ( ( (v) & 0x1 ) << 0 )
#define IWDG_SR_PVU_MASK IWDG_SR_PVU(ALL1)
#define IWDG_SR_RVU(v) ( ( (v) & 0x1 ) << 1 )
#define IWDG_SR_RVU_MASK IWDG_SR_RVU(ALL1)
#define IWDG_SR_WVU(v) ( ( (v) & 0x1 ) << 2 )
#define IWDG_SR_WVU_MASK IWDG_SR_WVU(ALL1)

/* IWDG WINR register macros */

#define IWDG_WINR_WIN(v) ( ( (v) & 0xFFF ) << 0 )
#define IWDG_WINR_WIN_MASK IWDG_WINR_WIN(ALL1)

#endif

