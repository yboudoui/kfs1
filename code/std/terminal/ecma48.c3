module terminal::ecma48;

import utils::math;
import utils::string;
import utils::printf;
import utils::vector;

// #include "std_io.h" TODO: plug this


const char ESCAPE_SEQUENCE              = 0x1B;
const char CONTROL_SEQUENCE_INTRODUCER  = 0x5B;

def Fp_ecma48_char_handler      = fn void (char);
def Fp_ecma48_empty_handler     = fn void ();
def Fp_ecma48_cursor_handler    = fn void (vector::Vec2);

fn void dummy_handler(char c) {(void)c;}

struct Ecma48_handlers
{
    Fp_ecma48_cursor_handler    on_cursor_mouvement;
    Fp_ecma48_empty_handler     on_clear_screen;
    Fp_ecma48_char_handler      default_char_handler;
    Fp_ecma48_char_handler[255] char_handlers;
}

fn int move_cursor(int fd, int x, int y)
{
    if (y) printf::dprintf(fd, "\033[%d%c", math::abs(y), (y < 0) ? 'A' : 'B');
    if (x) printf::dprintf(fd, "\033[%d%c", math::abs(x), (x < 0) ? 'D' : 'C');
    return 0;
}

fn int hooks_handler(char* input, Ecma48_handlers* handlers)
{
    uint index = 0;

    if (input[index] == ESCAPE_SEQUENCE)
    {
        index += 1;
        if (input[index] == CONTROL_SEQUENCE_INTRODUCER)
        {
            index += 1;
            int mouvement;
            index += string::basic_atoi(&mouvement, &input[index]);

            switch (input[index])
            {
            case 'A':
                handlers.on_cursor_mouvement(vector::Vec2{0, -mouvement});
                break;
            case 'B':
                handlers.on_cursor_mouvement(vector::Vec2{0, +mouvement});
                break;
            case 'C':
                handlers.on_cursor_mouvement(vector::Vec2{+mouvement, 0});
                break;
            case 'D':
                handlers.on_cursor_mouvement(vector::Vec2{-mouvement, 0});
                break;
            case 'J':
                if (mouvement == 2 && handlers.on_clear_screen) {
                    handlers.on_clear_screen();
                }
                break;
            }
            return index + 1;
        }
    }
    char c = input[index];
    Fp_ecma48_char_handler char_handler = handlers.char_handlers[c];
    if (char_handler) {
        char_handler(c);
    } else if (handlers.default_char_handler) {
        handlers.default_char_handler(c);
    } 
    return 1;
}

fn void hooks(char* buffer, uint size, Ecma48_handlers* handlers)
{
    for (uint i = 0; i < size; i+= hooks_handler(&buffer[i], handlers));
}
