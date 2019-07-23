// https://theboostcpplibraries.com/boost.operators
#include <boost/operators.hpp>
#include <string>
#include <utility>
#include <iostream>
#include "termcolor/termcolor.hpp"



struct animal
        // If two objects can be equal, also use boost::partially_ordered
        // see list at : http://www.boost.org/doc/libs/1_65_1/libs/utility/operators.htm
        : public boost::less_than_comparable<animal> {
    std::string name;
    int legs;

    animal(std::string n, int l) : name{std::move(n)}, legs{l} {}

    bool operator<(const animal &a) const { return legs < a.legs; }
};

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Greater-than operator with boost::less_than_comparable"
              << termcolor::reset << std::endl;
    {
        animal a1{"cat", 4};
        animal a2{"spider", 8};
        std::cout << std::boolalpha << "(a2 > a1): " << (a2 > a1) << '\n';
    }
}
