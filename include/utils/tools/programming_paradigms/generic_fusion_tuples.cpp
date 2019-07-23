// https://theboostcpplibraries.com/boost.fusion
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/view.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/int.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::fusion;

struct print {
    template<typename T>
    void operator()(const T &t) const {
        std::cout << std::boolalpha << t << '\n';
    }
};

int main() {

    std::cout << termcolor::bold << termcolor::underline << "Processing Fusion tuples" << termcolor::reset
              << std::endl;
    {
        typedef tuple<int, std::string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        std::cout << "get<0>(t): " << get<0>(t) << '\n';
        std::cout << "get<1>(t): " << get<1>(t) << '\n';
        std::cout << "std::boolalpha << get<2>(t): " << std::boolalpha << get<2>(t) << '\n';
        std::cout << "get<3>(t): " << get<3>(t) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Iterating over a tuple with boost::fusion::for_each()"
              << termcolor::reset << std::endl;
    {
        typedef tuple<int, std::string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        for_each(t, print{});
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Filtering a Fusion container with boost::fusion::filter_view" << termcolor::reset << std::endl;
    {
        typedef tuple<int, std::string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        filter_view<tuple_type, boost::is_integral<boost::mpl::arg<1>>> v{t};
        for_each(v, print{});
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing elements in Fusion containers with iterators"
              << termcolor::reset << std::endl;
    {
        typedef tuple<int, std::string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        auto it = begin(t);
        std::cout << *it << '\n';
        auto it2 = advance<boost::mpl::int_<2>>(it);
        std::cout << std::boolalpha << *it2 << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "A heterogeneous vector with boost::fusion::vector"
              << termcolor::reset << std::endl;
    {
        typedef vector<int, std::string, bool, double> vector_type;
        vector_type v{10, "Boost", true, 3.14};
        std::cout << at<boost::mpl::int_<0>>(v) << '\n';

        auto v2 = push_back(v, 'X');
        std::cout << size(v) << '\n';
        std::cout << size(v2) << '\n';
        std::cout << back(v2) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "A heterogeneous map with boost::fusion::map"
              << termcolor::reset << std::endl;
    {
        auto m = make_map<int, std::string, bool, double>("Boost", 10, 3.14, true);
        if (has_key<std::string>(m)) {
            std::cout << at_key<std::string>(m) << '\n';
        }
        auto m2 = erase_key<std::string>(m);
        auto m3 = push_back(m2, make_pair<float>('X'));
        std::cout << std::boolalpha << has_key<std::string>(m3) << '\n';
    }

    return 0;
}
