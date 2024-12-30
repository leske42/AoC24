#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	digit_count(int y)
{
	int	counter;
	int	nb;

	counter = 1;
	if (y == -2147483648)
		return (11);
	else if (y < 0)
		nb = (y * -1);
	else
		nb = y;
	while (nb > 9)
	{
		nb = nb / 10;
		counter++;
	}
	if (y < 0)
		return (counter + 1);
	else
		return (counter);
}

static void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
		ft_putnbr(nb);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int	print_i(int i)
{
	ft_putnbr(i);
	return (digit_count(i));
}

static int	digit_u(unsigned int y)
{
	int	counter;

	counter = 1;
	while (y > 9)
	{
		y = y / 10;
		counter++;
	}
	return (counter);
}

static void	put_u(unsigned int u)
{
	if (u > 9)
	{
		put_u(u / 10);
		put_u(u % 10);
	}
	else
		ft_putchar(u + '0');
}

int	print_u(unsigned int u)
{
	put_u(u);
	return (digit_u(u));
}

static int	digit_l(long int y)
{
	int	counter;
	long int	nb;

	counter = 1;
	if (y < 0)
		nb = (y * -1);
	else
		nb = y;
	while (nb > 9)
	{
		nb = nb / 10;
		counter++;
	}
	if (y < 0)
		return (counter + 1);
	else
		return (counter);
}

static void	ft_putlong(long int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
		ft_putlong(nb);
	}
	else if (nb > 9)
	{
		ft_putlong(nb / 10);
		ft_putlong(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int	print_l(long int u)
{
	ft_putlong(u);
	return (digit_l(u));
}
