#include "vectors.h"

t_vec2 vec2_add(t_vec2 a, t_vec2 b)
{
    return (t_vec2){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}
