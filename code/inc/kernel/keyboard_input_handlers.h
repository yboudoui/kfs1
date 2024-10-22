#ifndef KERNEL_KEYBOARD_INPUT_HANDLERS
#define KERNEL_KEYBOARD_INPUT_HANDLERS

#include "shell.h"

int terminal_input_fallback(t_key_scancode key_scancode);
int terminal_input_on_return(t_key_scancode key_scancode);
int terminal_input_on_backspace(t_key_scancode key_scancode);
int terminal_input_on_del(t_key_scancode key_scancode);
int terminal_input_on_tab(t_key_scancode key_scancode);
int terminal_input_on_button_left(t_key_scancode key_scancode);
int terminal_input_on_button_right(t_key_scancode key_scancode);
int terminal_input_on_button_up(t_key_scancode key_scancode);
int terminal_input_on_button_down(t_key_scancode key_scancode);

#endif