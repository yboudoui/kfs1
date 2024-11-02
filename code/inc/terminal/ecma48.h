#ifndef ECMA48_H
#define ECMA48_H

#include "keyboard.h"
#include <stdbool.h>
#include "utils.h"

bool get_scancode_from_sequence(size_t* size, char** sequence, t_key_scancode* key_scancode);
bool get_sequence_from_scancode(t_key_scancode key_scancode, char** sequence);

#endif