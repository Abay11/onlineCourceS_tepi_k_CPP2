//
// Created by adygha on 12/7/17.
//

//Воспользуйтесь IntList и метафункцией Generate для того, чтобы научиться "раскрывать" кортежи.
//От вас потребуется написать функцию apply, которая принимает функтор и кортеж с аргументами для вызова этого функтора и вызывает функтор от этих аргументов.
//
//Пример:
//auto f = [](int x, double y, double z) { return x + y + z; };
//auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
//auto res = apply(f, t);                // res = 36.6
//
//Указание: в решении этой задачи вам потребуется воспользоваться оператором "...", который позволяет раскрывать параметры в шаблонах с переменным числом аргументов. Пример использования этого оператора можно посмотреть в уроке про perfect forwarding.

#include <iostream>
#include <tuple>
#include <typeinfo>

template <int... Ints> struct IntList;

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



template <class F, typename...Args, int...indicies>
auto apply_(F f, std::tuple<Args...> t, IntList<indicies...>) -> decltype(f(std::get<indicies>(t)...)){
    return f(std::get<indicies>(t)...);
};


template <class F, typename...Args>
auto apply(F f,  std::tuple<Args...>t) -> decltype(apply_(f, t, typename Generate<(sizeof...(Args))>::type())){
    return apply_(f, t, typename Generate<(sizeof...(Args))>::type());
}


int main(){
    auto f = [](int x, double y, double z)->double{return x + y + z;};
    auto t = std::make_tuple(30, 5.0, 1.6);
    auto res = apply(f, t);
    std::cout << res << std::endl;
    return 0;
}