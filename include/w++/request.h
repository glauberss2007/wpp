//
// Created by Alan de Freitas on 16/09/17.
//

#ifndef WPP_REQUEST_H
#define WPP_REQUEST_H

#include <unordered_map>
#include <regex>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/case_conv.hpp>


#include "utility.hpp"
#include "methods.h"
#include "environment.h"
#include "query_string.h"
#include "routing_parameters.h"
#include "encryption.h"
#include "UaParser.h"
#include "application.h"


namespace wpp {
    struct route_properties;
    class application;
    class response;
    class guard;

    using reque = boost::beast::http::request<boost::beast::http::string_body>;
    using respo = boost::beast::http::response<boost::beast::http::string_body>;

    struct request {
        friend class application;
        using byte = unsigned char;
        using user_agent = UserAgent;

        // raw data
        method method_requested; // default: GET
        std::string url_; // processed url (request receives it already processed, it just copies everything)
        std::string query_string; // whole query string (with request_parameters)
        std::string body; // body of the request
        std::string http_version; // body of the request
        std::string remote_endpoint_address;
        unsigned short remote_endpoint_port;
        // processed data
        wpp::CaseInsensitiveMultimap request_parameters; // parsed query string
        std::unordered_multimap<std::string, std::string> headers; // unordered map of headers
        std::string method_string; // body of the request
        routing_params query_parameters;
        route_properties* current_route{nullptr};
        user_agent user_agent_;
        std::unordered_map<std::string, std::string> cookie_jar;

        application *parent_application{nullptr};
        wpp::guard *auth{nullptr};
        json session_data;
        json view_bag;

        request() : method_requested(method::get) {}

        request(method method__,
                std::string raw_url__,
                std::string url__,
                wpp::CaseInsensitiveMultimap request_parameters__,
                std::unordered_multimap<std::string, std::string> headers__,
                std::string body__)
                : method_requested(method__), url_(std::move(url__)),
                  request_parameters(std::move(request_parameters__)), headers(std::move(headers__)), body(std::move(body__)) {
        }

        request &add_header(std::string key__, std::string value__) {
            headers.emplace(std::move(key__), std::move(value__));
            return *this;
        }

        std::string get_header_value(const std::string &key, std::string default_ = "") const {
            if (headers.count(key))
            {
                return headers.find(key)->second;
            }
            return default_;
        }

        std::string header(const std::string &key, std::string default_ = "") const {
            return get_header_value(key,default_);
        }

        void parse_cookies();

        ///////////////////////////////////////////////////////////////
        //                    COOKIES                                //
        ///////////////////////////////////////////////////////////////

        std::string get_cookie(const std::string& key)
        {
            if (cookie_jar.count(key)){
                return cookie_jar[key];
            }
            return {};
        }

        ///////////////////////////////////////////////////////////////
        //                    REQUEST DATA                           //
        ///////////////////////////////////////////////////////////////

        // url path
        std::string path() {
            if (!url_.empty() && url_.front() == '/'){
                url_ = std::string(url_.begin()+1,url_.end());
            }
            return url_;
        }

        // full URL without query string
        std::string url() const;

        // includes query string
        std::string full_url() const;

        bool is(std::string expression) const {
            replace_all(expression,"*",".*");
            expression = "^" + expression + "$";
            return (std::regex_match(url_,std::regex(expression)));
        }

        string route_name();

        bool is_method(wpp::method r) const {
            return this->method_requested == r;
        }

        bool is_method(std::string str) const {
            boost::algorithm::to_upper(str);
            return this->method_string == str;
        }

        bool is_ajax() const {
            return this->get_header_value("X-Requested-With") == "XMLHttpRequest";
        }

        json all(){
            return json(request_parameters);
        }

        json only(std::initializer_list<wpp::string> l){
            json j;
            for (const std::string &key : l) {
                wpp::CaseInsensitiveMultimap::iterator iter = request_parameters.find(key);
                if (iter != request_parameters.end()){
                    j[key] = iter->second;
                }
            }
            return j;
        }

        json except(std::initializer_list<wpp::string> l){
            json j;
            for (CaseInsensitiveMultimap::iterator iter = request_parameters.begin();
                 iter != request_parameters.end(); ++iter) {
                const bool key_not_found = find(l.begin(),l.end(),iter->first) == l.end();
                if (key_not_found){
                    j[iter->first] = iter->second;
                }
            }
            return j;
        }

        json input(const std::string &key, json default_ = ""){
            // todo: implement access with dot notation: $request->input('products.0.name'); or $request->input('products.*.name');
            wpp::CaseInsensitiveMultimap::iterator iter = request_parameters.find(key);
            if (iter != request_parameters.end()){
                return iter->second;
            }
            return default_;
        }

        json has(const std::string &key){
            // todo: implement access with dot notation: $request->input('products.0.name'); or $request->input('products.*.name');
            return request_parameters.find(key) != request_parameters.end();
        }

        // TODO:

        user_agent user_agent_object() const {
            const UserAgentParser g_ua_parser(string(environment::user_agent_parser_root_path) + "/regexes.yaml");
            UserAgent ua = g_ua_parser.parse(user_agent_header());
            return ua;
        }

        bool is_mobile() const {
            std::string user_agent_full_header = user_agent_header();
            std::size_t found = user_agent_full_header.find("Mobi");
            if (found!=std::string::npos){
                return true;
            }
            return false;
        }

        ///////////////////////////////////////////////////////////////
        //                    GET FAMOUS HEADERS                     //
        ///////////////////////////////////////////////////////////////
        std::string user_agent_header() const {
            return get_header_value("User-Agent");
        }


        std::string accept_encoding_header() const {
            return get_header_value("Accept-Encoding");
        }

        std::string upgrade_insecure_requests_header() const {
            return get_header_value("Upgrade-Insecure-Requests");
        }

