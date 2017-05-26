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
#include <boost/algorithm/string.hpp>


using namespace std;

namespace utils {
    // reads on line a file considering all possible line breaks
    template <class IS = std::istream, class STRING = std::string, class DELIM = char>
    bool safeGetline(IS& is, STRING& t, DELIM delim = ';')
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

    template <class STRING = const string, class STRING_DELIM = string>
    STRING trim(STRING& s, STRING_DELIM& delim = " \r\n"){
        using namespace boost::algorithm;
        return trim_copy_if(s, is_any_of(delim));
    }

    template <class STRING = std::string, class DELIM = char>
    std::vector<STRING> explode(STRING const & s, DELIM delim)
    {
        std::vector<STRING> result;
        std::istringstream iss(s);

        for (STRING token; std::getline(iss, token, delim); )
        {
            result.push_back(std::move(token));
        }

        return result;
    }


}

#endif //WPP_STRING_UTILS_H
