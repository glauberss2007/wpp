
#ifndef DUMP_HPP_
# define DUMP_HPP_

/*
** Dependencies.
*/

# include <typeinfo>
# include <iostream>
# include <map>
# include <list>
# include <vector>

/*
** Map.
*/

template<typename A, typename B>
std::ostream &operator<<(std::ostream &os, std::map<A, B> const &map) {
    typename std::map<A, B>::const_iterator it;
    size_t len = 0;

    os << std::boolalpha;
    os << "{" << std::endl;
    for (it = map.begin(); it != map.end(); it++) {
        if (it != map.begin()) {
            os << "\"," << std::endl;
        }
        os << "  \"" << (it->first)
           << "\": \"" << (it->second);
    }
    os << std::endl << "}" << std::endl;
    os << std::noboolalpha;
    return os;
}

/*
** List.
*/

template<typename A>
std::ostream &operator<<(std::ostream &os, std::list<A> const &list) {
    typename std::list<A>::const_iterator pos;

    os << std::boolalpha;
    os << "[" << std::endl;
    for (pos = list.begin(); pos != list.end(); pos++) {
        if (pos != list.begin()) {
            os << "\"," << std::endl;
        }
        os << "  \"" << *pos;
    }
    os << std::endl << "]" << std::endl;
    os << std::noboolalpha;
    return os;
}

/*
** Vector.
*/

template<typename A>
std::ostream &operator<<(std::ostream &os, std::vector<A> const &vec) {
    os << std::boolalpha;
    os << "[" << std::endl;
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) {
            os << "\"," << std::endl;
        }
        os << "  \"" << vec[i];
    }
    os << std::endl << "]" << std::endl;
    os << std::noboolalpha;
    return os;
}

#endif /* !DUMP_HPP_ */