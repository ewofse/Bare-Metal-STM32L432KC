
#ifndef M4_SCB_H
#define M4_SCB_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t ACTLR;
    uint32_t RESERVED;
    uint32_t CPUID;
    uint32_t ICSR;
    uint32_t VTOR;
    uint32_t AIRCR;
    uint32_t SCR;
    uint32_t CCR;
    uint32_t SHPR1;
    uint32_t SHPR2;
    uint32_t SHPR3;
    uint32_t SHCRS;
    uint32_t CFSR;
    uint32_t HFSR;
    uint32_t MMAR;
    uint32_t BFAR;
    uint32_t AFSR;
} SCB_REG_BLOCKS;

/* System control block registers as structs */

#define SCB ( (SCB_REG_BLOCKS volatile *) 0xE000E008 )

/* Auxiliary control register macros */

#define SCB_ACTLR_DISMCYCINT(v) ( ( (v) & 0x1 ) << 0 )
#define SCB_ACTLR_DISMCYCINT_MASK SCB_ACTLR_DISMCYCINT(ALL1)
#define SCB_ACTLR_DISDEFWBUF(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_ACTLR_DISDEFWBUF_MASK SCB_ACTLR_DISDEFWBUF(ALL1)
#define SCB_ACTLR_DISFOLD(v) ( ( (v) & 0x1 ) << 2 )
#define SCB_ACTLR_DISFOLD_MASK SCB_ACTLR_DISFOLD(ALL1)

/* CPU ID register macros */

#define SCB_CPUID_IMPLEMENTER(v) ( ( (v) & 0xFF ) << 24 )
#define SCB_CPUID_IMPLEMENTER_MASK SCB_CPUID_IMPLEMENTER(ALL1)
#define SCB_CPUID_VARIANT(v) ( ( (v) & 0xF ) << 20 )
#define SCB_CPUID_VARIANT_MASK SCB_CPUID_VARIANT(ALL1)
#define SCB_CPUID_CONSTANT(v) ( ( (v) & 0xF ) << 16 )
#define SCB_CPUID_CONSTANT_MASK SCB_CPUID_CONSTANT(ALL1)
#define SCB_CPUID_PARTNO(v) ( ( (v) & 0xFFF ) << 4 )
#define SCB_CPUID_PARTNO_MASK SCB_CPUID_PARTNO(ALL1)
#define SCB_CPUID_REVISION(v) ( ( (v) & 0xF ) << 0 )
#define SCB_CPUID_REVISION_MASK SCB_CPUID_REVISION(ALL1)

/* Interrupt control and state register macros */

#define SCB_ICSR_VECTACTIVE(v) ( ( (v) & 0xFF ) << 0 )
#define SCB_ICSR_VECTACTIVE_MASK SCB_ICSR_VECTACTIVE(ALL1)
#define SCB_ICSR_VETTOBASE(v) ( ( (v) & 0x1 ) << 11 )
#define SCB_ICSR_VETTOBASE_MASK SCB_ICSR_VETTOBASE(ALL1)
#define SCB_ICSR_VECTPENDING(v) ( ( (v) & 0x3F ) << 12 )
#define SCB_ICSR_VECTPENDING_MASK SCB_ICSR_VECTPENDING(ALL1)
#define SCB_ICSR_ISRPENDING(v) ( ( (v) & 0x1 ) << 22 )
#define SCB_ICSR_ISRPENDING_MASK SCB_ICSR_ISRPENDING(ALL1)
#define SCB_ICSR_PENDSTCLR(v) ( ( (v) & 0x1 ) << 25 )
#define SCB_ICSR_PENDSTCLR_MASK SCB_ICSR_PENDSTCLR(ALL1)
#define SCB_ICSR_PENDSTSET(v) ( ( (v) & 0x1 ) << 26 )
#define SCB_ICSR_PENDSTSET_MASK SCB_ICSR_PENDSTSET(ALL1)
#define SCB_ICSR_PENDSVCLR(v) ( ( (v) & 0x1 ) << 27 )
#define SCB_ICSR_PENDSVCLR_MASK SCB_ICSR_PENDSVCLR(ALL1)
#define SCB_ICSR_PENDSVSET(v) ( ( (v) & 0x1 ) << 28 )
#define SCB_ICSR_PENDSVSET_MASK SCB_ICSR_PENDSVSET(ALL1)
#define SCB_ICSR_NMIPENDEN(v) ( ( (v) & 0x1 ) << 31 )
#define SCB_ICSR_NMIPENDEN_MASK SCB_ICSR_NMIPENDEN(ALL1)

