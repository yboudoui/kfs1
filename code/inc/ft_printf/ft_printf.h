#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_strlen_int(const char *str);
int	get_nb_args(const char *str);
int	is_valid_conv(char c);
int	sortandprint(char index, va_list args);
int	ft_putnbr(int nb);
int	putnbr_hex(unsigned int nb, char base);
int	putnbr_ui(unsigned int nb);
int	putptr(unsigned long long int ptr);
int	putnbr_ptr(unsigned long long int nb);

#endif