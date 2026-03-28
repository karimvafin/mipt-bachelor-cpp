#include <vector>
#include <iostream>


void print_vector(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
    // Вопрос 1: какие проблемы у сырых динамических массивов? (new, delete, pointers)
    int* ptr = new int[10];
    ptr[0] = 1;
    delete[] ptr;

    // Вопрос 2: что решает эти проблемы?

    // Вопрос 3: почему не нужно писать свою реализацию vector?

    // Вопрос 4: инициализация vector
    std::cout << "Вопрос 4: инициализация vector" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2;
    std::vector<int> v3(10, 0);
    std::vector<int> v3_1{10, 0};
    std::vector<int> v4(v2);
    std::vector<int> v5(std::move(v2));
    std::vector<int> v6 = std::move(v5);
    std::vector<int> v7 = v6;

    // Вопрос 5: методы вектора
    std::cout << "Вопрос 5: методы вектора" << std::endl;
    std::cout << v1[0] << std::endl;
    std::cout << v1.at(0) << std::endl;
    std::cout << v1.front() << std::endl;
    std::cout << v1.back() << std::endl;
    std::cout << v1.data() << std::endl;
    std::cout << v1.size() << std::endl;
    std::cout << v1.capacity() << std::endl;
    std::cout << v1.empty() << std::endl;

    v1.push_back(6);
    v1.pop_back();
    v1.insert(v1.begin() + 1, 7);
    v1.erase(v1.begin() + 1);
    v1.clear();
    v1.resize(10);
    v1.reserve(10);
    v1.shrink_to_fit();
    v1.swap(v2);

    // Вопрос 6: push_back и emplace_back
    std::cout << "Вопрос 6: push_back и emplace_back" << std::endl;
    std::vector<std::vector<int>> v8;
    std::vector<int> v = {1, 2, 3};
    v8.push_back(v);
    v8.emplace_back(1, 10);
    print_vector(v8[0]);
    print_vector(v8[1]);

    // Вопрос 7: инвалидация итераторов
    std::cout << "Вопрос 7: инвалидация итераторов" << std::endl;
    std::vector<int> v9 = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v9.begin();
    std::cout << "it before resize = " << *it << std::endl;
    v9.resize(10);
    print_vector(v9);
    std::cout << "it after resize = " << *it << std::endl;

    return 0; 
}