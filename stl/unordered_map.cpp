#include <unordered_map>
#include <iostream>
#include <string>


void print_map(const std::unordered_map<std::string, int>& m) {
    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
}


int main() {
    // Вопрос 1: что такое unordered_map?
    // (хэш-таблица, O(1) среднее для вставки/поиска/удаления, порядок не гарантирован)

    // Вопрос 2: чем отличается от std::map?
    // (map — красно-чёрное дерево, O(log n), элементы отсортированы по ключу)

    // Вопрос 3: инициализация unordered_map
    std::cout << "Вопрос 3: инициализация unordered_map" << std::endl;
    std::unordered_map<std::string, int> m1 = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::unordered_map<std::string, int> m2;
    std::unordered_map<std::string, int> m3(m1);
    std::unordered_map<std::string, int> m4(std::move(m3));
    print_map(m1);

    // Вопрос 4: вставка элементов
    std::cout << "Вопрос 4: вставка элементов" << std::endl;
    m2["four"] = 4;                           // operator[] — вставляет, если ключа нет
    m2.insert({"five", 5});                   // insert — не перезапишет существующий ключ
    m2.insert_or_assign("four", 44);          // insert_or_assign — перезапишет (C++17)
    m2.emplace("six", 6);                     // emplace — конструирует на месте
    print_map(m2);

    // Вопрос 5: опасность operator[]
    std::cout << "Вопрос 5: опасность operator[]" << std::endl;
    std::unordered_map<std::string, int> m5;
    std::cout << m5["missing"] << std::endl;  // создаёт элемент со значением 0!
    std::cout << m5.size() << std::endl;      // 1 — элемент появился

    // Вопрос 6: поиск элементов
    std::cout << "Вопрос 6: поиск элементов" << std::endl;
    auto it = m1.find("one");
    if (it != m1.end()) {
        std::cout << "found: " << it->first << " = " << it->second << std::endl;
    }
    std::cout << m1.count("two") << std::endl;     // 0 или 1
    std::cout << m1.contains("three") << std::endl; // C++20

    // Вопрос 7: безопасное чтение — at() бросает исключение, operator[] вставляет
    std::cout << "Вопрос 7: at() vs operator[]" << std::endl;
    try {
        std::cout << m1.at("one") << std::endl;
        std::cout << m1.at("missing") << std::endl;  // бросает std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    // Вопрос 8: удаление элементов
    std::cout << "Вопрос 8: удаление элементов" << std::endl;
    m1.erase("one");
    auto it2 = m1.find("two");
    if (it2 != m1.end()) m1.erase(it2);
    print_map(m1);

    // Вопрос 9: обход и структурные привязки (C++17)
    std::cout << "Вопрос 9: обход" << std::endl;
    std::unordered_map<std::string, int> m6 = {{"a", 1}, {"b", 2}, {"c", 3}};
    for (const auto& [key, value] : m6) {
        std::cout << key << " -> " << value << std::endl;
    }

    // Вопрос 10: инвалидация итераторов при rehash
    std::cout << "Вопрос 10: rehash и load_factor" << std::endl;
    std::unordered_map<int, int> m7;
    m7.reserve(100);                              // резервируем место, избегаем rehash
    std::cout << m7.bucket_count() << std::endl;
    std::cout << m7.load_factor() << std::endl;
    std::cout << m7.max_load_factor() << std::endl;

    return 0;
}
