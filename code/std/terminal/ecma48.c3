module terminal::ecma48(<Type>);

import utils::math;
import utils::string;
import utils::vector;

// #include "std_io.h" TODO: plug this


const char ESCAPE_SEQUENCE              = 0x1B;
const char CONTROL_SEQUENCE_INTRODUCER  = 0x5B;

def Fp_ecma48_char_handler      = fn void (Type*, char);
def Fp_ecma48_empty_handler     = fn void (Type*);
def Fp_ecma48_cursor_handler    = fn void (Type*, Vec2);

fn void dummy_handler(char c) {(void)c;}

struct Ecma48_handlers
{
    Type* ref;
    Fp_ecma48_cursor_handler    on_cursor_mouvement;
    Fp_ecma48_empty_handler     on_clear_screen;
    Fp_ecma48_char_handler      default_char_handler;
    Fp_ecma48_char_handler[255] char_handlers;
}

fn int move_cursor(int fd, int x = 0, int y = 0)
{
    if (y) string::dprintf(fd, "\033[%d%c", math::abs(y), (y < 0) ? 'A' : 'B');
    if (x) string::dprintf(fd, "\033[%d%c", math::abs(x), (x < 0) ? 'D' : 'C');
    return 0;
}

fn int Ecma48_handlers.hooks_handler(Ecma48_handlers* this, char* input)
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
                this.on_cursor_mouvement(this.ref, Vec2{0, -mouvement});
                break;
            case 'B':
                this.on_cursor_mouvement(this.ref, Vec2{0, +mouvement});
                break;
            case 'C':
                this.on_cursor_mouvement(this.ref, Vec2{+mouvement, 0});
                break;
            case 'D':
                this.on_cursor_mouvement(this.ref, Vec2{-mouvement, 0});
                break;
            case 'J':
                if (mouvement == 2 && this.on_clear_screen) {
                    this.on_clear_screen(this.ref);
                }
                break;
            }
            return index + 1;
        }
    }
    char c = input[index];
    Fp_ecma48_char_handler char_handler = this.char_handlers[c];
    if (char_handler) {
        char_handler(this.ref, c);
    } else if (this.default_char_handler) {
        this.default_char_handler(this.ref, c);
    } 
    return 1;
}

fn void Ecma48_handlers.hooks(Ecma48_handlers* this, char* buffer, uint size)
{
    for (uint i = 0; i < size; i+= this.hooks_handler(&buffer[i]));
}
