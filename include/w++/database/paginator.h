//
// Created by Alan de Freitas on 21/11/2017.
//

#ifndef WPP_PAGINATOR_H
#define WPP_PAGINATOR_H

#include "utils/container/php_utils.h"
#include "utils/container/laravel_utils.h"
#include "utils/string_utils.h"
#include "datatype_alias.h"
#include "aux_data_types.h"

namespace wpp {
    namespace db {

        class paginator {
            public:
                using self_t = paginator;
            protected:
                // All of the items being paginated.
                wpp::db::result _items;

            protected:
                // The number of items to be shown per page.
                int _per_page;

            protected:
                // The current page being "viewed".
                int _current_page;

            protected:
                // The base path to assign to all URLs.
                string _path = "/";

            protected:
                // The query parameters to add to all URLs.
                vector<pair<string,string>> _query = {};

            protected:
                // The URL fragment to add to all URLs.
                string _fragment;

            protected:
                // The query string variable used to store the page.
                string _page_name = "page";

            protected:
                // The current page resolver callback.
                static function<string()> _current_path_resolver;

            protected:
                // The current page resolver callback.
                static function<int(string)> _current_page_resolver;

            protected:
                // The view factory resolver callback.
                static function<factory()> _view_factory_resolver;

            public:
                // The default pagination view.
                static string _default_view;

            public:
                // The default "simple" pagination view.
                static string _default_simple_view;

            protected:
                // Determine if the given value is a valid page number.
                bool is_valid_page_number(int _page) {
                    return _page >= 1;
                }

                bool is_valid_page_number(string _page) {
                    _page = utils::filter_var_int(_page);
                    long page_num = 0;
                    if (utils::is_int(_page)) {
                        page_num = stol(_page);
                    }
                    return page_num >= 1;
                }

            public:
                // Get the URL for the previous page.
                string previous_page_url() {
                    if (this->current_page() > 1) {
                        return this->url(this->current_page() - 1);
                    }
                    return string();
                }

            public:
                // Create a range of pagination URLs.
                vector<pair<int,string>> get_url_range(int _start, int _end) {
                    vector<int> v = utils::range(_start, _end);
                    vector<pair<int,string>> v2;
                    for (auto &&_page : v) {
                        v2.push_back({_page,this->url(_page)});
                    }
                    return v2;
                }

            public:
                // Get the URL for a given page number.
                string url(int _page) {
                    if (_page <= 0) {
                        _page = 1;
                    }

                    // If we have any extra query string key / value pairs that need to be added
                    // onto the URL, we will put them in query string form and then attach it
                    // to the URL. This allows for extra information like sortings storage.
                    vector<pair<string,string>> _parameters = {{this->_page_name, std::to_string(_page)}};

                    if (!this->_query.empty()) {
                        _parameters = utils::array_merge(this->_query, _parameters);
                    }

                    string query_string = "";
                    for (int i = 0; i < _parameters.size(); ++i) {
                        pair<string,string>& parameter = _parameters[i];
                        query_string += parameter.first + "=" + parameter.second;
                        if (i < _parameters.size() - 1){
                            query_string += "&";
                        }
                    }

                    return this->_path + (utils::contains(this->_path, "?") ? "&" : "?") + query_string + this->build_fragment();
                }

            public:
                // Get / set the URL fragment to be appended to URLs.
                string fragment(string _fragment = "") {
                    if (_fragment.empty()) {
                        return this->_fragment;
                    }

                    this->_fragment = _fragment;

                    return this->_fragment;
                }

            public:
                // Add a set of query string values to the paginator.
                self_t& appends(string _key, string _value = "") {
                    return this->add_query(_key, _value);
                }

                self_t& appends(vector<pair<string,string>> _key, string _value = "") {
                    return this->append_array(_key);
                }

            protected:
                // Add an array of query string values.
                self_t& append_array(vector<pair<string,string>> _keys) {
                    for (pair<string,string>& k: _keys) {
                        this->add_query(k.first, k.second);
                    }

                    return *this;
                }

            protected:
                // Add a query string value to the paginator.
                self_t& add_query(string _key, string _value) {
                    if (_key != this->_page_name) {
                        vector<pair<string,string>>::iterator iter = std::find_if(this->_query.begin(), this->_query.end(), [&_key](pair<string,string>& x){
                            return x.first == _key;
                        });
                        if (iter == this->_query.end()){
                            this->_query.push_back({_key,_value});
                        } else {
                            iter->second = _value;
                        }
                    }

                    return *this;
                }

            protected:
                // Build the full fragment portion of a URL.
                string build_fragment() {
                    return !this->_fragment.empty() ? "#" + this->_fragment : "";
                }

            public:
                // Get the slice of items being paginated.
                wpp::db::result items() {
                    return this->_items;
                }

            public:
                // Get the number of the first item in the slice.
                int first_item() {
                    return !this->_items.empty() ? (this->_current_page - 1) * this->_per_page + 1 : -1;
                }

