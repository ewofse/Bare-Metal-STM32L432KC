#include "include/drivers/gpio.h"
#include "include/debug.h"

void GPIOA_clock_enable(void) {
	RCC->AHB2ENR |= MASK_RCC_AHB2ENR_GPIOAEN;
}

void GPIOB_clock_enable(void) {
	RCC->AHB2ENR |= MASK_RCC_AHB2ENR_GPIOBEN;
}

void GPIOC_clock_enable(void) {
	RCC->AHB2ENR |= MASK_RCC_AHB2ENR_GPIOCEN;
}

void GPIOH_clock_enable(void) {
	RCC->AHB2ENR |= MASK_RCC_AHB2ENR_GPIOHEN;
}

uint8_t GPIO_get_position(uint16_t pin) {
	uint8_t position = 0U;

	while (pin >> position != 1U) {
		++position;
	}

	return position;
}

static void GPIO_set_mode(GPIO_t * port, uint16_t pin, uint8_t mode) {
	CHECK_PARAMETER( IS_GPIO_MODE(mode) );	
	
	uint8_t position = GPIO_get_position(pin);

	port->MODER &= ~( 3U << (position * 2U) );
	port->MODER |= ( mode << (position * 2U) );
}

static void GPIO_set_output_type(GPIO_t * port, uint16_t pin, uint8_t output_type) {
	CHECK_PARAMETER( IS_GPIO_OUTPUT(output_type) );
	
	uint8_t position = GPIO_get_position(pin);

	port->OTYPER &= ~(1U << position);
	port->OTYPER |= (output_type << position);
}

static void GPIO_set_output_speed(GPIO_t * port, uint16_t pin, uint8_t output_speed) {
	CHECK_PARAMETER( IS_GPIO_SPEED(output_speed) );

	uint8_t position = GPIO_get_position(pin);

	port->OSPEEDR &= ~( 3U << (position * 2U) );
	port->OSPEEDR |= ( output_speed << (position * 2U) );
}

static void GPIO_set_resistor(GPIO_t * port, uint16_t pin, uint8_t resistor) {
	CHECK_PARAMETER( IS_GPIO_PUPD(resistor) );	
	
	uint8_t position = GPIO_get_position(pin);

	port->PUPDR &= ~( 3U << (position * 2U) );
	port->PUPDR |= ( resistor << (position * 2U) );
}

static void GPIO_set_alternate(GPIO_t * port, uint16_t pin, uint8_t alternate) {
	CHECK_PARAMETER( IS_GPIO_AF(alternate) );	

	uint8_t position = GPIO_get_position(pin);

	if ( position < (GPIO_NUMBER / 2) ) {
		port->AFR[0] &= ~( 15U << (position * 4U) );
		port->AFR[0] |= alternate << (position * 4U);
	} else {
		port->AFR[1] &= ~( 15U << (position * 4U) );
		port->AFR[1] |= alternate << (position * 4U);
	}
}

void GPIO_config(GPIO_t * port, GPIO_config_t config) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(config.pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, config.pin) );

	GPIO_set_mode(port, config.pin, config.mode);
	GPIO_set_resistor(port, config.pin, config.resistor);
	
	if (config.mode == GPIO_MODE_OUTPUT || config.mode == GPIO_MODE_ALTERNATE) {
		GPIO_set_output_type(port, config.pin, config.output_type);
		GPIO_set_output_speed(port, config.pin, config.output_speed);
	}

	if (config.mode == GPIO_MODE_ALTERNATE) {
		GPIO_set_alternate(port, config.pin, config.alternate);
	}
}

void GPIO_reset(GPIO_t * port, uint16_t pin) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );

	uint16_t position = GPIO_get_position(pin);

	port->MODER &= ~( 3U << (position * 2U) );
	port->OTYPER &= ~(1U << position);
	port->OSPEEDR &= ~( 3U << (position * 2U) );
	port->PUPDR &= ~( 3U << (position * 2U) );

	if ( position < (GPIO_NUMBER / 2) ) {
		port->AFR[0] &= ~( 15U << (position * 4U) );
	} else {
		port->AFR[1] &= ~( 15U << (position * 4U) );
	}
}

void GPIO_lock(GPIO_t * port, uint16_t pins) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_MASK(pins) );	
	
	port->LCKR = (1 << 16) | pins;
	port->LCKR = pins;	
	port->LCKR = (1 << 16) | pins;
	port->LCKR;
	while ( ( port->LCKR & (1 << 16) ) == 0 );
}

void GPIO_write(GPIO_t * port, uint16_t pin, _Bool value) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, pin) );
	CHECK_PARAMETER( IS_GPIO_VALUE(value) );

	if (value) {
		port->BSRR = (uint32_t) pin;
	} else {
		port->BRR = (uint32_t) pin;
	}
}

void GPIO_set(GPIO_t * port, uint16_t pin) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, pin) );

	port->BSRR = (uint32_t) pin;
}

void GPIO_clear(GPIO_t * port, uint16_t pin) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, pin) );

	port->BRR = (uint32_t) pin;
}

void GPIO_toggle(GPIO_t * port, uint16_t pin) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, pin) );

	port->BSRR = ( (port->ODR & pin) << GPIO_NUMBER ) | (~port->ODR & pin);
}

_Bool GPIO_read(GPIO_t * port, uint16_t pin) {
	CHECK_PARAMETER( IS_GPIO_PORT(port) );
	CHECK_PARAMETER( IS_GPIO_PIN(pin) );
	CHECK_PARAMETER( IS_GPIO_VALID(port, pin) );

	return (port->IDR & pin) ? (_Bool) GPIO_SET : (_Bool) GPIO_RESET;
}

