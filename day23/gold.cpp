/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:34:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/25 22:12:36 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

typedef std::set<std::string> Connections;
typedef std::map<std::string /*computer name*/, Connections /*connected computers*/> Graph;
Graph map;
Connections cur_biggest;

bool fits_into_cluster(std::set<std::string> cluster, std::string nw)
{
    Connections::iterator it = cluster.begin();
    while (it != cluster.end())
    {
        if (map[*it].find(nw) != map[*it].end())
            it++;
        else
            return false;
    }
    return true;
}

void find_biggest_set()
{
    Graph::iterator iter = map.begin();
    while (iter != map.end())
    {
        std::set<std::string> tiny_set;
        tiny_set.insert(iter->first);
        Connections::iterator iter2 = iter->second.begin();
        while (iter2 != iter->second.end())
        {
            if (fits_into_cluster(tiny_set, *iter2))
                tiny_set.insert(*iter2);
            iter2++;
        }
        if (tiny_set.size() > cur_biggest.size())
            cur_biggest = tiny_set;
        tiny_set.clear();
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
    find_biggest_set();
    std::cout << cur_biggest.size() << std::endl;
    Connections::iterator it = cur_biggest.begin();
    while (it != cur_biggest.end())
    {
        std::cout << *it << ",";
        it++;
    }
    std::cout << std::endl;
}