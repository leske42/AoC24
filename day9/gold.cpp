/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:12:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/09 17:55:50 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<vector>
#include<fstream>
#include<iostream>

typedef std::vector<std::pair<char, int>> Line;
typedef std::vector<int> Dotmap;
Dotmap dotmap;
#define DOT 2147483647
size_t res = 0;

void add_up_dotmap()
{
    int idx = 0;
    while (idx < dotmap.size())
    {
        res += dotmap[idx] * idx;
        idx++;
    }
}

void create_dotmap(Line line)
{
    int idx = 0;
    while (idx < line.size())
    {
        if (line[idx].first == -1)
        {
            idx++;
            continue;
        }
        int amount = line[idx].first - 48;
        while (amount)
        {
            dotmap.push_back(line[idx].second);
            amount--;
        }
        idx++;
    }
}

void reorganize_line(Line& line)
{
    int idx = 1;
    int reverse_idx = line.size() - 1;
    while (idx <= reverse_idx)
    {
        if (line[idx].first >= line[reverse_idx].first)
        {
            line[idx] = line[reverse_idx];
            line[reverse_idx].first = -1;
            idx += 2;
        }
        reverse_idx -= 2;
    }
    while (idx < line.size()) //remove all SPC so now we consider line has files only
    {
        line[idx].first = -1;
        idx += 2;
    }
}

void print_dotmap()
{
    for (int idx = 0; idx < dotmap.size(); idx++)
    {
        std::cout << dotmap[idx];
    }
    std::cout << std::endl;
}

int main(void)
{
    std::ifstream file("proba.txt");
    std::string content;
    file >> content;
    std::cout << "Line len: " << content.size() << std::endl; //DEBUGINFO: check if line ends with a file or emtpy space
    int idx = 0;
    int file_idx = 0;
    Line line;
    while (idx < content.size())
    {
        std::pair<char, int> newpair(content[idx], file_idx);
        line.push_back(newpair);
        if (idx % 2 == 0)
            file_idx++;
        idx++;
    }
    reorganize_line(line);
    create_dotmap(line);
    add_up_dotmap();
    print_dotmap();
    std::cout << res << std::endl;
}