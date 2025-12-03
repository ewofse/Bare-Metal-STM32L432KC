#ifndef STM32L432KC_USB_H
#define STM32L432KC_USB_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t EP0R;
    uint32_t EP1R;
    uint32_t EP2R;
    uint32_t EP3R;
    uint32_t EP4R;
    uint32_t EP5R;
    uint32_t EP6R;
    uint32_t EP7R;
    uint32_t RESERVED[8];
    uint32_t CNTR;
    uint32_t ISTR;
    uint32_t FNR;
    uint32_t DADDR;
    uint32_t BTABLE;
    uint32_t LPMCSR;
    uint32_t BCDR;
} USB_FS_REG_BLOCKS;

typedef struct {
    /* TODO */
    uint32_t PLACEHOLDER;
} USB_SRAM_REG_BLOCKS;

/* USB registers as structs */

#define USB_FS   ( (USB_FS_REG_BLOCKS volatile *) 0x40006800 )
#define USB_SRAM ( (USB_SRAM_REG_BLOCKS volatile *) 0x40006C00 )

/* USB EP0R - EP7R register macros */

#define USB_EPR_EA(v) ( ( (v) & 0xF ) << 0 )
#define USB_EPR_EA_MASK USB_EPR_EA(ALL1)
#define USB_EPR_STAT_TX(v) ( ( (v) & 0x3 ) << 4 )
#define USB_EPR_STAT_TX_MASK USB_EPR_STAT_TX(ALL1)
#define USB_EPR_DTOG_TX(v) ( ( (v) & 0x1 ) << 6 )
#define USB_EPR_DTOG_TX_MASK USB_EPR_DTOG_TX(ALL1)
#define USB_EPR_CTR_TX(v) ( ( (v) & 0x1 ) << 7 )
#define USB_EPR_CTR_TX_MASK USB_EPR_CTR_TX(ALL1)
#define USB_EPR_EP_KIND(v) ( ( (v) & 0x1 ) << 8 )
#define USB_EPR_EP_KIND_MASK USB_EPR_EP_KIND(ALL1)
#define USB_EPR_EP_TYPE(v) ( ( (v) & 0x3 ) << 9 )
#define USB_EPR_EP_TYPE_MASK USB_EPR_EP_TYPE(ALL1)
#define USB_EPR_SETUP(v) ( ( (v) & 0x1 ) << 11 )
#define USB_EPR_SETUP_MASK USB_EPR_SETUP(ALL1)
#define USB_EPR_STAT_RX(v) ( ( (v) & 0x3 ) << 12 )
#define USB_EPR_STAT_RX_MASK USB_EPR_STAT_RX(ALL1)
#define USB_EPR_DTOG_RX(v) ( ( (v) & 0x1 ) << 14 )
#define USB_EPR_DTOG_RX_MASK USB_EPR_DTOG_RX(ALL1)
#define USB_EPR_CTR_RX(v) ( ( (v) & 0x1 ) << 15 )
#define USB_EPR_CTR_RX_MASK USB_EPR_CTR_RX(ALL1)

/* USB CNTR register macros */

