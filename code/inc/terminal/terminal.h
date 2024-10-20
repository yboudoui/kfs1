#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"

typedef struct s_terminal t_terminal;

typedef int (*t_fp_terminal_input_handler)(t_terminal* terminal);

struct s_terminal {
  t_vga_entry_color           default_color;
  t_vga_frame                 vga_frame;
  t_vec2                      current_position;
  t_fp_terminal_input_handler default_handler;
  t_fp_terminal_input_handler handlers[255];
};

t_terminal* terminal_current(t_terminal* frame);

void terminal_return(void);

void  terminal_putchar_at(t_vec2 position, char c);
void  terminal_putchar(char c);
void  terminal_write(const char* data, size_t size);
void  terminal_write_string(const char* data);
void  terminal_write_number(t_itoa_base base, int nb);

void  terminal_clear(void);
void  terminal_update(void);
int   terminal_handle_input(char c);
void  terminal_reset_position(void);

#endif