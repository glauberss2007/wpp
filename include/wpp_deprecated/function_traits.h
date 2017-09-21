//
// Created by Alan de Freitas on 18/06/17.
//

#ifndef WPP_FUNCTIONTRAITS_H
#define WPP_FUNCTIONTRAITS_H

#pragma once

#include <cstdint>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <cstring>
#include <functional>
#include <string>

#include "settings.h"

namespace wpp
{
    namespace detail
    {

        template <class T, std::size_t N, class... Args>
        struct get_index_of_element_from_tuple_by_type_impl
        {
            static constexpr auto value = N;
        };

        template <class T, std::size_t N, class... Args>
        struct get_index_of_element_from_tuple_by_type_impl<T, N, T, Args...>
        {
            static constexpr auto value = N;
        };

        template <class T, std::size_t N, class U, class... Args>
        struct get_index_of_element_from_tuple_by_type_impl<T, N, U, Args...>
        {
            static constexpr auto value = get_index_of_element_from_tuple_by_type_impl<T, N + 1, Args...>::value;
        };

    } // namespace detail

    namespace utility
    {
        // get element of that type
        template <class T, class... Args>
        T& get_element_by_type(std::tuple<Args...>& t)
        {
            return std::get<detail::get_index_of_element_from_tuple_by_type_impl<T, 0, Args...>::value>(t);
        }

        // identify function traits
        template<typename T>
        struct function_traits;

#ifndef WPP_MSVC_WORKAROUND
        // save result in parent_t in this workaround
        template<typename T>
        struct function_traits : public function_traits<decltype(&T::operator())>
        {
            using parent_t = function_traits<decltype(&T::operator())>;
            static const size_t arity = parent_t::arity;
            using result_type = typename parent_t::result_type;
            template <size_t i>
            using arg = typename parent_t::template arg<i>;

        };
#endif

        // keep arity, result type, args from tuple
        template<typename ClassType, typename R, typename ...Args>
        struct function_traits<R(ClassType::*)(Args...) const>
        {
            static const size_t arity = sizeof...(Args);

            typedef R result_type;

            template <size_t i>
            using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        template<typename ClassType, typename R, typename ...Args>
        struct function_traits<R(ClassType::*)(Args...)>
        {
            static const size_t arity = sizeof...(Args);

            typedef R result_type;

            template <size_t i>
            using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        template<typename R, typename ...Args>
        struct function_traits<std::function<R(Args...)>>
        {
            static const size_t arity = sizeof...(Args);

            typedef R result_type;

            template <size_t i>
            using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
        };

        // convert chars of bytes to strings
        inline static std::string base64encode(const char* data, size_t size, const char* key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/")
        {
            std::string ret;
            ret.resize((size+2) / 3 * 4);
            auto it = ret.begin();
            while(size >= 3)
            {
                *it++ = key[(((unsigned char)*data)&0xFC)>>2];
                unsigned char h = (((unsigned char)*data++) & 0x03) << 4;
                *it++ = key[h|((((unsigned char)*data)&0xF0)>>4)];
                h = (((unsigned char)*data++) & 0x0F) << 2;
                *it++ = key[h|((((unsigned char)*data)&0xC0)>>6)];
                *it++ = key[((unsigned char)*data++)&0x3F];

                size -= 3;
            }
            if (size == 1)
            {
                *it++ = key[(((unsigned char)*data)&0xFC)>>2];
                unsigned char h = (((unsigned char)*data++) & 0x03) << 4;
                *it++ = key[h];
                *it++ = '=';
                *it++ = '=';
            }
            else if (size == 2)
            {
                *it++ = key[(((unsigned char)*data)&0xFC)>>2];
                unsigned char h = (((unsigned char)*data++) & 0x03) << 4;
                *it++ = key[h|((((unsigned char)*data)&0xF0)>>4)];
                h = (((unsigned char)*data++) & 0x0F) << 2;
                *it++ = key[h];
                *it++ = '=';
            }
            return ret;
        }

        inline static std::string base64encode_urlsafe(const char* data, size_t size)
        {
            return base64encode(data, size, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
        }


    } // namespace utility
}


#endif //WPP_FUNCTIONTRAITS_H
