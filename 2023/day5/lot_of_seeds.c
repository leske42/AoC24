#include "../libft/libft.h"

long int tiny(long int arr[], int size) {
    
    long int smallest = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < smallest && arr[i] != 0) {
            smallest = arr[i];
        }
    }
    return smallest;
}

long int seeder(long int *seeds)
{
    //long int *seeds = ft_calloc(1000, 8);
    long int *soils = ft_calloc(10000, 8);
    long int *fertil = ft_calloc(10000, 8);
    long int *water = ft_calloc(10000, 8);
    long int *light = ft_calloc(10000, 8);
    long int *temp = ft_calloc(10000, 8);
    long int *humid = ft_calloc(10000, 8);
    long int *locations = ft_calloc(10000, 8);
    long int min = 0;
    long int goal = 0;
    long int max = 0;
    int counter = 0;
    int i = 0;
    int fd = open("input.txt", 0);
    int fd2 = 0;
    int fd3 = 0;
    int fd4 = 0;
    int fd5 = 0;
    int fd6 = 0;
    int fd7 = 0;
    int fd8 = 0;
    char *line = get_next_line(fd);
    static char **one = NULL;
    static char **two = NULL;
    static char **three = NULL;
    static char **four = NULL;
    static char **five = NULL;
    static char **six = NULL;
    static char **seven = NULL;

    if (!one)
    {
        fd2 = open("1soil.txt", 0);
        one = malloc(sizeof(char *) * 18);
        while (i < 17)
        {
            one[i] = get_next_line(fd2);
            i++;
        }
        one[i] = NULL;
        i = 0;
        close(fd2);
    }
    if (!two)
    {
        fd3 = open("2fertil.txt", 0);
        two = malloc(sizeof(char *) * 15);
        while (i < 14)
        {
            two[i] = get_next_line(fd3);
            i++;
        }
        two[i] = NULL;
        i = 0;
        close(fd3);
    }
    if (!three)
    {
        fd4 = open("3water.txt", 0);
        three = malloc(sizeof(char *) * 24);
        while (i < 23)
        {
            three[i] = get_next_line(fd4);
            i++;
        }
        three[i] = NULL;
        i = 0;
        close(fd4);
    }
    if (!four)
    {
        fd5 = open("4light.txt", 0);
        four = malloc(sizeof(char *) * 48);
        while (i < 47)
        {
            four[i] = get_next_line(fd5);
            i++;
        }
        four[i] = NULL;
        i = 0;
        close(fd5);
    }
    if (!five)
    {
        fd6 = open("5temp.txt", 0);
        five = malloc(sizeof(char *) * 28);
        while (i < 27)
        {
            five[i] = get_next_line(fd6);
            i++;
        }
        five[i] = NULL;
        i = 0;
        close(fd6);
    }
    if (!six)
    {
        fd7 = open("6humidity.txt", 0);
        six = malloc(sizeof(char *) * 24);
        while (i < 23)
        {
            six[i] = get_next_line(fd7);
            i++;
        }
        six[i] = NULL;
        i = 0;
        close(fd7);
    }
    if (!seven)
    {
        fd8 = open("7location.txt", 0);
        seven = malloc(sizeof(char *) * 49);
        while (i < 48)
        {
            seven[i] = get_next_line(fd8);
            i++;
        }
        seven[i] = NULL;
        i = 0;
        close(fd8);
    }
    int j = 0;
    counter = i = 0;

    //first round: soil
    while (i < 10000)
    {
        while (one[j])
        {
            line = one[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (seeds[i] >= min && seeds[i] <= max)
            {
                soils[i] = goal + (seeds[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (soils[i] == 0)
            soils[i] = seeds[i];
        i++;
        counter = 0;
    }
    i = 0;
    counter = i = j = 0;

    //second round: fertilizer
    while (i < 10000)
    {
        while (two[j])
        {
            line = two[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (soils[i] >= min && soils[i] <= max)
            {
                fertil[i] = goal + (soils[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (fertil[i] == 0)
            fertil[i] = soils[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    //third round: water
    while (i < 10000)
    {
        while (three[j])
        {
            line = three[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (fertil[i] >= min && fertil[i] <= max)
            {
                water[i] = goal + (fertil[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (water[i] == 0)
            water[i] = fertil[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    //fourth round: light
    while (i < 10000)
    {
        while (four[j])
        {
            line = four[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (water[i] >= min && water[i] <= max)
            {
                light[i] = goal + (water[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (light[i] == 0)
            light[i] = water[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    //fifth round: temp
    while (i < 10000)
    {
        while (five[j])
        {
            line = five[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (light[i] >= min && light[i] <= max)
            {
                temp[i] = goal + (light[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (temp[i] == 0)
            temp[i] = light[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    //sixth round: humidity
    while (i < 10000)
    {
        while (six[j])
        {
            line = six[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (temp[i] >= min && temp[i] <= max)
            {
                humid[i] = goal + (temp[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (humid[i] == 0)
            humid[i] = temp[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    //seventh round: location
    while (i < 10000)
    {
        while (seven[j])
        {
            line = seven[j];
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            goal = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            min = ft_atoi(line + counter);
            while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
                counter++;
            while ((line[counter] < '0' || line[counter] > '9') && line[counter])
                counter++;
            max = min + ft_atoi(line + counter);

            //check if our target seed fits into min-max range
            if (humid[i] >= min && humid[i] <= max)
            {
                locations[i] = goal + (humid[i] - min);
                break ;
            }
            else
                j++;
            counter = 0;
        }
        if (locations[i] == 0)
            locations[i] = humid[i];
        i++;
        counter = 0;
    }
    counter = i = j = 0;

    long int smallest = tiny(locations, 10000);
    free(soils);
    free(fertil);
    free(water);
    free(light);
    free(temp);
    free(humid);
    free(locations);
    return (smallest);
}

int main(void)
{
    long int *result_arr = ft_calloc(10000, 8);
    long int *seeds = ft_calloc(10000, 8);
    int fd = open("input.txt", 0);
    char *line = get_next_line(fd);
    long int *nums = ft_calloc(20, 8);
    int i = 0;
    int counter = 0;
    long int max = 0;
    long int proxy = 0;
    int j = 0;

    //put seed values into num array
    while (line[counter])
    {
        while ((line[counter] < '0' || line[counter] > '9') && line[counter])
            counter++;
        nums[i] = ft_atoi(line + counter);
        i++;
        while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
            counter++;
    }
    counter = 0;
    i = 0;
    while (i < 19)
    {
        ft_printf("CURRENT I VALUE: %d\n", i);
        max = nums[i] + nums[i + 1];
        proxy = nums[i];
        while (proxy <= max)
        {
            seeds[counter] = proxy;
            counter++;
            if (counter == 10000 || proxy == max)
            {
                result_arr[j] = seeder(seeds);
                j++;
                free(seeds);
                seeds = ft_calloc(10000, 8);
                counter = 0;
            }
            proxy++;
        }
        i = i + 2;
        counter = 0;
    }
    long int smallest = tiny(result_arr, 10000);
    ft_printf("RESULT 0: %l\n", result_arr[0]);
    ft_printf("RESULT 1: %l\n", result_arr[1]);
    ft_printf("CLOSEST LOC IS: %l\n", smallest);
}