/* Vector table offset register macros */

#define SCB_VTOR_TBLOFF(v) ( ( (v) & 0x3FFFFF ) << 7 )
#define SCB_VTOR_TBLOFF_MASK SCB_VTOR_TBLOFF(ALL1)

/* Application interrupt and reset control register */

#define SCB_AIRCR_VECTRESET(v) ( ( (v) & 0x1 ) << 0 )
#define SCB_AIRCR_VECTRESET_MASK SCB_AIRCR_VECTRESET(ALL1)
#define SCB_AIRCR_VECTCLRACTIVE(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_AIRCR_VECTCLRACTIVE_MASK SCB_AIRCR_VECTCLRACTIVE(ALL1)
#define SCB_AIRCR_SYSRESETREQ(v) ( ( (v) & 0x1 ) << 2 )
#define SCB_AIRCR_SYSRESETREQ_MASK SCB_AIRCR_SYSRESETREQ(ALL1)
#define SCB_AIRCR_PRIGROUP(v) ( ( (v) & 0x7 ) << 8 )
#define SCB_AIRCR_PRIGROUP_MASK SCB_AIRCR_PRIGROUP(ALL1)
#define SCB_AIRCR_ENDIANNESS(v) ( ( (v) & 0x1 ) << 15 )
#define SCB_AIRCR_ENDIANNESS_MASK SCB_AIRCR_ENDIANNESS(ALL1)
#define SCB_AIRCR_VECTKEY(v) ( ( (v) & 0xFFFF ) << 16 )
#define SCB_AIRCR_VECTKEY_MASK SCB_AIRCR_VECTKEY(ALL1)

/* System control register macros */

#define SCB_SCR_SLEEPONEXIT(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_SCR_SLEEPONEXIT_MASK SCB_SCR_SLEEPONEXIT(ALL1)
#define SCB_SCR_SLEEPDEEP(v) ( ( (v) & 0x1 ) << 2 )
#define SCB_SCR_SLEEPDEEP_MASK SCB_SCR_SLEEPDEEP(ALL1)
#define SCB_SCR_SEVONPEND(v) ( ( (v) & 0x1 ) << 4 )
#define SCB_SCR_SEVONPEND_MASK SCB_SCR_SEVONPEND(ALL1)

/* Configuration and control register macros */

#define SCB_CCR_NONBASETHRDENA(v) ( ( (v) & 0x1 ) << 0 )
#define SCB_CCR_NONBASETHRDENA_MASK SCB_CCR_NONBASETHRDENA(ALL1)
#define SCB_CCR_USERSETMPEND(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_CCR_USERSETMPEND_MASK SCB_CCR_USERSETMPEND(ALL1)
#define SCB_CCR_UNALIGN_TRP(v) ( ( (v) & 0x1 ) << 3 )
#define SCB_CCR_UNALIGN_TRP_MASK SCB_CCR_UNALIGN_TRP(ALL1)
#define SCB_CCR_DIV_0_TRP(v) ( ( (v) & 0x1 ) << 4 )
#define SCB_CCR_DIV_0_TRP_MASK SCB_CCR_DIV_0_TRP(ALL1)
#define SCB_CCR_BFHFNMIGN(v) ( ( (v) & 0x1 ) << 8 )
#define SCB_CCR_BFHFNMIGN_MASK SCB_CCR_BFHFNMIGN(ALL1)
#define SCB_CCR_STKALIGN(v) ( ( (v) & 0x1 ) << 9 )
#define SCB_CCR_STKALIGN_MASK SCB_CCR_STKALIGN(ALL1)

