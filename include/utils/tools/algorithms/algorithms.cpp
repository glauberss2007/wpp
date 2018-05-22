// https://theboostcpplibraries.com/boost.algorithm

#include <boost/algorithm/cxx11/one_of.hpp>

#include <boost/algorithm/cxx11/iota.hpp>
#include <boost/algorithm/cxx11/is_sorted.hpp>
#include <boost/algorithm/cxx11/copy_if.hpp>

#include <boost/algorithm/cxx14/equal.hpp>
#include <boost/algorithm/cxx14/mismatch.hpp>

#include <boost/algorithm/hex.hpp>

#include <array>
#include <vector>
#include <iterator>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::algorithm;
using namespace std;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Testing for exactly one value with boost::algorithm::one_of_equal()" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a = {0, 5, 2, 1, 4, 3};
        auto predicate = [](int i) { return i == 4; };
        std::cout.setf(std::ios::boolalpha);
        std::cout << "one_of(a, predicate): " << one_of(a, predicate) << '\n';
        std::cout << "one_of(a.begin(), a.end(), predicate): " << one_of(a.begin(), a.end(), predicate) << '\n';
        std::cout << "one_of_equal(a.begin(), a.end(), 4): " << one_of_equal(a.begin(), a.end(), 4) << '\n';
        std::cout << "one_of_equal(a, 4): " << one_of_equal(a, 4) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "More variants of C++11 algorithms" << termcolor::reset << std::endl;
    {
        std::vector<int> v;
        // generates sequentially increasing numbers
        iota_n(std::back_inserter(v), 10, 5);
        std::cout.setf(std::ios::boolalpha);
        std::cout << is_increasing(v) << '\n';
        std::ostream_iterator<int> out{std::cout, ","};
        copy_until(v, out, [](int i) { return i > 12; });
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "C++14 algorithms from Boost.Algorithm" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2};
        std::vector<int> w{1, 2, 3};
        std::cout.setf(std::ios::boolalpha);
        std::cout << boost::algorithm::equal(v.begin(), v.end(), w.begin(), w.end()) << '\n';
        auto pair = boost::algorithm::mismatch(v.begin(), v.end(), w.begin(), w.end());
        if (pair.first != v.end()) {
            std::cout << *pair.first << '\n';
        }
        if (pair.second != w.end()) {
            std::cout << *pair.second << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::algorithm::hex() and boost::algorithm::unhex()" << termcolor::reset << std::endl;
    {
        // convert characters to hexadecimal values
        std::vector<char> v{'C', '+', '+'};
        hex(v, std::ostream_iterator<char>{std::cout, ""});
        std::cout << '\n';

        std::string s = "C++";
        std::cout << hex(s) << '\n';

        std::vector<char> w{'4', '3', '2', 'b', '2', 'b'};
        unhex(w, std::ostream_iterator<char>{std::cout, ""});
        std::cout << '\n';

        std::string t = "432b2b";
        std::cout << unhex(t) << '\n';
    }

    // http://www.boost.org/doc/libs/1_65_1/libs/algorithm/doc/html/index.html
    // Other algorithms
        // Searching Algorithms
            // Boyer-Moore Search
            // Boyer-Moore-Horspool Search
            // Knuth-Morris-Pratt Search
        // STL-like
            // clamp
            // gather
            // hex
            // is_palindrome
            // is_partitioned_until
            // minmax
            // minmax_element

}