            public:
                // Get the number of the last item in the slice.
                int last_item() {
                    return !this->_items.empty() ? this->first_item() + this->count() - 1 : -1;
                }

            public:
                // Get the number of items shown per page.
                int per_page() {
                    return this->_per_page;
                }

            public:
                // Determine if there are enough items to split into multiple pages.
                bool has_pages() {
                    return this->current_page() != 1 || this->has_more_pages();
                }

            public:
                // Determine if the paginator is on the first page.
                bool on_first_page() {
                    return this->current_page() <= 1;
                }

            public:
                // Get the current page.
                int current_page() {
                    return this->_current_page;
                }

            public:
                // Get the query string variable used to store the page.
                string get_page_name() {
                    return this->_page_name;
                }

            public:
                // Set the query string variable used to store the page.
                self_t& set_page_name(string _name) {
                    this->_page_name = _name;

                    return *this;
                }

            public:
                // Set the base path to assign to all URLs.
                self_t& with_path(string _path) {
                    return this->set_path(_path);
                }

            public:
                // Set the base path to assign to all URLs.
                self_t& set_path(string _path) {
                    this->_path = _path;

                    return *this;
                }

            public:
                // Resolve the current request path or return the default value.
                static string resolve_current_path(string _default = "/") {
                    if (self_t::_current_path_resolver) {
                        return self_t::_current_path_resolver();
                    }
                    return _default;
                }

            public:
                // Set the current request path resolver callback.
                template<typename Closure>
                static void current_path_resolver(Closure _resolver) {
                    self_t::_current_path_resolver = _resolver;
                }

            public:
                // Resolve the current page or return the default value.
                static int resolve_current_page(string _page_name = "page", int _default = 1) {
                    if (self_t::_current_page_resolver) {
                        return self_t::_current_page_resolver(_page_name);
                    }

                    return _default;
                }

            public:
                // Set the current page resolver callback.
                template<typename Closure>
                static void current_page_resolver(Closure _resolver) {
                    self_t::_current_page_resolver = _resolver;
                }

            public:
                // Get an instance of the view factory from the resolver.
                static factory view_factory() {
                    return self_t::_view_factory_resolver();
                }

            public:
                // Set the view factory resolver callback.
                template<typename Closure>
                static void view_factory_resolver(Closure _resolver) {
                    self_t::_view_factory_resolver = _resolver;
                }

            public:
                // Set the default pagination view.
                static void default_view(string _view) {
                    self_t::_default_view = _view;
                }


            public:
                // Set the default "simple" pagination view.
                static void default_simple_view(string _view) {
                    self_t::_default_simple_view = _view;
                }

            public:
                // Get an iterator for the items.
                wpp::db::result::iterator get_iterator() {
                    return this->_items.begin();
                }

                wpp::db::result::iterator get_begin_iterator() {
                    return this->_items.begin();
                }

                wpp::db::result::iterator get_end_iterator() {
                    return this->_items.end();
                }

            public:
                // Determine if the list of items is empty or not.
                bool is_empty() {
                    return this->_items.empty();
                }

            public:
                // Get the number of items for the current page.
                size_t count() {
                    return this->_items.size();
                }

            public:
                // Get the paginator"s underlying collection.
                wpp::db::result get_collection() {
                    return this->_items;
                }

            public:

                // Set the paginator"s underlying collection.
                self_t& set_collection(wpp::db::result _collection) {
                    this->_items = _collection;

                    return *this;
                }

            public:
                // Determine if the given item exists.
                bool offset_exists(size_t _key) {
                    return _key < this->_items.size();
                }

            public:
                // Get the item at the given offset.
                wpp::db::row offset_get(size_t _key) {
                    return this->_items[_key];
                    //wpp::db::result::iterator iter = std::find_if(this->_items.begin(), this->_items.end(), [&_key](pair<string,string>& x){
                    //    return x.first == _key;
                    //});
                    //if (iter != this->_items.end()){
                    //    return iter->second;
                    //} else {
                    //    return "";
                    //}
                }

            public:
                // Set the item at the given offset.
                void offset_set(size_t _key, wpp::db::row _value) {
                    auto iter = this->_items.begin() + _key;
                    *iter = _value;
                    //vector<pair<string,string>>::iterator iter = std::find_if(this->_items.begin(), this->_items.end(), [&_key](pair<string,string>& x){
                    //    return x.first == _key;
                    //});
                    //if (iter != this->_items.end()){
                    //    iter->second = _value;
                    //} else {
                    //    this->_items.push_back({_key, _value});
                    //}
                }

            public:
                // Unset the item at the given key.
                void offset_unset(size_t _key) {
                    // this->_items.erase(this->_items.begin() + _key);
                    // todo: erase not implemented
                    //vector<pair<string,string>>::iterator iter = std::find_if(this->_items.begin(), this->_items.end(), [&_key](pair<string,string>& x){
                    //    return x.first == _key;
                    //});
                    //if (iter != this->_items.end()){
                    //    this->_items.erase(iter);
                    //}
                }

