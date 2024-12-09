/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:12:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/09 11:13:53 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<vector>
#include<fstream>
#include<iostream>

typedef std::vector<char> Line;
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

bool contains_empty_space(int& idx)
{
    Dotmap::iterator iter = dotmap.begin();
    while (iter + idx != dotmap.end())
    {
        if (*(iter + idx) == DOT)
            return true;
        idx++;
    }
    return false;
}

void move_memory()
{
    int idx = 0;
    while (contains_empty_space(idx))
    {
        int back = DOT;
        while (back == DOT)
        {
            back = dotmap.back();
            dotmap.pop_back();
        }
        dotmap[idx] = back;
        idx++;
    }
}

void create_dotmap(Line line)
{
    int file_idx = -1;
    int idx = 0;
    while (idx < line.size())
    {
        if (line[idx] == -1)
        {
            idx++;
            continue;
        }
        file_idx++;
        int amount = line[idx] - 48;
        while (amount)
        {
            dotmap.push_back(file_idx);
            amount--;
        }
        idx++;
    }
}

void reorganize_line(Line& line)
{
    int idx = 1;
    int reverse_idx = line.size() - 1;
    while (idx < reverse_idx)
    {
        if (line[idx] > line[reverse_idx])
        {
            line[idx] = line[reverse_idx];
            line[reverse_idx] = -1;
            idx += 2;
        }
        reverse_idx -= 2;
    }
    while (idx < line.size()) //remove all SPC so now we consider line has files only
    {
        line[idx] = -1;
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
    std::cout << content.size() << std::endl; //DEBUGINFO: check if line ends with a file or emtpy space
    Line line(content.begin(), content.end());
    reorganize_line(line);
    create_dotmap(line);
    //move_memory();
    add_up_dotmap();
    print_dotmap();
    std::cout << res << std::endl;
}