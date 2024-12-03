#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>

void machine(std::string& str, size_t& idx, size_t& res)
{
    size_t first = atoi(str.c_str() + idx);
    size_t second = 0;
    while (isdigit(str[idx]))
        idx++;
    if (str[idx] != ',')
        goto invalidate;
    idx++;
    second = atoi(str.c_str() + idx);
    while (isdigit(str[idx]))
        idx++;
    if (str[idx] != ')')
        goto invalidate;
    idx++;
    // std::cout << "MULING " << first << " AND " << second << std::endl;
    res += (first * second);
    invalidate:
    return ;
}

int main(void)
{
    std::ifstream input("input.txt");
    size_t res = 0;
    std::string line;
    size_t idx;
    size_t old_idx;
    std::string substr;
    bool enable = true;
    bool over = false;
    while (!input.eof())
    {
        std::getline(input, line);
        idx = 0;
        while (idx < line.size())
        {
            old_idx = idx;
            idx = line.find("mul(", idx);
            if (idx != std::string::npos)
            {
                substr = line.substr(old_idx, idx - old_idx);
                std::cout << "substr is: " << substr << std::endl;
                size_t i = 0;
                old_idx = 0;
                over = false;
                while (!over)
                {
                    i = substr.find("do()", i);
                    old_idx = substr.find("don't()", old_idx);
                    if (i == std::string::npos || old_idx == std::string::npos)
                        over = true;
                    if (i == std::string::npos && old_idx == std::string::npos)
                        goto skip;
                    if (i < old_idx)
                    {
                        enable = true;
                        old_idx = i;
                    }
                    else
                    {
                        i = old_idx;
                        enable = false;
                    }

                }
                skip:
                idx += 4;
                if (enable)
                    machine(line, idx, res);
            }
            std::cout << "iter" << std::endl;
        }
    }
    std::cout << res << std::endl;
}