#ifndef USART_H
#define USART_H

#include <stdint.h>
#include "rcc.h"

#define IS_USART_REG(reg) ( \
	( (reg) == USART1 ) || \
	( (reg) == USART2 ) || \
	( (reg) == USART3 )	   \
)

#define IS_USART_WORD_SIZE(mask) ( \
	( (mask) == MASK_USART_CR1_WORD_LENGTH_8 ) || \
	( (mask) == MASK_USART_CR1_WORD_LENGTH_9 ) || \
	( (mask) == MASK_USART_CR1_WORD_LENGTH_7 ) 	  \
)

#define IS_USART_STOP_BIT(mask) ( \
	( (mask) == MASK_USART_CR2_STOP_BIT_1 ) || \
	( (mask) == MASK_USART_CR2_STOP_BIT_2 )    \
)

#define USART_TRANSMIT 		   0U
#define USART_RECEIVE 		   1U
#define USART_TRANSMIT_RECEIVE 2U

#define MASK_USART_CR1_UE (1 << 0)
#define MASK_USART_CR1_RE (1 << 2)
#define MASK_USART_CR1_TE (1 << 3)

#define MASK_USART_ISR_TXE  (1 << 7)
#define MASK_USART_ISR_TC   (1 << 6)
#define MASK_USART_ISR_RXNE (1 << 5)

#define MASK_USART_CR1_WORD_LENGTH_8 0x00000000
#define MASK_USART_CR1_WORD_LENGTH_9 0x00001000
#define MASK_USART_CR1_WORD_LENGTH_7 0x10001000

#define MASK_USART_CR2_STOP_BIT_1 (0 << 12)
#define MASK_USART_CR2_STOP_BIT_2 (2 << 12)

#define ADDRESS_BASE_USART1 0x40013800
#define ADDRESS_BASE_USART2 0x40004400
#define ADDRESS_BASE_USART3	0x40004800

#define USART1 ( (USART_t *) (ADDRESS_BASE_USART1) )
#define USART2 ( (USART_t *) (ADDRESS_BASE_USART2) )
#define USART3 ( (USART_t *) (ADDRESS_BASE_USART3) )

typedef struct {
	uint32_t volatile CR1;
	uint32_t volatile CR2;
	uint32_t volatile CR3;
	uint32_t volatile BRR;
	uint32_t volatile GTPR;
	uint32_t volatile RTOR;
	uint32_t volatile RQR;
	uint32_t volatile ISR;
	uint32_t volatile ICR;
	uint32_t volatile RDR;
	uint32_t volatile TDR;
} USART_t;

void USART1_clock_enable(void);
void USART2_clock_enable(void);
void USART3_clock_enable(void);

void USART_enable(USART_t * USART);
void USART_disable(USART_t * USART);

void USART_receive_enable(USART_t * USART);
void USART_transmit_enable(USART_t * USART);

void USART_set_baud_rate(USART_t * USART, uint16_t baud_rate);

uint8_t USART_receive(USART_t * USART);
void USART_transmit(USART_t * USART, uint8_t data);

void USART_config_packet(USART_t * USART, uint32_t word_size, uint32_t num_stop_bits);

void USART_enable_interrupt(USART_t * USART, uint32_t mask);
_Bool USART_read_interrupt_flag(USART_t * USART, uint32_t mask);
void USART_clear_interrupt_flag(USART_t * USART, uint32_t mask);

#endif

