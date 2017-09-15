// https://theboostcpplibraries.com/boost.conversion
#include <iostream>
#include "termcolor/termcolor.hpp"
#include <boost/cast.hpp>


struct base1 { virtual ~base1() = default; };
struct base2 { virtual ~base2() = default; };
struct derived : public base1, public base2 {};

int main()
{
    std::cout << termcolor::bold << termcolor::underline << "Down and cross casts with dynamic_cast" << termcolor::reset << std::endl;
    {
        auto downcast = [](base1 *b1)
        {
            derived *d = dynamic_cast<derived*>(b1);
        };

        auto crosscast = [](base1 *b1)
        {
            base2 *b2 = dynamic_cast<base2*>(b1);
        };

        derived *d = new derived;
        downcast(d);

        base1 *b1 = new derived;
        crosscast(b1);
    }

    std::cout << termcolor::bold << termcolor::underline << "Down and cross casts with polymorphic_downcast and polymorphic_cast" << termcolor::reset << std::endl;
    {
        auto downcast = [](base1 *b1)
        {
            derived *d = boost::polymorphic_downcast<derived*>(b1);
        };

        auto crosscast = [](base1 *b1)
        {
            base2 *b2 = boost::polymorphic_cast<base2*>(b1);
        };

        derived *d = new derived;
        downcast(d);

        base1 *b1 = new derived;
        crosscast(b1);
    }

}