#pragma once
#include "DispersionFunction.h"

template<typename Key>
class ModuleDispersionFunction : public DispersionFunction<Key> {
    unsigned tableSize;
public:
    ModuleDispersionFunction(unsigned size) : tableSize(size) {}
    unsigned operator()(const Key& key) const override {
        return static_cast<unsigned>(key) % tableSize;
    }
};