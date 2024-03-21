#pragma once
#include "ExplorationFunction.h"

template<typename Key>
class LinearExplorationFunction : public ExplorationFunction<Key> {
public:
    unsigned operator()(const Key&, unsigned attempt) const override {
        return attempt;
    }
};