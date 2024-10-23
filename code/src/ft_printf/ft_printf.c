#include "ft_printf.h"

int	ft_strlen_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (ft_putstr("(null)"));
	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	ft_putnbr(int nb)
{
	long	n;
	int		size;

	size = 0;
	n = nb;
	while (n || !size)
	{
		n /= 10;
		++size;
	}
	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		++size;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
	return (size);
}

int	putnbr_hex(unsigned int nb, char base)
{
	int				size;
	unsigned int	n;
	char			*basehex;

	if (base == 'x')
		basehex = "0123456789abcdef";
	else
		basehex = "0123456789ABCDEF";
	size = 0;
	n = nb;
	while (n || !size)
	{
		n /= 16;
		++size;
	}
	if (nb > 15)
	{
		putnbr_hex((nb / 16), base);
		ft_putchar(basehex[nb % 16]);
	}
	else
		ft_putchar(basehex[nb]);
	return (size);
}

int	putnbr_ptr(unsigned long long int nb)
{
	int						size;
	unsigned long long int	n;
	char					*basehex;

	basehex = "0123456789abcdef";
	size = 0;
	n = nb;
	while (n || !size)
	{
		n /= 16;
		++size;
	}
	if (nb > 15)
	{
		putnbr_ptr((nb / 16));
		ft_putchar(basehex[nb % 16]);
	}
	else
		ft_putchar(basehex[nb]);
	return (size);
}

int	putnbr_ui(unsigned int nb)
{
	unsigned int	n;
	int				size;

	size = 0;
	n = nb;
	while (n || !size)
	{
		n /= 10;
		++size;
	}
	if (nb > 9)
	{
		putnbr_ui(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb + '0');
	return (size);
}

int	putptr(void *ptr)
{
	unsigned long long	add;
	int					size;

	if (ptr == 0)
		return (ft_putstr("0x0"));
	add = (unsigned long long)ptr;
	ft_putstr("0x");
	size = putnbr_ptr(add) + 2;
	return (size);
}

int	sortandprint(char index, va_list args)
{
	int	len;

	len = 0;
	if (index == 'c')
		len = ft_putchar(va_arg(args, int));
	else if (index == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (index == 'p')
		len = putptr(va_arg(args, void *));
	else if (index == 'i' || index == 'd')
		len = ft_putnbr(va_arg(args, int));
	else if (index == 'u')
		len = putnbr_ui(va_arg(args, unsigned int));
	else if (index == 'x' || index == 'X')
		len = putnbr_hex(va_arg(args, unsigned int), index);
	else if (index == '%')
		len = ft_putchar('%');
	return (len);
}

int	is_valid_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	get_nb_args(const char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] != '\0' && is_valid_conv(str[i + 1]))
			{
				++nb;
				++i;
			}
		}
		++i;
	}
	return (nb);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	tab;
	int		len;

	if (!str)
		return (-1);
	va_start(tab, str);
	i = 0;
	len = ft_strlen_int(str) - (2 * get_nb_args(str));
	while (str[i])
	{
		if (str[i] == '%' && is_valid_conv(str[i + 1]))
			len = len + sortandprint(str[++i], tab);
		else if (str[i] != '%')
			ft_putchar (str[i]);
		++i;
	}
	va_end(tab);
	return (len);
}