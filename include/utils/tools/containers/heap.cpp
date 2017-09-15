// https://theboostcpplibraries.com/boost.heap
// differ from std::priority_queue by supporting more functions

#include <boost/heap/priority_queue.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <boost/heap/binomial_heap.hpp>

// Boost.Heap provides additional priority queues whose member functions mainly differ in their runtime complexity. For example, you can use the class boost::heap::fibonacci_heap if you want the member function push() to have a constant runtime complexity. The documentation on Boost.Heap provides a table with an overview of the runtime complexities of the various classes and functions.

using namespace boost::heap;

int main() {
    // In general this class behaves like std::priority_queue, except it allows you to iterate over elements
    std::cout << termcolor::bold << termcolor::underline << "Using boost::heap::priority_queue" << termcolor::reset << std::endl;
    {
        priority_queue<int> pq;
        pq.push(2);
        pq.push(3);
        pq.push(1);

        for (int i : pq) {
            std::cout << "i : " << i << std::endl;
        }

        priority_queue<int> pq2;
        pq2.push(4);
        std::cout << std::boolalpha << "(pq > pq2): " << (pq > pq2) << std::endl;
    }

    // In addition to allowing you to iterate over elements in priority order, it also lets you merge priority queues
    std::cout << termcolor::bold << termcolor::underline << "Using boost::heap::binomial_heap" << termcolor::reset << std::endl;
    {
        binomial_heap<int> bh;
        bh.push(2);
        bh.push(3);
        bh.push(1);

        binomial_heap<int> bh2;
        bh2.push(4);
        bh.merge(bh2);

        for (auto it = bh.ordered_begin(); it != bh.ordered_end(); ++it) {
            std::cout << "*it : " << *it << std::endl;
        }
        std::cout << std::boolalpha << "bh2.empty(): " << bh2.empty() << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Changing elements in boost::heap::binomial_heap" << termcolor::reset << std::endl;
    {
        binomial_heap<int> bh;
        auto handle = bh.push(2);
        bh.push(3);
        bh.push(1);

        bh.update(handle, 4);
        std::cout << "bh.top() : " << bh.top() << std::endl;
    }
}