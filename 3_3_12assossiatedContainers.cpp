//
// Created by adygha on 11/14/17.
//

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <functional>


// базовый класс фигуры (полиморфный)
struct Shape {
    virtual ~Shape() {}
};

// прямоугольник
struct Rectangle : Shape {};

// треугольник
struct Triangle : Shape {};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b){
    std::cout << "R x R\n"; return true;
};

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b){
    std::cout << "R x T\n"; return true;
};



// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    std::multimap<std::type_index, std::pair<std::type_index,
            std::function<Result(Base*, Base*)>> > types;
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    void addImpl(const std::type_info &t1,
                 const std::type_info &t2,
                 std::function<Result(Base*, Base*)> f)
    {
        auto internal_pair = std::pair<std::type_index, std::function<Result(Base*, Base*)>>(t2, f);
        auto external_pair = std::pair<std::type_index,
                std::pair<std::type_index, std::function<Result(Base*, Base*)>>>(t1, internal_pair);
        types.insert(external_pair);
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно
        // проверить есть ли реализация для b и а
        auto iter = types.find(typeid(*a));
        auto iter2 = types.find(typeid(*b));

        if (iter != types.end()) {
            auto iter_lower = types.lower_bound(typeid(*a));
            auto iter_upper = types.upper_bound(typeid(*a));

            while (iter_lower != iter_upper) {
                if ((*iter_lower).second.first == typeid(*b)) return true;
                else ++iter_lower;
            }
        }
        if (Commutative) {
            if (iter2 != types.end()) {
                auto iter2_lower = types.lower_bound(typeid(*b));
                auto iter2_upper = types.upper_bound(typeid(*b));

                while (iter2_lower != iter2_upper) {
                    if ((*iter2_lower).second.first == typeid(*a)) return true;
                    else ++iter2_lower;
                }
            }
        }

        return false;
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        auto iter = types.find(typeid(*a));
        auto iter2 = types.find(typeid(*b));

        if(iter != types.end()){
            auto iter_lower = types.lower_bound(typeid(*a));
            auto iter_upper = types.upper_bound(typeid(*a));

            while(iter_lower != iter_upper){
                if ((*iter_lower).second.first == typeid(*b)) return (*iter_lower).second.second(a, b);
                else ++iter_lower;
            }
        }
        if(Commutative) {
            if (iter2 != types.end()) {
                auto iter2_lower = types.lower_bound(typeid(*b));
                auto iter2_upper = types.upper_bound(typeid(*b));

                while (iter2_lower != iter2_upper) {
                    if ((*iter2_lower).second.first == typeid(*a)) return (*iter2_lower).second.second(b, a);
                    else ++iter2_lower;
                }
            }
        }

    }
};

bool test(int a){
    std::cout << "test called\n";
    return (a % 2 == 0);
}
int main(){
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
        std::cout << "YES we find function like it\n";
        // вызывается функция is_intersect_r_t(s2, s1)
        bool res = is_intersect.call(s1, s2);
        std::cout << res << std::endl;

        // Замечание: is_intersect_r_t ожидает,
        // что первым аргументом будет прямоугольник
        // а вторым треугольник, а здесь аргументы
        // передаются в обратном порядке.
        // ваша реализация должна самостоятельно
        // об этом позаботиться
    }
    else std::cout << "NO we can't find thas fuction\n";
    return 0;
}
