module terminal;

import terminal::handlers @public;

import vga;
import std_io;
import ecma48;
import utils::vector;
import utils::buffer;
import utils;
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
	this.vga_frame.main_frame_update();
}

fn int Terminal.handle_input(Terminal this, Scancode key_scancode)
{
	return ecma48::handler::dispatch(key_scancode, std_io::STD_IN);
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
	this.vga_frame.move_cursor_position_by(mouvement[0]);
	// TODO: limit to the screen -> maybe vga frame responsibility
}

fn void Terminal.on_default(Terminal* this, char c)
{
	this.vga_frame.put_entry(vga::entry(c, this.default_color));
}