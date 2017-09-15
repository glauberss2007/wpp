// https://theboostcpplibraries.com/boost.program_options
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::program_options;


int main(int argc, const char *argv[]){
    std::cout << termcolor::bold << termcolor::underline << "Basic approach with Boost.ProgramOptions"
              << termcolor::reset << std::endl;
    {
        try
        {
            auto on_age = [](int age)->void
            {
                std::cout << "On age: " << age << '\n';
            };

            options_description desc{"Options"};
            desc.add_options()
                        ("help,h", "Help screen")
                        ("pi", value<float>()->default_value(3.14f), "Pi")
                        ("age", value<int>()->notifier(on_age), "Age");

            variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            if (vm.count("help"))
                std::cout << desc << '\n';
            else if (vm.count("age"))
                std::cout << "Age: " << vm["age"].as<int>() << '\n';
            else if (vm.count("pi"))
                std::cout << "Pi: " << vm["pi"].as<float>() << '\n';
        }
        catch (const error &ex)
        {
            std::cerr << ex.what() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Positional options with Boost.ProgramOptions" << termcolor::reset << std::endl;
    {
        try
        {
            auto to_cout = [](const std::vector<std::string> &v)->void
            {
                std::copy(v.begin(), v.end(),
                          std::ostream_iterator<std::string>{std::cout, "\n"});
            };

            options_description desc{"Options"};
            desc.add_options()
                        ("help,h", "Help screen")
                        ("phone", value<std::vector<std::string>>()->
                                                                           multitoken()->zero_tokens()->composing(), "Phone");

            positional_options_description pos_desc;
            pos_desc.add("phone", -1);

            command_line_parser parser{argc, argv};
            parser.options(desc).positional(pos_desc).allow_unregistered();
            parsed_options parsed_options = parser.run();

            variables_map vm;
            store(parsed_options, vm);
            notify(vm);

            if (vm.count("help"))
                std::cout << desc << '\n';
            else if (vm.count("phone"))
                to_cout(vm["phone"].as<std::vector<std::string>>());
        }
        catch (const error &ex)
        {
            std::cerr << ex.what() << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Loading options from a configuration file" << termcolor::reset << std::endl;
    {
        try
        {
            options_description generalOptions{"General"};
            generalOptions.add_options()
                                  ("help,h", "Help screen")
                                  ("config", value<std::string>(), "Config file");

            options_description fileOptions{"File"};
            fileOptions.add_options()
                               ("age", value<int>(), "Age");

            variables_map vm;
            store(parse_command_line(argc, argv, generalOptions), vm);
            if (vm.count("config"))
            {
                std::ifstream ifs{vm["config"].as<std::string>().c_str()};
                if (ifs)
                    store(parse_config_file(ifs, fileOptions), vm);
            }
            notify(vm);

            if (vm.count("help"))
                std::cout << generalOptions << '\n';
            else if (vm.count("age"))
                std::cout << "Your age is: " << vm["age"].as<int>() << '\n';
        }
        catch (const error &ex)
        {
            std::cerr << ex.what() << '\n';
        }
    }
}
