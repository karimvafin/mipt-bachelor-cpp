cmake_minimum_required(VERSION 3.14)
project(vector_tasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vector_tests
    tasks.cpp
    tests.cpp
)

# Запуск тестов через ctest: cd build && ctest --output-on-failure
enable_testing()
add_test(NAME vector_tests COMMAND vector_tests)
