//
// Created by Alan de Freitas on 24/06/17.
//

#ifndef WPP_RULE_H
#define WPP_RULE_H

#include <cstdint>
#include <utility>
#include <tuple>
#include <unordered_map>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "common.h"
#include "http_response.h"
#include "http_request.h"
#include "utility.h"
#include "logging.h"
#include "websocket.h"
#include "const_str.h"
#include "function_traits.h"

namespace wpp {
    /// Base Rule to Match from URL/Route to Function
    // keep the rule, the name, the methods (http verbs of the rule), pointer to another "rule_to_upgrade"
    class BaseRule
    {
    public:
        // move from another rule
        BaseRule(std::string rule)
                : rule_(std::move(rule))
        {
        }

        virtual ~BaseRule()
        {
        }

        // validate (ad hoc)
        virtual void validate() = 0;

        // upgrade (returns the pointer to another "rule to upgrade")
        std::unique_ptr<BaseRule> upgrade()
        {
            if (rule_to_upgrade_)
                return std::move(rule_to_upgrade_);
            return {};
        }

        // handle (virtual)
        virtual void handle(const request&, response&, const routing_params&) = 0;

        // handle for upgrade function (returns 404)
        virtual void handle_upgrade(const request&, response& res, SocketAdaptor&&)
        {
            res = response(StatusCode::NotFound404);
            res.end();
        }

#ifdef WPP_ENABLE_SSL
        // handle upgrade for if server is SSL
        virtual void handle_upgrade(const request&, response& res, SSLAdaptor&&)
		{
			res = response(StatusCode::NotFound404);
			res.end();
		}
#endif

        // returns an uint32 that represents all the methods (0 or 1 in the 32 bits)
        uint32_t get_methods()
        {
            return methods_;
        }

    protected:
        // default method is get
        uint32_t methods_{1<<(int)HTTPMethod::Get};

        // rule signature
        std::string rule_;
        // rule name
        std::string name_;

        // "rule to upgrade"
        std::unique_ptr<BaseRule> rule_to_upgrade_;

        // friends with router class (to be declared much later to keep all routes)
        friend class Router;
        template <typename T>
        friend struct RuleParameterTraits;
    };

    // helper to get parameters of the handler/controller function using const_str
    namespace detail
    {

        namespace routing_handler_call_helper
        {
            template <typename T, int Pos>
            struct call_pair
            {
                using type = T;
                static const int pos = Pos;
            };

            template <typename H1>
            struct call_params
            {
                H1& handler;
                const routing_params& params;
                const request& req;
                response& res;
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename S1, typename S2>
            struct call
            {
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename ... Args1, typename ... Args2>
            struct call<F, NInt, NUint, NDouble, NString, const_str::S<int64_t, Args1...>, const_str::S<Args2...>>
            {
                void operator()(F cparams)
                {
                    using pushed = typename const_str::S<Args2...>::template push_back<call_pair<int64_t, NInt>>;
                    call<F, NInt+1, NUint, NDouble, NString,
                            const_str::S<Args1...>, pushed>()(cparams);
                }
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename ... Args1, typename ... Args2>
            struct call<F, NInt, NUint, NDouble, NString, const_str::S<uint64_t, Args1...>, const_str::S<Args2...>>
            {
                void operator()(F cparams)
                {
                    using pushed = typename const_str::S<Args2...>::template push_back<call_pair<uint64_t, NUint>>;
                    call<F, NInt, NUint+1, NDouble, NString,
                            const_str::S<Args1...>, pushed>()(cparams);
                }
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename ... Args1, typename ... Args2>
            struct call<F, NInt, NUint, NDouble, NString, const_str::S<double, Args1...>, const_str::S<Args2...>>
            {
                void operator()(F cparams)
                {
                    using pushed = typename const_str::S<Args2...>::template push_back<call_pair<double, NDouble>>;
                    call<F, NInt, NUint, NDouble+1, NString,
                            const_str::S<Args1...>, pushed>()(cparams);
                }
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename ... Args1, typename ... Args2>
            struct call<F, NInt, NUint, NDouble, NString, const_str::S<std::string, Args1...>, const_str::S<Args2...>>
            {
                void operator()(F cparams)
                {
                    using pushed = typename const_str::S<Args2...>::template push_back<call_pair<std::string, NString>>;
                    call<F, NInt, NUint, NDouble, NString+1,
                            const_str::S<Args1...>, pushed>()(cparams);
                }
            };

