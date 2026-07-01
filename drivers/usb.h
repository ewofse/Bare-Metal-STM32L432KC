#ifndef UBS_H
#define USB_H

#include <stdbool.h>

void configure_usb(void);
int usb_getchar(char * c);
int usb_putchar(char c);
_Bool usb_is_enumerated(void);

#endif

