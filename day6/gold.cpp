/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:46:16 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/08 22:02:12 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum Direction
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

struct s_player
{
    int x, y;
    Direction dir;
};

s_player player;

std::vector<std::vector<char> > map;
std::vector<std::vector<char> > map2;

int res = 0;
bool brk = false;
int og_y, og_x;
Direction og_dir;
int xdim, ydim;

Direction rotate(Direction dir)
{
    return (Direction)((dir + 1) % 4);
}

bool out_of_bounds()
{
    int new_x = player.x, new_y = player.y;
    switch (player.dir)
    {
        case UP:
            new_y--;
            break;
        case RIGHT:
            new_x++;
            break;
        case DOWN:
            new_y++;
            break;
        case LEFT:
            new_x--;
            break;
    }
    return (new_y < 0 || new_y >= map2.size() || new_x < 0 || new_x >= map2[0].size());
}

bool can_move()
{
    int new_x = player.x, new_y = player.y;
    switch (player.dir)
    {
        case UP:
            new_y--;
            break;
        case RIGHT:
            new_x++;
            break;
        case DOWN:
            new_y++;
            break;
        case LEFT:
            new_x--;
            break;
    }
    return new_y >= 0 && new_y < map.size() &&
           new_x >= 0 && new_x < map[0].size() &&
           (map2[new_y][new_x] != '#' && map2[new_y][new_x] != '0');
}

void move()
{
    if (map2[player.y][player.x] == 'X' + player.dir)
    {
        res++;
        brk = true;
    }
    map2[player.y][player.x] = 'X' + player.dir;
    switch (player.dir)
    {
        case UP:
            player.y--;
            break;
        case RIGHT:
            player.x++;
            break;
        case DOWN:
            player.y++;
            break;
        case LEFT:
            player.x--;
            break;
    }
}

void reset_data()
{
    map2 = map;
    player.x = og_x;
    player.y = og_y;
    player.dir = og_dir;
}

void run_simulation()
{
    while (player.x >= 0 && player.x < map2[0].size() && player.y >= 0 && player.y < map2.size())
    {
        if (out_of_bounds())
            break;
        else if (can_move())
            move();
        else
            player.dir = rotate(player.dir);
        if (brk)
        {
            brk = false;
            return;
        }
    }
}

void parse_map()
{
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row;
        int i = 0;
        while (i < line.size())
        {
            char c = line[i];
            row.push_back(c);
            if (c == '^' || c == '>' || c == 'v' || c == '<')
            {
                player.x = og_x = i;
                player.y = og_y = map.size();
                player.dir = og_dir = (c == '^') ? UP : (c == '>') ? RIGHT : (c == 'v') ? DOWN : LEFT;
            }
            i++;
        }
        map.push_back(row);
    }
    ydim = map.size();
    xdim = map[0].size();
}

/* NOTE
This solution has a one-off error for both my example
txt and my inputfile. I thought i messed up some calc
which i could not find so i just simply added one to
the solution. But recently i discovered that strangely
it has no error for Lukas input */
int main()
{
    parse_map();
    int x = 0;
    int y = 0;
    while (y < ydim)
    {
        while (x < xdim)
        {
            if (x == player.x && y == player.y)
            {
                x++;
                continue;
            }
            reset_data();
            map2[y][x] = '0';
            run_simulation();
            x++;
        }
        x = 0;
        y++;
    }
    std::cout << res << std::endl;
}