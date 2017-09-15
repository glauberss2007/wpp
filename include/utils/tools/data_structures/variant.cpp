// https://theboostcpplibraries.com/boost.variant
// can store values of different types

#include <boost/variant.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

struct output : public boost::static_visitor<>
{
    void operator()(double d) const { std::cout << d << '\n'; }
    void operator()(char c) const { std::cout << c << '\n'; }
    void operator()(std::string s) const { std::cout << s << '\n'; }
};

struct output2 : public boost::static_visitor<>
{
    template <typename T>
    void operator()(T t) const { std::cout << t << '\n'; }
};


int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::variant" << termcolor::reset << std::endl;
    {
        boost::variant<double, char, std::string> v;
        v = 3.14;
        v = 'A';
        v = "Boost";
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing values in boost::variant with boost::get()" << termcolor::reset << std::endl;
    {
        boost::variant<double, char, std::string> v;
        v = 3.14;
        std::cout << boost::get<double>(v) << '\n';
        v = 'A';
        std::cout << boost::get<char>(v) << '\n';
        v = "Boost";
        std::cout << boost::get<std::string>(v) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Direct streams of boost::variant on a stream" << termcolor::reset << std::endl;
    {
        boost::variant<double, char, std::string> v;
        v = 3.14;
        std::cout << v << '\n';
        v = 'A';
        std::cout << v << '\n';
        v = "Boost";
        std::cout << v << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a visitor for boost::variant" << termcolor::reset << std::endl;
    {
        boost::variant<double, char, std::string> v;
        v = 3.14;
        boost::apply_visitor(output{}, v);
        v = 'A';
        boost::apply_visitor(output{}, v);
        v = "Boost";
        boost::apply_visitor(output{}, v);
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a visitor with a function template for boost::variant" << termcolor::reset << std::endl;
    {
        boost::variant<double, char, std::string> v;
        v = 3.14;
        boost::apply_visitor(output2{}, v);
        v = 'A';
        boost::apply_visitor(output2{}, v);
        v = "Boost";
        boost::apply_visitor(output2{}, v);
    }

    return 0;
}