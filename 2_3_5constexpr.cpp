//
// Created by adygha on 11/3/17.
//

//Напишите constexpr бинарные операторы +, - и * (скалярное произведение) для структуры Point.
//Пример использования:
//
//constexpr size_t size = static_cast<size_t>(Point(2,4) * Point(4,3));
//int m[size]; // массив из 20 элементов


#include <iostream>

// определение структуры Point уже подключено
struct Point{
    constexpr Point(double x, double y)
        : x(x), y(y)
    {}

    constexpr operator double(){
        return x + y; //оператор приведения я примерно сообразил,
                        // не уверен так - не так, чисто что б код запускался
    }

    double x = 0;
    double y = 0;
};

// сложение
constexpr Point operator+(const Point &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}


//// вычитание
constexpr Point operator-(const Point &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}
//
//// скалярное произведение
constexpr double operator*(const Point &a, const Point &b){
    return a.x * b.x + a.y * b.y;
}

int main(){
    constexpr size_t size = static_cast<size_t >(Point(2,4) + Point(4,3));
    std::cout << size;
    return 0;
}