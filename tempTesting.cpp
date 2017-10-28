//
// Created by adygha on 10/27/17.
//

#include <iostream>


int main(){
    int const i = 1;

    int *p = 0;
//    p = &i; //error int const* -> int*
    int const** pp = const_cast<int const**>(&p);

    *pp = &i; // it's equal p = &i;

    *p = 2;

    std::cout << i << " ";
    std::cout << *p << std::endl;
    std::cout << (*pp == p) << std::endl;

    return 0;
}