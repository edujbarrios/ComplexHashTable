#include "StaticSequence.h"
#include "DynamicSequence.h"
#include "../DispersionFunctions/DispersionFunction.h"
#include "StaticSequence.h"
#include "StaticSequence.h"
#include "../ExplorationFunctions/ExplorationFunction.h"
#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>

#pragma once

template<class Key, class Container = StaticSequence<Key>>
class HashTable {
    std::vector<std::unique_ptr<Container>> table;
    DispersionFunction<Key>& fd;
    ExplorationFunction<Key>* fe = nullptr;
    unsigned tableSize;
    unsigned collisionCount = 0; // Contador de colisiones

public:
    HashTable(unsigned size, DispersionFunction<Key>& dispersionFunc, ExplorationFunction<Key>* explorationFunc = nullptr, unsigned blockSize = 0)
            : fd(dispersionFunc), fe(explorationFunc), tableSize(size) {
        for (unsigned i = 0; i < tableSize; ++i) {
            if constexpr (std::is_same<Container, DynamicSequence<Key>>::value) {
                table.emplace_back(std::make_unique<Container>());
            } else {
                table.emplace_back(std::make_unique<Container>(blockSize));
            }
        }
    }

    bool insert(const Key& key) {
        unsigned pos = fd(key);
        if (fe != nullptr) {
            unsigned attempt = 0;
            while (table[pos]->isFull() && attempt < tableSize) {
                pos = (fd(key) + (*fe)(key, ++attempt)) % tableSize;
                collisionCount++; // Incrementar el contador de colisiones
            }
        }
        std::cout << "\033[1;37m"; // Bold white
        table[pos]->insert(key);
        std::cout << "\033[0m"; // Reset color
        return true;
    }

    bool search(const Key& key) const {
        unsigned pos = fd(key);
        if (fe != nullptr) {
            unsigned attempt = 0;
            while (attempt < tableSize) {
                pos = (fd(key) + (*fe)(key, ++attempt)) % tableSize;
                if (table[pos]->search(key)) return true;
            }
            return false;
        }
        return table[pos]->search(key);
    }

    void showTable() const {
        std::cout << "\033[1;36m"; // Bold cyan
        std::cout << "Hash Table:\n";
        std::cout << "\033[0m"; // Reset color
        for (unsigned i = 0; i < tableSize; ++i) {
            std::cout << "\033[1;36m"; // Bold cyan
            std::cout << i << ")\t";  // Imprime el índice de la fila con un tabulador
            std::cout << "\033[0m"; // Reset color
            table[i]->showTable();    // Delega la impresión de la fila al contenedor
            std::cout << "\n";        // Nueva línea después de cada fila
        }
    }

    void printHelp() const {
        std::cout << "\033[1;36m"; // Bold cyan
        std::cout << "\n=== Hash Table Help ===\n";
        std::cout << "Options:\n";
        std::cout << "- Functions of Dispersion:\n";
        std::cout << "  1. Module (default)\n";
        std::cout << "  2. Sum\n";
        std::cout << "  3. Pseudorandom\n";
        std::cout << "- Functions of Exploration (only for closed hashing):\n";
        std::cout << "  1. Linear (default)\n";
        std::cout << "  2. Quadratic\n";
        std::cout << "  3. Double Dispersion\n";
        std::cout << "  4. Rediscovery\n";
        std::cout << "\nExample usage:\n";
        std::cout << "./executable -fd 2  -hash open\n";
        std::cout << "This sets the Sum dispersion function and Double Dispersion exploration function.\n";
        std::cout << "Hash type is open addressing.\n";
        std::cout << "\033[0m"; // Reset color
    }

void printCollisionCount() const {
    std::cout << "\033[1;33m"; // Establecer el color a amarillo en negrita
    std::cout << "Total collisions: " << collisionCount << std::endl;
    std::cout << "\033[0m"; // Restablecer el color
}
};

