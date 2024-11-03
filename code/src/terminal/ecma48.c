#include "ecma48.h"
#include "std_io.h"

int parse_sequence(const char* input, t_ecma48_sequence* seq)
{
    int index = 0;

    if (input[index] == '\033')
    {
        index += 1;
        if (input[index] == '[')
        {
            index += 1;
            int mouvement;
            index += basic_atoi(&mouvement, &input[index]);

            (*seq).type = CURSOR_MOVEMENT;
            switch (input[index])
            {
            case 'A':
                (*seq).data.cursor_movement.y -= mouvement;
                break;
            case 'B':
                (*seq).data.cursor_movement.y += mouvement;
                break;
            case 'C':
                (*seq).data.cursor_movement.x += mouvement;
                break;
            case 'D':
                (*seq).data.cursor_movement.x -= mouvement;
                break;
            }
            return index;
        }
    }
    else
    {
        (*seq).type = CHARACTER;
        (*seq).data.character = *input;
        return 0;
    }
}