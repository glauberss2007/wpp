//
// Created by Alan de Freitas on 18/06/17.
//

#ifndef WPP_CONSTSTR_H
#define WPP_CONSTSTR_H

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
    // create and compare constant strings
    namespace const_str
    {
#ifndef WPP_MSVC_WORKAROUND
        // Out of range exception
        struct OutOfRange
        {
            OutOfRange(unsigned /*pos*/, unsigned /*length*/) {}
        };
        constexpr unsigned requires_in_range( unsigned i, unsigned len )
        {
            return i >= len ? throw OutOfRange(i, len) : i;
        }

        // workaround for constant strings (which is not directly allowed)
        class const_str
        {
            const char * const begin_;
            unsigned size_;

        public:

            // construct for char *
            constexpr const_str(const char * s) : begin_(s), size_(sizeof(s) / sizeof(s[0])){};

            // construct for char * from position arr and size N
            template< unsigned N >
            constexpr const_str( const char(&arr)[N] ) : begin_(arr), size_(N - 1) {
                static_assert( N >= 1, "not a string literal");
            }

            // check if range is correct (compile time) and return i-th char
            constexpr char operator[]( unsigned i ) const {
                return requires_in_range(i, size_), begin_[i];
            }

            // return first char *
            constexpr operator const char *() const {
                return begin_;
            }

            // iterators (pointers, actually)
            constexpr const char* begin() const { return begin_; }
            constexpr const char* end() const { return begin_ + size_; }

            // get size
            constexpr unsigned size() const {
                return size_;
            }
        };

        // const char opening_tag = '<';
        const char opening_tag = wpp_settings::opening_tag;
        // const char closing_tag = '>';
        const char closing_tag = wpp_settings::closing_tag;

        // position where the parameter tag closes
        constexpr unsigned find_closing_tag(const_str s, unsigned p)
        {
            return s[p] == closing_tag ? p : find_closing_tag(s, p+1);
        }

        // check if string s from i to i+f is a valid route name
        constexpr bool is_valid(const_str s, unsigned i = 0, int f = 0)
        {
            return
                    i == s.size()
                    ? f == 0 :
                    f < 0 || f >= 2
                    ? false :
                    s[i] == opening_tag
                    ? is_valid(s, i+1, f+1) :
                    s[i] == closing_tag
                    ? is_valid(s, i+1, f-1) :
                    is_valid(s, i+1, f);
        }

        // returns if string a and string b (both with n elements) are the same
        constexpr bool is_equ_p(const char* a, const char* b, unsigned n)
        {
            return
                    *a == 0 && *b == 0 && n == 0
                    ? true :
                    (*a == 0 || *b == 0)
                    ? false :
                    n == 0
                    ? true :
                    *a != *b
                    ? false :
                    is_equ_p(a+1, b+1, n-1);
        }

        // return if string a (from ai) is equal to string b (from bi) of size n
        constexpr bool is_equ_n(const_str a, unsigned ai, const_str b, unsigned bi, unsigned n)
        {
            return
                    ai + n > a.size() || bi + n > b.size()
                    ? false :
                    n == 0
                    ? true :
                    a[ai] != b[bi]
                    ? false :
                    is_equ_n(a,ai+1,b,bi+1,n-1);
        }

        // compare strings to valid tags
        constexpr bool is_int(const_str s, unsigned i)
        {
            return is_equ_n(s, i, const_str({opening_tag,'i','n','t',closing_tag}), 0, 5);
        }

        constexpr bool is_uint(const_str s, unsigned i)
        {
            return is_equ_n(s, i, const_str({opening_tag,'u','i','n','t',closing_tag}), 0, 6);
        }

        constexpr bool is_float(const_str s, unsigned i)
        {
            return is_equ_n(s, i, const_str({opening_tag,'f','l','o','a','t',closing_tag}), 0, 7) ||
                   is_equ_n(s, i, const_str({opening_tag,'d','o','u','b','l','e',closing_tag}), 0, 8);
        }

        constexpr bool is_str(const_str s, unsigned i)
        {
            return is_equ_n(s, i, const_str({opening_tag,'s','t','r',closing_tag}), 0, 5) ||
                   is_equ_n(s, i, const_str({opening_tag,'s','t','r','i','n','g',closing_tag}), 0, 8);
        }

        constexpr bool is_path(const_str s, unsigned i)
        {
            return is_equ_n(s, i, const_str({opening_tag,'p','a','t','h',closing_tag}), 0, 6);
        }
#endif


        // associates each type with a parameter tag (an int value)
        template <typename T>
        struct parameter_tag
        {
            static const int value = 0;
        };


#define WPP_INTERNAL_PARAMETER_TAG(t, i) \
        template <> \
        struct parameter_tag<t> \
        { \
            static const int value = i; \
        }

        WPP_INTERNAL_PARAMETER_TAG(int, 1);
        WPP_INTERNAL_PARAMETER_TAG(char, 1);
        WPP_INTERNAL_PARAMETER_TAG(short, 1);
        WPP_INTERNAL_PARAMETER_TAG(long, 1);
        WPP_INTERNAL_PARAMETER_TAG(long long, 1);
        WPP_INTERNAL_PARAMETER_TAG(unsigned int, 2);
        WPP_INTERNAL_PARAMETER_TAG(unsigned char, 2);
        WPP_INTERNAL_PARAMETER_TAG(unsigned short, 2);
        WPP_INTERNAL_PARAMETER_TAG(unsigned long, 2);
        WPP_INTERNAL_PARAMETER_TAG(unsigned long long, 2);
        WPP_INTERNAL_PARAMETER_TAG(double, 3);
        WPP_INTERNAL_PARAMETER_TAG(std::string, 4);
#undef WPP_INTERNAL_PARAMETER_TAG

        template <typename ... Args>
        struct compute_parameter_tag_from_args_list;

        // parameter_tag from empty list is 0
        template <>
        struct compute_parameter_tag_from_args_list<>
        {
            static const int value = 0;
        };

        // parameter_tag for list is value from parameter_tag_first_elem + parameter_tag_snd_elem * 6 ...
        // the final number represents a list of parameter tags
        template <typename Arg, typename ... Args>
        struct compute_parameter_tag_from_args_list<Arg, Args...>
        {
            static const int sub_value =
                    compute_parameter_tag_from_args_list<Args...>::value;
            static const int value =
                    parameter_tag<typename std::decay<Arg>::type>::value
                    ? sub_value* 6 + parameter_tag<typename std::decay<Arg>::type>::value
                    : sub_value;
        };

        // inverse process to check if it's valid
        static inline bool is_parameter_tag_compatible(uint64_t a, uint64_t b)
        {
            if (a == 0)
                return b == 0;
            if (b == 0)
                return a == 0;
            int sa = a%6;
            int sb = a%6;
            if (sa == 5) sa = 4;
            if (sb == 5) sb = 4;
            if (sa != sb)
                return false;
            return is_parameter_tag_compatible(a/6, b/6);
        }

        static inline unsigned find_closing_tag_runtime(const char* s, unsigned p)
        {
            return
                    s[p] == 0
                    ? throw std::runtime_error("unmatched closing tag") :
                    s[p] == closing_tag
                    ? p : find_closing_tag_runtime(s, p + 1);
        }

        static inline uint64_t get_parameter_tag_runtime(const char* s, unsigned p = 0)
        {
            return
                    s[p] == 0
                    ?  0 :
                    s[p] == opening_tag ? (
                            std::strncmp(s+p, const_str({opening_tag,'i','n','t',closing_tag}), 5) == 0
                            ? get_parameter_tag_runtime(s, find_closing_tag_runtime(s, p)) * 6 + 1 :
                            std::strncmp(s+p, const_str({opening_tag,'u','i','n','t',closing_tag}), 6) == 0
                            ? get_parameter_tag_runtime(s, find_closing_tag_runtime(s, p)) * 6 + 2 :
                            (std::strncmp(s+p,  const_str({opening_tag,'f','l','o','a','t',closing_tag}), 7) == 0 ||
                             std::strncmp(s+p, const_str({opening_tag,'d','o','u','b','l','e',closing_tag}), 8) == 0)
                            ? get_parameter_tag_runtime(s, find_closing_tag_runtime(s, p)) * 6 + 3 :
                            (std::strncmp(s+p, const_str({opening_tag,'s','t','r',closing_tag}), 5) == 0 ||
                             std::strncmp(s+p, const_str({opening_tag,'s','t','r','i','n','g',closing_tag}), 8) == 0)
                            ? get_parameter_tag_runtime(s, find_closing_tag_runtime(s, p)) * 6 + 4 :
                            std::strncmp(s+p, const_str({opening_tag,'p','a','t','h',closing_tag}), 6) == 0
                            ? get_parameter_tag_runtime(s, find_closing_tag_runtime(s, p)) * 6 + 5 :
                            throw std::runtime_error("invalid parameter type")
                    ) :
                    get_parameter_tag_runtime(s, p+1);

        }
#ifndef WPP_MSVC_WORKAROUND

        // get sum of tags from any position s[p] up to the closing position (if there is an opening position)
        constexpr uint64_t get_parameter_tag(const_str s, unsigned p = 0)
        {
            return
                    p == s.size()
                    ?  0 :
                    s[p] == opening_tag ? (
                            is_int(s, p)
                            ? get_parameter_tag(s, find_closing_tag(s, p)) * 6 + 1 :
                            is_uint(s, p)
                            ? get_parameter_tag(s, find_closing_tag(s, p)) * 6 + 2 :
                            is_float(s, p)
                            ? get_parameter_tag(s, find_closing_tag(s, p)) * 6 + 3 :
                            is_str(s, p)
                            ? get_parameter_tag(s, find_closing_tag(s, p)) * 6 + 4 :
                            is_path(s, p)
                            ? get_parameter_tag(s, find_closing_tag(s, p)) * 6 + 5 :
                            throw std::runtime_error("invalid parameter type")
                    ) :
                    get_parameter_tag(s, p+1);
        }

        // version of the function for chars
        constexpr uint64_t get_parameter_tag(char* s, unsigned p = 0){
            const const_str c(s);
            return get_parameter_tag(c,p);
        }

#endif

        template <typename ... T>
        struct S
        {
            template <typename U>
            using push = S<U, T...>;

            template <typename U>
            using push_back = S<T..., U>;

            template <template<typename ... Args> class U>
            using rebind = U<T...>;
        };

        template <typename F, typename Set>
        struct CallHelper;

        template <typename F, typename ...Args>
        struct CallHelper<F, S<Args...>>
        {
            template <typename F1, typename ...Args1, typename =
            decltype(std::declval<F1>()(std::declval<Args1>()...))
            >
            static char __test(int);

            template <typename ...>
            static int __test(...);

            static constexpr bool value = sizeof(__test<F, Args...>(0)) == sizeof(char);
        };

        // convert the type tags back to types
        template <int N>
        struct single_tag_to_type
        {
        };

        template <>
        struct single_tag_to_type<1>
        {
            using type = int64_t;
        };

        template <>
        struct single_tag_to_type<2>
        {
            using type = uint64_t;
        };

        template <>
        struct single_tag_to_type<3>
        {
            using type = double;
        };

        template <>
        struct single_tag_to_type<4>
        {
            using type = std::string;
        };

        template <>
        struct single_tag_to_type<5>
        {
            using type = std::string;
        };

        // convert list of type tags back to list of types
        template <uint64_t Tag>
        struct arguments
        {
            using subarguments = typename arguments<Tag/6>::type;
            using type =
            typename subarguments::template push<typename single_tag_to_type<Tag%6>::type>;
        };

        template <>
        struct arguments<0>
        {
            using type = S<>;
        };

        template <typename ... T>
        struct last_element_type
        {
            using type = typename std::tuple_element<sizeof...(T)-1, std::tuple<T...>>::type;
        };


        template <>
        struct last_element_type<>
        {
        };


        // from http://stackoverflow.com/questions/13072359/c11-compile-time-array-with-logarithmic-evaluation-depth
        template<class T> using Invoke = typename T::type;

        template<unsigned...> struct seq{ using type = seq; };

        template<class S1, class S2> struct concat;

        template<unsigned... I1, unsigned... I2>
        struct concat<seq<I1...>, seq<I2...>>
                : seq<I1..., (sizeof...(I1)+I2)...>{};

        template<class S1, class S2>
        using Concat = Invoke<concat<S1, S2>>;

        template<unsigned N> struct gen_seq;
        template<unsigned N> using GenSeq = Invoke<gen_seq<N>>;

        template<unsigned N>
        struct gen_seq : Concat<GenSeq<N/2>, GenSeq<N - N/2>>{};

        template<> struct gen_seq<0> : seq<>{};
        template<> struct gen_seq<1> : seq<0>{};

        template <typename Seq, typename Tuple>
        struct pop_back_helper;

        template <unsigned ... N, typename Tuple>
        struct pop_back_helper<seq<N...>, Tuple>
        {
            template <template <typename ... Args> class U>
            using rebind = U<typename std::tuple_element<N, Tuple>::type...>;
        };

        template <typename ... T>
        struct pop_back //: tools pop_back_helper<typename gen_seq<sizeof...(T)-1>::type, std::tuple<T...>>
        {
            template <template <typename ... Args> class U>
            using rebind = typename pop_back_helper<typename gen_seq<sizeof...(T)-1>::type, std::tuple<T...>>::template rebind<U>;
        };

        template <>
        struct pop_back<>
        {
            template <template <typename ... Args> class U>
            using rebind = U<>;
        };

        // from http://stackoverflow.com/questions/2118541/check-if-c0x-parameter-pack-contains-a-type
        template < typename Tp, typename... List >
        struct contains : std::true_type {};

        template < typename Tp, typename Head, typename... Rest >
        struct contains<Tp, Head, Rest...>
                : std::conditional< std::is_same<Tp, Head>::value,
                        std::true_type,
                        contains<Tp, Rest...>
                >::type {};

        template < typename Tp >
        struct contains<Tp> : std::false_type {};

        template <typename T>
        struct empty_context
        {
        };

        template <typename T>
        struct promote
        {
            using type = T;
        };

        // change all types to a "better" equivalent type
#define WPP_INTERNAL_PROMOTE_TYPE(t1, t2) \
        template<> \
        struct promote<t1> \
        {  \
            using type = t2; \
        }

        WPP_INTERNAL_PROMOTE_TYPE(char, int64_t);
        WPP_INTERNAL_PROMOTE_TYPE(short, int64_t);
        WPP_INTERNAL_PROMOTE_TYPE(int, int64_t);
        WPP_INTERNAL_PROMOTE_TYPE(long, int64_t);
        WPP_INTERNAL_PROMOTE_TYPE(long long, int64_t);
        WPP_INTERNAL_PROMOTE_TYPE(unsigned char, uint64_t);
        WPP_INTERNAL_PROMOTE_TYPE(unsigned short, uint64_t);
        WPP_INTERNAL_PROMOTE_TYPE(unsigned int, uint64_t);
        WPP_INTERNAL_PROMOTE_TYPE(unsigned long, uint64_t);
        WPP_INTERNAL_PROMOTE_TYPE(unsigned long long, uint64_t);
        WPP_INTERNAL_PROMOTE_TYPE(float, double);
#undef WPP_INTERNAL_PROMOTE_TYPE

        template <typename T>
        using promote_t = typename promote<T>::type;

    } // namespace black_magic


}

#endif //WPP_CONSTSTR_H
