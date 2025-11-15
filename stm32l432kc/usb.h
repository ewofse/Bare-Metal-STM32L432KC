#ifndef STM32L432KC_USB_H
#define STM32L432KC_USB_H

#include <stdint.h>

#define ALL1 ( (uint32_t) 0xFFFFFFFF )

typedef struct {
    uint32_t EP0R;
    uint32_t EP1R;
    uint32_t EP2R;
    uint32_t EP3R;
    uint32_t EP4R;
    uint32_t EP5R;
    uint32_t EP6R;
    uint32_t EP7R;
    uint32_t RESERVED[8];
    uint32_t CNTR;
    uint32_t ISTR;
    uint32_t FNR;
    uint32_t DADDR;
    uint32_t BTABLE;
    uint32_t LPMCSR;
    uint32_t BCDR;
} USB_REG_BLOCKS;

/* USB registers as structs */

#define USB_SRAM ( (USB_REG_BLOCKS volatile *) 0x40006C00 )
#define USB_FS   ( (USB_REG_BLOCKS volatile *) 0x40006800 )

#endif

