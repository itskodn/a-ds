#pragma once
#include <vector>
#include <cstdint>

class HyperLogLog {
public:
    HyperLogLog(int B = 14);
    void add(unsigned int hash_val);
    double estimate() const;
    void reset();

private:
    int B_, m_;
    double alpha_;
    std::vector<uint8_t> regs_;
};
