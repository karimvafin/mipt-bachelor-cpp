#include <iostream>
#include <functional>
#include <vector>
#include <string>

// ── 1. Хранение разных callable в std::function ───────────────────────────────

int free_add(int a, int b) { return a + b; }

// Функтор — класс с operator()
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};

// ── 2. std::function как параметр функции ────────────────────────────────────

void transform(std::vector<int>& v, std::function<int(int)> f) {
    for (int& x : v) x = f(x);
}

void print_vec(const std::vector<int>& v, const std::string& label) {
    std::cout << label << ": ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

// ── 3. std::function как поле класса (callback) ───────────────────────────────

class Button {
public:
    std::function<void()> on_click;

    void click() {
        if (on_click) {
            on_click();
        } else {
            std::cout << "Button: no handler\n";
        }
    }
};

// ── 4. std::bind — частичное применение аргументов ───────────────────────────

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

// ── 5. std::function и рекурсия ───────────────────────────────────────────────
// Лямбда не может рекурсивно ссылаться на себя через auto,
// но может через std::function.

int main() {
    // 1. Разные callable в одном типе
    Multiplier triple{3};
    int y = triple(10);

    std::cout << "=== Storing different callables ===\n";

    std::function<int(int, int)> op;

    op = free_add;
    std::cout << "free function: " << op(3, 4) << "\n";  // 7

    op = [](int a, int b) { return a * b; };
    std::cout << "lambda:        " << op(3, 4) << "\n";  // 12

    op = std::plus<int>{};
    std::cout << "std::plus:     " << op(3, 4) << "\n";  // 7

    // 2. transform с разными функциями
    std::cout << "\n=== Transform ===\n";
    std::vector<int> v = {1, 2, 3, 4, 5};

    Multiplier triple{3};
    transform(v, triple);
    print_vec(v, "x3");  // 3 6 9 12 15

    int offset = 10;
    transform(v, [offset](int x) { return x + offset; });
    print_vec(v, "+10"); // 13 16 19 22 25

    // 3. Callback через std::function
    std::cout << "\n=== Callback ===\n";
    Button btn;
    btn.click();  // no handler

    int click_count = 0;
    btn.on_click = [&click_count]() {
        ++click_count;
        std::cout << "Button clicked! Count: " << click_count << "\n";
    };
    btn.click();
    btn.click();

    // Сбросить обработчик
    btn.on_click = nullptr;
    btn.click();  // no handler снова

    // 4. std::bind
    std::cout << "\n=== std::bind ===\n";

    // Фиксируем второй аргумент (exp = 2) — получаем функцию возведения в квадрат
    // std::placeholders::_1 — место для первого аргумента при вызове
    auto square = std::bind(power, std::placeholders::_1, 2);
    auto cube   = std::bind(power, std::placeholders::_1, 3);

    std::cout << "square(5) = " << square(5) << "\n";  // 25
    std::cout << "cube(3)   = " << cube(3)   << "\n";  // 27

    // 5. Рекурсивная лямбда через std::function
    std::cout << "\n=== Recursive lambda ===\n";
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    std::cout << "factorial(6) = " << factorial(6) << "\n";  // 720

    // 6. Проверка на пустоту
    std::cout << "\n=== Empty check ===\n";
    std::function<void()> empty_fn;
    std::cout << "empty_fn is " << (empty_fn ? "set" : "empty") << "\n";

    // Вызов пустого std::function бросает std::bad_function_call:
    // empty_fn();  // исключение!

    return 0;
}
