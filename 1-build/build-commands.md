# Команды для компиляции, Make и CMake

## Компилятор (g++)

- Сборка одного файла:
  - `g++ -std=c++20 -O2 -Wall -Wextra -pedantic -o app main.cpp`
- Компиляция в объектный файл:
  - `g++ -std=c++20 -O2 -Wall -Wextra -pedantic -c main.cpp`
- Генерация ассемблера:
  - `g++ -std=c++20 -O2 -Wall -Wextra -pedantic -S main.cpp -o main.s`
- Линковка нескольких объектов:
  - `g++ -o app main.o util.o`

Полезные флаги:

- `-std=c++20` — стандарт C++.
- `-O2` — оптимизация.
- `-g` — отладочная информация.
- `-Wall -Wextra -pedantic` — расширенные предупреждения.
- `-I<path>` — путь к заголовкам.
- `-L<path>` — путь к библиотекам.
- `-l<name>` — подключение библиотеки (`-lssl` → `libssl`).
- `-c` — только компиляция в `.o`.
- `-S` — остановиться на `.s`.

## Make

- Сборка первой цели в `Makefile`:
  - `make`
- Сборка конкретной цели:
  - `make run`
- Очистка:
  - `make clean`
- Параллельная сборка:
  - `make -j4`

Полезные опции:

- `-n` — показать команды, но не выполнять.
- `-B` — пересобрать всё.
- `-C <dir>` — запуск make в другой директории.
- `-f <file>` — использовать другой Makefile.

## CMake

- Конфигурация (out-of-source):
  - `cmake -S . -B build`
- Сборка:
  - `cmake --build build`
- Очистка (если генератор — Make):
  - `cmake --build build --target clean`
- Выбор генератора:
  - `cmake -S . -B build -G "Ninja"`

Полезные опции:

- `-DCMAKE_BUILD_TYPE=Debug` — тип сборки (Debug/Release).
- `-DCMAKE_CXX_COMPILER=g++` — выбор компилятора.
- `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` —生成 `compile_commands.json`.

## Запуск готового бинарника

- Запуск:
  - `./app`
- Права на запуск:
  - `chmod +x app`

## Размер бинарника

- Человекочитаемый размер:
  - `ls -lh app`
- Точный размер в байтах:
  - `stat -f%z app` (macOS)
  - `stat -c%s app` (Linux)
- Размеры секций:
  - `size app`
