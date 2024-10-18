
#include "utils.h"
#include "terminal.h"
#include "keyboard.h"


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
	terminal_writestring("DYAN OS!\n\n");

	unsigned char scancode;
	char buffer[64];
	buffer[0] = '\n';
	buffer[1] = ' ';
	buffer[2] = ' ';
	buffer[3] = '0';
	buffer[4] = 'x';
	
	while (1)
	{
		buffer[1] = keyboard_handler();
		if (!buffer[1]) {
			buffer[1] = ' ';
		}
		scancode = get_scancode();
		
		itoa_base(buffer + 5, scancode,  "0123456789ABCDEF");
		terminal_writestring(buffer);
	

		terminal_update_frame();
	}
	return ;
}