        std::string accept_header() const {
            return get_header_value("Accept");
        }

        std::string connection_header() const {
            return get_header_value("Connection");
        }

        std::string cookie_header() const {
            return get_header_value("Cookie");
        }

        std::string host_header() const {
            return get_header_value("Host");
        }

        std::string accept_language_header() const {
            return get_header_value("Accept-Language");
        }



        ///////////////////////////////////////////////////////////////
        //                    SESSION MANAGEMENT                     //
        ///////////////////////////////////////////////////////////////
        // Non-modifying methods
        json session_get(const std::string &key, json default_ = "") const {
            auto iter = session_data.find(key);
            if (iter != session_data.end()){
                return *iter;
            }

            iter = session_data.find("flashed_data_from_this_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != iter->end()) {
                    return *iter2;
                }
            }

            iter = session_data.find("flashed_data_from_last_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != iter->end()) {
                    return *iter2;
                }
            }

            return default_;
        }

        bool session_has(const std::string &key) const {
            auto iter = session_data.find(key);
            if (iter != session_data.end()){
                if (!iter->is_null()){
                    return true;
                }
            }

            iter = session_data.find("flashed_data_from_this_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != iter->end()) {
                    if (!iter2->is_null()) {
                        return true;
                    }
                }
            }

            iter = session_data.find("flashed_data_from_last_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != session_data.end()) {
                    if (!iter2->is_null()) {
                        return true;
                    }
                }
            }

            return false;
        }

        bool session_exists(const std::string &key) const {
            auto iter = session_data.find(key);
            if (iter != session_data.end()) {
                return true;
            }

            iter = session_data.find("flashed_data_from_this_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != iter->end()) {
                    return true;
                }
            }

            iter = session_data.find("flashed_data_from_last_request");
            if (iter != session_data.end()) {
                auto iter2 = iter->find(key);
                if (iter2 != iter->end()) {
                    return true;
                }
            }

            return false;
        }

        json session_all() const {
            return session_data;
        }

        // Modifying methods for insertion
        request& session_put(const std::string &key, const json& value) {
            if (key!="id"){
                session_data[key] = value;
            }
            return *this;
        }

        request& session_regenerate(response& res);

        request& session_flash(const std::string &key, const json& value) {
            json::iterator iter = session_data.find("flashed_data_from_this_request");
            if (iter == session_data.end()){
                session_data["flashed_data_from_this_request"] = json::object();
            }
            session_data["flashed_data_from_this_request"][key] = value;
            return *this;
        }

        json session_get_flashed(){
            json::iterator iter = session_data.find("flashed_data_from_last_request");
            if (iter != session_data.end() && iter->is_object()){
                return *iter;
            }
            return json::object();
        }

        request& session_reflash() {
            json::iterator iter = session_data.find("flashed_data_from_last_request");
            if (iter != session_data.end() && iter->is_object()){
                json::iterator iter_this_request = session_data.find("flashed_data_from_this_request");
                if (iter_this_request == session_data.end() && iter_this_request->is_object()){
                    session_data["flashed_data_from_this_request"] = json::object();
                }
                for (auto iterobj = iter->begin();
                     iterobj != iter->end(); ++iterobj) {
                    (*iter)[iterobj.key()] = iterobj.value();
                }
            }
            return *this;
        }

        request& session_keep(json list) {
            if (list.is_string()){
                list = json::array({list.get<string>()});
            }
            if (list.is_array()){
                json::iterator iter = session_data.find("flashed_data_from_last_request");
                if (iter != session_data.end() && iter->is_object()){
                    json::iterator iter_this_request = session_data.find("flashed_data_from_this_request");
                    if (iter_this_request == session_data.end() && iter_this_request->is_object()){
                        session_data["flashed_data_from_this_request"] = json::object();
                    }
                    for (auto iter_keep = list.begin();
                         iter_keep != list.end(); ++iter_keep) {
                        if (iter_keep->is_string()){
                            if (session_data["flashed_data_from_last_request"].find(*iter_keep) != session_data["flashed_data_from_last_request"].end()){
                                const string field_name = *iter_keep;
                                (*iter)[field_name] = session_data["flashed_data_from_last_request"][field_name];
                            }
                        }
                    }
                }
            }
            return *this;
        }

        request& session_push(const std::string &key, const json& value) {
            json::iterator iter = session_data.find(key);
            if (iter != session_data.end()){
                if (!iter->is_array()){
                    *iter = json::array();
                }
            } else {
                session_data[key] = json::array();
                iter = session_data.find(key);
            }
            iter->push_back(value);
            return *this;
        }

        // Modifying methods for removal
        request& session_erase(const std::string &key){
            session_data.erase(key);
            return *this;
        }

        request& session_forget(const std::string &key){
            return this->session_erase(key);
        }

        json session_pull(const std::string &key, json default_ = ""){
            json result;
            auto iter = session_data.find(key);
            if (iter != session_data.end()){
                result = std::move(*iter);
                session_data.erase(key);
            } else {
                result = default_;
            }
            return result;
        }

        // TODO: $request->flash(); // flash the current input to the session so that it is available during the user's next request to the application
        // TODO: $request->flashOnly(['username', 'email']);
        // TODO: $request->flashExcept('password');
        // TODO: $request->old('username');
        // TODO: $request->file('photo');
        // TODO: ($request->hasFile('photo'))
        // TODO: $request->file('photo')->isValid() // verify that there were no problems uploading the file via the isValid method
        // TODO: $request->file('photo')->path(); $request->file('photo')->extension();
        // TODO: $path = $request->photo->store('images');
        // TODO: $path = $request->photo->storeAs('images', 'filename.jpg');
    };

}



#endif //WPP_REQUEST_H
