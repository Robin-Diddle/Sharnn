#include <cstdint>
#include <iostream>
#include <random>
#include <streambuf>
#include <fstream>

#include "../../src/RNNHash.hpp"

const int samples_num = 10000;

int main() {
    std::ifstream fin;
    fin.open("distinguish.input");    
    std::ofstream fout;
    fout.open("distinguish.output");
    std::string line;

    RNNHash::Out_t out;
    RNNHash rnn_hash;
    
    for(int i = 0; i < 2 * samples_num; i++){
        std::getline(fin, line);
        std::istringstream str{line};
        out = rnn_hash(str);
        fout << out.to_hex_string() << std::endl;

    }

    printf("Finish hash\n");
}