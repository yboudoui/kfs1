#include "ecma48.h"

#define ESCAPE_SEQUENCE "\033"
#define CONTROL_SEQUENCE_INTRODUCER ESCAPE_SEQUENCE"["

typedef struct {
    t_key_scancode  scancode;
    const char*     sequence;
} EscapeSequenceMapping;

static EscapeSequenceMapping sequence_to_scancode[] = {
    {KEY_UP,        CONTROL_SEQUENCE_INTRODUCER "1A"},
    {KEY_DOWN,      CONTROL_SEQUENCE_INTRODUCER "1B"},
    {KEY_RIGHT,     CONTROL_SEQUENCE_INTRODUCER "1C"},
    {KEY_LEFT,      CONTROL_SEQUENCE_INTRODUCER "1D"},
    {KEY_BACKSPACE, "\b"},
    {KEY_ENTER,     "\n"},
    {KEY_TAB,       "\t"},
	{KEY_DELETE,	"\177"},
    {-1, NULL}  // End of array marker
};


bool get_scancode_from_sequence(size_t* size, char** sequence, t_key_scancode* key_scancode)
{
    size_t sequence_size;
    for (int i = 0; sequence_to_scancode[i].sequence != NULL; i++)
    {
        if (strcmp(*sequence, sequence_to_scancode[i].sequence) == 0)
        {
            (*key_scancode) = sequence_to_scancode[i].scancode;
            sequence_size = strlen(sequence_to_scancode[i].sequence);
            (*sequence) += sequence_size;
            (*size) -= sequence_size;
            return true;
        }
    }
    return false;
}

bool get_sequence_from_scancode(t_key_scancode key_scancode, char** sequence)
{
    for (int i = 0; sequence_to_scancode[i].sequence != NULL; i++)
    {
        if (key_scancode == sequence_to_scancode[i].scancode)
        {
            memcpy(*sequence, sequence_to_scancode[i].sequence, strlen(sequence_to_scancode[i].sequence));
            return true;
        }
    }
    (**sequence) = codepage_437[key_scancode];
    return true;
}