# Перечисления (enum) в C++

Цель: понять разницу между `enum` и `enum class`, научиться работать с базовым типом, использовать перечисления в `switch`, реализовывать битовые флаги.

Перечисление (enum) — тип данных, который задаёт именованный набор целочисленных констант. Вместо магических чисел код становится читаемым и безопасным.

## Базовый enum (unscoped)

Понятия:

- `enum` — объявление перечисления; его константы попадают в окружающую область видимости.
- Перечислитель (enumerator) — именованная константа внутри `enum`.
- Неявное начальное значение — первый перечислитель равен 0, каждый следующий на 1 больше.
- Явное значение — можно задать любое целое число, следующий перечислитель продолжает счёт от него.
- Неявное преобразование в `int` — unscoped `enum` автоматически конвертируется в целое, что иногда приводит к ошибкам.

Папка: `functional/enum`

Пример:

```cpp
enum Direction { North, East, South, West };

Direction d = North;  // ok
int n = d;            // ok — неявное преобразование в int (0)
```

Команды:

```
cd functional/enum
g++ -std=c++20 -Wall -Wextra -o basic 01-basic-enum.cpp
./basic
```

## enum class (scoped enum, C++11)

Понятия:

- `enum class` / `enum struct` — scoped перечисление; перечислители не утекают в окружающую область видимости.
- Отсутствие неявного преобразования — нельзя сравнить `enum class` с `int` без явного каста.
- `static_cast<int>(e)` — способ явно получить числовое значение перечислителя.
- Преимущества перед `enum`: нет конфликтов имён, нет случайных неявных преобразований.

Пример:

```cpp
enum class Color { Red, Green, Blue };

Color c = Color::Red;
// int n = c;            // ошибка компиляции
int n = static_cast<int>(c);  // ok, n == 0
```

Команды:

```
g++ -std=c++20 -Wall -Wextra -o scoped 02-enum-class.cpp
./scoped
```

## Базовый тип и продвинутые техники

Понятия:

- Базовый тип (underlying type) — целочисленный тип, которым представлен `enum`; по умолчанию `int`.
- Явное указание типа — `enum class Status : uint8_t { ... }` уменьшает размер до одного байта.
- `std::underlying_type_t<E>` — функция из `<type_traits>`, возвращает базовый тип перечисления.
- `std::to_underlying(e)` (C++23) — удобная замена `static_cast<std::underlying_type_t<E>>(e)`.
- Битовые флаги — перечислитель задаётся как степень двойки; флаги объединяются оператором `|`.

Пример базового типа:

```cpp
enum class Permission : uint8_t {
    None    = 0,
    Read    = 1 << 0,  // 1
    Write   = 1 << 1,  // 2
    Execute = 1 << 2,  // 4
};
```

Пример чтения underlying type:

```cpp
#include <type_traits>

using T = std::underlying_type_t<Permission>;  // uint8_t
T raw = static_cast<T>(Permission::Read);      // 1
```

Команды:

```
g++ -std=c++20 -Wall -Wextra -o advanced 03-advanced.cpp
./advanced
```