/* System handler priority register 1 macros */

#define SCB_SHPR1_PRI_4(v) ( ( (v) & 0xFF ) << 0 )
#define SCB_SHPR1_PRI_4_MASK SCB_SHPR1_PRI_4(ALL1)
#define SCB_SHPR1_PRI_5(v) ( ( (v) & 0xFF ) << 8 )
#define SCB_SHPR1_PRI_5_MASK SCB_SHPR1_PRI_5(ALL1)
#define SCB_SHPR1_PRI_6(v) ( ( (v) & 0xFF ) << 16 )
#define SCB_SHPR1_PRI_6_MASK SCB_SHPR1_PRI_6(ALL1)
#define SCB_SHPR1_PRI_7(v) ( ( (v) & 0xFF ) << 24 )
#define SCB_SHPR1_PRI_7_MASK SCB_SHPR1_PRI_7(ALL1)

/* System handler priority register 2 macros */

#define SCB_SHPR2_PRI_8(v) ( ( (v) & 0xFF ) << 0 )
#define SCB_SHPR2_PRI_8_MASK SCB_SHPR2_PRI_8(ALL1)
#define SCB_SHPR2_PRI_9(v) ( ( (v) & 0xFF ) << 8 )
#define SCB_SHPR2_PRI_9_MASK SCB_SHPR2_PRI_9(ALL1)
#define SCB_SHPR2_PRI_10(v) ( ( (v) & 0xFF ) << 16 )
#define SCB_SHPR2_PRI_10_MASK SCB_SHPR2_PRI_10(ALL1)
#define SCB_SHPR2_PRI_11(v) ( ( (v) & 0xFF ) << 24 )
#define SCB_SHPR2_PRI_11_MASK SCB_SHPR2_PRI_11(ALL1)

/* System handler priority register 3 macros */

#define SCB_SHPR3_PRI_12(v) ( ( (v) & 0xFF ) << 0 )
#define SCB_SHPR3_PRI_12_MASK SCB_SHPR3_PRI_12(ALL1)
#define SCB_SHPR3_PRI_13(v) ( ( (v) & 0xFF ) << 8 )
#define SCB_SHPR3_PRI_13_MASK SCB_SHPR3_PRI_13(ALL1)
#define SCB_SHPR3_PRI_14(v) ( ( (v) & 0xFF ) << 16 )
#define SCB_SHPR3_PRI_14_MASK SCB_SHPR3_PRI_14(ALL1)
#define SCB_SHPR3_PRI_15(v) ( ( (v) & 0xFF ) << 24 )
#define SCB_SHPR3_PRI_15_MASK SCB_SHPR3_PRI_15(ALL1)

/* System handler control and state register macros */

