#include "../libft/libft.h"

long int tiny(long int arr[], int size) {
    
    long int smallest = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main(void)
{
    long int *seeds = ft_calloc(20, 8);
    long int *soils = ft_calloc(20, 8);
    long int *fertil = ft_calloc(20, 8);
    long int *water = ft_calloc(20, 8);
    long int *light = ft_calloc(20, 8);
    long int *temp = ft_calloc(20, 8);
    long int *humid = ft_calloc(20, 8);
    long int *locations = ft_calloc(20, 8);
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
    //put seed values into seed array
    while (line[counter])
    {
        while ((line[counter] < '0' || line[counter] > '9') && line[counter])
            counter++;
        seeds[i] = ft_atoi(line + counter);
        i++;
        while ((line[counter] >= '0' && line[counter] <= '9') && line[counter])
            counter++;
    }
    counter = i = 0;

    //first round: soil
    while (i < 20)
    {
        fd2 = open("1soil.txt", 0);
        line = get_next_line(fd2);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd2);
            counter = 0;
        }
        if (soils[i] == 0)
            soils[i] = seeds[i];
        i++;
        counter = 0;
        close(fd2);
        fd2 = 0;
    }
    i = 0;
    counter = i = 0;

    //second round: fertilizer
    while (i < 20)
    {
        fd3 = open("2fertil.txt", 0);
        line = get_next_line(fd3);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd3);
            counter = 0;
        }
        if (fertil[i] == 0)
            fertil[i] = soils[i];
        i++;
        counter = 0;
        close(fd3);
        fd3 = 0;
    }
    counter = i = 0;

    //third round: water
    while (i < 20)
    {
        fd4 = open("3water.txt", 0);
        line = get_next_line(fd4);
        while (line)
        {
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
            if (i == 2)
                ft_printf("ID: %d FERTIL: %l MIN: %l MAX: %l START: %l LINE: %s\n", i, fertil[i], min, max, goal, line);
            if (fertil[i] >= min && fertil[i] <= max)
            {
                water[i] = goal + (fertil[i] - min);
                line = NULL;
            }
            else
                line = get_next_line(fd4);
            counter = 0;
        }
        if (water[i] == 0)
            water[i] = fertil[i];
        i++;
        counter = 0;
        close(fd4);
        fd4 = 0;
    }
    counter = i = 0;

    //fourth round: light
    while (i < 20)
    {
        fd5 = open("4light.txt", 0);
        line = get_next_line(fd5);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd5);
            counter = 0;
        }
        if (light[i] == 0)
            light[i] = water[i];
        i++;
        counter = 0;
        close(fd5);
        fd5 = 0;
    }
    counter = i = 0;

    //fifth round: temp
    while (i < 20)
    {
        fd6 = open("5temp.txt", 0);
        line = get_next_line(fd6);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd6);
            counter = 0;
        }
        if (temp[i] == 0)
            temp[i] = light[i];
        i++;
        counter = 0;
        close(fd6);
        fd6 = 0;
    }
    counter = i = 0;

    //sixth round: humidity
    while (i < 20)
    {
        fd7 = open("6humidity.txt", 0);
        line = get_next_line(fd7);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd7);
            counter = 0;
        }
        if (humid[i] == 0)
            humid[i] = temp[i];
        i++;
        counter = 0;
        close(fd7);
        fd7 = 0;
    }
    counter = i = 0;

    //seventh round: location
    while (i < 20)
    {
        fd8 = open("7location.txt", 0);
        line = get_next_line(fd8);
        while (line)
        {
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
                line = NULL;
            }
            else
                line = get_next_line(fd8);
            counter = 0;
        }
        if (locations[i] == 0)
            locations[i] = humid[i];
        i++;
        counter = 0;
        close(fd8);
        fd8 = 0;
    }
    counter = i = 0;
    while (i < 20)
    {
        ft_printf("INDEX: %d SEED: %l SOIL: %l FERTIL: %l WATER: %l LIGHT: %l TEMP: %l HUMID: %l LOC: %l\n", i, seeds[i], soils[i], fertil[i], water[i], light[i], temp[i], humid[i], locations[i]);
        i++;
    }
    long int smallest = tiny(locations, 20);
    ft_printf("CLOSEST LOC IS: %l\n", smallest);
}