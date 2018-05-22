//
// Created by Alan de Freitas on 19/09/17.
//

#ifndef WPP_ROUTE_PROPERTIES_H
#define WPP_ROUTE_PROPERTIES_H

#include <boost/tokenizer.hpp>

#include "utils/logging.h"

#include "enums.h"
#include "response.h"
#include "request.h"

namespace wpp {

    using resource_function = std::function<void(wpp::response &, wpp::request &)>;


    struct route_properties {
        using self_t = route_properties;

        // data
        string _name;
        string _uri;
        vector<method> _methods;
        resource_function _func;
        vector<string> _middleware;

        // pre-processed data
        vector<string> _uri_members;
        vector<uri_member_type> _uri_member_regex_type;

        // pre-process parameter data
        vector<string> _uri_parameter_names;
        vector<ParamType> _uri_member_data_type;
        vector<vector<string>> _uri_member_regexes;

        bool _is_resource = true;

        route_properties(string uri, vector<method> methods, resource_function func): _uri(uri), _methods(methods), _func(func){
            typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
            boost::char_separator<char> sep{"/"};
            tokenizer tok{uri, sep};
            for (const auto &t : tok) {
                bool is_regex_parameter = false;
                // if it might be regex
                if (t.length() > 1 && t[0] == '{' && t[t.size() - 1] == '}') {
                    std::smatch sm;
                    for (auto &x:paramTraits) {
                        if (std::regex_match(t, sm, std::regex(x.keyword))) {
                            if (t[t.size() - 2] == '?') {
                                _uri_members.push_back(sm[2].str());
                                _uri_member_regex_type.push_back(uri_member_type::optional_regex);
                            } else {
                                _uri_members.push_back(sm[2].str());
                                _uri_member_regex_type.push_back(uri_member_type::regex);
                            }
                            _uri_parameter_names.push_back(sm[2].str());
                            _uri_member_data_type.push_back(x.type);
                            _uri_member_regexes.push_back(x.formulas);
                            is_regex_parameter = true;
                            break;
                        }
                    }
                }

                if (!is_regex_parameter) {
                    _uri_members.push_back(t);
                    _uri_member_regex_type.push_back(uri_member_type::simple_string);
                };
            }
            if (!uri.empty() && uri[uri.length()-1 == '/']){
                _is_resource = false;
            }
        }

        bool is_resource(){
            return _is_resource;
        }

        bool is_folder(){
            return !_is_resource;
        }

        self_t& name(string name){
            _name = name;
            return *this;
        }

        self_t& middleware(string name){
            _middleware.push_back(name);
            return *this;
        }

        self_t& middleware(initializer_list<string> l){
            _middleware.insert(_middleware.end(),l.begin(),l.end());
            return *this;
        }

        self_t& where(string param, string regular_exp){
            string tmp = "^" + param + "$";
            auto it = find(_uri_parameter_names.begin(),_uri_parameter_names.end(),param);
            if (it != _uri_parameter_names.end()){
                _uri_member_regexes[it-_uri_parameter_names.begin()].push_back(regular_exp);
            }
            return *this;
        }

        self_t& where(initializer_list<initializer_list<string>> l){
            for (auto &&item : l) {
                if (item.size() == 2){
                    auto data = item.begin();
                    data++;
                    where(*item.begin(),*data);
                } else {
                    log::error << "The initializer list in route::where did not have the proper format" << std::endl;
                }
            }
            return *this;
        }
    };
}

#endif //WPP_ROUTE_PROPERTIES_H
