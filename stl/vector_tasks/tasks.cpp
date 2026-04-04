#include "tasks.h"
#include <stdexcept>

// =============================================================================
// Задания по std::vector
// Реализуйте все функции ниже — удалите throw и напишите свою реализацию.
// =============================================================================


// Задание 1: sum (0.25 баллов)
// Посчитайте сумму всех элементов вектора.
// Пример: sum({1, 2, 3, 4}) == 10
// Пример: sum({}) == 0
// -----------------------------------------------------------------------------
int sum(const std::vector<int>& v) {
   int res = 0;
   for(int i=0; i<v.size(); i++){
    res+= v[i];
   }
   return res;
}
// Задание 2: filter_even (0.25 баллов)
// Верните новый вектор, содержащий только чётные элементы исходного,
// сохраняя их порядок.
// Пример: filter_even({1, 2, 3, 4, 5, 6}) == {2, 4, 6}
// Пример: filter_even({1, 3, 5}) == {}
// -----------------------------------------------------------------------------
std::vector<int> filter_even(const std::vector<int>& v) {
    std::vector<int> u;
    for(int i=0; i<v.size(); i++){
        if(v[i]%2==0){u.push_back(v[i]);}
    }
    return u;
}
// Задание 3: rotate_left (0.25 баллов)
// Выполните циклический сдвиг вектора влево на k позиций (in-place).
// Элементы, «вышедшие» за левую границу, появляются в конце.
// Если k >= v.size(), сдвиг должен работать корректно (используйте остаток).
// Пример: v = {1, 2, 3, 4, 5}, k = 2  ->  v = {3, 4, 5, 1, 2}
// Пример: v = {1, 2, 3},        k = 0  ->  v = {1, 2, 3}
// -----------------------------------------------------------------------------
void rotate_left(std::vector<int>& v, std::size_t k) {
     if (v.empty()) return;
    if(k == 0) return;
    for(int i=0; i<k; i++){
        int temp = v[0];
        for(int j=0; j<v.size(); j++){
            if(j == v.size()-1){
                v[v.size()-1] = temp;
            }
            else{v[j] = v[j+1]; 
            }
        }
    }

}

// Задание 4: remove_duplicates (0.25 баллов)
// Верните новый вектор, в котором удалены все дубликаты.
// Первое вхождение каждого элемента сохраняется, порядок не меняется.
// Пример: remove_duplicates({3, 1, 4, 1, 5, 9, 2, 6, 5}) == {3, 1, 4, 5, 9, 2, 6}
// Пример: remove_duplicates({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> remove_duplicates(const std::vector<int>& v) {
      if (v.empty()) {  
        return v;
    }
    std::vector<int> u;
    bool flag = false;
    u.push_back(v[0]);
    for(int i = 1; i< v.size(); i++){
        for(int j=0; j<u.size(); j++){
            if(v[i] == u[j]){
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false; 
            continue;   
        }
        u.push_back(v[i]);
    }
    return u;
}
// Задание 5: flatten (0.25 баллов)
// «Разверните» двумерный вектор в одномерный, обходя строки слева направо,
// сверху вниз.
// Пример: flatten({{1, 2}, {3, 4}, {5}}) == {1, 2, 3, 4, 5}
// Пример: flatten({}) == {}
// -----------------------------------------------------------------------------
std::vector<int> flatten(const std::vector<std::vector<int>>& matrix) {
    std::vector<int> u;
    if(matrix.empty()) return u;
     for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            u.push_back(matrix[i][j]);
        }
     }
     return u;
}
// -----------------------------------------------------------------------------
// Задание 6: merge_sorted (0.25 баллов)
// Слейте два отсортированных по возрастанию вектора в один отсортированный
// вектор (аналог merge из merge sort). Не используйте std::merge.
// Пример: merge_sorted({1, 3, 5}, {2, 4, 6}) == {1, 2, 3, 4, 5, 6}
// Пример: merge_sorted({}, {1, 2}) == {1, 2}
// -----------------------------------------------------------------------------
std::vector<int> merge_sorted(const std::vector<int>& a, const std::vector<int>& b) {
    int i=0;
    int j=0;
    std::vector<int> res;
    while(i<a.size() && j<b.size()){
        if(a[i]<=b[j]) {
            res.push_back(a[i]);
            i++;}
        else {
            res.push_back(b[j]);
            j++;}
        }
    if(i==a.size()){
        for(j; j<b.size(); j++){
            res.push_back(b[j]);
        }
    }
    if(j==b.size()){
        for(i; i<a.size(); i++){
            res.push_back(a[i]);
        }
    }
    return res;
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
    if(v.empty()) throw std::invalid_argument(".");
    int res = v[0];
    int max_index = v[0];
    for(int i=1; i<v.size(); i++){
        max_index = std::max(max_index+v[i], v[i]);  
        res = std::max(res, max_index);
    }
    return res;
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
    if(k<=0) throw std::invalid_argument(".");
    std::vector<std::vector<int>> res;
    int index = 0;
    res.resize(k);
    for(int i=0; i<v.size(); i++){
        index = (v[i] % k + k) % k;
        res[index].push_back(v[i]);
    }
return res;
}
