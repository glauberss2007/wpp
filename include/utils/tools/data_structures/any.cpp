// https://theboostcpplibraries.com/boost.any
// provides the class boost::any which, like JavaScript variables, can store arbitrary types of information

#include <iostream>
#include "termcolor/termcolor.hpp"
#include <string>
#include <typeinfo>

#include <boost/any.hpp>

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::any" << termcolor::reset << std::endl;
    {
        boost::any a = 1;
        std::cout << "boost::any_cast<int>(a) : " << boost::any_cast<int>(a) << std::endl;
        a = 3.14;
        std::cout << "boost::any_cast<double>(a) : " << boost::any_cast<double>(a) << std::endl;
        a = true;
        std::cout << "boost::any_cast<bool>(a) : " << boost::any_cast<bool>(a) << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Storing a string in boost::any" << termcolor::reset << std::endl;
    {
        boost::any a = std::string{"Boost"};
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing values with boost::any_cast" << termcolor::reset << std::endl;
    {
        boost::any a = 1;
        std::cout << boost::any_cast<int>(a) << '\n';
        a = 3.14;
        std::cout << boost::any_cast<double>(a) << '\n';
        a = true;
        std::cout << std::boolalpha << boost::any_cast<bool>(a) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::bad_any_cast in case of an error" << termcolor::reset << std::endl;
    {
        try
        {
            boost::any a = 1;
            std::cout << boost::any_cast<float>(a) << '\n';
        }
        catch (boost::bad_any_cast &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Checking type of currently stored value" << termcolor::reset << std::endl;
    {
        boost::any a = 1;
        if (!a.empty())
        {
            const std::type_info &ti = a.type();
            std::cout << ti.name() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing values through a pointer" << termcolor::reset << std::endl;
    {
        boost::any a = 1;
        int *i = boost::any_cast<int>(&a);
        std::cout << *i << '\n';
    }
}