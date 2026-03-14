# SFML Tutorial - Полное руководство по работе с SFML

## 📋 Содержание

1. [Установка SFML](#установка-sfml)
2. [Пример 1: Базовое окно](#пример-1-базовое-окно)
3. [Пример 2: Текстуры и спрайты](#пример-2-текстуры-и-спрайты)
4. [Пример 3: Создание кнопок](#пример-3-создание-кнопок)

## 🚀 Установка SFML

### macOS (через Homebrew)

```bash
brew install sfml
```

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

### Windows

#### Вариант 1: Сборка из исходников (рекомендуется)

1. **Установите необходимые инструменты:**
   - [CMake](https://cmake.org/download/) (версия 3.10 или выше)
   - [Git](https://git-scm.com/download/win)
   - Компилятор C++:
     - **Visual Studio 2019/2022** (Community Edition бесплатна) с компонентами "Desktop development with C++"
     - Или **MinGW-w64** (через [MSYS2](https://www.msys2.org/))

2. **Скачайте исходники SFML:**
   ```bash
   git clone https://github.com/SFML/SFML.git
   cd SFML
   ```

3. **Соберите SFML:**
   ```bash
   # Создайте директорию для сборки
   mkdir build
   cd build
   
   # Для Visual Studio
   cmake .. -G "Visual Studio 17 2022" -A x64
   cmake --build . --config Release
   
   # Или для MinGW
   cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

4. **Установите SFML (опционально):**
   ```bash
   cmake --install . --prefix C:/SFML
   ```

#### Вариант 2: Готовые бинарники

1. **Скачайте SFML:**
   - Перейдите на https://www.sfml-dev.org/download.php
   - Выберите версию для вашего компилятора:
     - **SFML 3.x.x - Visual C++ 17 (2022) - 64-bit** (для Visual Studio 2022)
     - **SFML 3.x.x - MinGW 13.2.0 (SEH) - 64-bit** (для MinGW)
     - Или **SFML 2.6.x** для более старых версий компиляторов

2. **Распакуйте архив:**
   - Рекомендуется распаковать в `C:\SFML` или `C:\Libraries\SFML`
   - Структура должна быть: `C:\SFML\lib`, `C:\SFML\include`, `C:\SFML\bin`

3. **Настройте переменные окружения (опционально):**
   - Добавьте `C:\SFML\bin` в `PATH` (для запуска приложений)
   - Или скопируйте DLL файлы в папку с исполняемым файлом после сборки

#### Настройка CMake для Windows

Если SFML установлен в нестандартное место, укажите путь при конфигурации:

```bash
# Для Visual Studio
cmake .. -DCMAKE_PREFIX_PATH=C:/SFML

# Для MinGW
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/SFML
```

Или установите переменную окружения `SFML_ROOT`:
```bash
set SFML_ROOT=C:\SFML
```

### Проверка установки

После установки проверьте, что SFML доступен:

```bash
# macOS
brew list sfml

# Linux
dpkg -l | grep sfml

# Windows
# Проверьте наличие файлов в C:\SFML\include\SFML и C:\SFML\lib
dir C:\SFML\include\SFML
dir C:\SFML\lib
```

## 📦 Структура проекта

```
sfml-tutorial/
├── README.md                          # Этот файл
├── example1-basic-window/              # Пример 1: Базовое окно
│   ├── main.cpp
│   ├── CMakeLists.txt
│   └── README.md
├── example2-sprites-textures/         # Пример 2: Текстуры и спрайты
│   ├── main.cpp
│   ├── CMakeLists.txt
│   ├── README.md
│   └── resources/
│       └── sprite.png
└── example3-buttons/                  # Пример 3: Кнопки
    ├── main.cpp
    ├── Button.h
    ├── Button.cpp
    ├── CMakeLists.txt
    ├── README.md
    └── resources/
        └── button.png
```

## 🔧 Подключение SFML в CMake

SFML 3.0 использует заглавные буквы для компонентов, SFML 2.x - строчные. Вот универсальный CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MySFMLProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск SFML (версия 3.0 или 2.x)
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
```

## 📚 Примеры

### Пример 1: Базовое окно

**Время:** ~10 минут

Создание простого окна с обработкой событий закрытия.

[Перейти к примеру 1 →](example1-basic-window/README.md)

### Пример 2: Текстуры и спрайты

**Время:** ~20 минут

Загрузка изображений, создание текстур и спрайтов, работа с позиционированием и масштабированием.

[Перейти к примеру 2 →](example2-sprites-textures/README.md)

### Пример 3: Создание кнопок

**Время:** ~20 минут

Создание интерактивных кнопок с обработкой нажатий мыши, изменение состояния при наведении.

[Перейти к примеру 3 →](example3-buttons/README.md)

## 🎯 Ключевые концепции SFML

### Основные классы

- **`sf::RenderWindow`** - окно для отрисовки
- **`sf::Texture`** - текстура (загруженное изображение)
- **`sf::Sprite`** - спрайт (визуальное представление текстуры)
- **`sf::Event`** - события (нажатия клавиш, движение мыши и т.д.)
- **`sf::Vector2f`** - двумерный вектор для позиций и размеров

### Важные изменения в SFML 3.0

1. **Конструктор Sprite**: В SFML 3.0 `sf::Sprite()` без аргументов удалён. Нужно передавать текстуру:
   ```cpp
   // SFML 2.x (не работает в 3.0)
   sf::Sprite sprite;
   sprite.setTexture(texture);
   
   // SFML 3.0
   sf::Sprite sprite(texture);
   ```

2. **VideoMode**: Теперь использует `sf::Vector2u`:
   ```cpp
   // SFML 2.x
   sf::VideoMode(800, 600)
   
   // SFML 3.0
   sf::VideoMode(sf::Vector2u(800, 600))
   ```

3. **pollEvent()**: Возвращает `std::optional<Event>`:
   ```cpp
   // SFML 2.x
   sf::Event event;
   while (window.pollEvent(event)) { ... }
   
   // SFML 3.0
   while (auto event = window.pollEvent()) {
       if (event->is<sf::Event::Closed>()) { ... }
   }
   ```

4. **Keyboard::Key**: Теперь enum class:
   ```cpp
   // SFML 2.x
   sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
   
   // SFML 3.0
   sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
   ```

## 🛠️ Сборка проектов

### macOS и Linux

Для каждого примера:

```bash
cd example1-basic-window  # или example2, example3
mkdir build
cd build
cmake ..
make
./MySFMLProject  # или имя проекта из CMakeLists.txt
```

### Windows

#### С Visual Studio

```cmd
cd example1-basic-window
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

Затем запустите исполняемый файл:
```cmd
Release\Example1_BasicWindow.exe
```

Или откройте `.sln` файл в Visual Studio:
```cmd
start Example1_BasicWindow.sln
```

**Важно:** После сборки скопируйте DLL файлы SFML в папку с исполняемым файлом:
```cmd
copy C:\SFML\bin\*.dll Release\
```

#### С MinGW

```cmd
cd example1-basic-window
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
Example1_BasicWindow.exe
```

**Важно:** Убедитесь, что DLL файлы SFML находятся в `PATH` или скопируйте их в папку с исполняемым файлом:
```cmd
copy C:\SFML\bin\*.dll .
```

#### Автоматическое копирование DLL (опционально)

Для автоматического копирования DLL можно добавить в `CMakeLists.txt`:

```cmake
# Копирование DLL файлов (только для Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT}/bin/sfml-system-3.dll"
        "${SFML_ROOT}/bin/sfml-window-3.dll"
        "${SFML_ROOT}/bin/sfml-graphics-3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
```

## 📖 Дополнительные ресурсы

- [Официальная документация SFML](https://www.sfml-dev.org/documentation/)
- [SFML Tutorial на официальном сайте](https://www.sfml-dev.org/tutorials/)
- [SFML GitHub](https://github.com/SFML/SFML)

## ❓ Частые проблемы

### SFML не найден CMake

Убедитесь, что SFML установлен и доступен в системе. Попробуйте указать путь явно:

**macOS/Linux:**
```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/sfml ..
```

**Windows:**
```cmd
cmake .. -DCMAKE_PREFIX_PATH=C:/SFML
```

Или установите переменную окружения:
```cmd
set SFML_ROOT=C:\SFML
cmake ..
```

### Ошибка "DLL не найден" на Windows

Если при запуске появляется ошибка о недостающих DLL файлах:

1. Скопируйте все `.dll` файлы из `C:\SFML\bin` в папку с исполняемым файлом
2. Или добавьте `C:\SFML\bin` в переменную окружения `PATH`
3. Или используйте автоматическое копирование DLL через CMake (см. раздел "Сборка проектов")

### Ошибки компиляции с SFML 3.0

Убедитесь, что используете правильный синтаксис для SFML 3.0 (см. раздел "Важные изменения" выше).

### Изображения не загружаются

Проверьте, что пути к файлам указаны относительно исполняемого файла или используйте абсолютные пути.

## 🎓 Что дальше?

После прохождения туториала вы сможете:
- ✅ Создавать окна и обрабатывать события
- ✅ Работать с текстурами и спрайтами
- ✅ Создавать интерактивные элементы интерфейса
- ✅ Понимать различия между SFML 2.x и 3.0

Продолжайте экспериментировать и создавать свои проекты!

---

**Время прохождения:** 50-60 минут  
**Уровень:** Начинающий  
**Требования:** Базовые знания C++ и CMake
