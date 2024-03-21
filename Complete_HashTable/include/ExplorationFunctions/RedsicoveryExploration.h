#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include <cstring>
#include <memory>
#include <type_traits> // Para std::is_same
#include "ExplorationFunction.h"
#pragma once
template<typename Key>
class RediscoveryExplorationFunction : public ExplorationFunction<Key> {
public:
    unsigned operator()(const Key& key, unsigned attempt) const override {
        srand(static_cast<unsigned>(key) + attempt);
        return static_cast<unsigned>(rand());
    }
};