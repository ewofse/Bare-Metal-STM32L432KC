#ifndef STM32L432KC_SPI_H
#define STM32L432KC_SPI_H

#include <stdio.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SR;
    uint32_t DR;
    uint32_t CRCPR;
    uint32_t RXCRCR;
    uint32_t TXCRCR;
} SPI_REG_BLOCKS;

/* SPI registers as structs */

#define SPI1 ( (SPI_REG_BLOCKS volatile *) 0x40013000 )
#define SPI3 ( (SPI_REG_BLOCKS volatile *) 0x40003C00 )

/* SPI CR1 register macros */

#define SPI_CR1_CPHA(v) ( ( (v) & 0x1 ) << 0 )
#define SPI_CR1_CPHA_MASK SPI_CR1_CPHA(ALL1)
#define SPI_CR1_CPOL(v) ( ( (v) & 0x1 ) << 1 )
#define SPI_CR1_CPOL_MASK SPI_CR1_CPOL(ALL1)
#define SPI_CR1_MSTR(v) ( ( (v) & 0x1 ) << 2 )
#define SPI_CR1_MSTR_MASK SPI_CR1_MSTR(ALL1)
#define SPI_CR1_BR(v) ( ( (v) & 0x7 ) << 3 )
#define SPI_CR1_BR_MASK SPI_CR1_BR(ALL1)
#define SPI_CR1_SPE(v) ( ( (v) & 0x1 ) << 6 )
#define SPI_CR1_SPE_MASK SPI_CR1_SPE(ALL1)
#define SPI_CR1_LSBFIRST(v) ( ( (v) & 0x1 ) << 7 )
#define SPI_CR1_LSBFIRST_MASK SPI_CR1_LSBFIRST(ALL1)
#define SPI_CR1_SSI(v) ( ( (v) & 0x1 ) << 8 )
#define SPI_CR1_SSI_MASK SPI_CR1_SSI(ALL1)
#define SPI_CR1_SSM(v) ( ( (v) & 0x1 ) << 9 )
#define SPI_CR1_SSM_MASK SPI_CR1_SSM(ALL1)
#define SPI_CR1_RXONLY(v) ( ( (v) & 0x1 ) << 10 )
#define SPI_CR1_RXONLY_MASK SPI_CR1_RXONLY(ALL1)
#define SPI_CR1_CRCL(v) ( ( (v) & 0x1 ) << 11 )
#define SPI_CR1_CRCL_MASK SPI_CR1_CRCL(ALL1)
#define SPI_CR1_CRCNEXT(v) ( ( (v) & 0x1 ) << 12 )
#define SPI_CR1_CRCNEXT_MASK SPI_CR1_CRCNEXT(ALL1)
#define SPI_CR1_CRCEN(v) ( ( (v) & 0x1 ) << 13 )
#define SPI_CR1_CRCEN_MASK SPI_CR1_CRCEN(ALL1)
#define SPI_CR1_BIDIOE(v) ( ( (v) & 0x1 ) << 14 )
#define SPI_CR1_BIDIOE_MASK SPI_CR1_BIDIOE(ALL1)
#define SPI_CR1_BIDIMODE(v) ( ( (v) & 0x1 ) << 15 )
#define SPI_CR1_BIDIMODE_MASK SPI_CR1_BIDIMODE(ALL1)

/* SPI CR2 register macros */

