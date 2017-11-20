//
// Created by adygha on 11/1/17.
//

//Дополните класс Array перемещающим конструктором и перемещающим оператором присваивания.
//
//Замечание: все объявленные методы класса Array уже реализованы.

#include <iostream>
#include <utility>

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(size_t size = 0, int begin = 0) : size_(size), data_(new T[size_]){
        for (int i = 0; i < size_; ++i) {
            data_[i] = begin++;
        }
    }
    Array(Array const& a) : size_(a.size()), data_(new T[size_]){
        for (int i = 0; i < size_; ++i) {
            data_[i] = a[i];
        }
    }
    Array & operator=(Array const& a){
        size_ = a.size();
        delete[] data_;
        data_ = new T[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = a[i];
        }
        return *this;
    };
    ~Array(){
        if(data_ != nullptr)
            delete[] data_;
    };

    size_t size() const{
        return size_;
    };
    T& operator[](size_t i){
        return const_cast<T&>(
            const_cast<Array const&>(*this) [i]);
    };
    const T& operator[](size_t i) const{
        return data_[i];
    };

    void swap(Array &other){
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    // реализуйте перемещающий конструктор
    Array(Array &&other) : data_(nullptr), size_(0){ //перед тем как обменять данные, нужно проиниц-ть текущий объект
        swap(other);
    }

    // реализуйте перемещающий оператор присваивания
    Array& operator= (Array &&other){
        swap(other);
        return *this;
    }

private:
    size_t  size_;
    T *     data_;
};


int main(){
    Array<int> a(3, 10);
    Array<int> b;
    b = std::move(a);
    Array<int> c(3, 30);
    a = std::move(c);

    for (int i = 0; i < b.size(); ++i) {
        std::cout << b[i] << " " ;
    }
    std::cout << std::endl;
    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " " ;
    }
    std::cout << std::endl;
    for (int i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " " ;
    }

    return 0;
}
