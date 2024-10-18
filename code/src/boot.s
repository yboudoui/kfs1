/* boot.s - Minimal Assembly to start the kernel in C */
.global _start
.section .multiboot
.align 4
.long 0x1BADB002            /* Magic number for multiboot */
.long 0x00                  /* Flags (0 for now) */
.long -(0x1BADB002 + 0x00)  /* Checksum, so the 3 fields sum to zero */

.section .text
_start:
    call kernel_main        /* Jump to the C kernel entry point */

