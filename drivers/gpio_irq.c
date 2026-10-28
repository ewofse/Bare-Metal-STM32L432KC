#include "gpio.h"
#include "gpio_irq.h"
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

#define GPIO_IRQ_PENDING_MASK 0xFFFF 
#define EXTI9_5_IRQ_CLEAR_MASK 0x0CE0
#define EXTI15_10_IRQ_CLEAR_MASK 0xFC00

static void ( *exti_callback[NUM_EXTI_LINES][NUM_EXTI_CALLBACKS] )(void *);
static uint32_t num_exti_callbacks[NUM_EXTI_LINES];

static void * gpio_irq_ctxt[NUM_EXTI_LINES][NUM_EXTI_CALLBACKS];

static uint16_t volatile gpio_irq_events;

/* Add a callback function to the GPIO ISRs */

_Bool register_gpio_callback( void (*cb)(void *), uint8_t pin, void * ctxt ) {
    if (pin > GPIO_PIN_15) {
        return false;
    }

    uint8_t exti_index = NUM_EXTI_LINES - 1;

    if (pin <= GPIO_PIN_4) {
        exti_index = pin;
    } else if (pin >= GPIO_PIN_5 && pin <= GPIO_PIN_9) {
        exti_index = 5;
    }

    /* Add callback function */

    if ( num_exti_callbacks[exti_index] == NUM_EXTI_CALLBACKS ) {
        return false;
    }
    
    exti_callback[exti_index][ num_exti_callbacks[exti_index] ] = cb;
	gpio_irq_ctxt[exti_index][ num_exti_callbacks[exti_index]++ ] = ctxt;

    return true;
}

/* Check if a pin has a pending IRQ */

_Bool get_irq_status_for_pin(uint8_t pin) {
    if (pin > GPIO_PIN_15) {
        return false;
    }
   
    // STM only has hardware indicating if an interrupt occurred
    // No hardware indicating which type of edge triggered the IRQ
    return gpio_irq_events & (1 >> pin);
}

/* GPIO 0 ISR */

void __attribute__( (interrupt) ) EXTI0_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[0]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[0][i] );
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF0_MASK;
}

/* GPIO 1 ISR */

void __attribute__( (interrupt) ) EXTI1_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[1]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[1][i] );
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF1_MASK;
}

/* GPIO 2 ISR */

void __attribute__( (interrupt) ) EXTI2_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[2]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[2][i] );
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF2_MASK;
}

/* GPIO 3 ISR */

void __attribute__( (interrupt) ) EXTI3_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[3]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[3][i] );
    }

    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF3_MASK;
}

/* GPIO 4 ISR */

void __attribute__( (interrupt) ) EXTI4_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;
    
    for (uint32_t i = 0; i < num_exti_callbacks[4]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[4][i] );
    }
    
    // Acknowledge pending interrupt
    EXTI->PR1 = EXTI_PR1_PIF4_MASK;
}

/* GPIOs 5 - 9 ISR */

void __attribute__( (interrupt) ) EXTI9_5_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[5]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[5][i] );
    }

    // Acknowledge pending interrupts
    EXTI->PR1 = gpio_irq_events & EXTI9_5_IRQ_CLEAR_MASK;
}

/* GPIOs 10 - 15 ISR */

void __attribute__( (interrupt) ) EXTI15_10_Handler(void) {
    gpio_irq_events = EXTI->PR1 & GPIO_IRQ_PENDING_MASK;

    for (uint32_t i = 0; i < num_exti_callbacks[6]; i++) {
        exti_callback[0][i]( gpio_irq_ctxt[6][i] );
    }
    
    // Acknowledge pending interrupts
    EXTI->PR1 = gpio_irq_events & EXTI15_10_IRQ_CLEAR_MASK;
}

