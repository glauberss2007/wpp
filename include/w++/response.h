//
// Created by Alan de Freitas on 15/09/17.
//

#ifndef WPP_RESPONSE_H
#define WPP_RESPONSE_H

#include <string>
#include <unordered_map>
#include <initializer_list>
#include "utils/json.hpp"
#include "request.h"
#include "enums.h"

namespace wpp {
    using json = nlohmann::json;
    using ci_map = std::unordered_multimap<std::string, std::string>;

    struct response
    {
            // these variables are public for easy access
            // response's status code (200 = OK)
            enum status_code code{wpp::status_code::success_ok};
            // body of the response
            std::string body;
            // json value to be returned (if that's the case)
            json json_value;
            // 'headers' is a hash<string,string> that stores HTTP headers.
            ci_map headers{{"Content-Type","text/html"}};

            // set header in ci_map
            response& set_header(std::string key, std::string value)
            {
                headers.erase(key);
                headers.emplace(std::move(key), std::move(value));
                return *this;
            }
            response& header(std::string key, std::string value)
            {
                return this->set_header(key,value);
            }

            // set many headers at once
            response& with_headers(std::initializer_list<std::pair<std::string,std::string>> key_value_pairs)
            {
                for (auto pPair = key_value_pairs.begin(); pPair != key_value_pairs.end(); ++pPair) {
                    this->set_header(pPair->first,pPair->second);
                }
                return *this;
            }

            // add header to ci_map
            response& add_header(std::string key, std::string value)
            {
                headers.emplace(std::move(key), std::move(value));
                return *this;
            }

            std::string get_header_value(const std::string &key, std::string default_ = "") const {
                if (headers.count(key))
                {
                    return headers.find(key)->second;
                }
                return default_;
            }

            // TODO: cookie(name, value, minutes, path, domain, secure, httpOnly)
            // all cookies should be encrypted and signed so that they can't be modified or read by the client
            // create an exception for encrypting some cookies
            // TODO: redirect(address);
            // TODO: back() (it needs to use the session)
            // TODO: route(string routename) and route(string routename, json params) and route(string routename, ORMobject params)
            // TODO: redirect('dashboard')->with('status', 'Profile updated!'); // Redirecting With Flashed Session Data
            // TODO: response.view("hello", json data, 200); View responses
            // TODO: response()->download($pathToFile, $name, $headers); forces the user's browser to download the file
            // TODO: response()->file($pathToFile, $headers); used to display a file, such as an image or PDF, directly in the user's browser

            // constructors
            response() {}
            explicit response(int code) {}
            explicit response(enum status_code code) {}
            response(std::string body) : body(std::move(body)) {}
            response(json&& json_value) : json_value(std::move(json_value))
            {
                json_mode();
            }
            response(int code, std::string body) : code((status_code)code), body(std::move(body)) {}
            response(status_code code_, std::string body) : code(code_), body(std::move(body)) {}
            response(const json& json_value) : body(json_value.dump())
            {
                json_mode();
            }
            response(int code_, const wpp::json& json_value) : code((status_code)code_), body(json_value.dump())
            {
                json_mode();
            }
            response(status_code code_, const wpp::json& json_value) : code(code_), body(json_value.dump())
            {
                json_mode();
            }
            response(response&& r)
            {
                *this = std::move(r);
            }

            response& operator = (const response& r) = delete;
            response& operator = (response&& r) noexcept
            {
                body = std::move(r.body);
                json_value = std::move(r.json_value);
                code = r.code;
                headers = std::move(r.headers);
                completed_ = r.completed_;
                return *this;
            }

            // return if it's completed
            bool is_completed() const noexcept
            {
                return completed_;
            }

            // clear
            response& clear()
            {
                body.clear();
                json_value.clear();
                code = status_code::success_ok;
                headers.clear();
                completed_ = false;
                return *this;
            }

            // append to the body
            response& write(const std::string& body_part)
            {
                body += body_part;
                return *this;
            }

            // finish it
            response& end()
            {
                if (!completed_)
                {
                    completed_ = true;

                    if (complete_request_handler_)
                    {
                        complete_request_handler_();
                    }
                }
                return *this;
            }

            // finish it after appending another body part
            response& end(const std::string& body_part)
            {
                body += body_part;
                return end();
            }

            // returns a custom function to check if it's alive
            bool is_alive()
            {
                return is_alive_helper_ && is_alive_helper_();
            }

        private:
            bool completed_{};
            std::function<void()> complete_request_handler_;
            std::function<bool()> is_alive_helper_;

            //In case of a JSON object, set the Content-Type header
            response& json_mode()
            {
                set_header("Content-Type", "application/json");
                return *this;
            }
    };
}

#endif //WPP_RESPONSE_H
