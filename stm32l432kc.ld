/* Memory regions */

MEMORY {
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 48K
}

/* Memory sections */

SECTIONS {
    /* TEXT segment */

    .text : {
        *(.vector_table*)
        *(.init*)
        *(.text*)
        *(.rodata*)
        __etext = .;
    } > FLASH

    /* DATA segment */

    .data : ALIGN(4) {
        __data = .;
        *(.data)
        . = ALIGN(4);
        *(.data*)
        __edata = .;
    } > SRAM1 AT > FLASH

    __data_lma = LOADADDR(.data);

    /* BSS segment */

    .bss : ALIGN(4) {
        __bss = .;
        *(.bss*)
        . = ALIGN(4);
        __ebss = .;
    } > SRAM1 

    __end = .;

    /* Top of stack at end of RAM */

    __stack_top = ORIGIN(SRAM1) + LENGTH(SRAM1);
}

