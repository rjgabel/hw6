#ifndef HASH_H
#define HASH_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261,
                            261934300};
    MyStringHash(bool debug = true) {
        if (false == debug) {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const {
        unsigned long long w[5] = {};

        // Convert string
        for (size_t i = 0; i < 5; i++) {
            unsigned long long a = 0;
            for (size_t j = 0; j < 6; j++) {
                int index = k.size() - (i + 1) * 6 + j;
                int x = (index >= 0) ? letterDigitToNumber(k[index]) : 0;
                a = a * 36 + x;
            }
            w[4 - i] = a;
        }

        // Hash string
        unsigned long long h = 0;
        for (size_t i = 0; i < 5; i++) {
            h += rValues[i] * w[i];
        }
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const {
        if ('a' <= letter && letter <= 'z') {
            return letter - 'a';
        } else if ('A' <= letter && letter <= 'Z') {
            return letter - 'A';
        } else if ('0' <= letter && letter <= '9') {
            return letter - '0' + 26;
        } else {
            throw std::exception();
        }
    }

    // Code to generate the random R values
    void generateRValues() {
        // obtain a seed from the system clock:
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(
            seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random
        // number
        for (int i{0}; i < 5; ++i) {
            rValues[i] = generator();
        }
    }
};

#endif
