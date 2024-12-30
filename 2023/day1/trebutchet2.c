#include "../libft/libft.h"

int main(void)
{
    char *line;
    char *num = malloc(3);
    int fd = open("input.txt", 0);
    int counter = 0;
    int result = 0;
    char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int i;

    line = get_next_line(fd);
    while (line)
    {
        while (!num[0])
        {
            if (line[counter] <= '9' && line[counter] >= '0')
                num[0] = line[counter];
            else
            {
                i = 0;
                while(i < 10)
                {
                    if(strncmp(line + counter, numbers[i], ft_strlen(numbers[i])) == 0)
                    {
                        num[0] = '0' + i;
                        break ;
                    }
                    else
                        i++;
                }
            }
            counter++;
        }
        while (line[counter])
            counter++;
        while (!num[1])
        {
            if (line[counter] <= '9' && line[counter] >= '0')
                num[1] = line[counter];
            else
            {
                i = 0;
                while(i < 10)
                {
                    if(strncmp(line + counter, numbers[i], ft_strlen(numbers[i])) == 0)
                    {
                        num[1] = '0' + i;
                        break ;
                    }
                    else
                        i++;
                }
            }
            counter--;
        }
        num[2] = '\0';
        result = result + ft_atoi(num);
        line = get_next_line(fd);
        counter = 0;
        num[0] = num[1] = 0;
    }
    ft_printf("%d\n", result);
    free(line);
    free(num);
    close(fd);
    return(0);
}