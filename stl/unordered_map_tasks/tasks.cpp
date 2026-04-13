#include "tasks.h"
#include <map>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

// =============================================================================
// Задания по std::unordered_map
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1 (Лёгкое): count_elements
// Подсчитайте количество вхождений каждого элемента вектора.
// Верните unordered_map, где ключ — элемент, значение — количество вхождений.
// Пример: count_elements({1, 2, 2, 3, 3, 3}) == {1:1, 2:2, 3:3}
// Пример: count_elements({}) == {}
// -----------------------------------------------------------------------------
std::unordered_map<int, int> count_elements(const std::vector<int>& v) {
    std::unordered_map<int, int> result;
    for (int x : v) {
        result[x]++;
    }
    return result;
}

// -----------------------------------------------------------------------------
// Задание 2 (Лёгкое-Среднее): most_frequent
// Найдите элемент, который встречается чаще всего.
// При равном количестве вхождений верните наименьший из них.
// Выбрасывает std::invalid_argument, если вектор пуст.
// Пример: most_frequent({1, 2, 2, 3, 3, 3}) == 3
// Пример: most_frequent({4, 4, 5, 5}) == 4
// -----------------------------------------------------------------------------
int most_frequent(const std::vector<int>& v) {
    if (v.empty()) {
        throw std::invalid_argument("empty");
    }

    std::map<int, int> freq;
    for (int num : v) {
        ++freq[num];
    }

    int max_count = 0;
    int result = 0;
    
    for (const auto& p : freq) {
        if (p.second > max_count) {
            max_count = p.second;
            result = p.first;
        }
    }

    return result;
}

// -----------------------------------------------------------------------------
// Задание 3 (Среднее): two_sum
// Найдите индексы двух элементов, сумма которых равна target.
// Верните вектор из двух индексов {i, j}, где i < j.
// Гарантируется, что ровно одно решение существует.
// Пример: two_sum({2, 7, 11, 15}, 9) == {0, 1}
// Пример: two_sum({3, 2, 4}, 6) == {1, 2}
// Подсказка: используйте unordered_map для решения за O(n).
// -----------------------------------------------------------------------------
std::vector<int> two_sum(const std::vector<int>& v, int target) {
    std::unordered_map<int, int> m;

    for (int i = 0; i < v.size(); ++i) {
        int need = target - v[i];
        if (m.count(need)) {
            return {m[need], i};
        }
        m[v[i]] = i;
    }
    
    return {};
}

// -----------------------------------------------------------------------------
// Задание 4 (Среднее): group_anagrams
// Сгруппируйте слова-анаграммы вместе.
// Верните вектор групп; порядок групп и порядок слов внутри группы —
// произвольный (тесты проверяют только состав).
// Пример: group_anagrams({"eat","tea","tan","ate","nat","bat"})
//      == {{"eat","tea","ate"}, {"tan","nat"}, {"bat"}}
// Подсказка: у анаграмм одинаковый набор символов — используйте его как ключ.
// -----------------------------------------------------------------------------
std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& words) {
    std::unordered_map<std::string, std::vector<std::string>> groups;

    for (int i = 0; i < words.size(); i++) {
        std::string key = words[i];
        std::sort(key.begin(), key.end());
        groups[key].push_back(words[i]);
    }
    
    std::vector<std::vector<std::string>> result;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        result.push_back(it->second);
    }

    return result;
}

// -----------------------------------------------------------------------------
// Задание 5 (Сложное): top_k_frequent
// Верните k наиболее часто встречающихся элементов.
// Порядок элементов в ответе произвольный (тесты проверяют только состав).
// Выбрасывает std::invalid_argument, если k <= 0 или k > количества
// уникальных элементов.
// Пример: top_k_frequent({1, 1, 1, 2, 2, 3}, 2) == {1, 2}  (в любом порядке)
// Пример: top_k_frequent({1}, 1) == {1}
// -----------------------------------------------------------------------------
std::vector<int> top_k_frequent(const std::vector<int>& v, int k) {
    throw std::runtime_error("Not implemented");
}
