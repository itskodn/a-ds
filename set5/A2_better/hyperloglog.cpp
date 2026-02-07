#include "hyperloglog.h"
#include <cmath>
#include <algorithm>

HyperLogLog::HyperLogLog(int B) {
    B_ = B;
    m_ = 1 << B;
    regs_ = std::vector<uint8_t>(m_, 0);
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

void HyperLogLog::add(unsigned int value) {
    int i = value >> (32 - B_);
    unsigned int w = value << B_;
    uint8_t rank = 1;
    for (int j = 0; j < 32 - B_; j++) {
        if (w & (1u << 31)) {
            break;
        }
        rank++;
        w <<= 1;
    }
    if (rank > regs_[i]) {
        regs_[i] = rank;
    }
}

double HyperLogLog::estimate() const {
    double sum = 0;
    for (int j = 0; j < m_; j++)
        sum += pow(2.0, -(double)regs_[j]);
    double E = alpha_ * m_ * m_ / sum;
    if (E <= 2.5 * m_) {
        int V = 0;
        for (int j = 0; j < m_; j++) {
            if (regs_[j] == 0) {
                V++;
            }
        }
        if (V > 0) {
            E = m_ * log(m_ / V);
        }
    }
    double temp = pow(2.0, 32);
    if (E > temp / 30.0) {
        E = -temp * log(1.0 - E / temp);
    }
    return E;
}

void HyperLogLog::reset() {
    std::fill(regs_.begin(), regs_.end(), 0);
}
