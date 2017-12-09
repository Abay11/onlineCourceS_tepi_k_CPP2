//
// Created by adygha on 11/23/17.
//

#include <iostream>
#include <utility>

//Решите предыдущую задачу в предположении, что у класса T могут быть перемещающие методы.

template <class T>
void do_math()noexcept(std::is_nothrow_copy_constructible<T>()
                       && std::is_nothrow_copy_assignable<T>()
                       && noexcept(std::declval<T>() + std::declval<T>())
                       && std::is_nothrow_move_assignable<T>()
                       && std::is_nothrow_move_constructible<T>()){}

int main(){

    std::cout << std::boolalpha <<  noexcept(do_math<int>()) << std::endl;
    std::cout  <<  noexcept(do_math<std::string>());
    return 0;
}
