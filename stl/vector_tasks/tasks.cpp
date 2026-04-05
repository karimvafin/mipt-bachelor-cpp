#include "tasks.h"
#include <stdexcept>

// =============================================================================
// Задания по std::vector
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1: sum (0.25 баллов)
// Посчитайте сумму всех элементов вектора.
// Пример: sum({1, 2, 3, 4}) == 10
// Пример: sum({}) == 0
// -----------------------------------------------------------------------------
int sum(const std::vector<int>& v) {
    int sum = 0;
    for (int i : v) sum += i;
    return sum;
}

// -----------------------------------------------------------------------------
// Задание 2: filter_even (0.25 баллов)
// Верните новый вектор, содержащий только чётные элементы исходного,
// сохраняя их порядок.
// Пример: filter_even({1, 2, 3, 4, 5, 6}) == {2, 4, 6}
// Пример: filter_even({1, 3, 5}) == {}
// -----------------------------------------------------------------------------
std::vector<int> filter_even(const std::vector<int>& v) {
    std::vector<int> v_filtered;
    for (auto i : v) {
        if (i % 2 == 0) v_filtered.push_back(i);
    }
    return v_filtered;
}

// -----------------------------------------------------------------------------
// Задание 3: rotate_left (0.25 баллов)
// Выполните циклический сдвиг вектора влево на k позиций (in-place).
// Элементы, «вышедшие» за левую границу, появляются в конце.
// Если k >= v.size(), сдвиг должен работать корректно (используйте остаток).
// Пример: v = {1, 2, 3, 4, 5}, k = 2  ->  v = {3, 4, 5, 1, 2}
// Пример: v = {1, 2, 3},        k = 0  ->  v = {1, 2, 3}
// -----------------------------------------------------------------------------
void rotate_left(std::vector<int>& v, std::size_t k) {
    if (v.size() == 0) return; 
    k = k % v.size();
    std::vector<int> v_rotated;
    for (std::size_t i = k; i < v.size(); i++) v_rotated.push_back(v[i]);
    for (std::size_t i = 0; i < k; i++) v_rotated.push_back(v[i]);
    v = v_rotated;
}

// -----------------------------------------------------------------------------
// Задание 4: remove_duplicates (0.25 баллов)
// Верните новый вектор, в котором удалены все дубликаты.
// Первое вхождение каждого элемента сохраняется, порядок не меняется.
// Пример: remove_duplicates({3, 1, 4, 1, 5, 9, 2, 6, 5}) == {3, 1, 4, 5, 9, 2, 6}
// Пример: remove_duplicates({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> remove_duplicates(const std::vector<int>& v) {
    std::vector<int> v_cleared;
    for (auto i : v) {
        bool found = false;
        for (auto j : v_cleared) {
            if (i == j) found = true;
        }
        if (!found) v_cleared.push_back(i);
    }
    return v_cleared;
}

// -----------------------------------------------------------------------------
// Задание 5: flatten (0.25 баллов)
// «Разверните» двумерный вектор в одномерный, обходя строки слева направо,
// сверху вниз.
// Пример: flatten({{1, 2}, {3, 4}, {5}}) == {1, 2, 3, 4, 5}
// Пример: flatten({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> v_flatten;
    for (auto string : matrix) {
        for (auto i : string) v_flatten.push_back(i);
    }
    return v_flatten;
}

// -----------------------------------------------------------------------------
// Задание 6: merge_sorted (0.25 баллов)
// Слейте два отсортированных по возрастанию вектора в один отсортированный
// вектор (аналог merge из merge sort). Не используйте std::merge.
// Пример: merge_sorted({1, 3, 5}, {2, 4, 6}) == {1, 2, 3, 4, 5, 6}
// Пример: merge_sorted({}, {1, 2}) == {1, 2}
// -----------------------------------------------------------------------------
std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    int i = 0, j = 0;
    std::vector<int> v_merged;
    
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            v_merged.push_back(a[i]);
            i++;
        }
        else {
            v_merged.push_back(b[j]);
            j++;
        }
    }

    while (i < a.size()) {
        v_merged.push_back(a[i]);
        i++;
    }

    while (j < b.size()) {
        v_merged.push_back(b[j]);
        j++;
    }
    return v_merged;
}

// -----------------------------------------------------------------------------
// Задание 7: max_subarray_sum (0.5 баллов)
// Найдите максимальную сумму непрерывного подмассива (алгоритм Кадане).
// Подмассив должен содержать хотя бы один элемент.
// Если все элементы отрицательные — верните максимальный из них.
// Выбрасывает std::invalid_argument, если вектор пуст.
// Пример: max_subarray_sum({-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6
// Пример: max_subarray_sum({-3, -1, -2}) == -1
// -----------------------------------------------------------------------------
int max_subarray_sum(const std::vector<int>& v) {
    if (v.empty()) throw std::invalid_argument("Vector is empty!");
    int sum = 0, max_sum = 0;
    for (auto i : v) {
        sum += i;
        if (sum < 0) sum = 0;
        else if (max_sum < sum) max_sum = sum;
    }
    if (max_sum == 0) {
        max_sum = v[0];
        for (auto i : v) {
            if (i > max_sum) max_sum = i;
        }
    }
    return max_sum;
}

// -----------------------------------------------------------------------------
// Задание 8: group_by_remainder (0.5 баллов)
// Сгруппируйте элементы по остатку от деления на k.
// Верните вектор из k векторов: result[r] содержит элементы v[i], для которых
// (v[i] % k + k) % k == r, в порядке их появления в исходном векторе.
// Выбрасывает std::invalid_argument, если k <= 0.
// Пример: group_by_remainder({0, 1, 2, 3, 4, 5, 6}, 3)
//      == {{0, 3, 6}, {1, 4}, {2, 5}}
// -----------------------------------------------------------------------------
std::vector<std::vector<int>> group_by_remainder(const std::vector<int>& v, int k) {
    if (k <= 0) throw std::invalid_argument("k <= 0");
    
    std::vector<std::vector<int>> v_grouped;
    for (int i = 0; i < k; i++) {
        std::vector<int> a;
        v_grouped.push_back(a);
    }

    for (auto i : v) {
        v_grouped[(i % k + k) % k].push_back(i);
    }

    return v_grouped;
}
