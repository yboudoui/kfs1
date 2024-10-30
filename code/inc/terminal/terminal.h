#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"
#include "keyboard_scancode.h"
#define TABSIZE 4

typedef int (*t_fp_terminal_input_handler)(t_key_scancode);
typedef struct s_terminal_input_handler {
  t_fp_terminal_input_handler default_handler;
  t_fp_terminal_input_handler handlers[MAX_KEY_SCANCODE];
} t_terminal_input_handler;

typedef struct s_terminal {
  t_vga_frame                 vga_frame;
  t_vga_entry_color           default_color;
  t_terminal_input_handler    input_handler;
  t_vec2                      current_position;
} t_terminal;

t_terminal* current_terminal(t_terminal* frame);
#define CURRENT_TERMINAL t_terminal* terminal = current_terminal(NULL);

void  terminal_putchar_at(t_vec2 position, char c);
void  terminal_putchar(char c);
int   terminal_write(const char* data, size_t size);

void  terminal_put_block_at(size_t size, char* buffer, t_vec2 position);

void  terminal_clear(void);
void  terminal_update(void);
int   terminal_handle_input(t_key_scancode key_scancode);

////
void  move_cursor_position_by(int n);

bool  move_cursor_up(void);
bool  move_cursor_down(void);

#endif