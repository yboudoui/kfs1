#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
void itoa_base(char *buffer, int nb, char* base, size_t base_len);
void *memset(char c, void *buffer, size_t len);