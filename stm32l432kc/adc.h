#ifndef STM32L432KC_ADC_H
#define STM32L432KC_ADC_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t ISR;
    uint32_t IER;
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CFGR2;
    uint32_t SMPR1;
    uint32_t SMPR2;
    uint32_t RESERVED0;
    uint32_t TR1;
    uint32_t TR2;
    uint32_t TR3;
    uint32_t RESERVED1;
    uint32_t SQR1;
    uint32_t SQR2;
    uint32_t SQR3;
    uint32_t SQR4;
    uint32_t DR;
    uint32_t RESERVED2[2];
    uint32_t JSQR;
    uint32_t RESERVED3[4];
    uint32_t OFR1;
    uint32_t OFR2;
    uint32_t OFR3;
    uint32_t OFR4;
    uint32_t RESERVED4[4];
    uint32_t JDR1;
    uint32_t JDR2;
    uint32_t JDR3;
    uint32_t JDR4;
    uint32_t RESERVED5[5];
    uint32_t AWD2CR;
    uint32_t AWD3CR;
    uint32_t RESERVED6[2];
    uint32_t DIFSEL;
    uint32_t CALFACT;
} ADC_REG_BLOCKS;

typedef struct {
    uint32_t CSR;
    uint32_t RESERVED;
    uint32_t CCR;
    uint32_t CDR;
} ADC_COMMON_REG_BLOCKS;

/* ADC registers as structs */

#define ADC1 ( (ADC_REG_BLOCKS volatile *) 0x50040000 )
#define ADC_COMMON ( (ADC_COMMON_REG_BLOCKS volatile * ) 0x50043000 )

/* ADC ISR register macros */

#define ADC_ISR_ADRDY(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_ISR_ADRDY_MASK ADC_ISR_ADRDY(ALL1)
#define ADC_ISR_EOSMP(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_ISR_EOSMP_MASK ADC_ISR_EOSMP(ALL1)
#define ADC_ISR_EOC(v) ( ( (v) & 0x1 ) << 2 )
#define ADC_ISR_EOC_MASK ADC_ISR_EOC(ALL1)
#define ADC_ISR_EOS(v) ( ( (v) & 0x1 ) << 3 )
#define ADC_ISR_EOS_MASK ADC_ISR_EOS(ALL1)
#define ADC_ISR_OVR(v) ( ( (v) & 0x1 ) << 4 )
#define ADC_ISR_OVR_MASK ADC_ISR_OVR(ALL1)
#define ADC_ISR_JEOC(v) ( ( (v) & 0x1 ) << 5 )
#define ADC_ISR_JEOC_MASK ADC_ISR_JEOC(ALL1)
#define ADC_ISR_JEOS(v) ( ( (v) & 0x1 ) << 6 )
#define ADC_ISR_JEOS_MASK ADC_ISR_JEOS(ALL1)
#define ADC_ISR_AWD1(v) ( ( (v) & 0x1 ) << 7 )
#define ADC_ISR_AWD1_MASK ADC_ISR_AWD1(ALL1)
#define ADC_ISR_AWD2(v) ( ( (v) & 0x1 ) << 8 )
#define ADC_ISR_AWD2_MASK ADC_ISR_AWD2(ALL1)
#define ADC_ISR_AWD3(v) ( ( (v) & 0x1 ) << 9 )
#define ADC_ISR_AWD3_MASK ADC_ISR_AWD3(ALL1)
#define ADC_ISR_JQOVF(v) ( ( (v) & 0x1 ) << 10 )
#define ADC_ISR_JQOVF_MASK ADC_ISR_JQOVF(ALL1)

/* ADC IER register macros */

