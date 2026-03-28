#include "tasks.h"

#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <set>

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

// Сравниваем группы анаграмм независимо от порядка групп и слов внутри них
bool anagram_groups_equal(std::vector<std::vector<std::string>> actual,
                          std::vector<std::vector<std::string>> expected) {
    auto normalize = [](std::vector<std::vector<std::string>>& groups) {
        for (auto& g : groups) std::sort(g.begin(), g.end());
        std::sort(groups.begin(), groups.end());
    };
    normalize(actual);
    normalize(expected);
    return actual == expected;
}

// =============================================================================
// Задание 1: count_elements
// =============================================================================

void test_count_elements() {
    run_test("count_elements: пустой вектор", [] {
        check_eq(count_elements({}), std::unordered_map<int,int>{}, "пустой -> пустая карта");
    });
    run_test("count_elements: все уникальные", [] {
        auto result = count_elements({1, 2, 3});
        check_eq(result.at(1), 1, "1 встречается 1 раз");
        check_eq(result.at(2), 1, "2 встречается 1 раз");
        check_eq(result.at(3), 1, "3 встречается 1 раз");
    });
    run_test("count_elements: с повторами", [] {
        auto result = count_elements({1, 2, 2, 3, 3, 3});
        check_eq(result.at(1), 1, "1 встречается 1 раз");
        check_eq(result.at(2), 2, "2 встречается 2 раза");
        check_eq(result.at(3), 3, "3 встречается 3 раза");
    });
    run_test("count_elements: один элемент много раз", [] {
        auto result = count_elements({5, 5, 5, 5});
        check_eq((int)result.size(), 1, "один уникальный элемент");
        check_eq(result.at(5), 4, "5 встречается 4 раза");
    });
}

// =============================================================================
// Задание 2: most_frequent
// =============================================================================

void test_most_frequent() {
    run_test("most_frequent: исключение на пустом", [] {
        check_throws<std::invalid_argument>(
            [] { most_frequent({}); },
            "должен бросать std::invalid_argument"
        );
    });
    run_test("most_frequent: один элемент", [] {
        check_eq(most_frequent({42}), 42, "единственный элемент");
    });
    run_test("most_frequent: явный лидер", [] {
        check_eq(most_frequent({1, 2, 2, 3, 3, 3}), 3, "3 встречается чаще всего");
    });
    run_test("most_frequent: ничья — меньший побеждает", [] {
        check_eq(most_frequent({4, 4, 5, 5}), 4, "при ничьей возвращаем меньший");
    });
    run_test("most_frequent: все уникальные — наименьший", [] {
        check_eq(most_frequent({3, 1, 2}), 1, "все по одному разу — наименьший");
    });
}

// =============================================================================
// Задание 3: two_sum
// =============================================================================

void test_two_sum() {
    run_test("two_sum: базовый пример", [] {
        auto r = two_sum({2, 7, 11, 15}, 9);
        check_eq(r, (std::vector<int>{0, 1}), "индексы 0 и 1");
    });
    run_test("two_sum: ответ не в начале", [] {
        auto r = two_sum({3, 2, 4}, 6);
        check_eq(r, (std::vector<int>{1, 2}), "индексы 1 и 2");
    });
    run_test("two_sum: ответ в конце", [] {
        auto r = two_sum({1, 5, 3, 7}, 10);
        check_eq(r, (std::vector<int>{1, 3}), "индексы 1 и 3");
    });
    run_test("two_sum: i < j", [] {
        auto r = two_sum({4, 1, 3, 2}, 5);
        check(r.size() == 2 && r[0] < r[1], "первый индекс должен быть меньше второго");
        check_eq(r[0] + r[1], (int)(r[0] + r[1]), "санитарная проверка");
        // проверяем, что сумма элементов по индексам == 5
        std::vector<int> v = {4, 1, 3, 2};
        check(v[r[0]] + v[r[1]] == 5, "сумма элементов по индексам равна 5");
    });
}

// =============================================================================
// Задание 4: group_anagrams
// =============================================================================

void test_group_anagrams() {
    run_test("group_anagrams: пустой вектор", [] {
        check_eq(group_anagrams({}), std::vector<std::vector<std::string>>{}, "пустой -> пустой");
    });
    run_test("group_anagrams: нет анаграмм", [] {
        auto result = group_anagrams({"abc", "def"});
        check(anagram_groups_equal(result, {{"abc"}, {"def"}}), "две отдельные группы");
    });
    run_test("group_anagrams: классический пример", [] {
        auto result = group_anagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
        check(anagram_groups_equal(result,
            {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}}),
            "три группы анаграмм");
    });
    run_test("group_anagrams: все анаграммы друг друга", [] {
        auto result = group_anagrams({"abc", "bca", "cab"});
        check(anagram_groups_equal(result, {{"abc", "bca", "cab"}}), "одна группа");
    });
    run_test("group_anagrams: одно слово", [] {
        auto result = group_anagrams({"hello"});
        check(anagram_groups_equal(result, {{"hello"}}), "одна группа из одного слова");
    });
}

// =============================================================================
// Задание 5: top_k_frequent
// =============================================================================

void test_top_k_frequent() {
    run_test("top_k_frequent: исключение при k=0", [] {
        check_throws<std::invalid_argument>(
            [] { top_k_frequent({1, 2}, 0); },
            "k=0 -> invalid_argument"
        );
    });
    run_test("top_k_frequent: исключение при k > уникальных", [] {
        check_throws<std::invalid_argument>(
            [] { top_k_frequent({1, 2}, 3); },
            "k > unique -> invalid_argument"
        );
    });
    run_test("top_k_frequent: k=1", [] {
        auto result = top_k_frequent({1, 1, 1, 2, 2, 3}, 1);
        check_eq((int)result.size(), 1, "ровно 1 элемент");
        check_eq(result[0], 1, "самый частый — 1");
    });
    run_test("top_k_frequent: k=2", [] {
        auto result = top_k_frequent({1, 1, 1, 2, 2, 3}, 2);
        std::set<int> s(result.begin(), result.end());
        check_eq((int)s.size(), 2, "ровно 2 уникальных элемента");
        check(s.count(1) && s.count(2), "должны быть 1 и 2");
    });
    run_test("top_k_frequent: все элементы", [] {
        auto result = top_k_frequent({3, 1, 2}, 3);
        std::set<int> s(result.begin(), result.end());
        check_eq((int)s.size(), 3, "все три элемента");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_count_elements();
    test_most_frequent();
    test_two_sum();
    test_group_anagrams();
    test_top_k_frequent();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
