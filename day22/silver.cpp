/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:37:04 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/28 01:38:06 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

size_t res = 0;

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
    }
    res += num;
}

void parse_input()
{
    std::ifstream file("input.txt");
    while (!file.eof())
    {
            size_t next_num;
            file >> next_num;
            transform(next_num);
    }
}

int main(void)
{
    parse_input();
    std::cout << res << std::endl;
}