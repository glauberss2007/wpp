#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::spirit;

typedef boost::variant<int, bool> int_or_bool;

struct int_or_bool_values
{
    int_or_bool first;
    std::vector<int_or_bool> others;
};

// This macro makes it possible to treat int_or_bool_values like a tuple with two values of type int_or_bool and std::vector<int_or_bool>
BOOST_FUSION_ADAPT_STRUCT(
        int_or_bool_values,
        (int_or_bool, first)
                (std::vector<int_or_bool>, others)
)

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, int_or_bool_values(), Skipper>
{
    my_grammar() : my_grammar::base_type{values}
    {
        value = qi::int_ | qi::bool_;
        // first component has to be stored in an object of type boost::variant. The values parsed by the second component have to be stored in a container
        values = value >> ',' >> value % ',';
    }

    qi::rule<Iterator, int_or_bool(), Skipper> value;
    qi::rule<Iterator, int_or_bool_values(), Skipper> values;
};

struct print : public boost::static_visitor<>
{
    template <typename T>
    void operator()(T t) const
    {
        std::cout << std::boolalpha << t << ';';
    }
};

int main()
{
    std::string s = "3214,true,false,3213";
    //std::getline(std::cin, s);
    auto it = s.begin();
    my_grammar<std::string::iterator, ascii::space_type> g;
    int_or_bool_values v;
    if (qi::phrase_parse(it, s.end(), g, ascii::space, v))
    {
        print p;
        boost::apply_visitor(p, v.first);
        for (const auto &elem : v.others)
            boost::apply_visitor(p, elem);
    }
}
