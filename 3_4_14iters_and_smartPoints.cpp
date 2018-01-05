#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <typeinfo>


template <class T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, const T>{
private:
    using Vector = std::vector<T>;
    using List = std::list<Vector>;
    using VIter = typename Vector::const_iterator;
    using LIter = typename List::const_iterator;

    const List* list_;
    const Vector* vector_;
    LIter lCur_;
    VIter vCur_;
public:
    Iterator() = default;
    Iterator(const List* list, LIter lCur, const Vector* vector, VIter vCur) :
            list_(list),
            lCur_(lCur),
            vector_(vector),
            vCur_(vCur){}

    typename Iterator::reference operator*() const{
        return *vCur_;
    }

    typename Iterator::pointer operator->() const{
        return &(*vCur_);
    }

    Iterator& operator++(){
        if(std::next(vCur_) != vector_->end()){
            ++vCur_;
        }
        else if(std::next(lCur_) != list_->end()){
            ++lCur_;
            vector_ = &(*lCur_);
            vCur_ = vector_->begin();
        } else{
            ++vCur_;
        }
        return *this;
    }

    Iterator operator++(int){
        Iterator temp = *this;
        operator++();
        return temp;
    }

    Iterator& operator--(){
        if(vCur_ != vector_->begin()){
            --vCur_;
        }
        else if(lCur_ != list_->begin()){
            --lCur_;
            vector_ = &(*lCur_);
            vCur_ = std::prev(vector_->end());
        } else{
            --vCur_;
        }
        return *this;
    }
    Iterator operator--(int){
        Iterator temp = *this;
        operator--();
        return temp;
    }

    bool operator==(Iterator const& other) const{
        return lCur_ == other.lCur_ && vCur_ == other.vCur_;
    }

    bool operator!=(Iterator const& other) const{
        return !operator==(other);
    }
};


template <class T>
class VectorList{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    ListT data_;
public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const&) = default;
    VectorList(VectorList &&) = default;
    VectorList& operator=(VectorList &&) = default;
    VectorList& operator=(VectorList const&) = default;

    using const_iterator = Iterator<T>;

    template <class It>
    void append(It p, It q){
        if(p != q){
            data_.push_back(VectT(p,q));
        }
    }

    bool empty() const{
        return size() == 0;
    }

    size_t size() const{
        size_t s = 0;
        for(auto &v : data_)
            s += v.size();
        return s;
    }

    const_iterator begin() const{
        return const_iterator(
                &data_,
                data_.begin(),
                &(*data_.begin()),
                (*data_.begin()).begin()
        );
    }

    const_iterator end() const{
        if(empty()) return begin();
        return const_iterator(
                &data_,
                std::prev(data_.end()),
                &(*std::prev(data_.end())),
                (*std::prev(data_.end())).end()
        );
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const{
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const{
        return const_reverse_iterator(begin());
    }
};

template <class T>
void fromBeginToEnd(const VectorList<T>& c){
    for(auto x : c)
        std::cout << x << " ";
    std::cout << std::endl;
}

template <class T>
void fromEndToBegin(const VectorList<T>& c){
    auto r  = c.rbegin();
    for(; r != c.rend(); ++r){
        std::cout << *r << " ";
    }
    std::cout << std::endl;
}

template <class T>
void hitherThither(const VectorList<T>& c){
    auto r  = c.begin();
    for(; r != c.end(); ++r){
        std::cout << *r << " ";
    }
    std::cout << std::endl;
    for(; r != c.begin(); ){
        --r;
        std::cout << *r << " ";
    }
    std::cout << std::endl;
}




int main(){
    using TYPE = std::string;
    std::vector<TYPE> v{"1","2","3"}, v1{"4","5"}, v2{"6","7","8"};
    VectorList<TYPE> c;
    c.append(v.begin(), v.end());
    c.append(v1.begin(), v1.end());
    c.append(v2.begin(), v2.end());
//
    std::cout << c.size() << " " << distance(c.begin(), c.end()) << std::endl;
    std::cout << c.size() << " " << distance(c.rbegin(), c.rend()) << std::endl;
    fromBeginToEnd<TYPE>(c);
    fromEndToBegin<TYPE>(c);
    hitherThither<TYPE>(c);
    return 0;
}



