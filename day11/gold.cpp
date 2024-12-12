/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:21:47 by mhuszar           #+#    #+#             */
/*   Updated: 2024/12/12 02:06:42 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>

typedef std::vector<size_t> Vec;
size_t res = 0;

#define ITER 75

size_t numbers[10][ITER + 1] = {0};

static inline void __attribute__ ((always_inline)) jmp_zeroes()
{
    int n = ITER;
    while (n > 1)
    {
        numbers[1][n - 1] += numbers[0][n];
        numbers[0][n] = 0;
        n--;
    }
    res += numbers[0][1];
    numbers[0][1] = 0;
    res += numbers[0][0];
    numbers[0][0] = 0;
}

static inline void __attribute__ ((always_inline)) jmp_ones()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[1][n];
                break;
            case 1:
                res += numbers[1][n];
                break;
            case 2:
                res += numbers[1][n] << 1;
                break;
            default:
            {
                numbers[2][n - 3] += numbers[1][n] << 1;
                numbers[0][n - 3] += numbers[1][n];
                numbers[4][n - 3] += numbers[1][n];
            }
        }
        numbers[1][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_twos()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[2][n];
                break;
            case 1:
                res += numbers[2][n];
                break;
            case 2:
                res += numbers[2][n] << 1;
                break;
            default:
            {
                numbers[4][n - 3] += numbers[2][n] << 1;
                numbers[0][n - 3] += numbers[2][n];
                numbers[8][n - 3] += numbers[2][n];
            }
        }
        numbers[2][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_threes()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[3][n];
                break;
            case 1:
                res += numbers[3][n];
                break;
            case 2:
                res += numbers[3][n] << 1;
                break;
            default:
            {
                numbers[6][n - 3] += numbers[3][n];
                numbers[0][n - 3] += numbers[3][n];
                numbers[7][n - 3] += numbers[3][n];
                numbers[2][n - 3] += numbers[3][n];
            }
        }
        numbers[3][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_fours()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[4][n];
                break;
            case 1:
                res += numbers[4][n];
                break;
            case 2:
                res += numbers[4][n] << 1;
                break;
            default:
            {
                numbers[8][n - 3] += numbers[4][n];
                numbers[0][n - 3] += numbers[4][n];
                numbers[9][n - 3] += numbers[4][n];
                numbers[6][n - 3] += numbers[4][n];
            }
        }
        numbers[4][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_fives()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[5][n];
                break;
            case 1:
                res += numbers[5][n];
                break;
            case 2:
                res += numbers[5][n];
                break;
            case 3:
                res += numbers[5][n] << 1;
                break;
            case 4:
                res += numbers[5][n] << 2;
                break;
            default:
            {
                numbers[2][n - 5] += numbers[5][n] << 1;
                numbers[0][n - 5] += numbers[5][n] << 1;
                numbers[8][n - 5] += (numbers[5][n] << 2) - numbers[5][n];
                numbers[4][n - 5] += numbers[5][n];
            }
        }
        numbers[5][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_sixes()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[6][n];
                break;
            case 1:
                res += numbers[6][n];
                break;
            case 2:
                res += numbers[6][n];
                break;
            case 3:
                res += numbers[6][n] << 1;
                break;
            case 4:
                res += numbers[6][n] << 2;
                break;
            default:
            {
                numbers[4][n - 5] += numbers[6][n] << 1;
                numbers[5][n - 5] += numbers[6][n] << 1;
                numbers[2][n - 5] += numbers[6][n];
                numbers[7][n - 5] += numbers[6][n];
                numbers[9][n - 5] += numbers[6][n];
                numbers[6][n - 5] += numbers[6][n];
            }
        }
        numbers[6][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_sevens()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[7][n];
                break;
            case 1:
                res += numbers[7][n];
                break;
            case 2:
                res += numbers[7][n];
                break;
            case 3:
                res += numbers[7][n] << 1;
                break;
            case 4:
                res += numbers[7][n] << 2;
                break;
            default:
            {
                numbers[2][n - 5] += numbers[7][n] << 1;
                numbers[6][n - 5] += numbers[7][n] << 1;
                numbers[8][n - 5] += numbers[7][n];
                numbers[7][n - 5] += numbers[7][n];
                numbers[0][n - 5] += numbers[7][n];
                numbers[3][n - 5] += numbers[7][n];
            }
        }
        numbers[7][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_eights()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[8][n];
                break;
            case 1:
                res += numbers[8][n];
                break;
            case 2:
                res += numbers[8][n];
                break;
            case 3:
                res += numbers[8][n] << 1;
                break;
            case 4:
                res += numbers[8][n] << 2;
                break;
            default:
            {
                numbers[2][n - 5] += numbers[8][n] << 1;
                numbers[7][n - 5] += numbers[8][n] << 1;
                numbers[8][n - 4] += numbers[8][n];
                numbers[6][n - 5] += numbers[8][n];
                numbers[3][n - 5] += numbers[8][n];
            }
        }
        numbers[8][n] = 0;
        n--;
    }
}

static inline void __attribute__ ((always_inline)) jmp_nines()
{
    int n = ITER;
    while (n >= 0)
    {
        switch (n)
        {
            case 0:
                res += numbers[9][n];
                break;
            case 1:
                res += numbers[9][n];
                break;
            case 2:
                res += numbers[9][n];
                break;
            case 3:
                res += numbers[9][n] << 1;
                break;
            case 4:
                res += numbers[9][n] << 2;
                break;
            default:
            {
                numbers[6][n - 5] += numbers[9][n] << 1;
                numbers[8][n - 5] += numbers[9][n] << 1;
                numbers[9][n - 5] += numbers[9][n];
                numbers[1][n - 5] += numbers[9][n];
                numbers[4][n - 5] += numbers[9][n];
                numbers[3][n - 5] += numbers[9][n];
            }
        }
        numbers[9][n] = 0;
        n--;
    }
}

static inline bool __attribute__ ((always_inline)) avx()
{
    const size_t *data = (const size_t *)numbers;
    for (size_t i = 0; i < (ITER + 1) * 10; i += 4)
    {
        bool result = false;
        __asm__ (
            "vmovdqu (%1), %%ymm0;"
            "vptest %%ymm0, %%ymm0;"
            "setnz %%cl;"
            : "=c" (result)
            : "r" (data + i)
            : "ymm0", "memory"
        );
        if (result)
            return false;
    }
    return true;
}

static inline void __attribute__ ((always_inline)) kill_digits()
{
    int ctr = 0;
    while (!avx())
    {
        jmp_zeroes();
        jmp_ones();
        jmp_twos();
        jmp_threes();
        jmp_fours();
        jmp_fives();
        jmp_sixes();
        jmp_sevens();
        jmp_eights();
        jmp_nines();
    }
}

static inline void __attribute__ ((always_inline)) replace_dummies(Vec& vec)
{
    int i = 0;
    while (i < vec.size())
    {
        if (vec[i] == -1)
            vec.erase(vec.begin() + i);
        else
            i++;
    }
}

static inline bool __attribute__ ((always_inline)) remove_digit(Vec& vec, int idx, int lives)
{
    if (vec[idx] >= 10)
        return false;
    numbers[vec[idx]][lives] += 1;
    vec[idx] = -1;
    return true;
}

static inline bool __attribute__ ((always_inline)) split_stone(Vec& vec, size_t& idx)
{
    size_t num = vec[idx];
    size_t digits = std::log10(num) + 1;
    if (digits % 2 == 1)
        return false;
    vec[idx] = num % (size_t)pow(10, (digits / 2));
    vec.insert(vec.begin() + idx, num / (size_t)pow(10, (digits / 2)));
    idx++;
    return true;
}

static inline void __attribute__ ((always_inline)) multiply(size_t& num)
{
    num = (num << 11) - (num << 3) - (num << 3) - (num << 3);
}

static inline void __attribute__ ((always_inline)) transform_vec(Vec &vec, int lives)
{
    size_t i = 0;
    while (i < vec.size())
    {
        if (!remove_digit(vec, i, lives) && !split_stone(vec, i))
            multiply(vec[i]);
        i++;
    }
    replace_dummies(vec);
}

// void print_vec(Vec& vec)
// {
//     int i = 0;
//     std::cout << "VEC CONTENT: ";
//     while (i < vec.size())
//         std::cout << vec[i++] << " ";
//     std::cout << std::endl;
// }

static inline void __attribute__ ((always_inline)) parse_input()
{
    std::ifstream file("input.txt");
    size_t num;
    while (file >> num)
    {
        Vec tiny;
        tiny.push_back(num);
        for (int i = 0; i < ITER; i++)
            transform_vec(tiny, ITER - i);
        res += tiny.size();
        kill_digits();
        std::cout << "done with one num" << std::endl;
    }
}

int main(void)
{
    parse_input();
    std::cout << res << std::endl;
}
