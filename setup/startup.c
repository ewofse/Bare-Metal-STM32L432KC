#include <m4/scb.h> 

#define INITIAL_STACK_POINTER 0x2000C000

#define RESERVED ( ( void(*)(void) ) 0 )

extern void __stack_top(void);
extern void crt0(void);

void __attribute__( ( section (".init") ) ) entry_point(void) {
    crt0();
}

void DEFAULT_Handler(void) {
    // M4 system reset request
    SCB->AIRCR |= SCB_AIRCR_SYSRESETREQ(1);

    __asm__("CPSID I");
    
    // Try to sleep forever
    while (1) {
        __asm__("WFI");
    }
}

void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) NMI_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) HARDFAULT_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) MEMMANAGE_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) BUSFAULT_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) USAGEFAULT_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SVCALL_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DEBUG_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) PENDSV_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SYSTICK_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) WWDG_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) PVD_PWM_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) RTC_TAMP_STAMP_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) RTC_WKUP_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) FLASH_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) RCC_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI0_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI3_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI4_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH3_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH4_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH5_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH6_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA1_CH7_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) ADC1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) CAN1_TX_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) CAN1_RX0_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) CAN1_RX1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) CAN1_SCE_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI9_5_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM1_BRK_TIM15_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM1_UP_TIM16_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM1_TRG_COM_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM1_CC_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) I2C1_EV_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) I2C1_ER_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SPI_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) USART1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) USART2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) EXTI15_10_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) RTC_ALARM_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SPI3_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM6_DACUNDER_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TIM7_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH3_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH4_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH5_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) COMP_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) LPTIM1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) LPTIM2_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) USB_FS_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH6_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) DMA2_CH7_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) LPUART1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) QUADSPI_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) I2C3_EV_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) I2C3_ER_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SAI1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) SWPMI1_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) TSC_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) RNG_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) FPU_Handler(void);
void __attribute__( ( weak, alias("DEFAULT_Handler") ) ) CRS_Handler(void);

void ( * const __attribute__( ( section (".vector_table") ) ) vector_table[] )(void) = {
    &__stack_top,
    &entry_point,
    NMI_Handler,
    HARDFAULT_Handler,
    MEMMANAGE_Handler,
    BUSFAULT_Handler,
    USAGEFAULT_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    SVCALL_Handler,
    DEBUG_Handler,
    RESERVED,
    PENDSV_Handler,
    SYSTICK_Handler,
    WWDG_Handler,
    PVD_PWM_Handler,
    RTC_TAMP_STAMP_Handler,
    RTC_WKUP_Handler,
    FLASH_Handler,
    RCC_Handler,
    EXTI0_Handler,
    EXTI1_Handler,
    EXTI2_Handler,
    EXTI3_Handler,
    EXTI4_Handler,
    DMA1_CH1_Handler,
    DMA1_CH2_Handler,
    DMA1_CH3_Handler,
    DMA1_CH4_Handler,
    DMA1_CH5_Handler,
    DMA1_CH6_Handler,
    DMA1_CH7_Handler,
    ADC1_Handler,
    CAN1_TX_Handler,
    CAN1_RX0_Handler,
    CAN1_RX1_Handler,
    CAN1_SCE_Handler,
    EXTI9_5_Handler,
    TIM1_BRK_TIM15_Handler,
    TIM1_UP_TIM16_Handler,
    TIM1_TRG_COM_Handler,
    TIM1_CC_Handler,
    TIM2_Handler,
    RESERVED,
    RESERVED,
    I2C1_EV_Handler,
    I2C1_ER_Handler,
    RESERVED,
    RESERVED,
    SPI_Handler,
    RESERVED,
    USART1_Handler,
    USART2_Handler,
    RESERVED,
    EXTI15_10_Handler,
    RTC_ALARM_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    RESERVED,
    SPI3_Handler,
    RESERVED,
    RESERVED,
    TIM6_DACUNDER_Handler,
    TIM7_Handler,
    DMA2_CH1_Handler,
    DMA2_CH2_Handler,
    DMA2_CH3_Handler,
    DMA2_CH4_Handler,
    DMA2_CH5_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    COMP_Handler,
    LPTIM1_Handler,
    LPTIM2_Handler,
    USB_FS_Handler,
    DMA2_CH6_Handler,
    DMA2_CH7_Handler,
    LPUART1_Handler,
    QUADSPI_Handler,
    I2C3_EV_Handler,
    I2C3_ER_Handler,
    SAI1_Handler,
    RESERVED,
    SWPMI1_Handler,
    TSC_Handler,
    RESERVED,
    RESERVED,
    RNG_Handler,
    FPU_Handler,
    CRS_Handler,
    RESERVED,
    RESERVED
};

