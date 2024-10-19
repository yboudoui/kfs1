
#include "utils.h"
#include "shell.h"

void kernel_main(void) 
{
	t_shell shell = shell_init((t_vga_entry_color){
				.fg = VGA_COLOR_WHITE,
				.bg = VGA_COLOR_BLACK,
			});

	current_shell(&shell);
	terminal_update_frame();
	readline(shell_get_character);
	return ;
}