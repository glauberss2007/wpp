//
// Created by Alan de Freitas on 03/02/17.
//

#ifndef DATATRANSFORMATION_GENERATOR_H
#define DATATRANSFORMATION_GENERATOR_H

#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

namespace utils {

    std::default_random_engine embed_generator(std::chrono::system_clock::now().time_since_epoch().count());

    // Uniform distribution
    template <class T = double>
    T rand(T lower_bound = 0.0, T upper_bound = 1.0){
        return uniform_real_distribution<T>(lower_bound,upper_bound)(embed_generator);
    }

    template <class T = int>
    T randi(T lower_bound = 0, T upper_bound = numeric_limits<T>::max() ){
        return uniform_int_distribution<T>(lower_bound,upper_bound)(embed_generator);
    }

    // Based on the normal distribution
    template <class T = double>
    T normal(T mean = 0, T stddev = 1){
        return normal_distribution<T>(mean,stddev)(embed_generator);
    }

    template <class T = double>
    T randn(T mean = 0, T stddev = 1){
        return normal(mean,stddev);
    }

    template <class T = double>
    T fisher_f(T degrees_of_freedom_numerator = 2, T degrees_of_freedom_denominator = 2){
        return fisher_f_distribution<T>(degrees_of_freedom_numerator,degrees_of_freedom_denominator)(embed_generator);
    }

    template <class T = double>
    T lognormal(T mean = 0, T stddev = 1){
        return lognormal_distribution<T>(mean,stddev)(embed_generator);
    }

    template <class T = double>
    T cauchy(T peak_location = 0, T scale = 1){
        return cauchy_distribution<T>(peak_location,scale)(embed_generator);
    }

    template <class T = double>
    T chi_squared(T degrees_of_freedom = 1){
        return chi_squared_distribution<T>(degrees_of_freedom)(embed_generator);
    }

    template <class T = double>
    T student_t(T degrees_of_freedom = 1){
        return student_t_distribution<T>(degrees_of_freedom)(embed_generator);
    }

    // Related to Bernoulli (yes/no) trials
    template <class T = double>
    bool bernoulli(T probability = 1){
        return bernoulli_distribution(probability)(embed_generator);
    }

    template <class I = int, class T = double>
    I binomial(I trials = 10, T probability = 0.5){
        return binomial_distribution<I>(trials,probability)(embed_generator);
    };

    template <class I = int, class T = double>
    I negative_binomial(I unsuccessful_trials = 10, T probability = 0.5){
        return negative_binomial_distribution<I>(unsuccessful_trials,probability)(embed_generator);
    };
    template <class I = int, class T = double>
    I binomial_negative(I unsuccessful_trials = 10, T probability = 0.5){
        return negative_binomial<I>(unsuccessful_trials,probability)(embed_generator);
    };

    template <class I = int, class T = double>
    I geometric(T probability = 0.5){
        return geometric_distribution<T>(probability)(embed_generator);
    };

    // Rate-based distributions
    template <class T = int, class D = double>
    T poisson(D mean = 1.0){
        return poisson_distribution<T>(mean)(embed_generator);
    };

    template <class T = double>
    T exponential(T rate_of_occurrence = 1.0){
        return exponential_distribution<T>(rate_of_occurrence)(embed_generator);
    }

    template <class T = double>
    T gamma(T alpha_shape = 1.0, T beta_scale = 1.0){
        return gamma_distribution<T>(alpha_shape,beta_scale)(embed_generator);
    }

    template <class T = double>
    T weibull(T alpha_shape = 1.0, T beta_scale = 1.0){
        return weibull_distribution<T>(alpha_shape,beta_scale)(embed_generator);
    }

    template <class T = double>
    T extreme_value(T alpha_location = 0.0, T beta_scale = 1.0){
        return extreme_value_distribution<T>(alpha_location,beta_scale)(embed_generator);
    }

};


#endif //DATATRANSFORMATION_GENERATOR_H
