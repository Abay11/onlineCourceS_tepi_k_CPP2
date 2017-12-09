//
// Created by adygha on 11/23/17.
//
#include <utility>
#include <iostream>
#include <complex>

/*На предыдущем степе в условной спецификации noexcept мы воспользовались тем, что функция swap имеет
 * аргументы нужных нам типов. В тех случаях, когда аргументов нужного типа у функции нет,
 * можно использовать std::declval<T>(), который позволяет "определить" значение типа T в различных контекстах,
 * в т.ч. в noexcept.

 Специфицируйте noexcept для шаблонной функции do_math, если известно, что в её реализации значения типа T копируются,
 присваиваются и складываются при помощи оператора +.
Для простоты будем считать, что перемещающих методов у типа T нет.*/


template <class T>
void do_math()noexcept(std::is_nothrow_copy_constructible<T>()
&& std::is_nothrow_copy_assignable<T>() && noexcept(std::declval<T>() + std::declval<T>())){}

int main(){

    std::cout << std::boolalpha <<  noexcept(do_math<int>()) << std::endl;
    std::cout  <<  noexcept(do_math<std::string>());
    return 0;
}
