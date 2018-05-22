//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_STRING_UTILS_H
#define WPP_STRING_UTILS_H

#include <string>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>

#include <unordered_map>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>

#include "container/php_utils.h"

using namespace std;

namespace utils {
    using namespace boost::algorithm;

    // reads on line a file considering all possible line breaks
    template <class IS = std::istream, class STRING = std::string, class DELIM = char>
    bool safe_getline(IS& is, STRING& t, DELIM delim = ';')
    {
        t.clear();
        // The characters in the stream are read one-by-one using a std::streambuf.
        // That is faster than reading them one-by-one using the std::istream.
        // Code that uses streambuf this way must be guarded by a sentry object.
        // The sentry object performs various tasks,
        // such as thread synchronization and updating the stream state.
        std::istream::sentry se(is, true);
        std::streambuf* sb = is.rdbuf();

        while (true) {
            int c = sb->sbumpc();
            if (c == '\n'){
                return !t.empty();
            } else if (c == '\r'){
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return !t.empty();
            } else if (c == delim){
                if((sb->sgetc() == '\n')||(sb->sgetc() == '\r')){
                    sb->sbumpc();
                }
                return !t.empty();
            } else if (c == EOF){
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return !t.empty();
            } else {
                t += (char)c;
            }
        }
    }

    // Determine if a given string contains a given substring.
    bool contains(string const & haystack, string needle)
    {
        return haystack.find(needle) != std::string::npos;
    }

    string lower(string value)
    {
        return boost::algorithm::to_lower_copy(value);
    }

    // Convert a string to snake case.
    string snake(string value, string delimiter = "_")
    {
        string key = value;

        static std::unordered_map<string,map<string,string>> snake_cache;

        if (snake_cache[key].count(delimiter)) {
            return snake_cache[key][delimiter];
        }

        if (!utils::ctype_lower(value)) {
            value = utils::preg_replace("/\\s+/u", "", value);
            value = utils::lower(preg_replace("/(.)(?=[A-Z])/u", "$1" + delimiter, value));
        }

        return snake_cache[key][delimiter] = value;
    }



}

#endif //WPP_STRING_UTILS_H
