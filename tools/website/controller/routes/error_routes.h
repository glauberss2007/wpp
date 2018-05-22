//
// Created by Alan de Freitas on 06/10/16.
//

#ifndef WPP_REGISTER_ERROR_ROUTES_H
#define WPP_REGISTER_ERROR_ROUTES_H

#include <algorithm>
#include <functional>
#include <boost/filesystem.hpp>
#include <boost/iostreams/code_converter.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <fstream>
#include <vector>
#include <string>
// #include "crypto.hpp"
#include <w++>

using namespace std;
using namespace wpp;

void register_error_routes(application &app) {

    app.error(wpp::status_code::client_error_not_found, [&app](wpp::response &res, wpp::request &req) {
        wpp::json context;
        context["title"] = "Error 404";
        context["subtitle"] = "Smart LAO";
        context["window_title"] = "Error 404 | Smart LAO";
        context["text_title"] = "404, Page not found";
        context["text_subtitle"] = "The Page you are looking for doesn't exist or an other error occurred.";
        context["date"] = "2017";
        context["year"] = "2017";
        response::view v = app.view("home/error.html", context);
        res = v;
    });

    app.error(wpp::status_code::client_error_forbidden, [&app](wpp::response &res, wpp::request &req) {
        wpp::json context;
        context["title"] = "Error 403";
        context["subtitle"] = "Smart LAO";
        context["window_title"] = "Error 403 | Smart LAO";
        context["text_title"] = "403, Forbidden";
        context["text_subtitle"] = "You don't have permission to access this resource.";
        context["date"] = "2017";
        context["year"] = "2017";
        response::view v = app.view("home/error.html", context);
        res = v;
    });

    app.error(wpp::status_code::server_error_internal_server_error, [&app](wpp::response &res, wpp::request &req) {
        wpp::json context;
        context["title"] = "Error 500";
        context["subtitle"] = "Smart LAO";
        context["window_title"] = "Error 500 | Smart LAO";
        context["text_title"] = "500, Token mismatch";
        context["text_subtitle"] = "It looks like you can't submit a form. Please go back, reload the page and try again.";
        context["date"] = "2017";
        context["year"] = "2017";
        response::view v = app.view("home/error.html", context);
        res = v;
    });

    app.default_resource({method::get},[&app](wpp::response &res, wpp::request &req){
        // Try to find file resource if we couldn't find the route
        try {
            auto __assets_root_path = boost::filesystem::canonical(
                    app.assets_root_path());
            auto path = boost::filesystem::canonical(__assets_root_path / req.path());
            // Check if path is within __assets_root_path
            if (distance(__assets_root_path.begin(), __assets_root_path.end()) >
                distance(path.begin(), path.end()) ||
                !equal(__assets_root_path.begin(), __assets_root_path.end(), path.begin())) {
                throw invalid_argument("path must be within root path");
            }
            if (boost::filesystem::is_directory(path)) {
                path /= "index.html";
            }

            SimpleWeb::CaseInsensitiveMultimap header;

            //    Uncomment the following line to enable Cache-Control
            //header.emplace("Cache-Control", "max-age=86400");

            #ifdef HAVE_OPENSSL
            //    Uncomment the following lines to enable ETag
                                //    {
                                //      ifstream ifs(path.string(), ifstream::in | ios::binary);
                                //      if(ifs) {
                                //        auto hash = SimpleWeb::Crypto::to_hex_string(SimpleWeb::Crypto::md5(ifs));
                                //        header.emplace("ETag", "\"" + hash + "\"");
                                //        auto it = request->header.find("If-None-Match");
                                //        if(it != request->header.end()) {
                                //          if(!it->second.empty() && it->second.compare(1, hash.size(), hash) == 0) {
                                //            response->write(SimpleWeb::StatusCode::redirection_not_modified, header);
                                //            return;
                                //          }
                                //        }
                                //      }
                                //      else
                                //        throw invalid_argument("could not read file");
                                //    }
            #endif
            // open file to stream
            res._file_response = make_shared<ifstream>();
            res._file_response->open(path.string(), ifstream::in | ios::binary | ios::ate);
        } catch (const std::exception &e) {
            app.error(wpp::status_code::client_error_not_found, res, req);
        }
    });


}

#endif //WPP_REGISTER_ERROR_ROUTES_H