            template <typename F, int NInt, int NUint, int NDouble, int NString, typename ... Args1>
            struct call<F, NInt, NUint, NDouble, NString, const_str::S<>, const_str::S<Args1...>>
            {
                void operator()(F cparams)
                {
                    cparams.handler(
                            cparams.req,
                            cparams.res,
                            cparams.params.template get<typename Args1::type>(Args1::pos)...
                    );
                }
            };

            /// Wraps the func with the arguments in a standard format
            /// \tparam Func
            /// \tparam ArgsWrapped
            template <typename Func, typename ... ArgsWrapped>
            struct Wrapped
            {
                template <typename ... Args>
                void set(Func f, typename std::enable_if<
                        !std::is_same<typename std::tuple_element<0, std::tuple<Args..., void>>::type, const request&>::value
                        , int>::type = 0)
                {
                    handler_ = (
#ifdef WPP_CAN_USE_CPP14
                            [f = std::move(f)]
#else
                            [f]
#endif
                                    (const request&, response& res, Args... args){
                                res = response(f(args...));
                                res.end();
                            });
                }

                template <typename Req, typename ... Args>
                struct req_handler_wrapper
                {
                    req_handler_wrapper(Func f)
                            : f(std::move(f))
                    {
                    }

                    void operator()(const request& req, response& res, Args... args)
                    {
                        res = response(f(req, args...));
                        res.end();
                    }

                    Func f;
                };

                template <typename ... Args>
                void set(Func f, typename std::enable_if<
                        std::is_same<typename std::tuple_element<0, std::tuple<Args..., void>>::type, const request&>::value &&
                        !std::is_same<typename std::tuple_element<1, std::tuple<Args..., void, void>>::type, response&>::value
                        , int>::type = 0)
                {
                    handler_ = req_handler_wrapper<Args...>(std::move(f));
                    /*handler_ = (
                        [f = std::move(f)]
                        (const request& req, response& res, Args... args){
                             res = response(f(req, args...));
                             res.end();
                        });*/
                }

                template <typename ... Args>
                void set(Func f, typename std::enable_if<
                        std::is_same<typename std::tuple_element<0, std::tuple<Args..., void>>::type, const request&>::value &&
                        std::is_same<typename std::tuple_element<1, std::tuple<Args..., void, void>>::type, response&>::value
                        , int>::type = 0)
                {
                    handler_ = std::move(f);
                }

                template <typename ... Args>
                struct handler_type_helper
                {
                    using type = std::function<void(const wpp::request&, wpp::response&, Args...)>;
                    using args_type = const_str::S<typename const_str::promote_t<Args>...>;
                };

                template <typename ... Args>
                struct handler_type_helper<const request&, Args...>
                {
                    using type = std::function<void(const wpp::request&, wpp::response&, Args...)>;
                    using args_type = const_str::S<typename const_str::promote_t<Args>...>;
                };

                template <typename ... Args>
                struct handler_type_helper<const request&, response&, Args...>
                {
                    using type = std::function<void(const wpp::request&, wpp::response&, Args...)>;
                    using args_type = const_str::S<typename const_str::promote_t<Args>...>;
                };

                typename handler_type_helper<ArgsWrapped...>::type handler_;

                void operator()(const request& req, response& res, const routing_params& params)
                {
                    detail::routing_handler_call_helper::call<
                            detail::routing_handler_call_helper::call_params<
                                    decltype(handler_)>,
                            0, 0, 0, 0,
                            typename handler_type_helper<ArgsWrapped...>::args_type,
                            const_str::S<>
                    >()(
                            detail::routing_handler_call_helper::call_params<
                                    decltype(handler_)>
                                    {handler_, params, req, res}
                    );
                }
            };

        }
    }

    // Rule (kind of "empty") underlying all rules (dynamic and "static")
    class WebSocketRule : public BaseRule // (baserule contains methods, rule, name...)
    {
        using self_t = WebSocketRule;
    public:
        // construct baserule
        WebSocketRule(std::string rule)
                : BaseRule(std::move(rule))
        {
        }

        // nothing to do
        void validate() override
        {
        }

        // handling is simply returning 404 (last case)
        void handle(const request&, response& res, const routing_params&) override
        {
            res = response(404);
            res.end();
        }

        // create connection
        void handle_upgrade(const request& req, response&, SocketAdaptor&& adaptor) override
        {
            new wpp::websocket::Connection<SocketAdaptor>(req, std::move(adaptor), open_handler_, message_handler_, close_handler_, error_handler_);
        }
#ifdef WPP_ENABLE_SSL
        void handle_upgrade(const request& req, response&, SSLAdaptor&& adaptor) override
		{
			new wpp::websocket::Connection<SSLAdaptor>(req, std::move(adaptor), open_handler_, message_handler_, close_handler_, error_handler_);
		}
#endif

