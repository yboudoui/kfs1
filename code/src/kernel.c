#include "kernel.h"

void kernel_main(void) 
{
	t_terminal_frame frame = {
		.default_color = {
			.fg = VGA_COLOR_RED,
			.bg = VGA_COLOR_GREEN,
		}
	};
	current_terminal_frame(&frame);
  	terminal_clear();

	terminal_writestring("Hello, kernel World!\n");

	  // Halt the CPU (loop indefinitely)
	while (1);
	return ;
}