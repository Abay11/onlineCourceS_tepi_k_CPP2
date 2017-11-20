//
// Created by adygha on 11/20/17.
//

#include <vector>
#include <algorithm>
#include <iostream>

struct ElementN
{
    explicit ElementN(size_t n)
            : n(n), i(0)
    {}

    template<class T>
    bool operator()(T const& t) { return (i++ == n); }

    size_t n;
    size_t i;
};

int main()
{
    std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };

    v.erase(std::remove_if(v.begin(), v.end(), ElementN(3)), v.end());

    for (int i: v)
        std::cout << i << ' ';

    return 0;
}

/*0 1 2 4 5 6 8 9 10 11 12*/

/*
Дело в том, что алгоритмы стандартной библиотеки принимают функторы по значению. В данном случае предикат ElementN копируется в функцию remove_if и оттуда передаётся сначала в find_if, а потом в remove_copy_if. В обоих случаях при передачи предиката в алгоритм копируется экземпляр предиката из remove_if (т.е. в обоих случаях i = 0). Поэтому из массива удаляется не только элемент с номером 3 (начиная с нуля), но и элемент с номером 7.

Таким образом, алгоритмы стандартной библиотеки могут неправильно работать с функторами, которые изменяют своё состояние.*/