        // set functions that handle the connection (open, message, close, error)
        template <typename Func>
        self_t& onopen(Func f)
        {
            open_handler_ = f;
            return *this;
        }

        template <typename Func>
        self_t& onmessage(Func f)
        {
            message_handler_ = f;
            return *this;
        }

        template <typename Func>
        self_t& onclose(Func f)
        {
            close_handler_ = f;
            return *this;
        }

        template <typename Func>
        self_t& onerror(Func f)
        {
            error_handler_ = f;
            return *this;
        }

    protected:
        std::function<void(wpp::websocket::connection&)> open_handler_;
        std::function<void(wpp::websocket::connection&, const std::string&, bool)> message_handler_;
        std::function<void(wpp::websocket::connection&, const std::string&)> close_handler_;
        std::function<void(wpp::websocket::connection&)> error_handler_;
    };

    // parameters common to all rules
    template <typename T>
    struct RuleParameterTraits
    {
        using self_t = T;
        // create a new empty websocket rule and attribute to the rule
        WebSocketRule& websocket()
        {
            auto p =new WebSocketRule(((self_t*)this)->rule_);
            ((self_t*)this)->rule_to_upgrade_.reset(p);
            return *p;
        }

        // set name
        self_t& name(std::string name) noexcept
        {
            ((self_t*)this)->name_ = std::move(name);
            return (self_t&)*this;
        }

        // set 1 methods
        self_t& methods(HTTPMethod method)
        {
            ((self_t*)this)->methods_ = 1 << (int)method;
            return (self_t&)*this;
        }

        // set many methods
        template <typename ... MethodArgs>
        self_t& methods(HTTPMethod method, MethodArgs ... args_method)
        {
            methods(args_method...);
            ((self_t*)this)->methods_ |= 1 << (int)method;
            return (self_t&)*this;
        }

        // set many methods with std::initializer_list
        template <typename ... MethodArgs>
        self_t& methods(std::initializer_list<HTTPMethod> method_list)
        {
            for (auto method :method_list) {
                methods(method);
            }
            return (self_t&)*this;
        }

    };

    // dynamic (or run-time) rule - not based on meta-templates
    // the parameters are passed as a routing_params object
    class DynamicRule : public BaseRule, public RuleParameterTraits<DynamicRule> // (Traits<DynamicRule> to make the functions return DynamicRule)
    {
    public:
        // baserule constructor
        DynamicRule(std::string rule)
                : BaseRule(std::move(rule))
        {
        }

        // check if there is an erased handler
        void validate() override
        {
            if (!erased_handler_)
            {
                throw std::runtime_error(name_ + (!name_.empty() ? ": " : "") + "no handler for url " + rule_);
            }
        }

        // call the erased handler with standard params
        void handle(const request& req, response& res, const routing_params& params) override
        {
            erased_handler_(req, res, params);
        }

        // set the handler function (what to return from that rule)
        template <typename Func>
        void operator()(Func f)
        {
#ifdef WPP_MSVC_WORKAROUND
            using function_t = utility::function_traits<decltype(&Func::operator())>;
#else
            // function_traits keep arity, result_type, arg<0>, arg<1>, ...
            using function_t = utility::function_traits<Func>;
#endif
            // wrap the function in a standard form (resquest,response, params) and keep the handler on the erased_handler
            erased_handler_ = wrap(std::move(f), const_str::gen_seq<function_t::arity>());
        }

        // enable_if Arg1 == request && Arg2 == response
        // enable_if Arg1 == request && Arg2 != resposne
        // enable_if Arg1 != request
#ifdef WPP_MSVC_WORKAROUND
        template <typename Func, size_t ... Indices>
#else
        template <typename Func, unsigned ... Indices>
#endif
        std::function<void(const request&, response&, const routing_params&)>
        wrap(Func f, const_str::seq<Indices...>)
        {
#ifdef WPP_MSVC_WORKAROUND
            using function_t = utility::function_traits<decltype(&Func::operator())>;
#else
            using function_t = utility::function_traits<Func>;
#endif
            // match rule string with computed arg list
            if (!const_str::is_parameter_tag_compatible(
                    const_str::get_parameter_tag_runtime(rule_.c_str()),
                    const_str::compute_parameter_tag_from_args_list<
                            typename function_t::template arg<Indices>...>::value))
            {
                throw std::runtime_error("route_dynamic: Handler type is mismatched with URL parameters: " + rule_);
            }
            // change function arguments
            auto ret = detail::routing_handler_call_helper::Wrapped<Func, typename function_t::template arg<Indices>...>();
            ret.template set<
                    typename function_t::template arg<Indices>...
            >(std::move(f));
            return ret;
        }

