// https://theboostcpplibraries.com/boost.coroutine

#include <boost/coroutine2/all.hpp>
#include <functional>
#include <stdexcept>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::coroutines2;

void cooperative(coroutine<void>::push_type &sink);
void cooperative2(coroutine<int>::push_type &sink, int i);
void cooperative3(coroutine<std::tuple<int, std::string>>::pull_type &source);
void cooperative4(coroutine<void>::push_type &sink);

int main()
{
    std::cout << termcolor::bold << termcolor::underline << "Using coroutines" << termcolor::reset << std::endl;
    {
        coroutine<void>::pull_type source{cooperative};
        std::cout << ", ";
        source();
        std::cout << "!\n";
    }

    std::cout << termcolor::bold << termcolor::underline << "Returning a value from a coroutine" << termcolor::reset << std::endl;
    {
        using std::placeholders::_1;
        coroutine<int>::pull_type source{std::bind(cooperative2, _1, 0)};
        std::cout << source.get() << '\n';
        source();
        std::cout << source.get() << '\n';
        source();
    }

    std::cout << termcolor::bold << termcolor::underline << "Passing two values to a coroutine" << termcolor::reset << std::endl;
    {
        coroutine<std::tuple<int, std::string>>::push_type sink{cooperative3};
        sink(std::make_tuple(0, "aaa"));
        sink(std::make_tuple(1, "bbb"));
        std::cout << "end\n";
    }

    std::cout << termcolor::bold << termcolor::underline << "Coroutines and exceptions" << termcolor::reset << std::endl;
    {
        coroutine<void>::pull_type source{cooperative4};
        try
        {
            source();
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void cooperative(coroutine<void>::push_type &sink)
{
    std::cout << "Hello";
    sink();
    std::cout << "world";
}

void cooperative2(coroutine<int>::push_type &sink, int i)
{
    int j = i;
    sink(++j);
    sink(++j);
    std::cout << "end\n";
}

void cooperative3(coroutine<std::tuple<int, std::string>>::pull_type &source)
{
    auto args = source.get();
    std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';
    source();
    args = source.get();
    std::cout << std::get<0>(args) << " " << std::get<1>(args) << '\n';
}

void cooperative4(coroutine<void>::push_type &sink)
{
    sink();
    throw std::runtime_error("error");
}
