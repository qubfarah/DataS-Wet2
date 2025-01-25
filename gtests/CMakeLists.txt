cmake_minimum_required(VERSION 3.10)
project(UnitTests)
enable_testing()


find_package(GTest REQUIRED)
include(GoogleTest)


# Add the executable
add_executable(UnitTests
        main.cpp

        tests/hashtable.cpp
        tests/hashtable2.cpp
        tests/unionfind.cpp
)

# Link the executable to Google Test
target_link_libraries(UnitTests PUBLIC GTest::gtest GTest::gmock GTest::gtest_main)

#target core
target_link_libraries(UnitTests PUBLIC core)

# Add include directories
include_directories(${GTEST_INCLUDE_DIRS})