// https://theboostcpplibraries.com/boost.tribool
// while bool can distinguish two states, boost::logic::tribool handles three.

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::logic;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Three states of boost::logic::tribool" << termcolor::reset << std::endl;
    {
        tribool b;
        std::cout << std::boolalpha << b << '\n';

        b = true;
        b = false;
        b = indeterminate;
        if (b)
            ;
        else if (!b)
            ;
        else
            std::cout << "indeterminate\n";
    }

    std::cout << termcolor::bold << termcolor::underline << "Logical operators with boost::logic::tribool" << termcolor::reset << std::endl;
    {
        std::cout.setf(std::ios::boolalpha);

        tribool b1 = true;
        std::cout << (b1 || indeterminate) << '\n';
        std::cout << (b1 && indeterminate) << '\n';

        tribool b2 = false;
        std::cout << (b2 || indeterminate) << '\n';
        std::cout << (b2 && indeterminate) << '\n';

        tribool b3 = indeterminate;
        std::cout << (b3 || b3) << '\n';
        std::cout << (b3 && b3) << '\n';
    }
    return 0;
}