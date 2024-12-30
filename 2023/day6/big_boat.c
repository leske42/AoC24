#include "../libft/libft.h"

int main(void)
{
    unsigned long long int time;
    unsigned long long int goal_dist;
    unsigned long long int dist;
    unsigned long long int press = 0;
    int win_count1 = 0;

    goal_dist = 601116315591300;
    time = 60808676;
    while (press < 60808677)
    {
        dist = (time - press) * press;
        if (dist > goal_dist)
            win_count1++;
        press++;
    }
    ft_printf("RESULT: %u\n", win_count1);
}