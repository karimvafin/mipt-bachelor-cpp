# Пример 1: Базовое окно

**Время выполнения:** ~10 минут

## Цель

Научиться создавать базовое окно SFML и обрабатывать основные события (закрытие окна, нажатия клавиш).

## Что вы изучите

- Создание окна с помощью `sf::RenderWindow`
- Обработка событий через `pollEvent()`
- Главный цикл приложения (game loop)
- Очистка и отображение кадров

## Пошаговая инструкция

### Шаг 1: Подключение заголовочных файлов

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>
```

### Шаг 2: Создание окна

В SFML 3.0 конструктор `VideoMode` изменился:

```cpp
// SFML 3.0
sf::RenderWindow window(
    sf::VideoMode(sf::Vector2u(800, 600)), 
    "SFML Tutorial - Example 1"
);
```

### Шаг 3: Главный цикл

Главный цикл приложения состоит из трех частей:
1. Обработка событий
2. Обновление логики
3. Отрисовка

```cpp
while (window.isOpen())
{
    // 1. Обработка событий
    while (auto event = window.pollEvent()) { ... }
    
    // 2. Обновление логики
    // (пока пусто)
    
    // 3. Отрисовка
    window.clear(sf::Color(20, 30, 50));
    window.display();
}
```

### Шаг 4: Обработка событий

В SFML 3.0 события обрабатываются через `std::optional`:

```cpp
while (auto event = window.pollEvent())
{
    // Проверка типа события
    if (event->is<sf::Event::Closed>())
    {
        window.close();
    }
}
```

### Шаг 5: Сборка и запуск

```bash
mkdir build
cd build
cmake ..
make
./Example1_BasicWindow
```

## Ключевые моменты

1. **VideoMode**: В SFML 3.0 используйте `sf::Vector2u(width, height)`
2. **pollEvent()**: Возвращает `std::optional<Event>`, используйте `auto event = window.pollEvent()`
3. **Проверка типа события**: Используйте `event->is<sf::Event::Closed>()`
4. **Главный цикл**: Всегда должен содержать `clear()` и `display()`

## Упражнения

1. Измените размер окна на 1024x768
2. Измените цвет фона на другой
3. Добавьте обработку нажатия клавиши Space (вывод в консоль)

## Следующий шаг

Переходите к [Примеру 2: Текстуры и спрайты](../example2-sprites-textures/README.md)
