//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_STL_SHORTCUTS_H
#define WPP_STL_SHORTCUTS_H

#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>

namespace utils {

    using namespace std;

    template<template<class B, class All = std::allocator<B> > class C, class T>
    T accumulate(C<T> c){
        return std::accumulate(c.begin(),c.end(),0.);
    }

    template <template<class B, class All = std::allocator<B> > class C, class T>
    typename C<T>::iterator max(C<T> c){
        return max_element(c.begin(),c.end());
    }

    template <template<class B, class All = std::allocator<B> > class C, class T>
    typename C<T>::iterator min(C<T> c){
        return min_element(c.begin(),c.end());
    }


    template <template<class B, class All = std::allocator<B> > class C, class T>
    C<T>& fill(C<T> c, T value){
        fill(c.begin(), c.end(), value);
        return c;
    }

    template <template<class B, class All = std::allocator<B> > class C, class T>
    C<C<T>>& for_each(C<C<T>> c, T value){
        for_each(c.begin(), c.end(), [&value](C<T> &x){fill(x,0);});
        return c;
    }

    template <template<class B, class All = std::allocator<B> > class C, class T, class FUNC>
    C<T>& for_each(C<T> c, FUNC f){
        for_each(c.begin(), c.end(), f);
        return c;
    }

    template <template<class B, class All = std::allocator<B> > class C, class T, class FUNC>
    C<C<T>>& for_each(C<C<T>> c, FUNC f){
        for_each(c.begin(), c.end(), [&f](C<T> &x){for_each(x,f);});
        return c;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T>& sort(C<T> &c){
        sort(c.begin(),c.end());
        return c;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class F>
    C<T>& sort(C<T> &c, F comp){
        sort(c.begin(),c.end(),comp);
        return c;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<C<T>>& sort(C<C<T>> &c){
        for_each(c.begin(),c.end(), [](C<T> &x){sort(x);});
        return c;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class F>
    void sort(C<C<T>> &c, F comp){
        for_each(c.begin(),c.end(), [&comp](C<T> &x){sort(x,comp);});
    }


}

#endif //WPP_STL_SHORTCUTS_H
