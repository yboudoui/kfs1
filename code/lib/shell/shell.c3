module shell;

import terminal;
import readline;
import keyboard::scancode;
import vga;
import utils;
import std_io;

const uint TERMINAL_READLINE_BUFFER_SIZE = 128;

struct Shell
{
    Keyboard_handlers(<Shell>)  handler;
    Terminal                    terminal;
    uint                        scroll_index;
    uint                        current_working_buffer;
    Readline                    readline_buffer;
    // readline::Buffer* readline_buffer;
    // readline::Buffer[TERMINAL_READLINE_BUFFER_SIZE] readline_buffer;
    // readline::Buffer* readline_buffer;

}

fn void Shell.init(Shell* this, Color foreground = Color.LIGHT_GREY, Color background = Color.BLACK)
{
    this.terminal.init(foreground, background);
    this.handler = {
        .ref = this,
        .handlers = {
            [Scancode.KEY_ENTER]   = &Shell.on_return,
            [scancode::KEY_UP]     = &Shell.on_button_up,
            [scancode::KEY_DOWN]   = &Shell.on_button_down,
        }
    };
}

fn int Shell.handle_input(Shell* this, Scancode key_scancode)
{
    std_io::current_std_io(&this.terminal.stdio);

    int out;

    out = this.terminal.handle_input(key_scancode);
    if (out) return out;

    this.readline_buffer.readline();

    // Probably will be deleted
    // out = this.handler.handle_input(key_scancode);
    // if (out) return out;

    return 0;
}

fn void Shell.update(Shell* this)
{
    this.terminal.update();
}
//////


fn void Shell.scrool(Shell* this)
{
	// readline::Buffer*   tmp = null;

	// uint start = (this.scroll_index < vga::MAX_HEIGHT) ? 0 : this.scroll_index - vga::MAX_HEIGHT + 1;
	// uint end = start + vga::MAX_HEIGHT - 1;

    // this.terminal.clear();
	// for (uint i = start; i < end; i++)
	// {
	// 	tmp = &this.readline_buffer[i % TERMINAL_READLINE_BUFFER_SIZE];
	// 	terminal::write(tmp.buffer.data, tmp.buffer.size);
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
    if (!this.terminal.vga_frame.move_cursor_up()) {
        if(this.scroll_index) {
            this.scroll_index -= 1;
            this.scrool();
        }
    }
    return 0;
}

fn int Shell.on_button_down(Shell* this, Scancode key_scancode)
{
    if (!this.terminal.vga_frame.move_cursor_down()) return 0;
    if(this.scroll_index <= vga::MAX_HEIGHT) {
        this.scroll_index += 1;
        this.scrool();
    }
    return 0;
}