#ifndef STM32L432KC_USART_H
#define STM32L432KC_USART_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t BRR;
    uint32_t GTPR;
    uint32_t RTOR;
    uint32_t RQR;
    uint32_t ISR;
    uint32_t ICR;
    uint32_t RDR;
    uint32_t TDR;
} USART_REG_BLOCKS;

/* USART registers as structs */

#define USART1 ( (USART_REG_BLOCKS volatile *) 0x40013800 )
#define USART2 ( (USART_REG_BLOCKS volatile *) 0x40004400 )

/* USART CR1 register macros */

#define USART_CR1_UE(v) ( ( (v) & 0x1 ) << 0 )
#define USART_CR1_UE_MASK USART_CR1_UE(ALL1)
#define USART_CR1_UESM(v) ( ( (v) & 0x1 ) << 1 )
#define USART_CR1_UESM_MASK USART_CR1_UESM(ALL1)
#define USART_CR1_RE(v) ( ( (v) & 0x1 ) << 2 )
#define USART_CR1_RE_MASK USART_CR1_RE(ALL1)
#define USART_CR1_TE(v) ( ( (v) & 0x1 ) << 3 )
#define USART_CR1_TE_MASK USART_CR1_TE(ALL1)
#define USART_CR1_IDLEIE(v) ( ( (v) & 0x1 ) << 4 )
#define USART_CR1_IDLEIE_MASK USART_CR1_IDLEIE(ALL1)
#define USART_CR1_RXNEIE(v) ( ( (v) & 0x1 ) << 5 )
#define USART_CR1_RXNEIE_MASK USART_CR1_RXNEIE(ALL1)
#define USART_CR1_TCIE(v) ( ( (v) & 0x1 ) << 6 )
#define USART_CR1_TCIE_MASK USART_CR1_TCIE(ALL1)
#define USART_CR1_TXEIE(v) ( ( (v) & 0x1 ) << 7 )
#define USART_CR1_TXEIE_MASK USART_CR1_TXEIE(ALL1)
#define USART_CR1_PEIE(v) ( ( (v) & 0x1 ) << 8 )
#define USART_CR1_PEIE_MASK USART_CR1_PEIE(ALL1)
#define USART_CR1_PS(v) ( ( (v) & 0x1 ) << 9 )
#define USART_CR1_PS_MASK USART_CR1_PS(ALL1)
#define USART_CR1_PCE(v) ( ( (v) & 0x1 ) << 10 )
#define USART_CR1_PCE_MASK USART_CR1_PCE(ALL1)
#define USART_CR1_WAKE(v) ( ( (v) & 0x1 ) << 11 )
#define USART_CR1_WAKE_MASK USART_CR1_WAKE(ALL1)
#define USART_CR1_M0(v) ( ( (v) & 0x1 ) << 12 )
#define USART_CR1_M0_MASK USART_CR1_M0(ALL1)
#define USART_CR1_MME(v) ( ( (v) & 0x1 ) << 13 )
#define USART_CR1_MME_MASK USART_CR1_MME(ALL1)
#define USART_CR1_CMIE(v) ( ( (v) & 0x1 ) << 14 )
#define USART_CR1_CMIE_MASK USART_CR1_CMIE(ALL1)
#define USART_CR1_OVER8(v) ( ( (v) & 0x1 ) << 15 )
#define USART_CR1_OVER8_MASK USART_CR1_OVER8(ALL1)
#define USART_CR1_DEDT(v) ( ( (v) & 0x1F ) << 16 )
#define USART_CR1_DEDT_MASK USART_CR1_DEDT(ALL1)
#define USART_CR1_DEAT(v) ( ( (v) & 0x1F ) << 21 )
#define USART_CR1_DEAT_MASK USART_CR1_DEAT(ALL1)
#define USART_CR1_RTOIE(v) ( ( (v) & 0x1 ) << 26 )
#define USART_CR1_RTOIE_MASK USART_CR1_RTOIE(ALL1)
#define USART_CR1_EOBIE(v) ( ( (v) & 0x1 ) << 27 )
#define USART_CR1_EOBIE_MASK USART_CR1_EOBIE(ALL1)
#define USART_CR1_M1(v) ( ( (v) & 0x1 ) << 28 )
#define USART_CR1_M1_MASK USART_CR1_M1(ALL1)

