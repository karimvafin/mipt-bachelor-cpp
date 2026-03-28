# Задания по std::unordered_map

5 задач на работу с хэш-таблицей `std::unordered_map`.

## Структура

```
unordered_map_tasks/
├── tasks.h       — объявления функций
├── tasks.cpp     — здесь пишете реализацию
├── tests.cpp     — тесты (не трогать)
└── CMakeLists.txt
```

## Сборка и запуск

```bash
cmake -S . -B build
cmake --build build
./build/unordered_map_tests
```

Или через `ctest`:

```bash
cmake -S . -B build
cmake --build build
cd build && ctest --output-on-failure
```

## Рабочий процесс

1. Откройте `tasks.cpp`.
2. Найдите функцию, которую хотите реализовать.
3. Удалите строку `throw std::runtime_error("Not implemented");` и напишите код.
4. Пересоберите и запустите тесты — убедитесь, что все `[PASS]`.
