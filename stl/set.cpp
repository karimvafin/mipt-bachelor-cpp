#include <set>
#include <iostream>
#include <algorithm>


void print_set(const std::set<int>& s) {
    for (const auto& x : s) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}


int main() {
    // Вопрос 1: что такое set?
    // (красно-чёрное дерево, элементы уникальны и всегда отсортированы, O(log n))

    // Вопрос 2: чем отличается от unordered_set?
    // (unordered_set — хэш-таблица, O(1) среднее, порядок не гарантирован)

    // Вопрос 3: инициализация set
    std::cout << "Вопрос 3: инициализация set" << std::endl;
    std::set<int> s1 = {5, 3, 1, 4, 2, 3, 1};  // дубликаты молча игнорируются
    std::set<int> s2;
    std::set<int> s3(s1);
    std::set<int> s4(std::move(s3));
    std::set<int> s5(s1.begin(), s1.end());     // из диапазона итераторов
    print_set(s1);  // {1, 2, 3, 4, 5} — отсортировано, дубликатов нет

    // Вопрос 4: вставка элементов
    std::cout << "Вопрос 4: вставка элементов" << std::endl;
    auto [it1, ok1] = s2.insert(10);  // возвращает {iterator, bool}
    auto [it2, ok2] = s2.insert(10);  // повторная вставка — ok2 == false
    std::cout << "first insert: " << ok1 << std::endl;
    std::cout << "second insert: " << ok2 << std::endl;
    s2.emplace(20);
    print_set(s2);

    // Вопрос 5: поиск элементов
    std::cout << "Вопрос 5: поиск элементов" << std::endl;
    auto it = s1.find(3);
    if (it != s1.end()) {
        std::cout << "found: " << *it << std::endl;
    }
    std::cout << s1.count(3) << std::endl;     // 0 или 1
    std::cout << s1.contains(3) << std::endl;  // C++20

    // Вопрос 6: lower_bound и upper_bound
    std::cout << "Вопрос 6: lower_bound и upper_bound" << std::endl;
    std::set<int> s6 = {1, 3, 5, 7, 9};
    auto lo = s6.lower_bound(4);  // первый элемент >= 4
    auto hi = s6.upper_bound(7);  // первый элемент > 7
    std::cout << "lower_bound(4) = " << *lo << std::endl;  // 5
    std::cout << "upper_bound(7) = " << *hi << std::endl;  // 9
    // элементы в диапазоне [4, 7]:
    for (auto i = lo; i != hi; ++i) {
        std::cout << *i << " ";  // 5 7
    }
    std::cout << std::endl;

    // Вопрос 7: удаление элементов
    std::cout << "Вопрос 7: удаление элементов" << std::endl;
    std::set<int> s7 = {1, 2, 3, 4, 5};
    s7.erase(3);                         // по значению
    s7.erase(s7.begin());                // по итератору
    s7.erase(s7.find(4), s7.end());      // по диапазону
    print_set(s7);  // {2}

    // Вопрос 8: итераторы set — только bidirectional, разыменование даёт const
    std::cout << "Вопрос 8: итераторы set" << std::endl;
    std::set<int> s8 = {1, 2, 3};
    auto sit = s8.begin();
    // *sit = 10;  // ошибка компиляции — нельзя менять элемент через итератор
    std::cout << *sit << std::endl;

    // Вопрос 9: операции над множествами через алгоритмы STL
    std::cout << "Вопрос 9: операции над множествами" << std::endl;
    std::set<int> A = {1, 2, 3, 4};
    std::set<int> B = {3, 4, 5, 6};
    std::set<int> result;

    std::set_union(A.begin(), A.end(), B.begin(), B.end(),
                   std::inserter(result, result.begin()));
    print_set(result);  // {1, 2, 3, 4, 5, 6}
    result.clear();

    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                          std::inserter(result, result.begin()));
    print_set(result);  // {3, 4}
    result.clear();

    std::set_difference(A.begin(), A.end(), B.begin(), B.end(),
                        std::inserter(result, result.begin()));
    print_set(result);  // {1, 2}

    return 0;
}
