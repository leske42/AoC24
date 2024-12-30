#include "../libft/libft.h"

int main(void)
{
    int time;
    int goal_dist;
    int dist;
    int press = 0;
    int win_count1 = 0;
    int win_count2 = 0;
    int win_count3 = 0;
    int win_count4 = 0;

    goal_dist = 601;
    time = 60;
    while (press < 61)
    {
        dist = (time - press) * press;
        if (dist > goal_dist)
            win_count1++;
        press++;
    }
    press = 0;
    goal_dist = 1163;
    time = 80;
    while (press < 81)
    {
        dist = (time - press) * press;
        if (dist > goal_dist)
            win_count2++;
        press++;
    }
    press = 0;
    goal_dist = 1559;
    time = 86;
    while (press < 87)
    {
        dist = (time - press) * press;
        if (dist > goal_dist)
            win_count3++;
        press++;
    }
    press = 0;
    goal_dist = 1300;
    time = 76;
    while (press < 77)
    {
        dist = (time - press) * press;
        if (dist > goal_dist)
            win_count4++;
        press++;
    }
    ft_printf("RESULT: %d\n", win_count1 * win_count2 * win_count3 * win_count4);
}