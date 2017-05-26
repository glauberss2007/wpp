//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_CONTAINER_UTILS_H
#define WPP_CONTAINER_UTILS_H

#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace utils {
    // concatenate containers
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> cat(C<T> &v1, C<T> &v2){
        C<T> v3 = v1;
        copy(v2.begin(),v2.end(),back_inserter(v3));
        return v3;
    }

    // create another container with same size in every dimension (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& copyshape(C<T> &from, C<T2> &to){
        to.resize(from.size());
        return to;
    }

    // create another container with same size in every dimension (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& copyshape(C<C<T>> &from, C<C<T2>> &to){
        to.resize(from.size());
        typename C<C<T>>::iterator i = from.begin();
        for_each(to.begin(), to.end(), [&](C<T> &x){copyshape(*i,x); i++;});
        return to;
    }

    // print all elements between 2 iterators
    template<class Iterator>
    void disp(Iterator Begin, Iterator End){
        typedef typename std::iterator_traits<Iterator>::value_type elem;
        for_each(Begin,End,[](elem x){cout << x << "\t";});
        cout << endl;
    }

    // print all elements in a container (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T>& disp(C<T> &c){
        for_each(c.begin(),c.end(),[](T x){cout << x << "\t";});
        cout << endl;
        return c;
    }

    // print all elements in a container (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    void disp(C<C<T>> c){
        for_each(c.begin(),c.end(),[](C<T> x){disp(x);});
        cout << endl;
    }

    // create diagonal matrix
    template <typename T = double>
    vector<vector<T>> eye(long size){
        uniform_real_distribution<T> distribution(0,1);
        vector<vector<T>> result(size,vector<T>(size,0));
        for (int i=0; i<size; i++){
            result[i][i] = 1;
        }
        return result;
    }

    // generate vector with size linearly spaced elements
    template <typename T = double>
    vector<T> linspace(T lb, T ub, long size){
        vector<T> result(size);
        T step = (ub-lb)/(size-1);
        for (int i=0; i<size; i++){
            result[i] = lb + step*i;
        }
        return result;
    }

    // take mean of the elements
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T mean(C<T> &c){
        return accumulate(c.begin(),c.end(),0.)/c.size();
    }

    // inner product of two containers
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    T inner(C<T>& v, C<T2>& v2) {
        return inner_product(v.begin(),v.end(),v2.begin(),0.0);
    }

    // matrix NXM (vector of vectors) with ones
    template <typename T = double>
    vector<vector<T>> ones(long rows, long cols){
        return vector<vector<T>>(rows,vector<T>(cols,1));
    }

    // raise all number in container by alfa
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& pow(C<T>& v, const T2 alfa) {
        for_each(v.begin(),v.end(),[&](T &x){x += std::pow(x,alfa);});
        return v;
    }

    // productory of elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T prod(C<T> c){
        return accumulate(c.begin(),c.end(),1.,[](T init, T alfa){return init*alfa;});
    }

    // generate a random number with distribution [0,1]
    template <typename T = double>
    vector<T> rand(long size){
        uniform_real_distribution<T> distribution(0,1);
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }

    // generate matrix of random numbers with distribution [0,1]
    template <typename T = double>
    vector<vector<T>> rand(long n_rows, long n_cols){
        uniform_real_distribution<T> distribution(0,1);
        vector<vector<T>> result(n_rows);
        for_each(result.begin(),result.end(),[&](vector<T> &x){x = rand(n_cols);});
        return result;
    }

    // generate 3d matrix of random numbers distribution [0,1]
    template <typename T = double>
    vector<vector<vector<T>>> rand(long n_rows, long n_cols, long slices){
        uniform_real_distribution<T> distribution(0,1);
        vector<vector<vector<T>>> result(n_rows);
        for_each(result.begin(),result.end(),[&](vector<vector<T>> &x){x = rand(n_cols,slices);});
        return result;
    }

    // standard deviation
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c){
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0)/c.size() - pow(mean(c),2.));
    }

    // standard deviation (with preprocessed mean)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c, T mean){
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0)/c.size() - pow(mean,2.));
    }

    // sum of all elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T sum(C<T> c){
        return accumulate(c.begin(),c.end(),0.);
    }

    // creates a new function f(c<t>) that applies the function f(t) to all elements of a container c and return r (altered c)
    template <template<class B, class All = std::allocator<B> > class C, class T, class FUNC, class FUNC2>
    FUNC2 vectorize(FUNC f){
        FUNC2 f2 = [&f](C<T> &c){
            C<T> r;
            auto i = c.begin();
            for_each(r.begin(),r.end(),[&f](T &x){x = f(*i);i++;});
        };
        return f2;
    }

    // create 2d matrix of zeros
    template <typename T = double>
    vector<vector<T>> zeros(long rows, long cols){
        return vector<vector<T>>(rows,vector<T>(cols,0));
    }



}

#endif //WPP_CONTAINER_UTILS_H
