#include <boost/format.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <string>

struct animal
{
    std::string name;
    int legs;
};

std::ostream &operator<<(std::ostream &os, const animal &a)
{
    return os << a.name << ',' << a.legs;
}


//https://theboostcpplibraries.com/boost.format
int main() {
    std::cout << termcolor::bold << termcolor::underline << "Formatted streams with boost::format" << termcolor::reset << std::endl;
    {
        std::cout << boost::format{"%1%.%2%.%3%"} % 12 % 5 % 2014 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "Numbered placeholders with boost::format" << termcolor::reset << std::endl;
    {
        std::cout << boost::format{"%2%/%1%/%3%"} % 12 % 5 % 2014 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "Using manipulators with boost::io::group()" << termcolor::reset << std::endl;
    {
        // uses the manipulator std::showpos() on the value that will be associated with “%1%”
        std::cout << boost::format{"%1% %2% %1%"} %
                     boost::io::group(std::showpos, 1) % 2 << '\n';
    }
    // http://www.boost.org/libs/format/doc/format.html#printf_directives
    std::cout << termcolor::bold << termcolor::underline << "Placeholders with special characters" << termcolor::reset << std::endl;
    {
        // the first instance of the placeholder “%1%” is replaced with “%|1$+|”
        std::cout << boost::format{"%|1$+| %2% %1%"} % 1 % 2 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "boost::io::format_error in case of an error" << termcolor::reset << std::endl;
    {
        try
        {
            std::cout << boost::format{"%|+| %2% %1%"} % 1 % 2 << '\n';
        }
        catch (boost::io::format_error &ex)
        {
            std::cout << ex.what() << '\n';
        }
    }
    std::cout << termcolor::bold << termcolor::underline << "Placeholders without numbers" << termcolor::reset << std::endl;
    {
        std::cout << boost::format{"%|+| %|| %||"} % 1 % 2 % 1 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "boost::format with the syntax used from std::printf()" << termcolor::reset << std::endl;
    {
        std::cout << boost::format{"%+d %d %d"} % 1 % 2 % 1 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "boost::format with seemingly invalid placeholders" << termcolor::reset << std::endl;
    {
        std::cout << boost::format{"%+s %s %s"} % 1 % 2 % 1 << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "boost::format with user-defined type" << termcolor::reset << std::endl;
    {
        animal a{"cat", 4};
        std::cout << boost::format{"%1%"} % a << '\n';
    }
    return 0;
}