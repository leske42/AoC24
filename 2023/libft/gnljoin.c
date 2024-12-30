#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ctr1;
	int		ctr2;
	char	*new_str;

	ctr1 = ft_strlen((char *)s1);
	ctr2 = ft_strlen((char *)s2);
	new_str = (char *)malloc((ctr1 + ctr2 + 1) * 1);
	if (!new_str)
		return (0);
	ctr1 = 0;
	ctr2 = 0;
	while (s1[ctr1])
	{
		new_str[ctr1] = s1[ctr1];
		ctr1++;
	}
	while (s2[ctr2])
	{
		new_str[ctr1] = s2[ctr2];
		ctr1++;
		ctr2++;
	}
	new_str[ctr1] = '\0';
	return (new_str);
}

char	*ft_gnljoin(char *s1, char *s2)
{
	int		ctr1;
	int		ctr2;
	char	*new_str;

	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		free(s1);
		free(s2);
		return (0);
	}
	ctr1 = 0;
	ctr2 = 0;
	while (s1[ctr1])
	{
		new_str[ctr1] = s1[ctr1];
		ctr1++;
	}
	while (s2[ctr2])
		new_str[ctr1++] = s2[ctr2++];
	new_str[ctr1] = '\0';
	free (s1);
	return (new_str);
}