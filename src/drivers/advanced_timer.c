#include "advanced_timer.h"

void TIM1_clock_enable(void) {
   RCC->APB2ENR |= MASK_RCC_APB2ENR_TIM1EN;
}

void TIM1_enable(void) {
    TIM1->CR1 |= MASK_TIM1_CR1_CEN;
}

void TIM1_disbale(void) {
    TIM1->CR1 &= ~MASK_TIM1_CR1_CEN;
}

void TIM1_set_count_direction(_Bool direction) {
    TIM1->CR1 = (direction) ? TIM1->CR1 | MASK_TIM1_CR1_DIR : TIM1->CR1 & ~MASK_TIM1_CR1_DIR;
}

void TIM1_set_prescaler(uint16_t prescaler) {
    TIM1->PSC = prescaler;
}

void TIM1_set_reload(uint16_t reload) {
    TIM1->ARR = reload;
}

void TIM1_update_disable(void) {
    TIM1->CR1 |= MASK_TIM1_CR1_UDIS;
}

