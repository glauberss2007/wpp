// https://theboostcpplibraries.com/boost.circularbuffer
// capacity of the circular buffer is constant and set by you
// you can call push_back() as often as you like

#include <boost/circular_buffer.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main()
{
    std::cout << termcolor::bold << termcolor::underline << "Using boost::circular_buffer" << termcolor::reset << std::endl;
    {
        typedef boost::circular_buffer<int> circular_buffer;
        circular_buffer cb{3};

        std::cout << "cb.capacity() : " << cb.capacity() << std::endl;
        std::cout << "cb.size() : " << cb.size() << std::endl;

        cb.push_back(0);
        cb.push_back(1);
        cb.push_back(2);

        std::cout << "cb.size() : " << cb.size() << std::endl;

        cb.push_back(3);
        cb.push_back(4);
        cb.push_back(5);

        std::cout << "cb.size() : " << cb.size() << std::endl;

        for (int i : cb) {
            std::cout << "i : " << i << std::endl;
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Various member functions of boost::circular_buffer" << termcolor::reset << std::endl;
    {
        typedef boost::circular_buffer<int> circular_buffer;
        circular_buffer cb{3};

        cb.push_back(0);
        cb.push_back(1);
        cb.push_back(2);
        cb.push_back(3);

        // true if the beginning of the circular buffer is at the lowest memory address
        std::cout << std::boolalpha << "cb.is_linearized(): " << cb.is_linearized() << '\n';

        // Both array_one() and array_two() return a std::pair whose first element is a pointer to the corresponding array and whose second element is the size
        circular_buffer::array_range ar1, ar2;

        // array_one() accesses the array at the beginning of the circular buffer, and array_two() accesses the array at the end of the buffer
        ar1 = cb.array_one();
        ar2 = cb.array_two();

        std::cout << ar1.second << ";" << ar2.second << '\n';

        for (int i : cb)
            std::cout << i << '\n';

        // force a rearrangement of the elements by calling linearize()
        cb.linearize();

        ar1 = cb.array_one();
        ar2 = cb.array_two();
        std::cout << ar1.second << ";" << ar2.second << '\n';
    }
}