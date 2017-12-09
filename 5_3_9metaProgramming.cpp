пишите метафункцию Length для вычисления длины списка IntList.

Пример:

using primes = IntList<2,3,5,7,11,13>;

constexpr size_t len = Length<primes>::value; // 6


#include <iostream>

template <int...>
struct IntList;

template <int H, int...T>
struct IntList<H, T...>{
    static int const Head = H;
    using Tail = IntList<T...>;
};

template <>
struct IntList<>{};


template <typename IntList>
struct Length{
    static int const value = 1 + Length<typename IntList::Tail>::value;
};

template <>
struct Length<IntList<>>{
  static int const value = 0;
};

//// определите метафункцию Length для вычисления длины списка
//template <typename T>
//struct Length;

//template<template<int ...> class IntList, int ...Values>
//struct Length<IntList<Values...>>
//{
//    static const int value = sizeof...(Values);
//};

int main(){
    using primes = IntList<2,3,5,7,11,13>;
    constexpr size_t len = Length<primes>::value; // 6
    std::cout << len << std::endl;
    return 0;
}

