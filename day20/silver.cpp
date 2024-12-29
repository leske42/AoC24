/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:23:32 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/29 21:46:20 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unistd.h>

struct Player
{
    int x;
    int y;
    int prev_x;
    int prev_y;
    int start_x;
    int start_y;
};
Player player;

typedef std::map<int /*cheat gain in picosec*/, size_t /*amount of possible cheats*/> Cheatmap;
Cheatmap cheats;

struct Node
{
    char type;
    int serialno = -1;
};

typedef std::vector<Node> Row;
std::vector<Row> map;
int xdim, ydim;

void update_prev_fields()
{
    player.prev_x = player.x;
    player.prev_y = player.y;
}

void reset_player()
{
    player.x = player.start_x;
    player.y = player.start_y;
    update_prev_fields();
}

bool is_behind_me(int y, int x)
{
    return (y == player.prev_y && x == player.prev_x);
}

bool within_bounds(int y, int x)
{
    return (y >= 0 && y < ydim && x >= 0 && x <= xdim);
}

bool clear_to_move(int y, int x)
{
    return (map[y][x].type == '.' || map[y][x].type == 'E');
}

void move()
{
    if (within_bounds(player.y + 1, player.x) && !is_behind_me(player.y + 1, player.x))
    {
        if (clear_to_move(player.y + 1, player.x))
        {
            update_prev_fields();
            player.y++;
            return ;
        }
    }
    if (within_bounds(player.y - 1, player.x) && !is_behind_me(player.y - 1, player.x))
    {
        if (clear_to_move(player.y - 1, player.x))
        {
            update_prev_fields();
            player.y--;
            return ;
        }
    }
    if (within_bounds(player.y, player.x + 1) && !is_behind_me(player.y, player.x + 1))
    {
        if (clear_to_move(player.y, player.x + 1))
        {
            update_prev_fields();
            player.x++;
            return ;
        }
    }
    if (within_bounds(player.y, player.x - 1) && !is_behind_me(player.y, player.x - 1))
    {
        if (clear_to_move(player.y, player.x - 1))
        {
            update_prev_fields();
            player.x--;
            return ;
        }
    }
}

void draw_whole_map()
{
    for (int y = 0; y < ydim; y++)
    {
        for (int x = 0; x < xdim; x++)
        {
            if (y == player.y && x == player.x)
                std::cout << 'X';
            else
                std::cout << map[y][x].type;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    sleep(1);
}

void assign_costs()
{
    reset_player();
    int idx = 0;
    while (map[player.y][player.x].type != 'E')
    {
        move();
        idx++;
        map[player.y][player.x].serialno = idx;
    }
}

void try_all_cheats()
{
    if (within_bounds(player.y + 2, player.x))
    {
        if (map[player.y + 2][player.x].serialno != -1)
            cheats[map[player.y + 2][player.x].serialno - (map[player.y][player.x].serialno + 2)] += 1;
    }
    if (within_bounds(player.y - 2, player.x))
    {
        if (map[player.y - 2][player.x].serialno != -1)
            cheats[map[player.y - 2][player.x].serialno - (map[player.y][player.x].serialno + 2)] += 1;
    }
    if (within_bounds(player.y, player.x + 2))
    {
        if (map[player.y][player.x + 2].serialno != -1)
            cheats[map[player.y][player.x + 2].serialno - (map[player.y][player.x].serialno + 2)] += 1;
    }
    if (within_bounds(player.y, player.x - 2))
    {
        if (map[player.y][player.x - 2].serialno != -1)
            cheats[map[player.y][player.x - 2].serialno - (map[player.y][player.x].serialno + 2)] += 1;
    }
}

void parse_input()
{
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        Row new_row;
        while (line.size() > 0)
        {
            Node new_node;
            new_node.type = line[0];
            if (line[0] == 'S')
            {
                player.start_x = new_row.size();
                player.start_y = map.size();
            }
            new_row.push_back(new_node);
            line.erase(0, 1);
        }
        map.push_back(new_row);
    }
    xdim = map[0].size();
    ydim = map.size();
}

int main(void)
{
    parse_input();
    assign_costs();
    reset_player();
    while (map[player.y][player.x].type != 'E')
    {
        try_all_cheats();
        move();
        //draw_whole_map();
    }
    size_t res = 0;
    Cheatmap::iterator it = cheats.begin();
    while (it != cheats.end())
    {
        if (it->first >= 100)
            res += it->second;
        it++;
    }
    std::cout << res << std::endl;
}