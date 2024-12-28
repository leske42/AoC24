/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:37:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/28 01:38:18 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <map>
#include <set>

#define ELEMS 2008

typedef std::pair<unsigned char, unsigned char> Secret;
std::vector<Secret> digits[ELEMS];

typedef std::map<uint32_t /*sequence hash*/, size_t /*total value*/> Seqmap;
Seqmap seq_map;

int idx = 0;
size_t cur_biggest = 0;

void fill_map()
{
    for (int j = 0; j < ELEMS ; j++)
    {
        std::set<uint32_t> covered;
        for (int i = 1; i + 3 < 2000; i++)
        {
            uint32_t hash = digits[j][i].second | digits[j][i + 1].second << 8
                | digits[j][i + 2].second << 16 | digits[j][i + 3].second << 24;
            if (covered.find(hash) == covered.end())
            {
                seq_map[hash] += digits[j][i + 3].first;
                covered.insert(hash);
            }
        }
    }
    Seqmap::iterator iter = seq_map.begin();
    uint32_t hash_final = 0;
    while (iter != seq_map.end())
    {
        if (iter->second > cur_biggest)
            cur_biggest = iter->second;
        iter++;
    }
    std::cout << cur_biggest << std::endl;
}

void transform(size_t num)
{
    for (int i = 0; i < 2000; i++)
    {
        num = num ^ (num << 6);
        num = num & 16777215;
        num = num ^ (num >> 5);
        num = num & 16777215;
        num = num ^ (num << 11);
        num = num & 16777215;
        Secret new_secret;
        new_secret.first = num % 10;
        new_secret.second = 0;
        if (i != 0)
            new_secret.second = new_secret.first - digits[idx].back().first;
        digits[idx].push_back(new_secret);
    }
}

void parse_input()
{
    std::ifstream file("input.txt");
    while (!file.eof())
    {
            size_t next_num;
            file >> next_num;
            transform(next_num);
            idx++;
    }
}

int main(void)
{
    parse_input();
    fill_map();
}