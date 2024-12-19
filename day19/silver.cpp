/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:17:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/19 10:46:40 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> patterns;
int res = 0;

bool check_matches(int from, int idx, std::string& pattern)
{
    //std::cout << "called with vals " << from << " " << idx << " " << pattern << std::endl;
    //int prev_idx = 0;
    if (from == pattern.size())
        return true;
    while (idx < patterns.size())
    {
        if (pattern.compare(from, patterns[idx].size(), patterns[idx]) == 0)
        {
            /*if (idx == patterns.size() - 1)
            {
                if (pattern == "bbrgwb")
                    std::cout << "last match: " << patterns[idx] << std::endl;
                return (true);
            }
            else*/
            return (check_matches(from, idx + 1, pattern) || check_matches(from + patterns[idx].size(), 0, pattern));
        }
        idx++;
    }
    return (false);
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
        //std::cout << pattern << std::endl;
        pattern.pop_back();
        patterns.push_back(pattern);
    }
    while (!infile.eof())
    {
        std::getline(infile, pattern);
        if (check_matches(0, 0, pattern))
        {
            //std::cout << pattern << std::endl;
            res++;
        }
    }
    std::cout << res << std::endl;
}

int main(void)
{
    parse_input();
}