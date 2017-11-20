//
// Created by adygha on 11/4/17.
//

//Рассмотрим следующую функцию for_each.

#include <initializer_list>
#include <iostream>
#include <functional>

template<class F>
void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}




int main(){
    int m[10] = {1,2,3,4,5,6,7,8,9,10};
    for(int x : m)
        std::cout << x << " ";
    std::cout << std::endl;
    // определение переменной
//    auto square_fun = [](int& a){a *= a;};
    std::function<void (int&)> square_fun = [](int& a){a *= a;};
    for_each_int(m, m + 10, square_fun); // теперь m = {1,4,9,16,25,36,49,64,81,100};
    for(int x : m)
        std::cout << x << " ";
    return 0;
}



