#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "memory.h"

typedef struct {
  int x, y;
} t_vec2;
typedef void (*t_fp_set_vec2)(t_vec2*);

t_vec2 vec2_add(t_vec2 a, t_vec2 b);
void vec2_increment(t_vec2* a, t_vec2 b);

void clamp_int(int* value, int min, int max);

void clamp_vec2(t_vec2* value, t_vec2 min, t_vec2 max);

typedef struct s_clamped_vec2 {
 t_vec2 min, max, pos;
} t_clamped_vec2;

bool _with_clamped_vec2(t_clamped_vec2* clamped_vec2, size_t count, ...);
#define with_clamped_vec2(clamped_vec2, ...) _with_clamped_vec2(clamped_vec2, sizeof(t_fp_set_vec2[]){__VA_ARGS__} / sizeof(t_fp_set_vec2), __VA_ARGS__)

size_t clamped_vec2_get_linear_position(t_clamped_vec2 clamped_vec2);
void clamped_vec2_set_with_linear_position_by(t_clamped_vec2* clamped_vec2, int n);


static void vec2_up(t_vec2* pos)    { pos->y -= 1; }
static void vec2_down(t_vec2* pos)  { pos->y += 1; }
static void vec2_left(t_vec2* pos)  { pos->x -= 1; }
static void vec2_right(t_vec2* pos) { pos->x += 1; }

static void new_line(t_vec2* pos)   { pos->x = 0; pos->y -= 1; }

#endif