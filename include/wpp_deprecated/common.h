#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include "const_str.h"

namespace wpp
{


    enum class ParamType
    {
        INT, // int
        UINT, // positive int
        DOUBLE, // double
        STRING, // string
        PATH, // simple word
        MAX // only to keep the number of enums
    };

    struct routing_params
    {
        std::vector<int64_t> int_params;
        std::vector<uint64_t> uint_params;
        std::vector<double> double_params;
        std::vector<std::string> string_params;

        void debug_print() const
        {
            std::cerr << "routing_params" << std::endl;
            for(auto x:int_params)
                std::cerr<<x <<", " ;
            std::cerr<<std::endl;
            for(auto x:uint_params)
                std::cerr<<x <<", " ;
            std::cerr<<std::endl;
            for(auto x:double_params)
                std::cerr<<x <<", " ;
            std::cerr<<std::endl;
            for(auto& x:string_params)
                std::cerr<<x <<", " ;
            std::cerr<<std::endl;
        }

        template <typename T>
        T get(unsigned) const;

    };

    template<>
    inline int64_t routing_params::get<int64_t>(unsigned index) const
    {
        return int_params[index];
    }

    template<>
    inline uint64_t routing_params::get<uint64_t>(unsigned index) const
    {
        return uint_params[index];
    }

    template<>
    inline double routing_params::get<double>(unsigned index) const
    {
        return double_params[index];
    }

    template<>
    inline std::string routing_params::get<std::string>(unsigned index) const
    {
        return string_params[index];
    }
}

#ifndef WPP_MSVC_WORKAROUND
constexpr wpp::HTTPMethod operator "" _method(const char* str, size_t /*len*/)
{
    return
        wpp::const_str::is_equ_p(str, "GET", 3) ? wpp::HTTPMethod::Get :
        wpp::const_str::is_equ_p(str, "DELETE", 6) ? wpp::HTTPMethod::Delete :
        wpp::const_str::is_equ_p(str, "HEAD", 4) ? wpp::HTTPMethod::Head :
        wpp::const_str::is_equ_p(str, "POST", 4) ? wpp::HTTPMethod::Post :
        wpp::const_str::is_equ_p(str, "PUT", 3) ? wpp::HTTPMethod::Put :
        wpp::const_str::is_equ_p(str, "OPTIONS", 7) ? wpp::HTTPMethod::Options :
        wpp::const_str::is_equ_p(str, "CONNECT", 7) ? wpp::HTTPMethod::Connect :
        wpp::const_str::is_equ_p(str, "TRACE", 5) ? wpp::HTTPMethod::Trace :
        throw std::runtime_error("invalid http method");
}
#endif
