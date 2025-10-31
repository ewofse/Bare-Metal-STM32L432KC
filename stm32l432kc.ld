/* Memory regions */

MEMORY {
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 48K
}

/* Memory sections */

SECTIONS {
    .text : {
        *(.vector_table*)
        *(.text*)
        *(.init*)
        *(.rodata*)
        __etext = .;
    } > FLASH

    .data : {
        __sdata = .;
        *(.data*)
        __edata = .;
    } > SRAM1 AT > FLASH

    .bss : {
        *(.bss*)
        __end = .;
    } > SRAM1 
}

