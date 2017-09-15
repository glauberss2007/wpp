// https://theboostcpplibraries.com/boost.accumulators
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::accumulators;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Counting with boost::accumulators::tag::count" << termcolor::reset << std::endl;
    {
        accumulator_set<int, features<tag::count>> acc;
        acc(4);
        acc(-6);
        acc(9);
        std::cout << "count(acc): " << count(acc) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using mean and variance" << termcolor::reset << std::endl;
    {
        accumulator_set<double, features<tag::mean, tag::variance>> acc;
        acc(8);
        acc(9);
        acc(10);
        acc(11);
        acc(12);
        std::cout << "mean(acc): " << mean(acc) << '\n';
        std::cout << "variance(acc): " << variance(acc) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Calculating the weighted variance" << termcolor::reset << std::endl;
    {
        accumulator_set<double, features<tag::mean, tag::variance>, int> acc;
        acc(8, weight = 1);
        acc(9, weight = 1);
        acc(10, weight = 4);
        acc(11, weight = 1);
        acc(12, weight = 1);
        std::cout << "mean(acc): " << mean(acc) << '\n';
        std::cout << "variance(acc): " << variance(acc) << '\n';
    }

    std::cout << "Boost.Accumulators provides many more accumulators." << std::endl;
}
