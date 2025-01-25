cmake_minimum_required(VERSION 3.22)
project(DS_wet2_Winter_2024_2025)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")


add_library(core
        UnionFind.cpp
        HashTable.h
        UnionFind.h
        DoubleLinkedList.h
)

add_executable(DS_wet2_Winter_2024_2025
        main.cpp
        plains25a2.cpp
        plains25a2.h
        wet2util.h
        Team.cpp
        Team.h
        Jockey.cpp
        Jockey.h
)

target_link_libraries(DS_wet2_Winter_2024_2025 PUBLIC core)


add_subdirectory(gtests)