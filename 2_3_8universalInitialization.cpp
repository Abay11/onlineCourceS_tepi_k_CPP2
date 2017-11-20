//
// Created by adygha on 11/4/17.
//

struct cStyleStruct{
    int x;
    double y;
};

struct cppStyleStruct{
    cppStyleStruct(int x, double y): x(x), y(y) {}
    int x;
    double y;
};

// C++03
cStyleStruct s1 = {19, 37.0}; //инициализация
cppStyleStruct s2(19, 37.0);  //вызов конструктора

// C++11
cStyleStruct s3{19, 37.0}; //инициализация
cppStyleStruct s4{19, 37.0}; //вызов конструктор

//тип не обязателен
cStyleStruct getValue(){ return {6, 0.37}; }


