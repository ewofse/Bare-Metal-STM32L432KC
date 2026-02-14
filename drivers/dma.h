#ifndef DMA_H
#define DMA_H

#include <stm32l432kc/dma.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DMA_MODE_P2M,
    DMA_MODE_M2P,
    DMA_MODE_M2M,
    DMA_MODE_P2P = 4 // Bit 1 must be 0
} dma_mode;

typedef enum {
    DMA_SIZE_8,
    DMA_SIZE_16,
    DMA_SIZE_32
} dma_transfer_size;

typedef enum {
    DMA_PRIORITY_LOW,
    DMA_PRIORITY_MEDIUM,
    DMA_PRIORITY_HIGH,
    DMA_PRIORITY_VERY_HIGH
} dma_prio;

typedef enum {
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7
} dma_channel;

typedef DMA_REG_BLOCKS volatile dma_t;
typedef DMA_CHANNEL_REG_BLOCKS volatile dma_channel_t;

typedef struct {
    uint32_t p_addr;
    uint32_t m_addr;
    uint16_t num_transfers;
    _Bool p_inc;
    _Bool m_inc;
    _Bool circular;
    uint8_t ch_sel           : 4;
    dma_mode mode            : 3;
    dma_channel ch           : 3;
    dma_transfer_size p_size : 2;
    dma_transfer_size m_size : 2;
    dma_prio prio            : 2;
} dma_config_t;

typedef struct {
    dma_t * regs;
    dma_config_t opts;
} dma_handle_t;

void configure_dma(dma_t * regs, dma_channel ch);
void dma_start(dma_handle_t * handler);
_Bool register_dma_callback( dma_t * regs, dma_channel ch, void (*cb)(void) );

#endif

