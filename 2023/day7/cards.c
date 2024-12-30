#include "../libft/libft.h"

# define VALS_NUM 1000

int value(char c)
{
    if (c >= '2' && c <= '9')
        return (c - 48);
    else if (c == 'T')
        return (10);
    else if (c == 'J')
        return (11);
    else if (c == 'Q')
        return (12);
    else if (c == 'K')
        return (13);
    else if (c == 'A')
        return (14);
    else
        return (0);
}

char ***fill_arr(int fd)
{
    char *line;
    char ***output = malloc(sizeof(char **) * VALS_NUM);
    line = get_next_line(fd);
    int counter = 0;
    while (line)
    {
        output[counter] = ft_split(line, ' ');
        free(line);
        line = get_next_line(fd);
        counter++;
    }
    close(fd);
    return (output);
}

int in_it(char *s, char c)
{
    int counter = 0;
    int times = 0;
    while (s[counter])
    {
        if (s[counter] == c)
            times++;
        counter++;
    }
    return (times);
}

char *hand_type(char *hand)
{
    int counter = 0;
    int flag = 0;
    int flag2 = 0;
    int first_matches = 0;
    int second_matches = 0;
    int third_matches = 0;
    if (in_it(hand, hand[0]) == 5)
        return ("FIVE");
    else if (in_it(hand, hand[0]) == 4)
        return ("FOUR");
    first_matches = in_it(hand, hand[0]);
    while (hand[counter] == hand[0])
        counter++;
    if (in_it(hand, hand[counter]) == 4)
        return ("FOUR");
    else if (in_it(hand, hand[counter]) == 2 && first_matches == 3)
        return ("FULL");
    else if (in_it(hand, hand[counter]) == 3 && first_matches == 2)
        return ("FULL");
    else if (first_matches == 3 || in_it(hand, hand[counter]) == 3)
        return ("THREE");
    second_matches = in_it(hand, hand[counter]); //either 0, 1 or 2
    flag = hand[counter];
    while (hand[counter] == flag || hand[counter] == hand[0])
        counter++;
    if (in_it(hand, hand[counter]) == 3)
        return ("THREE");
    else if (in_it(hand, hand[counter]) + first_matches + second_matches == 5)
        return("2PAIRS");
    third_matches = in_it(hand, hand[counter]);
    flag2 = hand[counter];
    while (hand[counter] == flag || hand[counter] == flag2 || hand[counter] == hand[0])
        counter++;
    if (in_it(hand, hand[counter]) + first_matches + second_matches + third_matches > 4)
        return ("1PAIR");
    else
        return("HIGH");
}

int value_calc(char *hand, char c)
{
    //HIGH values range from 2-14
    //1PAIR values range from 20-140
    //2PAIR values range from 200-1400
    //THREE values range from 2000 - 14.000
    //FULL values range from 20.000 - 140.000
    //FOUR values range from 200.000 - 1.400.000
    //FIVE values range from 2.000.000 - 14.000.000
    int base = 0;
    if (ft_strcmp(hand_type(hand), "FIVE") == 0)
        base = 1000000;
    else if (ft_strcmp(hand_type(hand), "FOUR") == 0)
        base = 100000;
    else if (ft_strcmp(hand_type(hand), "FULL") == 0)
        base = 10000;
    else if (ft_strcmp(hand_type(hand), "THREE") == 0)
        base = 1000;
    else if (ft_strcmp(hand_type(hand), "2PAIRS") == 0)
        base = 100;
    else if (ft_strcmp(hand_type(hand), "1PAIR") == 0)
        base = 10;
    else if (ft_strcmp(hand_type(hand), "HIGH") == 0)
        base = 1;
    return (value(c) * base);

}

int main(void)
{
    int fd = open("input.txt", 0);
    char ***arr = fill_arr(fd);
    int *ranks = ft_calloc(sizeof(int), VALS_NUM);
    int current = 1;
    int mark = 0;
    int letter = 0;
    int rank = 1;
    unsigned long int result = 0;
    //Part to assign ranks to each hand
    while (current < VALS_NUM && rank < VALS_NUM)
    {
        while (ranks[mark] != 0 || current == mark)
            mark++;
        while (letter < 5)
        {
            if (value_calc(arr[current][0], arr[current][0][letter]) < value_calc(arr[mark][0], arr[mark][0][letter])
                && ranks[current] == 0)
            {
                mark = current;
                break ;
            }
            else if (value_calc(arr[current][0], arr[current][0][letter]) == value_calc(arr[mark][0], arr[mark][0][letter]))
                letter++;
            else
                break ;
        }
        letter = 0;
        current++;
        if (current == VALS_NUM)
        {
            ranks[mark] = rank;
            ft_printf("NEXT RANK IS RANK: %d BELONGS TO: %s\n", rank, arr[mark][0]);
            rank++;
            current = mark = 0;
        }
    }
    //Part to calculate the bet results
    current = 0;
    while (current < VALS_NUM)
    {
        if (ranks[current] == 0)
            ranks[current] = VALS_NUM;
        result = result + (ranks[current] * ft_atoi(arr[current][1]));
        current++;
    }
    ft_printf("THE RESULT IS: %zu\n", result);
    return (0);
}
