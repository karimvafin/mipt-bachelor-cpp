#include "tasks.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <cmath>

// =============================================================================
// Минимальный тест-раннер
// =============================================================================

static int g_total = 0;
static int g_failed = 0;

void run_test(const std::string& name, std::function<void()> test) {
    ++g_total;
    try {
        test();
        std::cout << "[PASS] " << name << "\n";
    } catch (const std::exception& e) {
        ++g_failed;
        std::cout << "[FAIL] " << name << " — " << e.what() << "\n";
    }
}

void check(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

template <typename T>
void check_eq(const T& actual, const T& expected, const std::string& message) {
    if (actual != expected) {
        throw std::runtime_error(message);
    }
}

void check_near(double actual, double expected, double eps, const std::string& message) {
    if (std::abs(actual - expected) > eps) {
        throw std::runtime_error(message);
    }
}

template <typename E>
void check_throws(std::function<void()> fn, const std::string& message) {
    try {
        fn();
    } catch (const E&) {
        return;
    } catch (...) {
        throw std::runtime_error(message + " (неверный тип исключения)");
    }
    throw std::runtime_error(message + " (исключение не было брошено)");
}

// =============================================================================
// Задание 1: my_min
// =============================================================================

void test_my_min() {
    run_test("my_min: int", [] {
        check_eq(my_min(3, 7), 3, "my_min(3, 7) должен быть 3");
    });
    run_test("my_min: int равные", [] {
        check_eq(my_min(5, 5), 5, "my_min(5, 5) должен быть 5");
    });
    run_test("my_min: double", [] {
        check_near(my_min(3.14, 2.71), 2.71, 1e-9, "my_min(3.14, 2.71) должен быть 2.71");
    });
    run_test("my_min: string", [] {
        check_eq(my_min(std::string("abc"), std::string("xyz")),
                 std::string("abc"), "my_min(abc, xyz) должен быть abc");
    });
    run_test("my_min: отрицательные", [] {
        check_eq(my_min(-10, -3), -10, "my_min(-10, -3) должен быть -10");
    });
}

// =============================================================================
// Задание 2: Box<T>
// =============================================================================

void test_box() {
    run_test("Box<int>: конструктор и get", [] {
        Box<int> b(42);
        check_eq(b.get(), 42, "get() должен вернуть 42");
    });
    run_test("Box<int>: set", [] {
        Box<int> b(0);
        b.set(99);
        check_eq(b.get(), 99, "после set(99) get() должен вернуть 99");
    });
    run_test("Box<double>: to_string", [] {
        Box<double> b(3.14);
        std::string s = b.to_string();
        check(!s.empty(), "to_string() не должен быть пустым");
    });
    run_test("Box<string>: get и set", [] {
        Box<std::string> b(std::string("hello"));
        check_eq(b.get(), std::string("hello"), "get() должен вернуть hello");
        b.set("world");
        check_eq(b.get(), std::string("world"), "после set() должен быть world");
    });
    run_test("Box<int>: to_string корректность", [] {
        Box<int> b(42);
        check_eq(b.to_string(), std::string("42"), "to_string() для 42");
    });
}

// =============================================================================
// Задание 3: FixedArray<T, N>
// =============================================================================

void test_fixed_array() {
    run_test("FixedArray: size", [] {
        FixedArray<int, 5> a;
        check_eq(a.size(), 5, "size() должен быть 5");
    });
    run_test("FixedArray: fill и at", [] {
        FixedArray<int, 3> a;
        a.fill(7);
        check_eq(a.at(0), 7, "at(0) должен быть 7");
        check_eq(a.at(1), 7, "at(1) должен быть 7");
        check_eq(a.at(2), 7, "at(2) должен быть 7");
    });
    run_test("FixedArray: operator[]", [] {
        FixedArray<int, 3> a;
        a.fill(0);
        a[0] = 10;
        a[1] = 20;
        a[2] = 30;
        check_eq(a[0], 10, "a[0] должен быть 10");
        check_eq(a[1], 20, "a[1] должен быть 20");
        check_eq(a[2], 30, "a[2] должен быть 30");
    });
    run_test("FixedArray: out_of_range", [] {
        FixedArray<int, 3> a;
        a.fill(0);
        check_throws<std::out_of_range>(
            [&] { a.at(5); },
            "at(5) должен бросить std::out_of_range"
        );
    });
    run_test("FixedArray: out_of_range отрицательный", [] {
        FixedArray<int, 3> a;
        a.fill(0);
        check_throws<std::out_of_range>(
            [&] { a.at(-1); },
            "at(-1) должен бросить std::out_of_range"
        );
    });
    run_test("FixedArray<string, 2>", [] {
        FixedArray<std::string, 2> a;
        a.fill("hello");
        check_eq(a.at(0), std::string("hello"), "at(0) должен быть hello");
        check_eq(a.at(1), std::string("hello"), "at(1) должен быть hello");
    });
}

// =============================================================================
// Задание 4: Converter<T>
// =============================================================================

void test_converter() {
    run_test("Converter<double>: convert_to<int>", [] {
        Converter<double> c(3.14);
        check_eq(c.convert_to<int>(), 3, "3.14 -> int должен быть 3");
    });
    run_test("Converter<double>: get", [] {
        Converter<double> c(2.71);
        check_near(c.get(), 2.71, 1e-9, "get() должен вернуть 2.71");
    });
    run_test("Converter<int>: convert_to<double>", [] {
        Converter<int> c(42);
        check_near(c.convert_to<double>(), 42.0, 1e-9, "42 -> double должен быть 42.0");
    });
    run_test("Converter<int>: convert_to<char>", [] {
        Converter<int> c(65);
        check_eq(c.convert_to<char>(), 'A', "65 -> char должен быть 'A'");
    });
    run_test("Converter<float>: convert_to<int>", [] {
        Converter<float> c(9.99f);
        check_eq(c.convert_to<int>(), 9, "9.99f -> int должен быть 9");
    });
}

// =============================================================================
// Задание 5: Pair<T, U> с конвертирующим конструктором
// =============================================================================

void test_pair() {
    run_test("Pair<int, int>: базовый конструктор", [] {
        Pair<int, int> p(1, 2);
        check_eq(p.first(), 1, "first() должен быть 1");
        check_eq(p.second(), 2, "second() должен быть 2");
    });
    run_test("Pair<string, double>", [] {
        Pair<std::string, double> p(std::string("hello"), 3.14);
        check_eq(p.first(), std::string("hello"), "first() должен быть hello");
        check_near(p.second(), 3.14, 1e-9, "second() должен быть 3.14");
    });
    run_test("Pair: конвертирующий конструктор int->double", [] {
        Pair<int, int> p1(10, 20);
        Pair<double, double> p2(p1);
        check_near(p2.first(), 10.0, 1e-9, "first() должен быть 10.0");
        check_near(p2.second(), 20.0, 1e-9, "second() должен быть 20.0");
    });
    run_test("Pair: конвертирующий конструктор double->int", [] {
        Pair<double, double> p1(3.7, 8.2);
        Pair<int, int> p2(p1);
        check_eq(p2.first(), 3, "first() должен быть 3 (усечение)");
        check_eq(p2.second(), 8, "second() должен быть 8 (усечение)");
    });
    run_test("Pair: конвертирующий конструктор смешанный", [] {
        Pair<int, double> p1(42, 2.5);
        Pair<double, int> p2(p1);
        check_near(p2.first(), 42.0, 1e-9, "first() int->double");
        check_eq(p2.second(), 2, "second() double->int (усечение)");
    });
}

// =============================================================================
// Задание 6: sum_all
// =============================================================================

void test_sum_all() {
    run_test("sum_all: пустой вызов", [] {
        check_eq(sum_all(), 0, "sum_all() должен быть 0");
    });
    run_test("sum_all: один аргумент", [] {
        check_eq(sum_all(42), 42, "sum_all(42) должен быть 42");
    });
    run_test("sum_all: несколько int", [] {
        check_eq(sum_all(1, 2, 3, 4, 5), 15, "sum_all(1,2,3,4,5) должен быть 15");
    });
    run_test("sum_all: double", [] {
        check_near(sum_all(1.5, 2.5), 4.0, 1e-9, "sum_all(1.5, 2.5) должен быть 4.0");
    });
    run_test("sum_all: отрицательные", [] {
        check_eq(sum_all(-1, -2, -3), -6, "sum_all(-1,-2,-3) должен быть -6");
    });
}

// =============================================================================
// Задание 7: count_if_positive
// =============================================================================

void test_count_if_positive() {
    run_test("count_if_positive: пустой вызов", [] {
        check_eq(count_if_positive(), 0, "пустой вызов -> 0");
    });
    run_test("count_if_positive: все положительные", [] {
        check_eq(count_if_positive(1, 2, 3), 3, "все 3 положительные");
    });
    run_test("count_if_positive: все отрицательные", [] {
        check_eq(count_if_positive(-1, -2, -3), 0, "нет положительных");
    });
    run_test("count_if_positive: смешанные", [] {
        check_eq(count_if_positive(1, -2, 3, 0, 5), 3, "три положительных");
    });
    run_test("count_if_positive: ноль не считается", [] {
        check_eq(count_if_positive(0, 0, 0), 0, "нули не положительные");
    });
    run_test("count_if_positive: double", [] {
        check_eq(count_if_positive(1.5, -0.5, 2.0), 2, "два положительных double");
    });
}

// =============================================================================
// Задание 8: concat_all
// =============================================================================

void test_concat_all() {
    run_test("concat_all: пустой вызов", [] {
        check_eq(concat_all(), std::string(""), "пустой -> пустая строка");
    });
    run_test("concat_all: один аргумент string", [] {
        check_eq(concat_all("hello"), std::string("hello"), "один аргумент");
    });
    run_test("concat_all: int", [] {
        check_eq(concat_all(42), std::string("42"), "число 42");
    });
    run_test("concat_all: несколько аргументов", [] {
        std::string result = concat_all(1, " + ", 2, " = ", 3);
        check_eq(result, std::string("1 + 2 = 3"), "1 + 2 = 3");
    });
    run_test("concat_all: разные типы", [] {
        std::string result = concat_all("x=", 42, " y=", 3.14);
        // Проверяем начало, т.к. точное представление double может варьироваться
        check(result.substr(0, 4) == "x=42", "должно начинаться с x=42");
    });
}

// =============================================================================
// Задание 9: transform_to_vector
// =============================================================================

void test_transform_to_vector() {
    run_test("transform_to_vector: квадраты", [] {
        auto result = transform_to_vector([](int x) { return x * x; }, 1, 2, 3, 4);
        check_eq(result, (std::vector<int>{1, 4, 9, 16}), "квадраты 1..4");
    });
    run_test("transform_to_vector: +1", [] {
        auto result = transform_to_vector([](int x) { return x + 1; }, 10, 20, 30);
        check_eq(result, (std::vector<int>{11, 21, 31}), "+1 к каждому");
    });
    run_test("transform_to_vector: один элемент", [] {
        auto result = transform_to_vector([](int x) { return x * 2; }, 5);
        check_eq(result, (std::vector<int>{10}), "5 * 2 = 10");
    });
    run_test("transform_to_vector: отрицательные", [] {
        auto result = transform_to_vector([](int x) { return -x; }, 1, -2, 3);
        check_eq(result, (std::vector<int>{-1, 2, -3}), "отрицание");
    });
}

// =============================================================================
// Задание 10: MyTuple
// =============================================================================

void test_my_tuple() {
    run_test("MyTuple<int>: один элемент", [] {
        MyTuple<int> t(42);
        check_eq(my_get<0>(t), 42, "get<0> должен быть 42");
    });
    run_test("MyTuple<int, double>: два элемента", [] {
        MyTuple<int, double> t(1, 2.5);
        check_eq(my_get<0>(t), 1, "get<0> должен быть 1");
        check_near(my_get<1>(t), 2.5, 1e-9, "get<1> должен быть 2.5");
    });
    run_test("MyTuple<int, double, string>: три элемента", [] {
        MyTuple<int, double, std::string> t(42, 3.14, std::string("hello"));
        check_eq(my_get<0>(t), 42, "get<0> должен быть 42");
        check_near(my_get<1>(t), 3.14, 1e-9, "get<1> должен быть 3.14");
        // check_eq(my_get<2>(t), std::string("hello"), "get<2> должен быть hello");
    });
    run_test("MyTuple: изменение через get", [] {
        MyTuple<int, std::string> t(0, std::string("old"));
        my_get<0>(t) = 99;
        // my_get<1>(t) = "new";
        check_eq(my_get<0>(t), 99, "после изменения get<0> должен быть 99");
        // check_eq(my_get<1>(t), std::string("new"), "после изменения get<1> должен быть new");
    });
    run_test("MyTuple: my_tuple_size", [] {
        MyTuple<int, double, std::string> t(1, 2.0, std::string("x"));
        check_eq(static_cast<int>(my_tuple_size(t)), 3, "размер должен быть 3");
    });
    run_test("MyTuple: пустой кортеж", [] {
        MyTuple<> t;
        check_eq(static_cast<int>(my_tuple_size(t)), 0, "размер пустого кортежа 0");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_my_min();
    test_box();
    test_fixed_array();
    test_converter();
    test_pair();
    test_sum_all();
    test_count_if_positive();
    test_concat_all();
    test_transform_to_vector();
    test_my_tuple();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
