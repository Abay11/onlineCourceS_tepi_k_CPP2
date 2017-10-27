/*Предположим, что при разработке игры вам потребовался юнит "Челмедведокорова" (ManBearCow).
Завершите разработку иерархии классов и реализуйте необходимые конструкторы.
PS: В данном игровом контексте предполагается, что человек — не животное.*/

#include <cstdlib>
#include <iostream>
#include <string>

// этот класс уже определён выше
struct Unit{
    explicit Unit(size_t id):id_(id){}

    size_t id() const { return id_; }
private:
    size_t id_;
};

// базовый класс для животных
struct Animal : virtual Unit{
    // name хранит название животного
    // "bear" для медведя
    // "pig" для свиньи
    Animal(std::string const& name, size_t id):Unit(id),name_(name){}
    // ...
    std::string const& name() const { return name_; }
private:
    std::string name_;
};

// класс для человека
struct Man : virtual Unit{
    explicit Man(size_t id) : Unit(id) {}
    // ...
};

// класс для медведя
struct Bear : Animal{
    explicit Bear(size_t id) : Unit(id), Animal("bear", id){}
    // ...
};

// класс для свиньи
struct Cow : Animal{
    explicit Cow(size_t id) : Unit(id), Animal("cow", id){}
    // ...
};

// класс для челмедведосвина
struct ManBearPig : Man, Bear, Cow{
    ManBearPig(size_t id) : Unit(id), Man(id), Bear(id), Cow(id){}
    // ...
};

int main(){
    ManBearPig *bmp = new ManBearPig(3);
    std::cout << ((Cow*)bmp)->name();
    return 0;
}

