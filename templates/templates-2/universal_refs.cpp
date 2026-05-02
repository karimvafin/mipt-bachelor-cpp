#include <iostream>
#include <vector>

class A {
    int x_;
    float y_;

public:
    A(int x, float y): x_(x), y_(y) {
        std::cout << "ctor" << std::endl;
    }

    ~A() {
        std::cout << "dtor" << std::endl;
    }

    A(const A& other) {
        std::cout << "copy ctor" << std::endl;
        x_ = other.x_;
        y_ = other.y_;
    }

    A(A&& other) {
        std::cout << "move ctor" << std::endl;
        x_ = other.x_;
        y_ = other.y_;
    }
};

// не работает со ссылками
// wrapper(ref_x, ref_y);
template <typename T1, typename T2>
void wrapper(T1 e1, T2 e2) {
    func(e1, e2);
}

// не работает с rvalue
// wrapper(1, 3.14);
template <typename T1, typename T2>
void wrapper(T1& e1, T2& e2) {
    func(e1, e2);
}

// не работает с non-const ref
// wrapper(ref_x, ref_y);
template <typename T1, typename T2>
void wrapper(const T1& e1, const T2& e2) {
    func(e1, e2);
}

// решение -- определить 4 случая:
template <typename T1, typename T2>
void wrapper(T1& e1, T2& e2);

template <typename T1, typename T2>
void wrapper(const T1& e1, const T2& e2);

template <typename T1, typename T2>
void wrapper(T1& e1, const T2& e2);

template <typename T1, typename T2>
void wrapper(const T1& e1, T2& e2);

// проблема -- увеличение количества параметров (2^n перегрузок)

// сжатие ссылок
template <typename T>
void baz(T t) {
    T& k = t;
}

// int i = 1;
// baz<int&>(i);

// Правила сжатия -- одиночный & всегда побеждает
// & & = &
// && & = &
// & && = &
// && && = &&

template <typename T>
void func(T&& t) {}

// func(4) rvalue, T = int
// 
// double d = 3.14;
// func(d); lvalue, T = double&
//
// float f() {...}
// func(f()); rvalue, T = float
//

// Perfect forwarding
template <typename T1, typename T2>
void wrapper(T1&& e1, T2&& e2) {
    func(std::forward<T1>(e1), std::forward<T2>(e2));
}

// forward
template <typename T>
T&& forward(typename std::remove_reference<T>::type& T) noexcept {
    return static_cast<T&&>(t);
}



int main() {
    std::vector<A> vec;
    A a1(1, 1.0f);
    vec.push_back(a1);
    // vec.push_back(std::move(a1));
    // vec.push_back(A(1, 1.0f));
    // vec.emplace_back(2, 2.0f);

    int ii = 1;
    float ff = 1.0f;
    wrapper(ii, ff);

    // int& && forward(int& t) noexcept {
    //     return static_cast<int& &&>(t);
    // }

    // Применим правила сжатия
    // int& forward(int& t) noexcept {
    //     return static_cast<int&>(t);
    // }
    // Итог -- передача по ссылке lvalue

    wrapper(42, 3.14f);

    // int&& forward(int& t) noexcept {
    //     return static_cast<int&&>(t);
    // }
    // Итог -- передача rvalue ссылки

    // Примеры использования
    // emplace_back
    vec.emplace_back(3, 3.0f);
    // make_unique
    auto u_ptr = std::make_unique<A>(3, 3.0f);
}