cmake_minimum_required(VERSION 3.14)
project(list_tasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(list_tests
    tasks.cpp
    tests.cpp
)

enable_testing()
add_test(NAME list_tests COMMAND list_tests)
