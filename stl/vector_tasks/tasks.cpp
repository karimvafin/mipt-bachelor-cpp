#include "tasks.h"

// =============================================================================
// Задания по std::vector
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1 (Лёгкое): sum
// Посчитайте сумму всех элементов вектора.
// Пример: sum({1, 2, 3, 4}) == 10
// Пример: sum({}) == 0
// -----------------------------------------------------------------------------
int sum(const std::vector<int>& v) {
    int sum = 0;
    for(int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum;
}

// -----------------------------------------------------------------------------
// Задание 2 (Лёгкое): filter_even
// Верните новый вектор, содержащий только чётные элементы исходного,
// сохраняя их порядок.
// Пример: filter_even({1, 2, 3, 4, 5, 6}) == {2, 4, 6}
// Пример: filter_even({1, 3, 5}) == {}
// -----------------------------------------------------------------------------
std::vector<int> filter_even(const std::vector<int>& v) {
    std::vector<int> even;
    int j = 0;
    even.reserve(v.size());

    for(int i = 0; i < v.size(); i++) {
        if (v[i] % 2 == 0) {
            even.push_back(v[i]);
        }
    }
    return even;
}

// -----------------------------------------------------------------------------
// Задание 3 (Лёгкое-Среднее): rotate_left
// Выполните циклический сдвиг вектора влево на k позиций (in-place).
// Элементы, «вышедшие» за левую границу, появляются в конце.
// Если k >= v.size(), сдвиг должен работать корректно (используйте остаток).
// Пример: v = {1, 2, 3, 4, 5}, k = 2  ->  v = {3, 4, 5, 1, 2}
// Пример: v = {1, 2, 3},        k = 0  ->  v = {1, 2, 3}
// -----------------------------------------------------------------------------
void rotate_left(std::vector<int>& v, std::size_t k) {
    if (v.empty()) {
        return;
    }
    k %= v.size(); 
    if (k == 0) return;
    
    std::vector<int> rotate(v.size(), 0);
    for (int i = k; i < v.size(); i++) {
        rotate[i - k] = v[i];
    }
    
    for (int i = 0; i < k; i++) {
        rotate[v.size() - k + i] = v[i]; 
    }
    
    v = rotate;
}

// -----------------------------------------------------------------------------
// Задание 4 (Среднее): remove_duplicates
// Верните новый вектор, в котором удалены все дубликаты.
// Первое вхождение каждого элемента сохраняется, порядок не меняется.
// Пример: remove_duplicates({3, 1, 4, 1, 5, 9, 2, 6, 5}) == {3, 1, 4, 5, 9, 2, 6}
// Пример: remove_duplicates({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> remove_duplicates(const std::vector<int>& v) {
    std::vector<int> res;
    res.reserve(v.size());

    for (int i = 0; i < v.size(); i++) {
        bool found = false;
        for (int j = 0; j < res.size(); j++) {
            if (res[j] == v[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            res.push_back(v[i]);
        }
    }
    return res;
}

// -----------------------------------------------------------------------------
// Задание 5 (Среднее): flatten
// «Разверните» двумерный вектор в одномерный, обходя строки слева направо,
// сверху вниз.
// Пример: flatten({{1, 2}, {3, 4}, {5}}) == {1, 2, 3, 4, 5}
// Пример: flatten({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        return {};
    }
    int size_matrics = 0;
    for (int i = 0; i < matrix.size(); i++) {
        size_matrics += matrix[i].size();
    }

    std::vector<int> result;
    result.reserve(size_matrics);

    for (int i = 0; i < matrix.size(); i++) {
        if (!matrix[i].empty()) {
            for (int j = 0; j < matrix[i].size(); j++) {
                result.push_back(matrix[i][j]);
            }
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Задание 6 (Среднее): merge_sorted
// Слейте два отсортированных по возрастанию вектора в один отсортированный
// вектор (аналог merge из merge sort). Не используйте std::merge.
// Пример: merge_sorted({1, 3, 5}, {2, 4, 6}) == {1, 2, 3, 4, 5, 6}
// Пример: merge_sorted({}, {1, 2}) == {1, 2}
// -----------------------------------------------------------------------------
std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    result.reserve(a.size() + b.size());

    size_t a_i = 0, b_i = 0;

    while (a_i < a.size() && b_i < b.size()) {
        if (a[a_i] <= b[b_i]) {
            result.push_back(a[a_i]);  
            a_i++;                      
        } else {
            result.push_back(b[b_i]);
            b_i++;
        }
    }

    while (a_i < a.size()) {
        result.push_back(a[a_i]);
        a_i++;
    }

    while (b_i < b.size()) {
        result.push_back(b[b_i]);
        b_i++;
    }

    return result;
}

// -----------------------------------------------------------------------------
// Задание 7 (Сложное): max_subarray_sum
// Найдите максимальную сумму непрерывного подмассива (алгоритм Кадане).
// Подмассив должен содержать хотя бы один элемент.
// Если все элементы отрицательные — верните максимальный из них.
// Выбрасывает std::invalid_argument, если вектор пуст.
// Пример: max_subarray_sum({-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6
// Пример: max_subarray_sum({-3, -1, -2}) == -1
// -----------------------------------------------------------------------------
int max_subarray_sum(const std::vector<int>& v) {
    if (v.empty()) {
        throw std::invalid_argument("empty vector");  
    }

    int max_sum = v[0];  
    int cur_sum = v[0];

    for (size_t i = 1; i < v.size(); i++) {  
        if (cur_sum > 0) {
            cur_sum = v[i] + cur_sum; 
        }
        else {
            cur_sum = v[i];
        }

        if (max_sum < cur_sum) {
            max_sum = cur_sum; 
        }
    }
    return max_sum;
}

// -----------------------------------------------------------------------------
// Задание 8 (Сложное): group_by_remainder
// Сгруппируйте элементы по остатку от деления на k.
// Верните вектор из k векторов: result[r] содержит элементы v[i], для которых
// (v[i] % k + k) % k == r, в порядке их появления в исходном векторе.
// Выбрасывает std::invalid_argument, если k <= 0.
// Пример: group_by_remainder({0, 1, 2, 3, 4, 5, 6}, 3)
//      == {{0, 3, 6}, {1, 4}, {2, 5}}
// -----------------------------------------------------------------------------
std::vector<std::vector<int>> group_by_remainder(const std::vector<int>& v, int k) {
    if (k <= 0) {
        throw std::invalid_argument("k<=0");
    }
    if (v.empty()) {
        return std::vector<std::vector<int>>(k);
    }

    std::vector<std::vector<int>> result(k);

    for (size_t i = 0; i < v.size(); i++) {
        result[(v[i] % k + k) % k].push_back(v[i]);
    }
    return result;
}