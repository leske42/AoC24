#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		counter;
	int		counter2;
	char	*ptr;

	counter = 0;
	counter2 = 0;
	while (src[counter])
		counter++;
	ptr = (char *) malloc(counter + 1);
	if (!ptr)
		return (0);
	while (counter2 <= counter)
	{
		ptr[counter2] = src[counter2];
		counter2++;
	}
	ptr[counter2] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	counter;
	char			*sub_str;

	counter = start;
	if (start >= ((unsigned int)ft_strlen(s)))
		return (ft_strdup(""));
	while (s[counter])
		counter++;
	if ((counter - start) < len)
		sub_str = (char *)malloc(sizeof(char ) * ((counter - start) + 1));
	else
		sub_str = (char *)malloc(sizeof(char ) * (len + 1));
	if (!sub_str)
		return (0);
	counter = 0;
	while (len && s[start])
	{
		sub_str[counter++] = s[start++];
		len--;
	}
	sub_str[counter] = '\0';
	return (sub_str);
}

int	count_words(const char *str, char c)
{
	int	cr;
	int	flag;
	int	words;

	flag = 0;
	cr = 0;
	words = 0;
	while (str[cr])
	{
		if (flag == 0 && str[cr] != c)
			words++;
		if (str[cr] != c)
			flag = 1;
		else if (str[cr] == c)
			flag = 0;
		cr++;
	}
	return (words);
}

static int	word_len(const char *str, int counter, char c)
{
	int	i;

	i = 0;
	while (str[counter] && str[counter] != c)
	{
		counter++;
		i++;
	}
	return (i);
}

static char	**free_everything(char **arr, int m_ctr)
{
	int	counter;

	counter = 0;
	while (counter < m_ctr)
	{
		free(arr[counter]);
		counter++;
	}
	free(arr);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**arr;
	int		m_ctr;
	int		ctr;

	ctr = 0;
	arr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!arr)
		return (0);
	m_ctr = 0;
	while (m_ctr < count_words(str, c))
	{
		while (str[ctr] == c)
			ctr++;
		if (str[ctr] != c)
		{
			arr[m_ctr] = ft_substr(str, ctr, word_len(str, ctr, c));
			if (!arr[m_ctr])
				return (free_everything(arr, m_ctr));
			ctr += word_len(str, ctr, c);
			m_ctr++;
		}
	}
	arr[m_ctr] = NULL;
	return (arr);
}