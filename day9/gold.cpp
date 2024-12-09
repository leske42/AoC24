/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:12:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/09 18:33:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<vector>
#include<fstream>
#include<iostream>

enum Type
{
    FILE_ = 0,
    SPACE_
};

struct s_info
{
    int value;
    int file_idx;
    Type type;
};

typedef std::vector<s_info> Line;
typedef std::vector<int> Dotmap;
Dotmap dotmap;
#define DOT 2147483647
size_t res = 0;

void add_up_dotmap()
{
    int idx = 0;
    while (idx < dotmap.size())
    {
        if (dotmap[idx] != DOT)
            res += dotmap[idx] * idx;
        idx++;
    }
}

void create_dotmap(Line line)
{
    int idx = 0;
    while (idx < line.size())
    {
        while (line[idx].value)
        {
            if (line[idx].type == SPACE_)
                dotmap.push_back(DOT);
            else
                dotmap.push_back(line[idx].file_idx);
            line[idx].value--;
        }
        idx++;
    }
}

void reorganize_line(Line& line)
{
    int reverse_idx = line.size();
    while (reverse_idx > 0) //cause 0th is always a file that will never be moved
    {
        reverse_idx--;
        if (line[reverse_idx].type == SPACE_)
            continue;
        int idx = 0;
        while (idx < reverse_idx)
        {
            if (line[idx].type == SPACE_ && line[idx].value == line[reverse_idx].value)
            {
                line[idx] = line[reverse_idx];
                line[reverse_idx].type = SPACE_;
                break;
            }
            else if (line[idx].type == SPACE_ && line[idx].value > line[reverse_idx].value)
            {
                s_info new_node;
                new_node.file_idx = -1;
                new_node.type = SPACE_;
                new_node.value = line[idx].value - line[reverse_idx].value;
                line[idx] = line[reverse_idx];
                line[reverse_idx].type = SPACE_;
                line.insert(line.begin() + idx + 1, new_node);
                break;
            }
            idx++;
        }
    }
    // while (idx < line.size()) //remove all SPC so now we consider line has files only
    // {
    //     line[idx].first = -1;
    //     idx += 2;
    // }
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
    std::ifstream file("input.txt");
    std::string content;
    file >> content;
    std::cout << "Line len: " << content.size() << std::endl; //DEBUGINFO: check if line ends with a file or emtpy space
    int idx = 0;
    int file_idx = 0;
    Line line;
    while (idx < content.size())
    {
        s_info new_block;
        new_block.value = content[idx] - 48;
        if (idx % 2 == 0)
        {
            new_block.file_idx = file_idx;
            new_block.type = FILE_;
            file_idx++;
        }
        else
        {
            new_block.file_idx = -1;
            new_block.type = SPACE_;
        }
        line.push_back(new_block);
        idx++;
    }
    reorganize_line(line);
    create_dotmap(line);
    add_up_dotmap();
    // print_dotmap();
    std::cout << res << std::endl;
}