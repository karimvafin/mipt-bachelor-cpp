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
    return std::set<int>(v.begin(), v.end());
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
    for (int x: a){
        if (b.count(x)){
            result.insert(x);
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

    for (int x : a){
        if (b.count(x) == 0){
            result.insert(x);
        }
    }

    for (int x : b){
        if (a.count(x) == 0){
            result.insert(x);
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
    for (int x : s){
        int find_element = target - x;
        if (find_element != x && s.find(find_element) != s.end()){
            return true;
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
    if (k < 0 || k > s.size()){
        throw std::invalid_argument("Error!");
    }
    std::set<int> buffer(s);
    std::set<int> result;
    for (int i =  0; i < k; ++i) {
        auto ub = buffer.upper_bound(x);
        auto lb = buffer.lower_bound(x);

        if (lb == buffer.end()){
            auto end = buffer.end();
            --end;
            result.insert(*end);
            buffer.erase(end);
            continue;
        }

        if (*lb == x){
            result.insert(x);
            buffer.erase(lb);
            continue;
        }
        if (lb == buffer.begin()){
            result.insert(*lb);
            buffer.erase(lb);
            continue;
        }
        --lb;
        if (x - *lb <= *ub - x){
            result.insert(*lb);
            buffer.erase(lb);
            continue;
        }
        if (*ub - x < x - *lb){
            result.insert(*ub);
            buffer.erase(ub);
            continue;
        }
    }
    return result;
}
