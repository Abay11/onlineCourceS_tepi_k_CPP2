//
// Created by adygha on 12/9/17.
//

//Определите класс Quantity, которые хранит вещественное число и его размерность в системе СИ
// (размерность хранится как список IntList длины 7).
// Для этого класса нужно определить операторы сложения, вычитания, умножения и деления.

/*Пример:
        template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

..


Требования к Quantity:
        Конструктор по умолчанию и explicit конструктор от double.
Метод value(), который возвращает значение типа double.
Можно складывать только величины одной размерности.
При умножении (делении) соответствующие размерности поэлементно складываются (вычитаются).
Нужно реализовать умножение и деление на число типа double.
Указание: для упрощения в данном задании достаточно реализовать только бинарные арифметические операторы.
  Гарантируется, что все списки, которые будут передаваться в Quantity имеют одинаковую длину.*/

#include <iostream>

template <int... Ints>
struct IntList;

template <int H, int ...ints>
struct IntList<H, ints...>
{
    static int const Head = H;
    using Tail = IntList<ints...>;
    static int const Length =  1 + Tail::Length;
};

template <>
struct IntList<>{
    static int const Length = 0;
};

template <int H, typename IL>
struct IntCons;

template <int H, int...ints>
struct IntCons<H, IntList<ints...>>
{
    using type = IntList<H, ints...>;
};

template<typename T> void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<class IL1, class IL2, template<int...>class F> struct Zip{
    using type = typename IntCons< F<IL1::Head, IL2::Head>::value,
            typename Zip<typename IL1::Tail, typename IL2::Tail, F>::type >::type;
};

template<template<int, int> class F> struct Zip<IntList<>, IntList<>, F>{
    using type = IntList<>;
};

/*template <typename IntList> struct Length{
        static int const value = 1 + Length<typename IntList::Tail>::value;
};

template<> struct Length<IntList<>>{
    static int const value = 0;
};*/

template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

template <typename IntList = IntList<>> void printList(){
    std::cout << IntList::Head << " ";
    printList<typename IntList::Tail>();
}

template <> void printList<IntList<>>(){
    std::cout << "\n";
}

template <int a, int b> struct Plus{
    static int const value = a + b;
};

template <int a, int b> struct Minus{
    static int const value = a - b;
};

template <typename Dimension> struct Quantity;

using NumberQ   = Quantity<Dimension<>>;          // число без размерности
using LengthQ   = Quantity<Dimension<1>>;          // метры
using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

// реализация класса Quantity
template <typename Dimension> struct Quantity{
    double value_;
    using type = Dimension;
//    Конструктор по умолчанию и explicit конструктор от double.
    Quantity(){}
    explicit Quantity(double d):value_(d){}

//    Метод value(), который возвращает значение типа double.
    double value()const{ return value_;}

//    Можно складывать только величины одной размерности.
    Quantity<Dimension> operator+(const Quantity<Dimension> &other){
        return Quantity<Dimension>(value_ + other.value());
    }
    Quantity<Dimension> operator-(const Quantity<Dimension> &other){
        return Quantity<Dimension>(value_ - other.value());
    }

//    При умножении (делении) соответствующие размерности поэлементно складываются (вычитаются).

    template <typename D>
    auto operator*(const Quantity<D>& other) -> decltype(Quantity<typename Zip<type, D, Plus>::type>()){
        using dimensionRes = typename Zip<type, D, Plus>::type;
        double doubleRes = value_ * other.value();
        return Quantity<dimensionRes>(doubleRes);
    };

    template <typename D>
    auto operator/(const Quantity<D>& other) -> decltype(Quantity<typename Zip<type, D, Minus>::type>()){
       using dimensionRes = typename Zip<type, D, Minus>::type;
        double doubleRes = value_ / other.value();
        return Quantity<dimensionRes>(doubleRes);
    }


    void printList(){
        ::printList<Dimension>();
    }
};

//    Нужно реализовать умножение и деление на число типа double.
template<typename D>
auto operator*(Quantity<D> q, double d) -> decltype(q * Quantity<Dimension<>>(d)){
    Quantity<Dimension<>>temp (d);
    return q * temp;
}

template<typename D>
auto operator*(double d, Quantity<D> const& q) -> decltype(q * d){
    return q * d;
}

template<typename D>
auto operator/(Quantity<D> q, double d) -> decltype(q / Quantity<Dimension<>>(d)){
    Quantity<Dimension<>>temp (d);
    return q / temp;
}

template<typename D>
auto operator/(double d, Quantity<D> const& q) -> decltype(Quantity<Dimension<>>(d)/q){
    Quantity<Dimension<>>temp (d);
    return temp / q;
}

int main()
{
    // IntList и Zip уже реализованы
    // шаблон Dimension из условия уже определён

    LengthQ   l{30000};      // 30 км

    TimeQ     t{10 * 60};    // 10 минут

//    l.printList();
// вычисление скорости
    VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с
    VelocityQ v2{30};     // результат типа VelocityQ, 50 м/с
    auto v3 = v + v2;
//    std::cout << v3.value();

    AccelQ    a{9.8};        // ускорение свободного падения
    MassQ     m{80};         // 80 кг
    auto temp = 240 / m;

    std::cout << temp.value() << "\n";
//    temp.printList();
//    m.printList();
//    3.0 * m;
// сила притяжения, которая действует на тело массой 80 кг
//    ForceQ    f = m * a;     // результат типа ForceQ
//    f.printList();
//    std::cout << f.value();
    return 0;
}