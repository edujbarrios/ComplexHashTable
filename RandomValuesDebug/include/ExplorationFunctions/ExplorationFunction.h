#pragma once
template<typename Key>
class ExplorationFunction {
public:
    virtual unsigned operator()(const Key&, unsigned) const = 0;
};
