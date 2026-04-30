// ============================================================
// Вариативные шаблоны (Variadic Templates)
// ============================================================
// Темы:
//   - Parameter pack: typename... Args, Args... args
//   - sizeof...(Args) / sizeof...(args)
//   - Рекурсивное раскрытие пакета
//   - Fold expressions (C++17)
//   - Pack expansion в разных контекстах
//   - Variadic class templates (рекурсивное наследование)
//   - Практические паттерны: make_unique, emplace, overloaded
// Компиляция: g++ -std=c++17 -Wall -o variadic_templates variadic_templates.cpp
// ============================================================

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <type_traits>
#include <utility>

// ============================================================
// 1. Что такое parameter pack
// ============================================================
// typename... Args — пакет типов (template parameter pack)
// const Args&... args — пакет значений (function parameter pack)
// sizeof...(Args) — количество типов в пакете (compile-time)

// Простейший пример: считаем количество аргументов
template <typename... Args>
constexpr std::size_t count_args(const Args&... args) {
    return sizeof...(Args);  // то же самое: sizeof...(args)
}

// Вопрос 1: чем sizeof...(Args) отличается от sizeof(Args...)?
// sizeof...(Args) — количество типов в пакете (например, 3).
// sizeof(Args...) — не существует, это ошибка компиляции.
// sizeof... — специальный оператор для пакетов параметров.

// ============================================================
// 2. Рекурсивное раскрытие пакета (до C++17)
// ============================================================
// Классический приём: «откусываем» первый элемент, обрабатываем его,
// рекурсивно вызываем функцию с оставшимися.

// База рекурсии: один аргумент
template <typename T>
T my_max_variadic(const T& val) {
    return val;
}

// Рекурсивный случай
template <typename T, typename... Rest>
T my_max_variadic(const T& first, const Rest&... rest) {
    T rest_max = my_max_variadic(rest...);
    return (first > rest_max) ? first : rest_max;
}

// Вопрос 2: что произойдёт, если вызвать my_max_variadic() без аргументов?
// Ошибка компиляции: ни одна перегрузка не подходит.
// У нас нет базы для пустого вызова — минимум 1 аргумент.

// ============================================================
// 3. Fold expressions (C++17)
// ============================================================
// 4 формы:
//   (pack op ...)       — унарная правая:  a1 op (a2 op (a3 op a4))
//   (... op pack)       — унарная левая:   ((a1 op a2) op a3) op a4
//   (pack op ... op init) — бинарная правая: a1 op (a2 op (a3 op init))
//   (init op ... op pack) — бинарная левая:  ((init op a1) op a2) op a3

// Сумма (унарная левая)
template <typename... Args>
auto sum_all(const Args&... args) {
    return (... + args);  // ((a1 + a2) + a3) + ...
}

// Сумма с начальным значением (бинарная правая) — безопасна для пустого пакета
template <typename... Args>
auto sum_safe(const Args&... args) {
    return (args + ... + 0);
}

// Вопрос 3: что будет при вызове sum_all() с пустым пакетом?
// Для большинства операторов — ошибка компиляции.
// Исключения: && -> true, || -> false, запятая -> void().
// Поэтому для пустого пакета используют бинарную свёртку с init.

// Все ли элементы положительные?
template <typename... Args>
bool all_positive(const Args&... args) {
    return ((args > 0) && ...);  // (a1>0) && ((a2>0) && ...)
}

// Вывод всех аргументов через запятую
template <typename... Args>
void print_all(const Args&... args) {
    bool first = true;
    // Fold expression с оператором-запятой:
    // для каждого аргумента выполняем лямбду
    ([&](const auto& arg) {
        if (!first) std::cout << ", ";
        std::cout << arg;
        first = false;
    }(args), ...);
    std::cout << "\n";
}

// ============================================================
// 4. Pack expansion в разных контекстах
// ============================================================
// Pattern... раскрывается в список через запятую,
// где pattern применяется к каждому элементу пакета.

// 4a. Передача аргументов в другую функцию
template <typename... Args>
void forward_to_print(Args&&... args) {
    // std::forward<Args>(args)... раскрывается в:
    // std::forward<A1>(a1), std::forward<A2>(a2), ...
    print_all(std::forward<Args>(args)...);
}

// 4b. Создание вектора из аргументов (pack expansion в initializer list)
template <typename T, typename... Args>
std::vector<T> make_vector(Args&&... args) {
    return {static_cast<T>(std::forward<Args>(args))...};
}

// 4c. Применение функции к каждому аргументу (pack expansion с выражением)
template <typename... Args>
void print_doubled(const Args&... args) {
    // (args * 2)... раскрывается в: (a1*2), (a2*2), (a3*2), ...
    print_all((args * 2)...);
}

// Вопрос 4: что значит запись (args * 2)...?
// Это pack expansion: паттерн (args * 2) применяется к каждому
// элементу пакета. Результат: (a1*2), (a2*2), (a3*2).

