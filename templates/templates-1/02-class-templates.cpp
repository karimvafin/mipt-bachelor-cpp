// ============================================================
// Шаблоны классов (Class Templates)
// ============================================================
// Темы:
//   - Stack<T>: шаблонный стек
//   - Pair<T,U>: шаблонная пара
//   - Array<T,N>: массив фиксированного размера
//   - Определение методов вне тела класса
//   - Специализация отдельного метода
//   - Почему шаблоны должны быть в заголовочных файлах
// Компиляция: g++ -std=c++17 -Wall -o 02-class-templates 02-class-templates.cpp
// ============================================================

#include <iostream>
#include <stdexcept>
#include <string>

// ============================================================
// ВАЖНО: Почему шаблоны должны быть в .h / .hpp файлах?
// ============================================================
// Шаблон сам по себе — это не код, а инструкция для компилятора.
// Реальный код (машинные инструкции) генерируется только при
// инстанцировании, то есть когда компилятор видит, например, Stack<int>.
//
// Если определение шаблона находится в .cpp файле:
//   stack.cpp  -> компилируется в stack.o, но Stack<int> там НЕТ
//   main.cpp   -> видит только объявление, не может инстанцировать
//   Линкер ищет Stack<int> -> не находит -> ошибка!
//
// Решение: размещать определения шаблонов в заголовочных файлах,
// чтобы каждая единица трансляции могла самостоятельно генерировать
// нужные специализации.
// ============================================================

// ============================================================
// 1. Шаблон Stack<T>
// ============================================================
// Реализация стека на основе динамического массива.
// Методы объявлены внутри класса, но определены снаружи
// для демонстрации синтаксиса.

template <typename T>
class Stack {
public:
    // Конструктор по умолчанию
    Stack();

    // Конструктор с начальной ёмкостью
    explicit Stack(int initial_capacity);

    // Деструктор
    ~Stack();

    // Положить элемент на вершину стека
    void push(const T& value);

    // Снять элемент с вершины стека
    void pop();

    // Посмотреть верхний элемент (без удаления)
    const T& top() const;

    // Проверка: стек пуст?
    bool empty() const;

    // Количество элементов в стеке
    int size() const;

    // Вывести содержимое стека (снизу вверх)
    void print() const;

private:
    T*  data_;      // динамический массив элементов
    int size_;      // текущее количество элементов
    int capacity_;  // выделенная ёмкость

    // Удвоить ёмкость при переполнении
    void resize();
};

// ------------------------------------------------------------
// Определения методов Stack<T> вне тела класса
// Синтаксис: template <typename T>  ИмяКласса<T>::метод(...)
// ------------------------------------------------------------

template <typename T>
Stack<T>::Stack() : data_(new T[4]), size_(0), capacity_(4) {}

template <typename T>
Stack<T>::Stack(int initial_capacity)
    : data_(new T[initial_capacity]), size_(0), capacity_(initial_capacity) {}

template <typename T>
Stack<T>::~Stack() {
    delete[] data_;
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (size_ == capacity_) {
        resize();
    }
    data_[size_++] = value;
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::underflow_error("pop() на пустом стеке");
    }
    --size_;
}

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::underflow_error("top() на пустом стеке");
    }
    return data_[size_ - 1];
}

template <typename T>
bool Stack<T>::empty() const {
    return size_ == 0;
}

template <typename T>
int Stack<T>::size() const {
    return size_;
}

template <typename T>
void Stack<T>::print() const {
    std::cout << "Stack[";
    for (int i = 0; i < size_; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << data_[i];
    }
    std::cout << "] <- top\n";
}

