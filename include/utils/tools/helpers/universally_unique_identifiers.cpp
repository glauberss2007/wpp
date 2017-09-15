// https://theboostcpplibraries.com/boost.uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::uuids;

int main(int argc, const char *argv[]) {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Boost.Uuid"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Generating random UUIDs with boost::uuids::random_generator"
              << termcolor::reset << std::endl;
    {
        random_generator gen;
        uuid id = gen();
        std::cout << "id: " << id << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Member functions of boost::uuids::uuid" << termcolor::reset << std::endl;
    {
        random_generator gen;
        uuid id = gen();
        std::cout << "id.size(): " << id.size() << '\n';
        std::cout << "std::boolalpha << id.is_nil(): " << std::boolalpha << id.is_nil() << '\n';
        std::cout << "id.variant(): " << id.variant() << '\n';
        std::cout << "id.version(): " << id.version() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Generators from Boost.Uuid" << termcolor::reset << std::endl;
    {
        nil_generator nil_gen;
        uuid id = nil_gen();
        std::cout << "std::boolalpha << id.is_nil(): " << std::boolalpha << id.is_nil() << '\n';

        string_generator string_gen;
        id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
        std::cout << "id.variant(): " << id.variant() << '\n';

        name_generator name_gen(id);
        std::cout << "name_gen(\"theboostcpplibraries.com\"): " << name_gen("theboostcpplibraries.com") << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Conversion to strings" << termcolor::reset << std::endl;
    {
        random_generator gen;
        uuid id = gen();

        std::string s = to_string(id);
        std::cout << "s: " << s << '\n';

        std::cout << "boost::lexical_cast<std::string>(id): " << boost::lexical_cast<std::string>(id) << '\n';
    }
}