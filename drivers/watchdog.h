#ifndef WATCHDOG_H
#define WATCHDOG_h

#include <stdbool.h>

void configure_independent_watchdog(void);
void feed_the_independent_watchdog(void);
void configure_window_watchdog(void);
void feed_the_window_watchdog(void);
_Bool register_window_watchdog_callback( void (*cb)(void) );

#endif