// ============================================================
// 5. Variadic class template: TypeList
// ============================================================
// Списки типов — фундаментальный строительный блок метапрограммирования.

template <typename... Types>
struct TypeList {
    static constexpr std::size_t size = sizeof...(Types);
};

// Получение первого типа списка
template <typename List>
struct Front;

template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
    using type = Head;
};

// Получение хвоста (всё кроме первого)
template <typename List>
struct PopFront;

template <typename Head, typename... Tail>
struct PopFront<TypeList<Head, Tail...>> {
    using type = TypeList<Tail...>;
};

// Проверка: содержит ли список данный тип
template <typename List, typename T>
struct Contains;

template <typename T>
struct Contains<TypeList<>, T> : std::false_type {};

template <typename Head, typename... Tail, typename T>
struct Contains<TypeList<Head, Tail...>, T>
    : std::conditional_t<std::is_same_v<Head, T>,
                         std::true_type,
                         Contains<TypeList<Tail...>, T>> {};

// Вопрос 5: зачем нужны TypeList, если есть std::tuple?
// TypeList хранит только типы, не создаёт объектов.
// std::tuple<int, double> создаёт объект с двумя полями.
// TypeList<int, double> — это просто «список типов» для метапрограммирования,
// без накладных расходов в рантайме.

// ============================================================
// 6. Рекурсивное наследование: простой Tuple
// ============================================================

template <typename... Types>
struct MyTuple {};

// Рекурсивный случай: наследуемся от «хвоста»
template <typename Head, typename... Tail>
struct MyTuple<Head, Tail...> : MyTuple<Tail...> {
    Head value;

    MyTuple() = default;
    MyTuple(const Head& h, const Tail&... t)
        : MyTuple<Tail...>(t...), value(h) {}
};

// Получение N-го элемента
template <std::size_t N, typename Head, typename... Tail>
auto& my_get(MyTuple<Head, Tail...>& t) {
    if constexpr (N == 0) {
        return t.value;
    } else {
        return my_get<N - 1>(static_cast<MyTuple<Tail...>&>(t));
    }
}

// Размер кортежа
template <typename... Types>
constexpr std::size_t my_tuple_size(const MyTuple<Types...>&) {
    return sizeof...(Types);
}

// Вопрос 6: почему MyTuple использует наследование, а не композицию?
// Наследование позволяет «раскрутить» рекурсию: каждый уровень
// добавляет одно поле. Base class subobject не занимает лишней памяти
// (Empty Base Optimization для пустого MyTuple<>).

// ============================================================
// 7. Паттерн: фабричная функция (аналог std::make_unique)
// ============================================================
// Perfect forwarding + variadic templates = универсальная фабрика.

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    void print() const { std::cout << "Point(" << x << ", " << y << ")\n"; }
};

struct Person {
    std::string name;
    int age;
    Person(std::string name, int age) : name(std::move(name)), age(age) {}
    void print() const { std::cout << "Person(" << name << ", " << age << ")\n"; }
};

// Наша фабрика: создаёт объект T, передавая аргументы в конструктор
template <typename T, typename... Args>
std::unique_ptr<T> my_make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Вопрос 7: почему std::forward, а не просто args...?
// Без forward rvalue-ссылки «проваливаются» в lvalue.
// std::forward сохраняет категорию значения: lvalue остаётся lvalue,
// rvalue остаётся rvalue. Это perfect forwarding.

// ============================================================
// 8. Паттерн: overloaded (для std::visit + std::variant)
// ============================================================
// Классический трюк C++17: наследование от нескольких лямбд.

template <typename... Lambdas>
struct Overloaded : Lambdas... {
    using Lambdas::operator()...;  // «вытаскиваем» все operator() в одну область видимости
};

// Deduction guide (C++17): позволяет не указывать типы явно
template <typename... Lambdas>
Overloaded(Lambdas...) -> Overloaded<Lambdas...>;

// Вопрос 8: для чего нужен using Lambdas::operator()...?
// Без using каждый operator() скрыт в своём базовом классе.
// using «экспортирует» все версии в Overloaded, чтобы работал
// overload resolution по типу аргумента.

// ============================================================
// 9. Паттерн: index_sequence для compile-time индексации
// ============================================================
// std::index_sequence позволяет «развернуть» кортеж или массив
// в пакет параметров.

