import kernel;

struct Multiboot_header @align(4) 
{
    int magic;
    int flags;
    int checksum;
}

const int MAGIC		= 0x1BADB002;
const int ALIGN		= (1 << 0);
const int MEMINFO	= (1 << 1);
const int FLAGS		= ALIGN | MEMINFO;
const int CHECKSUM	= -(MAGIC + FLAGS);

Multiboot_header multiboot_header @section(".multiboot")  @nostrip = {
    .magic		= MAGIC,
    .flags		= ALIGN | MEMINFO,
    .checksum	= CHECKSUM
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