//
// Created by adygha on 10/28/17.
//

#include <iostream>
#include <typeinfo>

struct Unit{
    virtual ~Unit(){} // наличие виртуальных методов необходимо
};

struct Soldier : Unit{};

int main(){
    Soldier s;
    Unit &ur = s;
    Unit *up = &s;

    std::cout << typeid(ur).name() << std::endl; //Soldier
    std::cout << typeid(*up).name() << std::endl; //Soldier
    std::cout << typeid(up).name() << std::endl; //Unit *
    std::cout << typeid(Soldier).name() << std::endl; //Soldier *
    std::cout << (typeid(ur).name() == typeid(Soldier).name()) << std::endl; //1, true


    return 0;
}