#define SCB_SHCRS_MEMFAULTACT(v) ( ( (v) & 0x1 ) << 0 )
#define SCB_SHCRS_MEMFAULTACT_MASK SCB_SHCRS_MEMFAULTACT(ALL1)
#define SCB_SHCRS_BUSFAULTACT(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_SHCRS_BUSFAULTACT_MASK SCB_SHCRS_BUSFAULTACT(ALL1)
#define SCB_SHCRS_USGFAULTACT(v) ( ( (v) & 0x1 ) << 3 )
#define SCB_SHCRS_USGFAULTACT_MASK SCB_SHCRS_USGFAULTACT(ALL1)
#define SCB_SHCRS_SVCALLACT(v) ( ( (v) & 0x1 ) << 7 )
#define SCB_SHCRS_SVCALLACT_MASK SCB_SHCRS_SVCALLACT(ALL1)
#define SCB_SHCRS_MONITORACT(v) ( ( (v) & 0x1 ) << 8 )
#define SCB_SHCRS_MONITORACT_MASK SCB_SHCRS_MONITORACT(ALL1)
#define SCB_SHCRS_PENDSVACT(v) ( ( (v) & 0x1 ) << 10 )
#define SCB_SHCRS_PENDSVACT_MASK SCB_SHCRS_PENDSVACT(ALL1)
#define SCB_SHCRS_SYSTICKACT(v) ( ( (v) & 0x1 ) << 11 )
#define SCB_SHCRS_SYSTICKACT_MASK SCB_SHCRS_SYSTICKACT(ALL1)
#define SCB_SHCRS_USGFAULTPENDED(v) ( ( (v) & 0x1 ) << 12 )
#define SCB_SHCRS_USGFAULTPENDED_MASK SCB_SHCRS_USGFAULTPENDED(ALL1)
#define SCB_SHCRS_MEMFAULTPENDED(v) ( ( (v) & 0x1 ) << 13 )
#define SCB_SHCRS_MEMFAULTPENDED_MASK SCB_SHCRS_MEMFAULTPENDED(ALL1)
#define SCB_SHCRS_BUSFAULTPENDED(v) ( ( (v) & 0x1 ) << 14 )
#define SCB_SHCRS_BUSFAULTPENDED_MASK SCB_SHCRS_BUSFAULTPENDED(ALL1)
#define SCB_SHCRS_SVCALLPENDED(v) ( ( (v) & 0x1 ) << 15 )
#define SCB_SHCRS_SVCALLPENDED_MASK SCB_SHCRS_SVCALLPENDED(ALL1)
#define SCB_SHCRS_MEMFAULTENA(v) ( ( (v) & 0x1 ) << 16 )
#define SCB_SHCRS_MEMFAULTENA_MASK SCB_SHCRS_MEMFAULTENA(ALL1)
#define SCB_SHCRS_BUSFAULTENA(v) ( ( (v) & 0x1 ) << 17 )
#define SCB_SHCRS_BUSFAULTENA_MASK SCB_SHCRS_BUSFAULTENA(ALL1)
#define SCB_SHCRS_USGFAULTENA(v) ( ( (v) & 0x1 ) << 18 )
#define SCB_SHCRS_USGFAULTENA_MASK SCB_SHCRS_USGFAULTENA(ALL1)

/* Configurable fault status register macros */

