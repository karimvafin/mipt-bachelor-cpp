#include "tasks.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>

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

// Бросает std::runtime_error с описанием, если условие ложно
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

// Ожидаем, что вызов бросит исключение типа E
template <typename E>
void check_throws(std::function<void()> fn, const std::string& message) {
    try {
        fn();
    } catch (const E&) {
        return; // ожидаемое исключение
    } catch (...) {
        throw std::runtime_error(message + " (неверный тип исключения)");
    }
    throw std::runtime_error(message + " (исключение не было брошено)");
}

// =============================================================================
// Задание 1: sum
// =============================================================================

void test_sum() {
    run_test("sum: пустой вектор", [] {
        check_eq(sum({}), 0, "sum({}) должен быть 0");
    });
    run_test("sum: один элемент", [] {
        check_eq(sum({42}), 42, "sum({42}) должен быть 42");
    });
    run_test("sum: положительные числа", [] {
        check_eq(sum({1, 2, 3, 4}), 10, "sum({1,2,3,4}) должен быть 10");
    });
    run_test("sum: отрицательные числа", [] {
        check_eq(sum({-1, -2, -3}), -6, "sum({-1,-2,-3}) должен быть -6");
    });
    run_test("sum: смешанные числа", [] {
        check_eq(sum({-5, 10, -3, 8}), 10, "sum({-5,10,-3,8}) должен быть 10");
    });
}

// =============================================================================
// Задание 2: filter_even
// =============================================================================

void test_filter_even() {
    run_test("filter_even: пустой вектор", [] {
        check_eq(filter_even({}), std::vector<int>{}, "должен вернуть пустой вектор");
    });
    run_test("filter_even: все нечётные", [] {
        check_eq(filter_even({1, 3, 5, 7}), std::vector<int>{}, "нет чётных элементов");
    });
    run_test("filter_even: все чётные", [] {
        check_eq(filter_even({2, 4, 6}), (std::vector<int>{2, 4, 6}), "все элементы чётные");
    });
    run_test("filter_even: смешанные", [] {
        check_eq(filter_even({1, 2, 3, 4, 5, 6}), (std::vector<int>{2, 4, 6}), "только {2,4,6}");
    });
    run_test("filter_even: отрицательные чётные", [] {
        check_eq(filter_even({-4, -3, -2, -1, 0}), (std::vector<int>{-4, -2, 0}), "только {-4,-2,0}");
    });
    run_test("filter_even: порядок сохраняется", [] {
        check_eq(filter_even({6, 1, 4, 3, 2}), (std::vector<int>{6, 4, 2}), "порядок: {6,4,2}");
    });
}

// =============================================================================
// Задание 3: rotate_left
// =============================================================================

void test_rotate_left() {
    run_test("rotate_left: сдвиг на 0", [] {
        std::vector<int> v = {1, 2, 3, 4, 5};
        rotate_left(v, 0);
        check_eq(v, (std::vector<int>{1, 2, 3, 4, 5}), "сдвиг на 0 не меняет вектор");
    });
    run_test("rotate_left: сдвиг на 1", [] {
        std::vector<int> v = {1, 2, 3, 4, 5};
        rotate_left(v, 1);
        check_eq(v, (std::vector<int>{2, 3, 4, 5, 1}), "сдвиг на 1");
    });
    run_test("rotate_left: сдвиг на 2", [] {
        std::vector<int> v = {1, 2, 3, 4, 5};
        rotate_left(v, 2);
        check_eq(v, (std::vector<int>{3, 4, 5, 1, 2}), "сдвиг на 2");
    });
    run_test("rotate_left: сдвиг на длину вектора", [] {
        std::vector<int> v = {1, 2, 3};
        rotate_left(v, 3);
        check_eq(v, (std::vector<int>{1, 2, 3}), "сдвиг на n эквивалентен сдвигу на 0");
    });
    run_test("rotate_left: сдвиг больше длины", [] {
        std::vector<int> v = {1, 2, 3, 4, 5};
        rotate_left(v, 7);
        check_eq(v, (std::vector<int>{3, 4, 5, 1, 2}), "7 % 5 == 2, сдвиг на 2");
    });
    run_test("rotate_left: пустой вектор", [] {
        std::vector<int> v = {};
        rotate_left(v, 3);
        check_eq(v, std::vector<int>{}, "пустой вектор не меняется");
    });
    run_test("rotate_left: один элемент", [] {
        std::vector<int> v = {42};
        rotate_left(v, 5);
        check_eq(v, (std::vector<int>{42}), "один элемент всегда остаётся");
    });
}

