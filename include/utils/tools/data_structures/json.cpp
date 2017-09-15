//
// Created by Alan de Freitas on 18/06/17.
//

#ifndef WPP_EXTERNALLIBS_H
#define WPP_EXTERNALLIBS_H

#include <iostream>
#include "termcolor/termcolor.hpp"
#include <vector>
#include <map>
#include <unordered_map>
#include <stdio.h>

#include <json.hpp>

int main() {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "JSON Modern C++"
              << termcolor::reset << std::endl;

    using json = nlohmann::json;
    using namespace std;

    {
        // create an empty structure (null)
        json j;

        std::cout << termcolor::bold << termcolor::underline << "JSON from initializer list" << termcolor::reset << std::endl;

        j = {
                {"pi",      3.141},
                {"happy",   true},
                {"name",    "Niels"},
                {"nothing", nullptr},
                {"answer",  {
                                    {"everything", 42}
                            }},
                {"list",    {       1, 0, 2}},
                {"object",  {
                                    {"currency",   "USD"},
                                       {"value", 42.99}
                            }}
        };

        j["object"] = {
                {"currency", "USD"},
                {"value",    42.99},
                {"country",  "USA"}
        };

        cout << "j: " << j << endl;

        std::cout << termcolor::bold << termcolor::underline << "JSON from string" << termcolor::reset << std::endl;

        j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

        cout << "j: " << j << endl;

        j = R"(
      {
        "happy": true,
        "pi": 3.141
      }
    )"_json;

        cout << "j: " << j << endl;

        j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

        cout << "j: " << j << endl;

        std::cout << termcolor::bold << termcolor::underline << "JSON to string" << termcolor::reset << std::endl;

        std::string s = j.dump();    // {\"happy\":true,\"pi\":3.141}

        cout << "s: " << s << endl;

        std::cout << termcolor::bold << termcolor::underline << "JSON to prettified string" << termcolor::reset << std::endl;

        std::cout << "j.dump(4): " << j.dump(4) << std::endl;
    }

}

#endif //WPP_EXTERNALLIBS_H
