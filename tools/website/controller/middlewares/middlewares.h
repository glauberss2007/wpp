//
// Created by Alan de Freitas on 21/09/17.
//

#ifndef WPP_MIDDLEWARES_H
#define WPP_MIDDLEWARES_H
#include <iterator>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <w++>

void register_middlewares(wpp::application &app) {
    using namespace std;
    using namespace wpp;

    ///////////////////////////////////////////////////////////////
    //                  MIDDLEWARE GROUPS                        //
    ///////////////////////////////////////////////////////////////

     app.middleware_group("web",{"throttle:60","add_queued_cookies_to_response","encrypt_cookies","start_session","share_errors_from_session","verify_csrf_token","locale"});
     app.middleware_group("api",{"throttle:60"});


    ///////////////////////////////////////////////////////////////
    //                    WEB MIDDLEWARE GROUP                   //
    ///////////////////////////////////////////////////////////////

    app.middleware("throttle", [&app](wpp::response &res, wpp::request &req, std::string parameter, wpp::resource_function& next) {
        int max_attempts = parameter.empty() ? 60 : stoi(parameter);
        int decay_minutes = 1;
        // make a unique string based on the route and user
        vector<string> route_strings;
        if (req.current_route){
            for (method& m: req.current_route->_methods){
                route_strings.push_back(method_string(m));
            }
            if (!req.current_route->_uri.empty()){
                route_strings.push_back(req.current_route->_uri);
            }
            if (!req.current_route->_name.empty()){
                route_strings.push_back(req.current_route->_name);
            }
        }
        route_strings.push_back(req.remote_endpoint_address);
        // join and digest it
        string fingerprint = app.digest(boost::algorithm::join(route_strings, "|"));

        bool too_many_attempts = false;
        if (app.get_cache().has(fingerprint + ":lockout")) {
            too_many_attempts = true;
        }
        int attempts = 0;
        if (!too_many_attempts){
            attempts = app.get_cache().get(fingerprint, 0);
            if (attempts >= max_attempts){
                app.get_cache().add(fingerprint+":lockout", std::time(nullptr) + (decay_minutes * 60), std::chrono::minutes(decay_minutes));
                app.get_cache().forget(fingerprint);
                too_many_attempts = true;
            }
        }
        int available_in = 0;
        if (too_many_attempts) {
            app.error(status_code::client_error_too_many_requests,res,req);
            available_in = (app.get_cache().get(fingerprint+":lockout",0)).get<long>() - std::time(nullptr);
            // add headers
            res.add_header("X-RateLimit-Limit",to_string(max_attempts));
            res.add_header("X-RateLimit-Remaining",to_string(max_attempts-attempts));
            if (available_in > 0){
                res.add_header("Retry-After",to_string(available_in));
                res.add_header("X-RateLimit-Reset",to_string(std::time(nullptr) + available_in));
            }
            return;
        }

        // hit
        app.get_cache().add(fingerprint, 0, std::chrono::minutes(decay_minutes));
        app.get_cache().increment(fingerprint);

        next(res,req);

        res.add_header("X-RateLimit-Limit",to_string(max_attempts));
        res.add_header("X-RateLimit-Remaining",to_string(max_attempts-attempts));
    });

    app.middleware("encrypt_cookies", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        unordered_set<string> disabled_encryption;
        bool success;
        for (auto &&cookie :req.cookie_jar) {
            if (disabled_encryption.count(cookie.first)){
                continue;
            }
            std::cout << "Cookie " << cookie.first << ":" << cookie.second;
            cookie.second = app.decrypt(cookie.second,success);
            if (success){
                std::cout << " decrypted to " << cookie.second << endl;
            } else {
                std::cout << " couldn't be decrypted" << endl;
                res.cookie(cookie.first,"",-1);
            }
        }

        next(res,req);

        for (auto &&cookie :res.cookie_jar) {
            if (disabled_encryption.count(cookie.first)){
                continue;
            }
            std::cout << "Cookie " << cookie.first << ":" << cookie.second << " encrypted to ";
            get<0>(cookie.second) = app.encrypt(get<0>(cookie.second));
            std::cout << get<0>(cookie.second) << endl;
        }
    });

    app.middleware("add_queued_cookies_to_response", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        next(res,req);
        std::cout << "Writing " << res.cookie_jar.size() << " queued cookies (";
        int printed = 0;
        for (auto i = res.cookie_jar.begin(); i != res.cookie_jar.end(); ++i) {
            std::cout << i->first;
            if (printed != res.cookie_jar.size()-1){
                std::cout << ",";
                printed++;
            }
        }
        std::cout << ")" << endl;
        res.write_cookie_headers();
    });

    app.middleware("start_session", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        const int session_minutes = 60;

        string session_id = req.get_cookie(app.session_name());
        const bool we_found_a_decrypted_session = !session_id.empty();
        if (we_found_a_decrypted_session) {
            const bool the_session_is_in_cache = app.get_cache().has("session_" + session_id);
            if (the_session_is_in_cache) {
                json session = app.get_cache().get("session_" + session_id);
                const bool client_is_the_same_as_last_one = session["ip_address"].get<string>() == req.remote_endpoint_address &&
                                                            session["user_agent"].get<string>() == req.user_agent_header();
                if (client_is_the_same_as_last_one) {
                    session["last_activity"] = to_string(std::time(nullptr));
                    req.session_data = std::move(session);
                }
            }
        }
        if (req.session_data.empty()) {
            req.session_regenerate(res);
            std::cout << "Generated a new session " << req.session_data["id"] << endl;
        }

        next(res,req);

        // Update session data for next request
        if (!req.session_data.empty()){
            // flash data to next request
            req.session_data["flashed_data_from_last_request"] = std::move(req.session_data["flashed_data_from_this_request"]);
            // set previous url
            const string full_url = req.full_url();
            if (req.method_requested == method::get && !full_url.empty() && !req.is_ajax()) {
                req.session_put("_previous.url",full_url);
            }
            // find id
            const string serialized_session_id = req.session_data["id"];
            // send/add cookie
            std::cout << "Adding cookie session " << app.session_name() << " = " << serialized_session_id << endl;
            res.cookie(app.session_name(),serialized_session_id,session_minutes);
            // update cache
            app.get_cache().put("session_"+serialized_session_id,req.session_data,app.max_session_inactive_time());
        }
    });

    app.middleware("share_errors_from_session", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        // If the current session has an "errors"
        json::iterator error_iter = req.session_data.find("_errors");
        if (error_iter != req.session_data.end()){
            // share its value with all view instances so the views can easily access errors
            req.view_bag["errors"] = *error_iter;
        } else {
            // An empty bag is set when there aren't errors.
            req.view_bag["errors"] = json::array();
        }
        next(res,req);
    });

    app.middleware("verify_csrf_token", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        const bool is_reading = req.method_requested == method::get || req.method_requested == method::head ||
                                req.method_requested == method::options;
        string token = req.input("_csrfmiddlewaretoken");
        if (token.empty()) {
            token = req.input("X-CSRF-TOKEN");
        }
        if (token.empty()) {
            string header = req.header("X-XSRF-TOKEN");
            token = app.decrypt(header);
        }
        string session_token;
        const bool it_makes_sense_to_look_for_a_session_token = !token.empty();
        if (!token.empty()) {
            json::iterator iter = req.session_data.find("_csrfmiddlewaretoken");
            const bool there_is_a_session_token = iter != req.session_data.end() && iter->is_string();
            if (there_is_a_session_token) {
                session_token = iter->get<std::string>();
            }
        }
        const bool tokens_match = !token.empty() && token == session_token;
        if (is_reading || tokens_match) {
            // run the route
            next(res, req);
            // add cookie to response
            if (!res._csrfmiddlewaretoken.empty()) {
                req.session_data["_csrfmiddlewaretoken"] = res._csrfmiddlewaretoken;
            } else {
                req.session_data.erase("_csrfmiddlewaretoken");
            }
        } else {
            app.error(status_code::server_error_internal_server_error, res, req);
        }
    });

    app.middleware("locale", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        // if session doesn't know the locale
        if (!req.session_has("locale")){
            // look in the header
            std::unordered_multimap<std::string, std::string>::iterator iter = req.headers.find("Accept-Language");
            if (iter != req.headers.end()){
                const string language_str = iter->second;
                vector<string> languages;
                boost::algorithm::split(languages, language_str, is_any_of(","));
                vector<pair<string,double>> languages_with_weights;
                for (string &language_code: languages) {
                    size_t sep = language_code.find(";");
                    if (sep != string::npos){
                        string weight = language_code.substr(sep+1);
                        if (regex_match(weight,std::regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"))){
                            language_code = language_code.substr(0,sep);
                            languages_with_weights.emplace_back(make_pair(language_code,std::stod(weight)));
                        } else {
                            language_code = language_code.substr(0,sep);
                            languages_with_weights.emplace_back(make_pair(language_code,1.0));
                        }
                    } else {
                        languages_with_weights.emplace_back(make_pair(language_code,1.0));
                    }
                }
                std::sort(languages_with_weights.begin(),languages_with_weights.end(),[](pair<string,double> &a, pair<string,double> &b){return a.second > b.second;});
                if (!languages_with_weights.empty()){
                    req.session_put("locale",languages_with_weights[0].first);
                }
            }
        }

        // A third option is to look GEOIP data
        // location C++: https://github.com/alandtsang/geolite2cpp
        // location C++: https://www.ccoderun.ca/GeoLite2++/api/
        // location C: https://github.com/maxmind/libmaxminddb

        next(res,req);

    });

    ///////////////////////////////////////////////////////////////
    //                   APPLICATION MIDDLEWARES                 //
    ///////////////////////////////////////////////////////////////

    app.middleware("auth", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        guard auth = (req.auth) ? *req.auth : guard(app.guard_call_back(),req);
        if (auth.guest()) {
            if (req.is_ajax()) {
                app.error(status_code::client_error_unauthorized,res,req);
            } else {
                res = response::redirect(app.url_for("login"));
            }
        } else {
            next(res,req);
        }
    });

    app.middleware("guest", [&app](wpp::response &res, wpp::request &req, wpp::resource_function& next) {
        guard auth = (req.auth) ? *req.auth : guard(app.guard_call_back(),req);
        if (!auth.guest()) {
            res = response::redirect(app.url_for("dashboard"));
        } else {
            next(res,req);
        }
    });

    app.middleware("role", [&app](wpp::response &res, wpp::request &req, std::string parameter, wpp::resource_function& next) {
        guard auth = (req.auth) ? *req.auth : guard(app.guard_call_back(),req);
        vector<string> roles;
        boost::algorithm::split(roles,parameter, is_any_of("|"));
        if (auth.guest() || !auth.has_role(roles)){
            app.error(status_code::client_error_forbidden,res,req);
        } else {
            next(res,req);
        }
    });

    app.middleware("permission", [&app](wpp::response &res, wpp::request &req, std::string parameter, wpp::resource_function& next) {
        guard auth = (req.auth) ? *req.auth : guard(app.guard_call_back(),req);
        vector<string> permissions;
        boost::algorithm::split(permissions,parameter, is_any_of("|"));
        if (auth.guest() || !auth.has_permission(permissions)){
            app.error(status_code::client_error_forbidden,res,req);
        } else {
            next(res,req);
        }
    });

    app.middleware("ability", [&app](wpp::response &res, wpp::request &req, std::string parameter, wpp::resource_function& next) {
        guard auth = (req.auth) ? *req.auth : guard(app.guard_call_back(),req);
        vector<string> roles_and_permissions;
        boost::algorithm::split(roles_and_permissions, parameter, is_any_of(","));
        vector<string> roles;
        if (!roles_and_permissions.empty()){
            boost::algorithm::split(roles, roles_and_permissions[0], is_any_of("|"));
        }
        vector<string> permissions;
        if (roles_and_permissions.size() > 1){
            boost::algorithm::split(permissions, roles_and_permissions[1], is_any_of("|"));
        }
        bool validate_all = true;
        if (roles_and_permissions.size() > 2){
            if (roles_and_permissions[2] == "false"  || roles_and_permissions[2] == "FALSE" || roles_and_permissions[2] == "False"){
                validate_all = false;
            }
        }
        const bool has_ability = (validate_all && (auth.has_role(roles) && auth.has_permission(permissions)))
                                || (!validate_all && (auth.has_role(roles) || auth.has_permission(permissions)));
        if (auth.guest() || !has_ability){
            app.error(status_code::client_error_forbidden,res,req);
        } else {
            next(res,req);
        }
    });

    // replace localhost on web_root for IP address

}


#endif //WPP_MIDDLEWARES_H
