#include "tasks.h"

#include <algorithm>
#include <iostream>

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
    std::unordered_map<int, int> count_map;
    for (auto i : v) {
        count_map[i]++;
    }
    return count_map;
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
    if (v.size() == 0) throw std::invalid_argument("Вектор пуст");
    std::unordered_map<int, int> count_map = count_elements(v);

    int popular_key = -1, cnt = -1;
    for (const auto& [key, value] : count_map ) {
        if (value > cnt) {
            popular_key = key;
            cnt = value;
        }
        else if (value == cnt && popular_key > key) {
            popular_key = key;
        }
    }
    return popular_key;
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
    std::unordered_map<int, int> indexes;
    for (int i = 0; i < v.size(); i++) {
        indexes[v[i]] = i + 1;
    }
    for (auto n : v) {
        if (indexes[target - n] != 0 && indexes[target - n] != indexes[n]){
            int a = indexes[n] - 1, b = indexes[target - n] - 1;
            std::vector<int> answer = { std::min(a, b) , std::max(a, b) };
            return answer;
        }
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
    std::unordered_map<std::string, std::vector<std::string>> group_map;

    for (auto word : words) {
        std::string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        group_map[sorted_word].push_back(word);
    }

    std::vector<std::vector<std::string>> answer;
    for (const auto& [key, value] : group_map) {
        answer.push_back(value);
    }

    return answer;
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
    std::unordered_map<int, int> count_map;
    std::unordered_map<int, std::vector<int>> index_map;
    int cnt = 0, k_cnt = 0, now_cnt = v.size();

    for (auto i : v) {
        count_map[i]++;
        if (count_map[i] == 1) cnt++;
    }

    if (k <= 0 || k > cnt) throw std::invalid_argument("Неподходящий k");

    for (const auto& [key, value] : count_map) {
        index_map[value].push_back(key);
    }
    
    std::vector<int> answer;
    while (k_cnt != k) {
        if (index_map.find(now_cnt) != index_map.end()) {

            int max_range = std::min(int(index_map[now_cnt].size()), k - k_cnt);
            for (int i = 0; i < max_range; i++) {
                answer.push_back(index_map[now_cnt][i]);
                k_cnt++;
            }
        }
        now_cnt--;
    }

    return answer;
}
