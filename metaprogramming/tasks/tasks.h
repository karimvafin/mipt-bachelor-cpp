#pragma once

#include <cstddef>
#include <stdexcept>
#include <type_traits>

// =============================================================================
// Задания по метапрограммированию (metaprogramming-1)
// Реализуйте все шаблоны ниже — замените заглушки на правильные реализации.
// Все шаблоны реализуются прямо в этом заголовочном файле.
//
// Подсказка: проверять корректность можно ещё во время компиляции через
// static_assert(...). Тесты в tests.cpp выполняются в runtime, но используют
// constexpr-значения и std::is_same_v.
// =============================================================================

// -----------------------------------------------------------------------------
// Задание 1: Pow<Base, Exp> (0.5 баллов)
//
// Compile-time возведение целого числа в степень.
// Реализуйте шаблонную структуру Pow с двумя нетиповыми параметрами:
// Pow<Base, Exp>::value должно быть равно Base в степени Exp.
//
// База рекурсии: Pow<Base, 0>::value == 1.
// Шаг рекурсии: Pow<Base, Exp>::value == Base * Pow<Base, Exp - 1>::value.
//
// Используйте static constexpr int value и частичную (или полную)
// специализацию для базы рекурсии.
//
// Пример: Pow<2, 10>::value == 1024
// Пример: Pow<3, 4>::value  == 81
// Пример: Pow<5, 0>::value  == 1
// Пример: Pow<-2, 3>::value == -8
// -----------------------------------------------------------------------------
template <int Base, unsigned Exp>
struct Pow {
    static constexpr int value = Base * Pow<Base, Exp - 1>::value;  
};

template <int Base>
struct Pow<Base, 0> {
    static constexpr int value = 1;
};

// -----------------------------------------------------------------------------
// Задание 2: IsReference<T> (0.5 баллов)
//
// Реализуйте type trait, который определяет, является ли тип ссылкой
// (lvalue T& или rvalue T&&). Аналог std::is_reference.
//
// Базовый шаблон должен давать value == false. Добавьте две частичные
// специализации: для T& и для T&&.
//
// Не используйте std::is_reference внутри реализации — нужно написать самим.
//
// Пример: IsReference<int>::value          == false
// Пример: IsReference<int*>::value         == false
// Пример: IsReference<int&>::value         == true
// Пример: IsReference<int&&>::value        == true
// Пример: IsReference<const int&>::value   == true
// -----------------------------------------------------------------------------
template <typename T>
struct IsReference {
    static constexpr bool value = false;  // TODO: добавьте специализации
};

template <typename T>
struct IsReference<T&> {
    static constexpr bool value = true;
};

template <typename T>
struct IsReference<T&&> {
    static constexpr bool value = true;
};

// -----------------------------------------------------------------------------
// Задание 3: RemoveConst<T> (1.0 балл)
//
// Реализуйте type transform, который удаляет const с самого верхнего уровня
// типа. Аналог std::remove_const.
//
// Также определите алиас:
//   template <typename T>
//   using RemoveConstT = typename RemoveConst<T>::type;
//
// Внимание: const снимается только с верхнего уровня типа.
//   RemoveConstT<int>            -> int
//   RemoveConstT<const int>      -> int
//   RemoveConstT<int* const>     -> int*           (const на указателе — снимается)
//   RemoveConstT<const int*>     -> const int*     (const на int — НЕ снимается)
//   RemoveConstT<const int&>     -> const int&     (const внутри ссылки — НЕ снимается)
//
// Подсказка: достаточно одной частичной специализации.
// Не используйте std::remove_const внутри реализации.
// -----------------------------------------------------------------------------
template <typename T>
struct RemoveConst {
    using type = T;  
};

template <typename T>
struct RemoveConst<const T> {
    using type = T;
};

template <typename T>
using RemoveConstT = typename RemoveConst<T>::type;

// -----------------------------------------------------------------------------
// TypeList — используется в заданиях 4 и 5.
// -----------------------------------------------------------------------------
template <typename... Ts>
struct TypeList {};

// -----------------------------------------------------------------------------
// Задание 4: TypeAt<N, List> (1.0 балл)
//
// Реализуйте шаблон, который возвращает N-й тип из TypeList.
//
// База рекурсии: TypeAt<0, TypeList<Head, Tail...>>::type == Head.
// Шаг рекурсии: TypeAt<N, TypeList<Head, Tail...>>::type
//             == TypeAt<N - 1, TypeList<Tail...>>::type.
//
// Если N выходит за границы списка, должна возникать ошибка компиляции
// (это обеспечивается автоматически, если нет подходящей специализации).
//
// Также определите алиас:
//   template <std::size_t N, typename List>
//   using TypeAtT = typename TypeAt<N, List>::type;
//
// Пример:
//   using L = TypeList<int, double, char>;
//   TypeAtT<0, L> == int
//   TypeAtT<1, L> == double
//   TypeAtT<2, L> == char
// -----------------------------------------------------------------------------
template <std::size_t N, typename List>
struct TypeAt { 
};

template <std::size_t N, typename Head, typename... Tail>
struct TypeAt<N, TypeList<Head, Tail...>> {   
    using type = typename TypeAt<N - 1, TypeList<Tail...>>::type; 
};

template <typename Head, typename... Tail>
struct TypeAt<0, TypeList<Head, Tail...>> {   
    using type = Head;                      
};

template <std::size_t N, typename List>
using TypeAtT = typename TypeAt<N, List>::type;

// -----------------------------------------------------------------------------
// Задание 5: Concat и Reverse для TypeList (2.0 балла)
//
// (а) Concat<List1, List2>::type — объединение двух TypeList в один.
//
//     Подсказка: специализируйте по двум параметрам-пакам:
//       template <typename... Xs, typename... Ys>
//       struct Concat<TypeList<Xs...>, TypeList<Ys...>> { ... };
//
//     Пример:
//       Concat<TypeList<int, double>, TypeList<char, long>>::type
//         == TypeList<int, double, char, long>
//
// (б) Reverse<List>::type — список в обратном порядке.
//
//     Идея: рекурсивно "снимаем" Head и приклеиваем его в конец Reverse от Tail.
//     Базы рекурсии: Reverse<TypeList<>> -> TypeList<>.
//     Используйте Concat из части (а).
//
//     Пример:
//       Reverse<TypeList<int, double, char>>::type
//         == TypeList<char, double, int>
//
// Также определите алиасы ConcatT и ReverseT.
// -----------------------------------------------------------------------------
template <typename List1, typename List2>
struct Concat {
    using type = TypeList<>;  
};
template <typename... Xs, typename... Ys>
 struct Concat<TypeList<Xs...>, TypeList<Ys...>> { 
    using type = TypeList<Xs..., Ys...>;
  };

template <typename List1, typename List2>
using ConcatT = typename Concat<List1, List2>::type;

template <typename List>
struct Reverse {
    using type = TypeList<>;  
};
template <typename List>
using ReverseT = typename Reverse<List>::type;
template <>
struct Reverse<TypeList<>> {
    using type = TypeList<>;
};
template <typename Head, typename... Tail>
struct Reverse<TypeList<Head, Tail...>> {
    using type = ConcatT<ReverseT<TypeList<Tail...>>,TypeList<Head>>;
};

