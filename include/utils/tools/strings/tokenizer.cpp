#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

// https://theboostcpplibraries.com/boost.tokenizer
// The library Boost.Tokenizer allows you to iterate over partial expressions in a string by interpreting certain characters as separators.

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Iterating over partial expressions in a string with boost::tokenizer" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        tokenizer tok{s};
        for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
            std::cout << *it << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Initializing boost::char_separator to adapt the iteration" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" "};
        tokenizer tok{s, sep};
        for (const auto &t : tok)
            std::cout << t << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Simulating the default behavior with boost::char_separator" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" ", "+"};
        tokenizer tok{s, sep};
        for (const auto &t : tok)
            std::cout << t << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Initializing boost::char_separator to display empty partial expressions" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" ", "+", boost::keep_empty_tokens};
        tokenizer tok{s, sep};
        for (const auto &t : tok)
            std::cout << t << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Boost.Tokenizer with wide strings" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::char_separator<wchar_t>,
                std::wstring::const_iterator, std::wstring> tokenizer;
        std::wstring s = L"Boost C++ Libraries";
        boost::char_separator<wchar_t> sep{L" "};
        tokenizer tok{s, sep};
        for (const auto &t : tok)
            std::wcout << t << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Parsing CSV files with boost::escaped_list_separator" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::escaped_list_separator<char>> tokenizer;
        std::string s = "Boost,\"C++ Libraries\"";
        tokenizer tok{s};
        for (const auto &t : tok)
            std::cout << t << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Iterating over partial expressions with boost::offset_separator" << termcolor::reset << std::endl;
    {
        typedef boost::tokenizer<boost::offset_separator> tokenizer;
        std::string s = "Boost_C++_Libraries";
        int offsets[] = {5, 5, 9};
        boost::offset_separator sep{offsets, offsets + 3};
        tokenizer tok{s, sep};
        for (const auto &t : tok)
            std::cout << t << '\n';
    }
    return 0;
}