            public:
                // Render the contents of the paginator to HTML.
                string to_html() {
                    return (string)
                    this->render();
                }


            public:
                // Make dynamic calls into the collection.
                //template<typename mixed>
                //mixed __call(string _method, array _parameters) {
                //    return this->get_collection()->_method(..._parameters);
                //}

            public:
                // Render the contents of the paginator when casting to string.
                string to_string() {
                    return this->render();
                }


            protected:
                // Determine if there are more items in the data source.
                bool _has_more;

            public:
                // Create a new paginator instance.
                paginator(wpp::db::result __items, int _per_page, int _current_page = -1, vector<pair<string,string>> _options = {}) : _items(__items) {
                    for (pair<string,string> _option: _options) {
                        if (_option.first == "default_simple_view"){
                            this->_default_simple_view = _option.second;
                        } else if (_option.first == "default_view"){
                            this->_default_view = _option.second;
                        } else if (_option.first == "fragment"){
                            this->_fragment = _option.second;
                        } else if (_option.first == "page_name"){
                            this->_page_name = _option.second;
                        } else if (_option.first == "path"){
                            this->_path = _option.second;
                        }
                    }
                    this->_per_page = _per_page;
                    this->_current_page = this->set_current_page(_current_page);
                    this->_path = this->_path != "/" ? utils::rtrim(this->_path, "/") : this->_path;

                    this->_has_more = this->_items.size() > this->_per_page;
                    this->_items = utils::array_slice(this->_items, 0, this->_per_page);
                }

            protected:
                // Get the current page for the request.
                int set_current_page(int _current_page) {
                    _current_page = _current_page > 0 ? _current_page : paginator::resolve_current_page();

                    return this->is_valid_page_number(_current_page) ? _current_page : 1;
                }

            protected:
                // Set the items for the paginator.
                void set_items(wpp::db::result _items) {
                    this->_items = _items;

                    this->_has_more = this->_items.size() > this->_per_page;

                    this->_items = utils::array_slice(this->_items, 0, this->_per_page);
                }

            public:
                // Get the URL for the next page.
                string next_page_url() {
                    if (this->has_more_pages()) {
                        return this->url(this->current_page() + 1);
                    }
                    return string();
                }

            public:
                // Render the paginator using the given view.
                string links(string _view = "", vector<pair<string,string>> _data = {}) {
                    return this->render(_view, _data);
                }

            public:
                // Render the paginator using the given view.
                string render(string _view = "", vector<pair<string,string>> _data = {}) {
                    return _view;
                    // this can be mustache templated later
                    //self_t::view_factory().make(!_view.empty() ? _view : self_t::_default_simple_view, utils::array_merge(_data, {"paginator" => _this})).render();
                }

            public:
                // Manually indicate that the paginator does have more pages.
                self_t& has_more_pages_when(bool _value = true) {
                    this->_has_more = _value;

                    return *this;
                }

            public:
                // Determine if there are more items in the data source.
                bool has_more_pages() {
                    return this->_has_more;
                }

            public:
                // Get the instance as an array.
                vector<pair<string, string>> to_array() {
                    return {
                            {"per_page",      std::to_string(this->per_page())},
                            {"current_page",  std::to_string(this->current_page())},
                            {"next_page_url", this->next_page_url()},
                            {"prev_page_url", this->previous_page_url()},
                            {"from",          std::to_string(this->first_item())},
                            {"to",            std::to_string(this->last_item())}
                            //,
                            //{"data",          utils::implode(", ",utils::flatten(this->_items))}
                    };
                }

            public:
                // Convert the object into something JSON serializable.
                vector<pair<string,string>> json_serialize() {
                    return this->to_array();
                }

            public:
                // Convert the object to its JSON representation.
                string to_json(int _options = 0) {
                    string json_str = "{\n"
                            "           \"per_page\":      " + std::to_string(this->per_page()) + ",\n"
                            "           \"current_page\":  " + std::to_string(this->current_page()) + ",\n"
                            "           \"next_page_url\": \"" + this->next_page_url() + "\",\n"
                            "           \"prev_page_url\": \"" + this->previous_page_url() + "\",\n"
                            "           \"from\":          " + std::to_string(this->first_item()) + ",\n"
                            "           \"to\":            " + std::to_string(this->last_item()) + "\n";
                            //"           \"data\":          {";
                    //for (int i = 0; i < this->_items.size(); ++i) {
                    //    pair<string,string> &item = this->_items[i];
                    //    if (i < this->_items.size() - 1){
                    //        json_str += "                      \"" + item.first + "\": \"" + item.second + "\",\n";
                    //    } else {
                    //        json_str += "                      \"" + item.first + "\": \"" + item.second + "\"\n";
                    //    }
                    //}
                    //json_str += "                            }\n}";
                    json_str += "}";
                    return json_str;
                }
        };
        // The default pagination view.
        string paginator::_default_view = "pagination::default";
        // The default "simple" pagination view.
        string paginator::_default_simple_view = "pagination::simple-default";
    }
}


#endif //WPP_PAGINATOR_H
