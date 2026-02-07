#include "stream.h"

static const std::string alf =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789-";

RandomStream::RandomStream(int size, int seed) {
    size_ = size;
    rng_ = std::mt19937(seed);
}

std::vector<std::string> RandomStream::generate() {
    std::vector<std::string> stream;
    stream.reserve(size_);
    std::uniform_int_distribution<int> len_dist(1, 30);
    std::uniform_int_distribution<int> char_dist(0, alf.size() - 1);
    for (int i = 0; i < size_; i++) {
        int len = len_dist(rng_);
        std::string s(len, ' ');
        for (int j = 0; j < len; j++)
            s[j] = alf[char_dist(rng_)];
        stream.push_back(s);
    }
    return stream;
}

std::vector<int> RandomStream::partition(int total, int step) {
    std::vector<int> steps;
    for (int p = step; p <= 100; p += step)
        steps.push_back(total*p / 100);
    if (steps.empty() || steps.back() != total)
        steps.push_back(total);
    return steps;
}


uint32_t HashFuncGen::HashFunc::operator()(const std::string& s) const {
    uint64_t h = 0, pw = 1;
    for (char c : s) {
        h += (unsigned char)c * pw;
        pw *= base;
    }
    h = h * a + b;
    uint32_t x = (uint32_t)(h ^ (h >> 32));
    x ^= x >> 16;
    x *= 0x85ebca6b;
    x ^= x >> 13;
    x *= 0xc2b2ae35;
    x ^= x >> 16;
    return x;
}

HashFuncGen::HashFuncGen(int seed) {
    rng_ = std::mt19937_64(seed);
}

HashFuncGen::HashFunc HashFuncGen::generate() {
    std::uniform_int_distribution<uint64_t> dist;
    HashFunc hf;
    hf.a = dist(rng_) | 1;
    hf.b = dist(rng_);
    hf.base = 257;
    return hf;
}
