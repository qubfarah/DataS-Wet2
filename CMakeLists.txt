cmake_minimum_required(VERSION 3.22)
project(DS_wet2_Winter_2024_2025)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(DS_wet2_Winter_2024_2025
        main.cpp
        plains25a2.cpp
        plains25a2.h
        wet2util.h
        Team.cpp
        Team.h
        Jockey.cpp
        Jockey.h
        DynamicArray.cpp
        UnionFind.cpp
        DynamicArray.h
        HashTable.h
        UnionFind.h
)
