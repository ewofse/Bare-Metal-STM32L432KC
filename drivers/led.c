#include "led.h"
#include <stm32l432kc/gpio.h>
#include <stm32l432kc/rcc.h>

void configure_led(void) {
    RCC->AHB2RSTR &= ~RCC_AHB2RSTR_GPIOBRST_MASK;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);

    GPIOB->MODER &= ~(GPIO_MODER_MODE3_MASK);
    GPIOB->MODER |= GPIO_MODER_MODE3(1);

    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED3_MASK);
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3(2);
    
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3_MASK);
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD3(0);

    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT3_MASK);
    GPIOB->OTYPER |= GPIO_OTYPER_OT3(0);
}

void turn_on_led(void) {
    GPIOB->BSRR = GPIO_BSRR_BS3(1);
}

void turn_off_led(void) {
    GPIOB->BSRR = GPIO_BSRR_BR3(1);
}

void toggle_led(void) {
    (GPIOB->ODR & GPIO_ODR_OD3_MASK) ? turn_off_led() : turn_on_led();
}

