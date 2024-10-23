#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"
#include "keyboard_scancode.h"
#include "readline.h"
#define TABSIZE 4

typedef int (*t_fp_terminal_input_handler)(t_key_scancode);
typedef struct s_terminal_input_handler {
  t_fp_terminal_input_handler default_handler;
  t_fp_terminal_input_handler handlers[MAX_KEY_SCANCODE];
} t_terminal_input_handler;

typedef struct s_terminal {
  t_vga_entry_color           default_color;


  t_vec2                      current_position;

  
  t_terminal_input_handler    input_handler;
  t_readline_buffer           readline_buffer;
  t_vga_frame                 vga_frame;

} t_terminal;

t_terminal* terminal_current(t_terminal* frame);
#define CURRENT_TERMINAL t_terminal* terminal = terminal_current(NULL);

void  terminal_putchar_at(t_vec2 position, char c);
void  terminal_putchar(char c);
void  terminal_write(const char* data, size_t size);
void  terminal_write_string(const char* data);
void  terminal_write_number(t_itoa_base base, int nb);
void terminal_put_block_at(char* buffer, t_vec2 position);

void  terminal_clear(void);
void  terminal_update(void);
int   terminal_handle_input(t_key_scancode key_scancode);
void  terminal_reset_position(void);


////
void move_cursor_to_new_line_at(int n);
void move_cursor_position_by(int n);

#endif