        // does the same as last function but keeps a name for the route
        template <typename Func>
        void operator()(std::string name, Func&& f)
        {
            name_ = std::move(name);
            (*this).template operator()<Func>(std::forward(f));
        }
    private:
        std::function<void(const request&, response&, const routing_params&)> erased_handler_;

    };

    // "static" rule (they keep the original parameters in the function)
    template <typename ... Args>
    class TaggedRule : public BaseRule, public RuleParameterTraits<TaggedRule<Args...>>
    {
    public:
        using self_t = TaggedRule<Args...>;

        // default constructor
        TaggedRule(std::string rule)
                : BaseRule(std::move(rule))
        {
        }

        // check if it has a handler
        void validate() override
        {
            if (!handler_)
            {
                throw std::runtime_error(name_ + (!name_.empty() ? ": " : "") + "no handler for url " + rule_);
            }
        }

        // set handler function if function doesn't have the request parameter
        template <typename Func>
        typename std::enable_if<const_str::CallHelper<Func, const_str::S<Args...>>::value, void>::type
        operator()(Func&& f)
        {
            static_assert(const_str::CallHelper<Func, const_str::S<Args...>>::value ||
                          const_str::CallHelper<Func, const_str::S<wpp::request, Args...>>::value ,
                          "Handler type is mismatched with URL parameters");
            static_assert(!std::is_same<void, decltype(f(std::declval<Args>()...))>::value,
                          "Handler function cannot have void return type; valid return types: string, int, wpp::resposne, wpp::json::wvalue");

            handler_ = [f = std::move(f)](const request&, response& res, Args ... args){
                res = response(f(args...));
                res.end();
            };
        }

        // set handler function if function has the request parameter
        template <typename Func>
        typename std::enable_if<
                !const_str::CallHelper<Func, const_str::S<Args...>>::value &&
                const_str::CallHelper<Func, const_str::S<wpp::request, Args...>>::value,
                void>::type
        operator()(Func&& f)
        {
            static_assert(const_str::CallHelper<Func, const_str::S<Args...>>::value ||
                          const_str::CallHelper<Func, const_str::S<wpp::request, Args...>>::value,
                          "Handler type is mismatched with URL parameters");
            static_assert(!std::is_same<void, decltype(f(std::declval<wpp::request>(), std::declval<Args>()...))>::value,
                          "Handler function cannot have void return type; valid return types: string, int, wpp::resposne, wpp::json::wvalue");

            // add the request to the handler for conformity
            handler_ = [f = std::move(f)](const wpp::request& req, wpp::response& res, Args ... args){
                res = response(f(req, args...));
                res.end();
            };
        }

        template <typename Func>
        typename std::enable_if<
                !const_str::CallHelper<Func, const_str::S<Args...>>::value &&
                !const_str::CallHelper<Func, const_str::S<wpp::request, Args...>>::value,
                void>::type
        operator()(Func&& f)
        {
            static_assert(const_str::CallHelper<Func, const_str::S<Args...>>::value ||
                          const_str::CallHelper<Func, const_str::S<wpp::request, Args...>>::value ||
                          const_str::CallHelper<Func, const_str::S<wpp::request, wpp::response&, Args...>>::value
                    ,
                          "Handler type is mismatched with URL parameters");
            static_assert(std::is_same<void, decltype(f(std::declval<wpp::request>(), std::declval<wpp::response&>(), std::declval<Args>()...))>::value,
                          "Handler function with response argument should have void return type");

            // move the function to the object
            handler_ = std::move(f);
        }

        // if there is a name string, we keep it and use the previous function
        template <typename Func>
        void operator()(std::string name, Func&& f)
        {
            name_ = std::move(name);
            (*this).template operator()<Func>(std::forward(f));
        }

        // call the handler function
        void handle(const request& req, response& res, const routing_params& params) override
        {
            detail::routing_handler_call_helper::call<
                    detail::routing_handler_call_helper::call_params<
                            decltype(handler_)>,
                    0, 0, 0, 0,
                    const_str::S<Args...>,
                    const_str::S<>
            >()(
                    detail::routing_handler_call_helper::call_params<
                            decltype(handler_)>
                            {handler_, params, req, res}
            );
        }

    private:
        std::function<void(const wpp::request&, wpp::response&, Args...)> handler_;

    };
}

#endif //WPP_RULE_H
