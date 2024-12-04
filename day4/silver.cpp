/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:59:28 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/04 21:02:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <fstream>
#include <iostream>

typedef std::vector<std::vector<char>> grid_t;
int res = 0;

grid_t create_grid()
{
    grid_t grid;
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    return (grid);
}

grid_t grid = create_grid();
const int xdim = grid[0].size();
const int ydim = grid.size();
int x, y = 0;

void check_left()
{
    if (x < 3)
        return ;
    if (grid[y][x] == 'X' && grid[y][x - 1] == 'M' && grid[y][x - 2] == 'A' && grid[y][x - 3] == 'S')
        res++;
}
void check_right()
{
    if (x > xdim - 4)
        return ;
    if (grid[y][x] == 'X' && grid[y][x + 1] == 'M' && grid[y][x + 2] == 'A' && grid[y][x + 3] == 'S')
        res++;
}
void check_up()
{
    if (y < 3)
        return ;
    if (grid[y][x] == 'X' && grid[y - 1][x] == 'M' && grid[y - 2][x] == 'A' && grid[y - 3][x] == 'S')
        res++;
}
void check_down()
{
    if (y > ydim - 4)
        return ;
    if (grid[y][x] == 'X' && grid[y + 1][x] == 'M' && grid[y + 2][x] == 'A' && grid[y + 3][x] == 'S')
        res++;
}
void check_downright()
{
    if (y > ydim - 4 || x > xdim - 4)
        return ;
    if (grid[y][x] == 'X' && grid[y + 1][x + 1] == 'M' && grid[y + 2][x + 2] == 'A' && grid[y + 3][x + 3] == 'S')
        res++;
}
void check_downleft()
{
    if (y > ydim - 4 || x < 3)
        return ;
    if (grid[y][x] == 'X' && grid[y + 1][x - 1] == 'M' && grid[y + 2][x - 2] == 'A' && grid[y + 3][x - 3] == 'S')
        res++;
}
void check_upright()
{
    if (y < 3 || x > xdim - 4)
        return ;
    if (grid[y][x] == 'X' && grid[y - 1][x + 1] == 'M' && grid[y - 2][x + 2] == 'A' && grid[y - 3][x + 3] == 'S')
        res++;
}
void check_upleft()
{
    if (y < 3 || x < 3)
        return ;
    if (grid[y][x] == 'X' && grid[y - 1][x - 1] == 'M' && grid[y - 2][x - 2] == 'A' && grid[y - 3][x - 3] == 'S')
        res++;
}

void check_dimensions()
{
    check_left();
    check_right();
    check_up();
    check_down();
    check_downright();
    check_downleft();
    check_upright();
    check_upleft();
}

int main(void)
{
    while (y < ydim)
    {
        x = 0;
        while (x < xdim)
        {
            if (grid[y][x] == 'X')
                check_dimensions();
            x++;
        }
        y++;
    }
    std::cout << res << std::endl;
}