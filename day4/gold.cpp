/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:59:28 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/04 21:03:28 by mhuszar          ###   ########.fr       */
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

void masmas()
{
    if (grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S' && grid[y - 1][x + 1] == 'M' && grid[y + 1][x - 1] == 'S')
        res++;
}
void samsam()
{
    if (grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M' && grid[y - 1][x + 1] == 'S' && grid[y + 1][x - 1] == 'M')
        res++;
}
void massam()
{
    if (grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S' && grid[y - 1][x + 1] == 'S' && grid[y + 1][x - 1] == 'M')
        res++;
}
void sammas()
{
    if (grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M' && grid[y - 1][x + 1] == 'M' && grid[y + 1][x - 1] == 'S')
        res++;
}

bool check_safe_frame()
{
    if (x > 0 && x < xdim - 1 && y > 0 && y < ydim - 1)
        return true;
    return false;
}

void check_dimensions()
{
    if (check_safe_frame())
    {
        masmas();
        samsam();
        massam();
        sammas();
    }
}

int main(void)
{
    while (y < ydim)
    {
        x = 0;
        while (x < xdim)
        {
            if (grid[y][x] == 'A')
                check_dimensions();
            x++;
        }
        y++;
    }
    std::cout << res << std::endl;
}