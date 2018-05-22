// https://theboostcpplibraries.com/boost.typetraits
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/typeof/std/utility.hpp>
#include <type_traits>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost;

template <typename T>
typename boost::enable_if<std::is_same<T, int>, T>::type create()
{
    return 1;
}

template <typename T>
typename boost::enable_if<std::is_same<T, std::string>, T>::type create()
{
    return "Boost";
}

template <typename T>
void print(typename boost::enable_if<std::is_integral<T>, T>::type i)
{
    std::cout << "Integral: " << i << '\n';
}

template <typename T>
void print(typename boost::enable_if<std::is_floating_point<T>, T>::type f)
{
    std::cout << "Floating point: " << f << '\n';
}

int main() {

    std::cout << termcolor::bold << termcolor::underline << "Determining type categories" << termcolor::reset
              << std::endl;
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << "is_integral<int>::value: " << is_integral<int>::value << '\n';
        std::cout << "is_floating_point<int>::value: " << is_floating_point<int>::value << '\n';
        std::cout << "is_arithmetic<int>::value: " << is_arithmetic<int>::value << '\n';
        std::cout << "is_reference<int>::value: " << is_reference<int>::value << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::true_type and boost::false_type" << termcolor::reset
              << std::endl;
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << "is_same<is_integral<int>::type, true_type>::value: " << is_same<is_integral<int>::type, true_type>::value << '\n';
        std::cout << "is_same<is_floating_point<int>::type, false_type>:: " << is_same<is_floating_point<int>::type, false_type>::value <<
                  '\n';
        std::cout << "is_same<is_arithmetic<int>::type, true_type>::value: " << is_same<is_arithmetic<int>::type, true_type>::value << '\n';
        std::cout << "is_same<is_reference<int>::type, false_type>::value: " << is_same<is_reference<int>::type, false_type>::value << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Checking type properties with Boost.TypeTraits"
              << termcolor::reset << std::endl;
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << "has_plus<int>::value: " << has_plus<int>::value << '\n';
        std::cout << "has_pre_increment<int>::value: " << has_pre_increment<int>::value << '\n';
        std::cout << "has_trivial_copy<int>::value: " << has_trivial_copy<int>::value << '\n';
        std::cout << "has_virtual_destructor<int>::value: " << has_virtual_destructor<int>::value << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Changing type properties with Boost.TypeTraits"
              << termcolor::reset << std::endl;
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << "is_const<add_const<int>::type>::value: " << is_const<add_const<int>::type>::value << '\n';
        std::cout << "is_same<remove_pointer<int *>::type, int>::value: " << is_same<remove_pointer<int *>::type, int>::value << '\n';
        std::cout << "is_same<make_unsigned<int>::type, unsigned int>:: " << is_same<make_unsigned<int>::type, unsigned int>::value <<
                  '\n';
        std::cout << "is_same<add_rvalue_reference<int>::type, int &&>:: " << is_same<add_rvalue_reference<int>::type, int &&>::value <<
                  '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Overloading functions with boost::enable_if on their return value" << termcolor::reset << std::endl;
    {
        std::cout << create<std::string>() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Specializing functions for a group of types with boost::enable_if" << termcolor::reset << std::endl;
    {
        print<short>(1);
        print<long>(2);
        print<double>(3.14);
    }

    std::cout << termcolor::bold << termcolor::underline << "Getting lambda return types" << termcolor::reset << std::endl;
    {

        auto foo = [](int a, char b){ return 0; };

        typedef decltype(foo) foo_type;
        //std::cout << "is_function_pointer< bool(*)(int) >::value" << boost::function_types::is_function_pointer< bool(*)(int) >::value << std::endl;
        std::cout << "function_arity< bool(*)(int) >::value = " << boost::function_types::function_arity< foo_type >::value << std::endl;
        std::cout << typeid(boost::mpl::at_c<boost::function_types::parameter_types<foo_type>,1>::type).name() << ",";
        std::cout << typeid(boost::mpl::at_c<boost::function_types::parameter_types<foo_type>,2>::type).name() << ",";

    }


    return 0;
}
