//
// Created by Alan de Freitas on 06/10/16.
//

#ifndef WPP_WEB_H
#define WPP_WEB_H

#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "../../view/views.h"
#include <boost/iostreams/device/mapped_file.hpp>

using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

#include "wpp.h"
#include <regex>

using namespace std;
using namespace wpp;

/// Register the routes for the whole app
/// \param app reference to the application
void register_web_routes(application& app){

//    app.any("/").name("Home")
//    ([](){
//        return wpp::response(string("Oi"));
//    });

    app.any("/").name("Home")
    ([](){
        boost::iostreams::mapped_file_source file("templates/home.html");
        // set format
//        mustache::format format{"Welcome to my page: {{title}}"};
        mustache::format format(file);
        // set title
        mustache::object data{{"title", "Home"}};
        // set timestamp
        Timestamp now;
        data["dt"] = std::string(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
        return wpp::response(to_string(format(data)));
    });

//    app.any("/requests").name("Requests")
//    ([](const wpp::request& req){
//        string all_requests;
//        all_requests += "\nreq.method: \t" + to_string((int)req.method) + "\n";
//        all_requests += "req.raw_url: \t" + req.raw_url + "\n";
//        all_requests += "req.url: \t" + req.url + "\n";
//        all_requests += "req.url_params: \t" + req.url_params.to_string() + "\n";
//        all_requests += "req.headers: \n";
//        for (auto header :req.headers) {
//            all_requests += "     " + header.first + ": \t" + header.second + "\n";
//        }
//        all_requests += "req.body: \t" + req.body + "\n";
//        // all_requests += "req.service " + to_string(req.io_service) + "\n";
//        // all_requests += "req.middleware_context " + req.middleware_context + "\n";
//
//        // other functions
//        // req.add_header()
//        // req.dispatch()
//        // req.post()
//        // req.get_header_value()
//        return all_requests;
////        wpp::mustache::context ctx;
////        ctx["title"] = all_requests;
////        Timestamp now;
////        ctx["dt"] = std::string(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
////        return wpp::mustache::load("home.html").render(ctx);
//    });
//
//    app.route({method::post,method::get},"/link/{string}").name("Link")
//    ([](std::string link_id){
//        mustache::format format{"Welcome to my page: {{title}}"};
//        wpp::mustache::object data;
//        data["title"] = "Link "+link_id;
//        Timestamp now;
//        data["dt"] = std::string(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
//        return format(data);
//    });
//
//    app.any("/json").name("Json")
//    ([]{
//        wpp::json j;
//        j["project"] = "rapidjson";
//        j["stars"] = 10;
//        return j;
//    });
//
//    app.any("/beer/{int}").name("beer")
//    ([](int count){
//        if (count > 100)
//            return wpp::response(400);
//        std::ostringstream os;
//        os << count << " bottles of beer!";
//        return wpp::response(os.str());
//    });
//
//
//    // route with route parameters
//    app.any("/users/{int}").name("User profile")
//    ([](int user_id){
//        return string("Hello user "+to_string(user_id));
//    });
//
//    app.any("/add/{int}/{int}").name("Add numbers")
//    ([](const wpp::request&, wpp::response& res, int a, int b){
//        std::ostringstream os;
//        os << a+b;
//        res.write(os.str());
//        res.end();
//    });
//
//    app.post("/add_json").name("Add numbers")
//    ([](const wpp::request& req){
//        json x = json::parse(req.body);
//        if (!x)
//            return wpp::response(400);
////        int sum = stoi(x["a"].get<std::string>()) + stoi(x["b"].get<std::string>());
//        int sum = 2 + 2;
//        std::ostringstream os;
//        os << sum;
//        return wpp::response{os.str()};
//    });
//
//    // {ip}:18080/params?foo='blabla'&pew=32&count[]=a&count[]=b
//    app.post("/params").name("Add numbers")
//    ([](const wpp::request& req){
//        std::ostringstream os;
//
//        // To get a simple string from the url params
//        // To see it in action /params?foo='blabla'
//        os << "Params: " << req.url_params << "\n\n";
//        os << "The key 'foo' was " << (req.url_params.get("foo") == nullptr ? "not " : "") << "found.\n";
//
//        // To get a double from the request
//        // To see in action submit something like '/params?pew=42'
//        if(req.url_params.get("pew") != nullptr) {
//            double countD = boost::lexical_cast<double>(req.url_params.get("pew"));
//            os << "The value of 'pew' is " <<  countD << '\n';
//        }
//
//        // To get a list from the request
//        // You have to submit something like '/params?count[]=a&count[]=b' to have a list with two values (a and b)
//        auto count = req.url_params.get_list("count");
//        os << "The key 'count' contains " << count.size() << " value(s).\n";
//        for(const auto& countVal : count) {
//            os << " - " << countVal << '\n';
//        }
//        return wpp::response{os.str()};
//    });


}


#endif //WPP_WEB_H
