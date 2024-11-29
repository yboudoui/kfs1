module shell;

import tty;
import readline;
import keyboard::scancode;
import vga;

// Keyboard_handlers(<Shell>)  handler = {
//     .handlers = {
//         [Scancode.KEY_ENTER]    = &Shell.on_return,
//         [Scancode.KEY_UP]       = &Shell.on_button_up,
//         [Scancode.KEY_DOWN]     = &Shell.on_button_down,
//     }
// };
// handler.ref = this

struct Shell
{
    Tty         tty;
    uint        scroll_index;
    Readline    readline_buffer;
}

fn int Shell.handle_input(Shell* this)
{
    // kernel::main.set_current_process_id(&this.tty);

    int out = this.tty.handle_input();
    if (out) return out;

    this.readline_buffer.readline();
    return 0;
}

//////


fn void Shell.scrool(Shell* this)
{
	// readline::Buffer*   tmp = null;

	// uint start = (this.scroll_index < vga::MAX_HEIGHT) ? 0 : this.scroll_index - vga::MAX_HEIGHT + 1;
	// uint end = start + vga::MAX_HEIGHT - 1;

    // this.tty.clear();
	// for (uint i = start; i < end; i++)
	// {
	// 	tmp = &this.readline_buffer[i % TERMINAL_READLINE_BUFFER_SIZE];
	// 	tty::write(tmp.buffer.data, tmp.buffer.size);
	// }
}

fn int Shell.on_return(Shell* this, Scancode key_scancode)
{
    // this.scroll_index += 1;
    // this.scrool();

    // this.current_working_buffer += 1;
    // this.current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE - 1;
    // uint working_buffer = this.current_working_buffer;
    // this.readline_buffer[working_buffer].reset();
    // // current_readline_buffer(&this.readline_buffer[working_buffer]); //?
    return 0;
}

fn int Shell.on_button_up(Shell* this, Scancode key_scancode)
{
    if (this.scroll_index = 0) return 0;
    if (!this.tty.vga_frame.move_cursor_up()) {
        if(this.scroll_index) {
            this.scroll_index -= 1;
            this.scrool();
        }
    }
    return 0;
}

fn int Shell.on_button_down(Shell* this, Scancode key_scancode)
{
    if (!this.tty.vga_frame.move_cursor_down()) return 0;
    if(this.scroll_index <= vga::MAX_HEIGHT) {
        this.scroll_index += 1;
        this.scrool();
    }
    return 0;
}