#define ADC_IER_ADRDYIE(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_IER_ADRDYIE_MASK ADC_IER_ADRDYIE(ALL1)
#define ADC_IER_EOSMPIE(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_IER_EOSMPIE_MASK ADC_IER_EOSMPIE(ALL1)
#define ADC_IER_EOCIE(v) ( ( (v) & 0x1 ) << 2 )
#define ADC_IER_EOCIE_MASK ADC_IER_EOCIE(ALL1)
#define ADC_IER_EOSIE(v) ( ( (v) & 0x1 ) << 3 )
#define ADC_IER_EOSIE_MASK ADC_IER_EOSIE(ALL1)
#define ADC_IER_OVRIE(v) ( ( (v) & 0x1 ) << 4 )
#define ADC_IER_OVRIE_MASK ADC_IER_OVRIE(ALL1)
#define ADC_IER_JEOCIE(v) ( ( (v) & 0x1 ) << 5 )
#define ADC_IER_JEOCIE_MASK ADC_IER_JEOCIE(ALL1)
#define ADC_IER_JEOSIE(v) ( ( (v) & 0x1 ) << 6 )
#define ADC_IER_JEOSIE_MASK ADC_IER_JEOSIE(ALL1)
#define ADC_IER_AWD1IE(v) ( ( (v) & 0x1 ) << 7 )
#define ADC_IER_AWD1IE_MASK ADC_IER_AWD1IE(ALL1)
#define ADC_IER_AWD2IE(v) ( ( (v) & 0x1 ) << 8 )
#define ADC_IER_AWD2IE_MASK ADC_IER_AWD2IE(ALL1)
#define ADC_IER_AWD3IE(v) ( ( (v) & 0x1 ) << 9 )
#define ADC_IER_AWD3IE_MASK ADC_IER_AWD3IE(ALL1)
#define ADC_IER_JQOVFIE(v) ( ( (v) & 0x1 ) << 10 )
#define ADC_IER_JQOVFIE_MASK ADC_IER_JQOVFIE(ALL1)

/* ADC CR register macros */

#define ADC_CR_ADEN(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_CR_ADEN_MASK ADC_CR_ADEN(ALL1)
#define ADC_CR_ADDIS(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_CR_ADDIS_MASK ADC_CR_ADDIS(ALL1)
#define ADC_CR_ADSTART(v) ( ( (v) & 0x1 ) << 2 )
#define ADC_CR_ADSTART_MASK ADC_CR_ADSTART(ALL1)
#define ADC_CR_JADSTART(v) ( ( (v) & 0x1 ) << 3 )
#define ADC_CR_JADSTART_MASK ADC_CR_JADSTART(ALL1)
#define ADC_CR_ADSTP(v) ( ( (v) & 0x1 ) << 4 )
#define ADC_CR_ADSTP_MASK ADC_CR_ADSTP(ALL1)
#define ADC_CR_JADSTP(v) ( ( (v) & 0x1 ) << 5 )
#define ADC_CR_JADSTP_MASK ADC_CR_JADSTP(ALL1)
#define ADC_CR_ADVREGEN(v) ( ( (v) & 0x1 ) << 28 )
#define ADC_CR_ADVREGEN_MASK ADC_CR_ADVREGEN(ALL1)
#define ADC_CR_DEEPPWD(v) ( ( (v) & 0x1 ) << 29 )
#define ADC_CR_DEEPPWD_MASK ADC_CR_DEEPPWD(ALL1)
#define ADC_CR_ADCALDIF(v) ( ( (v) & 0x1 ) << 30 )
#define ADC_CR_ADCALDIF_MASK ADC_CR_ADCALDIF(ALL1)
#define ADC_CR_ADCAL(v) ( ( (v) & 0x1 ) << 31 )
#define ADC_CR_ADCAL_MASK ADC_CR_ADCAL(ALL1)

/* ADC CFGR register macros */

