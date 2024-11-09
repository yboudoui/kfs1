#ifndef ECMA48_H
#define ECMA48_H

#include "keyboard.h"
#include <stdbool.h>
#include "utils.h"
#include "vectors.h"


#define ESCAPE_SEQUENCE '\033'
#define CONTROL_SEQUENCE_INTRODUCER '['

typedef void (*t_fp_ecma48_char_handler)(char);

static void dummy_handler(char c) {(void)c;}

typedef struct s_ecma48_handlers {
    void (*on_cursor_mouvement)(t_vec2);
    void (*on_clear_screen)(void);
    t_fp_ecma48_char_handler    default_char_handler;
    t_fp_ecma48_char_handler    char_handlers[255];
} t_ecma48_handlers;

void    ecma48_hooks(const char* buffer, size_t size, t_ecma48_handlers* handlers);
int     ecma48_move_cursor(int fd, int x, int y);


#endif