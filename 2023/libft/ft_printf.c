#include "libft.h"

int	print_s(char *str)
{
	int	counter;

	counter = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[counter])
	{
		write(1, &str[counter], 1);
		counter++;
	}
	return (counter);
}

int	print_c(char c)
{
	write(1, &c, 1);
	return (1);
}

int	printf_sub(va_list arg_list, const char typ)
{
	int	len;

	len = 0;
	if (typ == 'c')
		len = print_c(va_arg(arg_list, int));
	else if (typ == 's')
		len = print_s(va_arg(arg_list, char *));
    else if (typ == 'd' || typ == 'i')
		len = print_i(va_arg(arg_list, int));
    else if (typ == 'u')
		len = print_u(va_arg(arg_list, unsigned int));
    else if (typ == 'l')
		len = print_l(va_arg(arg_list, long int));
	else if (typ == '%')
		len = print_c('%');
	return (len);
}

int	flags_check(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i')
		return (1);
	else if (c == 'u' || c == 'l' || c == '%')
		return (1);
	else
		return (0);
}

int	ft_printf(const char *tipus, ...)
{
	int		counter;
	int		len;
	va_list	arg_list;

	va_start(arg_list, tipus);
	counter = 0;
	len = 0;
	while (tipus[counter])
	{
		if (tipus[counter] == '%')
		{
			counter++;
			if (!flags_check(tipus[counter]))
				return (-1);
			else
				len = len + printf_sub(arg_list, tipus[counter]);
		}
		else
			len = len + print_c(tipus[counter]);
		counter++;
	}
	va_end(arg_list);
	return (len);
}