#ifndef STM32L432KC_FLASH_H
#define STM32L432KC_FLASH_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t ACR;
    uint32_t PDKEYR;
    uint32_t KEYR;
    uint32_t OPTKEYR;
    uint32_t SR;
    uint32_t CR;
    uint32_t ECCR;
    uint32_t OPTR;
    uint32_t PCROP1SR;
    uint32_t PCROP1ER;
    uint32_t WRP1AR;
} FLASH_REG_BLOCKS;

/* Flash registers as structs */

#define FLASH ( (FLASH_REG_BLOCKS volatile *) 0x40022000 )

/* Flash ACR register macros */

#define FLASH_ACR_LATENCY(v) ( ( (v) & 0x7 ) << 0 )
#define FLASH_ACR_LATENCY_MASK FLASH_ACR_LATENCY(ALL1)
#define FLASH_ACR_PRFTEN(v) ( ( (v) & 0x1 ) << 8 )
#define FLASH_ACR_PRFTEN_MASK FLASH_ACR_LATENCY(ALL1)
#define FLASH_ACR_ICEN(v) ( ( (v) & 0x1 ) << 9 )
#define FLASH_ACR_ICEN_MASK FLASH_ACR_ICEN(ALL1)
#define FLASH_ACR_DCEN(v) ( ( (v) & 0x1 ) << 10 )
#define FLASH_ACR_DCEN_MASK FLASH_ACR_DCEN(ALL1)
#define FLASH_ACR_ICRST(v) ( ( (v) & 0x1 ) << 11 )
#define FLASH_ACR_ICRST_MASK FLASH_ACR_ICRST(ALL1)
#define FLASH_ACR_DCRST(v) ( ( (v) & 0x1 ) << 12 )
#define FLASH_ACR_DCRST_MASK FLASH_ACR_DCRST(ALL1)
#define FLASH_ACR_RUN_PD(v) ( ( (v) & 0x1 ) << 13 )
#define FLASH_ACR_RUN_PD_MASK FLASH_ACR_RUN_PD(ALL1)
#define FLASH_ACR_SLEEP_PD(v) ( ( (v) & 0x1 ) << 14 )
#define FLASH_ACR_SLEEP_PD_MASK FLASH_ACR_SLEEP_PD(ALL1)

/* Flash PDKEYR register macros */

#define FLASH_PDKEYR_PDKEYR(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define FLASH_PDKEYR_PDKEYR_MASK FLASH_PDKEYR_PDKEYR(ALL1)

/* Flash KEYR register macros */

#define FLASH_KEYR_KEYR(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define FLASH_KEYR_KEYR_MASK FLASH_KEYR_KEYR(ALL1)

/* Flash OPTKEYR register macros */

#define FLASH_OPTKEYR_OPTKEYR(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define FLASH_OPTKEYR_OPTKEYR_OPTMASK FLASH_OPTKEYR_OPTKEYR(ALL1)

/* Flash SR register macros */

#define FLASH_SR_EOP(v) ( ( (v) & 0x1 ) << 0 )
#define FLASH_SR_EOP_MASK FLASH_SR_EOP(ALL1)
#define FLASH_SR_OPERR(v) ( ( (v) & 0x1 ) << 1 )
#define FLASH_SR_OPERR_MASK FLASH_SR_OPERR(ALL1)
#define FLASH_SR_PROGERR(v) ( ( (v) & 0x1 ) << 3 )
#define FLASH_SR_PROGERR_MASK FLASH_SR_PROGERR(ALL1)
#define FLASH_SR_WRPERR(v) ( ( (v) & 0x1 ) << 4 )
#define FLASH_SR_WRPERR_MASK FLASH_SR_WRPERR(ALL1)
#define FLASH_SR_PGAERR(v) ( ( (v) & 0x1 ) << 5 )
#define FLASH_SR_PGAERR_MASK FLASH_SR_PGAERR(ALL1)
#define FLASH_SR_SIZERR(v) ( ( (v) & 0x1 ) << 6 )
#define FLASH_SR_SIZERR_MASK FLASH_SR_PGSERR(ALL1)
#define FLASH_SR_PGSERR(v) ( ( (v) & 0x1 ) << 7 )
#define FLASH_SR_PGSERR_MASK FLASH_SR_PGSERR(ALL1)
#define FLASH_SR_MISTERR(v) ( ( (v) & 0x1 ) << 8 )
#define FLASH_SR_MISTERR_MASK FLASH_SR_MISTERR(ALL1)
#define FLASH_SR_FASTERR(v) ( ( (v) & 0x1 ) << 9 )
#define FLASH_SR_FASTERR_MASK FLASH_SR_FASTERR(ALL1)
#define FLASH_SR_RDERR(v) ( ( (v) & 0x1 ) << 14 )
#define FLASH_SR_RDERR_MASK FLASH_SR_RDERR(ALL1)
#define FLASH_SR_OPTVERR(v) ( ( (v) & 0x1 ) << 15 )
#define FLASH_SR_OPTVERR_MASK FLASH_SR_OPTVERR(ALL1)
#define FLASH_SR_BSY(v) ( ( (v) & 0x1 ) << 16 )
#define FLASH_SR_BSY_MASK FLASH_SR_BUSY(ALL1)
#define FLASH_SR_PEMPTY(v) ( ( (v) & 0x1 ) << 17 )
#define FLASH_SR_PEMPTY_MASK FLASH_SR_PEMPTY(ALL1)

