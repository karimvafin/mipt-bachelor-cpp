#include <ios>
#include <iostream>
#include <type_traits>

// Что такое метапрограммирование?

// -- написание программ, которые работают с программами
// В С++ -- это код, который выполняется на этапе компиляции
// и помогает компилятору сгенерировать другой код

// Обычный код выполняется во время работы программы (runtime)
int square(int x) {
    return x * x;
}
// int arr1[square(5)];

// Метапрограммирование позволяет делать вычисления
// и принимать решения ещё до запуска программы, во время компиляции
constexpr int square_constexpr(int x) {
    return x * x;
}

int arr2[square_constexpr(5)]; // размер массива известен во время компиляции

// Для чего нужно метапрограммирование?
// Метапрограммирование полезно, когда нужно:
// 1. Убрать лишние runtime-проверки
// 2. Генерировать эффективный код
// 3. Писать обобщённые библиотеки
// 4. Проверять свойства типов
// 5. Выбирать реализацию в зависимости от типа
// 6. Делать вычисления на этапе компиляции

// Шаблоны -- основа метапрограммирования
template <typename T>
T max_value(T a, T b) {
    return a > b ? a : b;
}

auto max1 = max_value(3, 7);
auto max2 = max_value(2.5, 1.3);

// Компилятор автоматически создаст
// int max_value(int, int);
// double max_value(double, double);

// Шаблон — это не функция в обычном смысле, а инструкция компилятору, как создать функцию

// Шаблоны классов -- то же самое

// Шаблон может принимать не только типы, но и значения.
// static constexpr переменные -- статические переменные, известные на этапе компиляции
// то есть они не лежат где-то в памяти во время выполнения
// можно считать будто на их место просто подставится указанное значение
template <int N>
struct Constant {
    static constexpr int value = N;
};

int one = Constant<1>::value;
int four = Constant<4>::value;
// Constant<1> и Constant<4> это разные типы!

// Ключевая идея: значения могут участвовать в создании типов

// Вычисления на этапе компиляции: факториал

template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

int five_factorial = Factorial<5>::value; // 120

/*
Раскрывается следующим образом
5 * Factorial<4>::value
5 * 4 * Factorial<3>::value
5 * 4 * 3 * Factorial<2>::value
5 * 4 * 3 * 2 * Factorial<1>::value
5 * 4 * 3 * 2 * 1 * Factorial<0>::value
*/

// Специализация Factorial<0> -- база рекурсии
// Специализация -- способ сказать компилятору
// "для это конкретного шаблонного параметра используй другую реализацию"

// Частичная специализация -- для группы типов, например указателей

template <typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template <typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

bool b1 = IsPointer<int>::value;   // false
bool b2 = IsPointer<int*>::value;  // true

bool b3 = std::is_pointer<float*>::value;
bool b4 = std::is_pointer<int[]>::value;

// Интегральные константы
template <typename T, T v>
struct IntegralConstant {
    static constexpr T value = v;
};

using TrueType = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;
using One = IntegralConstant<int, 1>;

template <typename T>
struct IsPointer2 : FalseType {};

template <typename T>
struct IsPointer2<T*> : TrueType {};

bool b5 = IsPointer2<int*>::value;
bool b6 = IsPointer2<float**>::value;

// Type traits -- шаблонные структуры, отвечающие на вопросы о типах
/*
std::is_integral<int>::value       // true
std::is_integral<double>::value    // false

std::is_pointer<int*>::value       // true
std::is_pointer<int>::value        // false

std::is_same<int, int>::value      // true
std::is_same<int, double>::value   // false
*/

// Задача: IsSame
template <typename T, typename U>
struct IsSame : FalseType {};

template <typename T>
struct IsSame<T, T> : TrueType {};

bool b7 = IsSame<int, float>::value;
bool b8 = IsSame<int, int>::value;

// Пример
template <typename T>
void inspect() {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral type\n";
    } else if constexpr (std::is_floating_point<T>::value) {
        std::cout << "Floating point type\n";
    } else {
        std::cout << "Other type\n";
    }
}
// inspect<int>();
// inspect<double>();
// inspect<std::string>();

// constexpr if -- if на этапе компиляции
// Почему нельзя обычный if?
template <typename T>
void print_value(T value) {
    if constexpr (std::is_pointer<T>::value) {
        std::cout << *value << '\n';
    } else {
        std::cout << value << '\n';
    }
}
// Если T = int, то *value некорректно, потому что value — не указатель.
// Обычный if не спасает: компилятор всё равно проверяет обе ветки.
// А if constexpr отбрасывает неподходящую ветку на этапе компиляции.

