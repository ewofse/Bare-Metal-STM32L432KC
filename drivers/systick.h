#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdbool.h>
#include <stdint.h>

void configure_systick(void);
_Bool systick_has_fired(void);
_Bool register_systick_callback( void (*cb)(void) );
uint64_t get_system_time(void);

#endif

