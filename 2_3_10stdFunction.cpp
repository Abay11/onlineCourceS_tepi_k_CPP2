//
// Created by adygha on 11/4/17.
//

#include <functional>

/*std::function - универсальный класс для хранения указателей на функции,
указателей на методы и функциональных объектов(объекты с перегруженным оператором
круглые скобки)*/

namespace sdtFunctionTesting{
    int mult(int x, int y) { return x * y; }

    struct IntDiv {
        int operator()(int x, int y) const {
            return x / y;
        }
    };

    char OP = '*';

    void some() {
        std::function<int(int, int)> op;
        if (OP == '*')
            op = &mult;
        else if (OP == '/')
            op = IntDiv();
        int result = op(7, 8);
    }
    //также позволяет работать и с указателями на методы
}


//теперь собственно лямбда
//позволяют упростить создание функциональных объектов
//вместо создания отдельного функционального объекта(кажется это отдельная структура с перегруж () )
namespace lymbda{
//состоит из квадратных скобок, дальше список формальных параметров
    std::function<int(int, int)> op = [](int x, int y) { return x / y; }; //подобие IntDiv

//можно указать также и возвращаемое значение, аналогично новому синтаксу объявления функции в новом стандр
    std::function<int (int, int)> op2 = [](int x, int y) -> int { return x / y; };

    //C++14
    std::function <int (int, int)> op3 = [](auto x, auto y){return x / y; };

    //можно захватывать локальные переменные

    //захват по ссылке
    int total = 0;
    auto addToTotal = [&total](int x){ total += x;};

    //захват по значению
    auto subTotal = [total](int x){ x -= total; };

    //можно захватывать this(которая на самом деле тоже локальная переменная,
    //неявно передаваемая как первый параметр в методах класса
    struct Some {
        void someMethod() {
            auto callUpdate = [this]() { this->update(); };
        }
        void update(){}
    };
}