#define USB_CNTR_FRES(v) ( ( (v) & 0x1 ) << 0 )
#define USB_CNTR_FRES_MASK USB_CNTR_FRES(ALL1)
#define USB_CNTR_PDWN(v) ( ( (v) & 0x1 ) << 1 )
#define USB_CNTR_PDWN_MASK USB_CNTR_PDWN(ALL1)
#define USB_CNTR_LP_MODE(v) ( ( (v) & 0x1 ) << 2 )
#define USB_CNTR_LP_MODE_MASK USB_CNTR_LP_MODE(ALL1)
#define USB_CNTR_FSUSP(v) ( ( (v) & 0x1 ) << 3 )
#define USB_CNTR_FSUSP_MASK USB_CNTR_FSUSP(ALL1)
#define USB_CNTR_RESUME(v) ( ( (v) & 0x1 ) << 4 )
#define USB_CNTR_RESUME_MASK USB_CNTR_RESUME(ALL1)
#define USB_CNTR_L1RESUME(v) ( ( (v) & 0x1 ) << 5 )
#define USB_CNTR_L1RESUME_MASK USB_CNTR_L1RESUME(ALL1)
#define USB_CNTR_L1REQM(v) ( ( (v) & 0x1 ) << 7 )
#define USB_CNTR_L1REQM_MASK USB_CNTR_L1REQM(ALL1)
#define USB_CNTR_ESOFM(v) ( ( (v) & 0x1 ) << 8 )
#define USB_CNTR_ESOFM_MASK USB_CNTR_ESOFM(ALL1)
#define USB_CNTR_SOFM(v) ( ( (v) & 0x1 ) << 9 )
#define USB_CNTR_SOFM_MASK USB_CNTR_SOFM(ALL1)
#define USB_CNTR_RESETM(v) ( ( (v) & 0x1 ) << 10 )
#define USB_CNTR_RESETM_MASK USB_CNTR_RESETM(ALL1)
#define USB_CNTR_SUSPM(v) ( ( (v) & 0x1 ) << 11 )
#define USB_CNTR_SUSPM_MASK USB_CNTR_SUSPM(ALL1)
#define USB_CNTR_WKUPM(v) ( ( (v) & 0x1 ) << 12 )
#define USB_CNTR_WKUPM_MASK USB_CNTR_WKUPM(ALL1)
#define USB_CNTR_ERRM(v) ( ( (v) & 0x1 ) << 13 )
#define USB_CNTR_ERRM_MASK USB_CNTR_ERRM(ALL1)
#define USB_CNTR_PMAOVRM(v) ( ( (v) & 0x1 ) << 14 )
#define USB_CNTR_PMAOVRM_MASK USB_CNTR_PMAOVRM(ALL1)
#define USB_CNTR_CTRM(v) ( ( (v) & 0x1 ) << 15 )
#define USB_CNTR_CTRM_MASK USB_CNTR_CTRM(ALL1)

/* USB ISTR register macros */

#define USB_ISTR_EP_ID(v) ( ( (v) & 0xF ) << 0 )
#define USB_ISTR_EP_ID_MASK USB_ISTR_EP_ID(ALL1)
#define USB_ISTR_DIR(v) ( ( (v) & 0x1 ) << 4 )
#define USB_ISTR_DIR_MASK USB_ISTR_DIR(ALL1)
#define USB_ISTR_L1REQ(v) ( ( (v) & 0x1 ) << 7 )
#define USB_ISTR_L1REQ_MASK USB_ISTR_L1REQ(ALL1)
#define USB_ISTR_ESOF(v) ( ( (v) & 0x1 ) << 8 )
#define USB_ISTR_ESOF_MASK USB_ISTR_ESOF(ALL1)
#define USB_ISTR_SOF(v) ( ( (v) & 0x1 ) << 9 )
#define USB_ISTR_SOF_MASK USB_ISTR_SOF(ALL1)
#define USB_ISTR_RESET(v) ( ( (v) & 0x1 ) << 10 )
#define USB_ISTR_RESET_MASK USB_ISTR_RESET(ALL1)
#define USB_ISTR_SUSP(v) ( ( (v) & 0x1 ) << 11 )
#define USB_ISTR_SUSP_MASK USB_ISTR_SUSP(ALL1)
#define USB_ISTR_WKUP(v) ( ( (v) & 0x1 ) << 12 )
#define USB_ISTR_WKUP_MASK USB_ISTR_WKUP(ALL1)
#define USB_ISTR_ERR(v) ( ( (v) & 0x1 ) << 13 )
#define USB_ISTR_ERR_MASK USB_ISTR_ERR(ALL1)
#define USB_ISTR_PMAOVR(v) ( ( (v) & 0x1 ) << 14 )
#define USB_ISTR_PMAOVR_MASK USB_ISTR_PMAOVR(ALL1)
#define USB_ISTR_CTR(v) ( ( (v) & 0x1 ) << 15 )
#define USB_ISTR_CTR_MASK USB_ISTR_CTR(ALL1)

/* USB FNR register macros */

#define USB_FNR_FN(v) ( ( (v) & 0x7FF ) << 0 )
#define USB_FNR_FN_MASK USB_FNR_FN(ALL1)
#define USB_FNR_LSOF(v) ( ( (v) & 0x3 ) << 11 )
#define USB_FNR_LSOF_MASK USB_FNR_LSOF(ALL1)
#define USB_FNR_LCK(v) ( ( (v) & 0x1 ) << 13 )
#define USB_FNR_LCK_MASK USB_FNR_LCK(ALL1)
#define USB_FNR_RXDM(v) ( ( (v) & 0x1 ) << 14 )
#define USB_FNR_RXDM_MASK UBS_FNR_RXDM(ALL1)
#define USB_FNR_RXDP(v) ( ( (v) & 0x1 ) << 15 )
#define USB_FNR_RXDP_MASK UBS_FNR_RXDP(ALL1)

