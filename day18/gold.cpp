/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:04:59 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/18 15:29:05 by mhuszar          ###   ########.fr       */
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

typedef std::vector<char> Row;
std::vector<Row> grid;
int xdim, ydim;
int og_x, og_y;

struct Player
{
    int x = 0;
    int y = 0;
};
Player player;

typedef std::vector<std::pair<int, int>> Coordvec;
typedef std::pair<std::pair<size_t /*cost of route*/, Coordvec>, Player> Route;
Route old_route;
typedef std::multimap<std::pair<size_t /*cost of route*/, Coordvec>, Player> Routes;
Routes routes;

typedef std::map<size_t/*hash*/, size_t/*cost*/> Visited;
Visited visited;

size_t hash_route(Route& to_hash)
{
    return (to_hash.second.x << 8 | to_hash.second.y);
}

void move_up()
{
    Route new_route = old_route;
    if (old_route.second.y == 0)
        return ;
    if (grid[old_route.second.y - 1][old_route.second.x] == '#')
        return ;
    new_route.second.y -= 1;
    new_route.first.first += 1;
    if (visited.find(hash_route(new_route)) == visited.end())
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void move_down()
{
    Route new_route = old_route;
    if (old_route.second.y + 1 >= ydim)
        return ;
    if (grid[old_route.second.y + 1][old_route.second.x] == '#')
        return ;
    new_route.second.y += 1;
    new_route.first.first += 1;
    if (visited.find(hash_route(new_route)) == visited.end())
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void move_left()
{
    Route new_route = old_route;
    if (old_route.second.x == 0)
        return ;
    if (grid[old_route.second.y][old_route.second.x - 1] == '#')
        return ;
    new_route.second.x -= 1;
    new_route.first.first += 1;
    if (visited.find(hash_route(new_route)) == visited.end())
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void move_right()
{
    Route new_route = old_route;
    if (old_route.second.x + 1 >= xdim)
        return ;
    if (grid[old_route.second.y][old_route.second.x + 1] == '#')
        return ;
    new_route.second.x += 1;
    new_route.first.first += 1;
    if (visited.find(hash_route(new_route)) == visited.end())
    {
        routes.insert(new_route);
        visited[hash_route(new_route)] = new_route.first.first;
    }
}

void update_possible_routes()
{
    move_down();
    move_right();
    move_up();
    move_left();
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
        std::cout << "COST: " << old_route.first.first << std::endl;
        return true;
    }
    else
        update_possible_routes();
    return false;
}

void parse_input(char *mapname, int isize)
{
    for (int y = 0; y < isize; y++)
    {
        Row new_row(isize, '.');
        grid.push_back(new_row);
    }
    grid[isize - 1][isize - 1] = 'E';
    std::ifstream file(mapname);
    int x, y;
    char comma;
    int ctr = 0;
    xdim = isize;
    ydim = isize;
    while (!file.eof())
    {
        file >> x >> comma >> y;
        grid[y][x] = '#';
        ctr++;
        if (ctr > 1024)
        {
            
            std::cout << "inserting x: " << x << " y: " << y << std::endl;
            Route start_pos;
            start_pos.first.first = 0;
            start_pos.second.y = 0;
            start_pos.second.x = 0;
            routes.insert(start_pos);

            while (!algo())
                continue;
            routes.clear();
            visited.clear();
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
        return 0;
    parse_input(argv[1], 71);
}