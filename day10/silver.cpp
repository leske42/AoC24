/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:50:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/10 12:12:15 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>

typedef std::vector<char> Row;
std::vector<Row> map;
std::vector<std::pair<int, int>> visited;
int xdim, ydim;
int res = 0;

enum Direction
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN
};

bool out_of_bounds(int y, int x)
{
    return (y < 0 || y >= ydim || x < 0 || x >= xdim);
}

bool not_visited(int y, int x)
{
    return (std::find(visited.begin(), visited.end(),
        std::pair<int, int>(y, x)) == visited.end());
}

void pathfinder(int y, int x);

void move(Direction dir, int y, int x, char old)
{
    switch(dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    if (out_of_bounds(y, x))
        return;
    else if (map[y][x] != old + 1)
        return;
    else if (map[y][x] == '9' && not_visited(y, x))
    {
        visited.push_back(std::pair<int, int>(y, x));
        res++;
    }
    else
        pathfinder(y, x);
}

void pathfinder(int y, int x)
{
    move(UP, y, x, map[y][x]);
    move(DOWN, y, x, map[y][x]);
    move(LEFT, y, x, map[y][x]);
    move(RIGHT, y, x, map[y][x]);
}

void find_trailheads()
{
    for (int y = 0; y < ydim; y++)
    {
        for (int x = 0; x < xdim; x++)
        {
            if (map[y][x] == '0')
            {
                pathfinder(y, x);
                visited.clear();
            }
        }
    }
}

void parse_file()
{
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
        map.push_back(Row(line.begin(), line.end()));
    xdim = map[0].size();
    ydim = map.size();
}


int main(void)
{
    parse_file();
    find_trailheads();
    std::cout << res << std::endl;
}