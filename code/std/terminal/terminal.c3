module terminal;

import terminal::handlers @public;

import vga;
import std_io;
import ecma48;
import utils::vector;
import utils;
import keyboard::scancode;

const uint	TERMINAL_BUFFER_SIZE = 512;

struct Terminal
{
	Frame      	vga_frame;
    Entry_color	default_color;
    Entry_color	current_color;
    StdIO		stdio;
}

fn void Terminal.init(Terminal *this,  Color foreground = Color.LIGHT_GREY, Color background = Color.BLACK)
{
    this.default_color = Entry_color{foreground, background};
	this.current_color = this.default_color;

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

const Ecma48_handlers(<Terminal>) HANDLER = {
	.on_cursor_mouvement	= &Terminal.on_cursor_mouvement,
	.on_set_cursor_position	= &Terminal.on_set_cursor_position,
	.on_clear_screen		= &Terminal.clear,

	.on_scroll_up			= &Terminal.on_scroll_up,
	.on_scroll_down			= &Terminal.on_scroll_down,

	.on_graphic_rendition	= &Terminal.on_graphic_rendition,

	.on_next_line			= &Terminal.on_next_line,
	.default_char_handler	= &Terminal.on_default,
	.char_handlers = {
		[0x08]	= &Terminal.on_backspace,
		[0x7F]	= &Terminal.on_delete,
		[0x0A]	= &Terminal.on_enter,
	}
};

fn void Terminal.clear(Terminal *this)
{
    this.vga_frame.fill(vga::entry(' ', this.default_color));
	this.vga_frame.cursor.position = {0, 0};
}

fn void Terminal.on_backspace(Terminal* this, char c)
{
	this.vga_frame.remove(-1, vga::entry(' ', this.default_color));
	this.vga_frame.move_cursor_position_by(-1);
}

fn void Terminal.on_delete(Terminal* this, char c)
{
	this.vga_frame.remove(+1, vga::entry(' ', this.default_color));
}

fn void Terminal.on_enter(Terminal* this, char c)
{
    this.vga_frame.next_line();
}

fn void Terminal.on_next_line(Terminal* this)
{
    this.vga_frame.next_line();
}

fn void Terminal.on_cursor_mouvement(Terminal* this, Vec2 mouvement)
{
	this.vga_frame.move_cursor_position_by(mouvement[0]);
	// TODO: limit to the screen -> maybe vga frame responsibility
}

fn void Terminal.on_set_cursor_position(Terminal* this, Vec2 position)
{
	this.vga_frame.set_cursor_position(position);
	// TODO: limit to the screen -> maybe vga frame responsibility
}

fn void Terminal.on_default(Terminal* this, char c)
{
	this.vga_frame.put_entry(vga::entry(c, this.current_color));
	this.vga_frame.move_cursor_position_by(+1);
}

fn void Terminal.on_scroll_up(Terminal* this, uint n)
{
}

fn void Terminal.on_scroll_down(Terminal* this, uint n)
{
}

fn void Terminal.on_graphic_rendition(Terminal* this, uint ...args)
{
	uint n = args[0];

	if (n == 0) {
		return; // reset all
	}
	if (30 <= n && n <= 37) { // Set foreground color
		this.current_color.foreground = Color.values[n - 30];
		return;
	}
	if (40 <= n && n <= 47) { // Set background color
		this.current_color.background = Color.values[n - 40];
		return;
	}
}