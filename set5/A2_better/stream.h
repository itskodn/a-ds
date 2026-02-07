#pragma once
#include <vector>
#include <string>
#include <random>
#include <cstdint>

class RandomStream {
public:
    RandomStream(int size, int seed = 42);
    std::vector<std::string> generate();
    static std::vector<int> partition(int total, int step_pct = 10);

private:
    int size_;
    std::mt19937 rng_;
};

class HashFuncGen {
public:
    struct HashFunc {
        uint64_t a, b, base;
        uint32_t operator()(const std::string& s) const;
    };

    HashFuncGen(int seed = 123);
    HashFunc generate();

private:
    std::mt19937_64 rng_;
};