#define ADC_CFGR_DMAEN(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_CFGR_DMAEN_MASK ADC_CFGR_DMAEN(ALL1)
#define ADC_CFGR_DMACFG(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_CFGR_DMACFG_MASK ADC_CFGR_DMACFG(ALL1)
#define ADC_CFGR_DFSDMCFG(v) ( ( (v) & 0x1 ) << 2 )
#define ADC_CFGR_DFSDMCFG_MASK ADC_CFGR_DFSDMCFG(ALL1)
#define ADC_CFGR_RES(v) ( ( (v) & 0x3 ) << 3 )
#define ADC_CFGR_RES_MASK ADC_CFGR_RES(ALL1)
#define ADC_CFGR_ALIGN(v) ( ( (v) & 0x1 ) << 5 )
#define ADC_CFGR_ALIGN_MASK ADC_CFGR_ALIGN(ALL1)
#define ADC_CFGR_EXTSEL(v) ( ( (v) & 0xF ) << 6 )
#define ADC_CFGR_EXTSEL_MASK ADC_CFGR_EXTSEL(ALL1)
#define ADC_CFGR_EXTEN(v) ( ( (v) & 0x3 ) << 10 )
#define ADC_CFGR_EXTEN_MASK ADC_CFGR_EXTEN(ALL1)
#define ADC_CFGR_OVRMOD(v) ( ( (v) & 0x1 ) << 12 )
#define ADC_CFGR_OVRMOD_MASK ADC_CFGR_OVRMOD(ALL1)
#define ADC_CFGR_CONT(v) ( ( (v) & 0x1 ) << 13 )
#define ADC_CFGR_CONT_MASK ADC_CFGR_CONT(ALL1)
#define ADC_CFGR_AUTDLY(v) ( ( (v) & 0x1 ) << 14 )
#define ADC_CFGR_AUTDLY_MASK ADC_CFGR_AUTDLY(ALL1)
#define ADC_CFGR_DISCEN(v) ( ( (v) & 0x1 ) << 16 )
#define ADC_CFGR_DISCEN_MASK ADC_CFGR_DISCEN(ALL1)
#define ADC_CFGR_DISCNUM(v) ( ( (v) & 0x7 ) << 17 )
#define ADC_CFGR_DISCNUM_MASK ADC_CFGR_DISCNUM(ALL1)
#define ADC_CFGR_JDISCEN(v) ( ( (v) & 0x1 ) << 20 )
#define ADC_CFGR_JDISCEN_MASK ADC_CFGR_JDISCEN(ALL1)
#define ADC_CFGR_JQM(v) ( ( (v) & 0x1 ) << 21 )
#define ADC_CFGR_JQM_MASK ADC_CFGR_JQM(ALL1)
#define ADC_CFGR_AWD1SGL(v) ( ( (v) & 0x1 ) << 22 )
#define ADC_CFGR_AWD1SGL_MASK ADC_CFGR_AWD1SGL(ALL1)
#define ADC_CFGR_AWD1EN(v) ( ( (v) & 0x1 ) << 23 )
#define ADC_CFGR_AWD1EN_MASK ADC_CFGR_AWD1EN(ALL1)
#define ADC_CFGR_JAWD1EN(v) ( ( (v) & 0x1 ) << 24 )
#define ADC_CFGR_JAWD1EN_MASK ADC_CFGR_JAWD1EN(ALL1)
#define ADC_CFGR_JAUTO(v) ( ( (v) & 0x1 ) << 25 )
#define ADC_CFGR_JAUTO_MASK ADC_CFGR_JAUTO(ALL1)
#define ADC_CFGR_AWD1CH(v) ( ( (v) & 0x1F ) << 26 )
#define ADC_CFGR_AWD1CH_MASK ADC_CFGR_AWD1CH(ALL1)
#define ADC_CFGR_JQDIS(v) ( ( (v) & 0x1 ) << 31 )
#define ADC_CFGR_JQDIS_MASK ADC_CFGR_JQDIS(ALL1)

/* ADC CFGR2 register macros */

#define ADC_CFGR2_ROVSE(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_CFGR2_ROVSE_MASK ADC_CFGR2_ROVSE(ALL1)
#define ADC_CFGR2_JOVSE(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_CFGR2_JOVSE_MASK ADC_CFGR2_JOVSE(ALL1)
#define ADC_CFGR2_OVSR(v) ( ( (v) & 0x7 ) << 2 )
#define ADC_CFGR2_OVSR_MASK ADC_CFGR2_OVSR(ALL1)
#define ADC_CFGR2_OVSS(v) ( ( (v) & 0xf ) << 5 )
#define ADC_CFGR2_OVSS_MASK ADC_CFGR2_OVSS(ALL1)
#define ADC_CFGR2_TROVS(v) ( ( (v) & 0x1 ) << 9 )
#define ADC_CFGR2_TROVS_MASK ADC_CFGR2_TROVS(ALL1)
#define ADC_CFGR2_ROVSM(v) ( ( (v) & 0x1 ) << 10 )
#define ADC_CFGR2_ROVSM_MASK ADC_CFGR2_ROVSM(ALL1)

