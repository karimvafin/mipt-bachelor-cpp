#include "tasks.h"

#include <functional>
#include <iostream>
#include <string>
#include <type_traits>

// =============================================================================
// Минимальный тест-раннер
// =============================================================================

static int g_total = 0;
static int g_failed = 0;

void run_test(const std::string& name, std::function<void()> test) {
    ++g_total;
    try {
        test();
        std::cout << "[PASS] " << name << "\n";
    } catch (const std::exception& e) {
        ++g_failed;
        std::cout << "[FAIL] " << name << " — " << e.what() << "\n";
    }
}

void check(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

template <typename T>
void check_eq(const T& actual, const T& expected, const std::string& message) {
    if (actual != expected) {
        throw std::runtime_error(message);
    }
}

// =============================================================================
// Задание 1: Pow
// =============================================================================

void test_pow() {
    run_test("Pow: 2^0 == 1", [] {
        check_eq(Pow<2, 0>::value, 1, "Pow<2, 0> должен быть 1");
    });
    run_test("Pow: 2^10 == 1024", [] {
        check_eq(Pow<2, 10>::value, 1024, "Pow<2, 10> должен быть 1024");
    });
    run_test("Pow: 3^4 == 81", [] {
        check_eq(Pow<3, 4>::value, 81, "Pow<3, 4> должен быть 81");
    });
    run_test("Pow: 5^1 == 5", [] {
        check_eq(Pow<5, 1>::value, 5, "Pow<5, 1> должен быть 5");
    });
    run_test("Pow: (-2)^3 == -8", [] {
        check_eq(Pow<-2, 3>::value, -8, "Pow<-2, 3> должен быть -8");
    });
    run_test("Pow: 1^100 == 1", [] {
        check_eq(Pow<1, 100>::value, 1, "Pow<1, 100> должен быть 1");
    });
    run_test("Pow: 0^0 == 1 (по соглашению)", [] {
        check_eq(Pow<0, 0>::value, 1, "Pow<0, 0> должен быть 1");
    });
}

// =============================================================================
// Задание 2: IsReference
// =============================================================================

void test_is_reference() {
    run_test("IsReference<int> == false", [] {
        check(!IsReference<int>::value, "int не ссылка");
    });
    run_test("IsReference<int*> == false", [] {
        check(!IsReference<int*>::value, "int* не ссылка");
    });
    run_test("IsReference<int&> == true", [] {
        check(IsReference<int&>::value, "int& — lvalue-ссылка");
    });
    run_test("IsReference<int&&> == true", [] {
        check(IsReference<int&&>::value, "int&& — rvalue-ссылка");
    });
    run_test("IsReference<const int&> == true", [] {
        check(IsReference<const int&>::value, "const int& — lvalue-ссылка");
    });
    run_test("IsReference<double&&> == true", [] {
        check(IsReference<double&&>::value, "double&& — rvalue-ссылка");
    });
    run_test("IsReference<std::string> == false", [] {
        check(!IsReference<std::string>::value, "std::string не ссылка");
    });
}

// =============================================================================
// Задание 3: RemoveConst
// =============================================================================

void test_remove_const() {
    run_test("RemoveConst<int> -> int", [] {
        check(std::is_same_v<RemoveConstT<int>, int>, "int должен остаться int");
    });
    run_test("RemoveConst<const int> -> int", [] {
        check(std::is_same_v<RemoveConstT<const int>, int>, "const int -> int");
    });
    run_test("RemoveConst<const double> -> double", [] {
        check(std::is_same_v<RemoveConstT<const double>, double>, "const double -> double");
    });
    run_test("RemoveConst<int* const> -> int*", [] {
        check(std::is_same_v<RemoveConstT<int* const>, int*>,
              "const на указателе должен сниматься");
    });
    run_test("RemoveConst<const int*> -> const int*", [] {
        check(std::is_same_v<RemoveConstT<const int*>, const int*>,
              "const на int не должен сниматься (он не на верхнем уровне)");
    });
    run_test("RemoveConst<const int&> -> const int&", [] {
        check(std::is_same_v<RemoveConstT<const int&>, const int&>,
              "const внутри ссылки не должен сниматься");
    });
}

// =============================================================================
// Задание 4: TypeAt
// =============================================================================

void test_type_at() {
    using L = TypeList<int, double, char>;

    run_test("TypeAt<0, L> == int", [] {
        check(std::is_same_v<TypeAtT<0, L>, int>, "0-й тип — int");
    });
    run_test("TypeAt<1, L> == double", [] {
        check(std::is_same_v<TypeAtT<1, L>, double>, "1-й тип — double");
    });
    run_test("TypeAt<2, L> == char", [] {
        check(std::is_same_v<TypeAtT<2, L>, char>, "2-й тип — char");
    });
    run_test("TypeAt из списка одного элемента", [] {
        check(std::is_same_v<TypeAtT<0, TypeList<long>>, long>, "0-й тип — long");
    });
    run_test("TypeAt из длинного списка", [] {
        using Big = TypeList<int, double, char, float, long, short>;
        check(std::is_same_v<TypeAtT<4, Big>, long>, "4-й тип — long");
    });
    run_test("TypeAt: вложенные списки как элементы", [] {
        using L2 = TypeList<TypeList<int>, TypeList<double, char>>;
        check(std::is_same_v<TypeAtT<1, L2>, TypeList<double, char>>,
              "1-й тип — TypeList<double, char>");
    });
}

// =============================================================================
// Задание 5: Concat и Reverse
// =============================================================================

void test_concat() {
    run_test("Concat: <int> + <double> -> <int, double>", [] {
        using R = ConcatT<TypeList<int>, TypeList<double>>;
        check(std::is_same_v<R, TypeList<int, double>>, "склейка двух одиночек");
    });
    run_test("Concat: <int, double> + <char, long>", [] {
        using R = ConcatT<TypeList<int, double>, TypeList<char, long>>;
        check(std::is_same_v<R, TypeList<int, double, char, long>>,
              "склейка двух пар");
    });
    run_test("Concat: <> + <int>", [] {
        using R = ConcatT<TypeList<>, TypeList<int>>;
        check(std::is_same_v<R, TypeList<int>>, "пустой + одиночка");
    });
    run_test("Concat: <int> + <>", [] {
        using R = ConcatT<TypeList<int>, TypeList<>>;
        check(std::is_same_v<R, TypeList<int>>, "одиночка + пустой");
    });
    run_test("Concat: <> + <>", [] {
        using R = ConcatT<TypeList<>, TypeList<>>;
        check(std::is_same_v<R, TypeList<>>, "пустой + пустой");
    });
}

void test_reverse() {
    run_test("Reverse: <> -> <>", [] {
        check(std::is_same_v<ReverseT<TypeList<>>, TypeList<>>,
              "пустой список переворачивается в пустой");
    });
    run_test("Reverse: <int> -> <int>", [] {
        check(std::is_same_v<ReverseT<TypeList<int>>, TypeList<int>>,
              "одиночка остаётся одиночкой");
    });
    run_test("Reverse: <int, double> -> <double, int>", [] {
        check(std::is_same_v<ReverseT<TypeList<int, double>>, TypeList<double, int>>,
              "переворот пары");
    });
    run_test("Reverse: <int, double, char> -> <char, double, int>", [] {
        check(std::is_same_v<ReverseT<TypeList<int, double, char>>,
                             TypeList<char, double, int>>,
              "переворот тройки");
    });
    run_test("Reverse: <int, double, char, long> -> <long, char, double, int>", [] {
        check(std::is_same_v<ReverseT<TypeList<int, double, char, long>>,
                             TypeList<long, char, double, int>>,
              "переворот четвёрки");
    });
    run_test("Reverse(Reverse(L)) == L", [] {
        using L = TypeList<int, double, char, float>;
        check(std::is_same_v<ReverseT<ReverseT<L>>, L>,
              "двойной переворот возвращает исходный список");
    });
}

// =============================================================================
// Точка входа
// =============================================================================

int main() {
    test_pow();
    test_is_reference();
    test_remove_const();
    test_type_at();
    test_concat();
    test_reverse();

    std::cout << "\n" << (g_total - g_failed) << "/" << g_total << " тестов прошло\n";
    return g_failed == 0 ? 0 : 1;
}
