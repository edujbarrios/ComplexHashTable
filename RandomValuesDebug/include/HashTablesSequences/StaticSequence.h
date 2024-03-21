#pragma once
#include "Sequence.h"
#include <iostream>
#include <vector>
#include <stdexcept> // Para std::exception
#include <cstdlib>
#include <ctime>
#include <list>
#include <cstring>
#include <memory>
#include <type_traits> // Para std::is_same

template<class Key>
class StaticSequence : public Sequence<Key> {
    std::vector<Key> data;
    size_t maxSize;
public:
    StaticSequence(size_t size) : maxSize(size) {}

    bool search(const Key& k) const override {
        for (const Key& item : data) {
            if (item == k) return true;
        }
        return false;
    }

    bool insert(const Key& k) override {
        if (isFull() || search(k)) {
            throw std::invalid_argument("Value already inserted on the table");
        } else {
            data.push_back(k);
            return true;
        }
    }

    bool isFull() const override {
        return data.size() >= maxSize;
    }

    void showTable() const override {
        // Asumiendo que el blockSize está correctamente establecido.
        for (size_t i = 0; i < maxSize; ++i) {
            // Imprime los datos o espacios vacíos.
            std::cout << "[" << (i < data.size() ? std::to_string(data[i]) : "0") << "] ";
        }
    }
};
