#ifndef ECMA48_H
#define ECMA48_H

#include "keyboard.h"
#include <stdbool.h>
#include "utils.h"
#include "vectors.h"


#define ESCAPE_SEQUENCE '\033'
#define CONTROL_SEQUENCE_INTRODUCER '['

// typedef struct s_ecma48_sequence {
//     bool    is_controle;
    
//     char    character;
//     t_vec2  cursor_movement;

//     // struct {
//     //     int parameters[16];
//     //     size_t pos;
//     // } parameters;
// } t_ecma48_sequence;

typedef void (*t_fp_ecma48_char_handler)(char);

typedef struct s_ecma48_handlers {
    void (*on_cursor_mouvement)(t_vec2);
    t_fp_ecma48_char_handler    default_char_handler;
    t_fp_ecma48_char_handler    char_handlers[255];
} t_ecma48_handlers;
int ecma48_hooks(const char* input, t_ecma48_handlers* handlers);

// int ecma48_parse_sequence(const char* input, t_ecma48_sequence* seq);

int ecma48_move_cursor(int fd, int x, int y);

#endif