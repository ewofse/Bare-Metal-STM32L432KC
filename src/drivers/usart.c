#include "include/drivers/usart.h"
#include "include/debug.h"

void USART1_clock_enable(void) {
	RCC->APB2ENR |= MASK_RCC_APB2ENR_USART1EN;
}

void USART2_clock_enable(void) {
	RCC->APB1ENR1 |= MASK_RCC_APB1ENR1_USART2EN;
}

void USART3_clock_enable(void) {
	RCC->APB1ENR1 |= MASK_RCC_APB1ENR1_USART3EN;
}

void USART_enable(USART_t * USART) {
	CHECK_PARAMETER( IS_USART_REG(USART) );

	USART->CR1 |= MASK_USART_CR1_UE;
}

void USART_disable(USART_t * USART) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	USART->CR1 &= ~MASK_USART_CR1_UE;
}

void USART_receive_enable(USART_t * USART) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	USART->CR1 |= MASK_USART_CR1_RE;
}

void USART_transmit_enable(USART_t * USART) {
	CHECK_PARAMETER( IS_USART_REG(USART) );		
	
	USART->CR1 |= MASK_USART_CR1_TE;
}

void USART_set_baud_rate(USART_t * USART, uint16_t baud_rate) {	
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	USART->BRR = baud_rate;
    uint32_t volatile something;
}

uint8_t USART_receive(USART_t * USART) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	while ( !(USART->ISR & MASK_USART_ISR_RXNE) );

	return USART->RDR;
}

void USART_transmit(USART_t * USART, uint8_t data) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	while ( !(USART->ISR & MASK_USART_ISR_TXE) );
	
	USART->TDR = data;
}

void USART_config_packet(USART_t * USART, uint32_t word_size, uint32_t num_stop_bits) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	CHECK_PARAMETER( IS_USART_WORD_SIZE(word_size) );
	CHECK_PARAMETER( IS_USART_STOP_BIT(num_stop_bits) );
	
	USART->CR1 |= word_size;
	USART->CR2 |= num_stop_bits;
}

_Bool USART_read_interrupt_flag(USART_t * USART, uint32_t mask) {
	CHECK_PARAMETER( IS_USART_REG(USART) );

	return (_Bool) (USART->ISR & mask);
}

void USART_clear_interrupt_flag(USART_t * USART, uint32_t mask) {
	CHECK_PARAMETER( IS_USART_REG(USART) );
	
	USART->ICR |= mask;
}