/* ADC SMPR1 register macros */

#define ADC_SMPR1_SMP0(v) ( ( (v) & 0x7 ) << 0 )
#define ADC_SMPR1_SMP0_MASK ADC_SMPR1_SMP0(ALL1)
#define ADC_SMPR1_SMP1(v) ( ( (v) & 0x7 ) << 3 )
#define ADC_SMPR1_SMP1_MASK ADC_SMPR1_SMP1(ALL1)
#define ADC_SMPR1_SMP2(v) ( ( (v) & 0x7 ) << 6 )
#define ADC_SMPR1_SMP2_MASK ADC_SMPR1_SMP2(ALL1)
#define ADC_SMPR1_SMP3(v) ( ( (v) & 0x7 ) << 9 )
#define ADC_SMPR1_SMP3_MASK ADC_SMPR1_SMP3(ALL1)
#define ADC_SMPR1_SMP4(v) ( ( (v) & 0x7 ) << 12 )
#define ADC_SMPR1_SMP4_MASK ADC_SMPR1_SMP4(ALL1)
#define ADC_SMPR1_SMP5(v) ( ( (v) & 0x7 ) << 15 )
#define ADC_SMPR1_SMP5_MASK ADC_SMPR1_SMP5(ALL1)
#define ADC_SMPR1_SMP6(v) ( ( (v) & 0x7 ) << 18 )
#define ADC_SMPR1_SMP6_MASK ADC_SMPR1_SMP6(ALL1)
#define ADC_SMPR1_SMP7(v) ( ( (v) & 0x7 ) << 21 )
#define ADC_SMPR1_SMP7_MASK ADC_SMPR1_SMP7(ALL1)
#define ADC_SMPR1_SMP8(v) ( ( (v) & 0x7 ) << 24 )
#define ADC_SMPR1_SMP8_MASK ADC_SMPR1_SMP8(ALL1)
#define ADC_SMPR1_SMP9(v) ( ( (v) & 0x7 ) << 27 )
#define ADC_SMPR1_SMP9_MASK ADC_SMPR1_SMP9(ALL1)
#define ADC_SMPR1_SMPPLUS(v) ( ( (v) & 0x1 ) << 31 )
#define ADC_SMPR1_SMPPLUS_MASK ADC_SMPR1_SMPPLUS(ALL1)

/* ADC SMPR2 register macros */

#define ADC_SMPR2_SMP10(v) ( ( (v) & 0x7 ) << 0 )
#define ADC_SMPR2_SMP10_MASK ADC_SMPR2_SMP10(ALL1)
#define ADC_SMPR2_SMP11(v) ( ( (v) & 0x7 ) << 3 )
#define ADC_SMPR2_SMP11_MASK ADC_SMPR2_SMP11(ALL1)
#define ADC_SMPR2_SMP12(v) ( ( (v) & 0x7 ) << 6 )
#define ADC_SMPR2_SMP12_MASK ADC_SMPR2_SMP12(ALL1)
#define ADC_SMPR2_SMP13(v) ( ( (v) & 0x7 ) << 9 )
#define ADC_SMPR2_SMP13_MASK ADC_SMPR2_SMP13(ALL1)
#define ADC_SMPR2_SMP14(v) ( ( (v) & 0x7 ) << 12 )
#define ADC_SMPR2_SMP14_MASK ADC_SMPR2_SMP14(ALL1)
#define ADC_SMPR2_SMP15(v) ( ( (v) & 0x7 ) << 15 )
#define ADC_SMPR2_SMP15_MASK ADC_SMPR2_SMP15(ALL1)
#define ADC_SMPR2_SMP16(v) ( ( (v) & 0x7 ) << 18 )
#define ADC_SMPR2_SMP16_MASK ADC_SMPR2_SMP16(ALL1)
#define ADC_SMPR2_SMP17(v) ( ( (v) & 0x7 ) << 21 )
#define ADC_SMPR2_SMP17_MASK ADC_SMPR2_SMP17(ALL1)
#define ADC_SMPR2_SMP18(v) ( ( (v) & 0x7 ) << 24 )
#define ADC_SMPR2_SMP18_MASK ADC_SMPR2_SMP18(ALL1)

