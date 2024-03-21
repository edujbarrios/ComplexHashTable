#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept> // Para std::invalid_argument

class NIF {
    long nifNumber;

public:
    NIF() {
        generateRandomNIF();
    }

    NIF(long nif) : nifNumber(nif) {
        if (countDigits(nif) != 8) {
            throw std::invalid_argument("NIF must have exactly 8 digits.");
        }
    }

    bool operator==(const NIF& other) const {
        return nifNumber == other.nifNumber;
    }

    operator long() const {
        return nifNumber;
    }

    friend std::ostream& operator<<(std::ostream& os, const NIF& nif) {
        os << nif.nifNumber;
        return os;
    }

private:
    int countDigits(long number) const {
        int count = 0;
        while (number != 0) {
            number /= 10;
            ++count;
        }
        return count;
    }

    void generateRandomNIF() {
        //srand original ya no es neceasario
        nifNumber = 10000000 + std::rand() % 90000000; // Genera un número aleatorio de 8 dígitos
    }
};

