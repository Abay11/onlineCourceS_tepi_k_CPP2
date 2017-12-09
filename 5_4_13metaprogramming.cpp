//
// Created by adygha on 12/9/17.
//

//Напишите шаблонную функцию get_size, которая принимает значение некоторого типа,
// у которого есть либо константный метод size() возвращающий size_t,
// либо поле size типа size_t, и возвращает соответствующее значение.

#include <iostream>
#include <type_traits>


struct Struct
{
    Struct(int x = 0){}
    size_t size = 0;
};

/*typedef char YES;
struct NO{YES m[2];};

template <class T>
struct is_size_defined{

    template <class Z , size_t (Z::*)()const = &Z::size>
    struct wrapper{};

    template <class C>
    static YES check(wrapper<C> *p);

    template <class C>
    static NO check(...);

    static bool const value = (sizeof(YES) == sizeof(check<T>(0)));
};*/ // эта красотища оказалась ненужной

//для поля структуры
template <class T, size_t (T::*)() const = &T::size>
size_t get_size(T const &t){
    return t.size();
};

//для константного метода
template <class T, size_t (T::*) = &T::size>
size_t get_size (T const &t){
    return t.size;
};

/*template<class T> //скучное решение
auto get_size(const T& t) -> decltype(t.size){
    return t.size;
}*/

/*template<class T>
auto get_size(const T& t)-> decltype(t.size()){
    return t.size();
}*/

int main(){
    std::string s{"Hello"};
    size_t s_size = get_size(s);   // 5, вызывается метод size()
    std::cout << s_size << std::endl;
    Struct x{10};
    size_t x_size = get_size(x);  // 10, читается поле size
    std::cout << x_size << std::endl;

    return 0;
}