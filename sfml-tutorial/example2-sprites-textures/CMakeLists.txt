cmake_minimum_required(VERSION 3.10)
project(Example2_SpritesTextures)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск SFML
find_package(SFML 3 COMPONENTS System Window Graphics QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Подключение библиотек SFML
if(TARGET SFML::System)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        SFML::System
        SFML::Window
        SFML::Graphics
    )
else()
    target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})
endif()

# Копирование ресурсов в build директорию
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
     FILES_MATCHING PATTERN "*.png" PATTERN "*.jpg" PATTERN "*.jpeg")
