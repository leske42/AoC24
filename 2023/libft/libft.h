#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include <string.h>

//original libft
long int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *str, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		count_words(const char *str, char c);

//get_next_line
char	*get_next_line(int fd);
char	*ft_gnljoin(char *s1, char *s2);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

//printf and subfunctions
int		ft_printf(const char *tipus, ...);
void	ft_putchar(char c);
int		print_i(int i);
int		print_x(unsigned int x);
int		print_xup(unsigned int x);
int		print_c(char c);
int		print_s(char *str);
int		print_p(void *ptr);
int		print_u(unsigned int u);
int		print_l(long int u);

//hotrace and utils
# ifndef HASHTABLE_SIZE
#  define HASHTABLE_SIZE 10000000
# endif

typedef struct s_keyvalue
{
	char				*key;
	char				*val;
	size_t				hash2;
	struct s_keyvalue	*next;
}				t_keyvalue;

int		read_data(t_keyvalue **hashtable);
int		read_search_key(t_keyvalue **hashtable);
size_t	get_hash(char *keyvalue);
size_t	get_hash2(char *keyvalue);
void	free_hashtable(t_keyvalue **hashtable);
void	free_list(t_keyvalue *list);

#endif