//Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи.
//Напоминаю, что последовательность Фибоначчи определяется следующим образом:
//Fib(0)=0Fib(0)=0
//Fib(1)=1Fib(1)=1
//Fib(N)=Fib(N−1)+Fib(N−2)Fib(N)=Fib(N−1)+Fib(N−2)

//Пример:﻿
//std::cout << Fib<10>::value;     // 55

template <size_t N>
struct Fib{
    static size_t const value = Fib<N - 1>::value + Fib<N - 2>::value;
};
template <>
struct Fib<1>{
    static size_t const value = 1;
};
template <>
struct Fib<0>{
    static size_t const value = 0;
};
