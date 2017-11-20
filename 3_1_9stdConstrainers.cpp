//
// Created by adygha on 11/9/17.
//

//Для последовательности s1,s2,s3,…,sn−1,sns1,s2,s3,…,sn−1,sn будем называть подотрезком подпоследовательность в
// ида si,si+1,si+2,…,sj−2,sj−1si,si+1,si+2,…,sj−2,sj−1 для некоторых ii и jj, i≤ji≤j,
// .е. подотрезок — это непрерывная подпоследовательность.
//
//Напишите функцию max_increasing_len, которая принимает последовательность, хранящуюся в std::list,
// по двум итераторам, и вычисляет для неё длину самого длинного строго возрастающего подотрезка.

//Пример:

//Ограничения: не используйте другие контейнеры, не копируйте элементы из списка.

#include <iostream>
#include <list>

// так как в задании не указан тип элементов,
// которые хранятся в списке, то давайте сделаем
// эту функцию шаблонной
// Параметр It — это тип итератора
template<class It>
size_t max_increasing_len(It p, It q){
    // реализация
    int count = 0, maxCount = 0;
    for(It iter = p, temp; iter != q; ++iter) {
        if (count != 0 && *(--(temp = iter)) < *iter) {
            ++count;
        } else {
            maxCount = count > maxCount ? count : maxCount;
            count = 1;
        }
        /*if (count == 0) {
            count = 1;
        } else if (*(std::prev(iter)) < *iter) {
            ++count;
        } else {
            maxCount = std::max(maxCount, count);
            count = 1;
        }*/
    }
    return maxCount = count > maxCount ? count : maxCount;
}
int main(){
    std::list<int> const l = {3,2,1};
    int len1 = max_increasing_len(l.begin(), l.end());
    if(len1 == 1) std::cout << "1 TRUE" << std::endl;
    else std::cout << "1 FALSE. Ожидается 1, получено " << len1 << std::endl;
//
    std::list<int> const l2 = {7,8,9,4,5,6,1,2,3,4};
    size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 4, соответствует подотрезку 1,2,3,4
    if(len2 == 4) std::cout << "2 TRUE" << std::endl;
    else std::cout << "2 FALSE. Ожидается 4, получено " << len2 << std::endl;
//
    std::list<int> const l3 = {-3,-2,-1,0,0,1,2,3,4,5};
    size_t len3 = max_increasing_len(l3.begin(), l3.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
    if(len3 == 6) std::cout << "3 TRUE" << std::endl;
    else std::cout << "3 FALSE. Ожидается 6, получено " << len3 << std::endl;
//
    std::list<int> const l4 = {1,2,3};
    int len4 = max_increasing_len(l4.begin(), l4.end());
    if(len4 == 3) std::cout << "4 TRUE" << std::endl;
    else std::cout << "4 FALSE. Ожидается 3, получено " << len4 << std::endl;
//
    std::list<int> const l5 = {};
    int len5 = max_increasing_len(l5.begin(), l5.end());
    if(len5 == 0) std::cout << "5 TRUE" << std::endl;
    else std::cout << "5 FALSE. Ожидается 0, получено " << len5 << std::endl;
//
    std::list<int> const l6 = {111, 111, 111, 111, 111,};
    int len6 = max_increasing_len(l6.begin(), l6.end());
    if(len6 == 1) std::cout << "6 TRUE" << std::endl;
    else std::cout << "6 FALSE. Ожидается 1, получено " << len5 << std::endl;

    return 0;
};