/* USB DADDR register macros */

#define USB_DADDR_ADD0(v) ( ( (v) & 0x1 ) << 0 )
#define USB_DADDR_ADD0_MASK USB_DADDR_ADD0(ALL1)
#define USB_DADDR_ADD1(v) ( ( (v) & 0x1 ) << 1 )
#define USB_DADDR_ADD1_MASK USB_DADDR_ADD1(ALL1)
#define USB_DADDR_ADD2(v) ( ( (v) & 0x1 ) << 2 )
#define USB_DADDR_ADD2_MASK USB_DADDR_ADD2(ALL1)
#define USB_DADDR_ADD3(v) ( ( (v) & 0x1 ) << 3 )
#define USB_DADDR_ADD3_MASK USB_DADDR_ADD3(ALL1)
#define USB_DADDR_ADD4(v) ( ( (v) & 0x1 ) << 4 )
#define USB_DADDR_ADD4_MASK USB_DADDR_ADD4(ALL1)
#define USB_DADDR_ADD5(v) ( ( (v) & 0x1 ) << 5 )
#define USB_DADDR_ADD5_MASK USB_DADDR_ADD5(ALL1)
#define USB_DADDR_ADD6(v) ( ( (v) & 0x1 ) << 6 )
#define USB_DADDR_ADD6_MASK USB_DADDR_ADD6(ALL1)
#define USB_DADDR_EF(v) ( ( (v) & 0x1 ) << 7 )
#define USB_DADDR_EF_MASK USB_DADDR_EF(ALL1)

/* USB BTABLE register macros */

#define USB_BTABLE_BTABLE(v) ( ( (v) & 0x1FFF ) << 3 )
#define USB_BTABLE_BTABLE_MASK USB_BTABLE_BTABLE(ALL1)

/* USB LPMCSR register macros */

#define USB_LPMCSR_LPMEN(v) ( ( (v) & 0x1 ) << 0 )
#define USB_LPMCSR_LPMEN_MASK USB_LPMCSR_LPMEN(ALL1)
#define USB_LPMCSR_LPMACK(v) ( ( (v) & 0x1 ) << 1 )
#define USB_LPMCSR_LPMACK_MASK UBS_LPMCSR_LPMACK(ALL1)
#define USB_LPMCSR_REMWAKE(v) ( ( (v) & 0x1 ) << 3 )
#define USB_LPMCSR_REMWAKE_MASK USB_LPMCSR_REMWAKE(ALL1)
#define USB_LPMCSR_BESL(v) ( ( (v) & 0xF ) << 4 )
#define USB_LPMCSR_BESL_MASK USB_LPMCSR_BESL(ALL1)

/* USB BCDR register macros */

#define USB_BCDR_BCDEN(v) ( ( (v) & 0x1 ) << 0 )
#define USB_BCDR_BCDEN_MASK USB_BCDR_BCDEN(ALL1)
#define USB_BCDR_DCDEN(v) ( ( (v) & 0x1 ) << 1 )
#define USB_BCDR_DCDEN_MASK USB_BCDR_DCDEN(ALL1)
#define USB_BCDR_PDEN(v) ( ( (v) & 0x1 ) << 2 )
#define USB_BCDR_PDEN_MASK USB_BCDR_PDEN(ALL1)
#define USB_BCDR_SDEN(v) ( ( (v) & 0x1 ) << 3 )
#define USB_BCDR_SDEN_MASK USB_BCDR_SDEN(ALL1)
#define USB_BCDR_DCDET(v) ( ( (v) & 0x1 ) << 4 )
#define USB_BCDR_DCDET_MASK USB_BCDR_DCDET(ALL1)
#define USB_BCDR_PDET(v) ( ( (v) & 0x1 ) << 5 )
#define USB_BCDR_PDET_MASK USB_BCDR_PDET(ALL1)
#define USB_BCDR_SDET(v) ( ( (v) & 0x1 ) << 6 )
#define USB_BCDR_SDET_MASK USB_BCDR_SDET(ALL1)
#define USB_BCDR_PS2DET(v) ( ( (v) & 0x1 ) << 7 )
#define USB_BCDR_PS2DET_MASK USB_BCDR_PS2DET(ALL1)
#define USB_BCDR_DPPU(v) ( ( (v) & 0x1 ) << 15 )
#define USB_BCDR_DPPU_MASK USB_BCDR_DPPU(ALL1)

#endif

