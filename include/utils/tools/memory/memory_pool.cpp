#include <iostream>
#include "termcolor/termcolor.hpp"
#include <boost/pool/object_pool.hpp>

#include <boost/pool/singleton_pool.hpp>

#include <boost/pool/pool_alloc.hpp>
#include <vector>

#define BOOST_POOL_NO_MT
#include <boost/pool/pool_alloc.hpp>
#include <list>

struct int_pool {};
typedef boost::singleton_pool<int_pool, sizeof(int)> singleton_int_pool;

// https://theboostcpplibraries.com/boost.pool
int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::object_pool" << termcolor::reset << std::endl;
    {
        boost::object_pool<int> pool;

        int *i = pool.malloc();
        *i = 1;

        int *j = pool.construct(2);

        pool.destroy(i);
        pool.destroy(j);
    }
    std::cout << termcolor::bold << termcolor::underline << "Changing the segment size with boost::object_pool" << termcolor::reset << std::endl;
    {
        boost::object_pool<int> pool{32, 0};
        pool.construct();
        std::cout << pool.get_next_size() << '\n';
        pool.set_next_size(8);
    }
    std::cout << termcolor::bold << termcolor::underline << "Using boost::singleton_pool" << termcolor::reset << std::endl;
    {
        int *i = static_cast<int*>(singleton_int_pool::malloc());
        *i = 1;

        int *j = static_cast<int*>(singleton_int_pool::ordered_malloc(10));
        j[9] = 2;

        singleton_int_pool::release_memory();
        singleton_int_pool::purge_memory();
    }
    std::cout << termcolor::bold << termcolor::underline << "Using boost::pool_allocator" << termcolor::reset << std::endl;
    {
        std::vector<int, boost::pool_allocator<int>> v;
        for (int i = 0; i < 1000; ++i)
            v.push_back(i);

        v.clear();
        boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::
        purge_memory();
    }
    std::cout << termcolor::bold << termcolor::underline << "Using boost::fast_pool_allocator" << termcolor::reset << std::endl;
    {
        typedef boost::fast_pool_allocator<int,
                boost::default_user_allocator_new_delete,
                boost::details::pool::default_mutex,
                64, 128> allocator;

        std::list<int, allocator> l;
        for (int i = 0; i < 1000; ++i)
            l.push_back(i);

        l.clear();
        boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(int)>::
        purge_memory();
    }
    return 0;
}