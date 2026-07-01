#include "adc.h"
#include "dma.h"
#include <m4/nvic.h>
#include <stm32l432kc/adc.h>
#include <stm32l432kc/rcc.h>
#include <util/cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef NUM_ADC_CALLBACKS
#define NUM_ADC_CALLBACKS 5
#endif

#define NUM_ADC_CHANNELS 19
#define MAX_CHANNEL_SEQ NUM_ADC_CHANNELS - 3

#define ADC1_2_IRQ 18
#define ADC1_2_IRQ_PRI 15

static void ( *callback[NUM_ADC_CALLBACKS] )(void);
static uint32_t num_callbacks;

static cbuffer_t adc_fifo[NUM_ADC_CHANNELS];
static uint8_t ch_cnt;
static uint8_t ch_idx[MAX_CHANNEL_SEQ];

/* Setup the ADC */

void configure_adc(adc_handle_t * handler) {
    adc_t * adc = handler->regs;
    adc_config_t opts = handler->opts;

    // Reset channel sequences in case of reconfiguration
    ch_cnt = 0;
    
    for (uint8_t i = 0; i < MAX_CHANNEL_SEQ; i++) {
        ch_idx[i] = 0;
    }
    
    /* Clock selection and enable */

    RCC->CCIPR &= ~RCC_CCIPR_ADCSEL_MASK;
    RCC->CCIPR |= RCC_CCIPR_ADCSEL(3);
    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN(1);

    /* IRQ enable and priority */

    NVIC->ISER[0] = NVIC_ISER_SETENA(1, ADC1_2_IRQ);

    NVIC->IPR[4] =
            (NVIC->IPR[4] & ~NVIC_IPR4_PRI_18_MASK) 
          | NVIC_IPR4_PRI_18(ADC1_2_IRQ_PRI);

    /* Startup sequence */

    adc->ISR = ADC_ISR_ADRDY_MASK;

    adc->CR =
          ADC_CR_ADCAL(0)
        | ADC_CR_ADCALDIF(0)
        | ADC_CR_DEEPPWD(0) // Disable deep power down
        | ADC_CR_ADVREGEN(1) // Enable internal voltage regulator
        | ADC_CR_JADSTP(0)
        | ADC_CR_ADSTP(0)
        | ADC_CR_JADSTART(0)
        | ADC_CR_ADSTART(0)
        | ADC_CR_ADDIS(0)
        | ADC_CR_ADEN(0);

    for (uint32_t volatile i = 0; i < 1280; i++); // Need 20 us delay

    /* Calibrate the ADC */

    adc->CR |= ADC_CR_ADCAL(1);

    while (adc->CR & ADC_CR_ADCAL_MASK);

    /* Peripheral configurations */

    adc->IER =
          ADC_IER_JQOVFIE(0)
        | ADC_IER_AWD3IE(0)
        | ADC_IER_AWD2IE(0)
        | ADC_IER_AWD1IE(0)
        | ADC_IER_JEOSIE(0)
        | ADC_IER_JEOCIE(0)
        | ADC_IER_OVRIE( (_Bool) !opts.dma )
        | ADC_IER_EOSIE( (_Bool) !opts.dma )
        | ADC_IER_EOCIE( (_Bool) !opts.dma )
        | ADC_IER_EOSMPIE(0)
        | ADC_IER_ADRDYIE(0);

    adc->CFGR = 
          ADC_CFGR_JQDIS(1)
        | ADC_CFGR_AWD1CH(0)
        | ADC_CFGR_JAUTO(0)
        | ADC_CFGR_JAWD1EN(0)
        | ADC_CFGR_AWD1EN(0)
        | ADC_CFGR_AWD1SGL(0)
        | ADC_CFGR_JQM(0)
        | ADC_CFGR_JDISCEN(0)
        | ADC_CFGR_DISCNUM(0)
        | ADC_CFGR_DISCEN(0)
        | ADC_CFGR_AUTDLY(0)
        | ADC_CFGR_CONT(opts.mode)
        | ADC_CFGR_OVRMOD(0)
        | ADC_CFGR_EXTEN(opts.trig)
        | ADC_CFGR_EXTSEL(opts.trigsel)
        | ADC_CFGR_ALIGN(1)
        | ADC_CFGR_RES(opts.res)
        | ADC_CFGR_DFSDMCFG(0)
        | ADC_CFGR_DMACFG(1)
        | ADC_CFGR_DMAEN( (_Bool) opts.dma );

    adc->CFGR2 = 
          ADC_CFGR2_ROVSM(0)
        | ADC_CFGR2_TROVS(0)
        | ADC_CFGR2_OVSS(0)
        | ADC_CFGR2_OVSR(0)
        | ADC_CFGR2_JOVSE(0)
        | ADC_CFGR2_ROVSE(0);

    /* Channel sequence selection */

    adc_channel ch = opts.ch;
    uint8_t index = 0;

    while (ch) {
        if (ch & 1) {
            ch_idx[ch_cnt++] = index;
        }

        ch >>= 1;
        index++;
    }

    adc->SQR1 =
          ADC_SQR1_SQ4( ch_idx[3] )
        | ADC_SQR1_SQ3( ch_idx[2] )
        | ADC_SQR1_SQ2( ch_idx[1] )
        | ADC_SQR1_SQ1( ch_idx[0] )
        | ADC_SQR1_L(ch_cnt - 1);

    adc->SQR2 =
          ADC_SQR2_SQ9( ch_idx[8] )
        | ADC_SQR2_SQ8( ch_idx[7] )
        | ADC_SQR2_SQ7( ch_idx[6] )
        | ADC_SQR2_SQ6( ch_idx[5] )
        | ADC_SQR2_SQ5( ch_idx[4] );

    adc->SQR3 =
          ADC_SQR3_SQ14( ch_idx[13] )
        | ADC_SQR3_SQ13( ch_idx[12] )
        | ADC_SQR3_SQ12( ch_idx[11] )
        | ADC_SQR3_SQ11( ch_idx[10] )
        | ADC_SQR3_SQ10( ch_idx[9] );

    adc->SQR4 =
          ADC_SQR4_SQ16( ch_idx[15] )
        | ADC_SQR4_SQ15( ch_idx[14] );

    /* Set channel sample time */

    adc->SMPR1 = 
          ADC_SMPR1_SMPPLUS(0)
        | ADC_SMPR1_SMP9(3)
        | ADC_SMPR1_SMP8(3)
        | ADC_SMPR1_SMP7(3)
        | ADC_SMPR1_SMP6(3)
        | ADC_SMPR1_SMP5(3)
        | ADC_SMPR1_SMP4(3)
        | ADC_SMPR1_SMP3(3)
        | ADC_SMPR1_SMP2(3)
        | ADC_SMPR1_SMP1(3)
        | ADC_SMPR1_SMP0(3);

    adc->SMPR2 = 
          ADC_SMPR2_SMP18(3)
        | ADC_SMPR2_SMP17(3)
        | ADC_SMPR2_SMP16(3)
        | ADC_SMPR2_SMP15(3)
        | ADC_SMPR2_SMP14(3)
        | ADC_SMPR2_SMP13(3)
        | ADC_SMPR2_SMP12(3)
        | ADC_SMPR2_SMP11(3)
        | ADC_SMPR2_SMP10(3);

    adc->CR |= ADC_CR_ADEN(1);

    while ( !(adc->ISR & ADC_ISR_ADRDY_MASK) );
}

