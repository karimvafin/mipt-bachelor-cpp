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
    std::unordered_map<int, int> result;
    for (int x : v) {
        ++result[x];
    }
    return result;
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
    if (v.empty()) {
        throw std::invalid_argument("vector is empty");
    }
    auto counts = count_elements(v);
    int max_freq = 0;
    int result = 0;
    for (const auto& [value, freq] : counts) {
        if (freq > max_freq || (freq == max_freq && value < result)) {
            max_freq = freq;
            result = value;
        }
    }
    return result;
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
    std::unordered_map<int, int> seen;
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        int x = target - v[i];
        auto it = seen.find(x);
        if (it != seen.end()) {
            return {it->second, i};
        }
        seen[v[i]] = i;
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
    std::unordered_map<std::string, std::vector<std::string>> groups;
    for (const auto& word : words) {
        std::string key = word;
        std::sort(key.begin(), key.end());
        groups[key].push_back(word);
    }
    std::vector<std::vector<std::string>> result;
    result.reserve(groups.size());
    for (auto& pair : groups) {
        result.push_back(std::move(pair.second));
    }
    return result;
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
    if (k <= 0) {
        throw std::invalid_argument("k must be > 0");
    }
    std::unordered_map<int, int> freq;
    for (int x : v) {
        ++freq[x];
    }
    if (k > static_cast<int>(freq.size())) {
        throw std::invalid_argument("k > number of unique elements");
    }
    std::vector<std::pair<int, int>> items(freq.begin(), freq.end());
    std::sort(items.begin(), items.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    std::vector<int> result;
    result.reserve(k);
    for (int i = 0; i < k; ++i) {
        result.push_back(items[i].first);
    }
    return result;
}
