#include "led.h"
#include <stm32l432kc/gpio.h>
#include <stm32l432kc/rcc.h>

/* Setup LED */

void configure_led(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);
    
    // Set output
    GPIOB->MODER &= ~(GPIO_MODER_MODE3_MASK);
    GPIOB->MODER |= GPIO_MODER_MODE3(1);
    
    // Output speed
    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED3_MASK);
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3(2);
    
    // No pull-up/pull-down resistor 
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3_MASK);
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD3(0);
    
    // Output type
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT3_MASK);
    GPIOB->OTYPER |= GPIO_OTYPER_OT3(0);
}

/* Atomic write to turn on LED */

void turn_on_led(void) {
    GPIOB->BSRR = GPIO_BSRR_BS3(1);
}

/* Atomic write to turn off LED */

void turn_off_led(void) {
    GPIOB->BSRR = GPIO_BSRR_BR3(1);
}

/* Atomic write to toggle LED */

void toggle_led(void) {
    (GPIOB->ODR & GPIO_ODR_OD3_MASK) ? turn_off_led() : turn_on_led();
}

