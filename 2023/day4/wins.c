#include "../libft/libft.h"

int main(void)
{
    int fd = open("input.txt", 0);
    char *line;
    int counter = 0;
    line = get_next_line(fd);
    int goal_arr[10];
    int have_arr[25];
    int i = 0;
    int cur = 0;
    int result = 0;
    int card = 0;
    int cards[211];
    int cardproxy = 0;
    int curproxy = 0;
    while (i < 211)
    {
        cards[i] = 1;
        i++;
    }
    i = 0;
    while (line)
    {
        while (line[counter] != ':' && line[counter])
            counter++;
        while (line[counter] != '|' && line[counter])
        {
            counter++;
            while(line[counter] == 32)
                counter++;
            if (line[counter] == '|')
                break ;
            goal_arr[i] = ft_atoi(line + counter);
            i++;
            while((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
        }
        i = 0;
        while (line[counter])
        {
            while((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            if (!line[counter])
                break ;
            have_arr[i] = ft_atoi(line + counter);
            i++;
            while((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
        }
        counter = 0;
        i = 0;
        while (counter < 25)
        {
            i = 0;
            while (i < 10)
            {
                if (have_arr[counter] == goal_arr[i])
                    cur++;
                i++;
            }
            counter++;
        }
        counter = card + 1;
        cardproxy = cards[card];
        while (cardproxy)
        {
            curproxy = cur;
            counter = card + 1;
            while (curproxy && counter < 211)
            {
                cards[counter]++;
                curproxy--;
                counter++;
            }
            cardproxy--;
        }
        cur = counter = i = 0;
        line = get_next_line(fd);
        card++;
    }
    i = 0;
    while (i < 211)
    {
        result = result + cards[i];
        i++;
    }
    ft_printf("RESULT: %d\n", result);
}