cmake_minimum_required(VERSION 3.14)
project(template_tasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(template_tests
    tests.cpp
)

# Запуск тестов через ctest: cd build && ctest --output-on-failure
enable_testing()
add_test(NAME template_tests COMMAND template_tests)
