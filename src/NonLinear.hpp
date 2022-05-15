#pragma once

#include "../include/define.h"
#include "ChaoticSystem.hpp"

template <int N, int O, typename std::enable_if<N % 5 == 0, bool>::type = true>
class NonLinear {
public:
    explicit NonLinear(int nr, ChaoticSystem *cs) : nr(nr), cs(cs) {
    }

    void forward(const uint32_t *input, uint32_t *output) {
        uint32_t h[2][8];
        for (int i = 0; i < 8; i++) {
            h[0][i] = h[1][i] = 0;
        }
        for (int i = 0; i < N; i++) {
            uint64_t mul = ((uint64_t) cs->next()) * input[i];
            mul ^= (mul >> 32);
            h[0][i % 5] ^= mul;
        }

        for (int i = 0; i < nr; i++) {
            nl_5to8(h[i % 2], h[(i + 1) % 2]);
        }
        for (int count = 0, i = 0; count < O; count += 8, i++) {
            int copy_count = std::min(8, O - count);
            std::copy_n(h[(i + nr) % 2], copy_count, output + count);
            nl_5to8(h[(i + nr) % 2], h[(i + nr + 1) % 2]);
        }
    }

private:
    int nr;
    ChaoticSystem *cs;
    void nl_5to8(uint32_t *d, uint32_t *h) {
        uint32_t t = ch(d[1], d[2], d[3]) ^ d[4] ^ sum_1(d[3]);
        h[0] = d[0] ^ t ^ maj(d[1], d[2], d[3]) ^ sum_0(d[1]);
        h[1] = t ^ d[0];
        h[2] = d[0] ^ d[1];
        h[3] = d[1] ^ d[2];
        h[4] = d[2] ^ d[3];
        h[5] = d[0] ^ d[1] ^ t;
        h[6] = d[1] ^ d[2] ^ t;
        h[7] = d[2] ^ d[3] ^ t;
    }
    void nl_8to8(uint32_t *d, uint32_t *h) {
        uint32_t t = d[7] + ch(d[4], d[5], d[6]) + sum_1(d[4]);
        uint32_t a = t + maj(d[0], d[1], d[2]) + sum_0(d[0]);
        h[7] = d[6];
        h[6] = d[5];
        h[5] = d[4];
        h[4] = d[3] + t;
        h[3] = d[2];
        h[2] = d[1];
        h[1] = d[0];
        h[0] = a;
    }
    static uint32_t maj(uint32_t a, uint32_t b, uint32_t c) {
        return (a & b) ^ (b & c) ^ (a & c);
    }
    static uint32_t ch(uint32_t a, uint32_t b, uint32_t c) {
        return (a & b) ^ (~a & c);
    }
    static uint32_t sum_0(uint32_t x) {
        return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
    }
    static uint32_t sum_1(uint32_t x) {
        return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
    }
    static uint32_t rotr(uint32_t x, uint32_t n) {
        return (x >> n) | (x << (32 - n));
    }
};