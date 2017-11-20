//
// Created by adygha on 11/1/17.
//

#include <iostream>

// в шаблонной функции мы не знаем заранее, какой тип нужно возвращать
//template <typename A, typename B>
//RETURN_TYPE Plus(A a, B b){ return a + b; };

//template <typename A, typename B>
//decltype(a + b) Plus(A a, B b){ return a + b;};
//в таком способе, a & b встречаются раньше,
//перед их объявлением, и компилятор выдаст ошибку

//С++11
//template <typename A, typename B>
//auto Plus(A a, B b) -> decltype(a + b){
//    return a + b;
//};

//C++14
template <typename A, typename B>
auto Plus(A a, B b){
    return a + b;
};
//В новом стандарте теперь можно вообще
//опустить decltype
//или же вместо auto исползовать decltype(auto)
//и иметь те же премущества decltype перед auto



int main(){
    std::cout << Plus(1.0d, 3.4f);
    return 0;
}

