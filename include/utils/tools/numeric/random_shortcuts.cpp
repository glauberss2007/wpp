#include "utils/random_shortcuts.h"
#include <vector>
#include <set>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    using namespace std;
    using namespace utils;

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Uniform Distribution"
         << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Floating Point" << termcolor::reset << endl;
        cout << "utils::rand(): " << utils::rand() << endl;
        cout << "utils::rand(): " << utils::rand() << endl;
        cout << "utils::rand(): " << utils::rand() << endl;
        cout << "utils::rand(): " << utils::rand() << endl;
        cout << "std::rand(): " << std::rand() << " (don't use it: ambiguous)" << endl;
        cout << "rand<double>(): " << rand < double > () << endl;
        cout << "rand<double>(): " << rand < double > () << endl;
        cout << "rand(5.0,15.0): " << rand(5.0, 15.0) << endl;
        cout << "rand(5.0,15.0): " << rand(5.0, 15.0) << endl;
        cout << "rand<double>(5.0,15.0): " << rand < double > (5.0, 15.0) << endl;
        cout << "rand<double>(5.0,15.0): " << rand < double > (5.0, 15.0) << endl;
        cout << termcolor::bold << termcolor::underline << "Integer" << termcolor::reset << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10,3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10,3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10,3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10,3, 15) << endl;
    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Related to Normal distribution"
         << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Normal Distribution" << termcolor::reset << endl;
        std::cout << "randn(): " << randn() << std::endl;
        std::cout << "randn(): " << randn() << std::endl;
        std::cout << "randn(4.3,2.5): " << randn(4.3, 2.5) << std::endl;
        std::cout << "randn(4.3,2.5): " << randn(4.3, 2.5) << std::endl;
        std::cout << "randn(10,4.3,2.5): " << randn(10,4.3, 2.5) << std::endl;
        std::cout << "randn(10,4.3,2.5): " << randn(10,4.3, 2.5) << std::endl;
        std::cout << "randn(4,4,4.3,2.5): " << randn(4,4,4.3, 2.5) << std::endl;
        std::cout << "randn(4,4,4.3,2.5): " << randn(4,4,4.3, 2.5) << std::endl;
        std::cout << "randn<double>(4,2): " << randn<double>(4, 2) << std::endl;
        std::cout << "randn<double>(4,2): " << randn<double>(4, 2) << std::endl;
        std::cout << "randn(4,2): " << randn(4, 2) << std::endl;
        std::cout << "randn(4,2): " << randn(4, 2) << std::endl;
        std::cout << "randn<int>(4,2): " << randn<int>(4, 2) << std::endl;
        std::cout << "randn<int>(4,2): " << randn<int>(4, 2) << std::endl;
        std::cout << "normal(3.0,10.0): " << normal(3.0, 10.0) << std::endl;
        std::cout << "normal(3.0,10.0): " << normal(3.0, 10.0) << std::endl;
        std::cout << "normal(3,10): " << normal(3, 10) << std::endl;
        std::cout << "normal(3,10): " << normal(3, 10) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Lognormal distribution" << termcolor::reset << endl;
        std::cout << "lognormal(3.0,10.0): " << lognormal(3.0, 10.0) << std::endl;
        std::cout << "lognormal(3.0,10.0): " << lognormal(3.0, 10.0) << std::endl;
        std::cout << "lognormal(3,10): " << lognormal(3, 10) << std::endl;
        std::cout << "lognormal(3,10): " << lognormal(3, 10) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Chi-squared distribution" << termcolor::reset << endl;
        std::cout << "chi_squared(10.0): " << chi_squared(10.0) << std::endl;
        std::cout << "chi_squared(10.0): " << chi_squared(10.0) << std::endl;
        std::cout << "chi_squared(10): " << chi_squared(10) << std::endl;
        std::cout << "chi_squared(10): " << chi_squared(10) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Cauchy distribution" << termcolor::reset << endl;
        std::cout << "cauchy(1.0,1): " << cauchy(1.0, 1.) << std::endl;
        std::cout << "cauchy(1.0,1): " << cauchy(1.0, 1.) << std::endl;
        std::cout << "cauchy(1,1): " << cauchy(1, 1) << std::endl;
        std::cout << "cauchy(1,1): " << cauchy(1, 1) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Fisher F-distribution" << termcolor::reset << endl;
        std::cout << "fisher_f(2.0,2): " << fisher_f(2.0, 2.) << std::endl;
        std::cout << "fisher_f(2.0,2): " << fisher_f(2.0, 2.) << std::endl;
        std::cout << "fisher_f(2,2): " << fisher_f(2, 2) << std::endl;
        std::cout << "fisher_f(2,2): " << fisher_f(2, 2) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Student T-Distribution" << termcolor::reset << endl;
        std::cout << "student_t(10.0): " << student_t(10.0) << std::endl;
        std::cout << "student_t(10.0): " << student_t(10.0) << std::endl;
        std::cout << "student_t(10): " << student_t(10) << std::endl;
        std::cout << "student_t(10): " << student_t(10) << std::endl;


    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Related to Bernoulli (yes/no) trials:"
         << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Bernoulli distribution" << termcolor::reset << endl;
        std::cout << "bernoulli(0.7): " << bernoulli(0.7) << std::endl;
        std::cout << "bernoulli(0.7): " << bernoulli(0.7) << std::endl;
        std::cout << "bernoulli(0.3): " << bernoulli(0.3) << std::endl;
        std::cout << "bernoulli(0.3): " << bernoulli(0.3) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Binomial distribution" << termcolor::reset << endl;
        std::cout << "binomial(100,0.7): " << binomial(100,0.7) << std::endl;
        std::cout << "binomial(100,0.7): " << binomial(100,0.7) << std::endl;
        std::cout << "binomial(100,0.3): " << binomial(100,0.3) << std::endl;
        std::cout << "binomial(100,0.3): " << binomial(100,0.3) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Geometric distribution" << termcolor::reset << endl;
        std::cout << "geometric(0.9): " << geometric(0.9) << std::endl;
        std::cout << "geometric(0.9): " << geometric(0.9) << std::endl;
        std::cout << "geometric(0.1): " << geometric(0.1) << std::endl;
        std::cout << "geometric(0.1): " << geometric(0.1) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Negative binomial distribution" << termcolor::reset << endl;
        std::cout << "negative_binomial(100,0.7): " << negative_binomial(100,0.7) << std::endl;
        std::cout << "negative_binomial(100,0.7): " << negative_binomial(100,0.7) << std::endl;
        std::cout << "negative_binomial(100,0.3): " << negative_binomial(100,0.3) << std::endl;
        std::cout << "negative_binomial(100,0.3): " << negative_binomial(100,0.3) << std::endl;

    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Rate-based distributions:"
         << termcolor::reset
         << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Poisson distribution" << termcolor::reset << endl;
        std::cout << "poisson(1.5): " << poisson(1.5) << std::endl;
        std::cout << "poisson(1.5): " << poisson(1.5) << std::endl;
        std::cout << "poisson(1.5): " << poisson(1.5) << std::endl;
        std::cout << "poisson(1.5): " << poisson(1.5) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Exponential distribution" << termcolor::reset << endl;
        std::cout << "exponential(1.5): " << exponential(1.5) << std::endl;
        std::cout << "exponential(1.5): " << exponential(1.5) << std::endl;
        std::cout << "exponential(1.5): " << exponential(1.5) << std::endl;
        std::cout << "exponential(1.5): " << exponential(1.5) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Gamma distribution" << termcolor::reset << endl;
        std::cout << "gamma(1.5,1.5): " << gamma(1.5,1.5) << std::endl;
        std::cout << "gamma(1.5,1.5): " << gamma(1.5,1.5) << std::endl;
        std::cout << "gamma(1.5,1.5): " << gamma(1.5,1.5) << std::endl;
        std::cout << "gamma(1.5,1.5): " << gamma(1.5,1.5) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Weibull distribution" << termcolor::reset << endl;
        std::cout << "weibull(1.5,1.5): " << weibull(1.5,1.5) << std::endl;
        std::cout << "weibull(1.5,1.5): " << weibull(1.5,1.5) << std::endl;
        std::cout << "weibull(1.5,1.5): " << weibull(1.5,1.5) << std::endl;
        std::cout << "weibull(1.5,1.5): " << weibull(1.5,1.5) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Extreme Value distribution" << termcolor::reset << endl;
        std::cout << "extreme_value(1.5,1.5): " << extreme_value(1.5,1.5) << std::endl;
        std::cout << "extreme_value(1.5,1.5): " << extreme_value(1.5,1.5) << std::endl;
        std::cout << "extreme_value(1.5,1.5): " << extreme_value(1.5,1.5) << std::endl;
        std::cout << "extreme_value(1.5,1.5): " << extreme_value(1.5,1.5) << std::endl;

    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Piecewise distributions:"
         << termcolor::reset
         << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Discrete distribution" << termcolor::reset << endl;
        std::cout << "discrete({2,2,1,1,2,2,1,1,2,2}): " << discrete({2,2,1,1,2,2,1,1,2,2}) << std::endl;
        std::cout << "discrete({2,2,1,1,2,2,1,1,2,2}): " << discrete({2,2,1,1,2,2,1,1,2,2}) << std::endl;
        std::cout << "vector<int> a = {2,2,1,1,2,2,1,1,2,2}; " << std::endl;
        vector<int> a = {2,2,1,1,2,2,1,1,2,2};
        std::cout << "discrete(a): " << discrete(a) << std::endl;
        std::cout << "discrete(a): " << discrete(a) << std::endl;
        std::cout << "discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}): " << discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}) << std::endl;
        std::cout << "discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}): " << discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}) << std::endl;
        std::cout << "vector<double> b = {2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}; " << std::endl;
        vector<double> b = {2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0};
        std::cout << "discrete(b): " << discrete(b) << std::endl;
        std::cout << "discrete(b): " << discrete(b) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Piecewise constant distribution" << termcolor::reset << endl;
        cout << "std::vector<double> intervals {0.0, 2.0, 4.0, 6.0, 8.0, 10.0};" << endl;
        std::vector<double> intervals {0.0, 2.0, 4.0, 6.0, 8.0, 10.0};
        cout << "std::vector<double> weights {2.0, 1.0, 2.0, 1.0, 2.0};" << endl;
        std::vector<double> weights {2.0, 1.0, 2.0, 1.0, 2.0};
        std::cout << "piecewise_constant(intervals,weights): " << piecewise_constant(intervals,weights) << std::endl;
        std::cout << "piecewise_constant(intervals,weights): " << piecewise_constant(intervals,weights) << std::endl;
        std::cout << "piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}): " << piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}) << std::endl;
        std::cout << "piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}): " << piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}) << std::endl;

        cout << termcolor::bold << termcolor::underline << "Piecewise linear distribution" << termcolor::reset << endl;
        cout << "std::vector<double> intervals {0.0, 4.5, 9.0};" << endl;
        std::vector<double> intervals2 {0.0, 4.5, 9.0};
        cout << "std::vector<double> weights {10.0, 0.0, 10.0};" << endl;
        std::vector<double> weights2 {10.0, 0.0, 10.0};
        std::cout << "piecewise_linear(intervals2,weights2): " << piecewise_linear(intervals2,weights2) << std::endl;
        std::cout << "piecewise_linear(intervals2,weights2): " << piecewise_linear(intervals2,weights2) << std::endl;
        std::cout << "piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}): " << piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}) << std::endl;
        std::cout << "piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}): " << piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}) << std::endl;

    }


}
