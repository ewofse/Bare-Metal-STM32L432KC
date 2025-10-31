#ifndef INTERRUPT_H
#define INTERRUPT_H

#define enable_irq()         __asm__ volatile ("CPSIE I")
#define disable_irq()        __asm__ volatile ("CPSID I")
#define set_primask(p)       __asm__ volatile ( "MSR PRIMASK, %0" : : "r"(p) )
#define get_primask(p)       __asm__ volatile ( "MRS %0, PRIMASK" : "=r"(*p) )
#define wait_for_interrupt() __asm__ volatile ("WFI")
#define set_psp(p)           __asm__ volatile ( "MSR PSP, %0" : : "r"(p) )
#define get_psp(p)           __asm__ volatile ( "MRS %0, PSP" : "=r"(*p) )
#define set_control(p)       __asm__ volatile ( "MSR CONTROL, %0" : : "r"(p) )
#define get_control(p)       __asm__ volatile ( "MRS %0, CONTROL" : "=r"(*p) )

#endif

