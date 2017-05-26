//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_WPP_H
#define WPP_WPP_H

// STL libraries
#include <string>
#include <regex>
#include <vector>
#include <functional>
#include <utility>
#include <iostream>
#include <map>

// Boost libraries
#include <boost/optional.hpp>
using namespace std;
using boost::optional;

// Crow libraries
#include "crow.h"

namespace wpp {
    // typedefs and enums
    using json = crow::json::wvalue;
    using response = crow::response;
    using request = crow::request;
//    using view = crow::mustache;
    using namespace crow;


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

    private:

    };

}

#endif //WPP_WPP_H
