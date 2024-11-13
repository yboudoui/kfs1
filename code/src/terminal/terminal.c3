module terminal;

import terminal::ecma48;
import vga;
import utils::vector;
import utils::printf;
import utils::buffer;
import utils::window;
import keyboard;
import keyboard::codepage347;
import keyboard::scancode;
import std_io;

// #include "vga.h"
// #include "utils.h"
// #include "keyboard.h"
// #include "ecma48.h"
// #include "std_io.h"


const uint	TERMINAL_BUFFER_SIZE = 512;
const int	TABSIZE = 4;

struct Terminal 
{
    vga::frame::Frame          vga_frame;
    vga::color::Entry_color    default_color;
  
    keyboard::Fp_input_handler  input_handler;
    std_io::StdIO             	stdio;
    
	char[TERMINAL_BUFFER_SIZE] b;
	Buffer(<char>)   buffer;
    uint                caret_position;
}

fn void Terminal.init(Terminal *this, vga::color::Entry_color default_color, keyboard::Fp_input_handler input_handler)
{

	this.buffer.len = TERMINAL_BUFFER_SIZE;
    this.buffer.data = &this.b;


    this.default_color = default_color;
	this.input_handler = input_handler ? input_handler : &terminal_input_handler;
    this.vga_frame.init();
    this.vga_frame.fill(vga::color::entry(' ', default_color));
}

fn void Terminal.putchar_at(Terminal *this, vector::Vec2 position, char c)
{
	vga::color::Entry entry = vga::color::entry(c, this.default_color);
    this.vga_frame.put_entry_at(entry, position);
}

fn void	Terminal.put_block_at(Terminal *this, uint size, char* buffer, Vec2 position)
{
	Vec2 tmp;

	for (uint index = 0; index < size; index++)
	{
		if(buffer[index] == '\n')
		{
			tmp.x = 0;
			tmp.y += 1;
			continue;
		}
        this.putchar_at(position + tmp, buffer[index]);
		tmp.x += 1;
	}
}

fn void	Terminal.update(Terminal this)
{
    char[std_io::STD_IO_BUFFER_SIZE]	read_buffer @noinit;
    uint								read_size;
	
	read_size = std_io::read(std_io::STD_OUT, &read_buffer, std_io::STD_IO_BUFFER_SIZE);
	write(&read_buffer, read_size);
	this.vga_frame.main_frame_update();
}

// CALLBACKS
fn void Terminal.clear(Terminal *this) // KEEP IN MIND THIS WAS USED AS FUNCTION POINTER CALLBACK void  terminal_clear(void);
{
	this.caret_position = 0;
    this.vga_frame.fill(vga::color::entry(' ', this.default_color));
	this.vga_frame.cursor.position = {0, 0};
}

fn void Terminal.on_backspace(Terminal* this, char c)
{
	if (this.caret_position == 0) return;

	int len = (this.buffer.data[this.caret_position - 1] == '\t') ? -TABSIZE : -1;

	this.buffer.remove(
		window::from_position(this.caret_position, 1),
		Buffer(<char>){1, 0, " "}
	);

	this.caret_position -= 1;
	this.vga_frame.remove(len, vga::color::entry(' ', this.default_color));
	this.vga_frame.move_cursor_position_by(len);
}

fn void Terminal.on_delete(Terminal* this, char c)
{
	this.buffer.remove(window::from_position(this.caret_position, 1), Buffer(<char>){1, 0, " "});

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
	this.vga_frame.remove(len, vga::color::entry(' ', this.default_color));
}

fn void Terminal.on_enter(Terminal* this, char c)
{
	// t_buffer buffer = {TERMINAL_BUFFER_SIZE, this.buffer.size, this.buffer.data};
	// m_buffer_insert_one(char)(&buffer, this.caret_position, '\n');
	// this.buffer.size = buffer.size;
    this.vga_frame.next_line();
}

fn bool Terminal.loot_at(Terminal this, int nb, char c)
{
	return this.buffer.data[this.caret_position + nb] == c;
}

fn void Terminal.on_cursor_mouvement(Terminal* this, vector::Vec2 mouvement)
{	
	if (this.caret_position == this.buffer.size && mouvement.x > 0) return;

    int sign = 1;
	if(mouvement.x < 0) sign = -1;
	int len = mouvement.x * sign;

    // TODO: check limit
    for (uint i = 0; i < len; i++)
    {
		int index = (sign * i);
		if (sign < 0) index -= 1;
		this.vga_frame.move_cursor_position_by(sign * (this.loot_at(index, '\t') ? TABSIZE : 1));
    }
	this.caret_position += mouvement.x;
}

fn void Terminal.on_default(Terminal* this, char c)
{
	this.buffer.insert_one(this.caret_position, c);
	this.caret_position += 1;

	if (c == '\t') {
		for (uint i = 0; i < TABSIZE; i++)
			this.vga_frame.put_entry(vga::color::entry(' ', this.default_color));
		this.vga_frame.move_cursor_position_by(+TABSIZE);
	}
	else {
		this.vga_frame.put_entry(vga::color::entry(c, this.default_color));
		this.vga_frame.move_cursor_position_by(+1);
	}
}


// t_terminal* current_terminal(t_terminal* terminal)
// {
// 	static t_terminal* current_terminal = NULL;

// 	if (terminal != NULL) {
// 		current_terminal = terminal;
// 		current_this.buffer.len = TERMINAL_BUFFER_SIZE;
//         current_vga_frame(&current_this.vga_frame);
// 		current_keyboard_handler(current_this.input_handler);
// 		current_stdio(&current_this.stdio);
// 	}
// 	return current_terminal;
// }

fn int terminal_input_handler(scancode::Scancode key_scancode)
{
	static char*[] ops = {
	    [scancode::KEY_UP]    = "\033[%dA",
	    [scancode::KEY_DOWN]  = "\033[%dB",
	    [scancode::KEY_RIGHT] = "\033[%dC",
	    [scancode::KEY_LEFT]  = "\033[%dD",
	    // NULL,
	};

    if(ops[key_scancode] != null) {
        printf::dprintf(std_io::STD_IN, ops[key_scancode], 1);
	} else {
        printf::dprintf(std_io::STD_IN, "%c", keyboard::codepage347::table[key_scancode]);
	}
	return 0;
}

fn int write(char* buffer, uint size)
{
	// static ecma48::Ecma48_handlers handlers = {
	// 	.on_cursor_mouvement	= on_cursor_mouvement,
	// 	.on_clear_screen		= terminal_clear,
	// 	.default_char_handler	= on_default,
	// 	.char_handlers = {
	// 		[0x08]      		= on_backspace,
	// 		[0x7F]    			= on_delete,
	// 		[0x0A]				= on_enter,
	// 	}
	// };
	// ecma48_hooks(buffer, size, &handlers);
	// return size;
	return 0;
}

