#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::spirit;

// a class called my_grammar, which is derived from boost::spirit::qi::grammar.
// my_grammar and boost::spirit::qi::grammar are class templates.
template<typename Iterator, typename Skipper>
struct my_grammar
        : qi::grammar<Iterator,
                std::vector<boost::variant<int, bool>>(), Skipper> {
    // Boost.Spirit knows which rule is the entry point of the grammar
    my_grammar() : my_grammar::base_type{values} {
        value = qi::int_ | qi::bool_;
        values = value % ',';
    }

    qi::rule<Iterator, boost::variant<int, bool>(), Skipper> value;
    qi::rule<Iterator, std::vector<boost::variant<int, bool>>(), Skipper>
            values;
};

struct print
        : public boost::static_visitor<> {
    template<typename T>
    void operator()(T t) const {
        std::cout << std::boolalpha << t << ';';
    }
};

int main() {
    std::string s = "3213,true,false,3214";
    //std::getline(std::cin, s);
    auto it = s.begin();
    my_grammar<std::string::iterator, ascii::space_type> g;
    std::vector<boost::variant<int, bool>> v;
    if (qi::phrase_parse(it, s.end(), g, ascii::space, v)) {
        for (const auto &elem : v) {
            boost::apply_visitor(print{}, elem);
        }
    }
}