#define SCB_CFSR_IACCVIOL(v) ( ( (v) & 0x1 ) << 0 )
#define SCB_CFSR_IACCVIOL_MASK SCB_CFSR_IACCVIOL(ALL1)
#define SCB_CFSR_DACCVIOL(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_CFSR_DACCVIOL_MASK SCB_CFSR_DACCVIOL(ALL1)
#define SCB_CFSR_MUNSKERR(v) ( ( (v) & 0x1 ) << 3 )
#define SCB_CFSR_MUNSKERR_MASK SCB_CFSR_MUNSKERR(ALL1)
#define SCB_CFSR_MSTKERR(v) ( ( (v) & 0x1 ) << 4 )
#define SCB_CFSR_MSTKERR_MASK SCB_CFSR_MSTKERR(ALL1)
#define SCB_CFSR_MLSPERR(v) ( ( (v) & 0x1 ) << 5 )
#define SCB_CFSR_MLSPERR_MASK SCB_CFSR_MLSPERR(ALL1)
#define SCB_CFSR_MMARVALID(v) ( ( (v) & 0x1 ) << 7 )
#define SCB_CFSR_MMARVALID_MASK SCB_CFSR_MMARVALID(ALL1)
#define SCB_CFSR_IBUSERR(v) ( ( (v) & 0x1 ) << 8 )
#define SCB_CFSR_IBUSERR_MASK SCB_CFSR_IBUSERR(ALL1)
#define SCB_CFSR_PRECISERR(v) ( ( (v) & 0x1 ) << 9 )
#define SCB_CFSR_PRECISERR_MASK SCB_CFSR_PRECISERR(ALL1)
#define SCB_CFSR_IMPRECISERR(v) ( ( (v) & 0x1 ) << 10 )
#define SCB_CFSR_IMPRECISERR_MASK SCB_CFSR_IMPRECISERR(ALL1)
#define SCB_CFSR_UNSTKERR(v) ( ( (v) & 0x1 ) << 11 )
#define SCB_CFSR_UNSTKERR_MASK SCB_CFSR_UNSTKERR(ALL1)
#define SCB_CFSR_STKERR(v) ( ( (v) & 0x1 ) << 12 )
#define SCB_CFSR_STKERR_MASK SCB_CFSR_STKERR(ALL1)
#define SCB_CFSR_LSPERR(v) ( ( (v) & 0x1 ) << 13 )
#define SCB_CFSR_LSPERR_MASK SCB_CFSR_LSPERR(ALL1)
#define SCB_CFSR_BFARVALID(v) ( ( (v) & 0x1 ) << 15 )
#define SCB_CFSR_BFARVALID_MASK SCB_CFSR_BFARVALID(ALL1)
#define SCB_CFSR_UNDEFINSTR(v) ( ( (v) & 0x1 ) << 16 )
#define SCB_CFSR_UNDEFINSTR_MASK SCB_CFSR_UNDEFINSTR(ALL1)
#define SCB_CFSR_INVSTATE(v) ( ( (v) & 0x1 ) << 17 )
#define SCB_CFSR_INVSTATE_MASK SCB_CFSR_INVSTATE(ALL1)
#define SCB_CFSR_INVPC(v) ( ( (v) & 0x1 ) << 18 )
#define SCB_CFSR_INVPC_MASK SCB_CFSR_INVPC(ALL1)
#define SCB_CFSR_NOCP(v) ( ( (v) & 0x1 ) << 19 )
#define SCB_CFSR_NOCP_MASK SCB_CFSR_NOCP(ALL1)
#define SCB_CFSR_UNALIGNED(v) ( ( (v) & 0x1 ) << 24 )
#define SCB_CFSR_UNALIGNED_MASK SCB_CFSR_UNALIGNED(ALL1)
#define SCB_CFSR_DIVBYZERO(v) ( ( (v) & 0x1 ) << 25 )
#define SCB_CFSR_DIVBYZERO_MASK SCB_CFSR_DIVBYZERO(ALL1)

/* HardFault status register macros */

#define SCB_HFSR_VECTTBL(v) ( ( (v) & 0x1 ) << 1 )
#define SCB_HFSR_VECTTBL_MASK SCB_HFSR_VECTTBL(ALL1)
#define SCB_HFSR_FORCED(v) ( ( (v) & 0x1 ) << 30 )
#define SCB_HFSR_FORCED_MASK SCB_HFSR_FORCED(ALL1)
#define SCB_HFSR_DEBUGEVT(v) ( ( (v) & 0x1 ) << 31 )
#define SCB_HFSR_DEBUGEVT_MASK SCB_HFSR_DEBUGEVT(ALL1)

/* MemManage fault address register macros */

#define SCB_MMFAR_ADDRESS(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define SCB_MMFAR_ADDRESS_MASK SCB_MMFAR_ADDRESS(ALL1)

/* BusFault address register macros */

#define SCB_BFAR_ADDRESS(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define SCB_BFAR_ADDRESS_MASK SCB_BFAR_ADDRESS(ALL1)

/* Auxiliary fault status register macros */

#define SCB_AFSR_IMPDEF(v) ( ( (v) & 0xFFFFFFFF ) << 0 )
#define SCB_AFSR_IMPDEF_MASK SCB_AFSR_IMPDEF(ALL1)

#endif

