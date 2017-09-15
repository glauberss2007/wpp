// https://theboostcpplibraries.com/boost.program_options
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::archive;

class animal {
    public:
        animal() = default;

        animal(int legs) : legs_{legs} {}

        int legs() const { return legs_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) { ar & legs_; }

        int legs_;
};

struct free_standing_animal {
    int legs_;

    free_standing_animal() = default;

    free_standing_animal(int legs) : legs_{legs} {}

    int legs() const { return legs_; }
};

template<typename Archive>
void serialize(Archive &ar, free_standing_animal &a, const unsigned int version) {
    ar & a.legs_;
}

class named_animal {
    public:
        named_animal() = default;

        named_animal(int legs, std::string name) :
                legs_{legs}, name_{std::move(name)} {}

        int legs() const { return legs_; }

        const std::string &name() const { return name_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        friend void serialize(Archive &ar, named_animal &a, const unsigned int version);

        int legs_;
        std::string name_;
};

template<typename Archive>
void serialize(Archive &ar, named_animal &a, const unsigned int version) {
    ar & a.legs_;
    ar & a.name_;
}

class compatible_animal {
    public:
        compatible_animal() = default;

        compatible_animal(int legs, std::string name) :
                legs_{legs}, name_{std::move(name)} {}

        int legs() const { return legs_; }

        const std::string &name() const { return name_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        friend void serialize(Archive &ar, compatible_animal &a, const unsigned int version);

        int legs_;
        std::string name_;
};

template<typename Archive>
void serialize(Archive &ar, compatible_animal &a, const unsigned int version) {
    ar & a.legs_;
    if (version > 0) {
        ar & a.name_;
    }
}

BOOST_CLASS_VERSION(compatible_animal, 1)

class bird
        : public animal {
    public:
        bird() = default;

        bird(int legs, bool can_fly) :
                animal{legs}, can_fly_{can_fly} {}

        bool can_fly() const { return can_fly_; }

    private:
        friend class boost::serialization::access;

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<animal>(*this);
            ar & can_fly_;
        }

        bool can_fly_;
};

BOOST_CLASS_EXPORT(bird)

int main(int argc, const char *argv[]) {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Archive"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::archive::text_oarchive"
              << termcolor::reset << std::endl;
    {
        text_oarchive oa{std::cout};
        int i = 1;
        oa << i;
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::archive::text_iarchive" << termcolor::reset
              << std::endl;
    {
        auto save = []() -> void {
            std::ofstream file{"archive.txt"};
            text_oarchive oa{file};
            int i = 1;
            oa << i;
        };

        auto load = []() -> void {
            std::ifstream file{"archive.txt"};
            text_iarchive ia{file};
            int i = 0;
            ia >> i;
            std::cout << "i: " << i << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing with a stringstream" << termcolor::reset
              << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            int i = 1;
            oa << i;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            int i = 0;
            ia >> i;
            std::cout << "i: " << i << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing user-defined types with a member function"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal a{4};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal a;
            ia >> a;
            std::cout << "a.legs(): " << a.legs() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing with a free-standing function"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            free_standing_animal a{4};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            free_standing_animal a;
            ia >> a;
            std::cout << "a.legs(): " << a.legs() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing strings" << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            named_animal a{4, "cat"};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            named_animal a;
            ia >> a;
            std::cout << "a.legs(): " << a.legs() << '\n';
            std::cout << "a.name(): " << a.name() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Backward compatibility with version numbers"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            compatible_animal a{4, "cat"};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            compatible_animal a;
            ia >> a;
            std::cout << "a.legs(): " << a.legs() << '\n';
            std::cout << "a.name(): " << a.name() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Pointers and References"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Serializing pointers"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            boost::archive::text_oarchive oa{ss};
            animal *a = new animal{4};
            oa << a;
            std::cout << "std::hex << a: " << std::hex << a << '\n';
            delete a;
        };

        auto load = [&ss]() -> void {
            boost::archive::text_iarchive ia{ss};
            animal *a;
            ia >> a;
            std::cout << "std::hex << a: " << std::hex << a << '\n';
            std::cout << "std::dec << a->legs(): " << std::dec << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing smart pointers" << termcolor::reset
              << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            boost::scoped_ptr<animal> a{new animal{4}};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            boost::scoped_ptr<animal> a;
            ia >> a;
            std::cout << "a->legs(): " << a->legs() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing references" << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal a{4};
            animal &r = a;
            oa << r;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal a;
            animal &r = a;
            ia >> r;
            std::cout << "r.legs(): " << r.legs() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline
              << "Serialization of Class Hierarchy Objects"
              << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::underline << "Serializing derived classes correctly"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            bird penguin{2, false};
            oa << penguin;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            bird penguin;
            ia >> penguin;
            std::cout << "penguin.legs(): " << penguin.legs() << '\n';
            std::cout << "std::boolalpha << penguin.can_fly(): " << std::boolalpha << penguin.can_fly() << '\n';
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Registering derived classes statically with BOOST_CLASS_EXPORT" << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal *a = new bird{2, false};
            oa << a;
            delete a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal *a;
            ia >> a;
            std::cout << "a->legs(): " << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Registering derived classes dynamically with register_type()" << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            boost::archive::text_oarchive oa{ss};
            oa.register_type<bird>();
            animal *a = new bird{2, false};
            oa << a;
            delete a;
        };

        auto load = [&ss]() -> void {
            boost::archive::text_iarchive ia{ss};
            ia.register_type<bird>();
            animal *a;
            ia >> a;
            std::cout << "a->legs(): " << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Wrapper Functions for Optimization"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Serializing an array without a wrapper function"
              << termcolor::reset << std::endl;
    {
        std::stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            boost::array<int, 3> a{{0, 1, 2}};
            oa << boost::serialization::make_array(a.data(), a.size());
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            boost::array<int, 3> a;
            ia >> boost::serialization::make_array(a.data(), a.size());
            std::cout << "a[0] << \", \" << a[1] << \", \" << a[2]: " << a[0] << ", " << a[1] << ", " << a[2] << '\n';
        };

        save();
        load();
    }

}