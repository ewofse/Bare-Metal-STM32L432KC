#include "adc.h"
#include "dma.h"
#include <m4/nvic.h>
#include <stm32l432kc/adc.h>
#include <stm32l432kc/rcc.h>
#include <util/cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#define NUM_ADC_PERIPHERALS 2

#ifndef NUM_ADC_CALLBACKS
#define NUM_ADC_CALLBACKS 5
#endif

#define ADC1_2_IRQ 18
#define ADC1_2_PRI 15

static void ( *callback[NUM_ADC_CALLBACKS] )(void);
static uint32_t num_callbacks;

void configure_adc(adc_handle_t * handler) {
    adc_t * adc = handler->regs;
    adc_config_t opts = handler->opts;
    
    /* Clock selection and enable */

    RCC->CCIPR &= ~RCC_CCIPR_ADCSEL_MASK;
    RCC->CCIPR |= RCC_CCIPR_ADCSEL(3);
    RRC->AHB2ENR |= RCC_AHB2ENR_ADCEN(1);

    adc->IER =
          ADC_IER_JQOVFIE(0)
        | ADC_IER_AWD3IE(0)
        | ADC_IER_AWD2IE(0)
        | ADC_IER_AWD1IE(0)
        | ADC_IER_JEOSIE(0)
        | ADC_IER_JEOCIE(0)
        | ADC_IER_OVRIE(0)
        | ADC_IER_EOSIE(0)
        | ADC_IER_EOSMPIE(0)
        | ADC_IER_ADRDYIE( (_Bool) opts.dma );

    adc->CR =
          ADC_CR_ADCAL(0)
        | ADC_CR_ADCALDIF(0)
        | ADC_CR_DEEPPWD(0)
        | ADC_CR_ADVREGEN(1)
        | ADC_CR_JADSTP(0)
        | ADC_CR_ADSTP(0)
        | ADC_CR_JADSTART(0)
        | ADC_CR_ADSTART(0)
        | ADC_CR_ADDIS(0)
        | ADC_CR_ADEN(0);

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
        | ADC_CFGR_EXTSEL(0)
        | ADC_CFGR_ALIGN(0)
        | ADC_CFGR_RES(opts.res)
        | ADC_CFGR_DFSDMCFG(0)
        | ADC_CFGR_DMACFG(1)
        | ADC_CFGR_DMAEN( (_Bool) opts.dma );
}

void adc_start(void) {
}

_Bool register_adc_callback( void (*cb)(void) ) {
    if (num_callbacks == NUM_ADC_CALLBACKS) {
        return false;
    }

    callback[num_callbacks++] = cb;

    return true;
}

