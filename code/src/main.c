#include "kernel.h"

void main(void) 
{
	bootloader_screen();
	kernel_main();
	return ;
}