// constexpr функции
// Шаблонное метапрограммирование часто выглядит сложно:
template <int N>
struct FactorialL {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// constexpr функции позволяют упростить код
constexpr int factorial(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

constexpr int constexpr_value = factorial(5);

int arr[constexpr_value];

// constexpr функция означает, что эта функция может быть выполнена
// во время компиляции, если её аргументы известны во время компиляции.
// Но никто не запрещает вызывать ее с runtime аргументами:

// compile-time
// constexpr int a = factorial(5);

// runtime
// int n;
// std::cin >> n;
// int b = factorial(n);

// consteval функции обязаны быть вычисленными на этапе компиляции
// constexpr означает “может быть compile-time”
// consteval означает “обязательно compile-time”

consteval int square_consteval(int x) {
    return x * x;
}

constexpr int consteval_value = square_consteval(5); // ok

int n = 5;
// int b = square_consteval(n); // ошибка

// consteval полезен, когда функция не имеет смысла во время выполнения

// SFINAE -- Substitution Failure Is Not An Error
// то есть ошибка подстановки шаблонного параметра
// не является ошибкой компиляции, а просто исключает
// этот вариант из набора перегрузок

// Пусть мы хотим функцию только для целочисленных аргументов
template <typename T>
std::enable_if_t<std::is_integral<T>::value, void> print_integer(T value) {
    std::cout << "Integer: " << value << '\n';
}
// print_integer(10); норм
// print_integer(3.14); ошибка: нет подходящей функции

// std::enable_if_t<std::is_integral<T>::value, void>
// если std::is_integral<T>::value = true, то тип void
// если false, то будет ошибка подстановки
// но такое можно заменить на if constexpr

// Compile time выбор типа (std::conditional_t<condition, TypeIfTrue, TypeIfFalse>)
template <bool Cond, typename TrueType, typename FalseType>
struct Conditional {
    using type = TrueType;
};

template <typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> {
    using type = FalseType;
};

template <bool Cond, typename TrueType, typename FalseType>
using ConditionalT = typename Conditional<Cond, TrueType, FalseType>::type;

ConditionalT<true, int, double> x = 3.14;  // int
ConditionalT<false, int, double> y = 3.14; // double

// Compile time список типов
template <typename... Ts>
struct TypeList {};

// Получение размера списка
template <typename List>
struct Size;

template <typename... Ts>
struct Size<TypeList<Ts...>> {
    static constexpr std::size_t value = sizeof...(Ts);
};
// Использование: Size<TypeList<int, double, char>>::value

// Достать первый тип
template <typename List>
struct Front;

template <typename Head, typename... Tail>
struct Front<TypeList<Head, Tail...>> {
    using type = Head;
};

template <typename List>
using FrontT = typename Front<List>::type;

using MyTypes = TypeList<int, double, char>;

static_assert(IsSame<FrontT<MyTypes>, int>::value);

// Проверка наличия типа в TypeList
template <typename T, typename List>
struct Contains;

template <typename T>
struct Contains<T, TypeList<>> {
    static constexpr bool value = false;
};

template <typename T, typename Head, typename... Tail>
struct Contains<T, TypeList<Head, Tail...>> {
    static constexpr bool value =
        std::is_same<T, Head>::value || Contains<T, TypeList<Tail...>>::value;
};

// Tuple
// класс, содержащий разные типы данных
template <typename... Ts>
struct Tuple;

template <>
struct Tuple<> {};

template <typename Head, typename... Tail>
struct Tuple<Head, Tail...> {
    Head head;
    Tuple<Tail...> tail;

    Tuple(Head h, Tail... t)
        : head(h), tail(t...) {}
};

template <typename T>
void print(const T& value, std::string name) {
    std::cout << name << " = " << value << std::endl;
}


int main() {
    std::cout << "max1 = " << max1 << std::endl;
    std::cout << "max2 = " << max2 << std::endl;
    std::cout << "one = " << one << std::endl;
    std::cout << "four = " << four << std::endl;
    std::cout << "five_factorial = " << five_factorial << std::endl;
    std::cout << std::boolalpha << "b1 = " << b1 << std::endl;
    std::cout << std::boolalpha << "b2 = " << b2 << std::endl;
    std::cout << std::boolalpha << "b3 = " << b3 << std::endl;
    std::cout << std::boolalpha << "b4 = " << b4 << std::endl;
    std::cout << std::boolalpha << "b5 = " << b5 << std::endl;
    std::cout << std::boolalpha << "b6 = " << b6 << std::endl;
    std::cout << std::boolalpha << "b7 = " << b7 << std::endl;
    std::cout << std::boolalpha << "b8 = " << b8 << std::endl;

    std::cout << "inspect<int>() = ";
    inspect<int>();
    // std::cout << std::endl;
    std::cout << "inspect<double>() = ";
    inspect<double>();
    // std::cout << std::endl;
    std::cout << "inspect<std::string>() = ";
    inspect<std::string>();
    // std::cout << std::endl;

    print(constexpr_value, "constexpr_value");

    print_integer(10);
    // print_integer(3.14);

    Tuple<int, double, std::string> t(1, 2.5, "hello");
    print(t.head, "t.head");
    print(t.tail.head, "t.head");
    print(t.tail.tail.head, "t.head");

    std::tuple<int, float> t1(1, 2.0f);

    const auto& [a1, a2] = t1;
    
    std::cout << std::get<0>(t1) << std::endl;
    std::cout << std::get<1>(t1) << std::endl;

    print(x, "ConditionalT<true, int, double>");
    print(y, "ConditionalT<false, int, double>");

    print(Size<TypeList<int, double, char>>::value, "Size<TypeList<int, double, char>>::value");
}