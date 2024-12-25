/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:34:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/25 22:16:18 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <map>
#include <set>

typedef std::set<std::string> Connections;
typedef std::map<std::string /*computer name*/, Connections /*connected computers*/> Graph;
Graph map;

Graph::iterator iter;
Connections::iterator iter2;
Connections::iterator iter3;

size_t res = 0;

bool begins_with_t(void)
{
    if (iter->first[0] == 't')
        return (true);
    if ((*iter2)[0] == 't')
        return (true);
    return ((*iter3)[0] == 't');
}

#include <cstdint>

std::set<size_t> visited;

size_t hash_tirangle(std::string one, std::string two, std::string three)
{
    size_t ones = one[0] << 8 | one[1];
    size_t twos = two[0] << 8 | two[1];
    size_t threes = three[0] << 8 | three[1];
    if (ones < twos)
    {
        if (twos < threes)
            return (ones << 32 | twos << 16 | threes);
        return (ones << 32 | threes << 16 | twos);
    }
    if (threes > ones)
        return (twos << 32 | ones << 16 | threes);
    return (twos << 32 | threes << 16 | ones);
}

bool is_not_visited()
{
    size_t hash = hash_tirangle(iter->first, *iter2, *iter3);
    if (visited.find(hash) == visited.end())
    {
        //std::cout << "ONE: " << iter->first << " TWO: " << *iter2 << " THREE: " << *iter3 << std::endl;
        visited.insert(hash);
        return true;
    }
    return false;
}

void find_triangles()
{
    iter = map.begin();
    while (iter != map.end())
    {
        iter2 = iter->second.begin();
        while (iter2 != iter->second.end())
        {
            iter3 = iter->second.begin();
            while (iter3 != iter->second.end())
            {
                if ((map[*iter2].find(*iter3) != map[*iter2].end()) && begins_with_t() && is_not_visited())
                {
                    res++;
                }
                iter3++;
            }
            iter2++;
        }
        iter++;
    }
}

void parse_input()
{
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::string key;
        key.push_back(line[0]);
        key.push_back(line[1]);
        std::string val;
        val.push_back(line[3]);
        val.push_back(line[4]);
        map[key].insert(val);
        map[val].insert(key);
    }
}

int main(void)
{
    parse_input();
    find_triangles();
    std::cout << res / 2 << std::endl;
}