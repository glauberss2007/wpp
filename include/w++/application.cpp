//
// Created by glauber on 04/09/2019.
//

#include "application.hpp"

    using namespace std::chrono_literals;
    using boost::optional;
    using namespace std;

    using byte = unsigned char;

    using resource_function = std::function<void(wpp::response &, wpp::request &)>;
    using middleware_function = std::function<void(wpp::response &, wpp::request &, std::string parameter, resource_function&)>;


    void wpp::application::error(wpp::status_code s, wpp::response &res, wpp::request &req) {
        vector<pair<wpp::status_code, wpp::route_properties>>::iterator error_route_iter = find_if(
                this->_error_routes,
                [s](pair<wpp::status_code, wpp::route_properties> &x) {
                    return x.first ==
                           s;
                });
        // convert response from wpp back to driver
        if (error_route_iter != this->_error_routes.end()) {
            req.current_route = &(error_route_iter->second);
            req.current_route->_func(res, req);
        } else {
            std::vector<std::pair<wpp::status_code, std::string>> status_strings = wpp::status_codes();
            std::vector<std::pair<wpp::status_code, std::string>>::iterator code_string_iter = find_if(
                    status_strings.begin(), status_strings.end(),
                    [s](std::pair<wpp::status_code, std::string> &x) {
                        return x.first == s;
                    });
            if (code_string_iter != status_strings.end()) {
                res.body = "Error: " + code_string_iter->second;
            } else {
                res.body = "Error " + to_string((int) s);
            }
        }
        res.code = s;
    }

    using self_t = wpp::application;
    using byte = unsigned char;

    self_t &middleware(std::string name,
                       std::function<void(wpp::response &, wpp::request &, wpp::resource_function &)> middleware_func) {
        using namespace std::placeholders;
        std::function<void(wpp::response &, wpp::request &, std::string,
                           wpp::resource_function &)> base_middleware_func =
                [middleware_func](wpp::response &res, wpp::request &req, std::string str,
                                  wpp::resource_function &func) {
                    middleware_func(res, req, func);
                };
        this->_middleware_functions[name] = base_middleware_func;
        return *this;
    }

    self_t &middleware(std::string name, wpp::middleware_function func) {
        this->_middleware_functions[name] = func;
        return *this;
    }

    self_t &middleware_group(std::string name, initializer_list<string> middlewares) {
        this->_middleware_groups[name] = std::vector<string>(middlewares.begin(), middlewares.end());
        return *this;
    }

    self_t &group(initializer_list<std::string> middlewares, std::function<void(wpp::application &)> register_routes_func) {
        return this->group("", middlewares, register_routes_func);
    }

    self_t &group(std::string prefix, initializer_list<std::string> middlewares,
                  std::function<void(wpp::application &)> register_routes_func) {
        this->_group_prefix_context.push_back(prefix);
        this->_group_middleware_context.push_back(vector<string>(middlewares.begin(), middlewares.end()));
        register_routes_func(*this);
        this->_group_prefix_context.pop_back();
        this->_group_middleware_context.pop_back();
        return *this;
    }

    std::pair<resource_function, wpp::routing_params> get_resource(std::string path, wpp::method m) {
        // Find path- and method-match, and call write_server_response_
        // create a regex match
        auto r = this->_route_trie.find(path, m);
        if (std::get<0>(r)) {
            return std::make_pair(this->_routes[std::get<1>(r)]._func, std::move(std::get<2>(r)));
        } else {
            return std::make_pair(nullptr, std::move(std::get<2>(r)));
        }
    }

    unsigned &port() {
        return this->_port;
    }

    self_t &port(unsigned port) {
        this->_port = port;
        return *this;
    }

    self_t &web_root_path(string path) {
        this->_web_root_path = path;
        return *this;
    }

    string &web_root_path() {
        return this->_web_root_path;
    }

    self_t &secure(string certificate_file, string key_file) {
        this->_certificate_file = certificate_file;
        this->_key_file = key_file;
        return *this;
    }

    bool secure() {
        return (!this->_key_file.empty() && !this->_certificate_file.empty());
    }

    self_t &assets_root_path(string path) {
        this->_assets_root_path = path;
        return *this;
    }

    string &assets_root_path() {
        return this->_assets_root_path;
    }

    self_t &session_name(string name) {
        this->session_name_ = name;
        return *this;
    }

    string &session_name() {
        return this->session_name_;
    };

    self_t &guard_call_back(std::function<json(wpp::request &)> __guard_call_back) {
        this->_guard_call_back = __guard_call_back;
        return *this;
    }

    std::function<json(wpp::request &)> &guard_call_back() {
        return this->_guard_call_back;
    }

    self_t &max_session_inactive_time(std::chrono::duration<double, std::milli> time) {
        this->max_session_inactive_time_ = time;
        return *this;
    }

    std::chrono::duration<double, std::milli> &max_session_inactive_time() {
        return this->max_session_inactive_time_;
    }

    self_t &templates_root_path(string path) {
        this->_templates_root_path = path;
        return *this;
    }

    self_t &user_agent_parser_root_path(string path) {
        this->_user_agent_parser_root_path = path;
        return *this;
    }

    self_t &lambda(string name, std::function<std::string(const std::string &)> f) {
        this->_lambdas[string("@") + name] = wpp::mustache_data{wpp::basic_lambda<std::string>(f)};
        return *this;
    }

    self_t &lambda(string name, std::function<std::string(const std::string &, wpp::renderer &)> f) {
        this->_lambdas[string("@") + name] = wpp::mustache_data{basic_lambda2<std::string>{f}};
        return *this;
    }

    wpp::response::view view(string filename, wpp::json json_data) {
        return wpp::response::view(filename, json_data, this->_templates_root_path, this->_lambdas, this->_view_data, this->_pre_processed_views,
                              this->_pre_processed_partials);
    }

    wpp::response::view view(string filename, wpp::json json_data, wpp::request &req) {
        for (wpp::json::iterator it = req.view_bag.begin(); it != req.view_bag.end(); ++it) {
            json_data.emplace(it.key(), it.value());
        }
        return wpp::response::view(filename, json_data, this->_templates_root_path, this->_lambdas, this->_view_data, this->_pre_processed_views,
                              this->_pre_processed_partials);
    }

    self_t &view_data(std::string filename, std::function<wpp::json()> func) {
        this->_view_data[filename] = func;
        return *this;
    }

    self_t &multithreaded(bool on_off = true) {
        this->_multithreaded = on_off;
        return *this;
    }

    string url_for(string route_name) {
        std::unordered_map<string, unsigned>::iterator it = this->_route_by_name.find(route_name);
        // todo: consider route parameters
        const bool route_exists = it != this->_route_by_name.end();
        if (route_exists) {
            const wpp::route_properties chosen_route = this->_routes[it->second];
            string uri;
            for (const string item : chosen_route._uri_members) {
                uri += item + "/";
            }
            return this->web_root_path() + uri;
        } else {
            return this->web_root_path();
        }
    }

    string asset(string asset_name) {
        return this->web_root_path() + asset_name;
    }

    pair<bool, wpp::route_properties> route(string route_name) {
        auto it = this->_route_by_name.find(route_name);
        if (it != this->_route_by_name.end()) {
            return make_pair(true, wpp::_routes[it->second]);
        } else {
            return make_pair(false, this->_routes[0]);
        }
    }

    self_t &redirect(string route_name, wpp::response &res, wpp::request &req) {
        // todo: consider route parameters
        pair<bool, wpp::route_properties> r = this->route(route_name);
        if (r.first) {
            r.second._func(res, req);
        }
        return *this;
    }

    wpp::cache &get_cache() {
        return cache_;
    }

    void setup_trie() {
        for (int i = 0; i < this->_routes.size(); ++i) {
            // include name in app set for faster lookup
            if (_routes[i]._name != "") {
                _route_by_name[_routes[i]._name] = i;
            }
            // create trie
            _route_trie.add(_routes[i], i);
        }
    }

    self_t &set_keys() {
        // Load the necessary cipher
        EVP_add_cipher(EVP_aes_256_cbc());
        // set keys
        gen_params(key, iv);
        // return itself
        return *this;
    }

    string encrypt(string text) {
        // encrypt
        wpp::secure_string protected_text = std::move(text.c_str());
        wpp::secure_string cyphered_text;
        aes_encrypt(key.data(), iv.data(), protected_text, cyphered_text);
        // serialize
        static const char *const lut = "0123456789abcdef";
        size_t len = cyphered_text.size();
        std::string output;
        output.reserve(2 * len);
        for (size_t i = 0; i < len; ++i) {
            const unsigned char c = cyphered_text[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }
        return output;
    }

    string wpp::application::decrypt(string text, string fallback) {
        bool success = true;
        text = decrypt(text, success);
        if (success) {
            return text;
        } else {
            return fallback;
        }
    }

    string decrypt(string text, bool &success) {
        success = false;
        // deserialize
        wpp::secure_string cyphered_text = std::move(text.c_str());
        static const char *const lut = "0123456789abcdef";
        size_t len = cyphered_text.length();
        if (len & 1) {
            return string{""};
        }
        wpp::secure_string unserialized_cyphered_text;
        unserialized_cyphered_text.reserve(len / 2);
        for (size_t i = 0; i < len; i += 2) {
            char a = cyphered_text[i];
            const char *p = std::lower_bound(lut, lut + 16, a);
            if (*p != a) {
                //return string("not a hex digit");
                return string("");
            }

            char b = cyphered_text[i + 1];
            const char *q = std::lower_bound(lut, lut + 16, b);
            if (*q != b) {
                //return string("not a hex digit");
                return string("");
            }
            unserialized_cyphered_text.push_back(((p - lut) << 4) | (q - lut));
        }
        wpp::secure_string returned_text;
        // decrypt
        aes_decrypt(key.data(), iv.data(), unserialized_cyphered_text, returned_text, success);
        return string(returned_text.c_str());
    }

    string digest(string message) {
        const unsigned char *std_message = (const byte *) message.c_str();
        size_t message_len = message.size();
        unsigned char *digest;
        unsigned int digest_len;
        wpp::digest_message(std_message, message_len, &digest, &digest_len);
        string session_id = (char *) digest;
        // serialize to hexadecimal
        static const char *const lut = "0123456789abcdef";
        size_t len = session_id.size();
        std::string digested_message;
        digested_message.reserve(2 * len);
        for (size_t i = 0; i < len; ++i) {
            const unsigned char c = session_id[i];
            digested_message.push_back(lut[c >> 4]);
            digested_message.push_back(lut[c & 15]);
        }
        return digested_message;
    }

    wpp::route_properties &redirect(std::string from, std::string to) {
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
        default_resource({wpp::method::get}, func);
        return *this;
    }

}