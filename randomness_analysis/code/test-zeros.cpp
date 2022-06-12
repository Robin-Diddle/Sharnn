#include <iostream>
#include <fstream>
#include <random>
#include  <time.h>
#include <vector>
#include <bitset>

#include "../src/RNNHash.hpp"
#include "../include/define.h"

int main() {
    std::vector<unsigned long int>num(64);
    for(unsigned long int i=0;i<64;i++)
    {
    		num[i]=i;
    }
    std::default_random_engine random(time(NULL));
    std::uniform_int_distribution<int> dis1(0, 20);
    unsigned long int val {0};
    std::ofstream f {"zeros.out"};
    auto p {(char *) &val};
    for (int i = 0; i < 131072; ++i) {
        std::stringstream s;
        int cnt = dis1(random);
        random_shuffle(num.begin(),num.end());
        for(int j = 0;j<cnt;j++){
            val |= (unsigned long int)1<<num[j];
        }
        s << p[0] << p[1] << p[2] << p[3] << p[4] << p[5] << p[6] << p[7];
        RNNHash rnn_hash;
        auto out = rnn_hash(s);
        f << out.to_bytes();
        std::cout<<std::bitset<sizeof(val) * 8>(val)<<std::endl;
        val = 0;
    }
}