/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:12:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/09 10:54:53 by mhuszar          ###   ########.fr       */
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
    int file_idx = 0;
    int idx = 0;
    while (idx < line.size())
    {
        int amount = line[idx] - 48;
        while (amount)
        {
            if (idx % 2)
                dotmap.push_back(DOT);
            else
                dotmap.push_back(file_idx);
            amount--;
            
        }
        if (idx % 2 == 0) //does this cause issue for 0 len file?
            file_idx++;
        idx++;
    }
}

int main(void)
{
    std::ifstream file("input.txt");
    std::string content;
    file >> content;
    Line line(content.begin(), content.end());
    create_dotmap(line);
    move_memory();
    add_up_dotmap();
    std::cout << res << std::endl;
}