template <typename T>
void Stack<T>::resize() {
    int new_capacity = capacity_ * 2;
    T* new_data = new T[new_capacity];
    for (int i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

// ============================================================
// 2. Шаблон Pair<T, U>
// ============================================================
// Простая пара с двумя разнотипными полями.
// Демонстрирует шаблон с двумя параметрами типа.

template <typename T, typename U>
class Pair {
public:
    T first;
    U second;

    Pair(const T& f, const U& s) : first(f), second(s) {}

    void print() const;

    // Обменять значения first и second (доступно только когда T == U,
    // но C++ позволяет определить метод — он просто не будет компилироваться,
    // если типы не совместимы; здесь для простоты требуем T == U явно).
    void swap_values();
};

template <typename T, typename U>
void Pair<T, U>::print() const {
    std::cout << "Pair(" << first << ", " << second << ")\n";
}

template <typename T, typename U>
void Pair<T, U>::swap_values() {
    // Это скомпилируется только если T и U совместимы по присваиванию.
    T temp = first;
    first  = static_cast<T>(second);
    second = static_cast<U>(temp);
}

// ============================================================
// 3. Шаблон Array<T, N>: массив фиксированного размера
// ============================================================
// N — нетиповой параметр шаблона (non-type template parameter).
// Размер определяется на этапе компиляции, память на стеке.

template <typename T, int N>
class Array {
public:
    // Доступ по индексу с проверкой границ
    T& operator[](int index) {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Индекс Array<T,N> вне диапазона");
        }
        return data_[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Индекс Array<T,N> вне диапазона");
        }
        return data_[index];
    }

    // Размер известен на этапе компиляции
    constexpr int size() const { return N; }

    // Заполнить все элементы значением
    void fill(const T& value);

    // Вывести массив
    void print() const;

private:
    T data_[N];  // массив на стеке, размер N задан шаблоном
};

template <typename T, int N>
void Array<T, N>::fill(const T& value) {
    for (int i = 0; i < N; ++i) {
        data_[i] = value;
    }
}

template <typename T, int N>
void Array<T, N>::print() const {
    std::cout << "Array<" << N << ">[";
    for (int i = 0; i < N; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << data_[i];
    }
    std::cout << "]\n";
}

// ============================================================
// Частичная специализация Array<bool, N>
// ============================================================
// В C++ нельзя специализировать отдельный метод шаблонного класса,
// если класс сам по себе частично специализирован (т.е. N остаётся
// переменным). Правильное решение — полностью специализировать
// класс для T = bool.
//
// Здесь Array<bool, N> предоставляет ту же функциональность,
// но метод print() выводит "true"/"false" вместо 1/0.

template <int N>
class Array<bool, N> {
public:
    bool& operator[](int index) {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Индекс Array<bool,N> вне диапазона");
        }
        return data_[index];
    }

    const bool& operator[](int index) const {
        if (index < 0 || index >= N) {
            throw std::out_of_range("Индекс Array<bool,N> вне диапазона");
        }
        return data_[index];
    }

    constexpr int size() const { return N; }

    void fill(bool value) {
        for (int i = 0; i < N; ++i) data_[i] = value;
    }

    // Специализированный вывод: "true"/"false" вместо 1/0
    void print() const {
        std::cout << "Array<bool," << N << ">[";
        for (int i = 0; i < N; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << (data_[i] ? "true" : "false");
        }
        std::cout << "]\n";
    }

private:
    bool data_[N];
};

// ============================================================
// main
// ============================================================

int main() {
    std::cout << "=== 1. Stack<T> ===\n";

    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    int_stack.print();
    std::cout << "top = " << int_stack.top() << "\n";
    int_stack.pop();
    std::cout << "После pop: ";
    int_stack.print();

    Stack<std::string> str_stack;
    str_stack.push("яблоко");
    str_stack.push("банан");
    str_stack.push("вишня");
    str_stack.print();
    std::cout << "Размер стека строк: " << str_stack.size() << "\n";

    // Проверка исключения на пустом стеке
    Stack<double> empty_stack;
    try {
        empty_stack.top();
    } catch (const std::underflow_error& e) {
        std::cout << "Исключение поймано: " << e.what() << "\n";
    }

    std::cout << "\n=== 2. Pair<T, U> ===\n";

    Pair<int, double> p1(42, 3.14);
    p1.print();

    Pair<std::string, int> p2("возраст", 21);
    p2.print();

    // Пара с одинаковыми типами — swap_values() будет работать корректно
    Pair<int, int> p3(10, 20);
    p3.print();
    p3.swap_values();
    std::cout << "После swap_values: ";
    p3.print();

    std::cout << "\n=== 3. Array<T, N> ===\n";

    Array<int, 5> arr;
    arr.fill(0);
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = (i + 1) * 10;
    }
    arr.print();

    Array<double, 3> darr;
    darr[0] = 1.1;
    darr[1] = 2.2;
    darr[2] = 3.3;
    darr.print();

    // Специализированный метод print() для bool
    Array<bool, 4> barr;
    barr[0] = true;
    barr[1] = false;
    barr[2] = true;
    barr[3] = true;
    barr.print();  // выводит "true"/"false", а не 1/0

    // Проверка исключения выхода за границы
    try {
        arr[10] = 99;
    } catch (const std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }

    std::cout << "\n=== Итог ===\n";
    std::cout << "Шаблоны классов: один класс — для любого типа.\n"
              << "Array<T,N>: размер N хранится как нетиповой параметр,\n"
              << "            память выделяется на стеке.\n";

    return 0;
}
