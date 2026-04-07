#include "tasks.h"

// =============================================================================
// Задания по std::set
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1: unique_elements (0.25 баллов)
// Преобразуйте вектор в множество уникальных элементов.
// Пример: unique_elements({3, 1, 4, 1, 5, 9, 2, 6, 5}) == {1, 2, 3, 4, 5, 6, 9}
// Пример: unique_elements({}) == {}
// -----------------------------------------------------------------------------
std::set<int> unique_elements(const std::vector<int>& v) {
    std::set<int> s_unique;
    for (auto i : v) {
        s_unique.insert(i);
    }
    return s_unique;
}

// -----------------------------------------------------------------------------
// Задание 2: intersection (0.25 баллов)
// Верните множество элементов, которые есть и в a, и в b.
// Не используйте std::set_intersection.
// Пример: intersection({1,2,3,4}, {3,4,5,6}) == {3, 4}
// Пример: intersection({1,2}, {3,4}) == {}
// -----------------------------------------------------------------------------
std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> set_a(a.begin(), a.end());
    std::set<int> set_b(b.begin(), b.end());
    std::set<int> s_intersected;
    
    auto it_a = set_a.begin();
    auto it_b = set_b.begin();

    while (it_a != set_a.end() && it_b != set_b.end()) {
        if (*it_a == *it_b) {
            s_intersected.insert(*it_a);
            it_a++;
            it_b++;
        }
        else if (*it_a < *it_b) {
            it_a++;
        }
        else it_b++;
    }
    return s_intersected;
}

// -----------------------------------------------------------------------------
// Задание 3: symmetric_difference (0.25 баллов)
// Верните множество элементов, которые есть ровно в одном из двух множеств
// (присутствуют в a или в b, но не в обоих).
// Не используйте std::set_symmetric_difference.
// Пример: symmetric_difference({1,2,3}, {2,3,4}) == {1, 4}
// Пример: symmetric_difference({1,2}, {1,2}) == {}
// -----------------------------------------------------------------------------
std::set<int> symmetric_difference(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> set_a(a.begin(), a.end());
    std::set<int> set_b(b.begin(), b.end());
    std::set<int> s_difference;

    for (auto x : set_a) {
        if (set_b.find(x) == set_b.end()) {
            s_difference.insert(x);
        }
    }

    for (auto x : set_b) {
        if (set_a.find(x) == set_a.end()) {
            s_difference.insert(x);
        }
    }

    return s_difference;
}

// -----------------------------------------------------------------------------
// Задание 4: has_pair_with_sum (0.25 баллов)
// Проверьте, существуют ли два различных элемента множества, сумма которых
// равна target. Элемент не может использоваться дважды.
// Пример: has_pair_with_sum({1, 2, 3, 4}, 5) == true   (1+4 или 2+3)
// Пример: has_pair_with_sum({1, 2, 3, 4}, 8) == false
// Пример: has_pair_with_sum({4}, 8)           == false
// Подсказка: используйте find() для поиска дополнения за O(log n).
// -----------------------------------------------------------------------------
bool has_pair_with_sum(const std::set<int>& s, int target) {
    bool answer = false;
    for (auto it = s.begin(); it != s.end(); it++) {
        auto found = s.find(target - *it);
        if (found != it && found != s.end()) answer = true;
    }
    return answer;
}

// -----------------------------------------------------------------------------
// Задание 5: k_closest (0.5 баллов)
// Верните множество из k элементов, наиболее близких к x по абсолютному
// значению разности. Сам x не обязательно присутствует в s.
// При одинаковом расстоянии предпочтительнее меньший элемент.
// Выбрасывает std::invalid_argument, если k < 0 или k > s.size().
// Пример: k_closest({1, 3, 5, 7, 9}, 6, 3) == {3, 5, 7}
// Пример: k_closest({1, 2, 3, 4, 5}, 3, 2) == {2, 3}  (|2-3|=|4-3|=1, берём меньший)
// Подсказка: lower_bound даёт ближайший элемент >= x; проверьте также предыдущий.
// -----------------------------------------------------------------------------
std::set<int> k_closest(const std::set<int>& s, int x, int k) {
    if (k < 0 || k > s.size()) throw std::invalid_argument("Неверное значение k");

    auto found = s.find(x);
    std::set<int> s_copy = s;
    std::set<int> answer; 

    if (k == 0) return answer;

    int cnt;

    if (found == s.end()) {
        s_copy.insert(x);
        cnt = 0;
    }
    else {
        cnt = 1;
        answer.insert(x);
    }

    found = s_copy.find(x);
    auto it_l = found, it_r = found;
    --it_l;
    ++it_r;

    while (cnt != k && it_l != s_copy.begin() && it_r != s_copy.end()) {
        if (std::abs(*it_l - x) < std::abs(*it_r - x)) {
            answer.insert(*it_l);
            it_l--;
        }
        else if (std::abs(*it_r - x) < std::abs(*it_l - x)) {
            answer.insert(*it_r);
            it_r++;
        }
        else {
            if (*it_l < *it_r) {
                answer.insert(*it_l);
                it_l--;
            }
            else {
                answer.insert(*it_r);
                it_r++;
            }
        }
        cnt++;
    }

    if (cnt == k) return answer;

    if (it_r == s_copy.end()) {
        while (cnt != k) {
            answer.insert(*it_l);
            it_l--;
            cnt++;
        }

        return answer;
    }
    
    bool use_0 = false;
    while (cnt != k) {
        if (!use_0 && std::abs(*it_l - x) < std::abs(*it_r - x)) {
            answer.insert(*it_l);
            it_l--;
        }
        else if (std::abs(*it_r - x) < std::abs(*it_l - x)) {
            answer.insert(*it_r);
            it_r++;
        }
        else {
            if (*it_l < *it_r) {
                answer.insert(*it_l);
                it_l--;
            }
            else {
                answer.insert(*it_r);
                it_r++;
            }
        }
        cnt++;
    }

    return answer;
}
