//
// Created by Alan de Freitas on 15/09/17.
//

#ifndef WPP_RESPONSE_H
#define WPP_RESPONSE_H

#include <string>
#include <unordered_map>
#include <initializer_list>
#include <functional>
#include <memory>

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "utils/json.hpp"
#include "mustache/mustache.hpp"

#include "request.h"
#include "enums.h"

namespace wpp {

    using ci_map = std::unordered_multimap<std::string, std::string>;

    using namespace kainjow::mustache;

    using json = nlohmann::json;

    class application;


    struct response
    {

            ///////////////////////////////////////////////////////////////
            //                      PUBLIC MEMBERS                       //
            ///////////////////////////////////////////////////////////////

            // these variables are public for easy access
            // response's status code (200 = OK)
            enum status_code code{wpp::status_code::success_ok};
            // body of the response
            std::string body;
            // 'headers' is a hash<string,string> that stores HTTP headers.
            ci_map headers{{"Content-Type","text/plain; charset=utf-8"}};
            application *parent_application{nullptr};
            string _csrfmiddlewaretoken{""};
            std::shared_ptr<ifstream> _file_response;
            std::unordered_map<std::string, std::tuple<std::string,int,string,string,bool,bool>> cookie_jar;

            // Merge responses
            void merge(response &right){
                // right code has precedence
                this->code = right.code;
                // right body has precedence if it has a body
                if (!right.body.empty()){
                    this->body = right.body;
                }
                // content of the right has precedence, other headers can just be merged
                if (right.headers.count("Content-Type") && this->headers.count("Content-Type")){
                    this->headers.erase("Content-Type");
                }
                this->headers.insert(right.headers.begin(),right.headers.end());
                // parent application
                if (right.parent_application != nullptr){
                    this->parent_application = right.parent_application;
                }
                // token
                if (!right._csrfmiddlewaretoken.empty()){
                    this->_csrfmiddlewaretoken = right._csrfmiddlewaretoken;
                }
                // file responses have precedence
                if (right._file_response){
                    if (right._file_response->good()){
                        this->_file_response = right._file_response;
                    }
                }
                // cookies are just merged
                this->cookie_jar.insert(right.cookie_jar.begin(),right.cookie_jar.end());
            }


            ///////////////////////////////////////////////////////////////
            //                 ESPECIAL RESPONSE TYPES                   //
            ///////////////////////////////////////////////////////////////

            struct pre_processed_view {
                std::time_t timestamp;
                wpp::mustache formatted_template;
                std::vector<std::string> partials;
                std::vector<std::time_t> partials_timestamp;
                pre_processed_view(std::time_t _timestamp, wpp::mustache _formatted_template)
                        : timestamp(_timestamp), formatted_template(_formatted_template){}
            };

            template <typename string_type>
            struct pre_processed_partial {
                std::time_t timestamp;
                basic_data<string_type> formatted_template;
                pre_processed_partial(std::time_t _timestamp, basic_data<string_type> _formatted_template)
                        : timestamp(_timestamp), formatted_template(_formatted_template){}
            };

            struct view {
                using string_type = std::string;

                string _filename;
                wpp::mustache_data _data;
                string& _templates_root_path;
                basic_data<string_type>& _lambdas;
                std::unordered_map<std::string,std::function<wpp::json()>>& _view_data;
                unordered_map<std::string, pre_processed_view>& _pre_processed_views;
                std::unordered_map<mustache::string_type, pre_processed_partial<mustache::string_type>>& _pre_processed_partials;

                view(string filename,
                     wpp::json json_data,
                     string& templates_root_path,
                     basic_data<string_type>& lambdas,
                     std::unordered_map<std::string,std::function<wpp::json()>>& view_data,
                     unordered_map<std::string, response::pre_processed_view>& pre_processed_views,
                     std::unordered_map<mustache::string_type, response::pre_processed_partial<mustache::string_type>>& pre_processed_partials
                    )
                        : _filename(std::move(filename)),
                          _templates_root_path(templates_root_path),
                          _lambdas(lambdas),
                          _view_data(view_data),
                          _pre_processed_views(pre_processed_views),
                          _pre_processed_partials(pre_processed_partials)
                {
                    json_to_mustache(json_data,_data);
                };

