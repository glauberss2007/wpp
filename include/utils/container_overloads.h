//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_CONTAINER_OVERLOADS_H
#define WPP_CONTAINER_OVERLOADS_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

namespace utils {
    // overloads
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator+=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x += alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator+(const C<T>& v, const T2 alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x += alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator+=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::plus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator+(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::plus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator+=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x += alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator+(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x += alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator+=(C<C<T>>& a, const C<C<T2>> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::plus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator+(const C<C<T>>& a, const C<C<T2>> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::plus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator-=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x -= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator-(const C<T>& v, const T2 alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x -= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator-=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::minus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator-(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::minus<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator-=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x -= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator-(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x -= alfa;});
        return result;
    }

    template <class T> struct minus : binary_function <T,T,T> {
        T operator() (const T& x, const T& y) const {return x-y;}
    };

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator-=(C<C<T>>& a, const C<C<T2>> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), utils::minus<C<T>>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator-(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), utils::minus<C<T>>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator*=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x *= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator*(const C<T>& v, const T2 alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x *= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator*=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::multiplies<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator*(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::multiplies<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator*=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x *= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator*(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x *= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator*=(C<C<T>>& a, const C<C<T2>> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::multiplies<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator*(const C<C<T>>& a, const C<C<T2>> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::multiplies<T>());
        } else {
            cout << "The containers should have the same size" << endl;
        }
        return result;
    }


    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator/=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x -= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> operator/(const C<T>& v, T alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x /= alfa;});
        return result;
    }


}

#endif //WPP_CONTAINER_OVERLOADS_H
