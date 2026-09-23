#include "gpio.h"
#include "systick.h"
#include "interrupt.h"
#include <stdbool.h>

void main(void) {
    disable_irq();

    configure_systick();

    gpio_config_t led_config = {
        .pin = GPIO_PIN_3,
        .mode = GPIO_MODE_OUTPUT,
        .otype = GPIO_OTYPE_PUSHPULL,
        .ospeed = GPIO_OSPEED_HIGH,
        .pupd = GPIO_PUPD_NONE,
        .afr = GPIO_AFR_AF0
    };

    gpio_handle_t led_handler = {
        .regs = GPIOB,
        .opts = led_config
    };

    configure_gpio(&led_handler);

    enable_irq();

    uint16_t cnt = 0;

    while (true) {
        wait_for_interrupt();

        cnt = (cnt == 999) ? 0 : cnt + 1;

        if (cnt == 0) {
            toggle_gpio(&led_handler);
        }
    }
}

