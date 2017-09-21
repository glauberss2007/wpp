#pragma once

#include <chrono>
#include <string>
#include <functional>
#include <memory>
#include <future>
#include <cstdint>
#include <type_traits>
#include <thread>

#include "settings.h"
#include "logging.h"
#include "const_str.h"
#include "routing.h"
#include "middleware_context.h"
#include "http_request.h"
#include "http_server.h"

#ifdef WPP_MSVC_WORKAROUND
#define WPP_ROUTE(app, url) app.route_dynamic(url)
#else
#define WPP_ROUTE(app, url) app.route<wpp::const_str::get_parameter_tag(url)>(url)
#endif

namespace wpp
{
    enum method {get,delete_,destroy,head,post,put,options,connect,trace};

    // a variable in the namespace keeps the SSL context
#ifdef WPP_ENABLE_SSL
    using ssl_context_t = boost::asio::ssl::context;
#endif

    // class to represent a generic application
    template <typename ... Middlewares>
    class WPP
    {
    public:
        // class to represent the class itself (useful for subclasses)
        using self_t = WPP;
        // class/shortcut to represent the server of the class
        using server_t = Server<WPP, SocketAdaptor, Middlewares...>;
        // class/shortcut to represent the ssl_server
#ifdef WPP_ENABLE_SSL
        using ssl_server_t = Server<WPP, SSLAdaptor, Middlewares...>;
#endif

        // the constructor does nothing special
        WPP()
        {
        }

        // handle upgrade handle for a request
		template <typename Adaptor> 
        void handle_upgrade(const request& req, response& res, Adaptor&& adaptor)
        {
            router_.handle_upgrade(req, res, adaptor);
        }

        // handle usual request
        void handle(const request& req, response& res)
        {
            // include rule in the router
            router_.handle(req, res);
        }

        // create dynamic rule
        DynamicRule& route_dynamic(std::string&& rule)
        {
            return router_.new_rule_dynamic(std::move(rule));
        }

        // shortcuts to create dynamic rule
        DynamicRule& any(std::string&& rule){
            return this->route_dynamic(std::move(rule));
        }

        DynamicRule& get(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("GET"_method);
        }

        DynamicRule& delete_(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("DELETE"_method);
        }

        DynamicRule& destroy(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("DELETE"_method);
        }

        DynamicRule& head(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("HEAD"_method);
        }

        DynamicRule& post(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("POST"_method);
        }

        DynamicRule& put(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("PUT"_method);
        }

        DynamicRule& options(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("OPTIONS"_method);
        }

        DynamicRule& connect(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("CONNECT"_method);
        }

        DynamicRule& trace(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("TRACE"_method);
        }

        // create dynamic rule for the specified methods
        DynamicRule& route(std::initializer_list<wpp::method> l, std::string&& _rule){
            DynamicRule* r = &(this->route_dynamic(std::move(_rule)));
            std::vector<decltype("TRACE"_method)> cm;// = "GET"_method;
            for (auto m : l) {
                switch (m){
                    case method::get:
                        r->methods("GET"_method);
                        break;
                    case method::delete_:
                        r->methods("DELETE"_method);
                        break;
                    case method::destroy:
                        r->methods("DELETE"_method);
                        break;
                    case method::head:
                        r->methods("HEAD"_method);
                        break;
                    case method::post:
                        r->methods("POST"_method);
                        break;
                    case method::put:
                        r->methods("PUT"_method);
                        break;
                    case method::options:
                        r->methods("OPTIONS"_method);
                        break;
                    case method::connect:
                        r->methods("CONNECT"_method);
                        break;
                    case method::trace:
                        r->methods("TRACE"_method);
                        break;
                }
            }
            return *r;
        }

        // create static/tagged rule - we need to type the rule twice we calling: app.route<wpp::const_str::get_parameter_tag(url)>(url)
        template <uint64_t Tag> // the tag is a const_str representing the url
        auto route(std::string&& rule) // the string represents the rule again
            -> typename std::result_of<decltype(&Router::new_rule_tagged<Tag>)(Router, std::string&&)>::type // the return type is the same type of new_rule_tagged
        {
            // include the rule in the router
            return router_.new_rule_tagged<Tag>(std::move(rule));
        }

        // define server port
        self_t& port(std::uint16_t port)
        {
            port_ = port;
            return *this;
        }

        // define bindaddr
        self_t& bindaddr(std::string bindaddr)
        {
            bindaddr_ = bindaddr;
            return *this;
        }

        // enable concurrency to number of threads
        self_t& multithreaded()
        {
            return concurrency(std::thread::hardware_concurrency());
        }

        // define number of threads
        self_t& concurrency(std::uint16_t concurrency)
        {
            if (concurrency < 1)
                concurrency = 1;
            concurrency_ = concurrency;
            return *this;
        }

        // validate route rules (check if all have functions) and optimize the router trie
        void validate()
        {
            router_.validate();
        }

