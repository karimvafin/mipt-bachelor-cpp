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
    std::set<int> res;
    for(int i : v){
        res.insert(i);
    }
    return res;
}

// -----------------------------------------------------------------------------
// Задание 2: intersection (0.25 баллов)
// Верните множество элементов, которые есть и в a, и в b.
// Не используйте std::set_intersection.
// Пример: intersection({1,2,3,4}, {3,4,5,6}) == {3, 4}
// Пример: intersection({1,2}, {3,4}) == {}
// -----------------------------------------------------------------------------
std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> res;
    for(int i : a){
        if(b.find(i)!=b.end()){
            res.insert(i);
        }
    }
    return res;
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
    std::set<int> res;
    for(int i : a){
        if(b.find(i)==b.end()){
            res.insert(i);
        }
    }
    for(int i : b){
        if(a.find(i)==a.end()){
            res.insert(i);
        }
    }
    return res;
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
    if (s.empty() || s.size()==1) {return false;}
    for(int i: s){
        int j=target-i;
        if (s.find(j)!=s.end()){
            if(j!=i){
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
    if (k < 0 || k > s.size()) {
        throw std::invalid_argument("k is out of range");
    }
    
    std::set<int> res;
    if (k == 0) return res;

    auto right = s.lower_bound(x);
    auto left = right;
    if (right != s.begin()) {
        --left; 
    } else {
        left = s.end();
    }
    

    for (int i = 0; i < k; ++i) {
        if (left == s.end()) {
            res.insert(*right);
            ++right;
        } else if (right == s.end()) {
            res.insert(*left);
            if (left == s.begin()) {
                left = s.end();
            } else {
                --left;
            }
        } else {
            int dist_left = std::abs(*left - x);
            int dist_right = std::abs(*right - x);
            if (dist_left <= dist_right) {
                res.insert(*left);
                if (left == s.begin()) {
                    left = s.end();
                } else {
                    --left;
                }
            } else {
                res.insert(*right);
                ++right;
            }
        }
    }
    return res;
}
