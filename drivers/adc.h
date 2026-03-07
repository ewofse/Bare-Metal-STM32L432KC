#ifndef ADC_H
#define ADC_H

#include <stm32l432kc/adc.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ADC_CHANNEL_0  = 0x00001,
    ADC_CHANNEL_1  = 0x00002,
    ADC_CHANNEL_2  = 0x00004,
    ADC_CHANNEL_3  = 0x00008,
    ADC_CHANNEL_4  = 0x00010,
    ADC_CHANNEL_5  = 0x00020,
    ADC_CHANNEL_6  = 0x00040,
    ADC_CHANNEL_7  = 0x00080,
    ADC_CHANNEL_8  = 0x00100,
    ADC_CHANNEL_9  = 0x00200,
    ADC_CHANNEL_10 = 0x00400,
    ADC_CHANNEL_11 = 0x00800,
    ADC_CHANNEL_12 = 0x01000,
    ADC_CHANNEL_13 = 0x02000,
    ADC_CHANNEL_14 = 0x04000,
    ADC_CHANNEL_15 = 0x08000,
    ADC_CHANNEL_16 = 0x10000,
    ADC_CHANNEL_17 = 0x20000,
    ADC_CHANNEL_18 = 0x40000
} adc_channel;

typedef enum {
    ADC_MODE_SINGLE,
    ADC_MODE_CONTINUOUS
} adc_mode;

typedef enum {
    ADC_TRIGGER_NONE,
    ADC_TRIGGER_RISE,
    ADC_TRIGGER_FALL,
    ADC_TRIGGER_RISEFALL
} adc_trigger

typedef enum {
    ADC_RESOLUTION_12BIT,
    ADC_RESOLUTION_10BIT,
    ADC_RESOLUTION_8BIT,
    ADC_RESOLUTION_6BIT
} adc_resolution;

typedef enum {
    ADC_DMA_NONE,
    ADC_DMA_ONESHOT,
    ADC_DMA_CONTINUOUS
} acd_dma;

typedef ADC_REG_BLOCKS volatile adc_t;
typedef ADC_COMMON_REG_BLOCKS volatile adc_common_t;

typedef struct {
    adc_channel ch;
    adc_resolution res;
    adc_trigger trig;
    adc_dma dma;
    adc_mode mode;
} adc_config_t;

typedef struct {
    adc_t * regs;
    adc_config_t config;
} adc_handle_t;

void configure_adc(adc_handle_t * handler);
void adc_start(adc_handle_t * handler);
_Bool register_adc_callback( void (*cb)(void) );
_Bool get_irq_status_for_adc(adc_handle_t * handler);

#endif

