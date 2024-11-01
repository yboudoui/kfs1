#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"
#include "keyboard.h"
#include "std_io.h"

typedef struct s_terminal {
  t_vga_frame         vga_frame;
  t_vga_entry_color   default_color;
  t_fp_input_handler  input_handler;
  t_stdio             stdio;

  t_vec2              current_position;
} t_terminal;

t_terminal* current_terminal(t_terminal* frame);
#define CURRENT_TERMINAL t_terminal* terminal = current_terminal(NULL);

void  terminal_putchar_at(t_vec2 position, char c);
void  terminal_putchar(char c);
int   terminal_write(const char* data, size_t size);

void  terminal_put_block_at(size_t size, char* buffer, t_vec2 position);

void  terminal_clear(void);

//
void terminal_init(t_vga_entry_color default_color, t_fp_input_handler input_handler);


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
	  {KEY_DELETE,	  {0x7F, 0x00}},
    {NULL, -1}  // End of array marker
};

t_key_scancode get_scancode_from_sequence(const char* sequence);

#endif