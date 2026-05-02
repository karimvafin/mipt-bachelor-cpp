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
    return (a < b) ? a : b;
}

// -----------------------------------------------------------------------------
template <typename T>
class Box {
public:
    explicit Box(const T& value) : value_(value) {}

    const T& get() const {
        return value_;
    }


    void set(const T& value) {
        value_ = value;
    }
    std::string to_string() const {
        std::ostringstream oss;
        oss << value_;
        return oss.str();
    }

private:
    T value_;
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
public:
    T& at(int index) {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }


    T& operator[](int index) {
        return data_[index];
    }

    const T& operator[](int index) const {
        return data_[index];
    }


    int size() const {
        return N;
    }


    void fill(const T& value) {
        for (int i = 0; i < N; ++i) {
            data_[i] = value;
        }
    }

private:
    T data_[N];
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
public:
    explicit Converter(const T& value) : value_(value) {}

    const T& get() const {
        return value_;
    }

    template <typename U>
    U convert_to() const {
        return static_cast<U>(value_);
    }

private:
    T value_;
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
    // Обычный конструктор
    Pair(const T& f, const U& s) : first_(f), second_(s) {}

    // Конвертирующий конструктор
    template <typename T2, typename U2>
    Pair(const Pair<T2, U2>& other)
        : first_(static_cast<T>(other.first())),
          second_(static_cast<U>(other.second())) {}

    const T& first() const {
        return first_;
    }

    const U& second() const {
        return second_;
    }

private:
    T first_;
    U second_;
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
    return (args + ... + 0);
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
    return ((args > 0 ? 1 : 0) + ... + 0);
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
    ((oss << args << " "), ...);

    std::string result = oss.str();
    if (!result.empty()) {
        result.pop_back(); 
    }
    return result;
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
    return std::vector{ func(args)... };
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

template <typename... Types>
struct MyTuple {};


template <typename Head, typename... Tail>
struct MyTuple<Head, Tail...> : MyTuple<Tail...> {
    Head value;

    MyTuple() = default;

    MyTuple(const Head& h, const Tail&... t)
        : MyTuple<Tail...>(t...), value(h) {}
};
template <std::size_t N, typename Head, typename... Tail>
auto& my_get(MyTuple<Head, Tail...>& t) {
    if constexpr (N == 0) {
        return t.value;
    } else {
        return my_get<N - 1>(static_cast<MyTuple<Tail...>&>(t));
    }
}
template <typename... Types>
constexpr std::size_t my_tuple_size(const MyTuple<Types...>&) {
    return sizeof...(Types);
}