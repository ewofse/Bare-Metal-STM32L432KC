#include "gpio.h"
#include <m4/nvic.h>
#include <stm32l432kc/exti.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef NUM_EXTI0_CALLBACKS
#define NUM_EXTI0_CALLBACKS 5
#endif

#ifndef NUM_EXTI1_CALLBACKS
#define NUM_EXTI1_CALLBACKS 5
#endif

#ifndef NUM_EXTI2_CALLBACKS
#define NUM_EXTI2_CALLBACKS 5
#endif

#ifndef NUM_EXTI3_CALLBACKS
#define NUM_EXTI3_CALLBACKS 5
#endif

#ifndef NUM_EXTI4_CALLBACKS
#define NUM_EXTI4_CALLBACKS 5
#endif

#ifndef NUM_EXTI9_5_CALLBACKS
#define NUM_EXTI9_5_CALLBACKS 5
#endif

#ifndef NUM_EXTI15_10_CALLBACKS
#define NUM_EXTI15_10_CALLBACKS 5
#endif

#define EXTI0_IRQ 6
#define EXTI1_IRQ 7
#define EXTI2_IRQ 8
#define EXTI3_IRQ 9
#define EXTI4_IRQ 10
#define EXTI9_5_IRQ 23
#define EXTI15_10_IRQ 40

static void ( *exti0_callback[NUM_EXTI0_CALLBACKS] )(void);
static void ( *exti1_callback[NUM_EXTI1_CALLBACKS] )(void);
static void ( *exti2_callback[NUM_EXTI2_CALLBACKS] )(void);
static void ( *exti3_callback[NUM_EXTI3_CALLBACKS] )(void);
static void ( *exti4_callback[NUM_EXTI4_CALLBACKS] )(void);
static void ( *exti9_5_callback[NUM_EXTI9_5_CALLBACKS] )(void);
static void ( *exti15_10_callback[NUM_EXTI15_10_CALLBACKS] )(void);

static uint32_t num_exti0_callbacks;
static uint32_t num_exti1_callbacks;
static uint32_t num_exti2_callbacks;
static uint32_t num_exti3_callbacks;
static uint32_t num_exti4_callbacks;
static uint32_t num_exti9_5_callbacks;
static uint32_t num_exti15_10_callbacks;

static uint16_t volatile gpio_irq_events;

_Bool register_gpio_callback( void (*cb)(void), uint8_t pin ) {
    if (pin > 15) {
        return false;
    }

    switch (pin) {
        case (0):
            if (num_exti0_callbacks == NUM_EXTI0_CALLBACKS) {
                return false;
            }
            
            exti0_callback[num_exti0_callbacks++] = cb;

            break;

        case (1):
            if (num_exti1_callbacks == NUM_EXTI1_CALLBACKS) {
                return false;
            }
            
            exti1_callback[num_exti1_callbacks++] = cb;

            break;

        case (2):
            if (num_exti2_callbacks == NUM_EXTI2_CALLBACKS) {
                return false;
            }
            
            exti2_callback[num_exti2_callbacks++] = cb;

            break;

        case (3):
            if (num_exti3_callbacks == NUM_EXTI3_CALLBACKS) {
                return false;
            }
            
            exti3_callback[num_exti3_callbacks++] = cb;

            break;

        case (4):
            if (num_exti4_callbacks == NUM_EXTI4_CALLBACKS) {
                return false;
            }
            
            exti4_callback[num_exti4_callbacks++] = cb;

            break;

        case (5):
        case (6):
        case (7):
        case (8):
        case (9):
            if (num_exti9_5_callbacks == NUM_EXTI9_5_CALLBACKS) {
                return false;
            }

            exti9_5_callback[num_exti9_5_callbacks++] = cb;
            
            break;

        default:
            if (num_exti15_10_callbacks == NUM_EXTI15_10_CALLBACKS) {
                return false;
            }

            exti15_10_callback[num_exti15_10_callbacks++] = cb;

            break;
    }

    return true;
}

_Bool get_irq_status_for_pin(uint8_t pin) {
    if (pin > 15) {
        return false;
    }

    return gpio_irq_events & (1 << pin);
}

void __attribute__( (interrupt) ) EXTI0_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI0_IRQ);

    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti0_callbacks; i++) {
        exti0_callback[i]();
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF0_MASK;
}

void __attribute__( (interrupt) ) EXTI1_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI1_IRQ);
    
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti1_callbacks; i++) {
        exti1_callback[i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF1_MASK;
}

void __attribute__( (interrupt) ) EXTI2_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI2_IRQ);
    
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti2_callbacks; i++) {
        exti2_callback[i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF2_MASK;
}

void __attribute__( (interrupt) ) EXTI3_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI3_IRQ);
    
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti3_callbacks; i++) {
        exti3_callback[i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF3_MASK;
}

void __attribute__( (interrupt) ) EXTI4_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI4_IRQ);

    gpio_irq_events = EXTI->PR1 & 0xFFFF;
    
    for (uint32_t i = 0; i < num_exti4_callbacks; i++) {
        exti4_callback[i]();
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF4_MASK;
}

void __attribute__( (interrupt) ) EXTI9_5_Handler(void) {
    NVIC->ICPR0 = NVIC_ICPR_CLRPEND(1, EXTI9_5_IRQ);
    
    // Each callback must check their respective pin for pending ISR
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti9_5_callbacks; i++) {
        exti9_5_callback[i]();
    }

    // Acknowledge pending interrupts
    EXTI->PR1 = gpio_irq_events & 0x0CE0;
}

void __attribute__( (interrupt) ) EXTI15_10_Handler(void) {
    NVIC->ICPR1 = NVIC_ICPR_CLRPEND(1, EXTI15_10_IRQ - 32);
    
    // Each callback must check their respective pin for pending ISR
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti15_10_callbacks; i++) {
        exti15_10_callback[i]();
    }
    
    // Clear all processed IRQs
    EXTI->PR1 = gpio_irq_events & 0xFC00;
}

