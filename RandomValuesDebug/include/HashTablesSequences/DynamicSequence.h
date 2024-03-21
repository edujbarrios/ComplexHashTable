#pragma once
#include "Sequence.h"
#include <iostream>
#include <vector>
#include <stdexcept> // Para std::exception
#include <list>
#include <memory>
#include <type_traits> // Para std::is_same

template<class Key>
class DynamicSequence : public Sequence<Key> {
    std::list<Key> data;
public:
    bool search(const Key& k) const override {
        for (const Key& item : data) {
            if (item == k) return true;
        }
        return false;
    }

    bool insert(const Key& k) override {
        if (search(k)) {
            throw std::invalid_argument("Value already exists.");
        } else {
            data.push_back(k);
            return true;
        }
    }

    bool isFull() const override {
        return false; // DynamicSequence is never "full"
    }

    void showTable() const override {
        std::cout << "[ ";
        if (data.empty()) {
            std::cout << "0";
        } else {
            for (const auto& item : data) {
                std::cout << item << " ";
            }
        }
        std::cout << " ]";
    }
};
