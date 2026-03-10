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

#define ADC1_2_IRQ 18
#define ADC1_2_IRQ_PRI 15

static void ( *callback[NUM_ADC_CALLBACKS] )(void);
static uint32_t num_callbacks;

static cbuffer_t adc_fifo[NUM_ADC_CHANNELS];
static uint8_t ch_cnt;

/* Setup the ADC */

void configure_adc(adc_handle_t * handler) {
    adc_t * adc = handler->regs;
    adc_config_t opts = handler->opts;
    
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
        | ADC_IER_OVRIE(0)
        | ADC_IER_EOSIE(0)
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

    while (ch) {
        ch_cnt++;
        ch >>= 1;
    }

    for (uint8_t i = 0; i < ch_cnt; i++) {
        continue;
    }

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

_Bool get_adc_conversion_result(adc_channel ch, uint8_t * data) {
    return cbuffer_read(&adc_fifo[ch], data);
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

    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, ADC1_2_IRQ);

    if (ADC1->ISR & ADC_ISR_EOC_MASK) {
        ADC1->ISR = ADC_ISR_EOC_MASK;

        uint8_t data = (uint8_t) ( (ADC1->DR & ADC_DR_RDATA_MASK) >> 8 );

        cbuffer_write(&adc_fifo[ch], data);
        
        ch = (ch == ch_cnt) ? 0 : ch + 1;

        // TODO add overrun safety
    }

    for (uint32_t i = 0; i < num_callbacks; i++) {
        callback[i]();
    }
}

