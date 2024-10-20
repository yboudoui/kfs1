#ifndef UTILS_MEMSET_H
#define UTILS_MEMSET_H

#include <stddef.h>

#define DECLARE_MEMSET(type) \
inline static void memset_##type(type* dest, type value, size_t count) { \
    for (size_t i = 0; i < count; i++) { dest[i] = value; } \
}


DECLARE_MEMSET(char)

#define memset(type) memset_##type

#endif