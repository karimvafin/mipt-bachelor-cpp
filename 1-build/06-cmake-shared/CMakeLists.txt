# Минимальная версия CMake, необходимая для проекта.
cmake_minimum_required(VERSION 3.20)
# Имя проекта и используемый язык.
project(cmake_shared LANGUAGES CXX)

# Создание динамической библиотеки (shared library).
add_library(math SHARED
    # Исходник библиотеки.
    src/math/ops.cpp
)

# Публичные include-пути библиотеки.
target_include_directories(math
    # Настройки наследуются потребителями.
    PUBLIC
        # Путь к заголовкам.
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Требование стандарта C++20 для библиотеки.
target_compile_features(math PUBLIC cxx_std_20)

# Определение исполняемой цели приложения.
add_executable(app src/main.cpp)

# Линковка приложения с динамической библиотекой.
target_link_libraries(app PRIVATE math)

# Кладем библиотеку и бинарник в одну папку для удобного запуска.
set_target_properties(math app PROPERTIES
    # Папка для библиотеки.
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    # Папка для бинарника.
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# RPATH для удобного запуска из build (зависит от платформы).
if(APPLE)
    # @loader_path — папка исполняемого файла на macOS.
    set_target_properties(app PROPERTIES BUILD_RPATH "@loader_path")
else()
    # $ORIGIN — папка исполняемого файла на Linux/Unix.
    set_target_properties(app PROPERTIES BUILD_RPATH "$ORIGIN")
endif()
