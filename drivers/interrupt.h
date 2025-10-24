#ifndef INTERRUPT_H
#define INTERRUPT_H

#define enable_irq()         __asm__("CPSIE I")
#define disable_irq()        __asm__("CPSID I")
#define set_primask(p)       __asm__( "MSR PRIMASK, %0" : : "r"(p) )
#define get_primask(p)       __asm__( "MRS %0, PRIMASK" : "=r"(*p) )
#define wait_for_interrupt() __asm__("WFI")
#define set_psp(p)           __asm__( "MSR PSP, %0" : : "r"(p) )
#define get_psp(p)           __asm__( "MRS %0, PSP" : "=r"(*p) )
#define set_control(p)       __asm__( "MSR CONTROL, %0" : : "r"(p) )
#define get_control(p)       __asm__( "MRS %0, CONTROL" : "=r"(*p) )

#endif

