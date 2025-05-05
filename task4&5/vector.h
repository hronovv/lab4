#ifndef VECTOR_H
#define VECTOR_H
#include <limits>
#include <new>
#include <utility>
#include "iostream"
#include "iterator.h"
#include "pair.h"
#include "stddef.h"


template <typename T>
class GoodVector {
    using basic_iterator = Iterator<T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_iterator = Iterator<const T>;

   private:
    T* arr_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

   public:
    GoodVector();

    explicit GoodVector(size_t n);

    GoodVector(GoodVector<T> const& tmp_);

    GoodVector(std::initializer_list<T> list);

    ~GoodVector();

    bool empty() const;

    size_t size() const;

    size_t max_size() const;

    size_t capacity() const;

    void push_back(T obj);

    void pop_back();  // if called in EMPTY VECTOR → UB, even in std::vector.

    void clear();

    template <typename... Args>
    void emplace_back(Args&&... args);

    template <typename... Args>
    void emplace(const_iterator pos, Args&&... args);

    void insert(
        const_iterator pos_,
        T const& tmp_);	 // if pos_ > size, → memory errors and UB sometimes.

    void insert(const_iterator pos_, T&& tmp_);

    void insert(const_iterator pos_, size_t n, const T& value);

    void insert(const_iterator pos_, const T* begin, const T* end);

    void erase(basic_iterator beg, basic_iterator end);	 // ofc, beg <= end

    void erase(basic_iterator tmp);

    void assign(size_t n, T tmp_);

    void assign(
        const_iterator beg,
        const_iterator end);  // if the range is in an original vector → UB

    basic_iterator begin();

    basic_iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    reverse_iterator rbegin();

    reverse_iterator rend();

    void reserve(size_t new_size);

    void resize(size_t size_, T tmp_ = T());

    T operator[](size_t n);

    const T operator[](size_t n) const;

    T& back();

    T& at(size_t pos);

    T* data();

    T& front();

    void swap(GoodVector<T>& to_swap);
};
#endif	//VECTOR_H
