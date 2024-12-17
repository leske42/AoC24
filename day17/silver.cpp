/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:01:00 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/17 15:20:51 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <vector>
#include <exception>
#include <cmath>
#include <iostream>

size_t rax, rbx, rcx, rip, rdi;

std::vector<char> code;

size_t combo(char val)
{
    switch (val)
    {
        case 0:
            return (0);
        case 1:
            return (1);
        case 2:
            return (2);
        case 3:
            return (3);
        case 4:
            return (rax);
        case 5:
            return (rbx);
        case 6:
            return (rcx);
        case 7:
            throw ;
    }
    return (0);
}

void execute()
{
    size_t of = code.size();
    jmp:
    while (rip < of)
    {
        rdi = code[rip + 1];
        switch (code[rip])
        {
            case 0:
            {
                rax = rax / pow(2, combo(rdi));
                break;
            }
            case 1:
            {
                rbx = rbx ^ rdi;
                break;
            }
            case 2:
            {
                rbx = combo(rdi) % 8;
                break;
            }
            case 3:
            {
                if (rax)
                {
                    rip = (rdi);
                    goto jmp;
                }
                break;
            }
            case 4:
            {
                rbx = rbx ^ rcx;
                break;
            }
            case 5:
            {
                std::cout << combo(rdi) % 8 << ",";
                break;
            }
            case 6:
            {
                rbx = rax / pow(2, combo(rdi));
                break;
            }
            case 7:
            {
                rcx = rax / pow(2, combo(rdi));
                break;
            }
        }
        rip += 2;
    }
}

int main(void)
{
    rbx = rcx = rip = rdi = 0;
    rax = 63281501;
    code = {2,4,1,5,7,5,4,5,0,3,1,6,5,5,3,0};
    execute();
    std::cout << std::endl;
}