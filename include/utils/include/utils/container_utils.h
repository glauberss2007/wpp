//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_CONTAINER_UTILS_H
#define WPP_CONTAINER_UTILS_H

#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <set>

namespace utils {

    using namespace std;

    //////////////////////////////////////////////
    //         CONTAINER GENERATORS             //
    //////////////////////////////////////////////

    // create diagonal matrix
    template<typename T = double>
    vector<vector<T>> eye(long size) {
        vector<vector<T>> result(size, vector<T>(size, 0));
        for (int i = 0; i < size; i++) {
            result[i][i] = 1;
        }
        return result;
    }

    // generate vector with size linearly spaced elements
    template<typename T = double>
    vector<T> linspace(T lb, T ub, long size) {
        vector<T> result(size);
        double step = (double)(ub - lb) / (double)(size - 1);
        for (int i = 0; i < size; i++) {
            result[i] = (T)(lb + step * i);
        }
        return result;
    }

    // matrix NXM (vector of vectors) with ones
    template<typename T = double>
    vector<vector<T>> ones(long rows, long cols) {
        return vector<vector<T>>(rows, vector<T>(cols, 1));
    }

    template<typename T = double>
    vector<vector<T>> zeros(long rows, long cols) {
        return vector<vector<T>>(rows, vector<T>(cols, 0));
    }

    template<typename T = double>
    vector<T> ones(T n) {
        return vector<T>(n, 1);
    }

    template<typename T = double>
    vector<T> zeros(T n) {
        return vector<T>(n, 0);
    }




    template<typename T = int>
    vector<T> perm(T n) {
        vector<T> r(n);
        for (int i = 0; i < n; ++i) {
            r[i] = i;
        }
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        shuffle(r.begin(),r.end(),generator);
        return r;
    }

    template <typename T = int>
    vector<T> perm(long size, T initial = 0){
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = initial++;});
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        shuffle(result.begin(),result.end(),generator);
        return result;
    }




    // generate a random number with distribution [0,1]
    template<typename T = double>
    vector<T> rand(long size) {
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static uniform_real_distribution<T> distribution(0.0, 1.0);
        vector<T> result(size);
        for_each(result.begin(), result.end(), [](T &x) { x = distribution(generator); });
        return result;
    }

    // generate matrix of random numbers with distribution [0,1]
    template<typename T = double>
    vector<vector<T>> rand(long n_rows, long n_cols) {
        uniform_real_distribution<T> distribution(0, 1);
        vector<vector<T>> result(n_rows);
        for_each(result.begin(), result.end(), [&](vector<T> &x) { x = rand(n_cols); });
        return result;
    }

    // generate 3d matrix of random numbers distribution [0,1]
    template<typename T = double>
    vector<vector<vector<T>>> rand(long n_rows, long n_cols, long slices) {
        uniform_real_distribution<T> distribution(0, 1);
        vector<vector<vector<T>>> result(n_rows);
        for_each(result.begin(), result.end(), [&](vector<vector<T>> &x) { x = rand(n_cols, slices); });
        return result;
    }





    //////////////////////////////////////////////
    //          CONTAINER METHODS               //
    //////////////////////////////////////////////

    // print all elements between 2 iterators
    template<class Iterator>
    void disp(Iterator Begin, Iterator End) {
        typedef typename std::iterator_traits<Iterator>::value_type elem;
        for_each(Begin, End, [](elem x) { cout << x << "\t"; });
        cout << endl;
    }

    // print all elements in a container (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> &disp(C<T> &c) {
        for_each(c.begin(), c.end(), [](T x) { cout << x << "\t"; });
        cout << endl;
        return c;
    }

    // print all elements in a container (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    void disp(C<C<T>> c) {
        for_each(c.begin(), c.end(), [](C<T> x) { disp(x); });
        cout << endl;
    }

    // take mean of the elements
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T mean(C<T> &c) {
        return accumulate(c.begin(), c.end(), 0.) / c.size();
    }


    // raise all number in container by alfa
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> &pow(C<T> &v, const T2 alfa) {
        for_each(v.begin(), v.end(), [&](T &x) { x += std::pow(x, alfa); });
        return v;
    }

    // productory of elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T prod(C<T> c) {
        return accumulate(c.begin(), c.end(), 1., [](T init, T alfa) { return init * alfa; });
    }

    // standard deviation
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c) {
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0) / (c.size()-1) - std::pow(mean(c), 2.));
    }

    // standard deviation (with preprocessed mean)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c, T mean) {
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0) / (c.size()-1) - std::pow(mean, 2.));
    }

    // sum of all elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T sum(C<T> c) {
        return accumulate(c.begin(), c.end(), 0.);
    }

    //////////////////////////////////////////////
    //      OPERATIONS BETWEEN CONTAINERS       //
    //////////////////////////////////////////////

    // concatenate containers
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> cat(C<T> &v1, C<T> &v2) {
        C<T> v3 = v1;
        copy(v2.begin(), v2.end(), back_inserter(v3));
        return v3;
    }

    // create another container with same size in every dimension (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T2> &copyshape(C<T> &from, C<T2> &to) {
        to.resize(from.size());
        return to;
    }

    // create another container with same size in every dimension (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T2>> &copyshape(C<C<T>> &from, C<C<T2>> &to) {
        to.resize(from.size());
        typename C<C<T>>::iterator i = from.begin();
        for_each(to.begin(), to.end(), [&](C<T> &x) {
            copyshape(*i, x);
            i++;
        });
        return to;
    }

    // inner product of two containers
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    T2 inner(C<T> &v, C<T2> &v2) {
        return inner_product(v.begin(), v.end(), v2.begin(), 0.0);
    }

}

#endif //WPP_CONTAINER_UTILS_H