/* ADC TR1 register macros */

#define ADC_TR1_HT1(v) ( ( (v) & 0xFFF ) << 16 )
#define ADC_TR1_HT1_MASK ADC_TR1_HT1(ALL1)
#define ADC_TR1_LT1(v) ( ( (v) & 0xFFF ) << 0 )
#define ADC_TR1_LT1_MASK ADC_TR1_LT1(ALL1)

/* ADC TR2 register macros */

#define ADC_TR2_HT2(v) ( ( (v) & 0xFFF ) << 16 )
#define ADC_TR2_HT2_MASK ADC_TR2_HT2(ALL1)
#define ADC_TR2_LT2(v) ( ( (v) & 0xFFF ) << 0 )
#define ADC_TR2_LT2_MASK ADC_TR2_LT2(ALL1)

/* ADC TR3 register macros */

#define ADC_TR3_HT3(v) ( ( (v) & 0xFFF ) << 16 )
#define ADC_TR3_HT3_MASK ADC_TR3_HT3(ALL1)
#define ADC_TR3_LT3(v) ( ( (v) & 0xFFF ) << 0 )
#define ADC_TR3_LT3_MASK ADC_TR3_LT3(ALL1)

/* ADC SQR1 register macros */

#define ADC_SQR1_L(v) ( ( (v) & 0xF ) << 0 )
#define ADC_SQR1_L_MASK ADC_SQR1_L(ALL1)
#define ADC_SQR1_SQ1(v) ( ( (v) & 0x1F ) << 6 )
#define ADC_SQR1_SQ1_MASK ADC_SQR1_SQ1(ALL1)
#define ADC_SQR1_SQ2(v) ( ( (v) & 0x1F ) << 12 )
#define ADC_SQR1_SQ2_MASK ADC_SQR1_SQ2(ALL1)
#define ADC_SQR1_SQ3(v) ( ( (v) & 0x1F ) << 18 )
#define ADC_SQR1_SQ3_MASK ADC_SQR1_SQ3(ALL1)
#define ADC_SQR1_SQ4(v) ( ( (v) & 0x1F ) << 24 )
#define ADC_SQR1_SQ4_MASK ADC_SQR1_SQ4(ALL1)

/* ADC SQR2 register macros */

#define ADC_SQR2_SQ5(v) ( ( (v) & 0x1F ) << 0 )
#define ADC_SQR2_SQ5_MASK ADC_SQR2_SQ5(ALL1)
#define ADC_SQR2_SQ6(v) ( ( (v) & 0x1F ) << 6 )
#define ADC_SQR2_SQ6_MASK ADC_SQR2_SQ6(ALL1)
#define ADC_SQR2_SQ7(v) ( ( (v) & 0x1F ) << 12 )
#define ADC_SQR2_SQ7_MASK ADC_SQR2_SQ7(ALL1)
#define ADC_SQR2_SQ8(v) ( ( (v) & 0x1F ) << 18 )
#define ADC_SQR2_SQ8_MASK ADC_SQR2_SQ8(ALL1)
#define ADC_SQR2_SQ9(v) ( ( (v) & 0x1F ) << 24 )
#define ADC_SQR2_SQ9_MASK ADC_SQR2_SQ9(ALL1)

/* ADC SQR3 register macros */

