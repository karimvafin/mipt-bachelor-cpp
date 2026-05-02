#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <utility>

// =============================================================================
// Задания по шаблонам (templates-2)
// Реализуйте все функции и классы ниже — удалите throw и напишите реализацию.
// Все шаблоны реализуются прямо в этом заголовочном файле.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1: my_min (0.25 баллов)
// Напишите шаблонную функцию, возвращающую меньший из двух аргументов.
// Пример: my_min(3, 7) == 3
// Пример: my_min(std::string("abc"), std::string("xyz")) == "abc"
// -----------------------------------------------------------------------------
template <typename T>
T my_min(const T& a, const T& b) {
    return (a>b) ? b:a;
}

// -----------------------------------------------------------------------------
// Задание 2: Box<T> (0.25 баллов)
// Реализуйте шаблонный класс, хранящий одно значение типа T.
// Методы: get(), set(), to_string().
// to_string() может использовать std::ostringstream для преобразования в строку (можно посмотреть здесь: https://en.cppreference.com/w/cpp/io/basic_ostringstream.html).
// Пример: Box<int> b(42); b.get() == 42; b.to_string() == "42"
// Пример: Box<double> b(3.14); b.set(2.71); b.get() == 2.71
// -----------------------------------------------------------------------------
template <typename T>
class Box {
private:
   T x;
public:
    explicit Box(const T& value): x(value) {}

    const T& get() const {
       return x;
    }

    void set(const T& value) {
        x = value;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss<<x;
        std::string str = oss.str();
        return str;
    }
};

// -----------------------------------------------------------------------------
// Задание 3: FixedArray<T, N> (0.5 баллов)
// Реализуйте массив фиксированного размера с нетиповым параметром N.
// operator[] с проверкой границ (бросает std::out_of_range).
// Методы: size(), fill(value), at(index).
// Пример: FixedArray<int, 3> a; a.fill(0); a.at(0) == 0; a.size() == 3
// -----------------------------------------------------------------------------
template <typename T, int N>
class FixedArray {
    T data[N];
public:
    T& at(int index) {
        if(index>=N || index<0) {
            throw std::out_of_range("");
        }
        return data[index];
    }

    const T& at(int index) const {
        if(index>=N || index<0) {
            throw std::out_of_range("");
        }
        return data[index];
    }

    T& operator[](int index) {
        if(index>=N || index<0) {
            throw std::out_of_range("");
        }
        return data[index];
    }

    const T& operator[](int index) const {
         if(index>=N || index<0) {
            throw std::out_of_range("");
        }
        return data[index];
    }

    int size() const {
        return N;
    }

    void fill(const T& value) {
        for(int i=0; i<N; i++){
            data[i] = value;
        }
    }
};

// -----------------------------------------------------------------------------
// Задание 4: Converter<T> с шаблонным методом convert_to<U>() (0.5 баллов)
// Реализуйте класс, который хранит значение типа T и с шаблонным методом convert_to<U>(),
// который возвращает значение, приведённое к типу U через static_cast.
// Пример: Converter<double> c(3.14); c.convert_to<int>() == 3
// Пример: Converter<int> c(65); c.convert_to<char>() == 'A'
// -----------------------------------------------------------------------------
template <typename T>
class Converter {
    T  x;
public:
    explicit Converter(const T& value): x(value) {

    }

    const T& get() const {
        return x;
    }

    template <typename U>
    U convert_to() const {
        U b =  static_cast<U>(x);
        return b;
    }
};

// -----------------------------------------------------------------------------
// Задание 5: Pair<T, U> с конвертирующим конструктором (0.5 баллов)
// Шаблонный класс, хранящий пару значений (first, second).
// Должен иметь конвертирующий конструктор: Pair<T2, U2> -> Pair<T, U>,
// если T2 конвертируется в T и U2 конвертируется в U.
// Пример: Pair<int, int> p1(1, 2);
//          Pair<double, double> p2(p1); // int -> double
//          p2.first() == 1.0; p2.second() == 2.0
// -----------------------------------------------------------------------------
template <typename T, typename U>
class Pair {
public:
    Pair(const T& f, const U& s) {
        throw std::runtime_error("Not implemented");
    }

    // Конвертирующий конструктор из Pair<T2, U2>
    template <typename T2, typename U2>
    Pair(const Pair<T2, U2>& other) {
        throw std::runtime_error("Not implemented");
    }

    const T& first() const {
        throw std::runtime_error("Not implemented");
    }

    const U& second() const {
        throw std::runtime_error("Not implemented");
    }
};

// -----------------------------------------------------------------------------
// Задание 6: sum_all — variadic сумма через fold expression (0.5 баллов)
// Возвращает сумму всех аргументов. При пустом вызове возвращает 0.
// Пример: sum_all(1, 2, 3) == 6
// Пример: sum_all(1.5, 2.5) == 4.0
// Пример: sum_all() == 0
// -----------------------------------------------------------------------------
template <typename... Args>
auto sum_all(const Args&... args) {
    return(args + ... + 0);
}

