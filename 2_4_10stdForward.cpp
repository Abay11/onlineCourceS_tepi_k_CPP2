//
// Created by adygha on 11/9/17.
//
//Напишите функцию apply, которая принимает некоторую функцию / функциональный объект,
//        а так же аргументы для вызова этого объекта, и вызывает его, используя perfect forwarding.
//Пример:

/*
auto fun = [](std::string a, std::string const& b) { return a += b; };

std::string s("world!");

// s передаётся по lvalue ссылке,
// а временный объект по rvalue ссылке
s = apply(fun, std::string("Hello, "), s);*/

//Примечание: гарантируется, что количество аргументов, переданных в apply, совпадает с количеством
//аргументов у функции/функционального объекта. При этом у функции может быть произвольное число аргументов.

//Hint: ﻿в данном задании нужно использовать новый синтаксис определения функций.

#include <iostream>
#include <functional>

template <class F, class ...Args>
auto apply(F f, Args&& ...args) -> decltype(f(std::forward<Args>(args)...)){
    return f(std::forward<Args>(args)...);
}

int main(){
    std::cout << apply([](int i, int j)->int{return i + j;}, 3, 4);
    auto fun = [](std::string a, std::string const& b) { return a += b; };

    std::string s("world!");

    // s передаётся по lvalue ссылке,
    // а временный объект по rvalue ссылке
//    s = apply(fun, std::string("Hello, "), s);
//    std::cout << s;
    return 0;
}