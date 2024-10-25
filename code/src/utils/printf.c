#include "utils.h"
#include "terminal.h"

typedef int (*t_fp_dump)(char *buffer, va_list *args);

int dump_character(char *buffer, va_list *args)
{
	buffer[0] = va_arg(*args, int);
	return 1;
}

int dump_string(char *buffer, va_list *args)
{
	char* str = va_arg(*args, char *);
	size_t	size = strlen(str);
	memcpy(buffer, str, size);
	return size;
}

int dump_pointer(char *buffer, va_list *args)
{
	unsigned long long	address = va_arg(*args, unsigned long long int);

	if (address == 0) {
		memcpy(buffer, "0x0", 3);
		return (3);
	}
	memcpy(buffer, "0x", 2);
	return (itoa_lower_hexa(buffer + 2, address) + 2);
}

int dump_number(char *buffer, va_list *args)
{
	int number = va_arg(*args, int);
	return (itoa_decimal(buffer, number));
}

int dump_unsigned_number(char *buffer, va_list *args)
{
	int number = va_arg(*args, unsigned int);
	return (itoa_decimal(buffer, number));
}

int dump_lower_hexadecimal_case(char *buffer, va_list *args)
{
	unsigned int number = va_arg(*args, unsigned int);
	return (itoa_lower_hexa(buffer, number));
}

int dump_upper_hexadecimal_case(char *buffer, va_list *args)
{
	unsigned int number = va_arg(*args, unsigned int);
	return (itoa_upper_hexa(buffer, number));
}

int dump_percentage(char *buffer, va_list *args)
{
	buffer[0] = '%';
	return 1;
}

static const t_fp_dump a[128] = {
	['c'] = dump_character,
	['s'] = dump_string,
	['p'] = dump_pointer,
	['i'] = dump_number,
	['d'] = dump_number,
	['u'] = dump_unsigned_number,
	['x'] = dump_lower_hexadecimal_case,
	['X'] = dump_upper_hexadecimal_case,
	['%'] = dump_percentage,
	NULL,
};

int	printf(const char *str, ...)
{
	va_list	tab;
	int		len = 0;

	if (!str)
		return (-1);
	char buffer[2048] = {0};
	
	va_start(tab, str);
	while (*str)
	{
		if (str[0] == '%' && str[1][a]) {
			len += str[1][a](&buffer[len], &tab);
			str += 2;
		} else {
			buffer[len++] = *str++;
		}
	}
	va_end(tab);
	return (terminal_write(buffer, len));
}