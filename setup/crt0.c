#include <stdint.h>

extern uint8_t __etext, __sdata, __edata, __end;

void main(void);

void crt0(void) {
    uint8_t * from, * to;

    from = &__etext;
    to = &__sdata;
    
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

