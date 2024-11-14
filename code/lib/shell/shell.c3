module shell;

// import terminal;
// import readline;

// // #include "readline.h"
// // #include "terminal.h"
// // #include "codepage_437.h"


// const uint TERMINAL_READLINE_BUFFER_SIZE = 128;

// struct Shell
// {
//     terminal::Terminal  terminal;
//     readline::Buffer    readline_buffer[TERMINAL_READLINE_BUFFER_SIZE];
//     uint                scroll_index;
//     uint                current_working_buffer;
// }

// fn void Shell.init(Shell* this, vga::color::Color foreground, vga::color::Color background)
// {
//     this.terminal.init(
//         vga::color::Entry_color{
//             foreground,
//             background
//         },
//         null);
// }

// fn void Shell.scrool(Shell* this)
// {
// 	readline::Buffer*   tmp = null;

// 	uint start = (this.scroll_index < HEIGHT) ? 0 : this.scroll_index - HEIGHT + 1;
// 	uint end = start + HEIGHT - 1;

//     this.terminal.clear();
// 	for (uint i = start; i < end; i++)
// 	{
// 		tmp = &this.readline_buffer[i % TERMINAL_READLINE_BUFFER_SIZE];
// 		terminal_write(tmp->buffer.data, tmp->buffer.size);
// 	}
// }

// fn int Shell.on_return(Shell* this, t_key_scancode key_scancode)
// {
//     this.scroll_index += 1;
//     this.scrool();

//     this.current_working_buffer += 1;
//     this.current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE - 1;
//     uint working_buffer = this.current_working_buffer;
//     readline_buffer_reset(&this.readline_buffer[working_buffer]);
//     current_readline_buffer(&this.readline_buffer[working_buffer]); //?
//     return 0;
// }

// fn int Shell.input_on_button_up(Shell* this, t_key_scancode key_scancode)
// {
//     if (this.scroll_index <= 0) return 0;
//     if (!vga_frame_move_cursor_up()) {
//         if(this.scroll_index) {
//             this.scroll_index -= 1;
//             this.scrool();
//         }
//     }
//     return 0;
// }

// fn int Shell.input_on_button_down(Shell* this, t_key_scancode key_scancode)
// {
//     if (!vga_frame_move_cursor_down()) return 0;
//     if(this.scroll_index <= HEIGHT) {
//         this.scroll_index += 1;
//         this.scrool();
//     }
//     return 0;
// }



// static t_keyboard_handlers shell_scroll = {
//     .handlers = {
//         [KEY_ENTER] = shell_input_on_return,
//         [KEY_UP]    = shell_input_on_button_up,
//         [KEY_DOWN]  = shell_input_on_button_down,
//     }
// };

// Shell* current_shell(Shell* shell)
// {
// 	static Shell* current_shell = NULL;
//     size_t working_buffer;

// 	if (shell != NULL) {
// 		current_shell = shell;
//         current_terminal(&current_shell->terminal);
//         working_buffer = current_shell->current_working_buffer;
// 	    current_readline_buffer(&current_shell->readline_buffer[working_buffer]);
// 	}
// 	return current_shell;
// }







