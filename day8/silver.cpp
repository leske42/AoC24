/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:19:40 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/08 18:55:32 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int res = 0;
std::vector<std::vector<char>> map;
int xdim, ydim;
std::vector<std::pair<int, int> > covered;

bool within_bounds(int y, int x)
{
    std::pair<int, int> hehe(y, x);
    if (std::find(covered.begin(), covered.end(), hehe) == covered.end())
        covered.push_back(hehe);
    else
        return false;
    return (y < ydim && x < xdim && y >= 0 && x >= 0);
}

void find_antinode(int own_y, int own_x, int other_y, int other_x)
{
    int new_y = (other_y - own_y) + other_y;
    int new_x = (other_x - own_x) + other_x;
    if (within_bounds(new_y, new_x))
    {
        // std::cout << "Found antinode at y: " << new_y << " x: " << new_x << std::endl;
        res++;
    }
}

void find_all_occurence(char me, int own_y, int own_x)
{
    int x = 0;
    int y = 0;
    while (y < ydim)
    {
        while (x < xdim)
        {
            if (map[y][x] == me && !(y == own_y && x == own_x))
                find_antinode(own_y, own_x, y, x);
            x++;
        }
        x = 0;
        y++;
    }
}

void read_row(int y)
{
    int idx = 0;
    while (idx < xdim)
    {
        while (map[y][idx] == '.')
            idx++;
        find_all_occurence(map[y][idx], y, idx);
        idx++;
    }
}

int main(void)
{
    std::ifstream infile("input.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        std::vector<char> row (line.begin(), line.end());
        map.push_back(row);
    }
    xdim = map[0].size();
    ydim = map.size();
    std::cout << "Map dimensions: ydim: " << ydim << " xdim: " << xdim << std::endl;
    int y = 0;
    while (y < ydim)
    {
        read_row(y);
        y++;
    }
    std::cout << res << std::endl;
}