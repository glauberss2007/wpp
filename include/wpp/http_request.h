#pragma once

#include <boost/asio.hpp>

#include "common.h"
#include "structures.h"
#include "query_string.h"

namespace wpp
{
    template <typename T>
    inline const std::string& get_header_value(const T& headers, const std::string& key, const std::string& default_ = "")
    {
        if (headers.count(key))
        {
            return headers.find(key)->second;
        }
        return default_;
    }

	struct DetachHelper;

    // request keeps the message and processes the url (query_string)
    // we can add new headers / get headers
    struct request
    {
        HTTPMethod method; // default: GET
        std::string raw_url; // original url
        std::string url; // processed url (request receives it already processed, it just copies everything)
        query_string url_params; // whole query string (with url_params)
        ci_map headers; // unordered map of headers
        std::string body; // body of the request

        void* middleware_context{};
        boost::asio::io_service* io_service{};

        request()
            : method(HTTPMethod::Get)
        {
        }

        request(HTTPMethod method, std::string raw_url, std::string url, query_string url_params, ci_map headers, std::string body)
            : method(method), raw_url(std::move(raw_url)), url(std::move(url)), url_params(std::move(url_params)), headers(std::move(headers)), body(std::move(body))
        {
        }

        request& add_header(std::string key, std::string value)
        {
            headers.emplace(std::move(key), std::move(value));
            return *this;
        }

        const std::string& get_header_value(const std::string& key) const
        {
            return wpp::get_header_value(headers, key);
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

        // Request the io_service to invoke the given handler and return immediately
        template<typename CompletionHandler>
        void post(CompletionHandler handler)
        {
            io_service->post(handler);
        }

        // Request the io_service to invoke the given handler.
        template<typename CompletionHandler>
        void dispatch(CompletionHandler handler)
        {
            io_service->dispatch(handler);
        }

    };
}
