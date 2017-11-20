//
// Created by adygha on 10/28/17.
//
//
//В первой части курса была следующая задача.
//Вам требуется реализовать функцию,
// которая принимает на вход два указателя
// на базовый класс Expression, и возвращает true,
// если оба указателя указывают
// на самом деле на объекты одного
// и того же класса, и false
// в противном случае (т.е. если оба
// указателя указывают на BinaryOperation,
// то возвращается true, а если один
// из них указывает на Number,
// а второй на BinaryOperation, то false).
//
//Реализуйте её при помощи typeid.
//Требования к реализации: Использовать dynamic_cast
//и вызывать методы по переданным указателям запрещено.


#include <iostream>
#include <typeinfo>

struct Expression{
    virtual ~Expression(){};
};

struct Left : Expression{};
struct Right : Expression{};

bool check_equals(Expression *left, Expression *right){
    return (typeid(*left) == typeid(*right));
}

int main(){
    Left l; Right r;

    std::cout << check_equals(&l, &r);
    return 0;
}