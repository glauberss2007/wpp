//
// Created by Alan de Freitas on 21/09/17.
//

#ifndef WPP_CONFIG_H
#define WPP_CONFIG_H

#include "environment.h"

void config(application &app) {
    // Debug
    // logging::default_log_level::default_level = logging::log_level::debug;

    // HTTPS
    // app.secure(string(environment::https_keys_root_path) + "server.crt", string(environment::https_keys_root_path) + "server.key");

    // Filesystem
    app.assets_root_path(environment::assets_root_path);
    app.templates_root_path(environment::templates_root_path);
    app.user_agent_parser_root_path(environment::user_agent_parser_root_path);
    // The domain name
    string web_root_path = environment::web_root_path;
    if (web_root_path.find("//localhost") != string::npos){
        try {
            namespace ip = boost::asio::ip;
            boost::asio::io_service io_service;
            ip::tcp::resolver resolver(io_service);

            std::string h = ip::host_name();
            std::cout << "Host name is " << h << '\n';
            std::for_each(resolver.resolve({h, ""}), {}, [&web_root_path,&app](const auto& re) {
                const std::regex pattern("(\\d{1,3}(\\.\\d{1,3}){3})");
                string ip = re.endpoint().address().to_string();
                if (std::regex_match(ip,pattern)){
                    web_root_path = "http"+(app.secure()?string("s"):string(""))+"://" + ip + ":8080/";
                }
            });
        } catch (std::exception& e){
            std::cerr << "Could not deal with socket. Exception: " << e.what() << std::endl;
        }
    }
    app.web_root_path(web_root_path);
    // sessions
    app.session_name("smart_id");
    // Encryption
    app.set_keys();
    // Port
    app.port(8080);
    // Use all threads (false for debugging)
    app.multithreaded();

    // How to get user information so request can be allowed or not
    app.guard_call_back([](wpp::request& req){
        json user_id = req.session_get("user_id",nullptr);
        return (user_id.is_null()) ? json(nullptr) : wpp::json::object({{"id",15},{"name","Alan"},{"role","admin"},{"permission",{"read","edit","write"}}});
    });
}

#endif //WPP_CONFIG_H
