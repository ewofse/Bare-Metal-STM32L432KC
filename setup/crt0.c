#include <stm32l432kc/rcc.h>
#include <stdint.h>

extern uint8_t __etext, __sdata, __edata, __end;

void main(void);

static void configure_sysclk(void);
static void configure_clk48(void);

void crt0(void) {
    /* PLL SYSCLK and 48 MHz clock for peripherals such as USB */
    
    configure_sysclk();
    configure_clk48();

    uint8_t * from = &__etext;
    uint8_t * to = &__sdata;
    
    /* Copy DATA memory section from flash to RAM */

    while (to < &__edata) {
        *(to++) = *(from++);
    }
    
    /* Zero-initialize all data in BSS */

    while (to < &__end) {
        *(to++) = 0;
    }

    main();

    while (1); 
}

static void configure_sysclk(void) {
    RCC->CR &= ~RCC_CR_PLLON_MASK;

    while (RCC->CR & RCC_CR_PLLRDY_MASK);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC(1);
    
    // Need a combination of PLLR, PLLN, and PLLM such that...
    // SYSCLK = F_VCO * (PLLN / PLLM) / PLLR = "X" MHz
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_MASK;
    RCC->PLLCFGR |= 
          RCC_PLLCFGR_PLLR(2)
        | RCC_PLLCFGR_PLLN(32)
        | RCC_PLLCFGR_PLLM(0);

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN(1);
    RCC->CR |= RCC_CR_PLLON(1);
    
    while ( !(RCC->CR & RCC_CR_PLLRDY_MASK) );

    RCC->CFGR &= ~RCC_CFGR_SW_MASK;
    RCC->CFGR |= RCC_CFGR_SW(3);

    while ( (RCC->CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS(3) );
}

static void configure_clk48(void) {
    RCC->CRRCR |= RCC_CRRCR_HSI48ON(1);

    while ( !(RCC->CRRCR & RCC_CRRCR_HSI48RDY_MASK) );

    RCC->CCIPR &= ~RCC_CCIPR_CLK48SEL_MASK;
}

