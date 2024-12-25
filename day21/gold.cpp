/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:57:00 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/25 18:44:53 by mhuszar          ###   ########.fr       */
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
            case '<':
                return ("v<A");
            case 'v':
                return ("vA");
            case '>':
                return ("v>A");
            case 'A':
                return (">A");
        }
    }

    else if (from == '<')
    {
        switch (to)
        {
            case '^':
                return (">^A");
            case '<':
                return ("A");
            case 'v':
                return (">A");
            case '>':
                return (">>A");
            case 'A':
                return (">>^A");
        }
    }

    else if (from == 'v')
    {
        switch (to)
        {
            case '^':
                return ("^A");
            case '<':
                return ("<A");
            case 'v':
                return ("A");
            case '>':
                return (">A");
            case 'A':
                return ("^>A");
        }
    }

    else if (from == '>')
    {
        switch (to)
        {
            case '^':
                return ("<^A");
            case '<':
                return ("<<A");
            case 'v':
                return ("<A");
            case '>':
                return ("A");
            case 'A':
                return ("^A");
        }
    }

    else if (from == 'A')
    {
        switch (to)
        {
            case '^':
                return ("<A");
            case '<':
                return ("v<<A");
            case 'v':
                return ("<vA");
            case '>':
                return ("vA");
            case 'A':
                return ("A");
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

/*
L* has two main rules:
Rule of Grouping dictates that if you can execute similar moves consecutively, then do so (so as to be able to spam A later)
Rule of Left dictates that if you can press two keys in any order, give precedence to the one with the leftmost position
This is because on 1 depth more you will have to move left to reach that one -->
This means on 2 depths more you will have to reach the "<" ("left") button -->
And you want to do that before anything else (from the position of "A") so you can group your moves ("v<<")
So Rule of Left serves Rule of Grouping
*/
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