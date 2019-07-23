// https://theboostcpplibraries.com/boost.range

#include <array>
#include <deque>
#include <map>
#include <string>
#include <utility>
#include <iterator>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include "utils/stl_shortcuts.h"
#include "utils/container_overloads.h"
#include "utils/container_utils.h"

int main() {
    using namespace utils;

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Shortcuts for STL algorithms" << termcolor::reset << std::endl;
    {
        std::cout << termcolor::bold << termcolor::underline << "Creating vector" << termcolor::reset << std::endl;
        std::cout << "vector<int> a = perm(10);" << std::endl;
        vector<int> a = perm(10);
        std::cout << "a: " << a << std::endl;

        std::cout << termcolor::bold << termcolor::underline << "Sorting" << termcolor::reset << std::endl;
        {
            std::cout << "partial_sort(a,a.begin()+5);" << std::endl;
            partial_sort(a,a.begin()+5);
            std::cout << "a: " << a << std::endl;
            std::cout << "sort(a);" << std::endl;
            sort(a);
            std::cout << "a: " << a << std::endl;
            std::cout << std::boolalpha << "is_sorted(a): " << is_sorted(a) << '\n';
            std::cout << std::boolalpha << "binary_search(a,3): " << binary_search(a,3) << '\n';
            std::cout << std::boolalpha << "lower_bound(a,3)-a.begin(): " << lower_bound(a,3)-a.begin() << '\n';

        }

        std::cout << termcolor::bold << termcolor::underline << "Non-modifying sequence operations" << termcolor::reset << std::endl;
        {
            std::cout << "count(a, 0): " << count(a, 0) << '\n';
            std::cout << "find(a, 1)-a.begin(): " << find(a, 1)-a.begin() << '\n';
            std::cout << "*max_element(a): " << *max_element(a) << '\n';
            std::cout << "max_element(a)-a.begin(): " << max_element(a)-a.begin() << '\n';
            std::cout << "accumulate(a, 0): " << accumulate(a, 0) << '\n';

        }

        std::cout << termcolor::bold << termcolor::underline << "Modifying sequence operationsry" << termcolor::reset << std::endl;
        {
            std::cout << "random_shuffle(a);" << std::endl;
            random_shuffle(a);
            std::cout << "a: " << a << std::endl;
            std::cout << "std::deque<int> d;" << std::endl;
            std::deque<int> d;
            std::cout << "push_back(d, a);" << std::endl;
            push_back(d, a);
            std::cout << "remove_erase(d, 2);" << std::endl;
            remove_erase(d, 2);
            std::cout << "a: " << a << std::endl;
        }

    }



}