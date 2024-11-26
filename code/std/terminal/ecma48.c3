module ecma48(<Type>);

import std_io;
import utils::string;
import utils::vector;

const char ESCAPE_SEQUENCE              = '\e';
const char CONTROL_SEQUENCE_INTRODUCER  = 0x5B;

def Fp_ecma48_char_handler      = fn void (Type*, char);
def Fp_ecma48_empty_handler     = fn void (Type*);
def Fp_ecma48_cursor_handler    = fn void (Type*, Vec2);
def Fp_ecma48_scroll_handler    = fn void (Type*, uint);
def Fp_ecma48_handler    = fn void (Type*, uint...);

struct Ecma48_handlers
{
    Fp_ecma48_cursor_handler    on_cursor_mouvement;
    Fp_ecma48_cursor_handler    on_set_cursor_position;

    Fp_ecma48_scroll_handler    on_scroll_up;
    Fp_ecma48_scroll_handler    on_scroll_down;

    Fp_ecma48_handler           on_graphic_rendition;

    Fp_ecma48_empty_handler     on_clear_screen;
    Fp_ecma48_empty_handler     on_next_line;
    Fp_ecma48_char_handler      default_char_handler;
    Fp_ecma48_char_handler[255] char_handlers;
}

fn int parse_input_parameter(char* input, int[16]* output)
{
    uint index;
    uint output_index;
    while (input[index] && output_index < 16)
    {
        if(input[index] == ';') {
            index += 1;
            output_index += 1;
            continue;
        }
        if(string::is_digit(input[index])) {
            index += string::basic_atoi(&output[output_index], &input[index]);
            continue;
        }
        return index;
    }
    return index;
}

fn int Ecma48_handlers.dispatch(Ecma48_handlers* this, Type* ref, char* input)
{
    uint index = 0;

    if (input[index] == ESCAPE_SEQUENCE)
    {
        index += 1;
        switch (input[index])
        {
            case CONTROL_SEQUENCE_INTRODUCER:
            {
                index += 1;
                int[16] params;
                index += parse_input_parameter(&input[index], &params);
                switch (input[index])
                {
                case 'A':
                    this.on_cursor_mouvement(ref, Vec2{0, -params[0]});
                    break;
                case 'B':
                    this.on_cursor_mouvement(ref, Vec2{0, +params[0]});
                    break;
                case 'C':
                    this.on_cursor_mouvement(ref, Vec2{+params[0], 0});
                    break;
                case 'D':
                    this.on_cursor_mouvement(ref, Vec2{-params[0], 0});
                    break;
                case 'H':
                    if (this.on_set_cursor_position) this.on_set_cursor_position(ref, Vec2{params[1], params[0]});
                    break;
                case 'f':
                    if (this.on_cursor_mouvement) this.on_cursor_mouvement(ref, Vec2{params[1], params[0]});
                    break;
                case 'S': if (this.on_scroll_up)            this.on_scroll_up(ref, params[0]);          break;
                case 'T': if (this.on_scroll_down)          this.on_scroll_down(ref, params[0]);        break;
                case 'm': if (this.on_graphic_rendition)    this.on_graphic_rendition(ref, params[0]);  break;
                case 'J':
                    if (params[0] == 2 && this.on_clear_screen) {
                        this.on_clear_screen(ref);
                    }
                    break;
                }
                return index + 1;
            }
            case 'E':
                if (this.on_next_line) this.on_next_line(ref);
                break;
        }
    }

    char c = input[index];

    Fp_ecma48_char_handler char_handler = this.char_handlers[c];
    if (char_handler == null) char_handler = this.default_char_handler;
    if (char_handler != null) char_handler(ref, c);
    return 1;
}

fn void Ecma48_handlers.hooks_fd(Ecma48_handlers* this, Type* ref, int fd)
{
    char[std_io::STD_IO_BUFFER_SIZE]	read_buffer;
	int read_size = std_io::read(fd, &read_buffer, std_io::STD_IO_BUFFER_SIZE);
	if (read_size > 0) this.hooks(ref, &read_buffer, read_size);
}

fn void Ecma48_handlers.hooks(Ecma48_handlers* this, Type* ref, char* buffer, uint size)
{
    uint index = 0;
    while (index < size) index += this.dispatch(ref, &buffer[index]);
}

module ecma48::handler;

import utils::math;
import utils::string;
import utils::vector;
import keyboard::scancode;
import keyboard::codepage347;

fn void move_cursor(int fd, Vec2 mouvement)
{
    int x = mouvement[0];
    int y = mouvement[1];
    if (y) string::dprintf(fd, "\e[%d%c", math::abs(y), (y < 0) ? 'A' : 'B');
    if (x) string::dprintf(fd, "\e[%d%c", math::abs(x), (x < 0) ? 'D' : 'C');
}

import utils::collections;

fn int dispatch(Scancode key_scancode, int fd)
{
    Scancode[] keys = {Scancode.KEY_UP, Scancode.KEY_DOWN, Scancode.KEY_RIGHT, Scancode.KEY_LEFT};
	static Vec2[] ops = {
	    [Scancode.KEY_UP]    = { 0, -1},
	    [Scancode.KEY_DOWN]  = { 0, +1},
	    [Scancode.KEY_RIGHT] = {+1,  0},
	    [Scancode.KEY_LEFT]  = {-1,  0},
	};

    // utils::string::printf(" %d, (%x) [%s] ", key_scancode, keyboard::codepage347::TABLE[key_scancode], Scancode.names[(int)key_scancode]);
    // utils::string::printf(" [%s] ", Scancode.names[(int)key_scancode]);

    if (try i = collections::one_of(<Scancode>)(keys, key_scancode)) {
		ecma48::handler::move_cursor(fd, ops[keys[i]]);
    }
    else {
        char c = keyboard::codepage347::TABLE[key_scancode];
        if (string::dprintf(fd, "%c", c) < 0) return -1;
	}
	return 0;
}