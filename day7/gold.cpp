/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver copy.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:09:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/07 21:42:05 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

size_t res = 0;

size_t concat_nums(size_t one, size_t other)
{
    std::stringstream hehe;
    hehe << one << other;
    return (std::stoull(hehe.str()));
}

bool check_path(const std::vector<size_t> numbers, int index, size_t current, size_t target)
{

    if (index == numbers.size())
    {
        return current == target;
    }

    return check_path(numbers, index + 1, current + numbers[index], target) ||
           check_path(numbers, index + 1, concat_nums(current, numbers[index]), target) ||
           check_path(numbers, index + 1, current * numbers[index], target);
}

int main(void)
{
    std::ifstream infile("input.txt");
    std::string line;
    size_t goal;
    char colon;
    size_t next;
    while (std::getline(infile, line))
    {
        std::vector<size_t> stack;
        std::stringstream hehe(line);
        hehe >> goal;
        hehe >> colon;
        while (hehe >> next)
            stack.push_back(next);
        
        // std::cout << line << "Stack size: " << stack.size() << std::endl;
        if (check_path(stack, 1, stack[0], goal))
            res += goal;
    }
    std::cout << res << std::endl;
}