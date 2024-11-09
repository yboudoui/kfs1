#include "ecma48.h"
#include "std_io.h"

#include "utils.h"

int ecma48_move_cursor(int fd, int x, int y)
{
    if (y)
        dprintf(fd, "\033[%d%c", abs(y), (y < 0) ? 'A' : 'B');
    if (x)
        dprintf(fd, "\033[%d%c", abs(x), (x < 0) ? 'D' : 'C');
}

int ecma48_hooks_handler(const char* input, t_ecma48_handlers* handlers)
{
    int index = 0;

    if (input[index] == ESCAPE_SEQUENCE)
    {
        index += 1;
        if (input[index] == CONTROL_SEQUENCE_INTRODUCER)
        {
            index += 1;
            int mouvement;
            index += basic_atoi(&mouvement, &input[index]);

            switch (input[index])
            {
            case 'A':
                handlers->on_cursor_mouvement((t_vec2){.x = 0, .y = -mouvement});
                break;
            case 'B':
                handlers->on_cursor_mouvement((t_vec2){.x = 0, .y = +mouvement});
                break;
            case 'C':
                handlers->on_cursor_mouvement((t_vec2){.x = +mouvement, .y = 0});
                break;
            case 'D':
                handlers->on_cursor_mouvement((t_vec2){.x = -mouvement, .y = 0});
                break;
            case 'J':
                if (mouvement == 2 && handlers->on_clear_screen) {
                    handlers->on_clear_screen();
                }
                break;
            }
            return index + 1;
        }
    }
    char c = input[index];
    t_fp_ecma48_char_handler char_handler = handlers->char_handlers[c];
    if (char_handler) char_handler(c);
    else if (handlers->default_char_handler) handlers->default_char_handler(c);
    return 1;
}

void ecma48_hooks(const char* buffer, size_t size, t_ecma48_handlers* handlers)
{
    for (size_t i = 0; i < size; i+= ecma48_hooks_handler(&buffer[i], handlers));
}
