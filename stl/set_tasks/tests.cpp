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
// Задание 1: unique_elements
// =============================================================================

void test_unique_elements() {
    run_test("unique_elements: пустой вектор", [] {
        check_eq(unique_elements({}), std::set<int>{}, "пустой -> пустое множество");
    });
    run_test("unique_elements: без дубликатов", [] {
        check_eq(unique_elements({3, 1, 2}), (std::set<int>{1, 2, 3}), "элементы отсортированы");
    });
    run_test("unique_elements: с дубликатами", [] {
        check_eq(unique_elements({3, 1, 4, 1, 5, 9, 2, 6, 5}),
                 (std::set<int>{1, 2, 3, 4, 5, 6, 9}), "дубликаты удалены");
    });
    run_test("unique_elements: все одинаковые", [] {
        check_eq(unique_elements({7, 7, 7}), (std::set<int>{7}), "остаётся один");
    });
}

// =============================================================================
// Задание 2: intersection
// =============================================================================

void test_intersection() {
    run_test("intersection: оба пустые", [] {
        check_eq(intersection({}, {}), std::set<int>{}, "пустые -> пустое");
    });
    run_test("intersection: нет общих", [] {
        check_eq(intersection({1, 2}, {3, 4}), std::set<int>{}, "нет пересечения");
    });
    run_test("intersection: есть общие", [] {
        check_eq(intersection({1, 2, 3, 4}, {3, 4, 5, 6}), (std::set<int>{3, 4}), "{3,4}");
    });
    run_test("intersection: полное совпадение", [] {
        check_eq(intersection({1, 2, 3}, {1, 2, 3}), (std::set<int>{1, 2, 3}), "равные множества");
    });
    run_test("intersection: одно вложено в другое", [] {
        check_eq(intersection({1, 2, 3, 4, 5}, {2, 4}), (std::set<int>{2, 4}), "подмножество");
    });
}

// =============================================================================
// Задание 3: symmetric_difference
// =============================================================================

void test_symmetric_difference() {
    run_test("symmetric_difference: оба пустые", [] {
        check_eq(symmetric_difference({}, {}), std::set<int>{}, "пустые -> пустое");
    });
    run_test("symmetric_difference: нет общих", [] {
        check_eq(symmetric_difference({1, 2}, {3, 4}), (std::set<int>{1, 2, 3, 4}), "объединение");
    });
    run_test("symmetric_difference: есть общие", [] {
        check_eq(symmetric_difference({1, 2, 3}, {2, 3, 4}), (std::set<int>{1, 4}), "{1,4}");
    });
    run_test("symmetric_difference: равные множества", [] {
        check_eq(symmetric_difference({1, 2}, {1, 2}), std::set<int>{}, "равные -> пустое");
    });
    run_test("symmetric_difference: одно пустое", [] {
        check_eq(symmetric_difference({1, 2, 3}, {}), (std::set<int>{1, 2, 3}), "второе пустое");
    });
}

// =============================================================================
// Задание 4: has_pair_with_sum
// =============================================================================

void test_has_pair_with_sum() {
    run_test("has_pair_with_sum: пустое множество", [] {
        check(!has_pair_with_sum({}, 5), "пустое -> false");
    });
    run_test("has_pair_with_sum: один элемент", [] {
        check(!has_pair_with_sum({4}, 8), "один элемент не считается дважды");
    });
    run_test("has_pair_with_sum: пара существует", [] {
        check(has_pair_with_sum({1, 2, 3, 4}, 5), "1+4 или 2+3 == 5");
    });
    run_test("has_pair_with_sum: пары нет", [] {
        check(!has_pair_with_sum({1, 2, 3, 4}, 8), "нет пары с суммой 8");
    });
    run_test("has_pair_with_sum: отрицательные числа", [] {
        check(has_pair_with_sum({-3, -1, 0, 2, 4}, 1), "-1+2 == 1");
    });
    run_test("has_pair_with_sum: нулевая сумма", [] {
        check(has_pair_with_sum({-5, -2, 2, 5}, 0), "-5+5 или -2+2 == 0");
    });
}

// =============================================================================
// Задание 5: k_closest
// =============================================================================

void test_k_closest() {
    run_test("k_closest: исключение при k<0", [] {
        check_throws<std::invalid_argument>(
            [] { k_closest({1, 2, 3}, 2, -1); },
            "k<0 -> invalid_argument"
        );
    });
    run_test("k_closest: исключение при k > размеру", [] {
        check_throws<std::invalid_argument>(
            [] { k_closest({1, 2, 3}, 2, 5); },
            "k > size -> invalid_argument"
        );
    });
    run_test("k_closest: k=0", [] {
        check_eq(k_closest({1, 2, 3}, 2, 0), std::set<int>{}, "k=0 -> пустое множество");
    });
    run_test("k_closest: базовый пример", [] {
        check_eq(k_closest({1, 3, 5, 7, 9}, 6, 3), (std::set<int>{3, 5, 7}),
                 "|3-6|=3, |5-6|=1, |7-6|=1, |9-6|=3 — ближайшие {5,7}, третий — 3 или 9, берём 3");
    });
    run_test("k_closest: ничья — меньший побеждает", [] {
        check_eq(k_closest({1, 2, 3, 4, 5}, 3, 2), (std::set<int>{2, 3}),
                 "|2-3|=1, |3-3|=0 — ближайшие {3,2}");
    });
    run_test("k_closest: x в множестве", [] {
        check_eq(k_closest({1, 2, 3, 4, 5}, 3, 1), (std::set<int>{3}), "сам x ближе всего");
    });
    run_test("k_closest: все элементы", [] {
        check_eq(k_closest({1, 2, 3}, 5, 3), (std::set<int>{1, 2, 3}), "k == size");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_unique_elements();
    test_intersection();
    test_symmetric_difference();
    test_has_pair_with_sum();
    test_k_closest();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
