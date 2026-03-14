#include <iostream>
#include <algorithm>

// ── 1. Объявление и использование указателя на функцию ───────────────────────

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// Синтаксис: ReturnType (*name)(ParamTypes...)
// Псевдоним упрощает чтение
using BinaryOp = int(*)(int, int);

void apply_and_print(int a, int b, BinaryOp op) {
    std::cout << "Result: " << op(a, b) << "\n";
}

// ── 2. Массив указателей на функцию ──────────────────────────────────────────

// Удобно для таблиц диспетчеризации (dispatch table)
BinaryOp ops[] = { add, sub, mul };
const char* op_names[] = { "add", "sub", "mul" };

// ── 3. Возврат указателя на функцию ──────────────────────────────────────────

BinaryOp choose_op(char symbol) {
    switch (symbol) {
        case '+': return add;
        case '-': return sub;
        case '*': return mul;
        default:  return nullptr;
    }
}

// ── 4. Указатель на функцию как параметр сортировки ──────────────────────────

bool ascending(int a, int b)  { return a < b; }
bool descending(int a, int b) { return a > b; }

void bubble_sort(int* arr, int n, bool(*cmp)(int, int)) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (!cmp(arr[j], arr[j + 1]))
                std::swap(arr[j], arr[j + 1]);
}

void print_array(const int* arr, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

// ── 5. Указатель на функцию: ограничения ─────────────────────────────────────
// Лямбда БЕЗ захвата неявно конвертируется в указатель на функцию.
// Лямбда С захватом — нет.

int main() {
    int x = 10;
    int* x_ptr = &x;

    // 1. Базовое использование
    std::cout << "=== Basic usage ===\n";
    BinaryOp op = add;
    std::cout << "add(3, 4) = " << op(3, 4) << "\n";

    op = mul;
    std::cout << "mul(3, 4) = " << op(3, 4) << "\n";

    apply_and_print(10, 3, sub);

    // 2. Таблица диспетчеризации
    std::cout << "\n=== Dispatch table ===\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << op_names[i] << "(6, 2) = " << ops[i](6, 2) << "\n";
    }

    // 3. Возврат указателя на функцию
    std::cout << "\n=== Choose op ===\n";
    BinaryOp selected = choose_op('+');
    if (selected) {
        std::cout << "'+' op result: " << selected(7, 8) << "\n";
    }

    selected = choose_op('?');
    if (!selected) {
        std::cout << "Unknown op: nullptr\n";
    }

    // 4. Сортировка с компаратором
    std::cout << "\n=== Sorting ===\n";
    int arr[] = {5, 2, 8, 1, 9, 3};
    int n = 6;

    bubble_sort(arr, n, ascending);
    std::cout << "Ascending:  "; print_array(arr, n);

    bubble_sort(arr, n, descending);
    std::cout << "Descending: "; print_array(arr, n);

    // 5. Лямбда без захвата -> указатель на функцию
    std::cout << "\n=== Lambda without capture ===\n";
    BinaryOp lambda_op = [](int a, int b) { return a + b * 2; };
    std::cout << "lambda(3, 4) = " << lambda_op(3, 4) << "\n";  // 11

    // Лямбда с захватом НЕ конвертируется в указатель на функцию:
    // int factor = 3;
    // BinaryOp bad = [factor](int a, int b) { return a * factor + b; }; // ошибка!

    return 0;
}
