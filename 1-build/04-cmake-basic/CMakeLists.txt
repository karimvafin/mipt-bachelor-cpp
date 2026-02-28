# Минимальная версия CMake, необходимая для проекта.
cmake_minimum_required(VERSION 3.20)
# Имя проекта и используемый язык.
project(cmake_basic LANGUAGES CXX)

# Определение исполняемой цели и ее исходников.
add_executable(hello main.cpp)

# Требование стандарта C++20 для цели hello.
target_compile_features(hello PRIVATE cxx_std_20)

# message(${CMAKE_CURRENT_SOURCE_DIR})
