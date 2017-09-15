// https://theboostcpplibraries.com/boost.range

#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext.hpp>

#include <boost/range/adaptors.hpp>

#include <boost/range/irange.hpp>
#include <boost/range/istream_range.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <boost/regex.hpp>

#include <array>
#include <deque>
#include <map>

#include <string>
#include <utility>
#include <iterator>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "RANGE ALGORITHMS" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Counting with boost::count()" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a{{0, 1, 0, 1, 0, 1}};
        std::cout << boost::count(a, 0) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Range algorithms related to algorithms from the standard library" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        boost::random_shuffle(a);
        std::cout << "random_shuffle: " << std::endl;
        boost::copy(a, std::ostream_iterator<int>{std::cout, ","});
        std::cout << "\n" << "*boost::max_element(a): " << *boost::max_element(a) << '\n';
        std::cout << "boost::accumulate(a, 0): " << boost::accumulate(a, 0) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Range algorithms without counterparts in the standard library" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        std::cout << std::boolalpha << "boost::is_sorted(a)" << boost::is_sorted(a) << '\n';
        std::deque<int> d;
        boost::push_back(d, a);
        boost::remove_erase(d, 2);
        boost::copy_n(d, 3, std::ostream_iterator<int>{std::cout, ","});
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "RANGE ADAPTORS" << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::underline << "Filtering a range with boost::adaptors::filter()" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a{{0, 5, 2, 1, 3, 4}};
        std::cout << "Array a: " << std::endl;
        boost::copy(boost::adaptors::filter(a, [](int i){ return i > 2; }),
                    std::ostream_iterator<int>{std::cout, ","});
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Using keys(), values() and indirect()" << termcolor::reset << std::endl;
    {
        std::array<int, 3> a{{0, 1, 2}};
        std::map<std::string, int*> m;
        m.insert(std::make_pair("a", &a[0]));
        m.insert(std::make_pair("b", &a[1]));
        m.insert(std::make_pair("c", &a[2]));

        std::cout << "Access keys and values in a container directly and indirectly:" << std::endl;
        boost::copy(boost::adaptors::keys(m),
                    std::ostream_iterator<std::string>{std::cout, ","});
        boost::copy(boost::adaptors::indirect(boost::adaptors::values(m)),
                    std::ostream_iterator<int>{std::cout, ","});
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::adaptors::tokenize() – an adaptor for strings" << termcolor::reset << std::endl;
    {
        std::string s = "The Boost C++ Libraries";
        boost::regex expr{"[\\w+]+"};
        boost::copy(boost::adaptors::tokenize(s, expr, 0,
                                              boost::regex_constants::match_default),
                    std::ostream_iterator<std::string>{std::cout, ","});
    }

    std::cout << termcolor::bold << termcolor::underline << "HELPER CLASSES" << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::underline << "Creating a range for integers with boost::irange()" << termcolor::reset << std::endl;
    {
        boost::integer_range<int> ir = boost::irange(0, 3);
        // range for integers without having to use a container or another data structure
        std::cout << "integer_range<int>" << std::endl;
        boost::copy(ir, std::ostream_iterator<int>{std::cout, ","});
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating a range for an input stream with boost::istream_range()" << termcolor::reset << std::endl;
    {
        //boost::iterator_range<std::istream_iterator<int>> ir = boost::istream_range<int>(std::cin);
        //boost::copy(ir, std::ostream_iterator<int>{std::cout, "\n"});
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating ranges more easily with boost::sub_range()" << termcolor::reset << std::endl;
    {
        std::array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        boost::iterator_range<std::array<int, 6>::iterator> r1 =
                boost::random_shuffle(a);
        boost::sub_range<std::array<int, 6>> r2 =
                boost::random_shuffle(r1);
        boost::copy(r2, std::ostream_iterator<int>{std::cout, ","});
    }

}