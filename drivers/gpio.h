#ifndef GPIO_H
#define GPIO_H

#include <stm32l432kc/gpio.h>
#include <stdbool.h>

typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15
} gpio_pin;

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG
} gpio_mode;

typedef enum {
    GPIO_OTYPE_PUSHPULL,
    GPIO_OTYPE_OPENDRAIN
} gpio_otype;

typedef enum {
    GPIO_OSPEED_LOW,
    GPIO_OSPEED_MEDIUM,
    GPIO_OSPEED_HIGH,
    GPIO_OSPEED_VERYHIGH
} gpio_ospeed;

typedef enum {
    GPIO_PUPD_NONE,
    GPIO_PUPD_PULLUP,
    GPIO_PUPD_PULLDOWN
} gpio_pupd;

typedef enum {
    GPIO_AFR_AF0,
    GPIO_AFR_AF1,
    GPIO_AFR_AF2,
    GPIO_AFR_AF3,
    GPIO_AFR_AF4,
    GPIO_AFR_AF5,
    GPIO_AFR_AF6,
    GPIO_AFR_AF7,
    GPIO_AFR_AF8,
    GPIO_AFR_AF9,
    GPIO_AFR_AF10,
    GPIO_AFR_AF11,
    GPIO_AFR_AF12,
    GPIO_AFR_AF13,
    GPIO_AFR_AF14,
    GPIO_AFR_AF15
} gpio_afr;

typedef GPIO_REG_BLOCKS volatile gpio_t;

typedef struct {
    gpio_pin pin;
    gpio_mode mode;
    gpio_otype otype;
    gpio_ospeed ospeed;
    gpio_pupd pupd;
    gpio_afr afr;
} gpio_config_t;

typedef struct {
    gpio_t * regs;
    gpio_config_t opts;
} gpio_handle_t;

void configure_gpio(gpio_handle_t * handler);
_Bool read_gpio(gpio_handle_t * handler);
void set_gpio(gpio_handle_t * handler);
void reset_gpio(gpio_handle_t * handler);
void toggle_gpio(gpio_handle_t * handler);

#endif

