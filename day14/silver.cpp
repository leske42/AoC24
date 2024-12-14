/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:45:03 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/14 19:18:00 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::pair<int, int> Coordinates;
typedef std::pair<Coordinates, Coordinates> Robot;
std::vector<Robot> robots;

# define XDIM 101
# define YDIM 103

# define XHALF (XDIM / 2)
# define YHALF (YDIM / 2)

int res = 0;

void count_sectors()
{
    int sector_1, sector_2, sector_3, sector_4;
    sector_1 = sector_2 = sector_3 = sector_4 = 0;
    for (int j = 0; j < robots.size(); j++)
    {
        if (robots[j].first.first < XHALF && robots[j].first.second < YHALF)
            sector_1++;
        else if (robots[j].first.first > XHALF && robots[j].first.second < YHALF)
            sector_2++;
        else if (robots[j].first.first < XHALF && robots[j].first.second > YHALF)
            sector_3++;
        else if (robots[j].first.first > XHALF && robots[j].first.second > YHALF)
            sector_4++;
    }
    res = sector_1 * sector_2 * sector_3 * sector_4;
}

void update_robot(Robot& robot)
{
    robot.first.first += robot.second.first;
    robot.first.second += robot.second.second;
    if (robot.first.first >= XDIM)
        robot.first.first -= XDIM;
    else if (robot.first.first < 0)
        robot.first.first += XDIM;
    if (robot.first.second >= YDIM)
        robot.first.second -= YDIM;
    else if (robot.first.second < 0)
        robot.first.second += YDIM;
}

void parse_file()
{
    std::ifstream file("input.txt");
    std::string line;
    std::regex regex_pattern(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
    
    while (std::getline(file, line))
    {
        std::smatch matches;
        if (std::regex_search(line, matches, regex_pattern))
        {
            robots.push_back({
                std::pair<int, int>(std::stoi(matches[1]), std::stoi(matches[2])),
                std::pair<int, int>(std::stoi(matches[3]), std::stoi(matches[4])),
            });
        }
    }
}

int main(void)
{
    parse_file();
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < robots.size(); j++)
        {
            update_robot(robots[j]);
        }
    }
    count_sectors();
    std::cout << res << std::endl;
}

