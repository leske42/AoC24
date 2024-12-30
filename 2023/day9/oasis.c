#include "../libft/libft.h"

int array_sum(int *arr, int size)
{
    int counter = 0;
    int result = 0;
    while (counter < size)
    {
        result = result + arr[counter];
        counter++;
    }
    return (result);
}

void display_arr(int *arr, int size)
{
    int counter = 0;
    while (counter < size)
    {
        ft_printf("%d ", arr[counter]);
        counter++;
    }
    ft_printf("\n");
}

int zeroes(int *arr, int size)
{
    int counter = 0;
    while (counter < size)
    {
        if (arr[counter] != 0)
            return (0);
        counter++;
    }
    return (1);
}

int main(void)
{
    int fd = open("input.txt", 0);
    char *line = get_next_line(fd);
    int words;
    char **word_arr;
    int *arr[1000];
    int i = 0;
    int counter = 0;
    int result = 0;
    int cur_result = 0;
    while (line)
    {
        words = count_words(line, 32);
        word_arr = ft_split(line, 32);
        arr[i] = ft_calloc(sizeof(int), words);
        while (counter < words)
        {
            arr[i][counter] = atoi(word_arr[counter]);
            counter++;
        }
        counter = 0;
        //while (array_sum(arr[i], words) != 0) //This approach is wrong & leads to a one-off error. A SUM can also be zero if the previous sequence mirrors itself.
        while (!zeroes(arr[i], words))
        {
            arr[i + 1] = ft_calloc(sizeof(int), words - 1);
            while (counter + 1 < words)
            {
                arr[i + 1][counter] = arr[i][counter + 1] - arr[i][counter];
                counter++;
            }
            display_arr(arr[i], words);
            i++;
            words--;
            counter = 0;
        }
        while (i > -1)
        {
            cur_result = cur_result + arr[i][words - 1];
            words++;
            free(arr[i]);
            i--;
        }
        free(line);
        free(word_arr);
        counter = i = 0;
        result = result + cur_result;
        cur_result = 0;
        line = get_next_line(fd);
    }
    close(fd);
    ft_printf("the result is: %d\n", result);
}