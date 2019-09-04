//
// Created by Alan de Freitas on 16/09/17 and modified by Glauber Soares.
//

#ifndef WPP_APPLICATION_HPP
#define WPP_APPLICATION_HPP

#include <functional>
#include <utility>
#include <map>
#include <sstream>
#include <thread>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <iomanip>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <utils/traits.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/beast/http.hpp> //Beast Version

#include "utils/stl_shortcuts.h"
#include "utils/container_overloads.h"
#include "utils/container_utils.h"
#include "utils/include/simple_server/server_http.hpp"
#include "utils/include/simple_server/server_https.hpp"
// #include "utils/logging.h"

#include "utility.hpp"
#include "request.h"
#include "response.h"
#include "route_properties.h"
#include "trie.h"
#include "cache.h"
#include "encryption.h"
#include "cookie_parser.h"
//#include "http_server.h"

namespace wpp {

    using namespace std::chrono_literals;

    template<typename T>
    struct function_traits
            : public function_traits<decltype(&T::operator())> {
    };
    // For generic types, directly use the result of the signature of its 'operator()'

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const>
        // we specialize for pointers to member function
    {
        enum { arity = sizeof...(Args) };
        // arity is the number of arguments.

        typedef ReturnType result_type;

        template<size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
            // the i-th argument is equivalent to the i-th tuple element of a tuple
            // composed of those arguments.
        };
    };

    template<typename T>
    struct function_traits_variadic
            : public function_traits_variadic<decltype(&T::operator())> {
    };

    template<typename... Args>
    struct pack {};

    template<typename ClassType, typename ReturnType, typename Head, typename Head2, typename Head3, typename... Tails>
    struct function_traits_variadic<ReturnType(ClassType::*)(Head, Head2, Head3, Tails...) const>
        // we specialize for pointers to member function
    {
        enum { arity = sizeof...(Tails) + 2 };

        typedef ReturnType result_type;

        typedef Head head_type;
        typedef Head2 head2_type;
        typedef Head3 head3_type;
        typedef pack<Tails...> tails_pack;

        template<size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Head, Head2, Head3, Tails...>>::type type;
            // the i-th argument is equivalent to the i-th tuple element of a tuple
            // composed of those arguments.
        };
    };


    template<int M, int N>
    struct compile_time_relational {
        static const bool greater_than = M > N ? true : false;
    };

    using boost::optional;
    using namespace std;

    //Aliases for the Boost Beast Server
    //using request = boost::beast::http::request<boost::beast::http::string_body>;
    //using response = boost::beast::http::response<boost::beast::http::string_body>;
    //using route_function = std::function<void(wpp::request&, wpp::response&)>;

    using resource_function = std::function<void(wpp::response &, wpp::request &)>;
    using middleware_function = std::function<void(wpp::response &, wpp::request &, std::string parameter, resource_function&)>;

    class application {
    public:
        friend class request;

        using self_t = application;
        using byte = unsigned char;

        template<class FUNC_TYPE = resource_function>
        route_properties &any(std::string rule, FUNC_TYPE func) {
            return this->route(
                    {method::get, method::delete_, method::head, method::post, method::put, method::options,
                     method::connect, method::trace}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &get(std::string rule, FUNC_TYPE func) {
            return this->route({method::get}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &delete_(std::string rule, FUNC_TYPE func) {
            return this->route({method::delete_}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &head(std::string rule, FUNC_TYPE func) {
            return this->route({method::head}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &post(std::string rule, FUNC_TYPE func) {
            return this->route({method::post}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &put(std::string rule, FUNC_TYPE func) {
            return this->route({method::put}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &options(std::string rule, FUNC_TYPE func) {
            return this->route({method::options}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &connect(std::string rule, FUNC_TYPE func) {
            return this->route({method::connect}, rule, func);
        }

        template<class FUNC_TYPE = resource_function>
        route_properties &trace(std::string rule, FUNC_TYPE func) {
            return this->route({method::trace}, rule, func);
        }


        // Canonical Form
        // Defining behaviour for 2 parameters (canonical form):
        // void(response&,request&)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            // append contextual prefixes
            string str;
            bool first = true;
            for (auto &&partial_prefix : this->_group_prefix_context) {
                if (first){
                    str += boost::trim_copy_if(partial_prefix,boost::is_any_of("/ "));
                    first = false;
                } else {
                    str += "/" + boost::trim_copy_if(partial_prefix,boost::is_any_of("/ "));
                }
            }
            if (str.empty()){
                _rule = boost::trim_copy_if(_rule,boost::is_any_of("/ "));
            } else {
                _rule = str + "/" + boost::trim_copy_if(_rule,boost::is_any_of("/ "));
            }
            route_properties t(_rule, vector<method>(l.begin(), l.end()), func);
            // append middlewares from the context
            for (auto &&group_middlewares : this->_group_middleware_context) {
                for (auto &&m : group_middlewares) {
                    t.middleware(m);
                }
            }
            this->_routes.push_back(t);
            return _routes.back();
        }

        route_properties &redirect(std::string from, std::string to) {
            resource_function func = [this, to](wpp::response &res, wpp::request &req) {
                auto to_route = this->route(to);
                to_route.second._func(res, req);
            };
            return this->any(from, func);
        }



        self_t &on_error(std::function<void(wpp::request, const boost::system::error_code &)> func) {
            this->on_error_ = func;
            return *this;
        }

        self_t &default_resource(std::initializer_list<wpp::method> l,
                                 std::function<void(wpp::response &res, wpp::request &req)> func) {
            for (auto &&m : l) {
                this->default_resource_[(int) m] = func;
            }
            return *this;
        }

        self_t &default_resource(std::function<void(wpp::response &res, wpp::request &req)> func) {
            default_resource({method::get}, func);
            return *this;
        }


        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &error(wpp::status_code s, FUNC func) {
            route_properties t("", {method::get, method::post, method::options, method::connect, method::delete_,
                                    method::head, method::put, method::trace}, func);
            this->_error_routes.push_back({s, t});
            return _routes.back();
        }


        void error(wpp::status_code s, wpp::response& res, wpp::request& req);
        self_t& middleware(std::string name, std::function<void(wpp::response&,wpp::request&,wpp::resource_function&)> middleware_func);
        self_t& middleware(std::string name, wpp::middleware_function func);
        self_t& middleware_group(std::string name, initializer_list<string> middlewares);
        self_t& group(initializer_list<std::string> middlewares, std::function<void(application&)> register_routes_func);
        self_t& group(std::string prefix, initializer_list<std::string> middlewares, std::function<void(application&)> register_routes_func);

        // The route function depends first of all on the number of parameters
        // 2+ parameters
        template<typename FUNC, typename std::enable_if<compile_time_relational<function_traits<FUNC>::arity, 2>::greater_than>::type * = nullptr>
        route_properties &
        route(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            return this->route2plus(l, _rule, func, parameters_consumed);
        }

        // 2 parameters
        template<typename FUNC, typename std::enable_if<function_traits<FUNC>::arity == 2>::type * = nullptr>
        route_properties &
        route(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            return this->route2p(l, _rule, func, parameters_consumed);
        }

        // 1 parameter
        template<typename FUNC, typename std::enable_if<function_traits<FUNC>::arity == 1>::type * = nullptr>
        route_properties &
        route(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            return this->route1p(l, _rule, func, parameters_consumed);
        }

        // 0 parameters (return type cannot be void)
        template<typename FUNC, typename std::enable_if<function_traits<FUNC>::arity == 0>::type * = nullptr>
        route_properties &route(std::initializer_list<wpp::method> l,
                                std::string _rule,
                                FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) {
                res = (func());
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }


        // when we have query parameters, this parameters are converted according to the type
        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, int>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoi(*q);
            } else {
                return 0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<int>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoi(*q);
            } else {
                return optional<int>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, long int>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stol(*q);
            } else {
                return 0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<long int>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stol(*q);
            } else {
                return optional<long int>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, unsigned int>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoul(*q);
            } else {
                return 0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<unsigned int>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoul(*q);
            } else {
                return optional<unsigned int>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, long long>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoll(*q);
            } else {
                return 0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<long long>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoll(*q);
            } else {
                return optional<long long>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, unsigned long long>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoull(*q);
            } else {
                return 0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<unsigned long long>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stoull(*q);
            } else {
                return optional<unsigned long long>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, float>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stof(*q);
            } else {
                return 0.0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<float>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stof(*q);
            } else {
                return optional<float>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, double>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stod(*q);
            } else {
                return 0.0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<double>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stod(*q);
            } else {
                return optional<double>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, long double>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stold(*q);
            } else {
                return 0.0;
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<long double>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::stold(*q);
            } else {
                return optional<long double>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, std::string>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return string(*q);
            } else {
                return string("");
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<std::string>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            return q;
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, char *>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::string(*q);
            } else {
                return string("");
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<char *>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::string(*q);
            } else {
                return optional<char *>{};
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, const char *>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::string(*q);
            } else {
                return string("");
            }
        }

        template<typename QUERY_PARAM, typename std::enable_if<std::is_same<QUERY_PARAM, optional<const char *>>::value>::type * = nullptr>
        QUERY_PARAM convert_query_parameter(optional<std::string> q) {
            if (q) {
                return std::string(*q);
            } else {
                return optional<const char *>{};
            }
        }


        // void(request&,response&)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [this, func](wpp::response &res,
                                                                                               wpp::request &req) -> void {
                func(req, res);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }


        // void(response&,parameter)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {

                std::cout << "Parameter " << 1 << " receiving query parameter " << parameters_consumed << " ("
                          << req.query_parameters.get(parameters_consumed) << ")" << std::endl;
                func(res, this->convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                        req.query_parameters.get_optional(parameters_consumed)));
            };
            return this->route(l, _rule, canonical_func, parameters_consumed + 1);
        }


        // response(response&,request&)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                response res2 = func(res, req);
                res.merge(res2);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(request&,response&)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(req, res);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(request&,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(req,
                           this->convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                   req.query_parameters.get_optional(parameters_consumed)));
            };
            return this->route(l, _rule, canonical_func, parameters_consumed + 1);
        }

        // response(response&,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(res,
                           this->convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                   req.query_parameters.get_optional(parameters_consumed)));
            };
            return this->route(l, _rule, canonical_func, parameters_consumed + 1);
        }

        // response(parameter,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(convert_query_parameter<typename function_traits<FUNC>::template arg<0>::type>(
                        req.query_parameters.get_optional(parameters_consumed)),
                           convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                   req.query_parameters.get_optional(parameters_consumed + 1)));
            };
            return this->route(l, _rule, canonical_func, parameters_consumed + 2);
        }



        // defining behaviour for 1 parameter
        // void(response&)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route1p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                func(res);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route1p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(convert_query_parameter<typename function_traits<FUNC>::template arg<0>::type>(
                        req.query_parameters.get_optional(parameters_consumed)));
            };
            return this->route(l, _rule, canonical_func, parameters_consumed + 1);
        }

        // response(response&)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route1p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(res);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(request&)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route1p(std::initializer_list<wpp::method> l, std::string _rule, FUNC func, int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func = [parameters_consumed, this, func](
                    wpp::response &res,
                    wpp::request &req) -> void {
                res.parent_application = this;
                req.parent_application = this;
                res = func(req);
            };
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // void(response&,request&,parameter)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        func(res, req,
                             convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                     req.query_parameters.get_optional(parameters_consumed)));
                    };
            parameters_consumed++;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // void(request&,response&,parameter)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        func(req, res,
                             convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                     req.query_parameters.get_optional(parameters_consumed)));
                    };
            parameters_consumed++;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // void(response&,parameter,parameter)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        func(res, convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                req.query_parameters.get_optional(parameters_consumed)),
                             convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                     req.query_parameters.get_optional(parameters_consumed + 1)));
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(response,request,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        res = (func(res, req,
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                            req.query_parameters.get_optional(parameters_consumed))));
                    };
            parameters_consumed++;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(request,response,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        res = (func(req, res,
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                            req.query_parameters.get_optional(
                                                    parameters_consumed))));
                    };
            parameters_consumed++;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(response,parameter,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        res = (func(res,
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                            req.query_parameters.get_optional(
                                                    parameters_consumed)),
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                            req.query_parameters.get_optional(
                                                    parameters_consumed + 1))));
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // response(request,parameter,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        res = (func(req,
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                            req.query_parameters.get_optional(
                                                    parameters_consumed)),
                                    convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                            req.query_parameters.get_optional(
                                                    parameters_consumed + 1))));
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // // response(parameter,parameter,parameter)
        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                function_traits<FUNC>::arity == 3 &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<0>::type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::template arg<1>::type, wpp::response &>::value>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            std::function<void(wpp::response &, wpp::request &)> canonical_func =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        res = (func(
                                convert_query_parameter<typename function_traits<FUNC>::template arg<0>::type>(
                                        req.query_parameters.get_optional(
                                                parameters_consumed)),
                                convert_query_parameter<typename function_traits<FUNC>::template arg<1>::type>(
                                        req.query_parameters.get_optional(
                                                parameters_consumed + 1)),
                                convert_query_parameter<typename function_traits<FUNC>::template arg<2>::type>(
                                        req.query_parameters.get_optional(
                                                parameters_consumed + 2))));
                    };
            parameters_consumed += 3;
            return this->route(l, _rule, canonical_func, parameters_consumed);
        }

        // workaround to unpack the tails (packing is a workaround to pass it as parameter)
        template<typename FUNC, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            return route2plus(l, _rule, func, typename function_traits_variadic<FUNC>::tails_pack(),
                              parameters_consumed);
        }

        // void(response, request, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits_variadic<FUNC>::head_type, wpp::response &>::value &&
                std::is_same<typename function_traits_variadic<FUNC>::head2_type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        func(res, req, head_param, ts...);
                    };
            parameters_consumed++;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // void(request, response, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits_variadic<FUNC>::head_type, wpp::request &>::value &&
                std::is_same<typename function_traits_variadic<FUNC>::head2_type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        func(res, req, head_param, ts...); };
            parameters_consumed++;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // void(request, parameter, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits_variadic<FUNC>::head_type, wpp::response &>::value &&
                !std::is_same<typename function_traits_variadic<FUNC>::head2_type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param1 = convert_query_parameter<typename function_traits_variadic<FUNC>::head2_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        auto head_param2 = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed + 1));
                        func(res, head_param1, head_param2, ts...);
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // response(response,request, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits_variadic<FUNC>::head_type, wpp::response &>::value &&
                std::is_same<typename function_traits_variadic<FUNC>::head2_type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        res = func(res, req, head_param, ts...);
                    };
            parameters_consumed++;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // response(request, response, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits_variadic<FUNC>::head_type, wpp::request &>::value &&
                std::is_same<typename function_traits_variadic<FUNC>::head2_type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        res = func(req, res, head_param, ts...);
                    };
            parameters_consumed++;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // response(response, parameter, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits<FUNC>::head_type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::head2_type, wpp::request &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param1 = convert_query_parameter<typename function_traits_variadic<FUNC>::head2_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        auto head_param2 = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed + 1));
                        res = (func(res, head_param1, head_param2, ts...));
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // response(request, parameter, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                std::is_same<typename function_traits<FUNC>::head_type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::head_type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param1 = convert_query_parameter<typename function_traits_variadic<FUNC>::head2_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        auto head_param2 = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed + 1));
                        res = func(req, head_param1, head_param2, ts...);
                    };
            parameters_consumed += 2;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        // response(parameter, parameter, parameter, tails...)
        template<typename FUNC, typename... Tails, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than &&
                !std::is_same<typename function_traits<FUNC>::head_type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::head_type, wpp::response &>::value &&
                !std::is_same<typename function_traits<FUNC>::head2_type, wpp::request &>::value &&
                !std::is_same<typename function_traits<FUNC>::head2_type, wpp::response &>::value>::type * = nullptr>
        route_properties &
        route2plus(std::initializer_list<wpp::method> l,
                   std::string _rule,
                   FUNC func,
                   pack<Tails...>,
                   int parameters_consumed = 0) {
            std::function<void(wpp::response &res, wpp::request &req, Tails ... ts)> func_new =
                    [parameters_consumed, this, func](wpp::response &res, wpp::request &req, Tails ... ts) -> void {
                        res.parent_application = this;
                        req.parent_application = this;
                        auto head_param1 = convert_query_parameter<typename function_traits_variadic<FUNC>::head_type>(
                                req.query_parameters.get_optional(parameters_consumed));
                        auto head_param2 = convert_query_parameter<typename function_traits_variadic<FUNC>::head2_type>(
                                req.query_parameters.get_optional(parameters_consumed + 1));
                        auto head_param3 = convert_query_parameter<typename function_traits_variadic<FUNC>::head3_type>(
                                req.query_parameters.get_optional(parameters_consumed + 1));
                        res = (func(head_param1, head_param2, head_param3, ts...));
                    };
            parameters_consumed += 3;
            return this->route(l, _rule, func_new, parameters_consumed);
        }

        template<typename FUNC, typename std::enable_if<
                !std::is_same<typename function_traits<FUNC>::result_type, void>::value &&
                compile_time_relational<function_traits<FUNC>::arity, 3>::greater_than>::type * = nullptr>
        route_properties &route2plus(std::initializer_list<wpp::method> l,
                                     std::string _rule,
                                     FUNC func,
                                     int parameters_consumed = 0) {
            return route2plus(l, _rule, func, typename function_traits_variadic<FUNC>::tails_pack(),
                              parameters_consumed);
        }

        std::pair<resource_function, routing_params> get_resource(std::string path, method m);
        unsigned &port();
        self_t &port(unsigned port);
        self_t &web_root_path(string path);
        string &web_root_path();
        self_t &secure(string certificate_file, string key_file);
        bool secure();
        self_t &assets_root_path(string path);
        string &assets_root_path();
        self_t &session_name(string name);
        string &session_name();
        self_t& guard_call_back(std::function<json(wpp::request&)> __guard_call_back);
        std::function<json(wpp::request&)> &guard_call_back();
        self_t &max_session_inactive_time(std::chrono::duration<double, std::milli> time);
        std::chrono::duration<double, std::milli> &max_session_inactive_time();
        self_t &templates_root_path(string path);
        self_t &user_agent_parser_root_path(string path)
        self_t &lambda(string name, std::function<std::string(const std::string&)> f);
        self_t &lambda(string name, std::function<std::string(const std::string&,renderer&)> f);

        response::view view(string filename, wpp::json json_data);
        response::view view(string filename, wpp::json json_data, request& req);

        self_t& view_data(std::string filename, std::function<wpp::json()> func);
        self_t &multithreaded(bool on_off = true);

        string url_for(string route_name);
        string asset(string asset_name);
        pair<bool, route_properties> route(string route_name);

        self_t &redirect(string route_name, wpp::response &res, wpp::request &req);
        cache& get_cache();

        void setup_trie();

        template <typename Pointer_to_Server_Request = std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request>>
        void simple_server_to_wpp_request(application& this_application,Pointer_to_Server_Request& request,wpp::request& req){
            req.parent_application = &this_application;
            // convert/parse request
            // method / protocol
            req.method_requested = wpp::method_enum(request->method);
            req.method_string = request->method;
            req.http_version = request->http_version;
            // client
            req.remote_endpoint_address = request->remote_endpoint_address();
            req.remote_endpoint_port = request->remote_endpoint_port();
            // url
            req.url_ = request->path;
            // Content
            req.body = request->content.string();
            // Headers and cookies
            req.headers = ci_map(request->header.begin(), request->header.end());
            req.parse_cookies();
            // Query string
            req.query_string = std::move(request->query_string);
            req.request_parameters = QueryString::parse(req.query_string);
            // Posted content
            unordered_multimap<std::string, std::string>::iterator content_iterator = req.headers.find("Content-Type");
            if (req.method_requested != method::get && !req.body.empty() && content_iterator->second == "application/x-www-form-urlencoded"){
                // todo: Recognize other POST Content-Types (json and encrypted file)
                CaseInsensitiveMultimap post_params = QueryString::parse(req.body);
                std::move(post_params.begin(),post_params.end(),std::inserter(req.request_parameters,req.request_parameters.end()));
                wpp::CaseInsensitiveMultimap::iterator method_parameter_iter = req.request_parameters.find("_method");
                if (method_parameter_iter != req.request_parameters.end()){
                    req.method_requested = wpp::method_enum(method_parameter_iter->second);
                    req.method_string = wpp::method_string(req.method_requested);
                }
            }
        }

        // Trick to define a recursive function within this scope (for example purposes)
        // the trick reads a piece of data and sends little by little
        template <class HttpServer>
        class FileServer {
        public:
            static void
            read_and_send(const std::shared_ptr<typename HttpServer::Response> &response,
                          const std::shared_ptr<ifstream> &ifs) {
                // Read and send 128 KB at a time
                std::array<char, 1024 * 128> buffer;
                streamsize read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount();
                // if we could read more than 0 bytes
                if (read_length > 0) {
                    // write the buffer to response
                    response->write(&buffer[0], read_length);
                    // if we had to use the whole buffer (i.e. if there's more to read)
                    if (read_length == static_cast<streamsize>(buffer.size())) {
                        // send more to be sent
                        response->send(
                                [response, ifs](const SimpleWeb::error_code &ec) {
                                    if (!ec) {
                                        // this "more to be sent" recursively includes the read data...
                                        read_and_send(response, ifs);
                                    } else {
                                        cerr << "Connection interrupted" << endl;
                                    }
                                });
                    }
                }
            }
        };

        template<class HttpServer>
        HttpServer* return_server_object();

        self_t &start() {
            if (!this->secure()){
                return start_aux<SimpleWeb::Server<SimpleWeb::HTTP>>();
            } else {
                return start_aux<SimpleWeb::Server<SimpleWeb::HTTPS>>();
            }
        }

        template <class HttpServer>
        self_t &start_aux() {
            //std::cout << "http://localhost:" << this->_port << "/" << std::endl;
            std::cout << this->web_root_path() << std::endl;
            // sort routes
            utils::sort(_routes, [](route_properties &a, route_properties &b) { return a._uri < b._uri; });
            // optimize data in a trie
            setup_trie();
            std::cout << "ROUTES TRIE: " << std::endl;
            _route_trie.debug_print();
            using namespace std::placeholders;
            // Replace middleware groups by middleware routes
            for (route_properties &route : _routes) {
                vector<string> _middleware_routes;
                for (string &middlename : route._middleware) {
                    if (this->_middleware_groups.count(middlename)){
                        _middleware_routes.insert(_middleware_routes.end(),_middleware_groups[middlename].begin(),_middleware_groups[middlename].end());
                    } else if (_middleware_functions.count(middlename)){
                        _middleware_routes.push_back(middlename);
                    }
                }
                route._middleware = _middleware_routes;
            }
            // Apply middleware to routes
            for (route_properties &route : _routes) {
                for (vector<string>::reverse_iterator iter = route._middleware.rbegin(); iter != route._middleware.rend(); iter++) {
                    string middleware_declaration = *iter;
                    string middleware_name;
                    string middleware_parameter;
                    size_t found = middleware_declaration.rfind(':');
                    if (found!=std::string::npos){
                        middleware_parameter = middleware_declaration.substr(found+1);
                        middleware_name = middleware_declaration.substr(0,found);
                    } else {
                        middleware_name = middleware_declaration;
                    }
                    std::map<string, middleware_function>::iterator middleware_pair_iter = _middleware_functions.find(middleware_name);
                    const bool the_middleware_exists = middleware_pair_iter != this->_middleware_functions.end();
                    if (the_middleware_exists){
                        route._func = std::bind(middleware_pair_iter->second,_1,_2,middleware_parameter,route._func);
                    }
                }
            }

            // Apply settings
            using namespace std;

            unique_ptr<HttpServer> server(return_server_object<HttpServer>());

            server->config.port = this->_port;
            if (this->_multithreaded) {
                server->config.thread_pool_size = std::thread::hardware_concurrency();
            }

            // register all routes by method
            application &this_application = *this;
            for (int i = 0; i < number_of_methods(); ++i) {
                server->default_resource[method_string(
                        (method) i)] = [&this_application,i](std::shared_ptr<typename HttpServer::Response> response,
                                                             std::shared_ptr<typename HttpServer::Request> request) {

                    wpp::request req;
                    wpp::response res;
                    res.parent_application = &this_application;
                    this_application.simple_server_to_wpp_request(this_application, request, req);

                    // Look for the route request
                    std::tuple<bool, unsigned, routing_params> wpp_reply = this_application._route_trie.find(
                            req.url_, req.method_requested);
                    req.query_parameters = std::move(std::get<2>(wpp_reply));
                    const unsigned route_pos = std::get<1>(wpp_reply);
                    const bool a_valid_route_was_found = std::get<0>(wpp_reply);
                    //std::cout << method_string((method) i) << " Request on " << req.url_ << std::endl;
                    // Response to the request
                    if (a_valid_route_was_found) {
                        // Process request
                        std::cout << method_string((method) i) << " Request: " << req.url_ << std::endl;
                        req.current_route = &this_application._routes[route_pos];
                        this_application._routes[route_pos]._func(res, req);
                        // Write response
                        if (res._file_response && res._file_response->good()){
                            // filesize
                            auto length = res._file_response->tellg();
                            // go to beggining
                            res._file_response->seekg(0, ios::beg);
                            SimpleWeb::CaseInsensitiveMultimap header;
                            header.emplace("Content-Length", to_string(length));
                            response->write(header);
                            FileServer<HttpServer>::read_and_send(response, res._file_response);
                        } else {
                            response->write((SimpleWeb::StatusCode) ((int) res.code), res.body, SimpleWeb::CaseInsensitiveMultimap(res.headers.begin(), res.headers.end()));

                        }
                        std::cout << "Response: " << (int) res.code << " on route \""
                                  << this_application._routes[std::get<1>(wpp_reply)]._name << "\"" << std::endl;
                    } else if (this_application.default_resource_[i]) {
                        resource_function& backup_handle = *this_application.default_resource_[i];
                        route_properties r = route_properties(req.url_,{wpp::method(i)},backup_handle);
                        req.current_route = &r;
                        req.current_route->name("backup_route");
                        backup_handle(res, req);
                        res.write_cookie_headers();
                        if (res._file_response && res._file_response->good()){
                            auto length = res._file_response->tellg();
                            res._file_response->seekg(0, ios::beg);
                            SimpleWeb::CaseInsensitiveMultimap header;
                            header.emplace("Content-Length", to_string(length));
                            response->write(header);
                            FileServer<HttpServer>::read_and_send(response, res._file_response);
                        } else {
                            response->write((SimpleWeb::StatusCode) ((int) res.code), res.body, SimpleWeb::CaseInsensitiveMultimap(res.headers.begin(), res.headers.end()));
                        }
                    } else {
                        this_application.error(wpp::status_code::client_error_not_found, res, req);
                        res.write_cookie_headers();
                        response->write((SimpleWeb::StatusCode) ((int) res.code), res.body, SimpleWeb::CaseInsensitiveMultimap(res.headers.begin(), res.headers.end()));
                    }
                };
            }

            // Routes
            server->on_error = [](std::shared_ptr<typename HttpServer::Request> req, const SimpleWeb::error_code &ec) {
                std::cout << ec.message() << std::endl;
            };

            server->start();
            return *this;
        }

        self_t& set_keys();

        string encrypt(string text);
        string decrypt(string text, string fallback = "");
        string decrypt(string text, bool& success);
        string digest(string message);

    private:
        ///////////////////////////////////////////////////////////////
        //                         MODEL                             //
        ///////////////////////////////////////////////////////////////
        string _assets_root_path = "model/assets";

        ///////////////////////////////////////////////////////////////
        //                          VIEW                             //
        ///////////////////////////////////////////////////////////////
        string _templates_root_path = "view/templates";
        string _user_agent_parser_root_path = "";
        basic_data<response::view::string_type> _lambdas;
        std::unordered_map<std::string,std::function<wpp::json()>> _view_data;
        unordered_map<std::string, response::pre_processed_view> _pre_processed_views;
        std::unordered_map<mustache::string_type, response::pre_processed_partial<mustache::string_type>>
                _pre_processed_partials;

        ///////////////////////////////////////////////////////////////
        //                      CONTROLLER                           //
        ///////////////////////////////////////////////////////////////

        // Routes
        //Vector for newest routes
        //std::vector<std::pair<wpp::status_code , route_function>> _routes_Error;
        //std::vector<std::pair<std::regex, route_function>> _routes;
        std::vector<route_properties> _routes;
        std::unordered_map<string, unsigned> _route_by_name;
        Trie _route_trie;
        std::vector<pair<wpp::status_code, route_properties>> _error_routes;
        std::map<std::string, middleware_function> _middleware_functions;
        std::map<std::string, vector<std::string>> _middleware_groups;
        // Route groups
        std::vector<std::vector<std::string>> _group_middleware_context;
        std::vector<std::string> _group_prefix_context;
        // Default routes
        std::array<optional<resource_function>, number_of_methods()> default_resource_;
        std::function<void(wpp::request, const boost::system::error_code &)> on_error_;
        // Guard callback (function the return user data in json format so routes can control access)
        std::function<json(wpp::request&)> _guard_call_back;

        ///////////////////////////////////////////////////////////////
        //                          SETTINGS                         //
        ///////////////////////////////////////////////////////////////
        // Settings
        unsigned _port = 8080;
        bool _multithreaded = true;
        string _web_root_path = "localhost:8080";
        // Application utilities
        size_t _cache_size{100000};
        std::chrono::duration<double, std::milli> _cache_time{24h};
        class cache cache_{24h, 10000};
        // Chryptographic keys
        vector<byte> key;
        vector<byte> iv;
        string _key_file;
        string _certificate_file;
        // Cache
        // Session
        string session_name_ = {"application_id"};
        std::chrono::duration<double, std::milli> max_session_inactive_time_ = 5min;
    };

    template <>
    SimpleWeb::Server<SimpleWeb::HTTP>* application::return_server_object<SimpleWeb::Server<SimpleWeb::HTTP>>() {
        return new SimpleWeb::Server<SimpleWeb::HTTP>();
    }

    std::pair<resource_function, routing_params> application::get_resource(std::string path, method m) {
        return std::pair<resource_function, routing_params>();
    }

    template <>
    SimpleWeb::Server<SimpleWeb::HTTPS>* application::return_server_object<SimpleWeb::Server<SimpleWeb::HTTPS>>() {
        cout << "Creating a secure server" << endl;
        return new SimpleWeb::Server<SimpleWeb::HTTPS>(this->_certificate_file, this->_key_file);
    }


};


