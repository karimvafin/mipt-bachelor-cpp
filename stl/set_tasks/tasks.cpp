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
    std::set<int> result;
    for (int value : v) {
        result.insert(value);
    }
    return result;
}

// -----------------------------------------------------------------------------
// Задание 2: intersection (0.25 баллов)
// Верните множество элементов, которые есть и в a, и в b.
// Не используйте std::set_intersection.
// Пример: intersection({1,2,3,4}, {3,4,5,6}) == {3, 4}
// Пример: intersection({1,2}, {3,4}) == {}
// -----------------------------------------------------------------------------
std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    const std::set<int>& smaller = (a.size() < b.size()) ? a : b;
    const std::set<int>& larger = (a.size() < b.size()) ? b : a;
    
    for (int value : smaller) {
        if (larger.find(value) != larger.end()) {
            result.insert(value);
        }
    }
    
    return result;
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
    std::set<int> result;
    for (int value : a) {
        if (b.find(value) == b.end()) {
            result.insert(value);
        }
    }
    
    for (int value : b) {
        if (a.find(value) == a.end()) {
            result.insert(value);
        }
    }
    
    return result;
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
    for (int value : s) {
        int complement = target - value;
        
        // Make sure we don't use the same element twice
        if (complement != value) {
            if (s.find(complement) != s.end()) {
                return true;
            }
        }
    }
    return false;
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
    if (k < 0 || k > static_cast<int>(s.size())) {
        throw std::invalid_argument("k must be between 0 and s.size()");
    }
    
    if (k == 0) {
        return std::set<int>();
    }
    
    auto it = s.lower_bound(x);
    std::vector<int> candidates;
    
    auto left = it;
    auto right = it;
    
    if (left != s.begin()) {
        --left;
    } else {
        left = s.end();
    
    
    if (right == s.end() && left != s.end()) {
        right = s.end();
    }

    while (candidates.size() < static_cast<size_t>(k)) {
        bool left_valid = (left != s.end());
        bool right_valid = (right != s.end());
        
        if (!left_valid && !right_valid) {
            break;
        }
        
        if (!left_valid) {
            candidates.push_back(*right);
            ++right;
        } else if (!right_valid) {
            candidates.push_back(*left);
            if (left != s.begin()) {
                --left;
            } else {
                left = s.end();
            }
        } else {
            int left_dist = std::abs(*left - x);
            int right_dist = std::abs(*right - x);
            
            if (left_dist < right_dist) {
                candidates.push_back(*left);
                if (left != s.begin()) {
                    --left;
                } else {
                    left = s.end();
                }
            } else if (right_dist < left_dist) {
                candidates.push_back(*right);
                ++right;
            } else {
                if (*left < *right) {
                    candidates.push_back(*left);
                    if (left != s.begin()) {
                        --left;
                    } else {
                        left = s.end();
                    }
                } else {
                    candidates.push_back(*right);
                    ++right;
                }
            }
        }
    }
    
    std::set<int> result(candidates.begin(), candidates.end());
    return result;
}
