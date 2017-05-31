//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_WPP_H
#define WPP_WPP_H

// STL libraries
#include <string>
#include <iostream>
#include <initializer_list>

// Rapidjson libraries
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

// Boost libraries
#include <boost/optional.hpp>
using namespace std;
using boost::optional;

// Crow libraries
#include "crow.h"

namespace wpp {
    // typedefs and enums
    // TODO : Change wpp::json = crow::json for rapidjson
    using json = rapidjson::Document;
    using response = crow::response;
    using request = crow::request;

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

    enum method {get,delete_,destroy,head,post,put,options,connect,trace};

    // app object
    class wpp_app : public crow::SimpleApp {
    public:

        crow::DynamicRule& any(std::string&& rule){
            return this->route_dynamic(std::move(rule));
        }

        crow::DynamicRule& get(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("GET"_method);
        }

        crow::DynamicRule& delete_(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("DELETE"_method);
        }

        crow::DynamicRule& destroy(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("DELETE"_method);
        }

        crow::DynamicRule& head(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("HEAD"_method);
        }

        crow::DynamicRule& post(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("POST"_method);
        }

        crow::DynamicRule& put(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("PUT"_method);
        }

        crow::DynamicRule& options(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("OPTIONS"_method);
        }

        crow::DynamicRule& connect(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("CONNECT"_method);
        }

        crow::DynamicRule& trace(std::string&& rule){
            return this->route_dynamic(std::move(rule)).methods("TRACE"_method);
        }

        crow::DynamicRule& route(std::initializer_list<wpp::method> l, std::string&& _rule){
            crow::DynamicRule* r = &(this->route_dynamic(std::move(_rule)));
            vector<decltype("TRACE"_method)> cm;// = "GET"_method;
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


    private:
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








    };

}

#endif //WPP_WPP_H
