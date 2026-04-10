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
    std::unordered_map<int, int> res;
    for(int i : v){
        res[i]++;
    }
    return res;
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
        throw std::invalid_argument("Vector is empty");
    }
    std::unordered_map<int, int> freq = count_elements(v);
    int res = v[0];
    int max = 0;
    for (const auto& [i, count] : freq) {
        if (count > max || (count == max && i < res)) {
            max = count;
            res = i;
        }
    }
    return res;
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
    std::unordered_map<int, int> s; 
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        int j = target - v[i];       
        if (s.count(j)) {
            return {s[j], i};
        }       
        s[v[i]] = i;
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

    for (const std::string& word : words) {
        std::string key = word;
        std::sort(key.begin(), key.end());
        groups[key].push_back(word);
    }

    std::vector<std::vector<std::string>> res;
    for (auto& pair : groups) {
        res.push_back(std::move(pair.second)); 
    }
    return res;
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
        throw std::invalid_argument("k must be positive");
    }

    std::unordered_map<int, int> freq;
    for (int i : v) {
        freq[i]++;
    }
    
    if (k > freq.size()) {
        throw std::invalid_argument("k is greater than number of unique elements");
    }

    std::vector<std::pair<int, int>> freq_vec;
    for (const auto& p : freq) {
        freq_vec.emplace_back(p.second, p.first);
    }

    std::sort(freq_vec.begin(), freq_vec.end(), 
          [](auto a, auto b) { return a.first > b.first; });
    

    std::vector<int> res;
    for (int i = 0; i < k; ++i) {
        res.push_back(freq_vec[i].second);
    }
    return res;
}
