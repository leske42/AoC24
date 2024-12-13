/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:27:54 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/13 23:36:04 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <utility>
#include <unistd.h>
#include <set>

struct Machine
{
    std::pair<int, int> button_a;
    std::pair<int, int> button_b;
    std::pair<int, int> prize;
};

std::vector<Machine> machines;
std::vector<size_t> costs;
int res = 0;

std::set<std::pair<int, int>> visited;

size_t choose_smallest_price()
{
    if (costs.empty())
        return (0);
    std::sort(costs.begin(), costs.end());
    size_t res = costs.front();
    costs.clear();
    return res;
}

void try_combinations(Machine machine)
{
    int push_a = 0;
    int push_b = 0;

    while (push_b <= 100)
    {
        while (push_a <= 100)
        {
            int total_x = (push_a * machine.button_a.first) + (push_b * machine.button_b.first);
            int total_y = (push_a * machine.button_a.second) + (push_b * machine.button_b.second);
            if (total_x == machine.prize.first && total_y == machine.prize.second)
                costs.push_back(push_a * 3 + push_b * 1);
            push_a++;
        }
        push_a = 0;
        push_b++;
    }
}

void parse_file()
{
    std::ifstream file("input.txt");
    std::string line;
    std::string three_lines;
    int line_ctr = 0;
    std::regex coord_regex(R"(Button A: X\+(\d+), Y\+(\d+).*Button B: X\+(\d+), Y\+(\d+).*Prize: X=(\d+), Y=(\d+))");
    
    while (std::getline(file, line))
    {
        three_lines += line;
        line_ctr++;
        if (line_ctr == 3)
        {
            std::smatch matches;
            if (std::regex_search(three_lines, matches, coord_regex)) {
                machines.push_back({
                    std::pair<int, int>(std::stoi(matches[1]), std::stoi(matches[2])),
                    std::pair<int, int>(std::stoi(matches[3]), std::stoi(matches[4])),
                    std::pair<int, int>(std::stoi(matches[5]), std::stoi(matches[6]))
                });
            }
        }
        else if (line_ctr == 4)
        {
            line_ctr = 0;
            three_lines.clear();
        }
    }
}

int main()
{
    parse_file();
    int idx = 0;
    while (idx < machines.size())
    {
        try_combinations(machines[idx]);
        res += choose_smallest_price();
        idx++;
    }
    std::cout << "RESULT: " << res << std::endl;
    return 0;
}