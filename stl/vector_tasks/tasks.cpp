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
    for (const int& i : v) sum += i;
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
    std::vector<int> v2;
    for (auto it = v.begin(); it != v.end(); ++it)
        if (*it % 2 == 0) v2.push_back(*it);
    return v2;
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
    if (v.empty()) return;
    std::vector<int> v_temp;
    k %= v.size();
    for (auto it = v.begin() + k; it != v.end(); ++it) v_temp.push_back(*it);
    for (auto it = v.begin(); it != v.begin() + k; ++it) v_temp.push_back(*it);
    v = v_temp;
}

// -----------------------------------------------------------------------------
// Задание 4: remove_duplicates (0.25 баллов)
// Верните новый вектор, в котором удалены все дубликаты.
// Первое вхождение каждого элемента сохраняется, порядок не меняется.
// Пример: remove_duplicates({3, 1, 4, 1, 5, 9, 2, 6, 5}) == {3, 1, 4, 5, 9, 2, 6}
// Пример: remove_duplicates({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> remove_duplicates(const std::vector<int>& v) {
    std::vector<int> v_new;
    for (auto it = v.begin(); it != v.end(); ++it) {
        bool found = false;
        for (auto it2 = v_new.begin(); it2 != v_new.end(); ++it2) {
            if (*it == *it2) {
                found = true;
                break;
            }
        }
        if (!found) v_new.push_back(*it);
    }
    return v_new;
}

// -----------------------------------------------------------------------------
// Задание 5: flatten (0.25 баллов)
// «Разверните» двумерный вектор в одномерный, обходя строки слева направо,
// сверху вниз.
// Пример: flatten({{1, 2}, {3, 4}, {5}}) == {1, 2, 3, 4, 5}
// Пример: flatten({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> v;
    for (const std::vector<int>& row : matrix)
        for (const int& i : row) v.push_back(i);
    return v;
}

// -----------------------------------------------------------------------------
// Задание 6: merge_sorted (0.25 баллов)
// Слейте два отсортированных по возрастанию вектора в один отсортированный
// вектор (аналог merge из merge sort). Не используйте std::merge.
// Пример: merge_sorted({1, 3, 5}, {2, 4, 6}) == {1, 2, 3, 4, 5, 6}
// Пример: merge_sorted({}, {1, 2}) == {1, 2}
// -----------------------------------------------------------------------------
std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> c;
    auto it = a.begin();
    auto it2 = b.begin();
    while (it != a.end() && it2 != b.end()) {
        if (*it < *it2) {
            c.push_back(*it);
            ++it;
        } else {
            c.push_back(*it2);
            ++it2;
        }
    }
    while (it != a.end()) {
        c.push_back(*it);
        ++it;
    }
    while (it2 != b.end()) {
        c.push_back(*it2);
        ++it2;
    }
    return c;
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
    if (v.empty()) throw std::invalid_argument("vector is empty");

    int Xi = v[0];
    int max_sum = v[0];
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
        Xi = std::max(Xi + *it, *it);
        max_sum = std::max(max_sum, Xi);
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
    if (k <= 0) throw std::invalid_argument("number of groups must be positive");
    std::vector<std::vector<int>> group_by_remainder(k);
    for (auto it = v.begin(); it != v.end(); ++it) group_by_remainder[(*it % k + k) % k].push_back(*it);
    return group_by_remainder;
}
