//
// Created by adygha on 11/20/17.
//

//Выберите типы с которым следующий static_assert не вызовет ошибку компиляции.

#include <assert.h>
#include <iostream>
#include <vector>

template <class T>
void some() {
    static_assert(std::is_arithmetic<T>::value ||
                  (std::is_pointer<T>::value &&
                   std::is_class<typename std::remove_pointer<T>::type>::value), "T can not be used here");
}

int main(){
    some<int>(); //+ is_arithmetic
//    some<int*>(); //- !is_arithmetic || (is_pointer && !is_class<remove_pointer>)
//    some<std::vector<int>>();- //!is_arithmetic || (!is_pointer && !is_class<remove_pointer>)
//    some<std::vector<int*>>();- //!is_arithmetic || (!is_pointer && !is_class<remove_pointer>)
//    some<std::string>(); //- !is_arithmetic || (!is_pointer && !is_class<remove_pointer>)
    some<std::string*>(); //+ !is_arithmetic || (is_pointer && is_class<remove_pointer>)
    return 0;
}