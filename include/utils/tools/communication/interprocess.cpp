// https://theboostcpplibraries.com/boost.interprocess-shared-memory

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

using namespace boost::interprocess;

#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Creating shared memory" << termcolor::reset
              << std::endl;
    {
        shared_memory_object shdmem{open_or_create, "Boost", read_write};
        shdmem.truncate(1024);
        std::cout << shdmem.get_name() << '\n';
        offset_t size;
        if (shdmem.get_size(size))
            std::cout << size << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Mapping shared memory into the address space of a process" << termcolor::reset << std::endl;
    {
        shared_memory_object shdmem{open_or_create, "Boost", read_write};
        shdmem.truncate(1024);
        mapped_region region{shdmem, read_write};
        std::cout << std::hex << region.get_address() << '\n';
        std::cout << std::dec << region.get_size() << '\n';
        mapped_region region2{shdmem, read_only};
        std::cout << std::hex << region2.get_address() << '\n';
        std::cout << std::dec << region2.get_size() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Writing and reading a number in shared memory" << termcolor::reset << std::endl;
    {
        shared_memory_object shdmem{open_or_create, "Boost", read_write};
        shdmem.truncate(1024);
        mapped_region region{shdmem, read_write};
        int *i1 = static_cast<int*>(region.get_address());
        *i1 = 99;
        mapped_region region2{shdmem, read_only};
        int *i2 = static_cast<int*>(region2.get_address());
        std::cout << *i2 << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Deleting shared memory" << termcolor::reset << std::endl;
    {
        bool removed = shared_memory_object::remove("Boost");
        std::cout << std::boolalpha << removed << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using managed shared memory" << termcolor::reset << std::endl;
    {
        shared_memory_object::remove("Boost");
        managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
        int *i = managed_shm.construct<int>("Integer")(99);
        std::cout << *i << '\n';
        std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
        if (p.first)
            std::cout << *p.first << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating arrays in managed shared memory" << termcolor::reset << std::endl;
    {
        shared_memory_object::remove("Boost");
        managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
        int *i = managed_shm.construct<int>("Integer")[10](99);
        std::cout << *i << '\n';
        std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
        if (p.first)
        {
            std::cout << *p.first << '\n';
            std::cout << p.second << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "An exception of type boost::interprocess::bad_alloc" << termcolor::reset << std::endl;
    {
        try
        {
            shared_memory_object::remove("Boost");
            managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
            int *i = managed_shm.construct<int>("Integer")[4096](99);
        }
        catch (boost::interprocess::bad_alloc &ex)
        {
            std::cerr << ex.what() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Removing objects in shared memory" << termcolor::reset << std::endl;
    {
        shared_memory_object::remove("Boost");
        managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
        int *i = managed_shm.find_or_construct<int>("Integer")(99);
        std::cout << *i << '\n';
        managed_shm.destroy<int>("Integer");
        std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");
        std::cout << p.first << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Putting strings into shared memory" << termcolor::reset << std::endl;
    {
        shared_memory_object::remove("Boost");
        managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
        typedef allocator<char,
                managed_shared_memory::segment_manager> CharAllocator;
        typedef basic_string<char, std::char_traits<char>, CharAllocator> string;
        string *s = managed_shm.find_or_construct<string>("String")("Hello!",
                                                                    managed_shm.get_segment_manager());
        s->insert(5, ", world");
        std::cout << *s << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Atomic access on a managed shared memory" << termcolor::reset << std::endl;
    {
        auto construct_objects = [](managed_shared_memory &managed_shm)
        {
            managed_shm.construct<int>("Integer")(99);
            managed_shm.construct<float>("Float")(3.14);
        };

        shared_memory_object::remove("Boost");
        managed_shared_memory managed_shm{open_or_create, "Boost", 1024};
        auto atomic_construct = std::bind(construct_objects,
                                          std::ref(managed_shm));
        managed_shm.atomic_func(atomic_construct);
        std::cout << *managed_shm.find<int>("Integer").first << '\n';
        std::cout << *managed_shm.find<float>("Float").first << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a named mutex with boost::interprocess::named_mutex" << termcolor::reset << std::endl;
    {
        managed_shared_memory managed_shm{open_or_create, "shm", 1024};
        int *i = managed_shm.find_or_construct<int>("Integer")();
        named_mutex named_mtx{open_or_create, "mtx"};
        named_mtx.lock();
        ++(*i);
        std::cout << *i << '\n';
        named_mtx.unlock();
    }

    std::cout << termcolor::bold << termcolor::underline << "Using an anonymous mutex with interprocess_mutex" << termcolor::reset << std::endl;
    {
        managed_shared_memory managed_shm{open_or_create, "shm", 1024};
        int *i = managed_shm.find_or_construct<int>("Integer")();
        interprocess_mutex *mtx =
                managed_shm.find_or_construct<interprocess_mutex>("mtx")();
        mtx->lock();
        ++(*i);
        std::cout << *i << '\n';
        mtx->unlock();
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a named condition with boost::interprocess::named_condition" << termcolor::reset << std::endl;
    {
        managed_shared_memory managed_shm{open_or_create, "shm", 1024};
        int *i = managed_shm.find_or_construct<int>("Integer")(0);
        named_mutex named_mtx{open_or_create, "mtx"};
        named_condition named_cnd{open_or_create, "cnd"};
        scoped_lock<named_mutex> lock{named_mtx};
        while (*i < 10)
        {
            if (*i % 2 == 0)
            {
                ++(*i);
                named_cnd.notify_all();
                named_cnd.wait(lock);
            }
            else
            {
                std::cout << *i << std::endl;
                ++(*i);
                named_cnd.notify_all();
                named_cnd.wait(lock);
            }
        }
        named_cnd.notify_all();
        shared_memory_object::remove("shm");
        named_mutex::remove("mtx");
        named_condition::remove("cnd");
    }

    std::cout << termcolor::bold << termcolor::underline << "Using an anonymous condition with interprocess_condition" << termcolor::reset << std::endl;
    {
        managed_shared_memory managed_shm{open_or_create, "shm", 1024};
        int *i = managed_shm.find_or_construct<int>("Integer")(0);
        interprocess_mutex *mtx =
                managed_shm.find_or_construct<interprocess_mutex>("mtx")();
        interprocess_condition *cnd =
                managed_shm.find_or_construct<interprocess_condition>("cnd")();
        scoped_lock<interprocess_mutex> lock{*mtx};
        while (*i < 10)
        {
            if (*i % 2 == 0)
            {
                ++(*i);
                cnd->notify_all();
                cnd->wait(lock);
            }
            else
            {
                std::cout << *i << std::endl;
                ++(*i);
                cnd->notify_all();
                cnd->wait(lock);
            }
        }
        cnd->notify_all();
        shared_memory_object::remove("shm");
    }



}