#define SPI_CR2_RXDMAEN(v) ( ( (v) & 0x1 ) << 0 )
#define SPI_CR2_RXDMAEN_MASK SPI_CR2_RXDMAEN(ALL1)
#define SPI_CR2_TXDMAEN(v) ( ( (v) & 0x1 ) << 1 )
#define SPI_CR2_TXDMAEN_MASK SPI_CR2_TXDMAEN(ALL1)
#define SPI_CR2_SSOE(v) ( ( (v) & 0x1 ) << 2 )
#define SPI_CR2_SSOE_MASK SPI_CR2_SSOE(ALL1)
#define SPI_CR2_NSSP(v) ( ( (v) & 0x1 ) << 3 )
#define SPI_CR2_NSSP_MASK SPI_CR2_NSSP(ALL1)
#define SPI_CR2_FRF(v) ( ( (v) & 0x1 ) << 4 )
#define SPI_CR2_FRF_MASK SPI_CR2_FRF(ALL1)
#define SPI_CR2_ERRIE(v) ( ( (v) & 0x1 ) << 5 )
#define SPI_CR2_ERRIE_MASK SPI_CR2_ERRIE(ALL1)
#define SPI_CR2_RXNEIE(v) ( ( (v) & 0x1 ) << 6 )
#define SPI_CR2_RXNEIE_MASK SPI_CR2_RXNEIE(ALL1)
#define SPI_CR2_TXEIE(v) ( ( (v) & 0x1 ) << 7 )
#define SPI_CR2_TXEIE_MASK SPI_CR2_TXEIE(ALL1)
#define SPI_CR2_DS(v) ( ( (v) & 0xF ) << 8 )
#define SPI_CR2_DS_MASK SPI_CR2_DS(ALL1)
#define SPI_CR2_FRXTH(v) ( ( (v) & 0x1 ) << 12 )
#define SPI_CR2_FRXTH_MASK SPI_CR2_FRXTH(ALL1)
#define SPI_CR2_LDMA_RX(v) ( ( (v) & 0x1 ) << 13 )
#define SPI_CR2_LDMA_RX_MASK SPI_CR2_LDMA_RX(ALL1)
#define SPI_CR2_LDMA_TX(v) ( ( (v) & 0x1 ) << 14 )
#define SPI_CR2_LDMA_TX_MASK SPI_CR2_LDMA_TX(ALL1)

/* SPI SR register macros */

#define SPI_SR_RXNE(v) ( ( (v) & 0x1 ) << 0 )
#define SPI_SR_RXNE_MASK SPI_SR_RXNE(ALL1)
#define SPI_SR_TXE(v) ( ( (v) & 0x1 ) << 1 )
#define SPI_SR_TXE_MASK SPI_SR_TXE(ALL1)
#define SPI_SR_CRCERR(v) ( ( (v) & 0x1 ) << 4 )
#define SPI_SR_CRCERR_MASK SPI_SR_CRCERR(ALL1)
#define SPI_SR_MODF(v) ( ( (v) & 0x1 ) << 5 )
#define SPI_SR_MODF_MASK SPI_SR_MODF(ALL1)
#define SPI_SR_OVR(v) ( ( (v) & 0x1 ) << 6 )
#define SPI_SR_OVR_MASK SPI_SR_OVR(ALL1)
#define SPI_SR_BSY(v) ( ( (v) & 0x1 ) << 7 )
#define SPI_SR_BSY_MASK SPI_SR_BSY(ALL1)
#define SPI_SR_FRE(v) ( ( (v) & 0x1 ) << 8 )
#define SPI_SR_FRE_MASK SPI_SR_FRE(ALL1)
#define SPI_SR_FRLVL(v) ( ( (v) & 0x3 ) << 9 )
#define SPI_SR_FRLVL_MASK SPI_SR_FRLVL(ALL1)
#define SPI_SR_FTLVL(v) ( ( (v) & 0x3 ) << 11 )
#define SPI_SR_FTLVL_MASK SPI_SR_FTLVL(ALL1)

/* SPI DR register macros */

#define SPI_DR_DR(v) ( ( (v) & 0xFFFF ) << 0 )
#define SPI_DR_DR_MASK SPI_DR_DR(ALL1)

/* SPI CRCPR register macros */

#define SPI_CRCPR_CRCPOLY(v) ( ( (v) & 0xFFFF ) << 0 )
#define SPI_CRCPR_CRCPOLY_MASK SPI_CRCPR_CRCPOLY(ALL1)

/* SPI RXCRCR register macros */

#define SPI_RXCRCR_RXCRC(v) ( ( (v) & 0xFFFF) << 0 )
#define SPI_RXCRCR_RXCRC_MASK SPI_RXCRCR_RXCRC(ALL1)

/* SPI TXCRCR register macros */

#define SPI_TXCRCR_TXCRC(v) ( ( (v) & 0xFFFF) << 0 )
#define SPI_TXCRCR_TXCRC_MASK SPI_TXCRCR_TXCRC(ALL1)

#endif

