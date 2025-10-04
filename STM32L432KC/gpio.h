#ifndef STM32L432KC_GPIO_H
#define STM32L432KC_GPIO_H

#include <stdint.h>

typedef struct {
    uint32_t volatile MODER;
    uint32_t volatile OTYPER;
    uint32_t volatile OSPEEDR;
    uint32_t volatile PUPDR;
    uint32_t volatile IDR;
    uint32_t volatile ODR;
    uint32_t volatile BSRR;
    uint32_t volatile LCKR;
    uint32_t volatile AFR[2];
    uint32_t volatile BRR;
} GPIO_REG_BLOCKS;

/* GPIO registers as structs */

#define GPIOA ( (GPIO_REG_BLOCKS volatile *) 0x48000000 )
#define GPIOB ( (GPIO_REG_BLOCKS volatile *) 0x48000400 )
#define GPIOC ( (GPIO_REG_BLOCKS volatile *) 0x48000800 )
#define GPIOH ( (GPIO_REG_BLOCKS volatile *) 0x48001C00 )

/* Pin macros */

#define PA0_LOC  (1 << 0)
#define PA1_LOC  (1 << 1)
#define PA2_LOC  (1 << 2)
#define PA3_LOC  (1 << 3)
#define PA4_LOC  (1 << 4)
#define PA5_LOC  (1 << 5)
#define PA6_LOC  (1 << 6)
#define PA7_LOC  (1 << 7)
#define PA8_LOC  (1 << 8)
#define PA9_LOC  (1 << 9)
#define PA10_LOC (1 << 10)
#define PA11_LOC (1 << 11)
#define PA12_LOC (1 << 12)
#define PA13_LOC (1 << 13)
#define PA14_LOC (1 << 14)
#define PA15_LOC (1 << 15)

#define PB0_LOC  (1 << 0)
#define PB1_LOC  (1 << 1)
#define PB2_LOC  (1 << 2)
#define PB3_LOC  (1 << 3)
#define PB4_LOC  (1 << 4)
#define PB5_LOC  (1 << 5)
#define PB6_LOC  (1 << 6)
#define PB7_LOC  (1 << 7)

#define PC14_LOC (1 << 14)
#define PC15_LOC (1 << 15)

#define PH3_LOC  (1 << 3)

#define PA0_VALUE  0
#define PA1_VALUE  1
#define PA2_VALUE  2
#define PA3_VALUE  3
#define PA4_VALUE  4
#define PA5_VALUE  5
#define PA6_VALUE  6
#define PA7_VALUE  7
#define PA8_VALUE  8
#define PA9_VALUE  9
#define PA10_VALUE 10
#define PA11_VALUE 11
#define PA12_VALUE 12
#define PA13_VALUE 13
#define PA14_VALUE 14
#define PA15_VALUE 15

#define PB0_VALUE  0
#define PB1_VALUE  1
#define PB2_VALUE  2
#define PB3_VALUE  3
#define PB4_VALUE  4
#define PB5_VALUE  5
#define PB6_VALUE  6
#define PB7_VALUE  7

#define PC14_VALUE 14
#define PC15_VALUE 15

#define PH3_VALUE  3

#define GPIO_CONFIG_LOC(pin_value) ( (pin_value) * 2 )
#define GPIO_CONFIG_RESET_MASK(pin_value) ( ~( 3 << GPIO_CONFIG_LOC(pin_value) ) )

/* GPIO configuration macros */

#define INPUT_MODE                      0
#define GENERAL_PURPOSE_OUTPUT_MODE     1
#define ALTERANTE_FUNCTION_MODE         2
#define ANALOG_MODE                     3

#define OUTPUT_PUSH_PULL                0
#define OUTPUT_OPEN_DRAIN               1

#define LOW_SPEED                       0
#define MEDIUM_SPEED                    1
#define HIGH_SPEED                      2
#define VERY_HIGH_SPEED                 3

#define NO_PULL                         0
#define PULL_UP                         1
#define PULL_DOWN                       2

#endif

