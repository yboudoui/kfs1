
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
	char buffer[64] = {0};
	
	const char* hex_base = "0123456789ABCDEF";
	const char* dec_base = "0123456789";
	const char* base = dec_base;
	size_t base_len = strlen(base);


	size_t pos = 0;
	char c = 0;

	while (1)
	{
		c = keyboard_handler();
		if (c != 0) {
			buffer[pos++] = c;
			terminal_clear();
			terminal_reset_position();
			terminal_writestring(buffer);
			c = 0;
		}
		terminal_update_frame();
	}
	return ;
}