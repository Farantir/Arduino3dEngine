#ifndef _A3DE_UTIL_H_
#define _A3DE_UTIL_H_

namespace a3de
{
    // some template metaprogramming primitives
    // to avoid including a large portion of the
    // standard library

    template<typename T> struct remove_reference      { using type = T; };
    template<typename T> struct remove_reference<T&>  { using type = T; };
    template<typename T> struct remove_reference<T&&> { using type = T; };

    // lets us use move semantics without the standard library bloat
    template <typename T>
    typename remove_reference<T>::type&& move(T&& t)
    {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }

    // generic swap function
    template <typename T>
    void swap(T& lhs, T& rhs)
    {
        T tmp{move(rhs)};
        rhs = move(lhs);
        lhs = move(tmp);        
    }

    // shellsort
    void shellsort (int *array, int elemente);
}

#endif