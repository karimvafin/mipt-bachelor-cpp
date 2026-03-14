#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// ── 1. Базовый синтаксис лямбды ───────────────────────────────────────────────

// [захват](параметры) -> тип_возврата { тело }
// Тип возврата можно не писать — он выводится автоматически.

// ── 2. Захват переменных ──────────────────────────────────────────────────────

void capture_demo() {
    std::cout << "=== Capture ===\n";

    int x = 10;
    int y = 20;

    // [] — без захвата
    auto no_capture = []() { return 42; };
    std::cout << "no capture: " << no_capture() << "\n";

    // [x] — захват x по значению (копия на момент создания лямбды)
    auto by_value = [x]() { return x + 1; };
    x = 999;  // изменение оригинала не влияет на лямбду
    std::cout << "by value: " << by_value() << "\n";  // 11, не 1000

    // [&x] — захват x по ссылке
    int counter = 0;
    auto by_ref = [&counter]() { ++counter; };
    by_ref();
    by_ref();
    std::cout << "by ref counter: " << counter << "\n";  // 2

    // [=] — всё используемое по значению
    int a = 3, b = 4;
    auto all_by_value = [=]() { return a + b; };
    std::cout << "all by value: " << all_by_value() << "\n";  // 7

    // [&] — всё используемое по ссылке
    int sum = 0;
    auto all_by_ref = [&]() { sum = a + b + x; };
    all_by_ref();
    std::cout << "all by ref sum: " << sum << "\n";

    // [=, &y] — всё по значению, кроме y — по ссылке
    int result = 0;
    auto mixed = [=, &result]() { result = a + b; };
    mixed();
    std::cout << "mixed: " << result << "\n";  // 7
}

// ── 3. mutable: изменение захваченной по значению переменной ─────────────────

void mutable_demo() {
    std::cout << "\n=== mutable ===\n";

    int count = 0;

    // Без mutable нельзя изменить захваченную по значению переменную
    // auto bad = [count]() { count++; };  // ошибка!

    // С mutable — можно, но оригинал не меняется
    auto counter = [count]() mutable {
        ++count;
        return count;
    };
    std::cout << counter() << "\n";  // 1
    std::cout << counter() << "\n";  // 2
    std::cout << "original count: " << count << "\n";  // 0 — не изменился
}

// ── 4. Обобщённые лямбды (C++14) — параметры auto ────────────────────────────

void generic_lambda_demo() {
    std::cout << "\n=== Generic lambda ===\n";

    auto print = [](auto x) { std::cout << x << "\n"; };
    print(42);
    print(3.14);
    print("hello");

    auto add = [](auto a, auto b) { return a + b; };
    std::cout << add(1, 2) << "\n";       // 3
    std::cout << add(1.5, 2.5) << "\n";  // 4.0
}

// ── 5. Лямбды в алгоритмах STL ───────────────────────────────────────────────

void stl_demo() {
    std::cout << "\n=== STL algorithms ===\n";

    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
    std::cout << "sorted: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    int threshold = 5;
    auto it = std::find_if(v.begin(), v.end(), [threshold](int x) {
        return x > threshold;
    });
    std::cout << "first > " << threshold << ": " << *it << "\n";  // 6

    int count = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    std::cout << "even count: " << count << "\n";
}

// ── 6. Возврат лямбды из функции (фабрика замыканий) ─────────────────────────

auto make_adder(int n) {
    return [n](int x) { return x + n; };
}

auto make_multiplier(int factor) {
    return [factor](int x) { return x * factor; };
}

void factory_demo() {
    std::cout << "\n=== Closure factory ===\n";

    auto add5  = make_adder(5);
    auto add10 = make_adder(10);

    std::cout << "add5(3)  = " << add5(3)  << "\n";  // 8
    std::cout << "add10(3) = " << add10(3) << "\n";  // 13

    auto double_it = make_multiplier(2);
    std::cout << "double(7) = " << double_it(7) << "\n";  // 14
}

// ── 7. IIFE — немедленный вызов лямбды ───────────────────────────────────────

void iife_demo() {
    std::cout << "\n=== IIFE ===\n";

    // Полезно для инициализации const-переменных со сложной логикой
    const int value = []{
        int result = 0;
        for (int i = 1; i <= 10; ++i) result += i;
        return result;
    }();

    std::cout << "sum 1..10 = " << value << "\n";  // 55
}

int main() {
    int x = 0;
    int y = 1;
    std::function<void(int, float)> f = [=, &x](int z, float d){ x = y; };
    f(1, 1.0);

    capture_demo();
    mutable_demo();
    generic_lambda_demo();
    stl_demo();
    factory_demo();
    iife_demo();
    return 0;
}