// =============================================================================
// Задание 4: remove_duplicates
// =============================================================================

void test_remove_duplicates() {
    run_test("remove_duplicates: пустой вектор", [] {
        check_eq(remove_duplicates({}), std::vector<int>{}, "пустой -> пустой");
    });
    run_test("remove_duplicates: нет дубликатов", [] {
        check_eq(remove_duplicates({1, 2, 3}), (std::vector<int>{1, 2, 3}), "без изменений");
    });
    run_test("remove_duplicates: все одинаковые", [] {
        check_eq(remove_duplicates({5, 5, 5, 5}), (std::vector<int>{5}), "остаётся одно");
    });
    run_test("remove_duplicates: смешанные дубликаты", [] {
        check_eq(remove_duplicates({3, 1, 4, 1, 5, 9, 2, 6, 5}),
                 (std::vector<int>{3, 1, 4, 5, 9, 2, 6}), "удаляем повторы");
    });
    run_test("remove_duplicates: порядок сохраняется", [] {
        check_eq(remove_duplicates({4, 2, 4, 1, 2}), (std::vector<int>{4, 2, 1}), "порядок первых вхождений");
    });
    run_test("remove_duplicates: отрицательные числа", [] {
        check_eq(remove_duplicates({-1, -2, -1, -3, -2}), (std::vector<int>{-1, -2, -3}), "отрицательные");
    });
}

// =============================================================================
// Задание 5: flatten
// =============================================================================

void test_flatten() {
    run_test("flatten: пустой внешний вектор", [] {
        check_eq(flatten({}), std::vector<int>{}, "пустой -> пустой");
    });
    run_test("flatten: пустые внутренние векторы", [] {
        check_eq(flatten({{}, {}, {}}), std::vector<int>{}, "все строки пустые");
    });
    run_test("flatten: одна строка", [] {
        check_eq(flatten({{1, 2, 3}}), (std::vector<int>{1, 2, 3}), "одна строка");
    });
    run_test("flatten: квадратная матрица", [] {
        check_eq(flatten({{1, 2}, {3, 4}}), (std::vector<int>{1, 2, 3, 4}), "2x2");
    });
    run_test("flatten: рваная матрица", [] {
        check_eq(flatten({{1, 2}, {3, 4, 5}, {6}}), (std::vector<int>{1, 2, 3, 4, 5, 6}), "строки разной длины");
    });
    run_test("flatten: смешанные пустые строки", [] {
        check_eq(flatten({{1}, {}, {2, 3}}), (std::vector<int>{1, 2, 3}), "пустая строка в середине");
    });
}

// =============================================================================
// Задание 6: merge_sorted
// =============================================================================

void test_merge_sorted() {
    run_test("merge_sorted: оба пустые", [] {
        check_eq(merge_sorted({}, {}), std::vector<int>{}, "пустые -> пустой");
    });
    run_test("merge_sorted: первый пустой", [] {
        check_eq(merge_sorted({}, {1, 2, 3}), (std::vector<int>{1, 2, 3}), "первый пустой");
    });
    run_test("merge_sorted: второй пустой", [] {
        check_eq(merge_sorted({1, 2, 3}, {}), (std::vector<int>{1, 2, 3}), "второй пустой");
    });
    run_test("merge_sorted: чередование элементов", [] {
        check_eq(merge_sorted({1, 3, 5}, {2, 4, 6}), (std::vector<int>{1, 2, 3, 4, 5, 6}), "чередование");
    });
    run_test("merge_sorted: без чередования", [] {
        check_eq(merge_sorted({1, 2, 3}, {4, 5, 6}), (std::vector<int>{1, 2, 3, 4, 5, 6}), "весь первый перед вторым");
    });
    run_test("merge_sorted: с дубликатами", [] {
        check_eq(merge_sorted({1, 2, 2}, {2, 3}), (std::vector<int>{1, 2, 2, 2, 3}), "дубликаты сохраняются");
    });
    run_test("merge_sorted: разные размеры", [] {
        check_eq(merge_sorted({1, 10}, {2, 3, 4, 5, 6}),
                 (std::vector<int>{1, 2, 3, 4, 5, 6, 10}), "разные размеры");
    });
}

// =============================================================================
// Задание 7: max_subarray_sum
// =============================================================================

