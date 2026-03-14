#include <iostream>

// enum class: scoped перечисление (C++11).
// Перечислители НЕ утекают в окружающую область видимости.
// Нет неявного преобразования в int.
enum class Color {
    Red,
    Green,
    Blue
};

enum class Direction {
    North,
    East,
    South,
    West
};

// Нет конфликта имён: Color::Red и Direction::North — разные типы.
// С unscoped enum так сделать нельзя, если оба имеют одинаковые имена.

const char* color_name(Color c) {
    switch (c) {
        case Color::Red:   return "Red";
        case Color::Green: return "Green";
        case Color::Blue:  return "Blue";
    }
    return "Unknown";
}

const char* direction_name(Direction d) {
    switch (d) {
        case Direction::North: return "North";
        case Direction::East:  return "East";
        case Direction::South: return "South";
        case Direction::West:  return "West";
    }
    return "Unknown";
}

int main() {
    // Объявление — нужен префикс Color::
    Color c = Color::Green;

    std::cout << "Color: " << color_name(c) << "\n";

    // Нельзя неявно преобразовать в int — ошибка компиляции:
    // int n = c;

    // Явное преобразование через static_cast
    int n = static_cast<int>(c);
    // int n = c;
    std::cout << "As int: " << n << "\n";  // 1

    // Нельзя сравнивать с int — ошибка компиляции:
    // if (c == 1) { }

    // Нельзя смешивать разные enum class — ошибка компиляции:
    // if (c == Direction::North) { }

    Direction d = Direction::West;
    std::cout << "Direction: " << direction_name(d) << "\n";

    // Приведение int к enum class — тоже нужен static_cast
    Color c2 = static_cast<Color>(2);
    std::cout << "Color from int 2: " << color_name(c2) << "\n";  // Blue

    return 0;
}
