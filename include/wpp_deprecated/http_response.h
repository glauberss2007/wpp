#pragma once
#include <string>
#include <unordered_map>
#include <initializer_list>

#include "json.hpp"
#include "http_request.h"
#include "structures.h"

namespace wpp
{

    enum StatusCode {
        // 1xx Informational responses
        Continue100 = 100,
        SwitchingProtocols101 = 101,
        Processing102 = 102,
        // 2xx Success
        OK200 = 200,
        Created201 = 201,
        Accepted202 = 202,
        NonAuthoritativeInformation203 = 203,
        NoContent204 = 204,
        ResetContent205 = 205,
        PartialContent206 = 206,
        MultiStatus207 = 207,
        AlreadyReported208 = 208,
        IMUsed209 = 209,
        // 3xx Redirection
        MultipleChoices300 = 300,
        MovedPermanently301 = 301,
        Found302 = 302,
        SeeOther303 = 303,
        NotModified304 = 304,
        UseProxy305 = 305,
        SwitchProxy306 = 306,
        TemporaryRedirect307 = 307,
        PermanentRedirect308 = 308,
        // 4xx Client errors
        BadRequest400 = 400,
        Unauthorized401 = 401,
        PaymentRequired402 = 402,
        Forbidden403 = 403,
        NotFound404 = 404,
        MethodNotAllowed405 = 405,
        NotAcceptable406 = 406,
        ProxyAuthenticationRequired407 = 407,
        RequestTimeout408 = 408,
        Conflict409 = 409,
        Gone410 = 410,
        LengthRequired411 = 411,
        PreconditionFailed412 = 412,
        PayloadTooLarge413 = 413,
        URITooLong414 = 414,
        UnsupportedMediaType415 = 415,
        RangeNotSatisfiable416 = 416,
        ExpectationFailed417 = 417,
        ImaTeapot418 = 418,
        MisdirectedRequest421 = 421,
        UnprocessableEntity422 = 422,
        Locked423 = 423,
        FailedDependency424 = 424,
        UpgradeRequired426 = 426,
        PreconditionRequired427 = 427,
        TooManyRequests428 = 428,
        RequestHeaderFieldsTooLarge431 = 431,
        UnavailableForLegalReasons451 = 451,
        // 5xx Server error
        InternalServerError500 = 500,
        NotImplemented501 = 501,
        BadGateway502 = 502,
        ServiceUnavailable503 = 503,
        GatewayTimeout504 = 504,
        HTTPVersionNotSupported505 = 505,
        VariantAlsoNegotiates506 = 506,
        InsuffientStorage507 = 507,
        LoopDetected508 = 508,
        NotExtended510 = 510,
        NetworkAuthenticationRequired511 = 511
    };

    using json = nlohmann::json;

    // forward declaring Connection (just to make it a friend class)
    template <typename Adaptor, typename Handler, typename ... Middlewares>
    class Connection;

    // class with a response (opposite to parser.h's request)
    struct response
    {
        template <typename Adaptor, typename Handler, typename ... Middlewares>
        friend class wpp::Connection;

        // these variables are public for easy access
        // response's status code (200 = OK)
        int code{(int)StatusCode::OK200};
        // body of the response
        std::string body;
        // json value to be returned (if that's the case)
        json json_value;
        // 'headers' is a hash<string,string> that stores HTTP headers.
        ci_map headers;

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

        // get header in ci_map
        const std::string& get_header_value(const std::string& key, const std::string& default_ = "")
        {
            return wpp::get_header_value(headers, key, default_);
        }


        // constructors
        response() {}
        explicit response(int code) : code(code) {}
        explicit response(StatusCode code) : code((int)code) {}
        response(std::string body) : body(std::move(body)) {}
        response(json&& json_value) : json_value(std::move(json_value))
        {
            json_mode();
        }
        response(int code, std::string body) : code(code), body(std::move(body)) {}
        response(StatusCode code, std::string body) : code((int)code), body(std::move(body)) {}
        response(const json& json_value) : body(json_value.dump())
        {
            json_mode();
        }
        response(int code, const wpp::json& json_value) : code(code), body(json_value.dump())
        {
            json_mode();
        }
        response(StatusCode code, const wpp::json& json_value) : code((int)code), body(json_value.dump())
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
            code = 200;
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
