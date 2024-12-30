#include "../libft/libft.h"

int main(void)
{
    int result = 0;
    int counter = 0;
    int index = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    int cur = 0;
    char *line;
    int fd = open("input.txt", 0);
    line = get_next_line(fd);
    while(line)
    {
        while (line[counter] > '9' || line[counter] < '0')
            counter++;
        index = ft_atoi(line + counter);
        while (line[counter] != ':')
            counter++;
        while(line[counter])
        {
            while ((line[counter] > '9' || line[counter] < '0') && line[counter])
                counter++;
            cur = ft_atoi(line + counter);
            while ((line[counter] > 'z' || line[counter] < 'a') && line[counter])
                counter++;
            if (line[counter] == 'r')
            {
                if (red == 0)
                    red = cur;
                else if (cur > red)
                    red = cur;
            }
            else if (line[counter] == 'g')
            {
                if (green == 0)
                    green = cur;
                else if (cur > green)
                    green = cur;
            }
            else if (line[counter] == 'b')
            {
                if (blue == 0)
                    blue = cur;
                else if (cur > blue)
                    blue = cur;
            }
            cur = 0;
        }
        if (red <= 12 && green <= 13 && blue <= 14)
            result = result + index;
        red = green = blue = index = 0;
        line = get_next_line(fd);
        counter = 0;
    }
   ft_printf("%d\n", result);
   return(0);
}