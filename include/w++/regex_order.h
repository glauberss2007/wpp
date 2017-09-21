//
// Created by Alan de Freitas on 16/09/17.
//

#ifndef WPP_REGEX_ORDER_H
#define WPP_REGEX_ORDER_H

#include <regex>

namespace wpp {
    class regex_orderable
            : public std::regex {
            std::string str;

        public:
            regex_orderable(const char *regex_cstr) : std::regex(regex_cstr), str(regex_cstr) {}

            regex_orderable(std::string regex_str) : std::regex(regex_str), str(std::move(regex_str)) {}

            bool operator<(const regex_orderable &rhs) const noexcept {
                return str < rhs.str;
            }
    };
}


#endif //WPP_REGEX_ORDER_H
