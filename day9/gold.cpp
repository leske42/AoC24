/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:12:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/09 21:19:36 by mhuszar          ###   ########.fr       */
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

#define DOT -1
typedef std::vector<s_info> Line;
typedef std::vector<int> Dotmap;
Line line;
Dotmap dotmap;

size_t res = 0;
int front_idx;
int reverse_idx;

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

void create_dotmap()
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

void replace_node()
{
    line[front_idx] = line[reverse_idx];
    line[reverse_idx].type = SPACE_;
}

void insert_node_and_partition_space()
{
    s_info new_node;
    new_node.file_idx = -1;
    new_node.type = SPACE_;
    new_node.value = line[front_idx].value - line[reverse_idx].value;
    line[front_idx] = line[reverse_idx];
    line[reverse_idx].type = SPACE_;
    line.insert(line.begin() + front_idx + 1, new_node);
}

void reorganize_line()
{
    reverse_idx = line.size();
    while (reverse_idx > 0) //cause 0th is always a file that will never be moved
    {
        reverse_idx--;
        if (line[reverse_idx].type == SPACE_)
            continue;
        //we only reach this part if reverse_idx holds a FILE.
        front_idx = -1;
        while (++front_idx < reverse_idx)
        {
            if (line[front_idx].type == SPACE_)
            {
                if (line[front_idx].value == line[reverse_idx].value)
                    replace_node();
                else if (line[front_idx].value > line[reverse_idx].value)
                    insert_node_and_partition_space();
                else
                    continue;
                break;
            }
        }
    }
}

void add_blocks_to_line(std::string& content)
{
    int idx = 0;
    int file_idx = 0;
    while (idx < content.size())
    {
        s_info new_block;
        new_block.file_idx = -1;
        new_block.value = content[idx] - 48;
        if (idx % 2 == 0)
        {
            new_block.file_idx = file_idx++;
            new_block.type = FILE_;
        }
        else
            new_block.type = SPACE_;

        line.push_back(new_block);
        idx++;
    }
}

void print_dotmap()
{
    for (int idx = 0; idx < dotmap.size(); idx++)
        std::cout << dotmap[idx];
    std::cout << std::endl;
}

int main(void)
{
    std::ifstream file("input.txt");
    std::string content;
    file >> content;
    add_blocks_to_line(content);
    reorganize_line();
    create_dotmap();
    add_up_dotmap();
    std::cout << res << std::endl;
    //print_dotmap();
}