#define ADC_SQR3_SQ10(v) ( ( (v) & 0x1F ) << 0 )
#define ADC_SQR3_SQ10_MASK ADC_SQR3_SQ10(ALL1)
#define ADC_SQR3_SQ11(v) ( ( (v) & 0x1F ) << 6 )
#define ADC_SQR3_SQ11_MASK ADC_SQR3_SQ11(ALL1)
#define ADC_SQR3_SQ12(v) ( ( (v) & 0x1F ) << 12 )
#define ADC_SQR3_SQ12_MASK ADC_SQR3_SQ12(ALL1)
#define ADC_SQR3_SQ13(v) ( ( (v) & 0x1F ) << 18 )
#define ADC_SQR3_SQ13_MASK ADC_SQR3_SQ13(ALL1)
#define ADC_SQR3_SQ14(v) ( ( (v) & 0x1F ) << 24 )
#define ADC_SQR3_SQ14_MASK ADC_SQR3_SQ14(ALL1)

/* ADC SQR4 register macros */

#define ADC_SQR4_SQ15(v) ( ( (v) & 0x1F ) << 0 )
#define ADC_SQR4_SQ15_MASK ADC_SQR4_SQ15(ALL1)
#define ADC_SQR4_SQ16(v) ( ( (v) & 0x1F ) << 6 )
#define ADC_SQR4_SQ16_MASK ADC_SQR4_SQ16(ALL1)

/* ADC DR register macros */

#define ADC_DR_RDATA(v) ( ( (v) & 0xFFFF ) << 0 )
#define ADC_DR_RDATA_MASK ADC_DR_RDATA(ALL1)

/* ADC JSQR register macros */

#define ADC_JSQR_JL(v) ( ( (v) & 0x3 ) << 0 )
#define ADC_JSQR_JL_MASK ADC_JSQR_JL(ALL1)
#define ADC_JSQR_JEXTSEL(v) ( ( (v) & 0xF ) << 2 )
#define ADC_JSQR_JEXTSEL_MASK ADC_JSQR_JEXTSEL(ALL1)
#define ADC_JSQR_JEXTEN(v) ( ( (v) & 0x3 ) << 7 )
#define ADC_JSQR_JEXTEN_MASK ADC_JSQR_JEXTEN(ALL1)
#define ADC_JSQR_JSQ1(v) ( ( (v) & 0x1F ) << 9 )
#define ADC_JSQR_JSQ1_MASK ADC_JSQR_JSQ1(ALL1)
#define ADC_JSQR_JSQ2(v) ( ( (v) & 0x1F ) << 15 )
#define ADC_JSQR_JSQ2_MASK ADC_JSQR_JSQ2(ALL1)
#define ADC_JSQR_JSQ3(v) ( ( (v) & 0x1F ) << 21 )
#define ADC_JSQR_JSQ3_MASK ADC_JSQR_JSQ3(ALL1)
#define ADC_JSQR_JSQ4(v) ( ( (v) & 0x1F ) << 27 )
#define ADC_JSQR_JSQ4_MASK ADC_JSQR_JSQ4(ALL1)

/* ADC OFRy register macros */

#define ADC_OFRY_OFFSET(v) ( ( (v) & 0xFFF ) << 0 )
#define ADC_OFRY_OFFSET_MASK ADC_OFRY_OFFSET(ALL1)
#define ADC_OFRY_OFFSET_CH(v) ( ( (v) & 0x1F ) << 26 )
#define ADC_OFRY_OFFSET_CH_MASK ADC_OFRY_OFFSET_CH(ALL1)
#define ADC_OFRY_OFFSET_EN(v) ( ( (v) & 0x1 ) << 31 )
#define ADC_OFRY_OFFSET_EN_MASK ADC_OFRY_OFFSET_EN(ALL1)

/* ADC JDRy register macros */

#define ADC_JDRY_JDATA(v) ( ( (v) & 0xFFFF ) << 0 )
#define ADC_JDRY_JDATA_MASK ADC_JDRY_JDATA(ALL1)

/* ADC AWD2CR register macros */

#define ADC_AWD2CR_AWD2CH(v) ( ( (v) & 0x7FFFF ) << 0 )
#define ADC_AWD2CR_AWD2CH_MASK ADC_AWD2CR_AWD2CH(ALL1)

