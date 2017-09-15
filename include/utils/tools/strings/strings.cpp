//
// Created by Alan de Freitas on 08/09/17.
//

#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"
#include <locale>
#include <vector>
#include <boost/algorithm/string/regex.hpp>
#include <boost/tokenizer.hpp>

using namespace boost::algorithm;
using namespace std;

int main() {
    {
        string s = "Boost C++ Libraries";
        cout << s << '\n';
        cout << to_upper_copy(s) << '\n';
        cout << to_lower_copy(s) << '\n';
        cout << s << '\n';
        to_lower(s);
        cout << s << '\n';
        to_upper(s);
        cout << s << '\n';
    }
    {
        std::string s = "Boost C++ Libraries";
        std::cout << erase_first_copy(s, "s") << '\n';
        std::cout << erase_nth_copy(s, "s", 0) << '\n';
        std::cout << erase_last_copy(s, "s") << '\n';
        std::cout << erase_all_copy(s, "s") << '\n';
        std::cout << erase_head_copy(s, 5) << '\n';
        std::cout << erase_tail_copy(s, 9) << '\n';
    }
    {
        std::string s = "Boost C++ Libraries";
        boost::iterator_range<std::string::iterator> r = find_first(s, "C++");
        std::cout << "substring: " << r << '\n';
        r = find_first(s, "xyz");
        std::cout << "substring: " << r << '\n';
    }
    {
        std::vector<std::string> v{"Boost", "C++", "Libraries"};
        std::cout << join(v, " ") << '\n';
    }
    {
        std::string s = "Boost C++ Libraries";
        std::cout << replace_first_copy(s, "+", "-") << '\n';
        std::cout << replace_nth_copy(s, "+", 0, "-") << '\n';
        std::cout << replace_last_copy(s, "+", "-") << '\n';
        std::cout << replace_all_copy(s, "+", "-") << '\n';
        std::cout << replace_head_copy(s, 5, "BOOST") << '\n';
        std::cout << replace_tail_copy(s, 9, "LIBRARIES") << '\n';
    }
    {
        std::string s = "\t Boost C++ Libraries \t";
        std::cout << "_" << trim_left_copy(s) << "_\n";
        std::cout << "_" << trim_right_copy(s) << "_\n";
        std::cout << "_" << trim_copy(s) << "_\n";
    }
    {
        std::string s = "--Boost C++ Libraries--";
        std::cout << trim_left_copy_if(s, is_any_of("-")) << '\n';
        std::cout << trim_right_copy_if(s, is_any_of("-")) << '\n';
        std::cout << trim_copy_if(s, is_any_of("-")) << '\n';
    }
    {
        std::string s = "123456789Boost C++ Libraries123456789";
        std::cout << trim_left_copy_if(s, is_digit()) << '\n';
        std::cout << trim_right_copy_if(s, is_digit()) << '\n';
        std::cout << trim_copy_if(s, is_digit()) << '\n';
    }
    {
        std::string s = "Boost C++ Libraries";
        std::cout.setf(std::ios::boolalpha);
        std::cout << starts_with(s, "Boost") << '\n';
        std::cout << ends_with(s, "Libraries") << '\n';
        std::cout << contains(s, "C++") << '\n';
        std::cout << lexicographical_compare(s, "Boost") << '\n';
    }
    {
        std::string s = "Boost C++ Libraries";
        std::vector<std::string> v;
        split(v, s, is_space());
        std::cout << v.size() << '\n';
    }
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        tokenizer tok{s};
        for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
            std::cout << *it << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" "};
        tokenizer tok{s, sep};
        for (const auto &t : tok) {
            std::cout << t << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" ", "+"};
        tokenizer tok{s, sep};
        for (const auto &t : tok) {
            std::cout << t << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        std::string s = "Boost C++ Libraries";
        boost::char_separator<char> sep{" ", "+", boost::keep_empty_tokens};
        tokenizer tok{s, sep};
        for (const auto &t : tok) {
            std::cout << t << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::char_separator<wchar_t>,
                std::wstring::const_iterator, std::wstring> tokenizer;
        std::wstring s = L"Boost C++ Libraries";
        boost::char_separator<wchar_t> sep{L" "};
        tokenizer tok{s, sep};
        for (const auto &t : tok) {
            std::wcout << t << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::escaped_list_separator<char>> tokenizer;
        std::string s = "Boost,\"C++ Libraries\"";
        tokenizer tok{s};
        for (const auto &t : tok) {
            std::cout << t << '\n';
        }
    }
    {
        typedef boost::tokenizer<boost::offset_separator> tokenizer;
        std::string s = "Boost_C++_Libraries";
        int offsets[] = {5, 5, 9};
        boost::offset_separator sep{offsets, offsets + 3};
        tokenizer tok{s, sep};
        for (const auto &t : tok) {
            std::cout << t << '\n';
        }
    }
}