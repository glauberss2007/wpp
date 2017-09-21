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
