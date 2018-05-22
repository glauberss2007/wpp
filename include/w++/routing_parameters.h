//
// Created by Alan de Freitas on 19/09/17.
//

#ifndef WPP_ROUTING_PARAMETERS_H
#define WPP_ROUTING_PARAMETERS_H

#include "enums.h"
#include "utils/logging.h"
#include <string>
#include <vector>
#include <boost/optional.hpp>

namespace wpp{
    using namespace std;
    using namespace utils;
    using boost::optional;

    struct routing_params {
        std::vector<std::string> parameter_name;
        std::vector<optional<std::string>> parameter_value;
        std::vector<ParamType> parameter_trait;

        string get(string parameter, string def = ""){
            auto it = find(parameter_name.begin(),parameter_name.end(),parameter);
            if (it == parameter_name.end()){
                return def;
            } else {
                return *parameter_value[it - parameter_name.begin()];
            }
        }

        optional<string> get_optional(string parameter){
            auto it = find(parameter_name.begin(),parameter_name.end(),parameter);
            if (it == parameter_name.end()){
                return optional<string>{};
            } else {
                return parameter_value[it - parameter_name.begin()];
            }
        }

        string get(unsigned pos, string def = ""){
            if (pos > parameter_value.size()){
                return def;
            } else {
                return *parameter_value[pos];
            }
        }

        optional<string> get_optional(unsigned pos){
            if (pos > parameter_value.size()){
                return optional<string>{};
            } else {
                return parameter_value[pos];
            }
        }

        ParamType get_trait(string parameter, string def = ""){
            auto it = find(parameter_name.begin(),parameter_name.end(),parameter);
            if (it == parameter_name.end()){
                return ParamType::STRING;
            } else {
                return parameter_trait[it - parameter_name.begin()];
            }
        }

        void debug_print() const {
            log::info << "routing_params" << std::endl;
            for (int i = 0; i < parameter_name.size(); ++i) {
                if (parameter_value[i]){
                    log::info << parameter_name[i] << ": " << *parameter_value[i] <<  ", ";
                } else {
                    log::info << parameter_name[i] << ": (empty), ";
                }
            }
            log::info << std::endl;
        }

        template<typename T>
        T get(unsigned) const;
    };
}


#endif //WPP_ROUTING_PARAMETERS_H
