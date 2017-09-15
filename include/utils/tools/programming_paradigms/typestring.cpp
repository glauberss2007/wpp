#include <cstdio>
#include <iostream>
#include <type_traits>
#include "typestring/typestring.h"
#include <typeinfo>
#include <cxxabi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

template<typename A, typename B>
void check() {
    printf("[%s] %s\n", std::is_same<A,B>::value ? "pass" : "fail", A::data());
}

using test1
    = irqus::typestring<'H', 'e', 'l', 'l', 'o'
                     , ' '
                     , 'w', 'o', 'r', 'l', 'd'
                     , ','
                     , ' '
                     , 'h', 'o', 'w'
                     , ' '
                     , 'i', 's'
                     , ' '
                     , 'i', 't'
                     , ' '
                     , 'g', 'o', 'i', 'n', 'g', '?'>;

using test2
    = irqus::typestring<'u', 'p', 'p', 'e', 'r', 'c', 'a', 's', 'e'
                       , ':'
                       , ' '
                       , 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'
                       , 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'
                       , 'W', 'X', 'Y', 'Z' >;
using test3
    = irqus::typestring< 'l', 'o', 'w', 'e', 'r', 'c', 'a', 's', 'e'
                       , ':'
                       , ' '
                       , 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'
                       , 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'
                       , 'w', 'x', 'y', 'z' >;
using test4
    = irqus::typestring< 'f', 'l','o', 'a', 't', 'i', 'n', 'g'
                       , ' '
                       , ':'
                       , ' '
                       , '1', '2', '3', '4', '5', '6', '7', '8', '9'
                       , '.'
                       , '1', '2', '3', '4', '5', '6', '7', '8', '9'
                       , '+'
                       , 'e', '-', '1', '2', '3', '4'>;
using test5
    = irqus::typestring< 's', 'y', 'm', 'b', 'o', 'l', 's'
                       , ' '
                       , ' '
                       , ':'
                       , ' '
                       , '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '('
                       , ')', '_', '+', '=','-', '[', ']', '\\', '{', '}', '|'
                       , ':', ';', '\'', ',', '.', '?', '/'>;
      
int main() {
    check<typestring_is("Hello world, how is it going?"),test1>();
    check<typestring_is("uppercase: ABCDEFGHIJKLMNOPQRSTUVWXYZ"),test2>();
    check<typestring_is("lowercase: abcdefghijklmnopqrstuvwxyz"),test3>();
    check<typestring_is("floating : 123456789.123456789+e-1234"),test4>();
    check<typestring_is("symbols  : ~`!@#$%^&*()_+=-[]\\{}|:;',.?/"),test5>();
    check<typestring_is(""),irqus::typestring<'\0'>>(); // null!
    check< irqus::tycat< typestring_is("ABC")
                       , typestring_is("DEF")
                       , typestring_is("1234")>
         , typestring_is("ABCDEF1234") >();

    typedef typestring_is("Hello!") test; /* irqus::typestring<'H','e','l','l','o','!'> */
    std::cout << typeid(test).name() << std::endl;
    std::cout << typeid(typestring_is("Hello!")).name() << std::endl;
    std::cout << typeid(typestring_is("www.site.com/home/option.php?r=2")).name() << std::endl;

    std::string url = typeid(typestring_is("www.site.com/home/option.php?r=2")).name();
    int status = -1;
    std::string demangledName = abi::__cxa_demangle(url.data(), NULL, NULL, &status );
    if ( status == 0 )
    {
        std::cout << url << std::endl;
        std::cout << demangledName << std::endl;
    }
    std::cout << demangledName << std::endl;
    boost::algorithm::erase_all(demangledName, "(char)");
    boost::algorithm::erase_all(demangledName, "<");
    boost::algorithm::erase_all(demangledName, ">");
    boost::algorithm::erase_all(demangledName, "typestring");
    boost::algorithm::erase_all(demangledName, "irqus");
    boost::algorithm::erase_all(demangledName, "::");
    boost::algorithm::erase_all(demangledName, ",");
    std::cout << demangledName << '\n';
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    std::string s = demangledName;
    boost::char_separator<char> sep{" "};
    tokenizer tok{s, sep};
    std::string url_demangled;
    for (const auto &t : tok) {
        std::cout << t << ',';
        url_demangled.push_back(char(std::stoi(std::string(t))));
    }
    std::cout << std::endl;
    std::cout << url_demangled << std::endl;

    return {};
}
