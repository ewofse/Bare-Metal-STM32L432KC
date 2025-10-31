#ifndef PA0_H
#define PA0_H

#include <stdboo.h>
#include <stdint.h>

/* Example driver for GPIO
    
   void configure_pa0(void);
    - enable the clock for the GPIOx peripheral (RCC)
    - configure the pin's mode, speed, pupdr, etc.
    - enable the pin for external IRQs (EXTI_IMR)
    - Set the EXTI multiplexer to be controlled by the pin (SYSCFG_EXTICRx)
    - register the callback(s) to appropraite ISR vector
    - set the interrupt priority (NVIC_ISPRx)

    static void callback(void);
    - do something ahh

*/

#endif

