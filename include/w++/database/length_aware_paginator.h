//
// Created by Alan de Freitas on 21/11/2017.
//

#ifndef WPP_LENGTH_AWARE_PAGINATOR_H
#define WPP_LENGTH_AWARE_PAGINATOR_H

#include "database/paginator.h"

namespace wpp {
    namespace db {
        class length_aware_paginator: public paginator {
                 // The total number of items before slicing.
            protected:
                int _total;

                 // The last available page.
            protected:
                int _last_page;

            public:

                // Create a new paginator instance.
            length_aware_paginator(wpp::db::result _items, int total, int _per_page, int _current_page = -1, vector<pair<string,string>> _options = {})
                : paginator(_items,_per_page,_current_page,_options)
                    {
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
                this->_total = total;
                this->_per_page = _per_page;
                this->_last_page = (int) std::ceil(total / _per_page);
                this->_path = this->_path != "/" ? utils::rtrim(this->_path, "/") : this->_path;
                this->_current_page = this->set_current_page(_current_page, this->_page_name);
                this->set_items(_items);
            }


            protected:

                // Get the current page for the request.
                int set_current_page(int _current_page, string page_name) {
                    _current_page = _current_page > 0 ? _current_page : paginator::resolve_current_page(page_name);

                    return this->is_valid_page_number(_current_page) ? _current_page : 1;
                }

            protected:

                // Get the array of elements to pass to the view.
                vector<string> elements()
                {
                    return vector<string>({"Function not implemented"});
                            //vector<string>({this->_items.front().second,"...",this->_items.back().second});
                }

            public:

                // Get the total number of items being paginated.
                int total()
                {
                    return this->_total;
                }

                // Determine if there are more items in the data source.
                bool hasMorePages()
                {
                    return this->current_page() < this->last_page();
                }

                // Get the URL for the next page.
                string next_page_url()
                {
                    if (this->last_page() > this->current_page()) {
                        return this->url(this->current_page() + 1);
                    }
                    return string();
                }

                // Get the last page.
                int last_page()
                {
                    return this->_last_page;
                }

                // Get the instance as an array.
                vector<pair<string, string>> to_array() {
                    return {
                            {"per_page",      std::to_string(this->per_page())},
                            {"current_page",  std::to_string(this->current_page())},
                            {"last_page",     std::to_string(this->last_page())},
                            {"next_page_url", this->next_page_url()},
                            {"prev_page_url", this->previous_page_url()},
                            {"from",          std::to_string(this->first_item())},
                            {"to",            std::to_string(this->last_item())}
                            //{"data",          utils::implode(", ",utils::flatten(this->_items))}
                    };
                }



                // Convert the object into something JSON serializable.
                vector<pair<string,string>> json_serialize()
                {
                    return this->to_array();
                }

                /**
                 * Convert the object to its JSON representation.
                 *
                 * @param  int  $options
                 * @return string
                 */
                // Convert the object to its JSON representation.
                string to_json(int _options = 0) {
                    string json_str = "{\n"
                                              "           \"per_page\":      " + std::to_string(this->per_page()) + ",\n"
                                              "           \"current_page\":  " + std::to_string(this->current_page()) + ",\n"
                                              "           \"last_page\":     " + std::to_string(this->last_page()) + ",\n"
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
    }
}

#endif //WPP_LENGTH_AWARE_PAGINATOR_H
