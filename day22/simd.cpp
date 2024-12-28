/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:37:04 by mhuszar            #+#    #+#             */
/*   Updated: 2024/12/28 02:17:21 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>

size_t res = 0;

#define INPUT_LEN 2008

size_t *datastream[8]; //251 magic numbers in all of them

#define BOUNDARY ((INPUT_LEN / 8) + 1) //need to handle 3 stragglers in each of the datastreams, hence the padding

void alloc_streams()
{
    int idx = 0;
    while (idx < 8)
    {
        datastream[idx] = (size_t*)(aligned_alloc(32, BOUNDARY * sizeof(size_t)));
        if (!datastream[idx])
            std::cout << "aligned alloc failed for " << idx << std::endl;
        idx++;
    }
}

void parse_input()
{
    std::ifstream file("input.txt");
    int idx = 0;
    while (!file.eof())
    {
        for (int i = 0; i < 8; i++)
        {
            size_t next_num;
            file >> next_num;
            datastream[i][idx] = next_num;
        }
        idx++;
    }
    for (int i = 0; i < 8; i++)
        datastream[i][251] = 0; //need to zero out the padding
}

void avx()
{
    size_t mask = 16777215;
    for (size_t i = 0; i < BOUNDARY; i += 4)
    {
        __asm__ volatile (
            "vmovdqa (%0), %%ymm0;"
            "vmovdqa (%1), %%ymm1;"
            "vmovdqa (%2), %%ymm2;"
            "vmovdqa (%3), %%ymm3;"
            "vmovdqa (%4), %%ymm4;"
            "vmovdqa (%5), %%ymm5;"
            "vmovdqa (%6), %%ymm6;"
            "vmovdqa (%7), %%ymm7;"

            "vpbroadcastq %8, %%ymm15;"

            "vpsllq $6, %%ymm0, %%ymm8;"
            "vpxor %%ymm8, %%ymm0, %%ymm0;"
            "vpand %%ymm15, %%ymm0, %%ymm0;"
            "vpsrlq $5, %%ymm0, %%ymm8;"
            "vpxor %%ymm8, %%ymm0, %%ymm0;"
            "vpand %%ymm15, %%ymm0, %%ymm0;"
            "vpsllq $11, %%ymm0, %%ymm8;"
            "vpxor %%ymm8, %%ymm0, %%ymm0;"
            "vpand %%ymm15, %%ymm0, %%ymm0;"

            "vpsllq $6, %%ymm1, %%ymm9;"
            "vpxor %%ymm9, %%ymm1, %%ymm1;"
            "vpand %%ymm15, %%ymm1, %%ymm1;"
            "vpsrlq $5, %%ymm1, %%ymm9;"
            "vpxor %%ymm9, %%ymm1, %%ymm1;"
            "vpand %%ymm15, %%ymm1, %%ymm1;"
            "vpsllq $11, %%ymm1, %%ymm9;"
            "vpxor %%ymm9, %%ymm1, %%ymm1;"
            "vpand %%ymm15, %%ymm1, %%ymm1;"

            "vpsllq $6, %%ymm2, %%ymm10;"
            "vpxor %%ymm10, %%ymm2, %%ymm2;"
            "vpand %%ymm15, %%ymm2, %%ymm2;"
            "vpsrlq $5, %%ymm2, %%ymm10;"
            "vpxor %%ymm10, %%ymm2, %%ymm2;"
            "vpand %%ymm15, %%ymm2, %%ymm2;"
            "vpsllq $11, %%ymm2, %%ymm10;"
            "vpxor %%ymm10, %%ymm2, %%ymm2;"
            "vpand %%ymm15, %%ymm2, %%ymm2;"

            "vpsllq $6, %%ymm3, %%ymm11;"
            "vpxor %%ymm11, %%ymm3, %%ymm3;"
            "vpand %%ymm15, %%ymm3, %%ymm3;"
            "vpsrlq $5, %%ymm3, %%ymm11;"
            "vpxor %%ymm11, %%ymm3, %%ymm3;"
            "vpand %%ymm15, %%ymm3, %%ymm3;"
            "vpsllq $11, %%ymm3, %%ymm11;"
            "vpxor %%ymm11, %%ymm3, %%ymm3;"
            "vpand %%ymm15, %%ymm3, %%ymm3;"

            "vpsllq $6, %%ymm4, %%ymm12;"
            "vpxor %%ymm12, %%ymm4, %%ymm4;"
            "vpand %%ymm15, %%ymm4, %%ymm4;"
            "vpsrlq $5, %%ymm4, %%ymm12;"
            "vpxor %%ymm12, %%ymm4, %%ymm4;"
            "vpand %%ymm15, %%ymm4, %%ymm4;"
            "vpsllq $11, %%ymm4, %%ymm12;"
            "vpxor %%ymm12, %%ymm4, %%ymm4;"
            "vpand %%ymm15, %%ymm4, %%ymm4;"

            "vpsllq $6, %%ymm5, %%ymm13;"
            "vpxor %%ymm13, %%ymm5, %%ymm5;"
            "vpand %%ymm15, %%ymm5, %%ymm5;"
            "vpsrlq $5, %%ymm5, %%ymm13;"
            "vpxor %%ymm13, %%ymm5, %%ymm5;"
            "vpand %%ymm15, %%ymm5, %%ymm5;"
            "vpsllq $11, %%ymm5, %%ymm13;"
            "vpxor %%ymm13, %%ymm5, %%ymm5;"
            "vpand %%ymm15, %%ymm5, %%ymm5;"

            "vpsllq $6, %%ymm6, %%ymm14;"
            "vpxor %%ymm14, %%ymm6, %%ymm6;"
            "vpand %%ymm15, %%ymm6, %%ymm6;"
            "vpsrlq $5, %%ymm6, %%ymm14;"
            "vpxor %%ymm14, %%ymm6, %%ymm6;"
            "vpand %%ymm15, %%ymm6, %%ymm6;"
            "vpsllq $11, %%ymm6, %%ymm14;"
            "vpxor %%ymm14, %%ymm6, %%ymm6;"
            "vpand %%ymm15, %%ymm6, %%ymm6;"

            "vpsllq $6, %%ymm7, %%ymm14;"
            "vpxor %%ymm14, %%ymm7, %%ymm7;"
            "vpand %%ymm15, %%ymm7, %%ymm7;"
            "vpsrlq $5, %%ymm7, %%ymm14;"
            "vpxor %%ymm14, %%ymm7, %%ymm7;"
            "vpand %%ymm15, %%ymm7, %%ymm7;"
            "vpsllq $11, %%ymm7, %%ymm14;"
            "vpxor %%ymm14, %%ymm7, %%ymm7;"
            "vpand %%ymm15, %%ymm7, %%ymm7;"

            "vmovdqa %%ymm0, (%0);"
            "vmovdqa %%ymm1, (%1);"
            "vmovdqa %%ymm2, (%2);"
            "vmovdqa %%ymm3, (%3);"
            "vmovdqa %%ymm4, (%4);"
            "vmovdqa %%ymm5, (%5);"
            "vmovdqa %%ymm6, (%6);"
            "vmovdqa %%ymm7, (%7);"

            :
            : "r" (datastream[0] + i), "r" (datastream[1] + i), "r" (datastream[2] + i), "r" (datastream[3] + i), "r" (datastream[4] + i), "r" (datastream[5] + i), "r" (datastream[6] + i), "r" (datastream[7] + i), "r" (mask)
            : "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15", "memory"
        );
    }
}

void sum_datastreams()
{
    for (int idx = 0; idx < BOUNDARY; idx++)
    {
        for (int i = 0; i < 8; i++)
            res += datastream[i][idx];
    }
}

int main(void)
{
    alloc_streams();
    parse_input();
    for (int i = 0; i < 2000; i++)
        avx();
    sum_datastreams();
    std::cout << res << std::endl;
}