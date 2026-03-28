cmake_minimum_required(VERSION 3.14)
project(set_tasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(set_tests
    tasks.cpp
    tests.cpp
)

enable_testing()
add_test(NAME set_tests COMMAND set_tests)
