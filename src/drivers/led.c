#include "include/drivers/led.h"

void LED_config(void) {
	GPIO_config_t config = {
		.pin = PB3,
		.mode = GPIO_MODE_OUTPUT,
		.output_type = GPIO_OTYPE_PUSHPULL,
		.output_speed = GPIO_OSPEED_HIGH,
		.resistor = GPIO_PUPD_NONE,
		.alternate = AF0
	};

	GPIO_config(GPIOB, config);
}

void LED_set(void) {
	GPIOB->BSRR = PB3;
}

void LED_clear(void) {
	GPIOB->BRR = PB3;
}

void LED_toggle(void) {
	GPIOB->BSRR = ( (GPIOB->ODR & PB3) << GPIO_NUMBER ) | (~GPIOB->ODR & PB3);
}