// TODO: Implement different response types
// response.redirect().route("routename")
// response.redirect().route("routename", {'id',20})
// response.redirect().url('http://www.foo.com')


// TODO: Adapt the crow::request to wpp::request implementing the functions
// string name = request.input("name");
// if (request.is("admin/*"){ // foo } // test url against regex
// auto method = request.method();
// if (request.isMethod(method::post)) { //    }
// json input = request.all();
// string name = request.input("name", "Sally");
// name = request.input('products.0.name');
// vector<string> names = request.input('products.*.name');
// json input = request.only({"username", "password"});
// json input = request.except({"password", "credit_card"});
// if (request.has("name")) { // foo }
// request.flash(); // save current input in the session
// request->flash_only({"username", "email"});
// request->flash_except({"password", "credit_card"});
// return redirect("form").with_input(); // flash and redirect
// return redirect("form").withInput( request.except("password") );
// string username = request.old("username"); // from last request
// string value = request.cookie("name");
// return response('Hello World')->cookie("name", "value", $minutes);
// file = request.file("photo");
// if ( request.has_file("photo")){}
// if ( request.file("photo").is_valid()){}
// if ( request.file("photo").path()){}
// if ( request.file("photo").extension()){}
// path = request.file("photo").store("images"); // generate unique id
// path = request.file("photo").store_as("images","filename.jpg");

