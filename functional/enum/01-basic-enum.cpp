#include <iostream>

// Unscoped enum: перечислители попадают в окружающую область видимости.
// Первый перечислитель = 0, каждый следующий на 1 больше.
enum Direction {
    North,  // 0
    East,   // 1
    South,  // 2
    West    // 3
};

// Можно явно задавать значения.
// Следующий перечислитель продолжает счёт от предыдущего + 1.
enum HttpStatus {
    OK        = 200,
    Created   = 201,
    BadRequest = 400,
    NotFound  = 404,
    InternalServerError = 500
};

const char* direction_name(Direction d) {
    switch (d) {
        case North: return "North";
        case East:  return "East";
        case South: return "South";
        case West:  return "West";
    }
    return "Unknown";
}

int main() {
    // Объявление переменной enum
    Direction d = South;
    std::cout << "Direction: " << direction_name(d) << "\n";

    // Unscoped enum неявно преобразуется в int
    int val = d;
    std::cout << "As int: " << val << "\n";  // 2

    // Можно сравнивать с int (но это опасная практика)
    if (d == 2) {
        std::cout << "South == 2\n";
    }

    // Перечислители видны без префикса (утекают в область видимости)
    Direction d2 = East;  // не Direction::East, просто East
    std::cout << "d2: " << direction_name(d2) << "\n";

    // HTTP статусы
    HttpStatus status = NotFound;
    std::cout << "Status: " << status << "\n";  // 404

    // Размер enum по умолчанию — как int
    std::cout << "sizeof(Direction): " << sizeof(Direction) << "\n";
    std::cout << "sizeof(HttpStatus): " << sizeof(HttpStatus) << "\n";

    return 0;
}
