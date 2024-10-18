/* linker.ld */
ENTRY(_start)

SECTIONS
{
    . = 0x100000; /* Start the kernel at 1MB */
    .text : {
        *(.multiboot)
        *(.text)
    }
    /*
    .data : { *(.data) }
    .bss : { *(.bss) }
    */
}

