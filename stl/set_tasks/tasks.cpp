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
    auto real_position = v.begin();

while (real_position!=v.end())
{
   result.insert(*real_position);
   real_position++;
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
    auto real_position = a.begin();
     if (a.empty() || b.empty()) {
        return result;
    }
    while (real_position != a.end()) {
        int search = *real_position;
        auto found = b.find(search);
         if (found != b.end()) {
            result.insert(search);
        }
           real_position++;
    }/
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
   auto real_position = a.begin();
    while (real_position != a.end()) {
        if (b.find(*real_position) == b.end()) {
            result.insert(*real_position);
        }
        ++real_position;
    }

    real_position = b.begin();
    while (real_position!=b.end())
    {
        if(a.find(*real_position) == a.end())
            {result.insert(*real_position);}
        real_position++;
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
    auto real_position = s.begin();
    
    while (real_position != s.end()) {
        int first = *real_position;
        int second = target - first;;
        if (second != first && s.find(second) != s.end()) {
            return true;
        }
        real_position++;}
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
    if (k < 0 || static_cast<size_t>(k) > s.size()) {
        throw std::invalid_argument("Invalid k");
    }

    if (k == 0) {
        return {}; 
    }
     std::vector<std::pair<int, int>> with_dist;
    auto real_position = s.begin();
    
    while (real_position != s.end()) {
        int val = *real_position;
        int dist = std::abs(val - x);
        with_dist.push_back({val, dist});
        ++real_position;
    }

    for (int i = 0; i < static_cast<int>(with_dist.size()) - 1; ++i) {
        for (int j = i + 1; j < static_cast<int>(with_dist.size()); ++j) {
            bool bubble = false;
            
            if (with_dist[j].second < with_dist[i].second) {
                bubble = true; 
            }
            else if (with_dist[j].second == with_dist[i].second) {
                if (with_dist[j].first < with_dist[i].first) {
                    bubble = true; 
                }
            }
            
            if (bubble) {
                std::swap(with_dist[i], with_dist[j]);
            }
        }
    }

     std::set<int> result;
    for (int i = 0; i < k; ++i) {
        result.insert(with_dist[i].first);
    }
    
    return result;
}
