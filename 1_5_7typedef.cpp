//
// Created by adygha on 10/30/17.
//

//При помощи typedef определите тип ComplexFunction, который является указателем на функцию,
//которая принимает int и указатель на функцию, принимающую double и возвращающую int,
//и возвращает указатель на функцию, которая принимает char const * и возвращает int *.

#include <iostream>

typedef int* (*f_return)(char const*);
typedef int (*f_param)(double);
typedef f_return (*ComplexFunction)(int, f_param);



int main(){
    return 0;
}