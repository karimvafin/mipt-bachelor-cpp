#include "tasks.h"

#include <iostream>
#include <string>
#include <functional>

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
    if (!condition) throw std::runtime_error(message);
}

template <typename T>
void check_eq(const T& actual, const T& expected, const std::string& message) {
    if (actual != expected) throw std::runtime_error(message);
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
// Задание 1: sum
// =============================================================================

void test_sum() {
    run_test("sum: пустой список", [] {
        check_eq(sum({}), 0, "sum({}) должен быть 0");
    });
    run_test("sum: один элемент", [] {
        check_eq(sum({7}), 7, "sum({7}) должен быть 7");
    });
    run_test("sum: положительные числа", [] {
        check_eq(sum({1, 2, 3, 4}), 10, "sum({1,2,3,4}) == 10");
    });
    run_test("sum: отрицательные числа", [] {
        check_eq(sum({-1, -2, -3}), -6, "sum({-1,-2,-3}) == -6");
    });
    run_test("sum: смешанные числа", [] {
        check_eq(sum({-5, 10, -3, 8}), 10, "sum({-5,10,-3,8}) == 10");
    });
}

// =============================================================================
// Задание 2: remove_if_even
// =============================================================================

void test_remove_if_even() {
    run_test("remove_if_even: пустой список", [] {
        std::list<int> l = {};
        remove_if_even(l);
        check_eq(l, std::list<int>{}, "пустой остаётся пустым");
    });
    run_test("remove_if_even: все чётные", [] {
        std::list<int> l = {2, 4, 6};
        remove_if_even(l);
        check_eq(l, std::list<int>{}, "все удалены");
    });
    run_test("remove_if_even: все нечётные", [] {
        std::list<int> l = {1, 3, 5};
        remove_if_even(l);
        check_eq(l, (std::list<int>{1, 3, 5}), "ничего не изменилось");
    });
    run_test("remove_if_even: смешанные", [] {
        std::list<int> l = {1, 2, 3, 4, 5};
        remove_if_even(l);
        check_eq(l, (std::list<int>{1, 3, 5}), "остались только нечётные");
    });
    run_test("remove_if_even: ноль считается чётным", [] {
        std::list<int> l = {0, 1, 0};
        remove_if_even(l);
        check_eq(l, (std::list<int>{1}), "нули удалены");
    });
    run_test("remove_if_even: отрицательные чётные", [] {
        std::list<int> l = {-4, -3, -2, -1};
        remove_if_even(l);
        check_eq(l, (std::list<int>{-3, -1}), "отрицательные чётные удалены");
    });
}

// =============================================================================
// Задание 3: flatten
// =============================================================================

void test_flatten() {
    run_test("flatten: пустой внешний список", [] {
        check_eq(flatten({}), std::list<int>{}, "пустой -> пустой");
    });
    run_test("flatten: пустые внутренние списки", [] {
        check_eq(flatten({{}, {}, {}}), std::list<int>{}, "все пустые");
    });
    run_test("flatten: один внутренний список", [] {
        check_eq(flatten({{1, 2, 3}}), (std::list<int>{1, 2, 3}), "один список");
    });
    run_test("flatten: несколько списков", [] {
        check_eq(flatten({{1, 2}, {3}, {4, 5}}), (std::list<int>{1, 2, 3, 4, 5}), "три списка");
    });
    run_test("flatten: пустые списки в середине", [] {
        check_eq(flatten({{1}, {}, {2, 3}}), (std::list<int>{1, 2, 3}), "пустой в середине");
    });
}

// =============================================================================
// Задание 4: interleave
// =============================================================================

void test_interleave() {
    run_test("interleave: оба пустые", [] {
        std::list<int> a = {}, b = {};
        interleave(a, b);
        check_eq(a, std::list<int>{}, "a пустой");
        check_eq(b, std::list<int>{}, "b пустой");
    });
    run_test("interleave: a пустой", [] {
        std::list<int> a = {}, b = {1, 2, 3};
        interleave(a, b);
        check_eq(a, (std::list<int>{1, 2, 3}), "элементы b перенесены в a");
        check_eq(b, std::list<int>{}, "b стал пустым");
    });
    run_test("interleave: b пустой", [] {
        std::list<int> a = {1, 2, 3}, b = {};
        interleave(a, b);
        check_eq(a, (std::list<int>{1, 2, 3}), "a не изменился");
        check_eq(b, std::list<int>{}, "b остался пустым");
    });
    run_test("interleave: одинаковая длина", [] {
        std::list<int> a = {1, 3, 5}, b = {2, 4, 6};
        interleave(a, b);
        check_eq(a, (std::list<int>{1, 2, 3, 4, 5, 6}), "чередование");
        check_eq(b, std::list<int>{}, "b стал пустым");
    });
    run_test("interleave: a длиннее b", [] {
        std::list<int> a = {1, 3, 5}, b = {2, 4};
        interleave(a, b);
        check_eq(a, (std::list<int>{1, 2, 3, 4, 5}), "хвост из a");
        check_eq(b, std::list<int>{}, "b стал пустым");
    });
    run_test("interleave: b длиннее a", [] {
        std::list<int> a = {1}, b = {2, 3, 4};
        interleave(a, b);
        check_eq(a, (std::list<int>{1, 2, 3, 4}), "хвост из b");
        check_eq(b, std::list<int>{}, "b стал пустым");
    });
}

// =============================================================================
// Задание 5: is_palindrome
// =============================================================================

void test_is_palindrome() {
    run_test("is_palindrome: пустой список", [] {
        check(is_palindrome({}), "пустой список — палиндром");
    });
    run_test("is_palindrome: один элемент", [] {
        check(is_palindrome({7}), "один элемент — палиндром");
    });
    run_test("is_palindrome: два одинаковых", [] {
        check(is_palindrome({3, 3}), "{3,3} — палиндром");
    });
    run_test("is_palindrome: два разных", [] {
        check(!is_palindrome({1, 2}), "{1,2} — не палиндром");
    });
    run_test("is_palindrome: нечётной длины", [] {
        check(is_palindrome({1, 2, 3, 2, 1}), "{1,2,3,2,1} — палиндром");
    });
    run_test("is_palindrome: чётной длины", [] {
        check(is_palindrome({1, 2, 2, 1}), "{1,2,2,1} — палиндром");
    });
    run_test("is_palindrome: не палиндром", [] {
        check(!is_palindrome({1, 2, 3}), "{1,2,3} — не палиндром");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_sum();
    test_remove_if_even();
    test_flatten();
    test_interleave();
    test_is_palindrome();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
