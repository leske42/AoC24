/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:17:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/19 20:25:48 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> patterns;
size_t res;

void check_matches(std::string& pattern)
{
    std::vector<size_t> ways_till_end(pattern.size() + 1, 0);
    int idx = pattern.size() - 1;
    ways_till_end[idx + 1] = 1;
    while (idx >= 0)
    {
        for (int subpat = 0; subpat < patterns.size(); subpat++)
        {
            if (idx + patterns[subpat].size() <= pattern.size()
                && pattern.compare(idx, patterns[subpat].size(), patterns[subpat]) == 0)
            {
                // std::cout << "SUBPAT " << patterns[subpat] << " fits into " << pattern << " from index " << idx << std::endl;
                ways_till_end[idx] += ways_till_end[idx + patterns[subpat].size()];
            }
        }
        idx--;
    }
    res += ways_till_end[0];
    return;
}

void parse_input()
{
    std::ifstream infile("input.txt");
    std::string pattern;
    while (1)
    {
        infile >> pattern;
        if (pattern == "HEHE")
            break;
        pattern.pop_back();
        patterns.push_back(pattern);
    }
    std::getline(infile, pattern);
    while (!infile.eof())
    {
        std::getline(infile, pattern);
        check_matches(pattern);
    }
    std::cout << res << std::endl;
}

int main(void)
{
    res = 0;
    parse_input();
}