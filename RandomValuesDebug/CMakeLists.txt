cmake_minimum_required(VERSION 3.27)
project(zzzzz_copia)

set(CMAKE_CXX_STANDARD 14)

add_executable(zzzzz_copia
        src/main.cpp
        include/NIF.h
        include/DispersionFunctions/DispersionFunction.h
        include/DispersionFunctions/ModuloDispersion.h
        include/DispersionFunctions/SumDispersion.h
        include/DispersionFunctions/PseudoRandomDispersion.h
        include/ExplorationFunctions/ExplorationFunction.h
        include/ExplorationFunctions/LinnearExploration.h
        include/ExplorationFunctions/QuadraticExploration.h
        include/ExplorationFunctions/DoubleDispersionExploration.h
        include/ExplorationFunctions/RedsicoveryExploration.h
        include/HashTablesSequences/Sequence.h
        include/HashTablesSequences/DynamicSequence.h
        include/HashTablesSequences/StaticSequence.h
        include/HashTablesSequences/HashTable.h
)
