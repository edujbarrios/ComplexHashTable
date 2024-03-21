
#pragma once
template<typename Key>
class DispersionFunction {
public:
    virtual unsigned operator()(const Key&) const = 0;
};