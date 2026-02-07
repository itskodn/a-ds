#include "hyperloglog_optimized.h"
#include <cmath>
#include <algorithm>

HyperLogLogOptimized::HyperLogLogOptimized(int B) {
    B_ = B;
    m_ = 1 << B;
    data_.assign((m_ / 4) * 3, 0);
    if (m_ == 16) {
        alpha_ = 0.673;
    } else if (m_ == 32) {
        alpha_ = 0.697;
    } else if (m_ == 64) {
        alpha_ = 0.709;
    } else {
        alpha_ = 0.7213 / (1.0 + 1.079 / m_);
    }
}

uint8_t HyperLogLogOptimized::get_reg(int idx) const {
    int group = idx / 4;
    int pos = idx % 4;
    int base = group * 3;
    if (pos == 0) {
        return data_[base] >> 2;
    }
    if (pos == 1) {
        return ((data_[base] & 0x03) << 4) | (data_[base+1] >> 4);
    }
    if (pos == 2) {
        return ((data_[base+1] & 0x0F) << 2) | (data_[base+2] >> 6);
    }
    if (pos == 3) {
        return data_[base+2] & 0x3F;
    }
    return 0;
}

void HyperLogLogOptimized::set_reg(int i, uint8_t val) {
    int group = i / 4;
    int pos = i % 4;
    int base = group * 3;
    val = val & 0x3F;
    if (pos == 0) {
        data_[base] = (val << 2)|(data_[base] & 0x03);
    } else if (pos == 1) {
        data_[base] = (data_[base] & 0xFC)|(val >> 4);
        data_[base+1] = (val << 4) | (data_[base+1] & 0x0F);
    } else if (pos == 2) {
        data_[base+1] = (data_[base+1] & 0xF0) | (val >> 2);
        data_[base+2] = (val << 6) | (data_[base+2] & 0x3F);
    } else if (pos == 3) {
        data_[base+2] = (data_[base+2] & 0xC0) | val;
    }
}

void HyperLogLogOptimized::add(unsigned int hash_val) {
    int idx = hash_val >> (32 - B_);
    unsigned int w = hash_val << B_;
    uint8_t rho = 1;
    for (int j = 0; j < 32 - B_; j++) {
        if (w & (1u << 31)) break;
        rho++;
        w <<= 1;
    }
    if (rho > get_reg(idx))
        set_reg(idx, rho);
}

double HyperLogLogOptimized::estimate() const {
    double sum = 0;
    for (int j = 0; j < m_; j++)
        sum += pow(2.0, -(double)get_reg(j));
    double E = alpha_ * m_ * m_ / sum;

    if (E <= 2.5 * m_) {
        int V = 0;
        for (int j = 0; j < m_; j++)
            if (get_reg(j) == 0) {
                V++;
            }
        if (V > 0) {
            E = m_ * log((double)m_ / V);
        }
    }
    double two32 = pow(2.0, 32);
    if (E > two32 / 30.0) {
        E = -two32 * log(1.0 - E / two32);
    }
    return E;
}

void HyperLogLogOptimized::reset() {
    std::fill(data_.begin(), data_.end(), 0);
}

int HyperLogLogOptimized::memory_bytes() const {
    return (int)data_.size();
}
