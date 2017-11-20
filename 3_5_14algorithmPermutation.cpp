//
// Created by adygha on 11/20/17.
//

#include <algorithm>
#include <iostream>
#include <list>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    using value_type = typename std::iterator_traits<Iterator>::value_type;

    if(p == q) return 1;
    size_t count = 0;
    std::vector<value_type> duplicate(p, q);
    std::sort(duplicate.begin(), duplicate.end());
    do
    {
        if(std::adjacent_find(duplicate.begin(), duplicate.end()) == duplicate.end())
            ++count;
    }
    while(std::next_permutation(duplicate.begin(), duplicate.end()));
    return count;
}


int main(){
    std::list<int> cont{1,2,3,4,4};
    std::cout << count_permutations(cont.begin(), cont.end()) << std::endl;
    return 0;
}
