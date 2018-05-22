#if __GNUC__

#include <cxxabi.h>

#endif

#include <typeinfo>
#include <string>
#include <type_traits>
#include <functional>
#include <boost/test/unit_test.hpp>
#include <utils/traits.hpp>
#include <iostream>
#include <map>
#include "termcolor/termcolor.hpp"

using utils::function_traits;

template<typename T, typename U>
static std::string print_two_types() {
    const char *t_name = typeid(T).name();
    const char *u_name = typeid(U).name();
    #if __GNUC__
    int status;
    t_name = abi::__cxa_demangle(t_name, NULL, NULL, &status);
    u_name = abi::__cxa_demangle(u_name, NULL, NULL, &status);
    #endif
    return t_name + std::string(" != ") + u_name;
}


int main() {

    std::cout << termcolor::bold << termcolor::underline << "Function Traits"
              << termcolor::reset << std::endl;
    {
        typedef function_traits<int(long, double *, const char &&, std::nullptr_t)> FT;

        //std::cout << "FT::result_type == int" << (FT::result_type == int) << std::endl;
        //BOOST_CHECK_EQUAL(FT::arity, 4);
        //std::cout << "FT::arg<0>::type == long" << (FT::arg<0>::type == long) << std::endl;
        //std::cout << "FT::arg<1>::type == double * " << (FT::arg<1>::type == double * ) << std::endl;
        //std::cout << "FT::arg<2>::type == const char&&)" << (FT::arg<2>::type == const char&&) << std::endl,
        //std::cout << "FT::arg<3>::type == std::nullptr_t" << (FT::arg<3>::type == std::nullptr_t) << std::endl;
    }
    struct S;

    //typedef utils::function_traits<float(double)> FType;
    //std::cout << (FType::member_function_type < S > , float(S::*)(double)) << (FType::member_function_type < S > , float(S::*)(double)) << std::endl;
    //std::cout << (FType::member_function_type<const S &>, float(S::*)(double) const) << (FType::member_function_type<const S &>, float(S::*)(double) const) << std::endl;
    //std::cout << (FType::member_function_type<volatile S>, float(S::*)(double) volatile) << (FType::member_function_type<volatile S>, float(S::*)(double) volatile) << std::endl;
    //std::cout << (FType::member_function_type<const volatile S *>, float(S::*)(double) const volatile) << (FType::member_function_type<const volatile S *>, float(S::*)(double) const volatile) << std::endl;
    //
    //std::cout << (utils::pointee<int *>::type, int) << (utils::pointee<int *>::type, int) << std::endl;
    //std::cout << (utils::pointee<int **>::type, int * ) << (utils::pointee<int **>::type, int * ) << std::endl;
    //std::cout << (utils::pointee<const int *>::type << (utils::pointee<const int *>::type << std::endl,
    //const int);
    //std::cout << (utils::pointee<std::string::const_iterator>::type << (utils::pointee<std::string::const_iterator>::type << std::endl,
    //const char);
    //typedef std::map<short, char> Map;
    //std::cout << (utils::pointee<Map::reverse_iterator>::type, Map::value_type) << (utils::pointee<Map::reverse_iterator>::type, Map::value_type) << std::endl;
    //
    //std::cout << (utils::copy_cv<const int, double>::type << (utils::copy_cv<const int, double>::type << std::endl,
    //const double);
    //std::cout << (utils::copy_cv<int, const double>::type, double) << (utils::copy_cv<int, const double>::type, double) << std::endl;
    //std::cout << (utils::copy_cv<int *volatile, long long>::type << (utils::copy_cv<int *volatile, long long>::type << std::endl,
    //volatile long long);
    //std::cout << (utils::copy_cv<const char *, int>::type, int) << (utils::copy_cv<const char *, int>::type, int) << std::endl;
    //
    //struct T {
    //    int z;
    //
    //    static T get_t() noexcept { return T(); }
    //
    //    static const T get_const_t() noexcept { return T(); }
    //};
    //
    //ForwardLike_S s;
    //
    //T t;
    //BOOST_CHECK_EQUAL(s.g(t), 'L');
    //BOOST_CHECK_EQUAL(s.g(T::get_t()), 'R');
    //BOOST_CHECK_EQUAL(s.g(T::get_const_t()), 'C');
    //
    //char f(int &) const noexcept { return 'L'; }
    //char f(const int &) const noexcept { return 'C'; }
    //char f(int &&) const noexcept { return 'R'; }
    //
    //template<typename U>
    //char g(U &&u) const noexcept {
    //    return this->f(utils::forward_like<U>(u.z));
    //}
    //
    //struct K {
    //    int p;
    //
    //    double q(float r) const { return 0.0; }
    //};
    //
    //auto pp = std::mem_fn(&K::p);
    //auto qq = std::mem_fn(&K::q);
    //
    //typedef function_traits<decltype(pp)> FTp;
    //typedef function_traits<decltype(qq)> FTq;
    //
    //std::cout << (FTp::result_type, int) << (FTp::result_type, int) << std::endl;
    //BOOST_CHECK_EQUAL(FTp::arity, 1);
    //std::cout << (FTp::arg<0>::type, K * ) << (FTp::arg<0>::type, K * ) << std::endl;
    //std::cout << (FTq::result_type, double) << (FTq::result_type, double) << std::endl;
    //BOOST_CHECK_EQUAL(FTq::arity, 2);
    //std::cout << (FTq::arg<0>::type << (FTq::arg<0>::type << std::endl,
    //const K*);
    //std::cout << (FTq::arg<1>::type, float) << (FTq::arg<1>::type, float) << std::endl;
    //
    //double x = 4;
    //auto lambda = [=](int y) { return x + y; };
    //
    //typedef function_traits<decltype(lambda)> FT;
    //std::cout << (FT::result_type, double) << (FT::result_type, double) << std::endl;
    //BOOST_CHECK_EQUAL(FT::arity, 1);
    //std::cout << (FT::arg<0>::type, int) << (FT::arg<0>::type, int) << std::endl;
    //
    //auto lambda2 = [&](float z) mutable -> void * {
    //    x = z;
    //    return nullptr;
    //};
    //typedef function_traits<decltype(lambda2)> FT2;
    //std::cout << (FT2::result_type, void * ) << (FT2::result_type, void * ) << std::endl;
    //BOOST_CHECK_EQUAL(FT2::arity, 1);
    //std::cout << (FT2::arg<0>::type, float) << (FT2::arg<0>::type, float) << std::endl;
    //
    //typedef function_traits<std::plus<int>> FTplus;
    //std::cout << (FTplus::result_type, int) << (FTplus::result_type, int) << std::endl;
    //BOOST_CHECK_EQUAL(FTplus::arity, 2);
    //std::cout << (FTplus::arg<0>::type << (FTplus::arg<0>::type << std::endl,
    //const int&);
    //std::cout << (FTplus::arg<1>::type << (FTplus::arg<1>::type << std::endl,
    //const int&);
    //
    //typedef function_traits<std::equal_to<std::string>> FTequal;
    //std::cout << (FTequal::result_type, bool) << (FTequal::result_type, bool) << std::endl;
    //BOOST_CHECK_EQUAL(FTequal::arity, 2);
    //std::cout << (FTequal::arg<0>::type << (FTequal::arg<0>::type << std::endl,
    //const std::string&);
    //std::cout << (FTequal::arg<1>::type << (FTequal::arg<1>::type << std::endl,
    //const std::string&);
    //
    //typedef function_traits<std::logical_not<void *>> FTnot;
    //std::cout << (FTnot::result_type, bool) << (FTnot::result_type, bool) << std::endl;
    //BOOST_CHECK_EQUAL(FTnot::arity, 1);
    //std::cout << (FTnot::arg<0>::type, void * const&) << (FTnot::arg<0>::type, void * const&) << std::endl;
    //
    //typedef function_traits<decltype(std::not2(std::plus<double>()))> FTnotplus;
    //std::cout << (FTnotplus::result_type, bool) << (FTnotplus::result_type, bool) << std::endl;
    //BOOST_CHECK_EQUAL(FTnotplus::arity, 2);
    //std::cout << (FTnotplus::arg<0>::type << (FTnotplus::arg<0>::type << std::endl,
    //const double&);
    //std::cout << (FTnotplus::arg<1>::type << (FTnotplus::arg<1>::type << std::endl,
    //const double&);
    //
    //
    //int f(std::pair<int, void *>, volatile double *, long(*)(size_t));
    //
    //typedef function_traits<decltype(&f)> FT;
    //
    //std::cout << (FT::result_type, int) << (FT::result_type, int) << std::endl;
    //BOOST_CHECK_EQUAL(FT::arity, 3);
    //std::cout << (FT::arg<0>::type, std::pair<int, void *>) << (FT::arg<0>::type, std::pair<int, void *>) << std::endl;
    //std::cout << (FT::arg<1>::type << (FT::arg<1>::type << std::endl,
    //volatile double*);
    //std::cout << (FT::arg<2>::type, long(*)(size_t)) << (FT::arg<2>::type, long(*)(size_t)) << std::endl;
    //
    //
    //typedef function_traits<void (&)()> FT;
    //
    //std::cout << (FT::result_type, void) << (FT::result_type, void) << std::endl;
    //BOOST_CHECK_EQUAL(FT::arity, 0);
    //
    //typedef function_traits<int (*(&&)(const long &&))[]> FT;
    //
    //std::cout << (FT::result_type, int(*)[]) << (FT::result_type, int(*)[]) << std::endl;
    //BOOST_CHECK_EQUAL(FT::arity, 1);
    //std::cout << (FT::arg<0>::type << (FT::arg<0>::type << std::endl,
    //const long&&);
    //
    //struct S {
    //    short p(const char *) noexcept;
    //
    //    unsigned int q(std::pair<int, int>, int) const volatile throw();
    //
    //    bool operator==(const S &) const;
    //
    //    virtual void r() volatile {}
    //
    //    virtual ~S() {}
    //};
    //
    //typedef function_traits<decltype(&S::p)> FTp;
    //std::cout << (FTp::owner_type, S & ) << (FTp::owner_type, S & ) << std::endl;
    //std::cout << (FTp::result_type, short) << (FTp::result_type, short) << std::endl;
    //BOOST_CHECK_EQUAL(FTp::arity, 1);
    //std::cout << (FTp::arg<0>::type << (FTp::arg<0>::type << std::endl,
    //const char*);
    //
    //typedef function_traits<decltype(&S::q)> FTq;
    //std::cout << (FTq::owner_type << (FTq::owner_type << std::endl,
    //const volatile S&);
    //std::cout << (FTq::result_type, unsigned int) << (FTq::result_type, unsigned int) << std::endl;
    //BOOST_CHECK_EQUAL(FTq::arity, 2);
    //std::cout << (FTq::arg<0>::type, std::pair<int, int>) << (FTq::arg<0>::type, std::pair<int, int>) << std::endl;
    //std::cout << (FTq::arg<1>::type, int) << (FTq::arg<1>::type, int) << std::endl;
    //
    //typedef function_traits<decltype(&S::operator==)> FTe;
    //std::cout << (FTe::owner_type << (FTe::owner_type << std::endl,
    //const S&);
    //std::cout << (FTe::result_type, bool) << (FTe::result_type, bool) << std::endl;
    //BOOST_CHECK_EQUAL(FTe::arity, 1);
    //std::cout << (FTe::arg<0>::type << (FTe::arg<0>::type << std::endl,
    //const S&);
    //
    //typedef function_traits<decltype(&S::r)> FTr;
    //std::cout << (FTr::owner_type, volatile S&); << (FTr::owner_type, volatile S&); << std::endl,
    //std::cout << (FTr::result_type, void) << (FTr::result_type, void) << std::endl;
    //BOOST_CHECK_EQUAL(FTr::arity, 0);
    //
    //const auto &sr = &S::r;
    //typedef function_traits<decltype(sr)> FTr2;
    //std::cout << (FTr2::owner_type << (FTr2::owner_type << std::endl,
    //volatile S&);
    //std::cout << (FTr2::result_type, void) << (FTr2::result_type, void) << std::endl;
    //BOOST_CHECK_EQUAL(FTr2::arity, 0);
    //
    //typedef function_traits<std::function<long(int *, char **const *)>> FT;
    //
    //std::cout << (FT::result_type, long) << (FT::result_type, long) << std::endl;
    //BOOST_CHECK_EQUAL(FT::arity, 2);
    //std::cout << (FT::arg<0>::type, int * ) << (FT::arg<0>::type, int * ) << std::endl;
    //std::cout << (FT::arg<1>::type, char * * const*) << (FT::arg<1>::type, char * * const*) << std::endl;
    //

}
