//
// Created by adygha on 11/28/17.
//

//Напишите две метафункции для работы c IntList:
//
//        IntCons позволяет увеличить список на один элемент — он добавляется в начало списка.
//Generate позволяет сгенерировать список длины N с числами от 0 до N - 1.
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

template<int H, int K = H>
struct Generate
{
    using type = typename IntCons<K-H, typename Generate<H - 1, K>::type>::type;
};

template<int K>
struct Generate<0, K>
{
    using type = IntList<>;
};

template<typename T> void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main(){
    using l1 = Generate<4>::type;
    check<l1>();
    return 0;
}