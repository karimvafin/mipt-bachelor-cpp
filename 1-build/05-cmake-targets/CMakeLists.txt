# Минимальная версия CMake, необходимая для проекта.
cmake_minimum_required(VERSION 3.20)
# Имя проекта и используемый язык.
project(cmake_targets LANGUAGES CXX)

# Определение статической библиотеки math и ее исходников.
add_library(math STATIC
    # Единственный исходник библиотеки.
    src/math/ops.cpp
)

# Публичные include-пути библиотеки (видны потребителям).
target_include_directories(math
    # Флаги apply к публичному интерфейсу.
    PUBLIC
        # Путь к заголовкам библиотеки.
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Требование стандарта C++20 для библиотеки.
target_compile_features(math PUBLIC cxx_std_20)

# Предупреждения только для библиотеки (не для потребителей).
target_compile_options(math PRIVATE -Wall -Wextra -Wpedantic)

# Определение исполняемой цели приложения.
add_executable(app src/main.cpp)

# Линковка приложения с библиотекой math.
target_link_libraries(app PRIVATE math)
