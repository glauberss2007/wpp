// https://theboostcpplibraries.com/boost.optional
// used for optional return values

#include <iostream>
#include "termcolor/termcolor.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <boost/optional.hpp>

int get_even_random_number() {
    int i = std::rand();
    return (i % 2 == 0) ? i : -1;
}

using boost::optional;

optional<int> get_even_random_number1() {
    int i = std::rand();
    return (i % 2 == 0) ? i : optional<int>{};
}

optional<int> get_even_random_number2() {
    int i = std::rand();
    return optional<int>{i % 2 == 0, i};
}

using namespace boost;

optional<int> get_even_random_number3() {
    int i = std::rand();
    return make_optional(i % 2 == 0, i);
}

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Special values to denote optional return values" << termcolor::reset << std::endl;
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        int i = get_even_random_number();
        if (i != -1) {
            std::cout << std::sqrt(static_cast<float>(i)) << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Optional return values with boost::optional" << termcolor::reset << std::endl;
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        optional<int> i = get_even_random_number1();
        if (i) {
            std::cout << std::sqrt(static_cast<float>(*i)) << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Other useful member functions of boost::optional" << termcolor::reset << std::endl;
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        optional<int> i = get_even_random_number2();
        if (i.is_initialized()) {
            std::cout << std::sqrt(static_cast<float>(i.get())) << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Various helper functions of Boost.Optional" << termcolor::reset << std::endl;
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        optional<int> i = get_even_random_number3();
        double d = get_optional_value_or(i, 0);
        std::cout << std::sqrt(d) << '\n';
    }

    // Along with boost/optional/optional_io.hpp, Boost.Optional provides a header file with overloaded stream operators, which let you write objects of type boost::optional to, for example, standard streams.


}