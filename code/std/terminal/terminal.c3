module terminal;

import terminal::handlers @public;

import vga;
import std_io;
import ecma48;
import utils::vector;
import utils::buffer;
import keyboard::scancode;

const uint	TERMINAL_BUFFER_SIZE = 512;

struct Terminal
{
	Frame      								vga_frame;
    Entry_color								default_color;
    StdIO             						stdio;
	Buffer(<char, TERMINAL_BUFFER_SIZE>)	buffer;
    uint                					caret_position;
}

fn void Terminal.init(Terminal *this,  Color foreground = Color.LIGHT_GREY, Color background = Color.BLACK)
{
    this.default_color = Entry_color{foreground, background};

    this.vga_frame.init();
    this.vga_frame.fill(vga::entry(' ', this.default_color));
}

fn void	Terminal.update(Terminal* this)
{
	handlers::HANDLER.hooks_fd(this, std_io::STD_OUT);


	// char[std_io::STD_IO_BUFFER_SIZE]	read_buffer;
	// int read_size = std_io::read(std_io::STD_OUT, &read_buffer, std_io::STD_IO_BUFFER_SIZE);
	// for(usz i = 0; i < read_size; i++) {
	// 	this.vga_frame.put_entry(vga::entry(read_buffer[i], this.default_color));
	// 	this.vga_frame.move_cursor_position_by(+1);
	// }

	this.vga_frame.main_frame_update();
}

fn int Terminal.handle_input(Terminal this, Scancode key_scancode)
{
	return ecma48::handler::dispatch(std_io::STD_IN, key_scancode);
}

module terminal::handlers @private;

import vga;
import utils::vector;
import utils::window;
import ecma48;

import std_io;
import utils::string;

const int	TABSIZE = 4;

const Ecma48_handlers(<Terminal>) HANDLER = {
	.on_cursor_mouvement	= &Terminal.on_cursor_mouvement,
	.on_clear_screen		= &Terminal.clear,
	.default_char_handler	= &Terminal.on_default,
	.char_handlers = {
		[0x08]	= &Terminal.on_backspace,
		[0x7F]	= &Terminal.on_delete,
		[0x0A]	= &Terminal.on_enter,
	}
};

fn void Terminal.clear(Terminal *this)
{
	this.caret_position = 0;
    this.vga_frame.fill(vga::entry(' ', this.default_color));
	this.vga_frame.cursor.position = {0, 0};
}

fn void Terminal.on_backspace(Terminal* this, char c)
{
	if (this.caret_position == 0) return;

	int len = (this.buffer.data[this.caret_position - 1] == '\t') ? -TABSIZE : -1;

	this.buffer.remove(
		window::from_position(this.caret_position, 1),
		" "
	);

	this.caret_position -= 1;
	this.vga_frame.remove(len, vga::entry(' ', this.default_color));
	this.vga_frame.move_cursor_position_by(len);
}

fn void Terminal.on_delete(Terminal* this, char c)
{
	this.buffer.remove(
		window::from_position(this.caret_position, 1),
		" "
	);

	int len;
	switch (this.buffer.data[this.caret_position])
	{
	case '\t':
		len = TABSIZE;
		break;
	default:
		len = 1;
		break;
	}
	this.vga_frame.remove(len, vga::entry(' ', this.default_color));
}

fn void Terminal.on_enter(Terminal* this, char c)
{
	// t_buffer buffer = {TERMINAL_BUFFER_SIZE, this.buffer.size, this.buffer.data};
	// m_buffer_insert(char)(&buffer, this.caret_position, {'\n'});
	// this.buffer.size = buffer.size;
    this.vga_frame.next_line();
}

fn void Terminal.on_cursor_mouvement(Terminal* this, Vec2 mouvement)
{
	// if (this.caret_position == this.buffer.data.len && mouvement.x > 0) return;

    int sign = 1;
	if(mouvement.x < 0) sign = -1;
	int len = mouvement.x * sign;

    // TODO: check limit
    for (uint i = 0; i < len; i++)
    {
		int index = (sign * i);
		if (sign < 0) index -= 1;
		bool look_at = this.buffer.data[this.caret_position + index] == '\t';
		this.vga_frame.move_cursor_position_by(sign * (look_at ? TABSIZE : 1));
    }
	this.caret_position += mouvement.x;
}

fn void Terminal.on_default(Terminal* this, char c)
{
	this.buffer.insert(this.caret_position, &&(char[1]{c}));
	this.caret_position += 1;

	if (c == '\t') {
		for (uint i = 0; i < TABSIZE; i++) {
			// string::dprintf(std_io::STD_OUT, " ");
			this.vga_frame.put_entry(vga::entry(' ', this.default_color));
		}
		this.vga_frame.move_cursor_position_by(+TABSIZE);
	}
	else {
		this.vga_frame.put_entry(vga::entry(c, this.default_color));
		// string::dprintf(std_io::STD_OUT, "%c", c);
		this.vga_frame.move_cursor_position_by(+1);
	}
}