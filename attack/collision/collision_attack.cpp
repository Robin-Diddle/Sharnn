#include <cstdint>
#include <iostream>
#include <random>
#include <streambuf>
#include <map>

#include "../../src/RNNHash.hpp"

const int collision_len = 10;
const int iter_num = 1 << 25;
const int data_size = 10;
uint8_t data[data_size];

struct membuf : std::streambuf {
    membuf(char *begin, uint32_t size) {
        this->setg(begin, begin, begin + size);
    }
};

uint32_t random_number(uint32_t rand_max, uint32_t rand_min = 0) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist(
        0, 0xFFFFFFFF);
    return dist(rng) % (rand_max-rand_min) + rand_min;
}

void print_data(uint8_t *data) {
    for (int i = 0; i < data_size; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
                  << (uint32_t) data[i];
    }
    std::cout << std::endl;
}

int main() {
    std::map<std::string, std::string> hash2str;
    RNNHash::Out_t out;
    RNNHash h;

    for (int i = 0; i < iter_num; i++) {
        for (uint8_t &i : data) {
            i = random_number(126, 48);
        }
        std::string str = std::string(reinterpret_cast<char *>(data), data_size);
        // std::cout << "input: " << str << std::endl;
        std::istringstream input{str};
        out = h(input);
        std::string key = out.to_hex_string().substr(0, collision_len);
        // std::cout << "hash: " << out.to_hex_string() << std::endl;
        // std::cout << "key:" << key << std::endl;
        auto it = hash2str.find(key);
        if(it != hash2str.end()){
            print_data((uint8_t*)(it->second.c_str()));
            print_data(data);
            std::cout << it->second << std::endl;
            std::cout << str << std::endl;
            break;
        }
        hash2str[key] = str;
    }

    printf("Find collision in first %d bits\n", collision_len << 2);
}