/* Flash CR register macros */

#define FLASH_CR_PG(v) ( ( (v) & 0x1 ) << 0 )
#define FLASH_CR_PG_MASK FLASH_CR_PG(ALL1)
#define FLASH_CR_PER(v) ( ( (v) & 0x1 ) << 1 )
#define FLASH_CR_PER_MASK FLASH_CR_PER(ALL1)
#define FLASH_CR_MER1(v) ( ( (v) & 0x1 ) << 2 )
#define FLASH_CR_MER1_MASK FLASH_CR_MER1(ALL1)
#define FLASH_CR_PNB(v) ( ( (v) & 0xFF ) << 3 )
#define FLASH_CR_PNB_MASK FLASH_CR_PNB(ALL1)
#define FLASH_CR_STRT(v) ( ( (v) & 0x1 ) << 16 )
#define FLASH_CR_STRT_MASK FLASH_CR_STRT(ALL1)
#define FLASH_CR_OPT_STRT(v) ( ( (v) & 0x1 ) << 17 )
#define FLASH_CR_OPT_STRT_MASK FLASH_CR_OPT_STRT(ALL1)
#define FLASH_CR_FSTPG(v) ( ( (v) & 0x1 ) << 18 )
#define FLASH_CR_FSTPG_MASK FLASH_CR_FSTPG(ALL1)
#define FLASH_CR_EOPIE(v) ( ( (v) & 0x1 ) << 24 )
#define FLASH_CR_EOPIE_MASK FLASH_CR_EOPIE(ALL1)
#define FLASH_CR_ERRIE(v) ( ( (v) & 0x1 ) << 25 )
#define FLASH_CR_ERRIE_MASK FLASH_CR_ERRIE(ALL1)
#define FLASH_CR_RDERR_IE(v) ( ( (v) & 0x1 ) << 26 )
#define FLASH_CR_RDERR_IE_MASK FLASH_CR_RDERR_IE(ALL1)
#define FLASH_CR_OBL_LAUNCH(v) ( ( (v) & 0x1 ) << 27 )
#define FLASH_CR_OBL_LAUNCH_MASK FLASH_CR_OBL_LAUNCH(ALL1)
#define FLASH_CR_OPT_LOCK(v) ( ( (v) & 0x1 ) << 30 )
#define FLASH_CR_OPT_LOCK_MASK FLASH_CR_OPT_LOCK(ALL1)
#define FLASH_CR_LOCK(v) ( ( (v) & 0x1 ) << 31 )
#define FLASH_CR_LOCK_MASK FLASH_CR_LOCK(ALL1)

/* Flash ECCR register macros */

#define FLASH_ECCR_ADDR_ECC(v) ( ( (v) & 0x7FFFF ) << 0 )
#define FLASH_ECCR_ADDR_ECC_MASK FLASH_ECCR_ADDR_ECC(ALL1)
#define FLASH_ECCR_SYSF_ECC(v) ( ( (v) & 0x1 ) << 20 )
#define FLASH_ECCR_SYSF_ECC_MASK FLASH_ECCR_SYSF_ECC(ALL1)
#define FLASH_ECCR_ECCCIE(v) ( ( (v) & 0x1 ) << 24 )
#define FLASH_ECCR_ECCCIE_MASK FLASH_ECCR_ECCCIE(ALL1)
#define FLASH_ECCR_ECCC(v) ( ( (v) & 0x1 ) << 30 )
#define FLASH_ECCR_ECCC_MASK FLASH_ECCR_ECCC(ALL1)
#define FLASH_ECCR_ECCD(v) ( ( (v) & 0x1 ) << 31 )
#define FLASH_ECCR_ECCD_MASK FLASH_ECCR_ECCD(ALL1)

/* Flash OPTR register macros */

