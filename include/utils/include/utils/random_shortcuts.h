//
// Created by Alan de Freitas on 03/02/17.
//

#ifndef DATATRANSFORMATION_GENERATOR_H
#define DATATRANSFORMATION_GENERATOR_H

#include <algorithm>
#include <chrono>
#include <random>
#include <type_traits>
#include "container_overloads.h"


namespace utils {

    ////////////////////////////////////////////////////////////////
    //           Number Generator for all distribuitions          //
    ////////////////////////////////////////////////////////////////

    using namespace std;

    ////////////////////////////////////////////////////////////////
    //                 Uniform Distributions                      //
    ////////////////////////////////////////////////////////////////
    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T rand(){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static uniform_real_distribution<T> distribution(0.,1.);
        T result = distribution(generator);
        return result;
    }

    double rand(){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static uniform_real_distribution<double> distribution(0.,1.);
        double result = distribution(generator);
        return result;
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T rand(){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static uniform_int_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <class T = double>
    T rand(T lower_bound, T upper_bound){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return uniform_real_distribution<T>(lower_bound,upper_bound)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T randi(T lower_bound, T upper_bound = numeric_limits<T>::max() ){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return uniform_int_distribution<T>(lower_bound,upper_bound)(generator);
    }

    template <typename T = int>
    vector<T> randi(long size, T lb = 0, T ub = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static uniform_int_distribution<T> distribution(lb,ub);
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }


    ////////////////////////////////////////////////////////////////
    //              Related to Normal distribution                //
    ////////////////////////////////////////////////////////////////

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T normal(T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return normal_distribution<T>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T normal(T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return normal_distribution<double>(mean,stddev)(generator);
    }

    template <typename T = double>
    T randn(){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static normal_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T randn(T mean = 0, T stddev = 1){
        return normal(mean,stddev);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T randn(T mean = 0, T stddev = 1){
        return normal(mean,stddev);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    vector<T> randn(long size, T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static normal_distribution<T> distribution(mean,stddev);
        vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    vector<vector<T>> randn(long n_rows, long n_cols, T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        static normal_distribution<T> distribution(mean,stddev);
        vector<vector<T>> result(n_rows);
        for_each(result.begin(),result.end(),[&](vector<T> &x){x = randn(n_cols,mean,stddev);});
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T lognormal(T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return lognormal_distribution<T>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T lognormal(T mean = 0, T stddev = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return lognormal_distribution<double>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T chi_squared(T degrees_of_freedom = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return chi_squared_distribution<T>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T chi_squared(T degrees_of_freedom = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return chi_squared_distribution<double>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T cauchy(T peak_location = 0, T scale = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return cauchy_distribution<T>(peak_location,scale)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T cauchy(T peak_location = 0, T scale = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return cauchy_distribution<double>(peak_location,scale)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T fisher_f(T degrees_of_freedom_numerator = 2, T degrees_of_freedom_denominator = 2){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return fisher_f_distribution<T>(degrees_of_freedom_numerator,degrees_of_freedom_denominator)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T fisher_f(T degrees_of_freedom_numerator = 2, T degrees_of_freedom_denominator = 2){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return fisher_f_distribution<double>(degrees_of_freedom_numerator,degrees_of_freedom_denominator)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T student_t(T degrees_of_freedom = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return student_t_distribution<T>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T student_t(T degrees_of_freedom = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return student_t_distribution<double>(degrees_of_freedom)(generator);
    }

    ////////////////////////////////////////////////////////////////
    //           Related to Bernoulli (yes/no) trials             //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    bool bernoulli(T probability = 1){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return bernoulli_distribution(probability)(generator);
    }

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I binomial(I trials = 10, T probability = 0.5){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return binomial_distribution<I>(trials,probability)(generator);
    };

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I geometric(T probability = 0.5){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return geometric_distribution<I>(probability)(generator);
    };

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I negative_binomial(I unsuccessful_trials = 10, T probability = 0.5){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return negative_binomial_distribution<I>(unsuccessful_trials,probability)(generator);
    };


    ////////////////////////////////////////////////////////////////
    //                Rate-based distributions                    //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I poisson(T mean = 1.0){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return poisson_distribution<I>(mean)(generator);
    };

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T exponential(T rate_of_occurrence = 1.0){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return exponential_distribution<T>(rate_of_occurrence)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T gamma(T alpha_shape = 1.0, T beta_scale = 1.0){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return gamma_distribution<T>(alpha_shape,beta_scale)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T weibull(T alpha_shape = 1.0, T beta_scale = 1.0){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return weibull_distribution<T>(alpha_shape,beta_scale)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T extreme_value(T alpha_location = 0.0, T beta_scale = 1.0){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return extreme_value_distribution<T>(alpha_location,beta_scale)(generator);
    }

    ////////////////////////////////////////////////////////////////
    //                Piecewise distributions                     //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const initializer_list<T> l){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return discrete_distribution<T>(l)(generator);
    }

    template <typename T = int, typename I = int, std::enable_if_t<std::is_integral<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const initializer_list<T> l){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return discrete_distribution<T>(l.begin(),l.end())(generator);
    }

    template<template<class B, class All = std::allocator<B> > class C, class T = double, class I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const C<T>& c) {
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return discrete_distribution<T>(c.begin(),c.end())(generator);
    }

    template<template<class B, class All = std::allocator<B> > class C, class T = double, class I = int, std::enable_if_t<std::is_integral<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const C<T>& c) {
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return discrete_distribution<T>(c.begin(),c.end())(generator);
    }


    template <typename T = double, typename I = int>
    I piecewise_constant(const initializer_list<T> intervals, const initializer_list<T> weights){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return piecewise_constant_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <template<class B, class All = std::allocator<B> > class C, typename T = double, typename I = int>
    I piecewise_constant(const C<T> intervals, const C<T> weights){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return piecewise_constant_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <typename T = double, typename I = int>
    I piecewise_linear(const initializer_list<T> intervals, const initializer_list<T> weights){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return piecewise_linear_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <template<class B, class All = std::allocator<B> > class C, typename T = double, typename I = int>
    I piecewise_linear(const C<T> intervals, const C<T> weights){
        static default_random_engine generator((int) chrono::system_clock::now().time_since_epoch().count());
        return piecewise_linear_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }










};


#endif //DATATRANSFORMATION_GENERATOR_H
