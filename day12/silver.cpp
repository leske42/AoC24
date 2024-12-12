/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:55:34 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/12 20:51:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

typedef std::vector<char> Row;
std::vector<Row> map;

typedef std::pair<int, int> Coordinates;
std::vector<Coordinates> visited;
typedef std::map<int /*region ID*/, std::pair<int /*border size*/, std::vector<Coordinates> /*fields that belong here*/>> Areas;
Areas areas;

int xdim, ydim;
int res = 0;
int cur_id = 0;


enum Direction
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN
};

bool new_spot(Coordinates coord)
{
    Areas::iterator iter = areas.begin();
    while (iter != areas.end())
    {
        if (std::find((*iter).second.second.begin(), (*iter).second.second.end(), coord) != (*iter).second.second.end())
            return false;
        iter++;
    }
    return true;
}

bool out_of_bounds(int y, int x)
{
    return (y < 0 || y >= ydim || x < 0 || x >= xdim);
}

bool is_visited(int y, int x)
{
    return (std::find(visited.begin(), visited.end(),
        std::pair<int, int>(y, x)) != visited.end());
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
    if (out_of_bounds(y, x) || map[y][x] != old)
    {
        areas[cur_id].first++;
        return;
    }
    pathfinder(y, x);
}

void pathfinder(int y, int x)
{
    if (is_visited(y, x))
        return;
    else
        visited.push_back(std::pair<int, int>(y, x));
    move(UP, y, x, map[y][x]);
    move(DOWN, y, x, map[y][x]);
    move(LEFT, y, x, map[y][x]);
    move(RIGHT, y, x, map[y][x]);
}

void calc_area()
{
    for (int y = 0; y < ydim; y++)
    {
        for (int x = 0; x < xdim; x++)
        {
            if (new_spot(Coordinates(y, x)))
            {
                pathfinder(y, x);
                areas[cur_id].second = visited;
                visited.clear();
                cur_id++;
            }
        }
    }
}

void add_up_areas()
{
    for (const auto& pair : areas)
    {
        int id = pair.first;
        int borders = pair.second.first;
        int area = pair.second.second.size();
        res += borders * area;
        std::cout << "A region of " << id << " plants with price " << borders << " * " << area << " = " << borders * area << std::endl;
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
    calc_area();
    add_up_areas();
    std::cout << res << std::endl;
}