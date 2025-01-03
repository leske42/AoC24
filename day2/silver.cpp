/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:53:44 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/02 12:55:20 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

typedef std::vector<int>::iterator hehe;

bool ascending(hehe begin, hehe end)
{
    return std::is_sorted(begin, end, [](int a, int b)
    {
        if ((b - a >= 1) && (b - a <= 3))
            return false;
        else
            return true;
    }
    );
}

bool descending(hehe begin, hehe end)
{
    return std::is_sorted(begin, end, [](int a, int b)
    {
        if ((a - b >= 1) && (a - b <= 3))
            return false;
        else
            return true;
    }
    );
}

int main(void)
{
    std::ifstream file("input.txt");

    std::vector<int> numbers;
    std::string line;
    int res = 0;

    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        int number;
        while (stream >> number)
            numbers.push_back(number);
        if (ascending(numbers.begin(), numbers.end()) || descending(numbers.begin(), numbers.end()))
            res++;
        numbers.clear();
    }
    std::cout << res << std::endl;
}