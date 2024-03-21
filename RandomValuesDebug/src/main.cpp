#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include <cstring>
#include <memory>
#include <type_traits> // Para std::is_same
#include "../include/NIF.h"
#include "../include/ExplorationFunctions/LinnearExploration.h"
#include "../include/ExplorationFunctions/QuadraticExploration.h"
#include "../include/DispersionFunctions/SumDispersion.h"
#include "../include/DispersionFunctions/PseudoRandomDispersion.h"
#include "../include/DispersionFunctions/ModuloDispersion.h"
#include "../include/ExplorationFunctions/DoubleDispersionExploration.h"
#include "../include/HashTablesSequences/DynamicSequence.h"
#include "../include/HashTablesSequences/StaticSequence.h"
#include "../include/HashTablesSequences/HashTable.h"
#include "../include/ExplorationFunctions/RedsicoveryExploration.h"

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <unistd.h> // For UNIX/Linux
#endif



// Función para establecer el color del texto a cian
void setCyanColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    #else
    std::cout << "\033[1;36m"; // Código de escape ANSI para color cian
    #endif
}

// Función para establecer el color del texto a azul
void setBlueColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
    #else
    std::cout << "\033[1;34m"; // Código de escape ANSI para color azul
    #endif
}

// Función para establecer el color del texto a amarillo
void setYellowColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    #else
    std::cout << "\033[1;33m"; // Código de escape ANSI para color amarillo
    #endif
}

// Función para establecer el color del texto a verde
void setGreenColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    #else
    std::cout << "\033[1;32m"; // Código de escape ANSI para color verde
    #endif
}

// Función para establecer el color del texto a rojo
void setRedColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    #else
    std::cout << "\033[1;31m"; // Código de escape ANSI para color rojo
    #endif
}

// Función para restablecer el color del texto al predeterminado
void resetColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    #else
    std::cout << "\033[0m"; // Código de escape ANSI para restablecer el color
    #endif
}

int main(int argc, char* argv[]) {

    unsigned tableSize = 10;
    unsigned blockSize = 3;
    std::string hashType = "close";
    int dispersionFunctionCode = 1;
    int explorationFunctionCode = 1;
    int numRandomNIFs = 0; // Número de NIFs aleatorios a generar

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-ts") == 0) {
            tableSize = std::atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-fd") == 0) {
            dispersionFunctionCode = std::atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-hash") == 0) {
            hashType = argv[i + 1];
        } else if (strcmp(argv[i], "-bs") == 0) {
            blockSize = std::atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-fe") == 0) {
            explorationFunctionCode = std::atoi(argv[i + 1]);
            //modificacion
        } else if (strcmp(argv[i], "-num") == 0) {
            numRandomNIFs = std::atoi(argv[i + 1]);
        }
    }

    ModuleDispersionFunction<NIF> moduleDF(tableSize);
    SumDispersionFunction<NIF> sumDF(tableSize);
    PseudorandomDispersionFunction<NIF> pseudoDF(tableSize);

    LinearExplorationFunction<NIF> linearEF;
    QuadraticExplorationFunction<NIF> quadraticEF;
    DoubleDispersionExplorationFunction<NIF> doubleDF(moduleDF);
    RediscoveryExplorationFunction<NIF> rediscoveryEF;

    DispersionFunction<NIF>* df = &moduleDF;
    switch (dispersionFunctionCode) {
        case 2: df = &sumDF; break;
        case 3: df = &pseudoDF; break;
    }

    ExplorationFunction<NIF>* ef = nullptr;
    if (hashType == "close") {
        switch (explorationFunctionCode) {
            case 1: ef = &linearEF; break;
            case 2: ef = &quadraticEF; break;
            case 3: ef = &doubleDF; break;
            case 4: ef = &rediscoveryEF; break;
        }
    } else {
        if (explorationFunctionCode != 1 || blockSize != 3) {
            throw std::invalid_argument("Exploration function or block size are not applicable for open hashing.");
        }
    }

    if (hashType == "open") {
        HashTable<NIF, DynamicSequence<NIF>> hashTableOpen(tableSize, *df);
        int explorationCalls = 0; // Contador de llamadas a la función de exploración
        int overflowCount = 0; // Contador de desbordamientos
        if (numRandomNIFs > 0) {
            for (int i = 0; i < numRandomNIFs; ++i) {
                NIF randomNIF;
                explorationCalls += hashTableOpen.insert(randomNIF);
            
            }
            std::cout << "\n\033[1;33m - Inserted " << numRandomNIFs << " random NIFs into the hash table.\033[0m\n";
            hashTableOpen.printCollisionCount(); // Imprime el contador de colisiones
            hashTableOpen.showTable();
        }
    } else {
        HashTable<NIF, StaticSequence<NIF>> hashTableClosed(tableSize, *df, ef, blockSize);
        int explorationCalls = 0; // Contador de llamadas a la función de exploración
        int overflowCount = 0; // Contador de desbordamientos
        if (numRandomNIFs > 0) {
            for (int i = 0; i < numRandomNIFs; ++i) {
                NIF randomNIF;
                explorationCalls += hashTableClosed.insert(randomNIF);
            }
            std::cout << "\033[1;33mInserted " << numRandomNIFs << " random NIFs into the hash table.\033[0m\n";
            hashTableClosed.printCollisionCount(); // Imprime el contador de colisiones
            hashTableClosed.showTable();
        }
    }

    return 0;
}