void test_max_subarray_sum() {
    run_test("max_subarray_sum: исключение на пустом векторе", [] {
        check_throws<std::invalid_argument>(
            [] { max_subarray_sum({}); },
            "должен бросать std::invalid_argument на пустом векторе"
        );
    });
    run_test("max_subarray_sum: один положительный элемент", [] {
        check_eq(max_subarray_sum({5}), 5, "один элемент 5");
    });
    run_test("max_subarray_sum: один отрицательный элемент", [] {
        check_eq(max_subarray_sum({-7}), -7, "один элемент -7");
    });
    run_test("max_subarray_sum: все отрицательные", [] {
        check_eq(max_subarray_sum({-3, -1, -2}), -1, "максимальный из отрицательных");
    });
    run_test("max_subarray_sum: все положительные", [] {
        check_eq(max_subarray_sum({1, 2, 3, 4}), 10, "сумма всех");
    });
    run_test("max_subarray_sum: классический пример", [] {
        check_eq(max_subarray_sum({-2, 1, -3, 4, -1, 2, 1, -5, 4}), 6, "{4,-1,2,1} = 6");
    });
    run_test("max_subarray_sum: лучший подмассив в начале", [] {
        check_eq(max_subarray_sum({5, 4, -100, 1}), 9, "{5,4} = 9");
    });
    run_test("max_subarray_sum: лучший подмассив в конце", [] {
        check_eq(max_subarray_sum({-10, 1, 2, 3}), 6, "{1,2,3} = 6");
    });
}

// =============================================================================
// Задание 8: group_by_remainder
// =============================================================================

void test_group_by_remainder() {
    run_test("group_by_remainder: исключение при k=0", [] {
        check_throws<std::invalid_argument>(
            [] { group_by_remainder({1, 2, 3}, 0); },
            "должен бросать std::invalid_argument при k=0"
        );
    });
    run_test("group_by_remainder: исключение при k<0", [] {
        check_throws<std::invalid_argument>(
            [] { group_by_remainder({1, 2, 3}, -1); },
            "должен бросать std::invalid_argument при k<0"
        );
    });
    run_test("group_by_remainder: пустой вектор", [] {
        auto result = group_by_remainder({}, 3);
        check(result.size() == 3, "должно быть 3 группы");
        check_eq(result[0], std::vector<int>{}, "группа 0 пустая");
        check_eq(result[1], std::vector<int>{}, "группа 1 пустая");
        check_eq(result[2], std::vector<int>{}, "группа 2 пустая");
    });
    run_test("group_by_remainder: k=1", [] {
        auto result = group_by_remainder({1, 2, 3}, 1);
        check(result.size() == 1, "должна быть 1 группа");
        check_eq(result[0], (std::vector<int>{1, 2, 3}), "все в группе 0");
    });
    run_test("group_by_remainder: три группы", [] {
        auto result = group_by_remainder({0, 1, 2, 3, 4, 5, 6}, 3);
        check(result.size() == 3, "должно быть 3 группы");
        check_eq(result[0], (std::vector<int>{0, 3, 6}), "группа 0");
        check_eq(result[1], (std::vector<int>{1, 4}),    "группа 1");
        check_eq(result[2], (std::vector<int>{2, 5}),    "группа 2");
    });
    run_test("group_by_remainder: отрицательные элементы", [] {
        // (-6 % 3 + 3) % 3 == 0, (-5 % 3 + 3) % 3 == 1, (-4 % 3 + 3) % 3 == 2
        auto result = group_by_remainder({-6, -5, -4}, 3);
        check(result.size() == 3, "должно быть 3 группы");
        check_eq(result[0], (std::vector<int>{-6}), "группа 0");
        check_eq(result[1], (std::vector<int>{-5}), "группа 1");
        check_eq(result[2], (std::vector<int>{-4}), "группа 2");
    });
    run_test("group_by_remainder: порядок сохраняется", [] {
        auto result = group_by_remainder({5, 2, 8, 1, 4}, 2);
        check(result.size() == 2, "должно быть 2 группы");
        check_eq(result[0], (std::vector<int>{2, 8, 4}), "чётные в порядке появления");
        check_eq(result[1], (std::vector<int>{5, 1}),    "нечётные в порядке появления");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_sum();
    test_filter_even();
    test_rotate_left();
    test_remove_duplicates();
    test_flatten();
    test_merge_sorted();
    test_max_subarray_sum();
    test_group_by_remainder();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
