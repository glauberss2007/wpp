#include <boost/phoenix/phoenix.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "termcolor/termcolor.hpp"

bool is_odd(int i) { return i % 2 == 1; }

struct is_odd_impl
{
    typedef bool result_type;

    template <typename T>
    bool operator()(T t) const { return t % 2 == 1; }
};

boost::phoenix::function<is_odd_impl> is_odd_obj;

bool is_odd_function(int i) { return i % 2 == 1; }

BOOST_PHOENIX_ADAPT_FUNCTION(bool, is_odd_phoenix, is_odd_function, 1)


int main() {
    std::cout << termcolor::bold << termcolor::underline << "Predicates as global function, lambda function, and Phoenix function"
              << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        std::cout << std::count_if(v.begin(), v.end(), is_odd) << '\n';

        auto lambda = [](int i){ return i % 2 == 1; };
        std::cout << std::count_if(v.begin(), v.end(), lambda) << '\n';

        using namespace boost::phoenix::placeholders;
        auto phoenix = arg1 % 2 == 1;
        std::cout << std::count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Phoenix function versus lambda function" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        auto lambda = [](int i){ return i % 2 == 1; };
        std::cout << std::count_if(v.begin(), v.end(), lambda) << '\n';

        std::vector<long> v2;
        v2.insert(v2.begin(), v.begin(), v.end());

        using namespace boost::phoenix::placeholders;
        auto phoenix = arg1 % 2 == 1;
        std::cout << std::count_if(v.begin(), v.end(), phoenix) << '\n';
        std::cout << std::count_if(v2.begin(), v2.end(), phoenix) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Phoenix functions as deferred C++ code" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix::placeholders;
        auto phoenix = arg1 > 2 && arg1 % 2 == 1;
        std::cout << std::count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Explicit Phoenix types" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix;
        using namespace boost::phoenix::placeholders;
        auto phoenix = arg1 > val(2) && arg1 % val(2) == val(1);
        std::cout << std::count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::phoenix::placeholders::arg1 and boost::phoenix::val()" << termcolor::reset << std::endl;
    {
        using namespace boost::phoenix::placeholders;
        std::cout << arg1(1, 2, 3, 4, 5) << '\n';

        auto v = boost::phoenix::val(2);
        std::cout << v() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating your own Phoenix functions" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix::placeholders;
        std::cout << std::count_if(v.begin(), v.end(), is_odd_obj(arg1)) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Transforming free-standing functions into Phoenix functions" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix::placeholders;
        std::cout << std::count_if(v.begin(), v.end(), is_odd_phoenix(arg1)) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Phoenix functions with boost::phoenix::bind()" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix;
        using namespace boost::phoenix::placeholders;
        std::cout << std::count_if(v.begin(), v.end(), bind(is_odd, arg1)) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Arbitrarily complex Phoenix functions" << termcolor::reset << std::endl;
    {
        std::vector<int> v{1, 2, 3, 4, 5};

        using namespace boost::phoenix;
        using namespace boost::phoenix::placeholders;
        int count = 0;
        std::for_each(v.begin(), v.end(), if_(arg1 > 2 && arg1 % 2 == 1)
        [
                ++ref(count)
        ]);
        std::cout << count << '\n';
    }

    return 0;
}
