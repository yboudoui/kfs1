import kernel;

struct Multiboot_header @align(4) 
{
    int magic;
    int flags;
    int checksum;
}

Multiboot_header multiboot_header @section(".multiboot")  @nostrip = {
    .magic = 0x1BADB002,            // MAGIC
    .flags = (1 << 0) | (1 << 1),   // FLAGS (ALIGN | MEMINFO)
    .checksum = -(0x1BADB002 + ((1 << 0) | (1 << 1))) // CHECKSUM
}; 

char[16384] stack @section(".bss")  @nostrip @align(16);  // 16 KiB


fn void _start()  @section(".text") @nostrip @noreturn @export("_start")
{
	char *stack_top = &stack[16383];
	asm
	{
		movl stack_top, $esp;
	}

	main();

    asm("cli");
	while (1) {
		asm("hlt");
	}
}

fn void main()
{
	kernel::bootloader();
	kernel::entry();
}