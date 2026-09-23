#include "gpio.h"
#include <stm32l432kc/gpio.h>
#include <stm32l432kc/rcc.h>
#include <stdbool.h>

void configure_gpio(gpio_handle_t * handler) {
    gpio_t * gpio = handler->regs;
    gpio_config_t opts = handler->opts;

    /* Clock enable */

    if (gpio == GPIOA) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN(1);
    } else if (gpio == GPIOB) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN(1);
    } else if (gpio == GPIOC) {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN(1);
    } else {
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOHEN(1);
    }

    /* GPIO options */

    gpio->MODER &= ~GPIO_MODER_MODE_MASK(opts.pin);
    gpio->MODER |= GPIO_MODER_MODE(opts.mode, opts.pin);

    gpio->OTYPER &= ~GPIO_OTYPER_OT_MASK(opts.pin);
    gpio->OTYPER |= GPIO_OTYPER_OT(opts.otype, opts.pin);

    gpio->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED_MASK(opts.pin);
    gpio->OSPEEDR |= GPIO_OSPEEDR_OSPEED(opts.ospeed, opts.pin);

    gpio->PUPDR &= ~GPIO_PUPDR_PUPD_MASK(opts.pin);
    gpio->PUPDR |= GPIO_PUPDR_PUPD(opts.pupd, opts.pin);

    _Bool index = opts.pin >= GPIO_PIN_8;

    gpio->AFR[index] &= ~GPIO_AFR_AF(opts.afr, opts.pin);
    gpio->AFR[index] |= GPIO_AFR_AF_MASK(opts.pin);
}

/* Read incomming value on pin */

_Bool read_gpio(gpio_handle_t * handler) {
    gpio_t * gpio = handler->regs;
    gpio_config_t opts = handler->opts;

    return gpio->IDR & GPIO_IDR_ID_MASK(opts.pin);
}

/* Atomic write to set pin high */

void set_gpio(gpio_handle_t * handler) {
    gpio_t * gpio = handler->regs;
    gpio_config_t opts = handler->opts;

    gpio->BSRR = GPIO_BSRR_BS(1, opts.pin);
}

/* Atomic write to set pin low */

void reset_gpio(gpio_handle_t * handler) {
    gpio_t * gpio = handler->regs;
    gpio_config_t opts = handler->opts;

    gpio->BSRR = GPIO_BSRR_BR(1, opts.pin);
}

/* Atomic write to toggle pin */

void toggle_gpio(gpio_handle_t * handler) {
    gpio_t * gpio = handler->regs;
    gpio_config_t opts = handler->opts;

    ( gpio->ODR & GPIO_ODR_OD_MASK(opts.pin) ) ? \
        reset_gpio(handler) : set_gpio(handler);
}

