#pragma once
#include "ExplorationFunction.h"
#include "../DispersionFunctions/DispersionFunction.h"

template<typename Key>
class DoubleDispersionExplorationFunction : public ExplorationFunction<Key> {
    DispersionFunction<Key>& f;
public:
    DoubleDispersionExplorationFunction(DispersionFunction<Key>& func) : f(func)  {}
    unsigned operator()(const Key& key, unsigned attempt) const override {
        return f(key) * attempt;
    }
};
