module tty;

import tty::handlers @public;

import vga;
import std_io;
import ecma48;

struct Tty
{
	Frame      	vga_frame;
    Entry_color	default_color;
    Entry_color	current_color;
}

fn void Tty.init(Tty *this)
{
    this.default_color = Entry_color{Color.LIGHT_GREY, Color.BLACK};
	this.current_color = this.default_color;

    this.vga_frame.init();
    this.vga_frame.fill(vga::entry(' ', this.default_color));
}

fn void	Tty.update(Tty* this)
{
	handlers::HANDLER.hooks_fd(this, std_io::STD_OUT);
	this.vga_frame.main_frame_update();
}

fn int Tty.handle_input(Tty this)
{
	return ecma48::handler::dispatch_on_key_pressed(std_io::STD_IN);
}

module tty::handlers @private;

import vga;
import utils::vector; // should be removed
import utils::window; // should be removed
import ecma48;

const Ecma48_handlers(<Tty>) HANDLER = {
	.on_cursor_mouvement	= &Tty.on_cursor_mouvement,
	.on_set_cursor_position	= &Tty.on_set_cursor_position,
	.on_clear_screen		= &Tty.clear,

	.on_scroll_up			= &Tty.on_scroll_up,
	.on_scroll_down			= &Tty.on_scroll_down,

	.on_graphic_rendition	= &Tty.on_graphic_rendition,

	.on_next_line			= &Tty.on_next_line,
	.default_char_handler	= &Tty.on_default,
	.char_handlers = {
		[0x08]	= &Tty.on_backspace,
		[0x7F]	= &Tty.on_delete,
		[0x0A]	= &Tty.on_enter,
	}
};

fn void Tty.clear(Tty *this)
{
    this.vga_frame.fill(vga::entry(' ', this.default_color));
	this.vga_frame.cursor.position = {0, 0};
}

fn void Tty.on_backspace(Tty* this, char c)
{
	this.vga_frame.remove(-1, vga::entry(' ', this.default_color));
	this.vga_frame.move_cursor_position_by(-1);
}

fn void Tty.on_delete(Tty* this, char c)
{
	this.vga_frame.remove(+1, vga::entry(' ', this.default_color));
}

fn void Tty.on_enter(Tty* this, char c)
{
    this.vga_frame.next_line();
}

fn void Tty.on_next_line(Tty* this)
{
    this.vga_frame.next_line();
}

fn void Tty.on_cursor_mouvement(Tty* this, Vec2 mouvement)
{
	this.vga_frame.move_cursor_position_by(mouvement[0]);
	// TODO: limit to the screen -> maybe vga frame responsibility
}

fn void Tty.on_set_cursor_position(Tty* this, Vec2 position)
{
	this.vga_frame.set_cursor_position(position);
	// TODO: limit to the screen -> maybe vga frame responsibility
}

fn void Tty.on_default(Tty* this, char c)
{
	this.vga_frame.put_entry(vga::entry(c, this.current_color));
	this.vga_frame.move_cursor_position_by(+1);
}

fn void Tty.on_scroll_up(Tty* this, uint n)
{
}

fn void Tty.on_scroll_down(Tty* this, uint n)
{
}

fn void Tty.on_graphic_rendition(Tty* this, uint ...args)
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