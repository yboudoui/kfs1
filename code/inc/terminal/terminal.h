#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"


typedef struct {
  t_vga_entry_color default_color;
  t_vec2            current_position;
  t_vga_frame       vga_frame;
} t_terminal;

t_terminal* terminal_current(t_terminal* frame);
void terminal_return(t_terminal* terminal);


void terminal_putchar_at(t_terminal* terminal, t_vec2 position, char c);

void terminal_putchar(t_terminal* terminal, char c);
void terminal_write(t_terminal* terminal, const char* data, size_t size);
void terminal_write_string(t_terminal* terminal, const char* data);
void terminal_write_number(t_terminal* terminal, t_itoa_base base, int nb);

void terminal_clear(t_terminal* terminal);

void terminal_reset_position(void);

#endif