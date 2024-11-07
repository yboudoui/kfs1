#ifndef UTILS_MEMORY_H
#define UTILS_MEMORY_H

#include <stddef.h>

void	*memcpy(void *dest, const void *src, size_t n);
// void	*memmove(void *dest, const void *src, size_t n);

#define DECLARE_MEMSET(type) \
inline static void memset_##type(type* dest, type value, size_t count) {    \
    for (size_t i = 0; i < count; i++) { dest[i] = value; }                 \
}

#define memset(type) memset_##type

#define DECLARE_MEMMOVE(type)                                               \
static type* memmove_##type(void *dest, const void *src, size_t n) {        \
	if (!dest || !src) return (dest);                                       \
	int		is_before   = (dest < src);                                     \
	int		direction   = is_before -(!is_before);                          \
	size_t	index       = (n - !is_before) * (!is_before);                  \
	while (n--)	{                                                           \
		((type*)dest)[index] = ((type*)src)[index];                         \
		index += direction;                                                 \
	}                                                                       \
    return (dest);                                                          \
}

#define memmove(type) memmove_##type

DECLARE_MEMSET(char)

#endif