        // run the application
        void run()
        {
            // validate the rules
            validate();
#ifdef WPP_ENABLE_SSL
            if (use_ssl_)
            {
                // create server (with ssl context) according to application rules
                ssl_server_ = std::move(std::unique_ptr<ssl_server_t>(new ssl_server_t(this, bindaddr_, port_, &middlewares_, concurrency_, &ssl_context_)));
                // set tick
                ssl_server_->set_tick_function(tick_interval_, tick_function_);
                // run server
                ssl_server_->run();
            }
            else
#endif
            {
                // create server (without context) according to application rules
                server_ = std::move(std::unique_ptr<server_t>(new server_t(this, bindaddr_, port_, &middlewares_, concurrency_, nullptr)));
                // set tick
                server_->set_tick_function(tick_interval_, tick_function_);
                // run server
                server_->run();
            }
        }

        // stop the application (by stopping the servers)
        void stop()
        {
#ifdef WPP_ENABLE_SSL
            if (use_ssl_)
            {
                ssl_server_->stop();
            }
            else
#endif
            {
                server_->stop();
            }
        }

        void debug_print()
        {
            log_debug << "Routing:" << std::endl;
            router_.debug_print();
        }

#ifdef WPP_ENABLE_SSL
        // pass ssl .crt file to the application
        self_t& ssl_file(const std::string& crt_filename, const std::string& key_filename)
        {
            use_ssl_ = true;
            ssl_context_.set_verify_mode(boost::asio::ssl::verify_peer);
            ssl_context_.use_certificate_file(crt_filename, ssl_context_t::pem);
            ssl_context_.use_private_key_file(key_filename, ssl_context_t::pem);
            ssl_context_.set_options(
                    boost::asio::ssl::context::default_workarounds
                          | boost::asio::ssl::context::no_sslv2
                          | boost::asio::ssl::context::no_sslv3
                    );
            return *this;
        }

        //  pass ssl .pem file to the application
        self_t& ssl_file(const std::string& pem_filename)
        {
            use_ssl_ = true;
            ssl_context_.set_verify_mode(boost::asio::ssl::verify_peer);
            ssl_context_.load_verify_file(pem_filename);
            ssl_context_.set_options(
                    boost::asio::ssl::context::default_workarounds
                          | boost::asio::ssl::context::no_sslv2
                          | boost::asio::ssl::context::no_sslv3
                    );
            return *this;
        }

        // pass context to ssl
        self_t& ssl(boost::asio::ssl::context&& ctx)
        {
            use_ssl_ = true;
            ssl_context_ = std::move(ctx);
            return *this;
        }

        // by default, we don't use ssl
        bool use_ssl_{false};
        ssl_context_t ssl_context_{boost::asio::ssl::context::sslv23};

#else
        // check ssl_file
        template <typename T, typename ... Remain>
        self_t& ssl_file(T&&, Remain&&...)
        {
            // We can't call .ssl() member function unless WPP_ENABLE_SSL is defined.
            static_assert(
                    // make static_assert dependent to T; always false
                    std::is_base_of<T, void>::value,
                    "Define WPP_ENABLE_SSL to enable ssl support.");
            return *this;
        }

        // check ssl
        template <typename T>
        self_t& ssl(T&&)
        {
            // We can't call .ssl() member function unless WPP_ENABLE_SSL is defined.
            static_assert(
                    // make static_assert dependent to T; always false
                    std::is_base_of<T, void>::value,
                    "Define WPP_ENABLE_SSL to enable ssl support.");
            return *this;
        }
#endif

        // context of middlewares for the application
        using context_t = detail::context<Middlewares...>;

        // return context
        template <typename T>
        typename T::context& get_context(const request& req)
        {
            static_assert(const_str::contains<T, Middlewares...>::value, "App doesn't have the specified middleware type.");
            auto& ctx = *reinterpret_cast<context_t*>(req.middleware_context);
            return ctx.template get<T>();
        }

        // get a middleware by type
        template <typename T>
        T& get_middleware()
        {
            return utility::get_element_by_type<T, Middlewares...>(middlewares_);
        }

        // set tick to d milliseconds and function f
        template <typename Duration, typename Func>
        self_t& tick(Duration d, Func f) {
            tick_interval_ = std::chrono::duration_cast<std::chrono::milliseconds>(d);
            tick_function_ = f;
            return *this;
        }

    private:
        uint16_t port_ = 80;
        uint16_t concurrency_ = 1;
        std::string bindaddr_ = "0.0.0.0";
        Router router_;

        std::chrono::milliseconds tick_interval_;
        std::function<void()> tick_function_;

        std::tuple<Middlewares...> middlewares_;

#ifdef WPP_ENABLE_SSL
        std::unique_ptr<ssl_server_t> ssl_server_;
#endif
        std::unique_ptr<server_t> server_;
    };

    template <typename ... Middlewares>
    using middleware_application = WPP<Middlewares...>;

    using application = WPP<>;
}


