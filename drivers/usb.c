#include "usb.h"
#include <m4/nvic.h>
#include <stm32l432kc/usb.h>
#include <stm32l432kc/rcc.h>
#include <stm32l432kc/crs.h>
#include <stm32l432kc/pwr.h>
#include <stdbool.h>
#include <stdint.h>

#define USB_IRQ 0
#define USB_IRQ_PRI 15

static uint8_t control_packet[8];

static void write_pma_data(uint16_t pma_byte_offest, uint8_t const * src,
        uint16_t byte_count);
static void read_pma_data(uint16_t pma_byte_offset, uint8_t * dest, 
        uint16_t byte_count);

/* Write data to the USB SRAM (PMA) */

static void write_pma_data(uint16_t pma_byte_offset, uint8_t const * src, 
        uint16_t byte_count) {
    uint16_t pma_index = (pma_byte_offset - 64) / 2;

    /* Group the data bytes into half words and store into the USB SRAM */

    for ( uint16_t i = 0; i < (byte_count + 1) / 2; i++ ) {
        uint16_t half_word = src[i * 2];
        
        if ( (i * 2 + 1) < byte_count ) {
            half_word |= ( src[i * 2 + 1] << 8 );
        }

        USB_SRAM->PMA[pma_index++] = half_word;
    }
}

/* Read data from the USB SRAM (PMA) */

static void read_pma_data(uint16_t pma_byte_offset, uint8_t * dest, 
        uint16_t byte_count) {
    uint16_t pma_index = (pma_byte_offset - 64) / 2;

    /* Extract half words from PMA and store into a byte array */

    for ( uint16_t i = 0; i < (byte_count + 1) / 2; i++ ) {
        uint16_t half_word = USB_SRAM->PMA[pma_index++];
        
        dest[i * 2] = half_word & 0xFF;
        
        if ( (i * 2 + 1) < byte_count ) {
            dest[i * 2 + 1] = (half_word >> 8) & 0xFF;
        }
    }
}

/* Configure USB as Virtual COM/CDC */

void configure_usb(void) {
    /* Enable required independent VDD for USB peripheral */

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN(1);
    PWR->CR2 |= PWR_CR2_USV(1);

    /* Enable USB clock with autotrim for needed improved stability for USB */

    RCC->APB1ENR1 |= RCC_APB1ENR1_CRSEN(1);
    CRS->CR |= CRS_CR_AUTOTRIMEN(1) | CRS_CR_CEN(1);
    RCC->APB1ENR1 |= RCC_APB1ENR1_USBFSEN(1);

    /* GPIO setup */

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN(1);

    GPIOA->MODER &= ~(GPIOA_MODER_MODE11_MASK | GPIOA_MODER_MODE12_MASK);
    GPIOA->MODER |= GPIOA_MODER_MODE11(2) | GPIOA_MODER_MODE12(2);

    GPIOA->AFR[1] &= ~(GPIOA_AFR_AFSEL11_MASK | GPIOA_AFR_AFSEL12_MASK);
    GPIOA->AFR[1] |= GPIOA_AFR_AFSEL11(10) | GPIOA_AFR_AFSEL12(10);

    /* Initialize peripheral with USB reset */

    USB_FS->CNTR = USB_CNTR_FRES(1);
    for (uint32_t volatile i = 0; i < 1280; i++); // 20 us delay
    USB_FS->CNTR &= ~USB_CNTR_FRES_MASK;

    USB_FS->ISTR = 0;
    USB_FS->BTABLE = USB_BTABLE_BTABLE(0);

    /* Build BDT endpoint entires for Virtual COM Port/CDC */

    USB_SRAM->BDT[0].ADDR_TX  = 0x40;
    USB_SRAM->BDT[0].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[0].ADDR_RX  = 0x80;
    USB_SRAM->BDT[0].COUNT_RX = 
          USB_COUNT_RX_BLSIZE(1)
        | USB_COUNT_RX_NUM_BLOCK(1);

    USB_SRAM->BDT[1].ADDR_TX  = 0xC0;
    USB_SRAM->BDT[1].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[1].ADDR_RX  = 0;
    USB_SRAM->BDT[1].COUNT_RX = 0;

    USB_SRAM->BDT[2].ADDR_TX  = 0xD0;
    USB_SRAM->BDT[2].COUNT_TX = USB_COUNT_TX_COUNT_TX(0);
    USB_SRAM->BDT[2].ADDR_RX  = 0x110;
    USB_SRAM->BDT[2].COUNT_RX = 
          USB_COUNT_RX_BLSIZE(1)
        | USB_COUNT_RX_NUM_BLOCK(1);

    USB_FS->CNTR = USB_CNTR_RESETM(1) | USB_CNTR_CTRM(1);
    USB_FS->BCDR |= USB_BCDR_DPPU(1);
}

void __attribute__( (interrupt) ) USB_FS_Handler(void) {
    ;
}

