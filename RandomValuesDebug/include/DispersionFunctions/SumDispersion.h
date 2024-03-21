#pragma once
#include "DispersionFunction.h"

template<typename Key>
class SumDispersionFunction : public DispersionFunction<Key> {
    unsigned tableSize;
public:
    SumDispersionFunction(unsigned size) : tableSize(size) {}
    unsigned operator()(const Key& key) const override {
        unsigned sum = 0;
        long temp = key;
        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }
        return sum % tableSize;
    }
};
