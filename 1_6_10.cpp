//
// Created by adygha on 10/31/17.
//

//Напишите возвращающую bool шаблонную функцию compare,
//        которая принимает две константные ссылки на объекты одного типа
//и указатель на константный метод этого типа без параметров,
//который в свою очередь возвращает значение какого-то второго типа.
//Функция должна сравнивать объекты по значениям, которые для них вернёт
//        соответствующий метод, и возвращать true, если значение для первого
//объекта оказалось меньше, чем для второго.

//Пример использования функции compare:


// сравнение строк по длине
//bool r1 = compare(s1, s2, &std::string::size); // true
//bool r2 = compare(s1, s1, &std::string::size); // false



#include <iostream>

template<typename T, typename R>
bool compare(const T &a, const T &b, R (T::*mptr)() const){
    return ( (a.*mptr)() < (b.*mptr)());
}

int main(){
    std::string s1("Elf");
    std::string s2("Archer");
    std::cout << compare(s1, s2, &std::string::size);
    return 0;
}