#define FLASH_OPTR_RDP(v) ( ( (v) & 0xFF ) << 0 )
#define FLASH_OPTR_RDP_MASK FLASH_OPTR_RDP(ALL1)
#define FLASH_OPTR_BOR_LEV(v) ( ( (v) & 0x7 ) << 8 )
#define FLASH_OPTR_BOR_LEV_MASK FLASH_OPTR_BOR_LEV(ALL1)
#define FLASH_OPTR_NRST_STOP(v) ( ( (v) & 0x1 ) << 12 )
#define FLASH_OPTR_NRST_STOP_MASK FLASH_OPTR_NRST_STOP(ALL1)
#define FLASH_OPTR_NRST_STDBY(v) ( ( (v) & 0x1 ) << 13 )
#define FLASH_OPTR_NRST_STDBY_MASK FLASH_OPTR_NRST_STDBY(ALL1)
#define FLASH_OPTR_NRST_SHDW(v) ( ( (v) & 0x1 ) << 14 )
#define FLASH_OPTR_NRST_SHDW_MASK FLASH_OPTR_NRST_SHDW(ALL1)
#define FLASH_OPTR_IWDG_SW(v) ( ( (v) & 0x1 ) << 16 )
#define FLASH_OPTR_IWDG_SW_MASK FLASH_OPTR_IWDG_SW(ALL1)
#define FLASH_OPTR_IWDG_STOP(v) ( ( (v) & 0x1 ) << 17 )
#define FLASH_OPTR_IWDG_STOP_MASK FLASH_OPTR_IWDG_STOP(ALL1)
#define FLASH_OPTR_IWDG_STDBY(v) ( ( (v) & 0x1 ) << 18 )
#define FLASH_OPTR_IWDG_STDBY_MASK FLASH_OPTR_IWDG_STDBY(ALL1)
#define FLASH_OPTR_WWDG_SW(v) ( ( (v) & 0x1 ) << 19 )
#define FLASH_OPTR_WWDG_SW_MASK FLASH_OPTR_WWDG_SW(ALL1)
#define FLASH_OPTR_NBOOT1(v) ( ( (v) & 0x1 ) << 23 )
#define FLASH_OPTR_NBOOT1_MASK FLASH_OPTR_NBOOT1(ALL1)
#define FLASH_OPTR_SRAM2_PE(v) ( ( (v) & 0x1 ) << 24 )
#define FLASH_OPTR_SRAM2_PE_MASK FLASH_OPTR_SRAM2_PE(ALL1)
#define FLASH_OPTR_SRAM2_RST(v) ( ( (v) & 0x1 ) << 25 )
#define FLASH_OPTR_SRAM2_RST_MASK FLASH_OPTR_SRAM2_RST(ALL1)
#define FLASH_OPTR_NSWBOOT0(v) ( ( (v) & 0x1 ) << 26 )
#define FLASH_OPTR_NSWBOOT0_MASK FLASH_OPTR_NSWBOOT0(ALL1)
#define FLASH_OPTR_NBOOT0(v) ( ( (v) & 0x1 ) << 27 )
#define FLASH_OPTR_NBOOT0_MASK FLASH_OPTR_NBOOT0(ALL1)

/* Flash PCROP1SR register macros */

#define FLASH_PCROP1SR_PCROP1_STRT(v) ( ( (v) & 0xFFFF ) << 0 )
#define FLASH_PCROP1SR_PCROP1_STRT_MASK FLASH_PCROP1SR_PCROP1_STRT(ALL1)

/* Flash PCROP1ER register macros */

#define FLASH_PCROP1ER_PCROP1_END(v) ( ( (v) & 0xFFFF ) << 0 )
#define FLASH_PCROP1ER_PCROP1_END_MASK FLASH_PCROP1ER_PCROP1_END(ALL1)
#define FLASH_PCROP1ER_PCROP_RDP(v) ( ( (v) & 0x1 ) << 31 )
#define FLASH_PCROP1ER_PCROP_RDP_MASK FLASH_PCROP1ER_PCROP_RDP(ALL1)

/* Flash WRP1AR register macros */

#define FLASH_WRP1AR_WRP1A_STRT(v) ( ( (v) & 0xFF ) << 0 )
#define FLASH_WRP1AR_WRP1A_STRT_MASK FLASH_WRP1AR_WRP1A_STRT(ALL1)
#define FLASH_WRP1AR_WRP1A_END(v) ( ( (v) & 0xFF ) << 16 )
#define FLASH_WRP1AR_WRP1A_END_MASK FLASH_WRP1AR_WRP1A_END(ALL1)

/* Flash WRP1BR register macros */

#define FLASH_WRP1BR_WRP1B_STRT(v) ( ( (v) & 0xFF ) << 0 )
#define FLASH_WRP1BR_WRP1B_STRT_MASK FLASH_WRP1BR_WRP1B_STRT(ALL1)
#define FLASH_WRP1BR_WRP1B_END(v) ( ( (v) & 0xFF ) << 16 )
#define FLASH_WRP1BR_WRP1B_END_MASK FLASH_WRP1BR_WRP1B_END(ALL1)

#endif

