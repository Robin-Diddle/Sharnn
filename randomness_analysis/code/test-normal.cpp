#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

#include "../src/RNNHash.hpp"
#include "../include/define.h"

int main() {
    std::mt19937_64 rng(time(NULL));
    unsigned long int val {rng()};
    std::ofstream f {"normal.out"};
    auto p {(char *) &val};
    for (int i = 0; i < 131072; ++i) {
        std::stringstream s;
        s << p[0] << p[1] << p[2] << p[3] << p[4] << p[5] << p[6] << p[7];
        RNNHash rnn_hash;
        auto out = rnn_hash(s);
        f << out.to_bytes();
        val = rng();
        std::cout<<std::bitset<sizeof(val) * 8>(val)<<std::endl;
    }
}
