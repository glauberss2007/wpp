//
// Created by Alan de Freitas on 16/09/17.
//

#ifndef WPP_APPLICATION_H
#define WPP_APPLICATION_H

#include <functional>
#include <utility>
#include <map>
#include <sstream>
#include <thread>
#include <memory>
#include <unordered_set>
#include <iostream>
#include <boost/optional.hpp>

#include "request.h"
#include "response.h"
#include "route_properties.h"
#include "trie.h"

#include "utils/stl_shortcuts.h"
#include "utils/container_overloads.h"
#include "utils/container_utils.h"
#include "utils/include/simple_server/server_http.hpp"
#include "utils/logging.h"

namespace wpp {

    using boost::optional;
    using namespace std;

    using resource_function = std::function<void(wpp::response &, wpp::request &)>;

    class application {
    public:
        using self_t = application;

        // create dynamic rule
        // shortcuts to create dynamic rule
        route_properties& any(std::string rule, resource_function func) {
            return this->route({method::get, method::delete_, method::head, method::post, method::put, method::options,
                                method::connect, method::trace}, rule, func);
        }

        route_properties& get(std::string rule, resource_function func) {
            return this->route({method::get}, rule, func);
        }

        route_properties& delete_(std::string rule, resource_function func) {
            return this->route({method::delete_}, rule, func);
        }

        route_properties& head(std::string rule, resource_function func) {
            return this->route({method::head}, rule, func);
        }

        route_properties& post(std::string rule, resource_function func) {
            return this->route({method::post}, rule, func);
        }

        route_properties& put(std::string rule, resource_function func) {
            return this->route({method::put}, rule, func);
        }

        route_properties& options(std::string rule, resource_function func) {
            return this->route({method::options}, rule, func);
        }

        route_properties& connect(std::string rule, resource_function func) {
            return this->route({method::connect}, rule, func);
        }

        route_properties& trace(std::string rule, resource_function func) {
            return this->route({method::trace}, rule, func);
        }