                static void json_to_mustache(wpp::json& j, wpp::mustache_data& d){
                    if (j.is_array()){
                        d = wpp::mustache_data{mustache_data::type::list};
                        for (json::iterator it = j.begin(); it != j.end(); ++it) {
                            if (it->is_array() || it->is_object()){
                                wpp::mustache_data d2;
                                json_to_mustache(*it,d2);
                                d.push_back(std::move(d2));
                            } else if (it->is_string()) {
                                d.push_back(it->get<string>());
                            } else if (it->is_number()) {
                                d.push_back(it->dump());
                            } else if (it->is_boolean()){
                                d.push_back(it->get<bool>() ? mustache_data::type::bool_true : mustache_data::type::bool_false);
                            } else if (it->is_null()) {
                                d.push_back(mustache_data::type::invalid);
                            }
                        }
                    } else if (j.is_object()) {
                        d = wpp::mustache_data{mustache_data::type::object};
                        for (json::iterator it = j.begin(); it != j.end(); ++it) {
                            if (it.value().is_array() || it.value().is_object()){
                                wpp::mustache_data d2;
                                json_to_mustache(*it,d2);
                                d.set(it.key(),std::move(d2));
                            } else if (it.value().is_string()) {
                                d.set(it.key(),it.value().get<string>());
                            } else if (it.value().is_number()) {
                                d.set(it.key(),it.value().dump());
                            } else if (it.value().is_boolean()){
                                d.set(it.key(),it.value().get<bool>() ? mustache_data::type::bool_true : mustache_data::type::bool_false);
                            } else if (it.value().is_null()) {
                                d.set(it.key(),mustache_data::type::invalid);
                            }
                        }
                    } else if (j.is_string()) {
                        d = j.get<string>();
                    } else if (j.is_number()) {
                        d = j.dump();
                    } else if (j.is_boolean()){
                        d = j.get<bool>() ? mustache_data::type::bool_true : mustache_data::type::bool_false;
                    } else if (j.is_null()){
                        return;
                    }
                }

            };

            struct html {
                html(string text) : _data(std::move(text)){};
                string _data;
            };

            struct text {
                text(string text) : _data(std::move(text)){};
                string _data;
            };

            struct redirect {
                redirect(string __to, status_code __code = wpp::status_code::redirection_found, ci_map __headers = {}) : _to(std::move(__to)), _code(__code), _headers(__headers){};
                string _to;
                enum status_code _code{wpp::status_code::redirection_found};
                ci_map _headers;
            };


            ///////////////////////////////////////////////////////////////
            //                      CONSTRUCTORS                         //
            ///////////////////////////////////////////////////////////////

            response() {}
            response(enum status_code code) {}

            response(std::string body) : body(std::move(body)) {}
            response(int code, std::string body) : code((status_code)code), body(std::move(body)) {}
            response(status_code code_, std::string body) : code(code_), body(std::move(body)) {}

            response(int body) : body(to_string(body)) {}
            response(int code, int body) : code((status_code)code), body(to_string(body)) {}
            response(status_code code_, int body) : code(code_), body(to_string(body)) {}

            response(char* body) : body(std::move(body)) {}
            response(int code, char* body) : code((status_code)code), body(std::move(body)) {}
            response(status_code code_, char* body) : code(code_), body(std::move(body)) {}

            response(const char* body) : body(std::move(body)) {}
            response(int code, const char* body) : code((status_code)code), body(std::move(body)) {}
            response(status_code code_, const char* body) : code(code_), body(std::move(body)) {}

            response(wpp::json json_value) : body(std::move(json_value.dump())), headers({{"Content-Type","application/json; charset=utf-8"}}) {}
            response(int code_, const wpp::json& json_value) : code((status_code)code_), body(std::move(json_value.dump())), headers({{"Content-Type","application/json; charset=utf-8"}}) {}
            response(status_code code_, const wpp::json& json_value) : code(code_), body(std::move(json_value.dump())), headers({{"Content-Type","application/json; charset=utf-8"}}) {}