// TODO: Adapt the crow::response to wpp::response implementing the functions
//  return "Hello World";
//  return json;
//  return container;
//  return response("hello world",200).header("Content-Type", "text/plain");
//  return response("hello world",200).header("Content-Type", "text/plain");
//  return response(content).cookie("name", str_);
//  return response::redirect(url);
//  return response::route(name);
//  return response::route(name).with("status", "Profile updated!");
//  return response::route(name,json_param);
//  return response::back().with_input();
//  return response::back().with_input();
//  return response::view("template.html",json_data);
//  return response::json(json_data);
//  return response::download(path_to_file); // forces user download
//  return response::file(path_to_file); // displays file

// TODO: Implement views
//  if (view::exists("home.html")) {};
//  return view("home.html");
//  return view("home.html",data);
//  return view("home.html",data);
//  return view("home.html",data).with(data); // just as usual response



// TODO: Implement validator
// wpp::validate(request, {
//     {"title" , "required|unique:posts|max:255"},
//     {"body" , "required"},
//     {"author.name" , "required"}
// });
// validator.errors().all();
// define error messages (per error and ad hoc)
// Rules

// DATA TYPES (can be only one of those)
// Active URL
// Alpha
// Alpha Dash
// Alpha Numeric
// Array
// Boolean
// Date
// Date Format
// Digits
// E-Mail
// File
// Image (File)
// Integer
// IP Address
// JSON
// Numeric
// Regular Expression
// String
// Timezone
// URL

// RULES ON DATA
// After (Date)
// After Or Equal (Date)
// Before (Date)
// Before Or Equal (Date)
// Between
// Different
// Dimensions (Image Files)
// Digits Between
// Distinct
// Exists (Database)
// Filled
// In
// In Array
// Max
// Min
// Nullable
// Not In
// Present
// Required
// Required If
// Required Unless
// Required With
// Required With All
// Required Without
// Required Without All
// Same
// Size
// Unique (Database)

// TODO: Implement database connection and ORM on cmake
// make script/program to read the DB and create C++ objects to access data

#endif //WPP_APPLICATION_HPP
