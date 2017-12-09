//
// Created by adygha on 11/24/17.
//
#include <iostream>
#include <future>
#include <list>
#include <vector>
#include <string.h>
#include <algorithm>

template <class It, class F1, class F2>
auto map_reduce1 (It p, It q, F1 f1, F2 f2, size_t num = 1) -> decltype(f2(f1(*p), f1(*p))) {
    auto res = f1(*p);
    while (++p != q)
        res = f2(res, f1(*p));
    return res;
}

// реализация функции mapreduce
template <class It, class F1, class F2>
auto do_async(It prev, It next, F1 f1, F2 f2) -> decltype(f2(f1(*prev), f1(*prev))){
    It iter = prev;
    auto res = f1(*iter);
    while (++iter != next) {
        res = f2(res, f1(*iter));
    }
    return res;
}

template <class It, class F1, class F2>
auto map_reduce (It p, It q, F1 f1, F2 f2, size_t num) -> decltype(f2(f1(*p), f1(*p))){
    int dist = std::distance(p, q) / num;
    std::vector<std::future<decltype(f2(f1(*p), f1(*p)))>> futures;
    It next = p, prev;
    for (int i = 0; i < num - 1; ++i) {
        prev = next;
        std::advance(next, dist);
        futures.push_back(std::async(std::launch::async, do_async<It, F1, F2>, prev, next, f1, f2));
    }
    futures.push_back(std::async(std::launch::async, do_async<It, F1, F2>, next, q, f1, f2));
    decltype(f2(f1(*p), f1(*p))) res = (*futures.begin()).get();

    for(auto item = std::next(futures.begin()); item != futures.end(); ++item)
        res = f2(res, (*item).get());
    return res;
}


int main(){
   /* std::vector<std::string> v{"1", "2", "3", "4", "5", "6"};
    auto res = map_reduce(v.begin(), v.end(),
                          [](std::string s)->std::string{return s;},
                          [](std::string s, std::string s2)->std::string{return s + ", " + s2;}, 3);
    std::cout << res << std::endl;

    auto res1 = map_reduce1(v.begin(), v.end(),
                          [](std::string s)->std::string{return s;},
                          [](std::string s, std::string s2)->std::string{return s + ", " + s2;}, 3);
    std::cout << res1 << std::endl;*/


    std::list<int> l = {1,2,3,4};

    // параллельное суммирование в 3 потока
    int sum = map_reduce(l.begin(), l.end(), [](int i) -> int{return i + 3;}, std::plus<int>(), 3);
    int sum1 = map_reduce1(l.begin(), l.end(), [](int i) -> int{return i + 3;}, std::plus<int>(), 2);
    std::cout << "1. " << std::boolalpha << (sum == sum1) << std::endl;

    std::cout << sum << " " << sum1 << std::endl;

    // проверка наличия чётных чисел в четыре потока
    auto has_even = map_reduce(l.begin(), l.end(), [](int i){return i % 2 == 0;}, std::logical_or<bool>(), 4);
    auto has_even1 = map_reduce1(l.begin(), l.end(), [](int i){return i % 2 == 0;}, std::logical_or<bool>(), 4);
    std::cout << "2. " << std::boolalpha << (has_even == has_even1) << std::endl;


    std::list<std::string> s = {"1", "2", "3", "4", "5", "6"};
    auto stringCon = map_reduce(s.begin(), s.end(), [](std::string s){return s + " ";}, std::plus<std::string>(), 3);
    auto stringCon1 = map_reduce1(s.begin(), s.end(), [](std::string s){return s + " ";}, std::plus<std::string>(), 3);
    std::cout << "3. " << std::boolalpha << (stringCon == stringCon1) << std::endl;

    std::vector<double> d{4.0, 5.11, 6.11, 0, 5.44, 3.11};
    auto doubleTest = map_reduce(d.begin(), d.end(), [](double d)->int{return (int)d;}, [](int a, int b){return std::max(a, b);}, 3);
    auto doubleTest1 = map_reduce1(d.begin(), d.end(), [](double d)->int{return (int)d;}, [](int a, int b){return std::max(a, b);}, 3);
    std::cout << "4. " << std::boolalpha << (doubleTest == doubleTest1) << std::endl;
    std::cout << doubleTest << " " << doubleTest1 << std::endl;

    return 0;
}
