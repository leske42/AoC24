#include "libft.h"

int	init(char *str)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter] && str[counter] != '\n')
		counter++;
	if (str[counter] == '\n')
		return (1);
	else
		return (0);
}

char	*extract_line(char *proc_text)
{
	int		counter;
	char	*line;

	counter = 0;
	if (!proc_text[counter])
		return (0);
	while (proc_text[counter] != '\n' && proc_text[counter])
		counter++;
	counter++;
	line = (char *)malloc(sizeof(char) * counter + 1);
	if (!line)
		return (0);
	ft_strlcpy(line, proc_text, counter + 1);
	return (line);
}

char	*ft_reading(int fd, char *proc_text)
{
	char	*buf;
	int		char_num;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	while (!init(proc_text))
	{
		char_num = read(fd, buf, BUFFER_SIZE);
		if (char_num < 0)
		{
			free(buf);
			free(proc_text);
			return (0);
		}
		if (char_num == 0)
			break ;
		buf[char_num] = '\0';
		proc_text = ft_gnljoin(proc_text, buf);
		if (!proc_text)
			return (0);
	}
	free(buf);
	return (proc_text);
}

char	*remove_line(char *s1)
{
	int			counter;
	char		*marker;
	char		*result;

	counter = 0;
	while (s1[counter] && s1[counter] != '\n')
		counter++;
	if (s1[counter] == '\n')
		marker = &s1[counter + 1];
	else
	{
		free(s1);
		return (0);
	}
	result = (char *)malloc(ft_strlen(marker) + 1);
	if (!result)
	{
		free(s1);
		return (0);
	}
	ft_strlcpy(result, marker, ft_strlen(marker) + 1);
	free(s1);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*proc_text[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (proc_text[fd] == NULL)
	{
		proc_text[fd] = ft_calloc(1, 1);
		if (!proc_text[fd])
			return (0);
	}
	proc_text[fd] = ft_reading(fd, proc_text[fd]);
	if (!proc_text[fd])
		return (0);
	line = extract_line(proc_text[fd]);
	proc_text[fd] = remove_line(proc_text[fd]);
	return (line);
}