/* ADC AWD3CR register macros */

#define ADC_AWD3CR_AWD3CH(v) ( ( (v) & 0x7FFFF ) << 0 )
#define ADC_AWD3CR_AWD3CH_MASK ADC_AWD3CR_AWD3CH(ALL1)

/* ADC DIFSEL register macros */

#define ADC_DIFSEL_DIFSEL(v) ( ( (v) & 0x7FFFF ) << 0 )
#define ADC_DIFSEL_DIFSEL_MASK ADC_DIFSEL_DIFSEL(ALL1)

/* ADC CALFACT register macros */

#define ADC_CALFACT_CALFACT_S(v) ( ( (v) & 0x7F ) << 0 )
#define ADC_CALFACT_CALFACT_S_MASK ADC_CALFACT_CALFACT_S(ALL1)
#define ADC_CALFACT_CALFACT_D(v) ( ( (v) & 0x7F ) << 16 )
#define ADC_CALFACT_CALFACT_D_MASK ADC_CALFACT_CALFACT_D(ALL1)

/* ADC common CSR register macros */

#define ADC_CSR_ADRDY_MST(v) ( ( (v) & 0x1 ) << 0 )
#define ADC_CSR_ADRDY_MST_MASK ADC_CSR_ADRDY_MST(ALL1)
#define ADC_CSR_EOSMP_MST(v) ( ( (v) & 0x1 ) << 1 )
#define ADC_CSR_EOSMP_MST_MASK ADC_CSR_EOSMP_MST(ALL1)
#define ADC_CSR_EOC_MST(v) ( ( (v) & 0x1 ) << 2 )
#define ADC_CSR_EOC_MST_MASK ADC_CSR_EOC_MST(ALL1)
#define ADC_CSR_EOS_MST(v) ( ( (v) & 0x1 ) << 3 )
#define ADC_CSR_EOS_MST_MASK ADC_CSR_EOS_MST(ALL1)
#define ADC_CSR_OVR_MST(v) ( ( (v) & 0x1 ) << 4 )
#define ADC_CSR_OVR_MST_MASK ADC_CSR_OVR_MST(ALL1)
#define ADC_CSR_JEOC_MST(v) ( ( (v) & 0x1 ) << 5 )
#define ADC_CSR_JEOC_MST_MASK ADC_CSR_JEOC_MST(ALL1)
#define ADC_CSR_JEOS_MST(v) ( ( (v) & 0x1 ) << 6 )
#define ADC_CSR_JEOS_MST_MASK ADC_CSR_JEOS_MST(ALL1)
#define ADC_CSR_AWD1_MST(v) ( ( (v) & 0x1 ) << 7 )
#define ADC_CSR_AWD1_MST_MASK ADC_CSR_AWD1_MST(ALL1)
#define ADC_CSR_AWD2_MST(v) ( ( (v) & 0x1 ) << 8 )
#define ADC_CSR_AWD2_MST_MASK ADC_CSR_AWD2_MST(ALL1)
#define ADC_CSR_AWD3_MST(v) ( ( (v) & 0x1 ) << 9 )
#define ADC_CSR_AWD3_MST_MASK ADC_CSR_AWD3_MST(ALL1)
#define ADC_CSR_JQOVF_MST(v) ( ( (v) & 0x1 ) << 10 )
#define ADC_CSR_JQOVF_MST_MASK ADC_CSR_JQOVF_MST(ALL1)
#define ADC_CSR_ADRDY_SLV(v) ( ( (v) & 0x1 ) << 16 )
#define ADC_CSR_ADRDY_SLV_MASK ADC_CSR_ADRDY_SLV(ALL1)
#define ADC_CSR_EOSMP_SLV(v) ( ( (v) & 0x1 ) << 17 )
#define ADC_CSR_EOSMP_SLV_MASK ADC_CSR_EOSMP_SLV(ALL1)
#define ADC_CSR_EOC_SLV(v) ( ( (v) & 0x1 ) << 18 )
#define ADC_CSR_EOC_SLV_MASK ADC_CSR_EOC_SLV(ALL1)
#define ADC_CSR_EOS_SLV(v) ( ( (v) & 0x1 ) << 19 )
#define ADC_CSR_EOS_SLV_MASK ADC_CSR_EOS_SLV(ALL1)
#define ADC_CSR_OVR_SLV(v) ( ( (v) & 0x1 ) << 20 )
#define ADC_CSR_OVR_SLV_MASK ADC_CSR_OVR_SLV(ALL1)
#define ADC_CSR_JEOC_SLV(v) ( ( (v) & 0x1 ) << 21 )
#define ADC_CSR_JEOC_SLV_MASK ADC_CSR_JEOC_SLV(ALL1)
#define ADC_CSR_JEOS_SLV(v) ( ( (v) & 0x1 ) << 22 )
#define ADC_CSR_JEOS_SLV_MASK ADC_CSR_JEOS_SLV(ALL1)
#define ADC_CSR_AWD1_SLV(v) ( ( (v) & 0x1 ) << 23 )
#define ADC_CSR_AWD1_SLV_MASK ADC_CSR_AWD1_SLV(ALL1)
#define ADC_CSR_AWD2_SLV(v) ( ( (v) & 0x1 ) << 24 )
#define ADC_CSR_AWD2_SLV_MASK ADC_CSR_AWD2_SLV(ALL1)
#define ADC_CSR_AWD3_SLV(v) ( ( (v) & 0x1 ) << 25 )
#define ADC_CSR_AWD3_SLV_MASK ADC_CSR_AWD3_SLV(ALL1)
#define ADC_CSR_JQOVF_SLV(v) ( ( (v) & 0x1 ) << 26 )
#define ADC_CSR_JQOVF_SLV_MASK ADC_CSR_JQOVF_SLV(ALL1)

