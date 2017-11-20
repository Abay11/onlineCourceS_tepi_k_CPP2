//
// Created by adygha on 10/28/17.
//

//Предположим, что вам даётся два указателя
// на объект некоторого сложного полиморфного класса,
// который использует множественное наследование.
// Оба указателя имеют один и тот же тип, но могут с
// сылаться на разные однотипные базы внутри одного объекта.
//
//Напишите шаблонную функцию, которая по двум однотипным
// указателям проверяет, указывают ли они на один объект.

#include <iostream>

struct Unit{
    virtual ~Unit(){}
};

struct Elf : Unit{};

struct Archer : Unit{};

struct ElfArcher : Elf, Archer{};

template <class T>
bool isSameObjects(T const *p, T const *q) {
    return (dynamic_cast<const void*>(p)) == (dynamic_cast<const void*>(q));
}

int main(){
    ElfArcher a, b;
    Unit *ue = (Unit*)(Elf*)&a;
    Unit *ua = (Unit*)(Archer*)&a;
    std::cout << isSameObjects(ue, ua);

}