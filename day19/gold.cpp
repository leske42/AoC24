/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:17:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/19 11:07:21 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> patterns;
int res = 0;

void check_matches(int from, int idx, std::string& pattern)
{
    //int prev_idx = 0;
    while (idx < patterns.size())
    {
        if (pattern.compare(from, patterns[idx].size(), patterns[idx]) == 0)
        {
            //if (pattern == "brgr")
            //    std::cout << "called with vals " << from << " " << idx << " " << pattern << " " << patterns[idx] << std::endl;
            if (from == pattern.size() - patterns[idx].size())
            {
                res++;
                return ;
            }
            check_matches(from, idx + 1, pattern);
            check_matches(from + patterns[idx].size(), 0, pattern);
            return ;
        }
        idx++;
    }
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
        //std::cout << pattern << std::endl;
        pattern.pop_back();
        patterns.push_back(pattern);
    }
    while (!infile.eof())
    {
        std::getline(infile, pattern);
        check_matches(0, 0, pattern);
    }
    std::cout << res << std::endl;
}

int main(void)
{
    parse_input();
}