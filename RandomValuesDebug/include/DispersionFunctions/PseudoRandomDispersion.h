#pragma once
#include "DispersionFunction.h"
#include <iostream>
#include <cstdlib>


template<typename Key>
class PseudorandomDispersionFunction : public DispersionFunction<Key> {
    unsigned tableSize;
public:
    PseudorandomDispersionFunction(unsigned size) : tableSize(size) {}
    unsigned operator()(const Key& key) const override {
        srand((key));
        return rand() % tableSize;
    }
};

