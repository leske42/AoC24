#include "../libft/libft.h"

int main(void)
{
    char **arr = malloc(sizeof(char *) * 141);
    int fd = open("input.txt", 0);
    int counter = 0;
    int cur = 1;
    int result = 0;
    int flag = 0;
    int z = 0;
    int i = 0;
    int buf[8];
    arr[counter] = get_next_line(fd);
    while(arr[counter])
    {
        counter++;
        arr[counter] = get_next_line(fd);
    }
    counter = 0;
    while(arr[counter])
    {
        counter++;
    }
    int y = 0;
    int x = 0;
    while(x < 8)
    {
        buf[x] = 0;
        x++;
    }
    while (y < counter) {
    x = 0;
    while(arr[y][x])
    {
        while(arr[y][x] != '*' && arr[y][x])
            x++;
        if (!arr[y][x])
            break ;
        if (x != 0)
        {
            if(arr[y][x - 1] >= '0' && arr[y][x - 1] <= '9')
            {
                flag++;
                z = x - 1;
                while (arr[y][z] >= '0' && arr[y][z] <= '9')
                    z--;
                z++;
                cur = cur * ft_atoi(arr[y] + z);
                buf[0] = ft_atoi(arr[y] + z);
                ft_printf("LEFT NUM: %d\n", cur);
            }
        }
        if (arr[y][x + 1] >= '0' && arr[y][x + 1] <= '9')
        {
            z = x + 1;
            buf[1] = ft_atoi(arr[y] + z);
            if (buf[1] != buf[0])
            {
                flag++;
                cur = cur * ft_atoi(arr[y] + z);
            }
            ft_printf("RIGHT NUM: %d\n", cur);
        }
        if (y != 0)
        {
            if (arr[y - 1][x] >= '0' && arr[y - 1][x] <= '9')
            {
                z = x;
                while (arr[y - 1][z] >= '0' && arr[y - 1][z] <= '9')
                    z--;
                z++;
                buf[2] = ft_atoi(arr[y - 1] + z);
                if (buf[2] != buf[0] && buf[2] != buf[1])
                {
                    cur = cur * ft_atoi(arr[y - 1] + z);
                    flag++;
                }
                ft_printf("UP NUM: %d\n", cur);
            }
        }
        if (arr[y + 1])
        {
            if(arr[y + 1][x] >= '0' && arr[y + 1][x] <= '9')
            {
                z = x;
                while (arr[y + 1][z] >= '0' && arr[y + 1][z] <= '9')
                    z--;
                z++;
                buf[3] = ft_atoi(arr[y + 1] + z);
                if (buf[3] != buf[0] && buf[3] != buf[1] && buf[3] != buf[2])
                {
                    cur = cur * ft_atoi(arr[y + 1] + z);
                    flag++;
                }
                ft_printf("DOWN NUM: %d\n", cur);
            }
        }
        if (arr[y + 1])
        {
            if(arr[y + 1][x + 1] >= '0' && arr[y + 1][x + 1] <= '9')
            {
                z = x + 1;
                while (arr[y + 1][z] >= '0' && arr[y + 1][z] <= '9')
                    z--;
                z++;
                buf[4] = ft_atoi(arr[y + 1] + z);
                if (buf[4] != buf[0] && buf[4] != buf[1] && buf[4] != buf[2] && buf[4] != buf[3])
                {
                    cur = cur * ft_atoi(arr[y + 1] + z);
                    flag++;
                }
                ft_printf("DOWNRIGHT NUM: %d\n", cur);
            }
        }
        if (arr[y + 1])
        {
            if(arr[y + 1][x - 1] >= '0' && arr[y + 1][x - 1] <= '9')
            {
                z = x - 1;
                while (arr[y + 1][z] >= '0' && arr[y + 1][z] <= '9')
                    z--;
                z++;
                buf[5] = ft_atoi(arr[y + 1] + z);
                if (buf[5] != buf[0] && buf[5] != buf[1] && buf[5] != buf[2] && buf[5] != buf[3]
                    && buf[5] != buf[4])
                    {
                        cur = cur * ft_atoi(arr[y + 1] + z);
                        flag++;
                    }
                ft_printf("DOWNLEFT NUM: %d\n", cur);
            }
        }
        if (y != 0)
        {
            if(arr[y - 1][x + 1] >= '0' && arr[y - 1][x + 1] <= '9')
            {
                z = x + 1;
                while (arr[y - 1][z] >= '0' && arr[y - 1][z] <= '9')
                    z--;
                z++;
                buf[6] = ft_atoi(arr[y - 1] + z);
                if (buf[6] != buf[0] && buf[6] != buf[1] && buf[6] != buf[2] && buf[6] != buf[3]
                    && buf[6] != buf[4] && buf[6] != buf[5])
                    {
                        cur = cur * ft_atoi(arr[y - 1] + z);
                        flag++;
                    }
                ft_printf("UPRIGHT NUM: %d\n", cur);
            }
        }
        if (y != 0)
        {
            if(arr[y - 1][x - 1] >= '0' && arr[y - 1][x - 1] <= '9')
            {
                z = x - 1;
                while (arr[y - 1][z] >= '0' && arr[y - 1][z] <= '9')
                    z--;
                z++;
                buf[7] = ft_atoi(arr[y - 1] + z);
                if (buf[7] != buf[0] && buf[7] != buf[1] && buf[7] != buf[2] && buf[7] != buf[3]
                    && buf[7] != buf[4] && buf[7] != buf[5] && buf[7] != buf[6])
                    {
                        cur = cur * ft_atoi(arr[y - 1] + z);
                        flag++;
                    }
                ft_printf("UPLEFT NUM: %d\n", cur);
            }
        }
        if (flag == 2)
            result = result + cur;
        ft_printf("CUR: %d\n", cur);
        ft_printf("FLAG: %d\n", flag);
        ft_printf("RES: %d\n", result);
        while(i < 8)
        {
            buf[i] = 0;
            i++;
        }
        i = 0;
        flag = 0;
        cur = 1;
        x++;
    }
    y++;
    }
    ft_printf("RESULT: %d\n", result);
}