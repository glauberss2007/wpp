// https://theboostcpplibraries.com/boost.propertytree
// structure to store key/value pairs

#include <boost/property_tree/ptree.hpp>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>


#include <utility>
#include <iostream>
#include "termcolor/termcolor.hpp"
#include <cstdlib>

struct string_to_int_translator {
    typedef std::string internal_type;
    typedef int external_type;

    boost::optional<int> get_value(const std::string &s) {
        char *c;
        long l = std::strtol(s.c_str(), &c, 10);
        return boost::make_optional(c != s.c_str(), static_cast<int>(l));
    }
};

using namespace boost::property_tree;

using boost::property_tree::ptree;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Accessing data in boost::property_tree::ptree" << termcolor::reset << std::endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");

        ptree &c = pt.get_child("C:");
        ptree &windows = c.get_child("Windows");
        ptree &system = windows.get_child("System");
        std::cout << system.get_value<std::string>() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing data in basic_ptree<std::string, int>" << termcolor::reset << std::endl;
    {
        typedef boost::property_tree::basic_ptree<std::string, int> ptree;
        ptree pt;
        pt.put(ptree::path_type{"C:\\Windows\\System", '\\'}, 20);
        pt.put(ptree::path_type{"C:\\Windows\\Cursors", '\\'}, 50);

        ptree &windows = pt.get_child(ptree::path_type{"C:\\Windows", '\\'});
        int files = 0;
        for (const std::pair<std::string, ptree> &p : windows) {
            files += p.second.get_value<int>();
        }
        std::cout << files << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing data with a translator" << termcolor::reset << std::endl;
    {
        typedef boost::property_tree::iptree ptree;
        ptree pt;
        pt.put(ptree::path_type{"C:\\Windows\\System", '\\'}, "20 files");
        pt.put(ptree::path_type{"C:\\Windows\\Cursors", '\\'}, "50 files");

        string_to_int_translator tr;
        int files =
                pt.get<int>(ptree::path_type{"c:\\windows\\system", '\\'}, tr) +
                pt.get<int>(ptree::path_type{"c:\\windows\\cursors", '\\'}, tr);
        std::cout << files << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Various member functions of boost::property_tree::ptree" << termcolor::reset << std::endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");

        boost::optional<std::string> c = pt.get_optional<std::string>("C:");
        std::cout << std::boolalpha << c.is_initialized() << '\n';

        pt.put_child("D:.Program Files", ptree{"50 files"});
        pt.add_child("D:.Program Files", ptree{"60 files"});

        ptree d = pt.get_child("D:");
        for (const std::pair<std::string, ptree> &p : d) {
            std::cout << p.second.get_value<std::string>() << '\n';
        }

        boost::optional<ptree &> e = pt.get_child_optional("E:");
        std::cout << e.is_initialized() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Serializing a boost::property_tree::ptree in the JSON format" << termcolor::reset << std::endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");
        pt.put("C:.Windows.Cursors", "50 files");

        json_parser::write_json("file.json", pt);

        ptree pt2;
        json_parser::read_json("file.json", pt2);

        std::cout << std::boolalpha << (pt == pt2) << '\n';
    }

    return 0;
}