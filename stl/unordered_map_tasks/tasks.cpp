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
    std::unordered_map<int, int> us;
    for (int i = 0; i < v.size(); i++) {
        us[v[i]] += 1;
    }
    return us;
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
        throw std::invalid_argument("empty");  
    }
    
    std::unordered_map<int, int> us;
    for (int x : v) { 
        us[x] += 1;
    }
    
    int b_val = v[0]; 
    int b_c = 0;
    
    for (const auto& [val, c] : us) {  
        if (c > b_c || (c == b_c && val < b_val)) {
            b_c = c;
            b_val = val;
        }
    }
    
    return b_val;
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
    std::unordered_map<int, int> us;
    
    for (int i = 0; i < v.size(); i++) {
        int c = target - v[i];
        auto it = us.find(c);
        
        if (it != us.end()) {
            return {it->second, i};
        }
        us[v[i]] = i;
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
    std::unordered_map<int, std::vector<std::string>> a;  
    
    for (const auto& word : words) {
        int hash = 0;
        for (char c : word) {
            int val = (c - 'a' + 1);
            hash += val * val;
        }
        a[hash].push_back(word);
    }
    
    std::vector<std::vector<std::string>> res;
    for (auto const& [k, v] : a) {
        res.push_back(v);
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
    
    std::unordered_map<int, int> a;
    for (auto i : v) {
        a[i]++;
    }
    
    if (k > (a.size())) {
        throw std::invalid_argument("k exceeds number of unique elements");
    }
    
    std::vector<std::vector<int>> vec(v.size() + 1);
    
    for (const auto& [val, c] : a) {
        vec[c].push_back(val);
    }
    
    std::vector<int> res;
    for (int i = vec.size() - 1; i >= 0 && res.size() < k; i--) {
        for (int val : vec[i]) {
            res.push_back(val);
            if (res.size() == k) {
                break;
            }
        }
    }
    return res;
}
