#ifndef ECMA48_H
#define ECMA48_H

#include "keyboard.h"
#include <stdbool.h>
#include "utils.h"
#include "vectors.h"


#define ESCAPE_SEQUENCE "\033"
#define CONTROL_SEQUENCE_INTRODUCER "["

#define CURSOR_MOVE_RIGHT   ESCAPE_SEQUENCE CONTROL_SEQUENCE_INTRODUCER "%dC"
#define CURSOR_MOVE_LEFT    ESCAPE_SEQUENCE CONTROL_SEQUENCE_INTRODUCER "%dD"

// typedef enum e_cursor_mouvement {
//     UP, DOWN, RIGHT, LEFT,
//     MAX_MOUVEMENT,
// } t_cursor_mouvement;

// static char* cursor_mouvement[] = {
//     [RIGHT] = ESCAPE_SEQUENCE CONTROL_SEQUENCE_INTRODUCER "%dC",
//     [LEFT]  = ESCAPE_SEQUENCE CONTROL_SEQUENCE_INTRODUCER "%dD",
// };

typedef enum e_ecma48_sequence_type {
    CHARACTER,
    CURSOR_MOVEMENT,
} t_ecma48_sequence_type;

typedef union u_ecma48_sequence_data {
    char    character;
    t_vec2  cursor_movement;
} t_ecma48_sequence_data;

typedef struct s_ecma48_sequence {
    t_ecma48_sequence_type type;
    t_ecma48_sequence_data data;
} t_ecma48_sequence;

int parse_sequence(const char* input, t_ecma48_sequence* seq);

#endif