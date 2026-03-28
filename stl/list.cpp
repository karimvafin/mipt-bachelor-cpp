#include <list>
#include <iostream>


void print_list(const std::list<int>& l) {
    for (const auto& x : l) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}


int main() {
    // Вопрос 1: чем list отличается от vector?
    // (двусвязный список, нет случайного доступа, O(1) вставка/удаление в любом месте)

    // Вопрос 2: инициализация list
    std::cout << "Вопрос 2: инициализация list" << std::endl;
    std::list<int> l1 = {1, 2, 3, 4, 5};
    std::list<int> l2;
    std::list<int> l3(5, 0);
    std::list<int> l4(l1);
    std::list<int> l5(std::move(l4));
    print_list(l1);
    print_list(l3);

    // Вопрос 3: методы list
    std::cout << "Вопрос 3: методы list" << std::endl;
    std::cout << l1.front() << std::endl;
    std::cout << l1.back() << std::endl;
    std::cout << l1.size() << std::endl;
    std::cout << l1.empty() << std::endl;

    l1.push_back(6);
    l1.push_front(0);
    l1.pop_back();
    l1.pop_front();
    print_list(l1);

    // Вопрос 4: почему у list нет operator[] и at()?

    // Вопрос 5: итераторы — только двунаправленные (bidirectional), не random access
    std::cout << "Вопрос 5: итераторы list" << std::endl;
    std::list<int>::iterator it = l1.begin();
    ++it;
    --it;
    // it + 2;  // ошибка компиляции — нет random access
    std::cout << *it << std::endl;

    // Вопрос 6: вставка и удаление не инвалидируют другие итераторы
    std::cout << "Вопрос 6: инвалидация итераторов" << std::endl;
    std::list<int> l6 = {1, 2, 3, 4, 5};
    std::list<int>::iterator it2 = l6.begin();
    ++it2; // указывает на 2
    l6.insert(it2, 99);  // вставляем 99 перед 2
    print_list(l6);      // {1, 99, 2, 3, 4, 5}
    std::cout << "it2 после insert = " << *it2 << std::endl;  // всё ещё 2
    l6.erase(it2);       // удаляем 2, it2 инвалидирован
    print_list(l6);      // {1, 99, 3, 4, 5}

    // Вопрос 7: splice — перенос элементов без копирования (O(1))
    std::cout << "Вопрос 7: splice" << std::endl;
    std::list<int> a = {1, 2, 3};
    std::list<int> b = {4, 5, 6};
    a.splice(a.end(), b);   // переносим все элементы b в конец a
    print_list(a);           // {1, 2, 3, 4, 5, 6}
    print_list(b);           // {}

    // Вопрос 8: методы, специфичные для list
    std::cout << "Вопрос 8: sort, reverse, unique, remove" << std::endl;
    std::list<int> l7 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    l7.sort();
    print_list(l7);   // {1, 1, 2, 3, 4, 5, 5, 6, 9}
    l7.unique();
    print_list(l7);   // {1, 2, 3, 4, 5, 6, 9}
    l7.reverse();
    print_list(l7);   // {9, 6, 5, 4, 3, 2, 1}
    l7.remove(5);
    print_list(l7);   // {9, 6, 4, 3, 2, 1}

    return 0;
}
