// https://theboostcpplibraries.com/boost.container
// The implementation is platform independent.
// Boost.Container offers containers the standard library doesn’t provide.
// The containers from Boost.Container support incomplete types and can be used to define recursive containers.

#include <iostream>
#include "termcolor/termcolor.hpp"

#include <boost/container/vector.hpp>
#include <boost/container/stable_vector.hpp>

using namespace boost::container;

struct animal
{
    vector<animal> children;
};

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Recursive containers with Boost.Container" << termcolor::reset << std::endl;
    {
        animal parent, child1, child2;
        parent.children.push_back(child1);
        parent.children.push_back(child2);
    }
    std::cout << termcolor::bold << termcolor::underline << "Using boost::container::stable_vector" << termcolor::reset << std::endl;
    {
        stable_vector<int> v(2, 1);
        int &i = v[1];
        v.erase(v.begin());
        std::cout << i << '\n';
    }
    // boost::container::flat_set and boost::container::flat_map resemble std::set and std::map. However they are implemented as sorted vectors, not as a tree. This allows faster lookups and iterations, but inserting and removing elements is more expensive

    // boost::container::slist is a singly linked list. It is similar to std::forward_list, which was added to the standard library with C++11. boost::container::slist provides a member function size(), which is missing in std::forward_list

}