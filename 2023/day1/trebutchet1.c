#include "../libft/libft.h"

int main(void)
{
    char *line;
    char *num = malloc(3);
    int fd = open("input.txt", 0);
    int counter = 0;
    int result = 0;

  
    line = get_next_line(fd);
    while (line) {
    num[0] = num[1] = 0;
    while (line[counter] > '9' || line[counter] < '0')
        counter++;
    num[0] = line[counter];
    counter++;
    while (line[counter])
        counter++;
    while (line[counter] > '9' || line[counter] < '0')
        counter--;
    num[1] = line[counter];
    result = result + ft_atoi(num);
    line = get_next_line(fd);
    counter = 0;
    }
    ft_printf("%d\n", result);
    free(line);
    free(num);
    close(fd);
    return(0);
}