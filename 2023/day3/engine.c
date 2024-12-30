#include "../libft/libft.h"

int main(void)
{
    char **arr = malloc(sizeof(char *) * 141);
    int fd = open("input.txt", 0);
    int counter = 0;
    int cur = 0;
    int result = 0;
    int flag = 0;
    arr[counter] = get_next_line(fd);
    while(arr[counter])
    {
        counter++;
        arr[counter] = get_next_line(fd);
    }
    counter = 0;
    while(arr[counter])
        counter++;
    
    //look for a number
    int y = 0;
    int x = 0;
    while (y < counter) {
    x = 0;
    while(arr[y][x]) {
    while((arr[y][x] < '0' || arr[y][x] > '9') && arr[y][x])
        x++;
    cur = ft_atoi(arr[y] + x);

    //look for symbols: /, +, -, %, *, #, &, @, $, =
    //33-38, 42-45, 47, 58-64, 91-95?, 123-126?
    while(arr[y][x] >= '0' && arr[y][x] <= '9' && arr[y][x])
    {
        if (x != 0)
        {
        if(arr[y][x - 1] == '/' || arr[y][x - 1] == '+' || arr[y][x - 1] == '-' || arr[y][x - 1] == '%'
            || arr[y][x - 1] == '*' || arr[y][x - 1] == '#' || arr[y][x - 1] == '&' || arr[y][x - 1] == '@'
                || arr[y][x - 1] == '$' || arr[y][x - 1] == '=' || arr[y][x - 1] == '|' || arr[y][x - 1] == '?')
                    flag = 1;
        }
        if(arr[y][x + 1] == '/' || arr[y][x + 1] == '+' || arr[y][x + 1] == '-' || arr[y][x + 1] == '%'
            || arr[y][x + 1] == '*' || arr[y][x + 1] == '#' || arr[y][x + 1] == '&' || arr[y][x + 1] == '@'
                || arr[y][x + 1] == '$' || arr[y][x + 1] == '=' || arr[y][x + 1] == '|' || arr[y][x + 1] == '?')
                    flag = 1;
        if (y != 0)
        {
        if(arr[y - 1][x] == '/' || arr[y - 1][x] == '+' || arr[y - 1][x] == '-' || arr[y - 1][x] == '%'
            || arr[y - 1][x] == '*' || arr[y - 1][x] == '#' || arr[y - 1][x] == '&' || arr[y - 1][x] == '@'
                || arr[y - 1][x] == '$' || arr[y - 1][x] == '=' || arr[y - 1][x] == '|' || arr[y - 1][x] == '?')
                    flag = 1;
        }
        if (arr[y + 1])
        {
        if(arr[y + 1][x] == '/' || arr[y + 1][x] == '+' || arr[y + 1][x] == '-' || arr[y + 1][x] == '%'
            || arr[y + 1][x] == '*' || arr[y + 1][x] == '#' || arr[y + 1][x] == '&' || arr[y + 1][x] == '@'
                || arr[y + 1][x] == '$' || arr[y + 1][x] == '=' || arr[y + 1][x] == '|' || arr[y + 1][x] == '?')
                    flag = 1;
        }
        if (arr[y + 1])
        {
        if(arr[y + 1][x + 1] == '/' || arr[y + 1][x + 1] == '+' || arr[y + 1][x + 1] == '-' || arr[y + 1][x + 1] == '%'
            || arr[y + 1][x + 1] == '*' || arr[y + 1][x + 1] == '#' || arr[y + 1][x + 1] == '&' || arr[y + 1][x + 1] == '@'
                || arr[y + 1][x + 1] == '$' || arr[y + 1][x + 1] == '=' || arr[y + 1][x + 1] == '|' || arr[y + 1][x + 1] == '?')
                    flag = 1;
        }
        if (arr[y + 1])
        {
        if(arr[y + 1][x - 1] == '/' || arr[y + 1][x - 1] == '+' || arr[y + 1][x - 1] == '-' || arr[y + 1][x - 1] == '%'
            || arr[y + 1][x - 1] == '*' || arr[y + 1][x - 1] == '#' || arr[y + 1][x - 1] == '&' || arr[y + 1][x - 1] == '@'
                || arr[y + 1][x - 1] == '$' || arr[y + 1][x - 1] == '=' || arr[y + 1][x - 1] == '|' || arr[y + 1][x - 1] == '?')
                    flag = 1;
        }
        if (y != 0)
        {
        if(arr[y - 1][x + 1] == '/' || arr[y - 1][x + 1] == '+' || arr[y - 1][x + 1] == '-' || arr[y - 1][x + 1] == '%'
            || arr[y - 1][x + 1] == '*' || arr[y - 1][x + 1] == '#' || arr[y - 1][x + 1] == '&' || arr[y - 1][x + 1] == '@'
                || arr[y - 1][x + 1] == '$' || arr[y - 1][x + 1] == '=' || arr[y - 1][x + 1] == '|' || arr[y - 1][x + 1] == '?')
                    flag = 1;
        }
        if (y != 0)
        {
        if(arr[y - 1][x - 1] == '/' || arr[y - 1][x - 1] == '+' || arr[y - 1][x - 1] == '-' || arr[y - 1][x - 1] == '%'
            || arr[y - 1][x - 1] == '*' || arr[y - 1][x - 1] == '#' || arr[y - 1][x - 1] == '&' || arr[y - 1][x - 1] == '@'
                || arr[y - 1][x - 1] == '$' || arr[y - 1][x - 1] == '=' || arr[y - 1][x - 1] == '|' || arr[y - 1][x - 1] == '?')
                    flag = 1;
        }
        x++;
    }
    if (flag)
        result = result + cur;
    flag = cur = 0;
    }
    y++;
    }
    ft_printf("%d\n", result);
}