        route_properties& redirect(std::string from, std::string to) {
            resource_function func = [this,to](wpp::response &res, wpp::request &req){
                auto to_route = this->route(to);
                to_route.second._func(res,req);
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

        route_properties& route(std::initializer_list<wpp::method> l, std::string _rule, resource_function func) {
            route_properties t (_rule,vector<method>(l.begin(),l.end()),func);
            _routes.push_back(t);
            return _routes.back();
        }

        std::pair<resource_function, routing_params> get_resource(std::string path, method m) {
            // Find path- and method-match, and call write_server_response_
            // create a regex match
            auto r = _route_trie.find(path,m);
            if (std::get<0>(r)){
                return std::make_pair(_routes[std::get<1>(r)]._func, std::move(std::get<2>(r)));
            } else {
                return std::make_pair(nullptr, std::move(std::get<2>(r)));
            }
        }

        unsigned &port() {
            return this->_port;
        }

        self_t& port(unsigned port) {
            this->_port = port;
            return *this;
        }

        string url_for(string route_name){
            auto it = _route_by_name.find(route_name);
            // todo: consider route parameters
            if (it != _route_by_name.end()){
                return _routes[it->second]._uri;
            } else {
                return "";
            }
        }

        pair<bool,route_properties> route(string route_name){
            auto it = _route_by_name.find(route_name);
            if (it != _route_by_name.end()){
                return make_pair(true,_routes[it->second]);
            } else {
                return make_pair(false,_routes[0]);
            }
        }

        self_t& redirect(string route_name, wpp::response &res, wpp::request &req){
            // todo: consider route parameters
            pair<bool,route_properties> r = this->route(route_name);
            if (r.first){
                r.second._func(res,req);
            }
            return *this;
        }

        self_t& start() {
            log::info << "http://localhost:" << this->_port << "/" << std::endl;
            log::debug << "ROUTES" << std::endl;
            utils::sort(_routes, [](route_properties& a,route_properties& b){return a._uri < b._uri;});
            // optimize data
            for (int i = 0; i < _routes.size(); ++i) {
                log::debug << _routes[i]._uri << std::endl;
                // include name in app set for faster lookup
                if (_routes[i]._name != ""){
                    _route_by_name[_routes[i]._name] = i;
                }
                // create trie
                _route_trie.add(_routes[i], i);
            }
            // disp settings
            log::debug << "ROUTES TRIE: " << std::endl;
            _route_trie.debug_print();
            // settings
            using namespace std;
            using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
            HttpServer server;
            server.config.port = this->_port;
            if (this->_multithreaded){
                server.config.thread_pool_size = std::thread::hardware_concurrency();
            }
            application& this_application = *this;
            // all routes
            for (int i = 0; i < number_of_methods(); ++i) {
                server.default_resource[method_string((method)i)] = [&this_application](std::shared_ptr<HttpServer::Response> response,
                                                    std::shared_ptr<HttpServer::Request> request) {
                    // convert request
                    wpp::request req;
                    req.body = request->content.string();
                    req.headers = ci_map(request->header.begin(),request->header.end());
                    req.method_requested = wpp::method_enum(request->method);
                    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
                    boost::char_separator<char> sep{"&",";"};
                    tokenizer tok{request->query_string, sep};
                    // for each token
                    for (const auto &t : tok) {
                        std::smatch sm;
                        if (std::regex_match(t,sm,std::regex("^([^\\=\\&;]+)(\\=([^\\&;]+))?$"))){
                            if (sm.size() == 2){
                                req.url_params.insert(pair<string,string>(sm[1],""));
                            } else {
                                req.url_params.insert(pair<string,string>(sm[1],sm[3]));
                            }
                        }
                    }
                    req.method_string = request->method;
                    req.raw_url = request->path;
                    req.url = request->path;
                    req.path = request->path;
                    req.http_version = request->http_version;
                    req.remote_endpoint_address = request->remote_endpoint_address;
                    req.remote_endpoint_port = request->remote_endpoint_port;
                    // ask wpp what to do
                    std::tuple<bool, unsigned, routing_params> wpp_reply = this_application._route_trie.find(req.url,req.method_requested);
                    req.query_parameters = std::get<2>(wpp_reply);
                    // convert response from wpp back to driver
                    if (std::get<0>(wpp_reply)){
                        req.current_route = &this_application._routes[std::get<1>(wpp_reply)];
                        wpp::response res;
                        this_application._routes[std::get<1>(wpp_reply)]._func(res,req);
                        SimpleWeb::CaseInsensitiveMultimap server_headers(res.headers.begin(),res.headers.end());
                        response->write((SimpleWeb::StatusCode)((int)res.code), res.body, server_headers);
                    } else {
                        // try to find file resource
                        try {
                            auto web_root_path = boost::filesystem::canonical("web");
                            auto path = boost::filesystem::canonical(web_root_path / request->path);
                            // Check if path is within web_root_path
                            if (distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
                                !equal(web_root_path.begin(), web_root_path.end(), path.begin())) {
                                throw invalid_argument("path must be within root path");
                            }
                            if (boost::filesystem::is_directory(path)) {
                                path /= "index.html";
                            }

                            SimpleWeb::CaseInsensitiveMultimap header;

                            //    Uncomment the following line to enable Cache-Control
                            //    header.emplace("Cache-Control", "max-age=86400");

                            #ifdef HAVE_OPENSSL
                            //    Uncomment the following lines to enable ETag
            //    {
            //      ifstream ifs(path.string(), ifstream::in | ios::binary);
            //      if(ifs) {
            //        auto hash = SimpleWeb::Crypto::to_hex_string(SimpleWeb::Crypto::md5(ifs));
            //        header.emplace("ETag", "\"" + hash + "\"");
            //        auto it = request->header.find("If-None-Match");
            //        if(it != request->header.end()) {
            //          if(!it->second.empty() && it->second.compare(1, hash.size(), hash) == 0) {
            //            response->write(SimpleWeb::StatusCode::redirection_not_modified, header);
            //            return;
            //          }
            //        }
            //      }
            //      else
            //        throw invalid_argument("could not read file");
            //    }
                            #endif

                            auto ifs = make_shared<ifstream>();
                            ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

                            if (*ifs) {
                                auto length = ifs->tellg();
                                ifs->seekg(0, ios::beg);

                                header.emplace("Content-Length", to_string(length));
                                response->write(header);

                                // Trick to define a recursive function within this scope (for example purposes)
                                class FileServer {
                                    public:
                                        static void read_and_send(const std::shared_ptr<HttpServer::Response> &response,
                                                                  const std::shared_ptr<ifstream> &ifs) {
                                            // Read and send 128 KB at a time
                                            static vector<char> buffer(131072); // Safe when server is running on one thread
                                            streamsize read_length;
                                            if ((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) >
                                                0) {
                                                response->write(&buffer[0], read_length);
                                                if (read_length == static_cast<streamsize>(buffer.size())) {
                                                    response->send([response, ifs](const SimpleWeb::error_code &ec) {
                                                        if (!ec) {
                                                            read_and_send(response, ifs);
                                                        } else {
                                                            cerr << "Connection interrupted" << endl;
                                                        }
                                                    });
                                                }
                                            }
                                        }
                                };
                                FileServer::read_and_send(response, ifs);
                            } else {
                                throw invalid_argument("could not read file");
                            }
                        }
                        catch (const std::exception &e) {
                            response->write(SimpleWeb::StatusCode::client_error_bad_request,
                                            "Could not open path " + request->path + ": " + e.what());
                        }
                    }
                };
            }
            // routes
            server.on_error = [](std::shared_ptr<HttpServer::Request> req, const SimpleWeb::error_code & ec) {
                log::debug << ec.message() << std::endl;
            };
            server.start();
            return *this;
        }


        private:
        // routes
        std::vector<route_properties> _routes;
        std::unordered_map<string,unsigned> _route_by_name;
        Trie _route_trie;

        // defaults
        std::array<optional<resource_function>, number_of_methods()> default_resource_;
        std::function<void(wpp::request, const boost::system::error_code &)> on_error_;
        // settings
        unsigned _port = 8080;
        unsigned _multithreaded = true;

    };


    /*
     * DEFINE REGEXES
     *
     * Positive Integers  ^\d+$
Negative Integers  ^-\d+$
Integer ^-?\d+$
Positive Number ^\d*\.?\d+$
Negative Number  ^-\d*\.?\d+$
Positive Number or Negative Number  ^-?\d*\.?\d+$
Phone number ^\+?[\d\s]{3,}$
Phone with code  ^\+?[\d\s]+\(?[\d\s]{10,}$
Year 1900-2099  ^(19|20)\d{2}$
Date (dd mm yyyy, d/m/yyyy, etc.)
^([1-9]|0[1-9]|[12][0-9]|3[01])\D([1-9]|0[1-9]|1[012])\D(19[0-9][0-9]|20[0-9][0-9])$
IP v4:

    ^(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d\d|2[0-4]\d|25[0-5]){3}$
Alphabetic input

Personal Name ^[\w.']{2,}(\s[\w.']{2,})+$
Username  ^[\w\d_.]{4,}$
Password at least 6 symbols  ^.{6,}$
Password or empty input  ^.{6,}$|^$
email ^[_]*([a-z0-9]+(\.|_*)?)+@([a-z][a-z0-9-]+(\.|-*\.))+[a-z]{2,6}$
domain ^([a-z][a-z0-9-]+(\.|-*\.))+[a-z]{2,6}$

             * int \d+ [0-9]+
        * float [0-9]+\.?[0-9]+
        * word [a-zA-Z_0-9]
        * string [^/]+
        * path .+
        * /^\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/ (Email Id)
        * /^([\w-\.]+@(?!gmail.com)(?!yahoo.com)(?!hotmail.com)([\w- ]+\.)+[\w-]{2,4})?$/ (free/domain specific email id)
        * /(http(s)?://)?([\w-]+\.)+[\w-]+[.com]+(/[/?%&=]*)?/ (with or without http)
        * /((www\.|(http|https|ftp|news|file)+\:\/\/)[_.a-z0-9-]+\.[a-z0-9\/_:@=.+?,##%&~-]*[^.|\'|\# |!|\(|?|,| |>|<|;|\)])/( valid everywhere)
        * / ^[a-z0-9\.@#\$%&]+$/ (only contains letter [a-z] digits[0-9], special characters(@#$%&))
        * / ^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$/ (Minimum 8 characters at least 1 Alphabet and 1 Number)
        * / ^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&])[A-Za-z\d$@$!%*?&]{8,}/ (Minimum 8 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet, 1 Number and 1 Special Character)
        * / ^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[$@$!%*?&])[A-Za-z\d$@$!%*?&]{8,10}/ (Minimum 8 and Maximum 10 characters at least 1 Uppercase Alphabet, 1 Lowercase Alphabet, 1 Number and 1 Special Character)
        * / ^[a-zA-Z0-9\s]{7,16}$/ (Minimum length 7 and Maximum length 16 Characters allowed [a–z] [A-Z] [0-9])
        * / ^((\+){0,1}91(\s){0,1}(\-){0,1}(\s){0,1}){0,1}9[0-9](\s){0,1}(\-){0,1}(\s){0,1}[1-9]{1}[0-9]{7}$/ (without +91 or 0)
        * /^((\\+91-?)|0)?[0-9]{10}$/ (with or without +91 or 0)
        * ^((\\+|00)(\\d{1,3})[\\s-]?)?(\\d{10})$/ (split the number and the country code)
        * /(?s)^((?!manish).)*$/ (string contains manish)
        * \d/ (at list one digit )
        * /(.)*(\\d)(.)* / (contains number)
        * /^\d$/ (contains only number )
        * /^\d{11}$/ (contains only 11 digit number )
        * /^[a-zA-Z]+$/ (contains only letter )
        * /^[a-zA-Z0-9]+$/ (contains only letter and number )
        * /^[a-z0-9_-]{3,16}$/ (username)
        * /^[a-z0-9-]+$/ (slug)
        * /^([a-z0-9_\.-]+)@([\da-z\.-]+)\.([a-z\.]{2,6})$/ (email)
        * /^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$/ (url)
        * /^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/ (IP address)
        * /^<([a-z]+)([^<]+)*(?:>(.*)<\/\1>|\s+\/>)$/
     *
     *
     */
}

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

#endif //WPP_APPLICATION_H
