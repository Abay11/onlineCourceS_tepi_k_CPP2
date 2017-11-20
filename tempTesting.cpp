#include <vector>
#include <list>
#include <iostream>


template <typename T>
class VectorList;

template <typename T>
class VectorListIter : std::iterator<std::bidirectional_iterator_tag, VectorList<T>>
{
    friend class VectorList<T>;
    typedef typename std::vector<T>* vectorPtr;
    typedef typename std::vector<T>::iterator vectorIterator;
    typedef typename std::list<std::vector<T>>* listPtr;
    typedef typename std::list<std::vector<T>>::iterator listIterator;
private:
    T* data_;
    vectorPtr vPtr_;
    vectorIterator vIter_;
    listPtr lPtr_;
    listIterator lIter_;
//    VectorListIter(T* value, vectorPtr* vPtr, vectorIterator vIter, listIterator lIter):data_(value), vPtr_(vPtr), vIter_(vIter), lIter_(lIter){}
    VectorListIter(vectorPtr vPtr, vectorIterator vIter, listPtr lPtr, listIterator lIter)
            :vPtr_(vPtr), vIter_(vIter), lPtr_(lPtr), lIter_(lIter){}
public:
    // constructors;
    VectorListIter(const VectorListIter&) = default;
    VectorListIter(VectorListIter&&) = default;

    T& operator*()
    {
        return *vIter_;
    }

    VectorListIter operator++()
    {
        if(++vIter_ != (*vPtr_).end())
        {
            return *this;
        }
        else if(++lIter_ != (*lPtr_).end())
        {
            vPtr_ = &(*lIter_);
            vIter_ = (*vPtr_).begin();
        }
        return *this;
    }

    VectorListIter operator--(){
        if(--vIter_ >= (*vPtr_).begin())
        {

        }
        else if(--lIter_ != (--(*lPtr_).begin()))
        {
            vPtr_ = &(*lIter_);
            vIter_ = (--(*vPtr_).end());
        }
        return *this;
    }

    bool operator!=(const VectorListIter& other) const
    {
        return ( vIter_ != other.vIter_ );
    }

    bool operator==(const VectorListIter& other) const
    {
        return (vIter_ == other.vIter_);
    }


};



template <typename T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    ListT data_;

public:
    using value_type = T;
    VectorList() = default;
    VectorList(const VectorList& ) = default;
    VectorList(VectorList&& ) = default;
    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    typedef VectorListIter<T> iterator;
    typedef VectorListIter<const T> const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;

    template <class It>
    void append(It p, It q)
    {
        if(p != q){
            data_.push_back(VectT(p, q));
        }
    }

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t size_ = 0;
        for(auto listIter : data_)
        {
            size_ += listIter.size();
        }
        return size_;
    }

    iterator begin()
    {
        typename std::vector<T>* vPtr = &(data_.front());
        typename std::vector<T>::iterator vIter = (*vPtr).begin();
        typename std::list<std::vector<T>>* lPtr = &(data_);
        typename std::list<std::vector<T>>::iterator lIter = (*lPtr).begin();
        return iterator(vPtr, vIter, lPtr, lIter);
    }

    iterator end()
    {
        typename std::vector<T>* vPtr = &(*--(data_.end()));
        typename std::vector<T>::iterator vIter = (*vPtr).end();
        typename std::list<std::vector<T>>* lPtr = &(data_);
        typename std::list<std::vector<T>>::iterator lIter = (*lPtr).end();
        return VectorListIter<T>(vPtr, vIter, lPtr, lIter);
    }

    reverse_iterator rbegin(){
        typename std::vector<T>* vPtr = &(*--(data_.rbegin()));
        typename std::vector<T>::iterator vIter = (*vPtr).rbegin();
        typename std::list<std::vector<T>>* lPtr = &(data_);
        typename std::list<std::vector<T>>::iterator lIter = (*lPtr).rbegin();
        return reverse_iterator(iterator(vPtr, vIter, lPtr, lIter));
    }

    reverse_iterator rend(){
        typename std::vector<T>* vPtr = &(*--(data_.rbegin()));
        typename std::vector<T>::iterator vIter = (*vPtr).rbegin();
        typename std::list<std::vector<T>>* lPtr = &(data_);
        typename std::list<std::vector<T>>::iterator lIter = (*lPtr).rbegin();
        return reverse_iterator(iterator(vPtr, vIter, lPtr, lIter));
    }
};


int main(){
    VectorList<int> vectList;
    std::vector<int> temp{11, 12, 13};
    std::vector<int> temp2{24, 25, 26};
    std::vector<int> temp3{37, 38, 39};
    vectList.append(temp.begin(), temp.end());
    vectList.append(temp2.begin(), temp2.end());
    vectList.append(temp3.begin(), temp3.end());

    std::vector<int>::reverse_iterator rv = vectList.rbegin();
    std::cout << *rv << std::endl;
//    auto v = vectList.begin();
//    for (int i = 0; i < 10; ++i) {
//        std::cout << (v == vectList.end()) << std::endl;
//        ++v;
//    }
    /*for (auto v : vectList) {
        std::cout << v << " ";
    }*/

//    reverse_iterator<int> rIt = vectList.begin();

//    VectorList<int>::reverse_iterator revIt = vectList.rbegin();
//    std::cout << *revIt << std::endl;



    return 0;
}