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
    //else
      //  std::cout << map2[player.y][player.x] << std::endl;
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
    //map2[player.y][player.x] = player.dir;
}

int main()
{
    std::ifstream file("input_lukas.txt");
    
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

    int ydim = map.size();
    int xdim = map[0].size();
    int x = 0;
    int y = 0;
    int og_y = player.y;
    int og_x = player.x;
    Direction og_dir = player.dir;

    while (y < ydim)
    {
        while (x < xdim)
        {
            if (x == player.x && y == player.y)
                goto next;
            map2 = map;
            player.x = og_x;
            player.y = og_y;
            player.dir = og_dir;
            map2[y][x] = '0';
            goto run;
            next:
            x++;
        }
        x = 0;
        y++;
    }
    goto end;

    run:
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
            goto next;
        }
    }
    goto next;

    end:

    std::cout << res << std::endl;
}