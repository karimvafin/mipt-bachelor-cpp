cmake_minimum_required(VERSION 3.14)
project(unordered_map_tasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(unordered_map_tests
    tasks.cpp
    tests.cpp
)

enable_testing()
add_test(NAME unordered_map_tests COMMAND unordered_map_tests)
