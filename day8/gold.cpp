/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:19:40 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/08 19:36:00 by mhuszar          ###   ########.fr       */
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

bool stored(int y, int x)
{
    std::pair<int, int> hehe(y, x);
    if (std::find(covered.begin(), covered.end(), hehe) == covered.end())
    {
        covered.push_back(hehe);
        return false;
    }
    else
        return true;
}

bool within_bounds(int y, int x)
{
    return (y < ydim && x < xdim && y >= 0 && x >= 0);
}

void find_antinodes(int own_y, int own_x, int other_y, int other_x)
{
    if (!stored(own_y, own_x))
        res++;
    if (!stored(other_y, other_x))
        res++;
    int new_y = (other_y - own_y) + other_y;
    int new_x = (other_x - own_x) + other_x;
    while (within_bounds(new_y, new_x))
    {
        if (!stored(new_y, new_x))
            res++;
        new_y = (other_y - own_y) + new_y;
        new_x = (other_x - own_x) + new_x;
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
                find_antinodes(own_y, own_x, y, x);
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
    int y = 0;
    while (y < ydim)
    {
        read_row(y);
        y++;
    }
    std::cout << res << std::endl;
}