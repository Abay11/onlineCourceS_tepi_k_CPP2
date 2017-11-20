//
// Created by adygha on 11/4/17.
//

#include <iostream>
#include <functional>

template<class F>
bool find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        if (f(*p))
            return true;
    return false;
}

//Определите переменную gen_finder, хранящую безымянную функцию,
// которая принимает массив значений типа int через два указателя
//и возвращает безымянную функцию, которая в свою очередь принимает
// значение типа int и проверяет, есть ли это значение в переданном массиве.

//Пример:


// определение переменной
int main(){
    int primes[4] = {1, 3, 4, 2};
    int m[1] = {2};

    auto gen_finder = [](int *begin, int *end) -> std::function<bool(int)>{
        return [begin, end](int x) -> bool{
            int *t = begin;
            for(; t != end; ++t){
                if(*t == x)
                    return true;
            }
            return false;
        };
    };

    /*auto gen_finder = [](int *b, int *e){
        return [b, e](int x) -> bool{
            int *t = b;
            for(; t != e; ++t){
                if(*t == x)
                    return true;
            }
            return false;
        };
    };*/
    // has_primes будет истиной, т.к. в m есть число 7
    bool has_primes = find_if(m, m + 1, gen_finder(primes, primes + 4));
    std::cout << has_primes << std::endl;
    return 0;
}
