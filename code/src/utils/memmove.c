#include "utils.h"

void	*memmove(void *dest, const void *src, size_t n)
{
	int		is_before;
	int		direction;
	size_t	index;

	if (!dest || !src)
		return (dest);
	is_before = (dest < src);
	direction = is_before -(!is_before);
	index = (n - !is_before) * (!is_before);
	while (n--)
	{
		((char *)dest)[index] = ((char *)src)[index];
		index += direction;
	}
	return (dest);
}