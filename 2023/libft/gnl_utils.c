#include "libft.h"

static size_t	len_ct(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size <= 0)
		return (len_ct(src));
	while (src[counter] != '\0' && counter < (size - 1))
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (counter < size)
		dst[counter] = '\0';
	while (src[counter])
		counter++;
	return (counter);
}

int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter])
		counter++;
	return (counter);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	c_size;

	c_size = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > (2147483647 / size) || size > (2147483647 / nmemb))
		return (0);
	ptr = (unsigned char *) malloc(c_size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, c_size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*proxy;
	size_t			counter;

	counter = 0;
	proxy = s;
	while (counter < n)
	{
		proxy[counter] = '\0';
		counter++;
	}
}