//
// Created by adygha on 12/7/17.
//

//Напишите метафункцию Zip (аналог std::transform), которая принимает два списка целых чисел одинаковой длины, а так же бинарную метафункцию,
// и возвращает список, получившийся в результате поэлементного применения метафункции к соответствующим элементам исходных списков.
#include <iostream>

template <int... Ints>
struct IntList;

template <int H, int ...ints>
struct IntList<H, ints...>
{
    static int const Head = H;
    using Tail = IntList<ints...>;
    static int const Length =  1 + Tail::Length;
};

template <>
struct IntList<>{
    static int const Length = 0;
};

template <int H, typename IL>
struct IntCons;

template <int H, int...ints>
struct IntCons<H, IntList<ints...>>
{
    using type = IntList<H, ints...>;
};

template<typename T> void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<class IL1, class IL2, template<int...>class F> struct Zip{
    using type = typename IntCons< F<IL1::Head, IL2::Head>::value,
    typename Zip< typename IL1::Tail, typename IL2::Tail, F >::type >::type;
};

template<template<int, int> class F> struct Zip<IntList<>, IntList<>, F>{
    using type = IntList<>;
};

//это тоже решение, с использованием variadic templates, но по заданию требуется другая техника
/*template<int...N1, int...N2, template<int...>class F>
struct Zip<IntList<N1...>, IntList<N2...>, F>{
//    using type = IntCons<F<H1, H2>::value, IntList<>>;
    using type = IntList<F<N1, N2>::value...>;

};*/

//template <template<int, int> typename F> struct Zip<IntList<>, IntList<>, F>{};


// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;
};


int main(){
// два списка одной длины
    using L1 = IntList<1,2,3,4,5>;
    using L2 = IntList<1,3,7,7,2>;

// результат применения — список с поэлементными суммами
    using L3 = Zip<L1, L2, Plus>;  // IntList<2, 5, 10, 11, 7>
    check<L3::type>();
    return 0;
}

