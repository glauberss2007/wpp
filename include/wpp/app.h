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


// TODO: check for files before checking for rules
// if there is a file image.jpg, the file contents should be returned instead of
// trying to match a rule image.jpg

// TODO: Implement different syntaxes and regexes for the rules
// <int?>
// <[A-Za-z]+>

// TODO: Implement functions to return values from routes
// string url = route("routename");
// string url = current_route("routename");
// string url = current_route_name("routename");

// TODO: Implement different responses
// response.redirect().route("routename")
// response.redirect().route("routename", {'id',20})
// response.redirect().url('http://www.foo.com')

// TODO: Implement middleware rules besides route rules
// app.middleware("auth")
//  ([]{return (user.auth());})
//
// app.any("link").middleware("auth")
// app.any("link").middleware({"auth","can","guest")
//
// just like routes, middlewares can access the request

// TODO: Implement middleware groups
// app.middleware_group("name",{"auth","guest"})

// TODO: implement csrf() on POST, PUT, or DELETE
// <form action="/foo/bar" method="POST">
// <input type="hidden" name="_method" value="PUT">
// or {{ method_field('PUT') }}
// <input type="hidden" name="_token" value="{{ csrf_token() }}">
// </form>
//
// <meta name="csrf-token" content="{{ csrf_token() }}">
//
// generate one csrf in each user session
// there should be a verify_csrf_token middleware for all post routes
// XSRF-TOKEN

// TODO: Implement route groups
// app.group("prefix").middleware("auth")

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
//  implement mechanism to attach functions/data to views
//  implement mechanism to attach functions/data with a group of views

// TODO: Implement mustache lambdas
// so we can have the same functions as in blade templates
// std::string view{"{{#bold}}{{yay}} :){{/bold}}"};
// mstch::map context{
//         {"yay", std::string{"Yay!"}},
//         {"bold", mstch::lambda{[](const std::string& text) -> mstch::node {
//             return "<b>" + text + "</b>";
//         }}}
// };
//
// std::cout << mstch::render(view, context) << std::endl;
// https://github.com/kainjow/Mustache


// TODO: All cookies have to be encrypted

// TODO: Keep user sessions
// there are many alternatives
// file - sessions are stored in storage/framework/sessions.
// cookie - sessions are stored in secure, encrypted cookies.
// database - sessions are stored in a relational database.
// memcached / redis - sessions are stored in one of these fast, cache based stores.
// array - sessions are stored in a c++ array and will not be persisted.
//        Session data:
//                string("id")  unique();
//                unsignedInteger("user_id")    nullable();
//                string("ip_address", 45)  nullable();
//                text("user_agent")    nullable();
//                text("payload");
//                integer("last_activity");
//
// request.session("key")
// request.session().get("key")
// request.session().get("key","default")
// json data = request.session().all();
// json data = request.session().has("users");
// request.session().put("key", "value");
// request.session().flash("status", "Task was successful!");
// request.session().reflash();
// request.session().>forget("key");
// request.session().flush();
// $request.session().regenerate(); // regenerate session id

// TODO: Implement validator
// wpp::validate(request, {
//     {"title" , "required|unique:posts|max:255"},
//     {"body" , "required"},
//     {"author.name" , "required"}
// });
// validator.errors().all();
// define error messages (per error and ad hoc)
// Rules
// Active URL
// After (Date)
// After Or Equal (Date)
// Alpha
// Alpha Dash
// Alpha Numeric
// Array
// Before (Date)
// Before Or Equal (Date)
// Between
// Boolean
// Date
// Date Format
// Different
// Digits
// Digits Between
// Dimensions (Image Files)
// Distinct
// E-Mail
// Exists (Database)
// File
// Filled
// Image (File)
// In
// In Array
// Integer
// IP Address
// JSON
// Max
// Min
// Nullable
// Not In
// Numeric
// Present
// Regular Expression
// Required
// Required If
// Required Unless
// Required With
// Required With All
// Required Without
// Required Without All
// Same
// Size
// String
// Timezone
// Unique (Database)
// URL

// TODO: Implement database connection and ORM on cmake
// make script/program to read the DB and create C++ objects to access data