            response(wpp::response::html text) : body(std::move(text._data)), headers({{"Content-Type","text/html; charset=utf-8"}}) {}
            response(wpp::response::text text) : body(std::move(text._data)), headers({{"Content-Type","text/plain; charset=utf-8"}}) {}
            response(wpp::response::redirect text) : code(text._code), headers(text._headers) {
                this->set_header("Location",text._to);
                this->set_header("Refresh", string("0; url=") + text._to);
                this->set_header("Content-Type","text/html");
                this->body = string() + "<html>\n"
                                        "<head>\n"
                                        "    <title>Moved</title>\n"
                                        "    <meta http-equiv=\"Refresh\" content=\"0; url="+text._to+"\" />\n"
                                        "</head>\n"
                                        "<body>\n"
                                        "    <h1>Moved</h1>\n"
                                        "    <p>This page has moved to <a href=\""+text._to+"\">"+text._to+"</a>.</p>\n"
                                        "</body>\n"
                                        "</html>";

            }

            response(wpp::response::view view_data) : headers({{"Content-Type","text/html; charset=utf-8"}}) {
                // create a context handler with: the data we have (), the lambdas we registered, and preprocessed templates
                file_partial_context<mustache::string_type> ctx{&view_data._data,&view_data._lambdas,&view_data._pre_processed_views,&view_data._pre_processed_partials,&view_data._templates_root_path,&view_data._view_data};
                // get template
                mustache* tmpl = ctx.get_template(view_data._filename);
                // render in the body of the message
                if (tmpl != nullptr){
                    this->body = tmpl->render(ctx);
                } else {
                    this->body = "Error 500";
                }
                // if a csrf was generated while rendering the view
                const basic_data<std::string>* element = ctx.get("_csrfmiddlewaretoken");
                if (element != nullptr){
                    this->_csrfmiddlewaretoken = element->string_value();
                }

            }

            ///////////////////////////////////////////////////////////////
            //                      OPERATE ON MEMBERS                   //
            ///////////////////////////////////////////////////////////////
            // set header in ci_map
            response& set_header(std::string key, std::string value)
            {
                headers.emplace(std::move(key), std::move(value));
                return *this;
            }

            response& header(std::string key, std::string value)
            {
                return this->set_header(key,value);
            }

            response& cookie(std::string name, std::string value, int minutes = 60, string path = "/", string domain = "", bool secure = false, bool httpOnly = false){
                cookie_jar.emplace(make_pair(name,make_tuple(value,minutes,path,domain,secure,httpOnly)));
                return *this;
            }

