#include <iostream>

struct Base{
    int value;
    Base(int v):value(v){}
};

struct D1:Base{
    D1(int v):Base(v){}
};

struct D2:Base{
    D2(int v):Base(v){}
};

struct D3:D1,D2{
    D3(int d1, int d2):D1(d1),D2(d2){}
};

// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответствующий D2
Base const* D1BaseToD2Base( Base const *base )
{
    /*D1 *d1 = (D1*)base;
    D3 *d3 = (D3*)d1;
    D2 *d2 = d3;
    base = d2;
    return base;*/
    return (Base*)(D2*)(D3*)(D1*)base;
}

int main() {
    D3 d3(1,2);
    D1 *d1 = &d3;
    Base const *b = d1;
    std::cout << b->value << std::endl;
    b = D1BaseToD2Base(b);
    std::cout << b->value;
    return 0;
}