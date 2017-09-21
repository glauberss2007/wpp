//
// Created by Alan de Freitas on 16/09/17.
//

#ifndef WPP_REQUEST_H
#define WPP_REQUEST_H

#include "methods.h"
#include <unordered_map>
#include <regex>
#include "query_string.h"
#include "routing_parameters.h"


namespace wpp {
    struct route_properties;

    struct request {
        using ci_map = std::unordered_multimap<std::string, std::string>;

        method method_requested; // default: GET
        std::string raw_url; // original url
        std::string url; // processed url (request receives it already processed, it just copies everything)
        multimap<std::string,std::string> url_params; // whole query string (with url_params)
        ci_map headers; // unordered map of headers
        std::string body; // body of the request
        std::string http_version; // body of the request
        std::string method_string; // body of the request
        std::string path; // body of the request
        std::string remote_endpoint_address;
        unsigned short remote_endpoint_port;
        routing_params query_parameters;
        route_properties* current_route{nullptr};

        request() : method_requested(method::get) {}

        request(method method__,
                std::string raw_url__,
                std::string url__,
                multimap<string,string> url_params__,
                ci_map headers__,
                std::string body__)
                : method_requested(method__), raw_url(std::move(raw_url__)), url(std::move(url__)),
                  url_params(std::move(url_params__)), headers(std::move(headers__)), body(std::move(body__)) {}

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

        // TODO: $request->path(); // The path method returns the request's path information. So, if the incoming request is targeted at http://domain.com/foo/bar, the path method will return foo/bar:
        // TODO: is('admin/*') method allows you to verify that the incoming request path matches a given pattern.
        // TODO: $request->url();
        // TODO: $request->fullUrl();
        // TODO: $request->isMethod('post')
        // TODO: $input = $request->all(); // return everything in json
        // TODO: $request->input("name", default_ = ""); regardless of the verb - $request->input('products.0.name'); or $request->input('products.*.name');
        // TODO: $request->only(['username', 'password']);
        // TODO: $request->except(['credit_card']);
        // TODO: $request->has('name')
        // TODO: $request->flash(); // flash the current input to the session so that it is available during the user's next request to the application
        // TODO: $request->flashOnly(['username', 'email']);
        // TODO: $request->flashExcept('password');
        // TODO: $request->old('username');
        // TODO: $request->cookie('name');
        // TODO: $cookie = cookie('name', 'value', $minutes);
        // TODO: $request->file('photo');
        // TODO: ($request->hasFile('photo'))
        // TODO: $request->file('photo')->isValid() // verify that there were no problems uploading the file via the isValid method
        // TODO: $request->file('photo')->path(); $request->file('photo')->extension();
        // TODO: $path = $request->photo->store('images');
        // TODO: $path = $request->photo->storeAs('images', 'filename.jpg');
    };

}



#endif //WPP_REQUEST_H
