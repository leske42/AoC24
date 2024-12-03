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
    res += (first * second);
    invalidate:
    return ;
}

bool switch_mode(size_t old_idx, std::string substr, bool res)
{
    size_t i = 0;
    old_idx = 0;
    while (1)
    {
        i = substr.find("do()", i);
        old_idx = substr.find("don't()", old_idx);
        if (i == std::string::npos && old_idx == std::string::npos)
            return res;
        if (i < old_idx)
        {
            res = true;
            if (old_idx == std::string::npos)
                return res;
            old_idx = i;
        }
        else
        {
            res = false;
            if (i == std::string::npos)
                return res;
            i = old_idx;
        }
    }
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
                enable = switch_mode(idx, line.substr(old_idx, idx - old_idx), enable);
            else
                break;
            idx += 4;
            if (enable)
                machine(line, idx, res);
        }
    }
    std::cout << res << std::endl;
}