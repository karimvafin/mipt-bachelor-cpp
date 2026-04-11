#include "tasks.h"

#include <algorithm>

// =============================================================================
// Задания по std::unordered_map
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1: count_elements (0.25 баллов)
// Подсчитайте количество вхождений каждого элемента вектора.
// Верните unordered_map, где ключ — элемент, значение — количество вхождений.
// Пример: count_elements({1, 2, 2, 3, 3, 3}) == {1:1, 2:2, 3:3}
// Пример: count_elements({}) == {}
// -----------------------------------------------------------------------------
std::unordered_map<int, int> count_elements(const std::vector<int>& v) {
    std::unordered_map<int, int> count_elements;
    for (int i : v) ++count_elements[i];
    return count_elements;
}

// -----------------------------------------------------------------------------
// Задание 2: most_frequent (0.25 баллов)
// Найдите элемент, который встречается чаще всего.
// При равном количестве вхождений верните наименьший из них.
// Выбрасывает std::invalid_argument, если вектор пуст.
// Пример: most_frequent({1, 2, 2, 3, 3, 3}) == 3
// Пример: most_frequent({4, 4, 5, 5}) == 4
// -----------------------------------------------------------------------------
int most_frequent(const std::vector<int>& v) {
    if (v.empty()) throw std::invalid_argument("vector is empty");
    std::unordered_map<int, int> count_elements;
    for (int i : v) ++count_elements[i];
    int max_count = 0;
    int most_frequent = v[0];
    for (const auto& pair : count_elements) {
        if (pair.second > max_count || (pair.second == max_count && pair.first < most_frequent)) {
            max_count = pair.second;
            most_frequent = pair.first;
        }
    }
    return most_frequent;
}

// -----------------------------------------------------------------------------
// Задание 3: two_sum (0.25 баллов)
// Найдите индексы двух элементов, сумма которых равна target.
// Верните вектор из двух индексов {i, j}, где i < j.
// Гарантируется, что ровно одно решение существует.
// Пример: two_sum({2, 7, 11, 15}, 9) == {0, 1}
// Пример: two_sum({3, 2, 4}, 6) == {1, 2}
// Подсказка: используйте unordered_map для решения за O(n).
// -----------------------------------------------------------------------------
std::vector<int> two_sum(const std::vector<int>& v, int target) {
    std::unordered_map<int, int> um;
    for (int i = 0; i < v.size(); ++i) {
        int add = target - v[i];
        if (um.find(add) != um.end()) return {um[add], i};
        um[v[i]] = i;
    }
    return {};
}

// -----------------------------------------------------------------------------
// Задание 4: group_anagrams (0.25 баллов)
// Сгруппируйте слова-анаграммы вместе.
// Верните вектор групп; порядок групп и порядок слов внутри группы —
// произвольный (тесты проверяют только состав).
// Пример: group_anagrams({"eat","tea","tan","ate","nat","bat"})
//      == {{"eat","tea","ate"}, {"tan","nat"}, {"bat"}}
// Подсказка: у анаграмм одинаковый набор символов — используйте его как ключ.
// -----------------------------------------------------------------------------
std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& words) {
    std::vector<std::vector<std::string>> results;
    std::unordered_map<std::string, std::vector<std::string>> um;
    for (const auto& word : words) {
        std::string key = word;
        std::sort(key.begin(), key.end());
        um[key].push_back(word);
    }
    results.reserve(um.size());
    for (auto it = um.begin(); it != um.end(); ++it)
        results.push_back(it->second);
    return results;
}

// -----------------------------------------------------------------------------
// Задание 5: top_k_frequent (0.5 баллов)
// Верните k наиболее часто встречающихся элементов.
// Порядок элементов в ответе произвольный (тесты проверяют только состав).
// Выбрасывает std::invalid_argument, если k <= 0 или k > количества
// уникальных элементов.
// Пример: top_k_frequent({1, 1, 1, 2, 2, 3}, 2) == {1, 2}  (в любом порядке)
// Пример: top_k_frequent({1}, 1) == {1}
// -----------------------------------------------------------------------------
std::vector<int> top_k_frequent(const std::vector<int>& v, int k) {
    if (k <= 0) throw std::invalid_argument("k can't be negative");
    std::unordered_map<int, int> um;
    for (int i : v) ++um[i];
    if (k > um.size()) throw std::invalid_argument("k exeeds number of unique elements");
    std::vector<std::pair<int, int>> top_k_frequent(um.begin(), um.end());
    std::sort(top_k_frequent.begin(), top_k_frequent.end(), [](const auto& pair1, const auto& pair2) { return pair1.second > pair2.second; });
    std::vector<int> results;
    for (int i = 0; i < k; ++i) results.push_back(top_k_frequent[i].first);
    return results;
}