// -----------------------------------------------------------------------------
// Задание 7: count_if_positive — посчитать положительные аргументы (0.5 баллов)
// Принимает произвольное количество числовых аргументов.
// Возвращает количество аргументов, которые строго больше нуля.
// Используйте fold expression.
// Пример: count_if_positive(1, -2, 3, 0, 5) == 3
// Пример: count_if_positive(-1, -2) == 0
// Пример: count_if_positive() == 0
// -----------------------------------------------------------------------------
template <typename... Args>
int count_if_positive(const Args&... args) {
    int count = 0;
    ([&](const auto& arg) {
        if(arg>0) count+=1;
    }(args), ...);
    return count;
}

// -----------------------------------------------------------------------------
// Задание 8: concat_all — конкатенация аргументов в строку (0.5 баллов)
// Принимает произвольное количество аргументов любых типов.
// Возвращает строку, содержащую строковые представления всех аргументов,
// разделённых пробелом.
// Используйте std::ostringstream и fold expression.
// Пример: concat_all(1, 2.5, "hello") == "1 2.5 hello"
// Пример: concat_all("abc") == "abc"
// Пример: concat_all() == ""
// -----------------------------------------------------------------------------
template <typename... Args>
std::string concat_all(const Args&... args) {
    std::ostringstream oss;
       ([&](const auto& arg) {
        oss<<arg;
    }(args), ...);
    std::string str = oss.str();
    return str;
}

// -----------------------------------------------------------------------------
// Задание 9: transform_to_vector — применить выражение к variadic (0.5 баллов)
// Принимает функцию и произвольное количество аргументов.
// Возвращает std::vector с результатами применения функции к каждому аргументу.
// Используйте pack expansion в списке инициализации.
// Пример: transform_to_vector([](int x){ return x*x; }, 1, 2, 3) == {1, 4, 9}
// Пример: transform_to_vector([](int x){ return x+1; }, 10) == {11}
// -----------------------------------------------------------------------------
template <typename F, typename... Args>
auto transform_to_vector(F&& func, const Args&... args) {
    return std::vector{func(args) ...};
}

// -----------------------------------------------------------------------------
// Задание 10: MyTuple с get (2.0 балл)
// Реализуйте упрощённый кортеж через рекурсивное наследование.
// Нужен шаблонный класс MyTuple<Types...> и функция my_get<N>(tuple).
//
// MyTuple<> — пустой кортеж (база рекурсии).
// MyTuple<Head, Tail...> — хранит Head value и наследуется от MyTuple<Tail...>.
//
// my_get<0>(t) возвращает первый элемент, my_get<1>(t) — второй, и т.д.
// my_tuple_size(t) возвращает количество элементов.
//
// Пример: MyTuple<int, double, std::string> t(42, 3.14, "hello");
//          my_get<0>(t) == 42
//          my_get<1>(t) == 3.14
//          my_get<2>(t) == "hello"
//          my_tuple_size(t) == 3
// -----------------------------------------------------------------------------

// База рекурсии
template <typename... Types>
struct MyTuple {
    // Пустой кортеж — ничего не хранит
};

// TODO: реализуйте специализацию MyTuple<Head, Tail...>
// которая хранит Head value и наследуется от MyTuple<Tail...>
// Раскомментируйте и допишите:
//
// template <typename Head, typename... Tail>
// struct MyTuple<Head, Tail...> : MyTuple<Tail...> {
//     Head value;
//     MyTuple() = default;
//     MyTuple(const Head& h, const Tail&... t)
//         : MyTuple<Tail...>(t...), value(h) {}
// };

// Заглушка: позволяет коду компилироваться до реализации.
// Удалите эту специализацию, когда напишете свою выше.
template <typename Head, typename... Tail>
struct MyTuple<Head, Tail...> : MyTuple<Tail...> {
    Head value{};
    MyTuple() = default;

    template <typename... Args>
    MyTuple(const Head&, const Args&...) {
        throw std::runtime_error("Not implemented");
    }
};

// TODO: реализуйте функцию my_get<N>(MyTuple<Head, Tail...>& t)
// которая возвращает ссылку на N-й элемент (используйте if constexpr)
template <std::size_t N, typename Head, typename... Tail>
auto& my_get(MyTuple<Head, Tail...>& t) {
    // Замените throw на реализацию с if constexpr
    throw std::runtime_error("Not implemented");
    return t.value;  // заглушка, чтобы компилировалось
}

// TODO: реализуйте функцию my_tuple_size(const MyTuple<Types...>&)
// которая возвращает sizeof...(Types)
template <typename... Types>
constexpr std::size_t my_tuple_size(const MyTuple<Types...>&) {
    throw std::runtime_error("Not implemented");
    return 0;
}
