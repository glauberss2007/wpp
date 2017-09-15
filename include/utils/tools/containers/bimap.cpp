// https://theboostcpplibraries.com/boost.bimap
// similar to std::map, but supports looking up values from either side

#include <boost/bimap.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <boost/bimap/multiset_of.hpp>

#include <boost/bimap/unconstrained_set_of.hpp>
#include <boost/bimap/support/lambda.hpp>

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::bimap" << termcolor::reset << std::endl;
    {
        typedef boost::bimap<std::string, int> bimap;
        bimap animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        std::cout << animals.left.count("cat") << '\n';
        std::cout << animals.right.count(8) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing relations" << termcolor::reset << std::endl;
    {
        typedef boost::bimap<std::string, int> bimap;
        bimap animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        for (auto it = animals.begin(); it != animals.end(); ++it)
            std::cout << it->left << " has " << it->right << " legs\n";
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::bimaps::set_of explicitly" << termcolor::reset << std::endl;
    {
        typedef boost::bimap<boost::bimaps::set_of<std::string>,
                boost::bimaps::set_of<int>> bimap;
        bimap animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        std::cout << animals.left.count("spider") << '\n';
        std::cout << animals.right.count(8) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Allowing duplicates with boost::bimaps::multiset_of" << termcolor::reset << std::endl;
    {
        typedef boost::bimap<boost::bimaps::set_of<std::string>,
                boost::bimaps::multiset_of<int>> bimap;
        bimap animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"dog", 4});

        std::cout << animals.left.count("dog") << '\n';
        std::cout << animals.right.count(4) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Disabling one side with boost::bimaps::unconstrained_set_of" << termcolor::reset << std::endl;
    {
        typedef boost::bimap<std::string,
                boost::bimaps::unconstrained_set_of<int>> bimap;
        bimap animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        auto it = animals.left.find("cat");
        animals.left.modify_key(it, boost::bimaps::_key = "dog");

        std::cout << it->first << '\n';
    }


}