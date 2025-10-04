#define INITIAL_STACK_POINTER 0x2000C000

extern void crt0(void);

void __attribute__( ( section (".init") ) ) entry_point(void) {
    crt0();
}

void * const __attribute__( ( section (".vector_table") ) ) vector_table[] = {
    (void *) INITIAL_STACK_POINTER,	
    &entry_point
};

