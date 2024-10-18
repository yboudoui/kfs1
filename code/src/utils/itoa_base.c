#include "utils.h"

void reverse_string(char *str, size_t length) {
    size_t start = 0;
    size_t end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


void itoa_base(char *buffer, int nb, char* base)
{
    size_t i = 0;
    size_t base_len = strlen(base);

    while (nb > base_len)
    {
        buffer[i++] = base[nb % base_len];
        nb /= base_len;
    }
    buffer[i++] = base[nb % base_len];
    buffer[i] = 0;
    reverse_string(buffer, i);
}