/* USART CR2 register macros */

#define USART_CR2_ADDM7(v) ( ( (v) & 0x1 ) << 4 )
#define USART_CR2_ADDM7_MASK USART_CR2_ADDM7(ALL1)
#define USART_CR2_LBDL(v) ( ( (v) & 0x1 ) << 5 )
#define USART_CR2_LBDL_MASK USART_CR2_LBDL(ALL1)
#define USART_CR2_LBDIE(v) ( ( (v) & 0x1 ) << 6 )
#define USART_CR2_LBDIE_MASK USART_CR2_LBDIE(ALL1)
#define USART_CR2_LBCL(v) ( ( (v) & 0x1 ) << 8 )
#define USART_CR2_LBCL_MASK USART_CR2_LBCL(ALL1)
#define USART_CR2_CPHA(v) ( ( (v) & 0x1 ) << 9 )
#define USART_CR2_CPHA_MASK USART_CR2_CPHA(ALL1)
#define USART_CR2_CPOL(v) ( ( (v) & 0x1 ) << 10 )
#define USART_CR2_CPOL_MASK USART_CR2_CPOL(ALL1)
#define USART_CR2_CLKEN(v) ( ( (v) & 0x1 ) << 11 )
#define USART_CR2_CLKEN_MASK USART_CR2_CLKEN(ALL1)
#define USART_CR2_STOP(v) ( ( (v) & 0x3 ) << 12 )
#define USART_CR2_STOP_MASK USART_CR2_STOP(ALL1)
#define USART_CR2_LINEN(v) ( ( (v) & 0x1 ) << 14 )
#define USART_CR2_LINEN_MASK USART_CR2_LINEN(ALL1)
#define USART_CR2_SWAP(v) ( ( (v) & 0x1 ) << 15 )
#define USART_CR2_SWAP_MASK USART_CR2_SWAP(ALL1)
#define USART_CR2_RXINV(v) ( ( (v) & 0x1 ) << 16 )
#define USART_CR2_RXINV_MASK USART_CR2_RXINV(ALL1)
#define USART_CR2_TXINV(v) ( ( (v) & 0x1 ) << 17 )
#define USART_CR2_TXINV_MASK USART_CR2_TXINV(ALL1)
#define USART_CR2_DATAINV(v) ( ( (v) & 0x1 ) << 18 )
#define USART_CR2_DATAINV_MASK USART_CR2_DATAINV(ALL1)
#define USART_CR2_MSBFIRST(v) ( ( (v) & 0x1 ) << 19 )
#define USART_CR2_MSBFIRST_MASK USART_CR2_MSBFIRST(ALL1)
#define USART_CR2_ABREN(v) ( ( (v) & 0x1 ) << 20 )
#define USART_CR2_ABREN_MASK USART_CR2_ABREN(ALL1)
#define USART_CR2_ABRMOD(v) ( ( (v) & 0x3 ) << 21 )
#define USART_CR2_ABRMOD_MASK USART_CR2_ABRMOD(ALL1)
#define USART_CR2_RTOEN(v) ( ( (v) & 0x1 ) << 23 )
#define USART_CR2_RTOEN_MASK USART_CR2_RTOEN(ALL1)
#define USART_CR2_ADD(v) ( ( (v) & 0xFF ) << 24 )
#define USART_CR2_ADD_MASK USART_CR2_ADD(ALL1)

/* USART CR3 register macros */

