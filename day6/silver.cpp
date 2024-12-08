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

std::vector<std::vector<char>> map;

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
    return (new_y < 0 || new_y >= map.size() || new_x < 0 || new_x >= map[0].size());
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
           (map[new_y][new_x] == '.' || map[new_y][new_x] == 'X');
}

void move()
{
    map[player.y][player.x] = 'X';
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
    map[player.y][player.x] = 'X';
}

int main()
{
    std::ifstream file("proba.txt");
    
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
                player.x = i;
                player.y = map.size();
                player.dir = (c == '^') ? UP : (c == '>') ? RIGHT : (c == 'v') ? DOWN : LEFT;
            }
            i++;
        }
    map.push_back(row);
    }

    while (player.x >= 0 && player.x < map[0].size() && player.y >= 0 && player.y < map.size())
    {
        if (out_of_bounds())
            break;
        else if (can_move())
            move();
        else
            player.dir = rotate(player.dir);
    }

    int res = 0;
    int x, y;
    x = y = 0;
    while (y < map.size())
    {
        while (x < map[0].size())
        {
            if (map[y][x] == 'X')
                res++;
            std::cout << map[y][x];
            x++;
        }
        std::cout << std::endl;
        x = 0;
        y++;
    }
    std::cout << res << std::endl;
}