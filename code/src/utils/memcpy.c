#include "utils.h"

void	*memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d || !s)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}