// https://theboostcpplibraries.com/boost.multiarray
// arrays with multiple dimensions
// can be used like containers from the standard library

// Unlike containers from the standard library, operator[] checks whether an index is valid. If an index is not valid, the program exits with std::abort(). If you don’t want the validity of indexes to be checked, define the macro BOOST_DISABLE_ASSERTS before you include boost/multi_array.hpp.

#include <boost/multi_array.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <algorithm>
#include <cstring>

int main() {
    std::cout << termcolor::bold << termcolor::underline << "One-dimensional array with boost::multi_array" << termcolor::reset << std::endl;
    {
        // second parameter determines how many dimensions
        // boost::extents sets dimension sizes
        boost::multi_array<char, 1> a{boost::extents[6]};

        a[0] = 'B';
        a[1] = 'o';
        a[2] = 'o';
        a[3] = 's';
        a[4] = 't';
        a[5] = '\0';

        // origin() returns a pointer to the first element
        std::cout << "a.origin(): " << a.origin() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Views and subarrays of a two-dimensional array" << termcolor::reset << std::endl;
    {
        boost::multi_array<char, 2> a{boost::extents[2][6]};

        // lets you access a part of an array and treat that part as though it were a separate array
        typedef boost::multi_array<char, 2>::array_view<1>::type array_view;
        typedef boost::multi_array_types::index_range range;
        array_view view = a[boost::indices[0][range{0, 5}]];

        std::memcpy(view.origin(), "tsooB", 6);
        std::reverse(view.begin(), view.end());

        std::cout << "view.origin(): " << view.origin() << '\n';

        boost::multi_array<char, 2>::reference subarray = a[1];
        std::memcpy(subarray.origin(), "C++", 4);

        std::cout << "subarray.origin(): " << subarray.origin() << '\n';
    }
    std::cout << termcolor::bold << termcolor::underline << "Wrapping a C array with boost::multi_array_ref" << termcolor::reset << std::endl;
    {
        char c[12] =
                {
                        't', 's', 'o', 'o', 'B', '\0',
                        'C', '+', '+', '\0', '\0', '\0'
                };

        boost::multi_array_ref<char, 2> a{c, boost::extents[2][6]};

        typedef boost::multi_array<char, 2>::array_view<1>::type array_view;
        typedef boost::multi_array_types::index_range range;
        array_view view = a[boost::indices[0][range{0, 5}]];

        std::reverse(view.begin(), view.end());
        std::cout << "view.origin(): " << view.origin() << '\n';

        boost::multi_array<char, 2>::reference subarray = a[1];
        std::cout << "subarray.origin(): " << subarray.origin() << '\n';
    }
}