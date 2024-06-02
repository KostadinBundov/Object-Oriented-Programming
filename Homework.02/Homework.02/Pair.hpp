#pragma once
#include <iostream>

template <class T, class D>
class Pair
{
private:
    T first;
    D second;

public:
    Pair(const T& first, const D& second);
    Pair();
    Pair(T&& first, D&& second);

    const T& getFirst() const;
    const D& getSecond() const;

    void setFirst(const T& first);
    void setFirst(T&& first);
    void setSecond(const D& second);
    void setSecond(D&& second);
};

template <class T, class D>
Pair<T, D>::Pair(const T& first, const D& second) : first(first), second(second) {}

template <class T, class D>
Pair<T, D>::Pair() = default;

template <class T, class D>
Pair<T, D>::Pair(T&& first, D&& second) : first(std::move(first)), second(std::move(second)) {}

template <class T, class D>
const T& Pair<T, D>::getFirst() const
{
    return first;
}

template <class T, class D>
const D& Pair<T, D>::getSecond() const
{
    return second;
}

template <class T, class D>
void Pair<T, D>::setFirst(const T& first)
{
    this->first = first;
}

template <class T, class D>
void Pair<T, D>::setFirst(T&& first)
{
    this->first = std::move(first);
}

template <class T, class D>
void Pair<T, D>::setSecond(const D& second)
{
    this->second = second;
}

template <class T, class D>
void Pair<T, D>::setSecond(D&& second)
{
    this->second = std::move(second);
}