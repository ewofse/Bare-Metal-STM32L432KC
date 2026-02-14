#include "gpio.h"
#include <m4/nvic.h>
#include <stm32l432kc/exti.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef NUM_EXTI_CALLBACKS
#define NUM_EXTI_CALLBACKS 5
#endif

#define NUM_EXTI_LINES 7

#define EXTI0_IRQ 6
#define EXTI1_IRQ 7
#define EXTI2_IRQ 8
#define EXTI3_IRQ 9
#define EXTI4_IRQ 10
#define EXTI9_5_IRQ 23
#define EXTI15_10_IRQ 40

static void ( *exti_callback[NUM_EXTI_LINES][NUM_EXTI_CALLBACKS] )(void);
static uint32_t num_exti_callbacks[NUM_EXTI_LINES];

static uint16_t volatile gpio_irq_events;

/* Add a callback function to the GPIO ISRs */

_Bool register_gpio_callback( void (*cb)(void), uint8_t pin ) {
    if (pin > 15) {
        return false;
    }

    uint8_t exti_index = NUM_EXTI_LINES - 1;

    if (pin <= 4) {
        exti_index = pin;
    } else if (pin >= 5 && pin <= 9) {
        exti_index = 5;
    }

    /* Add callback function */

    if ( num_exti_callbacks[exti_index] == NUM_EXTI_CALLBACKS ) {
        return false;
    }
    
    exti_callback[exti_index][ num_exti_callbacks[exti_index]++ ] = cb;

    return true;
}

/* Check if a pin has a pending IRQ */

_Bool get_irq_status_for_pin(uint8_t pin) {
    if (pin > 15) {
        return false;
    }
   
    // STM only has hardware indicating if an interrupt occurred
    // No hardware indicating which type of edge triggered the IRQ
    return gpio_irq_events & (1 >> pin);
}

/* GPIO 0 ISR */

void __attribute__( (interrupt) ) EXTI0_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI0_IRQ);

    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[0]; i++) {
        exti_callback[0][i]();
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF0_MASK;
}

/* GPIO 1 ISR */

void __attribute__( (interrupt) ) EXTI1_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI1_IRQ);
    
    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[1]; i++) {
        exti_callback[1][i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF1_MASK;
}

/* GPIO 2 ISR */

void __attribute__( (interrupt) ) EXTI2_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI2_IRQ);
    
    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[2]; i++) {
        exti_callback[2][i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF2_MASK;
}

/* GPIO 3 ISR */

void __attribute__( (interrupt) ) EXTI3_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI3_IRQ);
    
    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[3]; i++) {
        exti_callback[3][i]();
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF3_MASK;
}

/* GPIO 4 ISR */

void __attribute__( (interrupt) ) EXTI4_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI4_IRQ);

    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;
    
    for (uint32_t i = 0; i < num_exti_callbacks[4]; i++) {
        exti_callback[4][i]();
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF4_MASK;
}

/* GPIOs 5 - 9 ISR */

void __attribute__( (interrupt) ) EXTI9_5_Handler(void) {
    // Clearn pending IRQ
    NVIC->ICPR[0] = NVIC_ICPR_CLRPEND(1, EXTI9_5_IRQ);
    
    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[5]; i++) {
        exti_callback[5][i]();
    }

    // Acknowledge pending interrupts
    EXTI->PR1 = gpio_irq_events & 0x0CE0;
}

/* GPIOs 10 - 15 ISR */

void __attribute__( (interrupt) ) EXTI15_10_Handler(void) {
    // Clear pending IRQ
    NVIC->ICPR[1] = NVIC_ICPR_CLRPEND(1, EXTI15_10_IRQ - 32);
    
    // Each callback must check their respective pin for pending IRQ
    gpio_irq_events = EXTI->PR1 & 0xFFFF;

    for (uint32_t i = 0; i < num_exti_callbacks[6]; i++) {
        exti_callback[6][i]();
    }
    
    // Clear all processed IRQs
    EXTI->PR1 = gpio_irq_events & 0xFC00;
}

