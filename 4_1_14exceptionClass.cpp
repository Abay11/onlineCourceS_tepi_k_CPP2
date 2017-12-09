//
// Created by adygha on 11/20/17.
//

#include <string>
#include <sstream>
#include <iostream>


// описание класса исключения bad_from_string
class bad_from_string : public std::exception
{
    std::string info;
public:
    bad_from_string(std::string e ="from_string except") : info(e){}
    const char* what() const noexcept{
        return info.c_str();
    }
};

// функция from_string
template<class T>
T from_string(std::string const& s)
{

    std::istringstream is(s);
    T t; std::string temp;
    is >> std::noskipws >> t;
    if(!temp.empty())
        throw bad_from_string("conversion error");
    return t;
        /*std::istringstream is(s);
        T t;
        is >> std::noskipws >> t;
        if (is.fail()) //Returns true if an error has occurred on the associated stream.
            throw bad_from_string("conversion error");
        is.get(); //Reads one character and returns it if available. Otherwise, returns Traits::eof() and sets failbit and eofbit.
        if(is.good()) //Returns true if the the most recent I/O operation on the stream completed successfully.
            throw bad_from_string("conversion error");
        return t;*/
}
using std::string;
int main()
{
    string s1("123");
//    int    a1 = from_string<int>   (s1); // a1 = 123
//    double b1 = from_string<double>(s1); // b1 = 123.0
//    string c1 = from_string<string>(s1); // c1 = "123"
//
//    string s2("12.3");
//    int    a2 = from_string<int>   (s2); // исключение
//    double b2 = from_string<double>(s2); // b2 = 12.3
//    string c2 = from_string<string>(s2); // c2 = "12.3"

//    string s3("a a");
//    int    a3 = from_string<int>   (s3); // исключение
//    double b3 = from_string<double>(s3); // исключение
//    char c3 = from_string<char>(s3); // c3 = "abc"
//    std::cout << c3;

    char a, c, b; std::string temp, temp2;
    std::cin >> std::noskipws >>temp>>temp2;
    std::cout << temp << temp2;


    return 0;
}