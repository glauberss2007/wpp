//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef PHP_CONTAINER_UTILS_H
#define PHP_CONTAINER_UTILS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include <algorithm>
#include <numeric>
#include <random>
#include <regex>
#include <cmath>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <set>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/join.hpp>
// #include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace utils {

    // using ...

    // array_shift() shifts the first value of the array off and returns it, shortening the array by one element
    // take mean of the elements
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T array_shift(C<T> &c) {
        T t = c[0];
        c.erase(c.begin());
        return t;
    }

    template<class C>
    typename C::value_type array_shift(C &c) {
        typename C::value_type t = c[0];
        c.erase(c.begin());
        return t;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    T array_unshift(C<T> &c, T t) {
        c.insert(c.begin(),t);
        return t;
    }

    inline bool is_double(const std::string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        std::strtod(s.c_str(), &p) ;

        return (*p == 0) ;
    }

    inline bool is_int(const std::string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        std::strtol(s.c_str(), &p, 10) ;

        return (*p == 0) ;
    }

    inline std::vector<std::string> explode(std::string delimiter, std::string input)
    {
        std::vector<std::string> v;
        // boost::algorithm::split(v, input, delimiter);
        return v;
    };

    std::string implode(std::string separator, std::vector<std::string> input)
    {
        return boost::algorithm::join(input,separator);
    };

    template<typename string_type>
    string_type implode(string_type separator, std::vector<string_type> input)
    {
        return boost::algorithm::join(input,separator);
    };


    std::string trim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_copy_if(input,boost::is_any_of(charlist));
    };

    std::string rtrim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_right_copy_if(input,boost::is_any_of(charlist));
    };

    std::string ltrim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_left_copy_if(input, boost::is_any_of(charlist));
    };

    int microtime_milliseconds() {
        using namespace std::chrono;
        milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        return ms.count();
    }

    double microtime() {
        using namespace std::chrono;
        milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        double f = ms.count();
        f /= 1000;
        return f;
    }

    double round(double v, int precision){
        const double exp = std::pow(10,precision);
        return std::round(v*exp)/exp;
    }

    template<typename T>
    void func_get_args(std::vector<T> &v, T t) // recursive variadic function
    {
        v.push_back(t);
    }

    template<typename T, typename... TS>
    void func_get_args(std::vector<T> &v, T t, TS... args) // recursive variadic function
    {
        v.push_back(t);
        func_get_args(v, args...);
    }

    // Returns an array comprising a function's argument list
    template<typename T>
    std::vector<T> func_get_args(T t) {
        return std::vector<T>({t});
    }

    template<typename T, typename... TS>
    std::vector<T> func_get_args(TS... args) // recursive variadic function
    {
        std::vector<T> v;
        func_get_args(v, args...);
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    bool in_array(const T t, const C<T> c) {
        return c.find(c.begin(),c.end(),t) != c.end();
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> array_slice(C<T> array, size_t offset, size_t length) {
        if (array.begin()+offset < array.end()){
            if (array.begin()+offset+length < array.end()){
                return C<T>(array.begin()+offset, array.begin()+offset+length);
            } else {
                return C<T>(array.begin()+offset, array.end());
            }
        } else {
            return C<T>();
        }

    }

    template<class ResultContainer>
    ResultContainer array_slice(ResultContainer results, size_t offset, size_t length) {
        using row = decltype(results.front());
        if (results.begin()+offset < results.end()){
            if (results.begin()+offset+length < results.end()){
                return ResultContainer(results.begin()+offset, results.begin()+offset+length);
            } else {
                return ResultContainer(results.begin()+offset, results.end());
            }
        } else {
            return ResultContainer();
        }

    }

    std::string strtolower(std::string s){
        return boost::algorithm::to_lower_copy(s);
    }

    size_t strpos(std::string haystack, std::string needle){
        return haystack.find(needle);
    }

    std::vector<std::string> preg_split(std::regex r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false)
    {
        std::vector<std::string> splits;
        std::smatch m;

        while (std::regex_search(s, m, r))
        {
            int split_on = m.position();
            if (!PREG_SPLIT_NO_EMPTY || 0 != split_on){
                splits.push_back(s.substr(0, split_on));
            }
            s = s.substr(split_on + m.length());
            if (DELIM_CAPTURE){
                for (int i = 1; i < m.size(); ++i) {
                    splits.push_back(m[i]);
                }
            }
        }

        if(!s.empty()) {
            splits.push_back(s); // and there may be one last token at the end
        }

        return splits;
    }

    std::vector<std::string> preg_split(const char* r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false){
        return preg_split(std::regex(std::string(r)),s,PREG_SPLIT_NO_EMPTY,DELIM_CAPTURE);
    }

    std::vector<std::string> preg_split(std::string r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false){
        return preg_split(std::regex(r),s,PREG_SPLIT_NO_EMPTY,DELIM_CAPTURE);
    }


    std::string preg_replace(std::regex pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,pattern,replacement);
    }

    std::string preg_replace(std::string pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,std::regex(pattern),replacement);
    }

    std::string preg_replace(const char* pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,std::regex(std::string(pattern)),replacement);
    }

    std::string preg_replace(std::regex pattern, std::string replacement, std::string subject, int limit)
    {
        if (limit >= 0){
            for (int i = 0; i < limit; ++i) {
                subject = std::regex_replace(subject,pattern,replacement,std::regex_constants::format_first_only);
            }
        }
        return subject;
    }

    std::string preg_replace(std::string pattern, std::string replacement, std::string subject, int limit)
    {
        return utils::preg_replace(std::regex(pattern),replacement,subject,limit);
    }

    std::string preg_replace(const char* pattern, std::string replacement, std::string subject, int limit)
    {
        return utils::preg_replace(std::regex(std::string(pattern)),replacement,subject,limit);
    }

    bool ctype_lower(std::string str){
        for (char &c : str) {
            if (!islower(c)){
                return false;
            }
        }
        return true;
    }

    std::string str_to_lower(std::string str){
        return boost::algorithm::to_lower_copy(str);
    }

    std::string str_replace(std::string search, std::string replace, std::string subject){
        return boost::algorithm::replace_all_copy(subject, search, replace);
    }

    std::string str_replace(std::vector<std::string> search, std::string replace, std::string subject){
        std::string r = subject;
        for (std::string &s : search) {
            boost::algorithm::replace_all(r, s, replace);
        }
        return r;
    }

    std::string ucfirst(std::string str){
        if (str.empty()){
            return str;
        } else if (!islower(str[0])){
            std::string first = boost::algorithm::to_lower_copy(std::string(1,str[0]));
            return first + std::string(str.substr(1));
        } else {
            return str;
        }
    }

    template<typename FUNC, typename ARRAY>
    ARRAY array_map(FUNC f, ARRAY _values){
        for (auto &&value :_values) {
            value = f(value);
        }
    };
    
    std::vector<int> range(int start, int end, int step = 1){
        if (start > end){
            return range(end,start,step);
        }
        std::vector<int> v;
        v.reserve((end-start)/step);
        for (int i = start; i <= end; i+=step) {
            v.push_back(i);
        }
        return v;
    }

    std::string filter_var_int(std::string variable) {
        std::string filtered;
        // copy only numbers, +, and -:
        auto it = std::copy_if (variable.begin(), variable.end(), std::back_inserter(filtered), [](char c){
            return std::regex_match(std::string({c,'\0'}),std::regex("[\\+\\-0-9]"));
        });
        return filtered;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> array_merge(C<T> c1, C<T> &c2) {
        c1.insert(c1.end(),c2.begin(),c2.end());
        return c1;
    }


}

#endif //PHP_CONTAINER_UTILS_H
