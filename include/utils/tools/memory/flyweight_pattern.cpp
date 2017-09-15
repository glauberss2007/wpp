// https://theboostcpplibraries.com/boost.flyweight
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <string>
#include <vector>
#include <utility>

#include <boost/flyweight.hpp>
#include <boost/flyweight/set_factory.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/no_tracking.hpp>


struct person_ {
    int id_;
    std::string city_;
};

using namespace boost::flyweights;

struct person {
    int id_;
    flyweight<std::string> city_;

    person(int id, std::string city) : id_{id}, city_{std::move(city)} {}
};

struct located_person {
    int id_;
    flyweight<std::string> city_;
    flyweight<std::string> country_;

    located_person(int id, std::string city, std::string country)
            : id_{id}, city_{std::move(city)}, country_{std::move(country)} {}
};

struct city {};
struct country {};

struct tagged_person {
    int id_;
    flyweight<std::string, tag<city>> city_;
    flyweight<std::string, tag<country>> country_;

    tagged_person(int id, std::string city, std::string country)
            : id_{id}, city_{std::move(city)}, country_{std::move(country)} {}
};

struct templated_person {
    int id_;
    flyweight<std::string, set_factory<>, no_locking, no_tracking> city_;
    // boost::flyweights::set_factory tells Boost.Flyweight to use a sorted container
    // With boost::flyweights::no_locking, support for multithreading is deactivated.
    // boost::flyweights::no_tracking tells Boost.Flyweight to not track objects stored in internal containers: when objects are no longer used, Boost.Flyweight detects this and removes them from the containers
    templated_person(int id, std::string city) : id_{id}, city_{std::move(city)} {}
};


int main() {
    std::cout << termcolor::bold << termcolor::underline
              << "A hundred thousand identical strings without Boost.Flyweight" << termcolor::reset << std::endl;
    {
        std::vector<person_> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }

    std::cout << termcolor::bold << termcolor::underline
              << "One string instead of a hundred thousand strings with Boost.Flyweight" << termcolor::reset
              << std::endl;
    {
        std::vector<person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::flyweights::flyweight multiple times"
              << termcolor::reset << std::endl;
    {
        std::vector<located_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin", "Germany"});
        }
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Using boost::flyweights::flyweight multiple times with tags" << termcolor::reset << std::endl;
    {
        std::vector<tagged_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin", "Germany"});
        }

    }

    std::cout << termcolor::bold << termcolor::underline << "Template parameters of boost::flyweights::flyweight"
              << termcolor::reset << std::endl;
    {
        std::vector<templated_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }
}