#define USART_CR3_EIE(v) ( ( (v) & 0x1 ) << 0 )
#define USART_CR3_EIE_MASK USART_CR3_EIE(ALL1)
#define USART_CR3_IREN(v) ( ( (v) & 0x1 ) << 1 )
#define USART_CR3_IREN_MASK USART_CR3_IREN(ALL1)
#define USART_CR3_IRLP(v) ( ( (v) & 0x1 ) << 2 )
#define USART_CR3_IRLP_MASK USART_CR3_IRLP(ALL1)
#define USART_CR3_HDSEL(v) ( ( (v) & 0x1 ) << 3 )
#define USART_CR3_HDSEL_MASK USART_CR3_HDSEL(ALL1)
#define USART_CR3_NACK(v) ( ( (v) & 0x1 ) << 4 )
#define USART_CR3_NACK_MASK USART_CR3_NACK(ALL1)
#define USART_CR3_SCEN(v) ( ( (v) & 0x1 ) << 5 )
#define USART_CR3_SCEN_MASK USART_CR3_SCEN(ALL1)
#define USART_CR3_DMAR(v) ( ( (v) & 0x1 ) << 6 )
#define USART_CR3_DMAR_MASK USART_CR3_DMAR(ALL1)
#define USART_CR3_DMAT(v) ( ( (v) & 0x1 ) << 7 )
#define USART_CR3_DMAT_MASK USART_CR3_DMAT(ALL1)
#define USART_CR3_RTSE(v) ( ( (v) & 0x1 ) << 8 )
#define USART_CR3_RTSE_MASK USART_CR3_RTSE(ALL1)
#define USART_CR3_CTSE(v) ( ( (v) & 0x1 ) << 9 )
#define USART_CR3_CTSE_MASK USART_CR3_CTSE(ALL1)
#define USART_CR3_CTSIE(v) ( ( (v) & 0x1 ) << 10 )
#define USART_CR3_CTSIE_MASK USART_CR3_CTSIE(ALL1)
#define USART_CR3_ONEBIT(v) ( ( (v) & 0x1 ) << 11 )
#define USART_CR3_ONEBIT_MASK USART_CR3_ONEBIT(ALL1)
#define USART_CR3_OVRDIS(v) ( ( (v) & 0x1 ) << 12 )
#define USART_CR3_OVRDIS_MASK USART_CR3_OVRDIS(ALL1)
#define USART_CR3_DDRE(v) ( ( (v) & 0x1 ) << 13 )
#define USART_CR3_DDRE_MASK USART_CR3_DDRE(ALL1)
#define USART_CR3_DEM(v) ( ( (v) & 0x1 ) << 14 )
#define USART_CR3_DEM_MASK USART_CR3_DEM(ALL1)
#define USART_CR3_DEP(v) ( ( (v) & 0x1 ) << 15 )
#define USART_CR3_DEP_MASK USART_CR3_DEP(ALL1)
#define USART_CR3_SCARCNT0(v) ( ( (v) & 0x1 ) << 17 )
#define USART_CR3_SCARCNT0_MASK USART_CR3_SCARCNT0(ALL1)
#define USART_CR3_SCARCNT1(v) ( ( (v) & 0x1 ) << 18 )
#define USART_CR3_SCARCNT1_MASK USART_CR3_SCARCNT1(ALL1)
#define USART_CR3_SCARCNT2(v) ( ( (v) & 0x1 ) << 19 )
#define USART_CR3_SCARCNT2_MASK USART_CR3_SCARCNT2(ALL1)
#define USART_CR3_WUS0(v) ( ( (v) & 0x1 ) << 20 )
#define USART_CR3_WUS0_MASK USART_CR3_WUS0(ALL1)
#define USART_CR3_WUS1(v) ( ( (v) & 0x1 ) << 21 )
#define USART_CR3_WUS1_MASK USART_CR3_WUS1(ALL1)
#define USART_CR3_WUFIE(v) ( ( (v) & 0x1 ) << 22 )
#define USART_CR3_WUFIE_MASK USART_CR3_WUFIE(ALL1)
#define USART_CR3_UCESM(v) ( ( (v) & 0x1 ) << 23 )
#define USART_CR3_UCESM_MASK USART_CR3_UCESM(ALL1)
#define USART_CR3_TCBGTIE(v) ( ( (v) & 0x1 ) << 24 )
#define USART_CR3_TCBGTIE_MASK USART_CR3_TCBGTIE(ALL1)

/* USART BRR register macros */

#define USART_BRR_BRR(v) ( ( (v) & 0xFFFF ) << 0 )
#define USART_BRR_BRR_MASK USART_BRR_BRR(ALL1)

/* USART GTPR register macros */

