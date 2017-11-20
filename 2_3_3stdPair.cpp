//
// Created by adygha on 11/2/17.
//

//Напишите шаблонную функцию to_pair,
// которая принимает произвольный std::tuple и два индекса внутри
// и возвращает std::pair, содержащий элементы
// переданного std::tuple с соответствующими индексами.

//Замечание: реализация должна работать в рамках стандарта C++11.

#include <tuple>
#include <iostream>


//мой вариант
//template <int i, int j, typename ...T>
//auto to_pair(std::tuple<T...> t) -> decltype(std::make_pair(std::get<i>(t), std::get<j>(t))){
//    return std::make_pair(std::get<i>(t), std::get<j>(t));
//}

//вариант преподавателя
template <size_t i, size_t j, class T>
auto to_pair(T const& t) -> decltype(std::make_pair(std::get<i>(t), std::get<j>(t) ) ){
    return std::make_pair(std::get<i>(t), std::get<j>(t));
}

int main(){
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t); //
    std::cout << p.first << " " << p.second;
    return 0;
}

//Пример:
//
//auto t = std::make_tuple(0, 3.5, "Hello");
//std::pair<double, char const *> p = to_pair<1,2>(t);
// p содержит 3.5 и "Hello"