/* Begin sampling */

void start_adc(adc_handle_t * handler) {
    adc_t * adc = handler->regs;

    adc->CR |= ADC_CR_ADSTART(1);
}

/* Pause sampling */

void pause_adc(adc_handle_t * handler) {
    adc_t * adc = handler->regs;

    adc->CR &= ~ADC_CR_ADSTART_MASK;
}

/* Retrieve one sample from FIFO  */

_Bool get_adc_conversion_result(adc_channel ch, uint16_t * data) {
    return cbuffer_read( &adc_fifo[ch], (uint8_t *) data );
}

/* Obtain the FIFO of samples (for DMA) */

cbuffer_t * get_adc_fifo(adc_channel ch) {
    return &adc_fifo[ch];
}

/* Add a callback function to IRQ */

_Bool register_adc_callback( void (*cb)(void) ) {
    if (num_callbacks == NUM_ADC_CALLBACKS) {
        return false;
    }

    callback[num_callbacks++] = cb;

    return true;
}

/* ADC 1 & 2 ISR (shared) */

void __attribute__( (interrupt) ) ADC1_2_Handler(void) {
    static adc_channel ch;

    if (ADC1->ISR & ADC_ISR_EOC_MASK) {
        ADC1->ISR = ADC_ISR_EOC_MASK;

        uint8_t data = (uint8_t) ( (ADC1->DR & ADC_DR_RDATA_MASK) >> 8 );

        cbuffer_write( &adc_fifo[ ch_idx[ch++] ], data );
    }

    if (ADC1->ISR & ADC_ISR_EOS_MASK) {
        ADC1->ISR = ADC_ISR_EOS_MASK;
        ch = 0;
    }

    if (ADC1->ISR & ADC_ISR_OVR_MASK) {
        ADC1->ISR = ADC_ISR_OVR_MASK;
        ch = 0;
    }

    for (uint32_t i = 0; i < num_callbacks; i++) {
        callback[i]();
    }
}