#define USART_GTPR_PSC(v) ( ( (v) & 0xFF ) << 0 )
#define USART_GTPR_PSC_MASK USART_GTPR_PSC(ALL1)
#define USART_GTPR_GT(v) ( ( (v) & 0xFF ) << 8 )
#define USART_GTPR_GR_MASK USART_GTPR_GT(ALL1)

/* USART RTOR register macros */

#define USART_RTOR_RTO(v) ( ( (v) & 0xFFFFFF ) << 0 )
#define USART_RTOR_RTO_MASK USART_RTOR_RTO(ALL1)
#define USART_RTOR_BLEN(v) ( ( (v) & 0xFF ) << 24 )
#define USART_RTOR_BLEN_MASK USART_RTOR_BLEN(ALL1)

/* USART RQR register macros */

#define USART_RQR_ABRRQ(v) ( ( (v) & 0x1 ) << 0 )
#define USART_RQR_ABRRQ_MASK USART_RQR_ABRRQ(ALL1)
#define USART_RQR_SBKRQ(v) ( ( (v) & 0x1 ) << 1 )
#define USART_RQR_SBKRQ_MASK USART_RQR_SBKRQ(ALL1)
#define USART_RQR_MMRQ(v) ( ( (v) & 0x1 ) << 2 )
#define USART_RQR_MMRQ_MASK USART_RQR_MMRQ(ALL1)
#define USART_RQR_RXFRQ(v) ( ( (v) & 0x1 ) << 3 )
#define USART_RQR_RXFRQ_MASK USART_RQR_RXFRQ(ALL1)
#define USART_RQR_TXFRQ(v) ( ( (v) & 0x1 ) << 4 )
#define USART_RQR_TXFRQ_MASK USART_RQR_TXFRQ(ALL1)

/* USART ISR register macros */

#define USART_ISR_PE(v) ( ( (v) & 0x1 ) << 0 )
#define USART_ISR_PE_MASK USART_ISR_PE(ALL1)
#define USART_ISR_FE(v) ( ( (v) & 0x1 ) << 1 )
#define USART_ISR_FE_MASK USART_ISR_FE(ALL1)
#define USART_ISR_NF(v) ( ( (v) & 0x1 ) << 2 )
#define USART_ISR_NF_MASK USART_ISR_NF(ALL1)
#define USART_ISR_ORE(v) ( ( (v) & 0x1 ) << 3 )
#define USART_ISR_ORE_MASK USART_ISR_ORE(ALL1)
#define USART_ISR_IDLE(v) ( ( (v) & 0x1 ) << 4 )
#define USART_ISR_IDLE_MASK USART_ISR_IDLE(ALL1)
#define USART_ISR_RXNE(v) ( ( (v) & 0x1 ) << 5 )
#define USART_ISR_RXNE_MASK USART_ISR_RXNE(ALL1)
#define USART_ISR_TC(v) ( ( (v) & 0x1 ) << 6 )
#define USART_ISR_TC_MASK USART_ISR_TC(ALL1)
#define USART_ISR_TXE(v) ( ( (v) & 0x1 ) << 7 )
#define USART_ISR_TXE_MASK USART_ISR_TXE(ALL1)
#define USART_ISR_LBDF(v) ( ( (v) & 0x1 ) << 8 )
#define USART_ISR_LBDF_MASK USART_ISR_LBDF(ALL1)
#define USART_ISR_CTSIF(v) ( ( (v) & 0x1 ) << 9 )
#define USART_ISR_CTSIF_MASK USART_ISR_CTSIF(ALL1)
#define USART_ISR_CTS(v) ( ( (v) & 0x1 ) << 10 )
#define USART_ISR_CTS_MASK USART_ISR_CTS(ALL1)
#define USART_ISR_RTOF(v) ( ( (v) & 0x1 ) << 11 )
#define USART_ISR_RTOF_MASK USART_ISR_RTOF(ALL1)
#define USART_ISR_EOBF(v) ( ( (v) & 0x1 ) << 12 )
#define USART_ISR_EOBF_MASK USART_ISR_EOBF(ALL1)
#define USART_ISR_ABRE(v) ( ( (v) & 0x1 ) << 14 )
#define USART_ISR_ABRE_MASK USART_ISR_ABRE(ALL1)
#define USART_ISR_ABRF(v) ( ( (v) & 0x1 ) << 15 )
#define USART_ISR_ABRF_MASK USART_ISR_ABRF(ALL1)
#define USART_ISR_BUSY(v) ( ( (v) & 0x1 ) << 16 )
#define USART_ISR_BUSY_MASK USART_ISR_BUSY(ALL1)
#define USART_ISR_CMF(v) ( ( (v) & 0x1 ) << 17 )
#define USART_ISR_CMF_MASK USART_ISR_CMF(ALL1)
#define USART_ISR_SBKF(v) ( ( (v) & 0x1 ) << 18 )
#define USART_ISR_SBKF_MASK USART_ISR_SBKF(ALL1)
#define USART_ISR_WUF(v) ( ( (v) & 0x1 ) << 20 )
#define USART_ISR_WUF_MASK USART_ISR_WUF(ALL1)
#define USART_ISR_TEACK(v) ( ( (v) & 0x1 ) << 21 )
#define USART_ISR_TEACK_MASK USART_ISR_TEACK(ALL1)
#define USART_ISR_REACK(v) ( ( (v) & 0x1 ) << 22 )
#define USART_ISR_REACK_MASK USART_ISR_REACK(ALL1)
#define USART_ISR_TCBGT(v) ( ( (v) & 0x1 ) << 25 )
#define USART_ISR_TCBGT_MASK USART_ISR_TCBGT(ALL1)