            response& write_cookie_headers()
            {
                for (auto &&item: cookie_jar) {
                    std::string name, value;
                    int minutes;
                    string path, domain;
                    bool secure, httpOnly;
                    name = item.first;
                    tie(value, minutes, path, domain, secure, httpOnly) = item.second;
                    // encrypt cookie
                    //string encrypted_cookie = this->parent_application->encrypt(value);
                    string cookie_str;
                    cookie_str = name + "=" + value;
                    if (minutes != 0){
                        char outstr[200];
                        time_t timer;
                        struct tm *utc_time;
                        //const char* fmt = "%a, %d %b %y %T";
                        const char* fmt = "%a, %d %b %y %T %Z";
                        // save current time to timer
                        timer = time(nullptr);
                        // add minutes
                        timer += minutes * 60;
                        // Convert time_t timer to tm utc_time as UTC time
                        utc_time = gmtime(&timer);
                        if (utc_time == nullptr) {
                            perror("gmtime error");
                            exit(EXIT_FAILURE);
                        }
                        // convert to string
                        if (strftime(outstr, sizeof(outstr), fmt, utc_time) == 0) {
                            fprintf(stderr, "strftime returned 0");
                            exit(EXIT_FAILURE);
                        }
                        cookie_str += string("; Expires=") + string(outstr);
                        cookie_str += string("; Max-Age=") + to_string(minutes*60);
                    }
                    if (!path.empty()){
                        cookie_str += string("; Path = ") + path;
                    }
                    if (!domain.empty()){
                        cookie_str += string("; Domain = ") + path;
                    }
                    if (secure){
                        cookie_str += string("; Secure");
                    }
                    if (httpOnly){
                        cookie_str += string("; HttpOnly");
                    }
                    this->set_header("Set-Cookie",cookie_str);
                }
                return *this;
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



            // TODO: redirect(address);
            // TODO: back() (it needs to use the session)
            // TODO: route(string routename) and route(string routename, json params) and route(string routename, ORMobject params)
            // TODO: redirect('dashboard')->with('status', 'Profile updated!'); // Redirecting With Flashed Session Data
            // TODO: response.view("hello", json data, 200); View responses
            // TODO: response()->download($pathToFile, $name, $headers); forces the user's browser to download the file
            // TODO: response()->file($pathToFile, $headers); used to display a file, such as an image or PDF, directly in the user's browser

            // clear
            response& clear()
            {
                body.clear();
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

            // use string stream and then concatenate
            response& operator<<(const string& rhs)
            {
                body += rhs;
                return *this;
            }

            template <typename TYPE>
            response& operator<<(TYPE rhs)
            {
                stringstream stream;
                stream << rhs;
                body += stream.str();
                return *this;
            }

            ///////////////////////////////////////////////////////////////
            //                  OTHER RESPONSE TYPES                     //
            ///////////////////////////////////////////////////////////////


            template <typename string_type>
            class file_partial_context : public basic_context<string_type> {
                public:

                    using clock = std::chrono::steady_clock;
                    using time_point = clock::time_point;

                    file_partial_context(const basic_data<string_type>* data,
                                         const basic_data<string_type>* lambdas,
                                         unordered_map<std::string, pre_processed_view>* pre_processed_views,
                                         std::unordered_map<string_type, pre_processed_partial<string_type>>* pre_processed_partials,
                                         std::string* templates_root_path, std::unordered_map<std::string,std::function<wpp::json()>>* view_data)
                            : _lambdas(lambdas),
                              pre_processed_views_(pre_processed_views),
                              pre_processed_partials_(pre_processed_partials),
                              templates_root_path_(templates_root_path),
                              _view_data(view_data)
                    {
                        push(data);
                    }

                    file_partial_context() {
                    }

                    virtual void push(const basic_data<string_type> *data) override {
                        items_.insert(items_.begin(), data);
                    }

                    virtual void push_copy(const basic_data<string_type> *data) override {
                        items_copy_.push_back(std::unique_ptr<basic_data<string_type>>(new basic_data<string_type>(*data)));
                        items_.insert(items_.begin(), items_copy_.back().get());
                    }

                    virtual void pop() override {
                        items_.erase(items_.begin());
                    }

                    virtual const basic_data<string_type> *get(const string_type &name) const override {
                        if (!name.empty() && name.at(0) == '@') {
                            return _lambdas->get(name);
                        }

                        // process {{.}} name
                        if (name.size() == 1 && name.at(0) == '.') {
                            return items_.front();
                        }
                        if (name.find('.') == string_type::npos) {
                            // process normal name without having to split which is slower
                            for (const auto &item : items_) {
                                const auto var = item->get(name);
                                if (var) {
                                    return var;
                                }
                            }
                            return nullptr;
                        }
                        // process x.y-like name
                        const auto names = split(name, '.');
                        for (const auto &item : items_) {
                            auto var = item;
                            for (const auto &n : names) {
                                var = var->get(n);
                                if (!var) {
                                    break;
                                }
                            }
                            if (var) {
                                return var;
                            }
                        }
                        return nullptr;
                    }

                    virtual const basic_data<string_type>* get_partial(const string_type& name) override {
                        if (_view_data->find(name) != _view_data->end()){
                            basic_data<string_type> * d = new basic_data<string_type>;
                            wpp::json j = (*_view_data)[name]();
                            view::json_to_mustache(j,*d);
                            basic_data<string_type> * d2 = new basic_data<string_type>(*items_.front());
                            d->merge(*d2);
                            delete d2;
                            items_.front() = d;
                        }
                        string complete_file_path_to_template = *(this->templates_root_path_) + "/" + name;
                        auto template_root_path = boost::filesystem::canonical(complete_file_path_to_template);
                        const auto cached = (*pre_processed_partials_).find(name);
                        if (cached != (*pre_processed_partials_).end()) {
                            const auto file_has_not_changed = cached->second.timestamp == boost::filesystem::last_write_time(template_root_path);
                            if (file_has_not_changed){
                                return &(cached->second.formatted_template);
                            } else {
                                string_type result;
                                if (read_file(complete_file_path_to_template, result)) {
                                    basic_data<string_type> tmp = basic_data<string_type>(result);
                                    auto iter = pre_processed_partials_->find(name);
                                    pre_processed_partial<string_type>* partial_ptr = &(iter->second);
                                    partial_ptr->formatted_template = std::move(tmp);
                                    return &(partial_ptr->formatted_template);
                                } else {
                                    return &(cached->second.formatted_template);
                                }
                            }
                        } else {
                            string_type result;
                            if (read_file(complete_file_path_to_template, result)) {
                                pre_processed_partial<string_type> tmp(boost::filesystem::last_write_time(template_root_path),basic_data<string_type>(result));
                                basic_data<string_type>* data_result = &(*pre_processed_partials_).emplace(std::make_pair(name, tmp)).first->second.formatted_template;
                                return data_result;
                            } else {
                                return nullptr;
                            }
                        }
                    }

                    wpp::mustache* get_template(const string_type& name) {
                        string complete_file_path_to_template = *(this->templates_root_path_) + "/" + name;
                        auto template_root_path = boost::filesystem::canonical(complete_file_path_to_template);
                        const auto cached = (*pre_processed_views_).find(name);
                        if (cached != (*pre_processed_views_).end()) {
                            const auto file_has_not_changed = cached->second.timestamp == boost::filesystem::last_write_time(template_root_path);
                            if (file_has_not_changed){
                                return &(cached->second.formatted_template);
                            } else {
                                string_type result;
                                if (read_file(complete_file_path_to_template, result)) {
                                    mustache tmp = mustache(result);
                                    auto iter = pre_processed_views_->find(name);
                                    pre_processed_view* view_ptr = &(iter->second);
                                    view_ptr->formatted_template = std::move(tmp);
                                    return &(view_ptr->formatted_template);
                                } else {
                                    return &(cached->second.formatted_template);
                                }
                            }
                        }
                        string_type result;
                        if (read_file(complete_file_path_to_template, result)) {
                            pre_processed_view tmp(boost::filesystem::last_write_time(template_root_path),mustache(result));
                            wpp::mustache* data_result = &(*pre_processed_views_).emplace(std::make_pair(name, tmp)).first->second.formatted_template;
                            return data_result;
                        } else {
                            return nullptr;
                        }
                    }


                private:

                    bool read_file(const string_type& name, string_type& file_contents) const {
                        boost::iostreams::mapped_file_source file(name);
                        if (file.size() > 0){
                            file_contents = file.data();
                            return true;
                        }
                        return false;
                    }

                    unordered_map<std::string, pre_processed_view>* pre_processed_views_;
                    std::unordered_map<string_type, pre_processed_partial<string_type>>* pre_processed_partials_;
                    const basic_data<string_type>* _lambdas;
                    std::vector<const basic_data<string_type> *> items_;
                    std::vector<std::unique_ptr<basic_data<string_type>>> items_copy_;
                    std::string* templates_root_path_;
                    std::unordered_map<std::string,std::function<wpp::json()>>* _view_data;

            };


        private:
            bool completed_{};
            std::function<void()> complete_request_handler_;
            std::function<bool()> is_alive_helper_;

            //In case of a JSON object, set the Content-Type header
            response& json_mode()
            {
                set_header("Content-Type", "application/json; charset=utf-8");
                return *this;
            }
    };


}

#endif //WPP_RESPONSE_H
