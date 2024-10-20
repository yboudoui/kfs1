#include "utils.h"
#include "shell.h"

void kernel_main(void) 
{
	VGA_ENABLE_CURSOR

	t_shell shell;
	
	shell = shell_init((t_vga_entry_color){
		.fg = VGA_COLOR_WHITE,
		.bg = VGA_COLOR_BLACK,
	});

	current_shell(&shell);
	terminal_clear(&shell.terminal);
	

	vga_main_frame_update(shell.terminal.vga_frame);
	

	while (keyboard_handler(shell_get_character) == 0);
}