/* USART ICR register macros */

#define USART_ICR_PECF(v) ( ( (v) & 0x1 ) << 0 )
#define USART_ICR_PECF_MASK USART_ICR_PECF(ALL1)
#define USART_ICR_FECF(v) ( ( (v) & 0x1 ) << 1 )
#define USART_ICR_FECF_MASK USART_ICR_FECF(ALL1)
#define USART_ICR_NCF(v) ( ( (v) & 0x1 ) << 2 )
#define USART_ICR_NCF_MASK USART_ICR_NCF(ALL1)
#define USART_ICR_ORECF(v) ( ( (v) & 0x1 ) << 3 )
#define USART_ICR_ORECF_MASK USART_ICR_ORECF(ALL1)
#define USART_ICR_IDLECF(v) ( ( (v) & 0x1 ) << 4 )
#define USART_ICR_IDLECF_MASK USART_ICR_IDLECF(ALL1)
#define USART_ICR_TCCF(v) ( ( (v) & 0x1 ) << 6 )
#define USART_ICR_TCCF_MASK USART_ICR_TCCF(ALL1)
#define USART_ICR_TCBGTCF(v) ( ( (v) & 0x1 ) << 7 )
#define USART_ICR_TCBGTCF_MASK USART_ICR_TCBGTCF(ALL1)
#define USART_ICR_LBDCF(v) ( ( (v) & 0x1 ) << 8 )
#define USART_ICR_LBDCF_MASK USART_ICR_LBDCF(ALL1)
#define USART_ICR_CTSCF(v) ( ( (v) & 0x1 ) << 9 )
#define USART_ICR_CTSCF_MASK USART_ICR_CTSCF(ALL1)
#define USART_ICR_RTOCF(v) ( ( (v) & 0x1 ) << 11 )
#define USART_ICR_RTOCF_MASK USART_ICR_RTOCF(ALL1)
#define USART_ICR_EOBCF(v) ( ( (v) & 0x1 ) << 12 )
#define USART_ICR_EOBCF_MASK USART_ICR_EOBCF(ALL1)
#define USART_ICR_CMCF(v) ( ( (v) & 0x1 ) << 17 )
#define USART_ICR_CMCF_MASK USART_ICR_CMCF(ALL1)
#define USART_ICR_WUCF(v) ( ( (v) & 0x1 ) << 20 )
#define USART_ICR_WUCF_MASK USART_ICR_WUCF(ALL1)

/* USART RDR register macros */

#define USART_RDR_RDR(v) ( ( (v) & 0xFF ) << 0 )
#define USART_RDR_RDR_MASK USART_RDR_RDR(ALL1)

/* USART TDR register macros */

#define USART_TDR_TDR(v) ( ( (v) & 0xFF ) << 0 )
#define USART_TDR_TDR_MASK USART_TDR_TDR(ALL1)

#endif

