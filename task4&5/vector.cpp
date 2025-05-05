#include "vector.h"
#include <utility>


template <typename T>
GoodVector<T>::GoodVector() {
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <typename T>
GoodVector<T>::GoodVector(size_t n) {
    reserve(n);


    for (int i = 0; i < n; i++) {
        new (arr_ + i) T();
    }
}  // when the size is passed

template <typename T>
GoodVector<T>::GoodVector(GoodVector<T> const& tmp_) {
    size_ = tmp_.size_;
    capacity_ = tmp_.capacity_;
    arr_ = reinterpret_cast<T*>(new int8_t[size_ * sizeof(T)]);


    for (size_t i = 0; i < size_; i++) {
        new (arr_ + i) T(tmp_[i]);
    }  // copy constructor, could be also with the help of r-value, if no need to use tmp_ again
}


template <typename T>
GoodVector<T>::GoodVector(std::initializer_list<T> list)
    : size_(list.size()), capacity_(list.size()) {
    arr_ = reinterpret_cast<T*>(new int8_t[size_ * sizeof(T)]);
    auto list_iterator = list.begin();


    for (size_t i = 0; i < size_; i++, list_iterator++) {
        T tmp = *list_iterator;
        new (arr_ + i) T(std::move(
            tmp));	// passing as r-value + clearing tmp(demanded for placement new)
    }
}

template <typename T>
GoodVector<T>::~GoodVector() {


    for (size_t i = 0; i < size_; i++) {
        (arr_ + i)->~T();  // explicit destructor
    }
    arr_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template <typename T>
bool GoodVector<T>::empty() const {
    return size_ == 0;
}  // so simple, either empty (true) or not(false)

template <typename T>
size_t GoodVector<T>::size() const {
    return size_;
}  // just returning how many elements we have in the vector

template <typename T>
typename GoodVector<T>::basic_iterator
GoodVector<T>::begin() {  // typename just to point that iterator is a class
    return basic_iterator(arr_);
}  // returning the iterator that contains adress of the 1st element

template <typename T>
typename GoodVector<T>::basic_iterator GoodVector<T>::end() {
    return basic_iterator(arr_ + size_);
}  // returning the iterator that contains adress of the last element

template <typename T>
typename GoodVector<T>::const_iterator GoodVector<T>::cbegin() const {
    return const_iterator(arr_);
}  // returning the constant iterator that contains adress of the 1st element

template <typename T>
typename GoodVector<T>::const_iterator GoodVector<T>::cend() const {
    return const_iterator(arr_ + size_);
}  // returning the constant iterator that contains adress of the last element

template <typename T>
typename GoodVector<T>::reverse_iterator GoodVector<T>::rbegin() {
    return reverse_iterator(arr_ + size_);
}  // returning the rereverse iterator that contains adress of the last element

template <typename T>
typename GoodVector<T>::reverse_iterator GoodVector<T>::rend() {
    return reverse_iterator(arr_);
}  // returning the rereverse iterator that contains adress of the 1st element

template <typename T>
size_t GoodVector<T>::max_size() const {
    return UINT64_MAX / sizeof(T);
}  // returning max potential elements(with the type we have) that vector is able to contain

template <typename T>
void GoodVector<T>::reserve(size_t new_capacity) {


    if (new_capacity < size_) {
        return;
    }  // nothing happens
    T* tmp = reinterpret_cast<T*>(
        new int8_t[new_capacity * sizeof(T)]);	// creating new vector


    for (int i = 0; i < size_; i++) {
        new (tmp + i) T(arr_[i]);  // using placement new
        (arr_ + i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(arr_);
    arr_ = tmp;
    capacity_ = new_capacity;
}

template <typename T>
void GoodVector<T>::resize(size_t new_size, T tmp_) {


    if (new_size > capacity_) {
        reserve(new_size);
    }


    for (size_t i = size_; i < new_size; i++) {
        new (arr_ + i) T(tmp_);
    }


    for (size_t i = new_size; i < size_; i++) {
        (arr_ + i)->~T();
    }  // if cutting our vector
    size_ = new_size;
}  // could also add if else construction, but 1 loop will always not run, guess why

template <typename T>
void GoodVector<T>::push_back(T tmp_) {


    if (size_ >= capacity_) {
        reserve((2 * size_) + 1);
    }
    new (arr_ + size_) T(std::move(tmp_));	// passing as r-value
    size_++;
}

template <typename T>
void GoodVector<T>::pop_back() {
    if (!empty()) {
        (arr_ + size_ - 1)->~T();
    }  // deleting if not empty
    size_--;  // UB LINE if empty, even in std::vector, also can be put in if brackets(idk however why they didnt do it in stl)
}

template <typename T>
void GoodVector<T>::insert(const_iterator pos_, T const& tmp_) {
    size_t pos = (pos_).base() - arr_;
    reserve(size_ + 1);


    for (size_t i = size_; i > pos; i--) {
        new (arr_ + i) T(arr_[i - 1]);
        (arr_ + i - 1)
            ->~T();	 // no need is passed as r-value, but there's no use of std::move, so using explicit destrcutor
    }
    new (arr_ + pos) T(tmp_);
    size_++;
}

template <typename T>
void GoodVector<T>::insert(const_iterator pos_, size_t n, const T& value) {
    size_t pos = (pos_).base() - arr_;
    reserve(size_ + n);


    for (size_t i = size_; i > pos; i--) {
        new (arr_ + i + n - 1) T(arr_[i - 1]);
        (arr_ + i - 1)->~T();
    }


    for (size_t i = 0; i < n; ++i) {
        new (arr_ + pos + i) T(value);
    }  // same logic but n elements, so loop

    size_ += n;
}

template <typename T>
void GoodVector<T>::insert(const_iterator pos_, const T* begin, const T* end) {
    size_t pos = (pos_).base() - arr_;
    size_t new_size = size_ + (end - begin);
    reserve(new_size);


    for (size_t i = size_; i > pos; i--) {
        new (arr_ + i + (end - begin - 1)) T(arr_[i - 1]);
        (arr_ + i - 1)->~T();
    }


    for (const T* it = begin; it != end; ++it) {
        new (arr_ + pos++) T(*it);
    }  // same logic but elements where pointer points, so simple

    size_ = new_size;
}

template <typename T>
void GoodVector<T>::insert(
    const_iterator pos_,
    T&& tmp_) {	 // overloading for the r-value, e.x if element we passing has no need to be used later
    size_t pos = (pos_).base() - arr_;
    reserve(size_ + 1);


    for (size_t i = size_; i > pos; i--) {
        new (arr_ + i) T(arr_[i - 1]);
        (arr_ + i - 1)->~T();
    }
    new (arr_ + pos) T(tmp_);
    size_++;
}

template <typename T>
void GoodVector<T>::swap(GoodVector<T>& to_swap) {
    std::swap(to_swap.arr_, arr_);
    std::swap(to_swap.size_, size_);
    std::swap(to_swap.capacity_, capacity_);
}  //simple swaps(std::move ofc)

template <typename T>
template <typename... Args>
void GoodVector<T>::emplace(const_iterator pos, Args&&... args) {
    T tmp(args...);
    insert(pos, tmp);
}  // using r-value reference

template <typename T>
template <typename... Args>
void GoodVector<T>::emplace_back(Args&&... args) {
    T tmp(args...);
    push_back(tmp);
}  // using r-value reference + variadic template

template <typename T>
void GoodVector<T>::erase(basic_iterator beg, basic_iterator end) {
    int i1 = beg.base() - arr_;
    int i2 = end.base() - arr_;
    if (size_ - (i2 - i1) == 0) {
        clear();
        return;
    }  // if whole vector is about to be erased, no need to continue, just use already defined clear method


    for (auto i = i1; i < size_; i++) {
        new (arr_ + i) T(arr_[i + (i2 - i1)]);
    }  // just relocating elements after i2 to the orginial vector, potential ub(just random numbers) however(when i+(i2-i1)>size), but we will resize it
    resize(size_ - (i2 - i1));
}

template <typename T>
void GoodVector<T>::erase(basic_iterator tmp) {
    erase(tmp, tmp + 1);
}  // if 1 element is about to be erased

template <typename T>
void GoodVector<T>::assign(size_t n, T tmp_) {
    clear();
    resize(n, std::move(tmp_));
}  // just clearing vector and making a new one with the size identical elements

template <typename T>
void GoodVector<T>::assign(const_iterator beg, const_iterator end) {
    clear();
    int new_size =
        end.base() - beg.base();  // how many elements new vector contains
    resize(new_size);


    for (auto i = 0; i < new_size; i++) {
        new (arr_ + i) T(*(beg + i));  // using emplacement new
    }
}

template <typename T>
void GoodVector<T>::clear() {
    resize(0);
}  // just makes the vector empty by deleting each element

template <typename T>
size_t GoodVector<T>::capacity() const {
    return capacity_;
}  // returns the capacity of the vector

template <typename T>
T& GoodVector<T>::back() {
    return arr_[size_ - 1];
}  // returns a reference to the last element

template <typename T>
T& GoodVector<T>::at(size_t pos) {
    return arr_[pos];
}  // returns the reference to an element in the certain position in the vector

template <typename T>
T* GoodVector<T>::data() {
    return arr_;
}  // just returns the pointer to our vector

template <typename T>
T& GoodVector<T>::front() {
    return arr_[0];
}  // returns a reference to the 1-st element of the vector

template <typename T>
T GoodVector<T>::operator[](size_t n) {
    return *(arr_ + n);
}  // overloading operator [] that gives a copy of element which is located in our vector in position n

template <typename T>
const T GoodVector<T>::operator[](size_t n) const {
    return *(arr_ + n);
}  // overloading the operator above but for const element

/*  Below
    Explicit template instantiation
    For linker :)
*/

template class GoodVector<int>;
template void GoodVector<int>::emplace<int>(Iterator<int const>, int&&);
template void GoodVector<int>::emplace_back<int>(int&&);

template class GoodVector<unsigned long>;
template void GoodVector<unsigned long>::emplace<unsigned long>(
    Iterator<unsigned long const>, unsigned long&&);
template void GoodVector<unsigned long>::emplace_back<unsigned long>(
    unsigned long&&);

template class GoodVector<short>;
template void GoodVector<short>::emplace<short>(Iterator<short const>, short&&);
template void GoodVector<short>::emplace_back<short>(short&&);

template class GoodVector<double>;
template void GoodVector<double>::emplace<double>(Iterator<double const>,
                                                  double&&);
template void GoodVector<double>::emplace_back<double>(double&&);

template class GoodVector<char>;
template void GoodVector<char>::emplace<char>(Iterator<char const>, char&&);
template void GoodVector<char>::emplace_back<char>(char&&);

template class GoodVector<float>;
template void GoodVector<float>::emplace<float>(Iterator<float const>, float&&);
template void GoodVector<float>::emplace_back<float>(float&&);

template class GoodVector<long long>;
template void GoodVector<long long>::emplace<long long>(
    Iterator<long long const>, long long&&);
template void GoodVector<long long>::emplace_back<long long>(long long&&);

template class GoodVector<std::string>;
template void GoodVector<std::string>::emplace<std::string>(
    Iterator<std::string const>, std::string&&);
template void GoodVector<std::string>::emplace_back<std::string>(std::string&&);

template class GoodVector<unsigned long long>;
template void GoodVector<unsigned long long>::emplace<unsigned long long>(
    Iterator<unsigned long long const>, unsigned long long&&);
template void GoodVector<unsigned long long>::emplace_back<unsigned long long>(
    unsigned long long&&);

template class GoodVector<GoodVector<GoodVector<GoodPair<
    GoodPair<std::string, std::string>, GoodPair<std::string, std::string>>>>>;
template class GoodVector<GoodVector<GoodPair<
    GoodPair<std::string, std::string>, GoodPair<std::string, std::string>>>>;
template class GoodVector<
    GoodPair<GoodVector<int>, GoodVector<GoodPair<int, double>>>>;
template class GoodVector<GoodPair<int, double>>;
