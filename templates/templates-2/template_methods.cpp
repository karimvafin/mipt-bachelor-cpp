// ============================================================
// Шаблонные методы внутри шаблонных классов (Member Templates)
// ============================================================
// Темы:
//   - Шаблонный метод в нешаблонном классе
//   - Шаблонный метод в шаблонном классе
//   - Конвертирующий конструктор (converting constructor)
//   - Шаблонный operator=
//   - Шаблонный метод с SFINAE / if constexpr
//   - Friend-шаблоны
//   - Проблемы и подводные камни
// Компиляция: g++ -std=c++17 -Wall -o template_methods template_methods.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// 1. Шаблонный метод в обычном (нешаблонном) классе
// ============================================================
// Класс сам по себе не шаблонный, но один из его методов — шаблонный.
// Это полезно, когда класс хранит данные одного типа,
// но должен уметь взаимодействовать с разными типами.

class Printer {
public:
    // Шаблонный метод: может принимать аргумент любого типа
    template <typename T>
    void print(const T& value) const {
        std::cout << "Printer::print -> " << value << "\n";
    }

    // Шаблонный метод с двумя параметрами
    template <typename T, typename U>
    void print_pair(const T& a, const U& b) const {
        std::cout << "Printer::print_pair -> (" << a << ", " << b << ")\n";
    }
};

// Вопрос 1: чем отличается шаблонный метод от шаблонного класса?
// Шаблонный метод параметризуется при каждом вызове метода,
// а шаблонный класс — при создании экземпляра класса.

// ============================================================
// 2. Шаблонный метод в шаблонном классе
// ============================================================
// Здесь класс параметризован типом T (основной тип контейнера),
// а некоторые методы дополнительно параметризованы типом U.

template <typename T>
class Container {
public:
    explicit Container(const T& value) : value_(value) {}

    // Обычный метод шаблонного класса
    const T& get() const { return value_; }

    // Шаблонный метод: конвертация из другого типа
    // U — это параметр метода, а не класса!
    template <typename U>
    void set_from(const U& other) {
        // static_cast позволяет конвертировать, если типы совместимы
        value_ = static_cast<T>(other);
    }

    void print() const {
        std::cout << "Container<T>::value = " << value_ << "\n";
    }

private:
    T value_;
};

// Вопрос 2: почему set_from не может быть обычным методом (не шаблонным)?
// Потому что U заранее неизвестен — мы хотим принимать любой совместимый тип.
// Если бы мы написали void set_from(const T& other), можно было бы передать
// только тот же тип T.

// ============================================================
// 3. Конвертирующий конструктор (converting constructor)
// ============================================================
// Один из самых частых примеров шаблонного метода в шаблонном классе.
// Позволяет создать Box<double> из Box<int>, например.

template <typename T>
class Box {
public:
    explicit Box(const T& val) : value_(val) {}

    // Конвертирующий конструктор: создаём Box<T> из Box<U>
    // U может быть любым типом, конвертируемым в T
    template <typename U>
    Box(const Box<U>& other) : value_(static_cast<T>(other.get())) {
        std::cout << "  [конвертирующий конструктор Box<U> -> Box<T>]\n";
    }

    const T& get() const { return value_; }

    // Конвертирующий operator=
    template <typename U>
    Box<T>& operator=(const Box<U>& other) {
        std::cout << "  [конвертирующий operator= Box<U> -> Box<T>]\n";
        value_ = static_cast<T>(other.get());
        return *this;
    }

    void print() const {
        std::cout << "Box<T>::value = " << value_ << "\n";
    }

private:
    T value_;
};

// Вопрос 3: почему конвертирующий конструктор не заменяет
// copy constructor?
// Шаблонный конструктор никогда не считается copy/move конструктором.
// Компилятор всё равно генерирует дефолтный copy constructor для Box<T>.
// Box<int>(const Box<int>&) — это copy constructor (неявно),
// Box<int>(const Box<double>&) — это конвертирующий (шаблонный).


// ============================================================
// 5. Friend-шаблоны
// ============================================================
// Проблема: как дать шаблонному классу доступ к приватным полям
// другой специализации того же шаблона?

template <typename T>
class Wrapper {
    // Делаем все специализации Wrapper друзьями друг другу.
    // Без этого Wrapper<double> не смог бы обратиться к value_ у Wrapper<int>.
    template <typename U>
    friend class Wrapper;

public:
    explicit Wrapper(const T& val) : value_(val) {}

    // Конвертирующий конструктор, обращающийся к приватному полю
    template <typename U>
    Wrapper(const Wrapper<U>& other) : value_(static_cast<T>(other.value_)) {
        // other.value_ доступен благодаря friend-объявлению
    }

