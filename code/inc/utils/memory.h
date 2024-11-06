#ifndef UTILS_MEMORY_H
#define UTILS_MEMORY_H

#include <stddef.h>

void	*memcpy(void *dest, const void *src, size_t n);
void	*memmove(void *dest, const void *src, size_t n);

#define DECLARE_MEMSET(type) \
inline static void memset_##type(type* dest, type value, size_t count) { \
    for (size_t i = 0; i < count; i++) { dest[i] = value; } \
}


DECLARE_MEMSET(char)

#define memset(type) memset_##type

#endif