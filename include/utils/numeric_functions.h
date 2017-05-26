//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_NUMERIC_FUNCTIONS_H_H
#define WPP_NUMERIC_FUNCTIONS_H_H

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

    template <typename T = double>
    T rand(){
        uniform_real_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <typename T = double>
    T randn(){
        normal_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <typename T = double>
    vector<T> randn(long size){
        normal_distribution<T> distribution(0,1);
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }

    template <typename T = double>
    vector<vector<T>> randn(long n_rows, long n_cols){
        normal_distribution<T> distribution(0,1);
        vector<vector<T>> result(n_rows);
        for_each(result.begin(),result.end(),[&](vector<T> &x){x = randn(n_cols);});
        return result;
    }



    template <typename T = int>
    vector<T> randi(long size, T lb = 0, T ub = 1){
        uniform_int_distribution<T> distribution(lb,ub);
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }

    template <typename T = int>
    vector<T> randperm(long size, T initial = 0){
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = initial++;});
        shuffle(result.begin(),result.end(),generator);
        return result;
    }


}

#endif //WPP_NUMERIC_FUNCTIONS_H_H
