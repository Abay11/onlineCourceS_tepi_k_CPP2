//
// Created by adygha on 11/4/17.
//

#include <iostream>


int main(){
    u8"kalsfjklsajdf"; //char[]
    u"UTF-16"; //char16_t[]
    U"UTF-32"; //char32_t[]
    L"wide-char"; //wchar_t[]

    u8"unicode character: \u2018.";
    u"bigger unicode character: \u2018.";
    U"unicode character: \u00002018.";

    R"(The String Data \ Stuff " )";
    std::cout << R"delimiter(The String Data \ Stuff ")delimiter" << std::endl;

    std::cout << LR"(Raw wide string literal \t (without a tab))";
    u8R"XXX(I'm a "raw UTF-8 string.)XXX";
    uR"*(This is a "raw UTF-16" string.)*";
    std::cout << (UR"(This is a raw UTF-32" srting.)");



    //std::cout << *str;
    return 0;
}