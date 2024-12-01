/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hehe.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:18:55 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/01 13:30:55 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>

int main(void)
{
    const char* filename = "input.txt";
    std::ifstream input(filename);
    std::vector<int> left;
    std::vector<int> right;
    int num1 = 0, num2 = 0;

    while (!input.eof())
    {
        input >> num1 >> num2;
        left.push_back(num1);
        right.push_back(num2);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    size_t res = 0;
    int idx = 0;
    while (idx < right.size())
    {
        res += abs(left[idx] - right[idx]);
        idx++;
    }
    std::cout << res << std::endl;
}