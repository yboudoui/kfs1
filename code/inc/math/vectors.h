#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <stddef.h>

typedef struct {
  int x, y;
} t_vec2;

t_vec2 vec2_add(t_vec2 a, t_vec2 b);
#endif