/* System entry point */

ENTRY(entry_point)

/* Memory regions */

MEMORY {
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K /* SRAM1 and SRAM2 */
}

/* Memory sections */

SECTIONS {
    /* TEXT segment */

    .text : {
        . = ALIGN(4);
        KEEP( *(.vector_table*) )
        *(.init*)
        *(.text*)
        *(.text.*)
        *(.rodata*)
        . = ALIGN(4);
        __etext = .;
    } > FLASH

    /* DATA segment */

    .data : ALIGN(8) {
        __data = .;
        __data_lma = LOADADDR(.data);
        *(.data*)
        . = ALIGN(8);
        __edata = .;
    } > RAM AT > FLASH

    /* BSS segment */

    .bss : ALIGN(8) {
        __bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __ebss = .;
    } > RAM 

    . = ALIGN(8);
    __end = .;
    PROVIDE(end = .);

    /* Top of stack at end of RAM */

    __stack_top = ALIGN( ORIGIN(RAM) + LENGTH(RAM), 8 );
}

