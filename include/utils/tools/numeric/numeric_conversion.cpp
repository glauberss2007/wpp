// https://theboostcpplibraries.com/boost.accumulators
#include <boost/numeric/conversion/cast.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Implicit conversion from int to short"
              << termcolor::reset << std::endl;
    {
        int i = 0x10000;
        short s = i;
        std::cout << "s: " << s << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Overflow detection with boost::numeric_cast" << termcolor::reset << std::endl;
    {
        try
        {
            int i = 0x10000;
            short s = boost::numeric_cast<short>(i);
            std::cout << "s: " << s << '\n';
        }
        catch (boost::numeric::bad_numeric_cast &e)
        {
            std::cerr << "e.what(): " << e.what() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Overflow detection for negative numbers" << termcolor::reset << std::endl;
    {
        try
        {
            int i = -0x10000;
            short s = boost::numeric_cast<short>(i);
            std::cout << "s: " << s << '\n';
        }
        catch (boost::numeric::negative_overflow &e)
        {
            std::cerr << "e.what(): " << e.what() << '\n';
        }
    }
}
