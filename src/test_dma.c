#include "dma.h"
#include "usart.h"
#include "led.h"
#include "interrupt.h"
#include <printf.h>
#include <stdbool.h>

#define USART_BAUD_RATE 115200

int (* _stdout_putchar)(char c);

void main(void) {
    disable_irq();
    
    dma_config_t dma1_ch1_config = {
        .mode = DMA_MODE_M2M,
        .p_size = DMA_SIZE_8,
        .m_size = DMA_SIZE_8,
        .prio = DMA_PRIORITY_LOW,
        .ch = DMA_CHANNEL_1,
        .p_addr = 0,
        .m_addr = 0,
        .num_transfers = 25,
        .p_inc = true,
        .m_inc = true,
        .circular = false,
        .ch_sel = 0
    };

    dma_handle_t dma1_ch1_handle = {
        .regs = DMA1,
        .opts = dma1_ch1_config
    };

    configure_dma(&dma1_ch1_handle);

    dma_config_t dma1_ch6_config = {
        .mode = DMA_MODE_P2M,
        .p_size = DMA_SIZE_8,
        .m_size = DMA_SIZE_8,
        .prio = DMA_PRIORITY_LOW,
        .ch = DMA_CHANNEL_6,
        .p_addr = (uint32_t) &(USART2->RDR),
        .m_addr = 0,
        .num_transfers = 50,
        .p_inc = false,
        .m_inc = true,
        .circular = false,
        .ch_sel = 2 
    };

    dma_handle_t dma1_ch6_handle = {
        .regs = DMA1,
        .opts = dma1_ch6_config
    };

    configure_dma(&dma1_ch6_handle);

    dma_config_t dma1_ch7_config = {
        .mode = DMA_MODE_M2P,
        .p_size = DMA_SIZE_8,
        .m_size = DMA_SIZE_8,
        .prio = DMA_PRIORITY_LOW,
        .ch = DMA_CHANNEL_7,
        .p_addr = (uint32_t) &(USART2->TDR),
        .m_addr = 0,
        .num_transfers = 40,
        .p_inc = false,
        .m_inc = true,
        .circular = false,
        .ch_sel = 2 
    };

    dma_handle_t dma1_ch7_handle = {
        .regs = DMA1,
        .opts = dma1_ch7_config
    };

    configure_dma(&dma1_ch7_handle);

    register_dma_callback(&dma1_ch1_handle, toggle_led);
    register_dma_callback(&dma1_ch6_handle, toggle_led);
    register_dma_callback(&dma1_ch7_handle, toggle_led);

    usart_config_t usart2_config = {
        .baud_rate = USART_BAUD_RATE,
        .rx_pin = USART2_RX_PIN_PA15,
        .tx_pin = USART2_TX_PIN_PA2,
        .mode = USART_MODE_RXTX,
        .word = USART_WORD_8N1,
        .stop = USART_STOP_ONE,
        .dma = USART_DMA_RXTX
    };

    usart_handle_t usart2_handle = {
        .regs = USART2,
        .opts = usart2_config 
    };

    configure_usart(&usart2_handle);

    configure_led();

    enable_irq();

    char const src_ch1[] = "M2M has been perfomed.\n\r";
    char dest_ch1[50] = "No M2M has been performed.\n\r";
    char const src_ch7[] = "M2P has been performed through USART.\n\r";
    char dest_ch6[51] = "No P2M has been performed.\n\r";

    _stdout_putchar = usart_putchar_stdout;

    while (true) {
        wait_for_interrupt();

        char c;

        while ( !usart_getchar(&usart2_handle, &c) );

        switch (c) {
            /* Memory to memory transfer */

            case '1':
                dma1_ch1_handle.opts.p_addr = (uint32_t) src_ch1;
                dma1_ch1_handle.opts.m_addr = (uint32_t) dest_ch1;
                dma_start(&dma1_ch1_handle);

                break;

            /* Memory to peripheral transfer */

            case '2':
                dma1_ch7_handle.opts.m_addr = (uint32_t) src_ch7;
                dma_start(&dma1_ch7_handle);

                break;

            /* Peripheral to memory transfer */

            case '3':
                dma1_ch6_handle.opts.m_addr = (uint32_t) dest_ch6;
                dma_start(&dma1_ch6_handle);

                dest_ch6[50] = 0;

                break;

            case 'p':
                printf("%s\n\r", dest_ch1);
                printf("%s\n\r", dest_ch6);

                break;
        };
    }
}

