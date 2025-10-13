#ifndef M4_SCB_H
#define M4_SCH_H

#include <stdint.h>

typedef struct {
    uint32_t ACTLR;
    uint32_t RESERVED[3320];
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

#define SCB_ACTLR_DISMCYCINT_MASK (1 << 0)
#define SCB_ACTLR_DISDEFWBUF_MASK (1 << 1)
#define SCB_ACTLR_DISFOLD_MASK    (1 << 2)

/* CPU ID register macros */

#define SCB_CPUID_IMPLEMENTER_MASK 0xFF000000
#define SCB_CPUID_VARIANT_MASK     0x00F00000
#define SCB_CPUID_CONSTANT_MASK    0x000F0000
#define SCB_CPUID_PARTNO_MASK      0x0000FFF0
#define SCB_CPUID_REVISION_MASK    0x0000000F

/* Interrupt control and state register macros */

#define SCB_ISCR_VECTACTIVE_MASK  0x000000FF
#define SCB_ISCR_VETTOBASE_MASK   (1 << 11)
#define SCB_ICSR_VECTPENDING_MASK 0x0003F000
#define SCB_ICSR_ISRPENDING_MASK  (1 << 22)
#define SCB_ICSR_PENDSTCLR_MASK   (1 << 25)
#define SCB_ICSR_PENDSTSET_MASK   (1 << 26)
#define SCB_ICSR_PENDSVCLR_MASK   (1 << 27)
#define SCB_ISCR_PENDSVSET_MAKS   (1 << 28)
#define SCB_ICSR_NMIPENDEN_MASK   (1 << 31)

/* Vector table offset register macros */

#define SCB_VTOR_TBLOFF_MASK 0xFFFFFF80

/* Application interrupt and reset control register */

#define SCB_AIRCR_VECTRESET_MASK     (1 << 0)
#define SCB_AIRCR_VECTCLRACTIVE_MASK (1 << 1)
#define SCB_AIRCR_SYSRESETREQ_MASK   (1 << 2)
#define SCB_AIRCR_PRIGROUP_MASK      0x00000700
#define SCB_AIRCR_ENDIANNESS_MASK    (1 << 15)
#define SCB_AIRCR_VECTKEY_MASK       0xFFFF0000

/* System control register macros */

#define SCB_SCR_SLEEPONEXIT_MASK (1 << 1)
#define SCB_SCR_SLEEPDEEP_MASK   (1 << 2)
#define SCB_SCR_SEVONPEND_MASK   (1 << 4)

/* Configuration and control register macros */

#define SCB_CCR_NONBASETHRDENA_MASK (1 << 0)
#define SCB_CCR_USERSETMPEND_MASK   (1 << 1)
#define SCB_CCR_UNALIGN_TRP_MASK    (1 << 3)
#define SCB_CCR_DIV_0_TRP_MASK      (1 << 4)
#define SCB_CCR_BFHFNMIGN_MASK      (1 << 8)
#define SCB_CCR_STKALIGN_MASK       (1 << 9)

/* System handler priority register 1 macros */

#define SCB_SHPR1_PRI_4_MASK (0xFF << 0)
#define SCB_SHPR1_PRI_5_MASK (0xFF << 8)
#define SCB_SHPR1_PRI_6_MASK (0xFF << 16)
#define SCB_SHPR1_PRI_7_MASK (0xFF << 24)

/* System handler priority register 2 macros */

#define SCB_SHPR2_PRI_8_MASK  (0xFF << 0)
#define SCB_SHPR2_PRI_9_MASK  (0xFF << 8)
#define SCB_SHPR2_PRI_10_MASK (0xFF << 16)
#define SCB_SHPR2_PRI_11_MASK (0xFF << 24)

/* System handler priority register 3 macros */

#define SCB_SHPR3_PRI_12_MASK (0xFF << 0)
#define SCB_SHPR3_PRI_13_MASK (0xFF << 8)
#define SCB_SHPR3_PRI_14_MASK (0xFF << 16)
#define SCB_SHPR3_PRI_15_MASK (0xFF << 24)

/* System handler control and state register macros */

#define SCB_SHCRS_MEMFAULTACT_MASK    (1 << 0)
#define SCB_SHCRS_BUSFAULTACT_MASK    (1 << 1)
#define SCB_SHCRS_USGFAULTACT_MASK    (1 << 3)
#define SCB_SHCRS_SVCALLACT_MASK      (1 << 7)
#define SCB_SHCRS_MONITORACT_MASK     (1 << 8)
#define SCB_SHCRS_PENDSVACT_MASK      (1 << 10)
#define SCB_SHCRS_SYSTICKACT_MASK     (1 << 11)
#define SCB_SHCRS_USGFAULTPENDED_MASK (1 << 12)
#define SCB_SHCRS_MEMFAULTPENDED_MASK (1 << 13)
#define SCB_SHCRS_BUSFAULTPENDED_MASK (1 << 14)
#define SCB_SHCRS_SVCALLPENDED_MASK   (1 << 15)
#define SCB_SHCRS_MEMFAULTENA_MASK    (1 << 16)
#define SCB_SHCRS_BUSFAULTENA_MASK    (1 << 17)
#define SCB_SHCRS_USGFAULTENA_MASK    (1 << 18)

/* Configurable fault status register macros */

#define SCB_CFSR_IACCVIOL_MASK    (1 << 0)
#define SCB_CFSR_DACCVIOL_MASK    (1 << 1)
#define SCB_CFSR_MUNSKERR_MASK    (1 << 3)
#define SCB_CFSR_MSTKERR_MASK     (1 << 4)
#define SCB_CFSR_MLSPERR_MASK     (1 << 5)
#define SCB_CFSR_MMARVALID_MASK   (1 << 7)
#define SCB_CFSR_IBUSERR_MASK     (1 << 8)
#define SCB_CFSR_PRECISERR_MASK   (1 << 9)
#define SCB_CFSR_IMPRECISERR_MASK (1 << 10)
#define SCB_CFSR_UNSTKERR_MASK    (1 << 11)
#define SCB_CFSR_STKERR_MASK      (1 << 12)
#define SCB_CFSR_LSPERR_MASK      (1 << 13)
#define SCB_CFSR_BFARVALID_MASK   (1 << 15)
#define SCB_CFSR_UNDEFINSTR_MASK  (1 << 16)
#define SCB_CFSR_INVSTATE_MASK    (1 << 17)
#define SCB_CFSR_INVPC_MASK       (1 << 18)
#define SCB_CFSR_NOCP_MASK        (1 << 19)
#define SCB_CFSR_UNALIGNED_MASK   (1 << 24)
#define SCB_CFSR_DIVBYZERO_MASK   (1 << 25)

/* HardFault status register macros */

#define SCB_HFSR_VECTTBL_MASK  (1 << 1)
#define SCB_HFSR_FORCED_MASK   (1 << 30)
#define SCB_HFSR_DEBUGEVT_MASK (1 << 31)

/* MemManage fault address register macro */

#define SCB_MMFAR_ADDRESS_MASK 0xFFFFFFFF

/* BusFault address register macro */

#define SCB_BFAR_ADDRESS_MASK 0xFFFFFFFF

/* Auxiliary fault status register macro */

#define SCB_AFSR_IMPDEF_MASK 0xFFFFFFFF

#endif