    void print() const {
        std::cout << "Wrapper<T>::value = " << value_ << "\n";
    }

private:
    T value_;
};

// Вопрос 5: почему нужен friend?
// Wrapper<double> и Wrapper<int> — это РАЗНЫЕ классы.
// Один не имеет доступа к приватным полям другого без friend.

// ============================================================
// 6. Определение шаблонного метода вне класса
// ============================================================
// Синтаксис «двойного template»: сначала параметры класса,
// потом параметры метода.

template <typename T>
class Converter {
public:
    template <typename U>
    U convert_to() const;

private:
    T value_;

public:
    explicit Converter(const T& val) : value_(val) {}
};

// Определение вне класса — два template<...>:
// первый для класса, второй для метода
template <typename T>
template <typename U>
U Converter<T>::convert_to() const {
    return static_cast<U>(value_);
}

// Вопрос 5: можно ли поменять порядок template<typename T> и
// template<typename U> местами?
// Нет! Сначала всегда идут параметры внешнего шаблона (класса),
// потом параметры внутреннего (метода).

// ============================================================
// 6. Практический пример: шаблонный метод assign_from
//    в контейнере, принимающем итераторы
// ============================================================
// Это паттерн из STL: конструкторы и методы, принимающие
// пару итераторов произвольного типа.

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    // Шаблонный метод: заполнение из пары итераторов
    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        data_.clear();
        for (auto it = first; it != last; ++it) {
            data_.push_back(static_cast<T>(*it));
        }
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < data_.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]\n";
    }

    size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;
};

// Вопрос 6: почему в std::vector конструктор из двух итераторов —
// шаблонный метод, а не перегрузка для конкретного типа итератора?
// Потому что итераторы бывают разных типов: указатели, итераторы
// от другого контейнера, итераторы std::istream. Шаблон покрывает всё.

// ============================================================
// 7. Подводные камни
// ============================================================

// 7. Шаблонный виртуальный метод — ЗАПРЕЩЁН!
// class Base {
//     virtual template <typename T>   // ОШИБКА КОМПИЛЯЦИИ
//     void process(const T& val);
// };
// Причина: компилятор не может построить vtable, потому что
// не знает, сколько инстанций метода может быть.

// Вопрос 8: как обойти запрет на виртуальный шаблонный метод?
// Паттерн «type erasure» или использование std::function.
// Например, принимать std::function<void(...)> вместо шаблонного метода.

// ============================================================
// main
// ============================================================

int main() {
    std::cout << "=== 1. Шаблонный метод в обычном классе ===\n";
    Printer p;
    p.print(42);
    p.print(3.14);
    p.print(std::string("привет"));
    p.print_pair(1, "два");

    std::cout << "\n=== 2. Шаблонный метод в шаблонном классе ===\n";
    Container<double> c(0.0);
    c.print();
    c.set_from(42);      // int -> double
    c.print();
    c.set_from(3.14f);   // float -> double
    c.print();

    std::cout << "\n=== 3. Конвертирующий конструктор ===\n";
    Box<int> bi(42);
    Box<double> bd(bi);   // Box<int> -> Box<double>
    bd.print();

    Box<int> bi2(100);
    Box<double> bd2(0.0);
    bd2 = bi2;            // Box<int> -> Box<double> через operator=
    bd2.print();

    std::cout << "\n=== 4. Friend-шаблоны ===\n";
    Wrapper<int> wi(42);
    Wrapper<double> wd(wi);  // int -> double, доступ к private через friend
    wi.print();
    wd.print();

    std::cout << "\n=== 5. Определение вне класса (двойной template) ===\n";
    Converter<double> conv(3.14);
    int i = conv.convert_to<int>();
    float f = conv.convert_to<float>();
    std::cout << "convert_to<int>()   = " << i << "\n";
    std::cout << "convert_to<float>() = " << f << "\n";

    std::cout << "\n=== 6. Шаблонный метод с итераторами ===\n";
    std::vector<double> src = {1.1, 2.2, 3.3, 4.4};
    SimpleVector<int> sv;
    sv.assign(src.begin(), src.end());  // double -> int
    sv.print();

    int arr[] = {10, 20, 30};
    sv.assign(arr, arr + 3);           // из сырого массива
    sv.print();

    std::cout << "\n=== Итог ===\n";
    std::cout << "Шаблонный метод: template<typename U> внутри класса\n"
              << "Конвертирующий конструктор: Box<T>(const Box<U>&)\n"
              << "Двойной template при определении вне класса\n"
              << "Виртуальные шаблонные методы запрещены\n"
              << "Friend-шаблоны для доступа между специализациями\n";

    return 0;
}
