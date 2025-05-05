#ifndef TASK5_PAIR_H
#define TASK5_PAIR_H
#include <initializer_list>


template <typename T1, typename T2>
struct GoodPair {
    T1 first;
    T2 second;

    GoodPair() = default;


    GoodPair(T1 a, T2 b) {
        this->first = a;
        this->second = b;
    }  // simple logic to call an element of the pair


    GoodPair(std::initializer_list<GoodPair> a) { GoodPair(*a.begin()); }

    void operator=(GoodPair const& pair_) {
        first = pair_.first;
        second = pair_.second;
    }
};
#endif