template <typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
    // Раскрытие пакета: std::get<0>(t), std::get<1>(t), ...
    ((std::cout << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
    std::cout << "\n";
}

template <typename... Types>
void print_tuple(const std::tuple<Types...>& t) {
    print_tuple_impl(t, std::index_sequence_for<Types...>{});
}

// Вопрос 9: зачем нужен std::index_sequence?
// Чтобы превратить compile-time целые числа 0, 1, 2, ...
// в пакет параметров, который можно раскрыть через pack expansion.
// Без него нельзя написать std::get<0>(t), std::get<1>(t), ...
// для произвольного количества элементов.

// ============================================================
// 10. Подводные камни
// ============================================================

// 10a. Раскрытие пакета происходит только в определённых контекстах:
//   - аргументы функции:  f(args...)
//   - список инициализации: {args...}
//   - базовые классы:      class D : Bases... { using Bases::f...; };
//   - fold expression:     (args + ...)
// Нельзя: args...; (просто раскрыть «в никуда»)

// 10b. Порядок вычисления в fold expression
// (f(args), ...) гарантирует порядок слева направо (с C++17).
// Но f(g(args)...) — порядок вычисления аргументов НЕ определён!

// 10c. Пустые пакеты
// sizeof...(Args) может быть 0. Нужно обрабатывать этот случай.
// Рекурсия без базы для пустого пакета — ошибка компиляции.

// ============================================================
// main
// ============================================================

int main() {
    std::cout << "=== 1. sizeof...(Args) ===\n";
    std::cout << "count_args()          = " << count_args() << "\n";
    std::cout << "count_args(1,2,3)     = " << count_args(1, 2, 3) << "\n";
    std::cout << "count_args(1,\"a\",3.0) = " << count_args(1, "a", 3.0) << "\n";

    std::cout << "\n=== 2. Рекурсивное раскрытие: my_max_variadic ===\n";
    std::cout << "max(3, 1, 4, 1, 5, 9) = " << my_max_variadic(3, 1, 4, 1, 5, 9) << "\n";
    std::cout << "max(42)               = " << my_max_variadic(42) << "\n";

    std::cout << "\n=== 3. Fold expressions ===\n";
    std::cout << "sum_all(1,2,3,4,5) = " << sum_all(1, 2, 3, 4, 5) << "\n";
    std::cout << "sum_safe()          = " << sum_safe() << "\n";
    std::cout << "sum_safe(10,20)     = " << sum_safe(10, 20) << "\n";
    std::cout << "all_positive(1,2,3) = " << all_positive(1, 2, 3) << "\n";
    std::cout << "all_positive(1,-2)  = " << all_positive(1, -2) << "\n";

    std::cout << "\n=== 4. print_all через fold ===\n";
    print_all(1, 2.5, "hello", 'A');

    std::cout << "\n=== 5. Pack expansion ===\n";
    std::cout << "forward_to_print: ";
    forward_to_print(10, 20, 30);

    std::cout << "make_vector<int>: ";
    auto v = make_vector<int>(1, 2, 3, 4, 5);
    for (auto x : v) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "print_doubled(1,2,3): ";
    print_doubled(1, 2, 3);

    std::cout << "\n=== 6. TypeList ===\n";
    using MyList = TypeList<int, double, std::string>;
    std::cout << "MyList::size = " << MyList::size << "\n";

    using First = Front<MyList>::type;
    std::cout << "Front<MyList> is int? "
              << std::is_same_v<First, int> << "\n";

    using Tail = PopFront<MyList>::type;
    std::cout << "PopFront<MyList>::size = " << Tail::size << "\n";

    std::cout << "Contains<MyList, int>?    " << Contains<MyList, int>::value << "\n";
    std::cout << "Contains<MyList, char>?   " << Contains<MyList, char>::value << "\n";

    std::cout << "\n=== 7. MyTuple ===\n";
    MyTuple<int, double, std::string> t(42, 3.14, "мир");
    std::cout << "my_get<0>(t) = " << my_get<0>(t) << "\n";
    std::cout << "my_get<1>(t) = " << my_get<1>(t) << "\n";
    std::cout << "my_get<2>(t) = " << my_get<2>(t) << "\n";
    std::cout << "my_tuple_size = " << my_tuple_size(t) << "\n";

    std::cout << "\n=== 8. my_make_unique (фабрика) ===\n";
    auto pt = my_make_unique<Point>(1.0, 2.0);
    pt->print();
    auto person = my_make_unique<Person>("Иван", 25);
    person->print();

    std::cout << "\n=== 9. Overloaded ===\n";
    auto visitor = Overloaded{
        [](int x)    { std::cout << "int: " << x << "\n"; },
        [](double x) { std::cout << "double: " << x << "\n"; },
        [](const std::string& x) { std::cout << "string: " << x << "\n"; }
    };
    visitor(42);
    visitor(3.14);
    visitor(std::string("привет"));

    std::cout << "\n=== 10. print_tuple (index_sequence) ===\n";
    auto tup = std::make_tuple(1, 2.5, std::string("C++"), 'Z');
    std::cout << "tuple: ";
    print_tuple(tup);

    std::cout << "\n=== Итог ===\n";
    std::cout << "typename... Args — пакет типов\n"
              << "sizeof...(Args)  — размер пакета\n"
              << "Рекурсия: T + Rest... с базой для одного/нуля\n"
              << "Fold: (... op args), (args op ...), с init\n"
              << "Pack expansion: pattern... применяется к каждому элементу\n"
              << "index_sequence: compile-time индексы для раскрытия\n";

    return 0;
}
