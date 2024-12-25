/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:57:00 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/25 17:44:07 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <cstdint>

typedef std::map<uint16_t, size_t> Cache;
Cache local_cache[25];
#define MAX_LEVEL 24

std::string choose_val(char from, char to)
{
    if (from == '^')
    {
        switch (to)
        {
            case '^':
                return ("A");
                break;
            case '<':
                return ("v<A");
                break;
            case 'v':
                return ("vA");
                break;
            case '>':
                return ("v>A");
                break;
            case 'A':
                return (">A");
                break;
        }
    }

    else if (from == '<')
    {
        switch (to)
        {
            case '^':
                return (">^A");
                break;
            case '<':
                return ("A");
                break;
            case 'v':
                return (">A");
                break;
            case '>':
                return (">>A");
                break;
            case 'A':
                return (">>^A");
                break;
        }
    }

    else if (from == 'v')
    {
        switch (to)
        {
            case '^':
                return ("^A");
                break;
            case '<':
                return ("<A");
                break;
            case 'v':
                return ("A");
                break;
            case '>':
                return (">A");
                break;
            case 'A':
                return ("^>A");
                break;
        }
    }

    else if (from == '>')
    {
        switch (to)
        {
            case '^':
                return ("<^A");
                break;
            case '<':
                return ("<<A");
                break;
            case 'v':
                return ("<A");
                break;
            case '>':
                return ("A");
                break;
            case 'A':
                return ("^A");
                break;
        }
    }

    else if (from == 'A')
    {
        switch (to)
        {
            case '^':
                return ("<A");
                break;
            case '<':
                return ("v<<A");
                break;
            case 'v':
                return ("<vA");
                break;
            case '>':
                return ("vA");
                break;
            case 'A':
                return ("A");
                break;
        }
    }
    throw ;
    return ("hehe");
}

uint16_t calc_key(char from, char to)
{
    return (from << 8 | to);
}

size_t vectorize(char from, char to, int level)
{
    if (local_cache[level].find(calc_key(from, to)) != local_cache[level].end())
        return (local_cache[level][calc_key(from, to)]);
    size_t ret = 0;
    std::string str;
    if (level != MAX_LEVEL)
        str += "A"; //we always end every movement with "A" so have to assume A as 0th value
    str += choose_val(from, to);
    if (level == MAX_LEVEL)
        return str.size();
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        ret += vectorize(str[idx], str[idx + 1], level + 1);
    local_cache[level][calc_key(from, to)] = ret;
    return ret;
}

int main(void)
{
    size_t res = 0;
    size_t total = 0;
    
    std::string str = "A^^^AvA<<A>>vvA"; //964 - 72
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        res += vectorize(str[idx], str[idx + 1], 0);
    total += res * 964;
    res = 0;
    
    str = "A<^^Av>A^^AvvvA"; //539 - 70
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        res += vectorize(str[idx], str[idx + 1], 0);
    total += res * 539;
    res = 0;
    
    str = "A<^^^AvvvA^>AvA"; //803 - 76
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        res += vectorize(str[idx], str[idx + 1], 0);
    total += res * 803;
    res = 0;

    str = "A^<<A^A^>>AvvvA"; //149 - 76
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        res += vectorize(str[idx], str[idx + 1], 0);
    total += res * 149;
    res = 0;
    
    str = "A^^^<<A>A>AvvvA"; //789 - 66
    for (size_t idx = 0; idx + 1 < str.size(); idx++)
        res += vectorize(str[idx], str[idx + 1], 0);
    total += res * 789;
    
    std::cout << total << std::endl;
}