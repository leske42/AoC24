/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:42:26 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/16 22:54:16 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <sys/cdefs.h>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <set>

typedef std::vector<std::vector<char>> Grid;
Grid grid;
int xdim, ydim;
int og_x, og_y;

enum Direction
{
    LIMBO = -1,
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

struct Player
{
    int x = 0;
    int y = 0;
    Direction dir = RIGHT;
};
Player player;

typedef std::vector<std::pair<int, int>> Coordvec;
Coordvec sol;
size_t res = 2147483647;

typedef std::pair<std::pair<size_t /*cost of route*/, Coordvec>, Player> Route;
Route old_route;
typedef std::multimap<std::pair<size_t /*cost of route*/, Coordvec>, Player> Routes;
Routes routes;

typedef std::map<size_t/*hash*/, size_t/*cost*/> Visited;
Visited visited;

size_t hash_route(Route& to_hash)
{
    return (to_hash.second.x << 16 | to_hash.second.y << 8 | to_hash.second.dir);
}

void rotate_right()
{
    Route new_route = old_route;
    new_route.second.dir = (Direction)((new_route.second.dir + 1) % 4);
    new_route.first.first += 1000;
    if (visited.find(hash_route(new_route)) == visited.end() || visited[hash_route(new_route)] == new_route.first.first)
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void rotate_left()
{
    Route new_route = old_route;
    new_route.second.dir = (Direction)((new_route.second.dir - 1));
    if (new_route.second.dir == LIMBO)
        new_route.second.dir = LEFT;
    new_route.first.first += 1000;
    if (visited.find(hash_route(new_route)) == visited.end() || visited[hash_route(new_route)] == new_route.first.first)
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void move()
{
    Route new_route = old_route;
    switch (old_route.second.dir)
    {
        case UP:
        {
            if (old_route.second.y == 0)
                return ;
            if (grid[old_route.second.y - 1][old_route.second.x] == '#')
                return ;
            new_route.second.y -= 1;
            new_route.first.first += 1;
            break;
        }
        case RIGHT:
        {
            if (old_route.second.x + 1 >= xdim)
                return ;
            if (grid[old_route.second.y][old_route.second.x + 1] == '#')
                return ;
            new_route.second.x += 1;
            new_route.first.first += 1;
            break;
        }
        case DOWN:
        {
            if (old_route.second.y + 1 >= ydim)
                return ;
            if (grid[old_route.second.y + 1][old_route.second.x] == '#')
                return ;
            new_route.second.y += 1;
            new_route.first.first += 1;
            break;
        }
        case LEFT:
        {
            if (old_route.second.x == 0)
                return ;
            if (grid[old_route.second.y][old_route.second.x - 1] == '#')
                return ;
            new_route.second.x -= 1;
            new_route.first.first += 1;
            break;
        }
        default:
            throw std::runtime_error("wtf");
    }
    if (visited.find(hash_route(new_route)) == visited.end() || visited[hash_route(new_route)] == new_route.first.first)
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void update_possible_routes()
{
    rotate_left();
    rotate_right();
    move();
}

static inline bool __attribute__ ((always_inline)) algo()
{
    old_route = *routes.begin();
    old_route.first.second.push_back(std::pair<int,int>(old_route.second.y, old_route.second.x));
    routes.erase(routes.begin());
    
    int y = old_route.second.y;
    int x = old_route.second.x;
    if (grid[y][x] == 'E')
    {
        if (old_route.first.first <= res)
        {
            res = old_route.first.first;
            sol.insert(sol.end(), old_route.first.second.begin(), old_route.first.second.end());
        }
        else
            return true;
    }
    else
        update_possible_routes();
    return false;
}

int grab_input(const std::string& file)
{
    std::ifstream inputfile(file);
    std::string line;
    while (std::getline(inputfile, line))
    {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    xdim = grid[0].size();
    ydim = grid.size();
    for (int y = 0; y < ydim; y++)
    {
        for (int x = 0; x < xdim; x++)
        {
            if (grid[y][x] == 'S')
            {
                og_y = y;
                og_x = x;
            }
        }
    }
    return 0;
}

int main(int ac, char** av)
{
    if (ac != 2)
        return 0;
    grab_input(av[1]);

    Route start_pos;
    start_pos.first.first = 0;
    start_pos.second.y = og_y;
    start_pos.second.x = og_x;
    start_pos.second.dir = RIGHT;
    routes.insert(start_pos);

    while (!algo())
        continue;

    std::set<std::pair<int, int>> unique_elements(sol.begin(), sol.end());

    std::cout << unique_elements.size() << std::endl;
}
