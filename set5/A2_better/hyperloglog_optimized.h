#pragma once
#include <vector>
#include <cstdint>

class HyperLogLogOptimized {
public:
    HyperLogLogOptimized(int B = 14);
    void add(unsigned int hash_val);
    double estimate() const;
    void reset();
    int memory_bytes() const;

private:
    uint8_t get_reg(int idx) const;
    void set_reg(int idx, uint8_t val);

    int B_, m_;
    double alpha_;
    std::vector<uint8_t> data_;
};
