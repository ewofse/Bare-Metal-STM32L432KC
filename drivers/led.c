#include "led.h"
#include "gpio.h"
#include "rcc.h"

void configure_led(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_MASK;

    GPIOB->MODER &= GPIO_CONFIG_RESET_MASK(PB3_VALUE);
    GPIOB->MODER |= GENERAL_PURPOSE_OUTPUT_MODE << GPIO_CONFIG_LOC(PB3_VALUE); 

    GPIOB->OSPEEDR &= GPIO_CONFIG_RESET_MASK(PB3_VALUE);
    GPIOB->OSPEEDR |= HIGH_SPEED << GPIO_CONFIG_LOC(PB3_VALUE);
    
    GPIOB->PUPDR &= GPIO_CONFIG_RESET_MASK(PB3_VALUE); 
    GPIOB->PUPDR |= NO_PULL << GPIO_CONFIG_LOC(PB3_VALUE);

    GPIOB->OTYPER &= ~(OUTPUT_PUSH_PULL << PB3_VALUE);
}

void turn_on_led(void) {
    GPIOB->BSRR = PB3_LOC;
}

void turn_off_led(void) {
    GPIOB->BSRR = PB3_LOC << 16;
}

void toggle_led(void) {
    GPIOB->BSRR = (GPIOB->ODR & PB3_LOC) ? PB3_LOC << 16 : PB3_LOC;
}

