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

// Function to set text color to cyan
void setCyanColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    #else
    std::cout << "\033[1;36m"; // ANSI escape code for cyan color
    #endif
}

// Function to set text color to blue
void setBlueColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
    #else
    std::cout << "\033[1;34m"; // ANSI escape code for blue color
    #endif
}

// Function to set text color to yellow
void setYellowColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    #else
    std::cout << "\033[1;33m"; // ANSI escape code for yellow color
    #endif
}

// Function to set text color to green
void setGreenColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    #else
    std::cout << "\033[1;32m"; // ANSI escape code for green color
    #endif
}

// Function to set text color to red
void setRedColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    #else
    std::cout << "\033[1;31m"; // ANSI escape code for red color
    #endif
}

// Function to reset text color to default
void resetColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    #else
    std::cout << "\033[0m"; // ANSI escape code to reset color
    #endif
}

template<typename HashTableType>
void runMenu(HashTableType& hashTable) {
    char option;
    do {
        setBlueColor();
        std::cout << "\nHash Table Menu\n";
        resetColor();
        setYellowColor();
        std::cout << "1. Insert NIF\n";
        std::cout << "2. Search NIF\n";
        std::cout << "3. Show Table\n";
        std::cout << "4. Usage\n";
        std::cout << "5. Generate and insert random NIF\n";
        std::cout << "6. Exit\n"; 
        resetColor();
        setGreenColor();
        std::cout << "Select an option: ";
        resetColor();
        std::cin >> option;

        switch (option) {
            case '1': {
                try {
                    std::cout << "Enter NIF to insert: ";
                    long nifNumber;
                    std::cin >> nifNumber;
                    NIF nif(nifNumber);
                    if (hashTable.insert(nif)) {
                        setGreenColor();
                        std::cout << "NIF inserted successfully.\n";
                    } else {
                        setRedColor();
                        std::cout << "Failed to insert NIF.\n";
                    }
                    resetColor();
                } catch (const std::invalid_argument& e) {
                    setRedColor();
                    std::cerr << "Error: " << e.what() << std::endl;
                    resetColor();
                }
                break;
            }
            case '2': {
                std::cout << "Enter NIF to search: ";
                long nifNumber;
                std::cin >> nifNumber;
                NIF nif(nifNumber);
                if (hashTable.search(nif)) {
                    setGreenColor();
                    std::cout << "NIF found.\n";
                } else {
                    setRedColor();
                    std::cout << "NIF not found.\n";
                }
                resetColor();
                break;
            }
            case '3':
                hashTable.showTable();
                break;
            case '4':
                hashTable.printHelp();
                break;
            case '5': {
                NIF randomNIF;
                if (hashTable.insert(randomNIF)) {
                    setGreenColor();
                    std::cout << "Random NIF inserted successfully: " << randomNIF << "\n";
                } else {
                    setRedColor();
                    std::cout << "Failed to insert random NIF.\n";
                }
                resetColor();
                break;
            }
            case '6':
                std::cout << "Exiting...\n";
                break;
            default:
                setRedColor();
                std::cout << "Invalid option. Please try again.\n";
                resetColor();
        }
    } while (option != '6');
}

int main(int argc, char* argv[]) {

    //PreCharged information for  Clion Automatic Execution usage 
    unsigned tableSize = 10;
    unsigned blockSize = 3;
    std::string hashType = "close";
    int dispersionFunctionCode = 1;
    int explorationFunctionCode = 1;

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
        }
    }

    ModuleDispersionFunction<NIF> moduleDF(tableSize);
    SumDispersionFunction<NIF> sumDF(tableSize);
    PseudorandomDispersionFunction<NIF> pseudoDF(tableSize);

    LinearExplorationFunction<NIF> linearEF;
    QuadraticExplorationFunction<NIF> quadraticEF;
    DoubleDispersionExplorationFunction<NIF> doubleDF(moduleDF); // Assuming moduleDF for simplicity
    RediscoveryExplorationFunction<NIF> rediscoveryEF;

    DispersionFunction<NIF>* df = &moduleDF; // Default
    switch (dispersionFunctionCode) {
        case 2: df = &sumDF; break;
        case 3: df = &pseudoDF; break;
    }

    ExplorationFunction<NIF>* ef = nullptr; // Only for closed hashing
    if (hashType == "close") {
        switch (explorationFunctionCode) {
            case 1: ef = &linearEF; break;
            case 2: ef = &quadraticEF; break;
            case 3: ef = &doubleDF; break;
            case 4: ef = &rediscoveryEF; break;
        }
    } else {
        // Throw exception if attempting to use exploration function or block size with open hashing
        if (explorationFunctionCode != 1 || blockSize != 3) {
            throw std::invalid_argument("Exploration function or block size are not applicable for open hashing.");
        }
    }
    if (hashType == "open") {
        HashTable<NIF, DynamicSequence<NIF>> hashTableOpen(tableSize, *df);
        runMenu(hashTableOpen);
    } else { // Closed by default
        HashTable<NIF, StaticSequence<NIF>> hashTableClosed(tableSize, *df, ef, blockSize);
        runMenu(hashTableClosed);
    }

    return 0;
}
