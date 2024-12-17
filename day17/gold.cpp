/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:36:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/17 15:20:06 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
#include <vector>

std::vector<size_t> vec = {2,4,1,5,7,5,4,5,0,3,1,6,5,5,3,0};

void recurse(size_t rax, size_t limit, size_t print)
{
    while (rax < limit)
    {
        size_t mod8 = rax % 8;
        size_t xor5 = mod8 ^ 5;
        size_t div = rax / pow(2, xor5);
        size_t result = xor5 ^ div ^ 6;
        if (result % 8 == vec[print]) {
            if (print == 0)
                std::cout << "RAX: " << rax << std::endl;
            recurse(rax * 8, (rax + 1) * 8, print - 1);
        }
        rax++;
    }
}

int main()
{
    recurse(0, 8, vec.size() - 1);
}
