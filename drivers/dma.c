#include "dma.h"
#include "interrupt.h"
#include <m4/nvic.h>
#include <stm32l432kc/dma.h>
#include <stm32l432kc/rcc.h>
#include <stdbool.h>
#include <stdint.h>

#define NUM_DMA_PERIPHERALS 2
#define NUM_DMA_CHANNELS 7
#define NUM_TOTAL_CHANNELS NUM_DMA_PERIPHERALS * NUM_DMA_CHANNELS

#ifndef NUM_DMA_CALLBACKS
#define NUM_DMA_CALLBACKS 5
#endif

#define DMA1_CH1_IRQ 11
#define DMA1_CH2_IRQ 12
#define DMA1_CH3_IRQ 13
#define DMA1_CH4_IRQ 14
#define DMA1_CH5_IRQ 15
#define DMA1_CH6_IRQ 16
#define DMA1_CH7_IRQ 17

#define DMA2_CH1_IRQ 56
#define DMA2_CH2_IRQ 57
#define DMA2_CH3_IRQ 58
#define DMA2_CH4_IRQ 59
#define DMA2_CH5_IRQ 60
#define DMA2_CH6_IRQ 68
#define DMA2_CH7_IRQ 69

#define DMA_IRQ_PRI 15

static void ( *callback[NUM_TOTAL_CHANNELS][NUM_DMA_CALLBACKS] )(void);
static uint32_t num_callbacks[NUM_TOTAL_CHANNELS];

uint8_t const dma1_irq_LUT[NUM_DMA_CHANNELS] = {
    DMA1_CH1_IRQ,
    DMA1_CH2_IRQ,
    DMA1_CH3_IRQ,
    DMA1_CH4_IRQ,
    DMA1_CH5_IRQ,
    DMA1_CH6_IRQ,
    DMA1_CH7_IRQ
};

uint8_t const dma2_irq_LUT[NUM_DMA_CHANNELS] = {
    DMA2_CH1_IRQ,
    DMA2_CH2_IRQ,
    DMA2_CH3_IRQ,
    DMA2_CH4_IRQ,
    DMA2_CH5_IRQ,
    DMA2_CH6_IRQ,
    DMA2_CH7_IRQ
};

/* ISR helper function for all DMA channels */

static void dma_isr (
        dma_t * regs, 
        dma_channel ch, 
        void (**cb)(void), 
        uint32_t num_callbacks 
);

static void dma_isr (
        dma_t * regs, 
        dma_channel ch, 
        void (**cb)(void), 
        uint32_t num_callbacks 
) {
    /* Clear all interrupt flags for channel */
    
    regs->IFCR = DMA_IFCR_MASK(ch);

    for (uint32_t i = 0; i < num_callbacks; i++) {
        cb[i]();
    }
}

/* Configure clock, NVIC, and IRQ priority for DMA channel */

void configure_dma(dma_t * regs, dma_channel ch) {
    uint8_t irq;

    /* Clock enable and IRQ number selection */

    if (regs == DMA1) {
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN(1);
        irq = dma1_irq_LUT[ch];
    } else {
        RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN(1);
        irq = dma2_irq_LUT[ch];
    }

    /*  NVIC IRQ enable and priority */

    uint8_t en_index = irq / 32;
    uint8_t pri_index = irq / 4;

    NVIC->ISER[en_index] = NVIC_ISER_SETENA(1, irq);
    NVIC->IPR[pri_index] = 
        ( NVIC->IPR[pri_index] & ~NVIC_IPR_PRI_MASK(irq) ) 
        | NVIC_IPR_PRI(irq, DMA_IRQ_PRI);
}

/* Configure DMA controller and begin data transfers */

void dma_start(dma_handle_t * handler) {
    dma_t * dma = handler->regs;
    dma_config_t opts = handler->opts;
    dma_channel_t * ch = &dma->CHANNEL[opts.ch];

    /* Reset the channel in the case of reconfiguration */

    ch->CCR &= ~DMA_CCR_EN_MASK; // Must disable channel to modify bits
    while (ch->CCR & DMA_CCR_EN_MASK);
    ch->CCR = 0;

    dma->IFCR = DMA_IFCR_MASK(opts.ch);

    /* Set number of transfers and source/destination address */

    ch->CPAR = DMA_CPAR_PA(opts.p_addr);
    ch->CMAR = DMA_CMAR_MA(opts.m_addr);
    ch->CNDTR = DMA_CNDTR_NDT(opts.num_transfers);

    dma->CSELR = ( dma->CSELR & ~DMA_CSELR_MASK(opts.ch) )
        | DMA_CSELR(opts.ch, opts.ch_sel);

    /* Configure DMA options */

    ch->CCR =
          DMA_CCR_MEM2MEM(opts.mode >> 1)
        | DMA_CCR_PL(opts.prio)
        | DMA_CCR_MSIZE(opts.m_size)
        | DMA_CCR_PSIZE(opts.p_size)
        | DMA_CCR_MINC(opts.m_inc)
        | DMA_CCR_PINC(opts.p_inc)
        | DMA_CCR_CIRC(opts.circular)
        | DMA_CCR_DIR(opts.mode & 1)
        | DMA_CCR_TEIE(0)
        | DMA_CCR_HTIE(0)
        | DMA_CCR_TCIE(1)
        | DMA_CCR_EN(1);
}

/* Add a callback function to IRQ */

_Bool register_dma_callback( dma_t * regs, dma_channel c, void (*cb)(void) ) {
    uint8_t index = (regs == DMA1) ? c : c + NUM_DMA_CHANNELS;

    if ( num_callbacks[index] == NUM_DMA_CALLBACKS ) {
        return false;
    }
    
    callback[index][ num_callbacks[index]++ ] = cb;
    
    return true;
}

/* DMA1 channel ISRs */

void __attribute__( (interrupt) ) DMA1_CH1_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_1, callback[0], num_callbacks[0] );
}

void __attribute__( (interrupt) ) DMA1_CH2_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_2, callback[1], num_callbacks[1] );
}

void __attribute__( (interrupt) ) DMA1_CH3_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_3, callback[2], num_callbacks[2] );
}

void __attribute__( (interrupt) ) DMA1_CH4_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_4, callback[3], num_callbacks[3] );
}

void __attribute__( (interrupt) ) DMA1_CH5_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_5, callback[4], num_callbacks[4] );
}

void __attribute__( (interrupt) ) DMA1_CH6_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_6, callback[5], num_callbacks[5] );
}

void __attribute__( (interrupt) ) DMA1_CH7_Handler(void) {
    dma_isr( DMA1, DMA_CHANNEL_7, callback[6], num_callbacks[6] );
}

/* DMA2 channel ISRs */

void __attribute__( (interrupt) ) DMA2_CH1_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_1, callback[7], num_callbacks[7] );
}

void __attribute__( (interrupt) ) DMA2_CH2_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_2, callback[8], num_callbacks[8] );
}

void __attribute__( (interrupt) ) DMA2_CH3_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_3, callback[9], num_callbacks[9] );
}

void __attribute__( (interrupt) ) DMA2_CH4_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_4, callback[10], num_callbacks[10] );
}

void __attribute__( (interrupt) ) DMA2_CH5_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_5, callback[11], num_callbacks[11] );
}

void __attribute__( (interrupt) ) DMA2_CH6_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_6, callback[12], num_callbacks[12] );
}

void __attribute__( (interrupt) ) DMA2_CH7_Handler(void) {
    dma_isr( DMA2, DMA_CHANNEL_7, callback[13], num_callbacks[13] );
}

