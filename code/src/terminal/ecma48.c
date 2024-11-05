#include "ecma48.h"
#include "std_io.h"

#include "utils.h"

int ecma48_move_cursor(char* buffer, int x, int y)
{
    int index = 0;

    if (buffer == NULL) return index;

    if (y)
        index += sprintf(&buffer[index], "\033[%d%c", abs(y), (y < 0) ? 'A' : 'B');
    if (x)
        index += sprintf(&buffer[index], "\033[%d%c", abs(x), (x < 0) ? 'D' : 'C');
    return index;
}

int ecma48_parse_sequence(const char* input, t_ecma48_sequence* seq)
{
    int index = 0;
    (*seq) = (t_ecma48_sequence){0};

    if (input[index] == ESCAPE_SEQUENCE)
    {
        index += 1;
        if (input[index] == CONTROL_SEQUENCE_INTRODUCER)
        {
            seq->is_controle = true;
            index += 1;
            int mouvement;
            index += basic_atoi(&mouvement, &input[index]);

            switch (input[index])
            {
            case 'A':
                seq->cursor_movement.y -= mouvement;
                break;
            case 'B':
                seq->cursor_movement.y += mouvement;
                break;
            case 'C':
                seq->cursor_movement.x += mouvement;
                break;
            case 'D':
                seq->cursor_movement.x -= mouvement;
                break;
            }
            return index;
        }
    }
    else
    {
        seq->character = input[index];
        seq->is_printable = true;
        if (input[index] == '\t') {
            seq->is_printable = false;
            // seq->cursor_movement.x += 4;
        }
        return 0;
    }
}

