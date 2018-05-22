//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef MATLAB_GENERATOR_CONTAINER_UTILS_H
#define MATLAB_GENERATOR_CONTAINER_UTILS_H

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

}

#endif //MATLAB_GENERATOR_CONTAINER_UTILS_H
