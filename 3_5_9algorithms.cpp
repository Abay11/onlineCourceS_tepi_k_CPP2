//
// Created by adygha on 11/19/17.
//

//Напишите алгоритм remove_nth, который удаляет элемент из последовательности по номеру этого элемента.
//
//Пример:

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    if(p == q) return q;
    size_t i = -1;
    FwdIt iter = p, prev_iter;
    for (; iter != q; ++iter)
    {
        ++i;
        if(i >= n && std::next(iter) != q)
            std::iter_swap(iter, std::next(iter));
        prev_iter = iter;
    }

    if(i >= n)return prev_iter;
    return q;
}

int main(){

    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
    std::vector<int> res = {0,1,2,3,4,6,7,8,9,10};
    (v == res) ? std::cout << "1. True\n" : std::cout << "1. False\n";

    std::vector<int> v2 = {0,1,2};
    v2.erase(remove_nth(v2.begin(), v2.end(), 5), v2.end());
    std::vector<int> res2 = {0,1,2};
    (v2 == res2) ? std::cout << "2. True\n" : std::cout << "2. False\n";

    std::vector<int> v3 = {0,1};
    v3.erase(remove_nth(v3.begin(), v3.end(), 1), v3.end());
    std::vector<int> res3 = {0};
    (v3 == res3) ? std::cout << "3. True\n" : std::cout << "3. False\n";

    std::vector<int> v4 = {0,1};
    v4.erase(remove_nth(v4.begin(), v4.end(), 0), v4.end());
    std::vector<int> res4 = {1};
    (v4 == res4) ? std::cout << "4. True\n" : std::cout << "4. False\n";

    std::vector<int> v5 = {0};
    v5.erase(remove_nth(v5.begin(), v5.end(), 0), v5.end());
    std::vector<int> res5 = {};
    (v5 == res5) ? std::cout << "5. True\n" : std::cout << "5. False\n";

    std::vector<int> v6 = {};
    v6.erase(remove_nth(v6.begin(), v6.end(), 0), v6.end());
    std::vector<int> res6 = {};
    (v6 == res6) ? std::cout << "6. True\n" : std::cout << "6. False\n";


    return 0;
}