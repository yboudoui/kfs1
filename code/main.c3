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

const uint STACK_SIZE = 16 * 1024;
char[STACK_SIZE] stack @section(".bss")  @nostrip @align(16);  // 16 KiB


fn void _start()  @section(".text") @nostrip @noreturn @export("_start")
{
	char *stack_top = &stack[STACK_SIZE - 1];
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
	kernel::main.new_process(&kernel::bootloader);
	kernel::main.run_process();

	kernel::main.new_process(&kernel::entry);
	kernel::main.run_process();
}

