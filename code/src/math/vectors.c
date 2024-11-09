#include "vectors.h"

t_vec2 vec2_add(t_vec2 a, t_vec2 b)
{
    return (t_vec2){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}

void vec2_increment(t_vec2* a, t_vec2 b)
{
    (*a) = vec2_add(*a, b);
}

void clamp_int(int* value, int min, int max)
{
    if (*value < min) (*value) = min;
    if (*value > max) (*value) = max;
}


void clamp_vec2(t_vec2* value, t_vec2 min, t_vec2 max)
{
    clamp_int(&value->x, min.x, max.x);
    clamp_int(&value->y, min.y, max.y);
}

void update_clamp_vec2(t_clamped_vec2* clamped_vec2)
{
    clamp_vec2(&clamped_vec2->pos, clamped_vec2->min, clamped_vec2->max);
}

bool _with_clamped_vec2(t_clamped_vec2* clamped_vec2, size_t count, ...)
{
    va_list args;
    va_start(args, count);

    t_vec2 tmp = clamped_vec2->pos;

    for (int i = 0; i < count; i++) {
        t_fp_set_vec2 update = va_arg(args, t_fp_set_vec2);
        update(&clamped_vec2->pos);
    }

    va_end(args);
    update_clamp_vec2(clamped_vec2);
    return (memcmp(&clamped_vec2->pos, &tmp, sizeof(t_vec2)) == 0);
}

size_t clamped_vec2_get_linear_position(t_clamped_vec2 clamped_vec2)
{
    return clamped_vec2.pos.y * clamped_vec2.max.x + clamped_vec2.pos.x;
}

void clamped_vec2_set_with_linear_position_by(t_clamped_vec2* clamped_vec2, int n)
{
    size_t linear_position = clamped_vec2_get_linear_position(*clamped_vec2);
    linear_position += n;
    clamped_vec2->pos.x = linear_position % clamped_vec2->max.x;
    clamped_vec2->pos.y = linear_position / clamped_vec2->max.x;
    update_clamp_vec2(clamped_vec2);
}