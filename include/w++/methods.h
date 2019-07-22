//
// Created by Alan de Freitas on 16/09/17.
//

#ifndef WPP_METHODS_H
#define WPP_METHODS_H

namespace wpp {
    enum class method {
            delete_ = 0,
            get,
            head,
            post,
            put,
            connect,
            options,
            trace,
    };

    inline std::string method_string(method method_) {
        switch (method_) {
            case method::delete_:
                return "DELETE";
            case method::get:
                return "GET";
            case method::head:
                return "HEAD";
            case method::post:
                return "POST";
            case method::put:
                return "PUT";
            case method::connect:
                return "CONNECT";
            case method::options:
                return "OPTIONS";
            case method::trace:
                return "TRACE";
        }
        return "invalid";
    }

    constexpr size_t number_of_methods(){ return 8; }

    constexpr unsigned int str2int(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
    }

    inline method method_enum(std::string method_) {
        switch (str2int(method_.c_str())) {
            case str2int("DELETE"):
                return method::delete_;
            case str2int("GET"):
                return method::get;
            case str2int("HEAD"):
                return method::head;
            case str2int("POST"):
                return method::post;
            case str2int("PUT"):
                return method::put;
            case str2int("CONNECT"):
                return method::connect;
            case str2int("OPTIONS"):
                return method::options;
            case str2int("TRACE"):
                return method::trace;
        }
        return method::get;
    }

}


#endif //WPP_METHODS_H
