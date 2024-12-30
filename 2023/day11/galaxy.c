#include "../libft/libft.h"

//this main marks the empty rows (i manually copied them)
/*int main (void)
{
    char **arr = malloc(sizeof(char *) * 140);
    int counter = 0;
    int fd = open("input.txt", 0);
    while (counter < 140)
    {
        arr[counter] = get_next_line(fd);
        counter++;
    }
    counter = 0;
    int i = 0;
    while (counter < 140)
    {
        while (arr[counter][i] && arr[counter][i] != '#')
            i++;
        if (!arr[counter][i])
            ft_printf("found a guilty line at row: %d\n", counter + 1);
        i = 0;
        counter++;
    }
    return (0);
}*/

//this main marks the unoccupied columns
/*
int main (void)
{
    char **arr = malloc(sizeof(char *) * 151);
    int counter = 0;
    int fd = open("mod_input.txt", 0);
    char occupied_lines[142];
    while (counter < 151)
    {
        arr[counter] = get_next_line(fd);
        counter++;
    }
    counter = 0;
    ft_printf("Line length is: %d\n", ft_strlen(arr[counter]));
    int i = 0;
    while (i < 142)
    {
        occupied_lines[i] = 'n';
        i++;
    }
    occupied_lines[i] = '\0';
    i = 0;
    while (counter < 151 && i < 142)
    {
        while (arr[counter][i])
        {
            if (arr[counter][i] == '#')
                occupied_lines[i] = 'y';
            i++;
        }
        i = 0;
        counter++;
    }
    while (i < 142)
    {
        if (occupied_lines[i] == 'n')
            ft_printf("column %d is unoccupied!\n", i);
        i++;
    }
}
*/

//this main creates the big input txt
/*
int main (void)
{
    char **arr = malloc(sizeof(char *) * 151);
    int counter = 0;
    int fd = open("mod_input.txt", 0);
    char occupied_lines[142];
    while (counter < 151)
    {
        arr[counter] = get_next_line(fd);
        counter++;
    }
    counter = 0;
    ft_printf("Line length is: %d\n", ft_strlen(arr[counter]));
    int i = 0;
    while (i < 142)
    {
        occupied_lines[i] = 'n';
        i++;
    }
    occupied_lines[i] = '\0';
    i = 0;
    while (counter < 151 && i < 142)
    {
        while (arr[counter][i])
        {
            if (arr[counter][i] == '#')
                occupied_lines[i] = 'y';
            i++;
        }
        i = 0;
        counter++;
    }
    counter = i = 0;
    int fd2 = open("big_input.txt", O_RDWR);
    while (counter < 151 && i < 142)
    {
        while (arr[counter][i])
        {
            write(fd2, &arr[counter][i], 1);
            if (occupied_lines[i] == 'n' && arr[counter][i] != '\n')
                write(fd2, ".", 1);
            i++;
        }
        i = 0;
        counter++;
    }
}*/

typedef struct s_galaxy {
    int index;
    int x;
    int y;
    struct s_galaxy *next;
} t_galaxy;

t_galaxy *create_node(int ind, int col, int row)
{
    t_galaxy *new_node = malloc(sizeof(t_galaxy));
    new_node->index = ind;
    new_node->x = col;
    new_node->y = row;
    new_node->next = NULL;
    return (new_node);
}

int absolute(int nb)
{
    if (nb < 0)
        return (nb * -1);
    else
        return (nb);
}

int main (void)
{
    char **arr = malloc(sizeof(char *) * 151);
    int counter = 0;
    int fd = open("big_input.txt", 0);
    t_galaxy *head = NULL;
    t_galaxy *proxy = NULL;
    while (counter < 151)
    {
        arr[counter] = get_next_line(fd);
        counter++;
    }
    counter = 0;
    int i = 0;
    int j = 1;
    while (counter < 151 && i < 142)
    {
        while (arr[counter][i])
        {
            if (arr[counter][i] == '#')
            {
                if (!head)
                    head = create_node(j, i, counter);
                else
                {
                    proxy = head;
                    while (proxy->next)
                        proxy = proxy->next;
                    proxy->next = create_node(j, i, counter);
                }
                j++;
            }
            i++;
        }
        i = 0;
        counter++;
    }

    //I'm turning my linked list into a circle
    proxy = head;
    while (proxy->next)
        proxy = proxy->next;
    proxy->next = head;
    int safety = head->index;
    ft_printf("HEAD INDEX: %d, LAST INDEX: %d\n", safety, proxy->index);
    long int result = 0;
    long int cur_result = 0;
    proxy = head->next;
    while (head->next->index != safety)
    {
        while (proxy != head)
        {
            cur_result = cur_result + absolute(head->x - proxy->x) + absolute(head->y - proxy->y);
            proxy = proxy->next;
        }
        result = result + cur_result;
        cur_result = 0;
        head = head->next;
        proxy = head->next;
    }
    while (proxy != head)
    {
        cur_result = cur_result + absolute(head->x - proxy->x) + absolute(head->y - proxy->y);
        proxy = proxy->next;
    }
    result = result + cur_result;
    cur_result = 0;
    //now i have to divide by two since i counted each relation twice
    ft_printf("total result is: %l\n", result / 2);
}