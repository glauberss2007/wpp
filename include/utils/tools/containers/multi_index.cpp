// https://theboostcpplibraries.com/boost.multiindex
// containers that support an arbitrary number of interfaces

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::multi_index;

struct animal {
    std::string name;
    int legs;
};

typedef multi_index_container<
        animal,
        indexed_by<
                hashed_non_unique<
                        member<
                                animal, std::string, &animal::name
                        >
                >,
                hashed_non_unique<
                        member<
                                animal, int, &animal::legs
                        >
                >
        >
> animal_multi;

typedef multi_index_container<
        animal,
        indexed_by<
                hashed_non_unique<
                        member<
                                animal, std::string, &animal::name
                        >
                >,
                hashed_unique<
                        member<
                                animal, int, &animal::legs
                        >
                >
        >
> animal_multi2;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::multi_index::multi_index_container" << termcolor::reset << std::endl;
    {
        animal_multi animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        std::cout << animals.count("cat") << '\n';

        const animal_multi::nth_index<1>::type &legs_index = animals.get<1>();
        std::cout << legs_index.count(8) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Changing elements in a MultiIndex container with modify()" << termcolor::reset << std::endl;
    {
        animal_multi animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        auto &legs_index = animals.get<1>();
        auto it = legs_index.find(4);
        legs_index.modify(it, [](animal &a){ a.name = "dog"; });

        std::cout << animals.count("dog") << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "A MultiIndex container with boost::multi_index::hashed_unique" << termcolor::reset << std::endl;
    {
        animal_multi2 animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"dog", 4});

        auto &legs_index = animals.get<1>();
        std::cout << legs_index.count(4) << '\n';
    }
}