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
    while (!input.eof())
    {
        std::getline(input, line);
        idx = 0;
        while (idx < line.size())
        {
            idx = line.find("mul(", idx);
            if (idx != std::string::npos)
            {
                idx += 4;
                machine(line, idx, res);
            }
            // std::cout << idx << std::endl;
        }
        // std::cout << "BROKEN" << std::endl;
    }
    std::cout << res << std::endl;
}