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
    std::set<int> s;
   for(int i=0; i<v.size(); i++){
    s.insert(v[i]);
   }
   return s;
}

// -----------------------------------------------------------------------------
// Задание 2: intersection (0.25 баллов)
// Верните множество элементов, которые есть и в a, и в b.
// Не используйте std::set_intersection.
// Пример: intersection({1,2,3,4}, {3,4,5,6}) == {3, 4}
// Пример: intersection({1,2}, {3,4}) == {}
// -----------------------------------------------------------------------------
std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> s;
    for(auto it=a.begin(); it!=a.end(); ++it){
        if(b.count(*it)==1) s.insert(*it);
    }
    return s;
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
    std::set<int> s;
    for(auto it=a.begin(); it!=a.end(); ++it){
        if(b.count(*it)==0) s.insert(*it);
    }
    for(auto it=b.begin(); it!=b.end(); ++it){
        if(a.count(*it)==0) s.insert(*it);
    }
    return s;
    
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
   for(auto it = s.begin(); it!=s.end(); ++it){
    auto it_ = s.find(target - *it);
    if(it_!=s.end() && it_!=it) return true;
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
    std::set<int> a;
    if (k < 0 or k > s.size()) {
        throw std::invalid_argument("Invalid argument");
    }
    if (k == 0) return a;
    
    auto right = s.lower_bound(x);
    auto left = right;
    
    if (left != s.begin()) {
        --left;
    } else {
        left = s.end();  
    }
    
    while (a.size() < k) {
        bool hasleft = (left != s.end());
        bool hasright = (right != s.end());
        
        if (!hasright) {
            a.insert(*left);
            if (left != s.begin()) {
                --left;
            } else {
                left = s.end();
            }
        }
        else if (!hasleft) {
            a.insert(*right);
            ++right;
        }
        else {
            int distleft = std::abs(x - *left);
            int distright = std::abs(x - *right);
            
            if (distleft <= distright) {
                a.insert(*left);
                if (left != s.begin()) {
                    --left;
                } else {
                    left = s.end();
                }
            } 
            else if (distright < distleft) {
                a.insert(*right);
                ++right;
            }
        }
    }
    
    return a;
}