/* ADC common CCR register macros */

#define ADC_CCR_DUAL(v) ( ( (v) & 0x1F ) << 0 )
#define ADC_CCR_DUAL_MASK ADC_CCR_DUAL(ALL1)
#define ADC_CCR_DELAY(v) ( ( (v) & 0xF ) << 8 )
#define ADC_CCR_DELAY_MASK ADC_CCR_DELAY(ALL1)
#define ADC_CCR_DMACFG(v) ( ( (v) & 0x1 ) << 13 )
#define ADC_CCR_DMACFG_MASK ADC_CCR_DMACFG(ALL1)
#define ADC_CCR_MDMA(v) ( ( (v) & 0x3 ) << 14 )
#define ADC_CCR_MDMA_MASK ADC_CCR_MDMA(ALL1)
#define ADC_CCR_CKMODE(v) ( ( (v) & 0x3 ) << 16 )
#define ADC_CCR_CKMODE_MASK ADC_CCR_CKMODE(ALL1)
#define ADC_CCR_PRESC(v) ( ( (v) & 0xF ) << 18 )
#define ADC_CCR_PRESC_MASK ADC_CCR_PRESC(ALL1)
#define ADC_CCR_VREFEN(v) ( ( (v) & 0x1 ) << 22 )
#define ADC_CCR_VREFEN_MASK ADC_CCR_VREFEN(ALL1)
#define ADC_CCR_CH17SEL(v) ( ( (v) & 0x1 ) << 23 )
#define ADC_CCR_CH17SEL_MASK ADC_CCR_CH17SEL(ALL1)
#define ADC_CCR_CH18SEL(v) ( ( (v) & 0x1 ) << 24 )
#define ADC_CCR_CH18SEL_MASK ADC_CCR_CH18SEL(ALL1)

/* ADC common CDR register macros */

#define ADC_CDR_RDATA_MST(v) ( ( (v) & 0xFFFF ) << 0 )
#define ADC_CDR_RDATA_MST_MASK ADC_CDR_RDATA_MST(ALL1)
#define ADC_CDR_RDATA_SLV(v) ( ( (v) & 0xFFFF ) << 16 )
#define ADC_CDR_RDATA_SLV_MASK ADC_CDR_RDATA_SLV(ALL1)

#endif

