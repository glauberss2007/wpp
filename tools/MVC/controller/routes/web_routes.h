//
// Created by Alan de Freitas on 06/10/16.
//

#ifndef WPP_WEB_H
#define WPP_WEB_H

#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "../../view/views.h"

using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

#include "wpp.h"
#include <regex>

using namespace std;
using namespace wpp;

void register_web_routes(wpp_app& app){

    app.any("/").name("Home")
    ([]{
        crow::mustache::context ctx;
        ctx["title"] = "Home";
        Timestamp now;
        ctx["dt"] = std::string(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
        return crow::mustache::load("home.html").render(ctx);
    });

    app.any("/link/<int>").name("Link")
    ([](int link_id){
        crow::mustache::context ctx;
        ctx["title"] = "Link "+to_string(link_id);
        Timestamp now;
        ctx["dt"] = std::string(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
        return crow::mustache::load("home.html").render(ctx);
    });

    app.any("/json").name("Json")
    ([]{
        wpp::json x;
        x["message"] = "Hello, World!";
        return x;
    });

    app.any("/beer/<int>").name("beer")
    ([](int count){
        if (count > 100)
            return wpp::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return wpp::response(os.str());
    });


    // route with route parameters
    app.any("/users/<int>").name("User profile")
    ([](int user_id){
        Timestamp now;
        std::string dt(DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT));
        return crow::mustache::load("templates/home.html").render();
    });

    app.any("/add/<int>/<int>").name("Add numbers")
    ([](const wpp::request&, crow::response& res, int a, int b){
        std::ostringstream os;
        os << a+b;
        res.write(os.str());
        res.end();
    });

    app.post("/add_json").name("Add numbers")
    ([](const wpp::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return wpp::response(400);
        int sum = x["a"].i()+x["b"].i();
        std::ostringstream os;
        os << sum;
        return wpp::response{os.str()};
    });

    // {ip}:18080/params?foo='blabla'&pew=32&count[]=a&count[]=b
    app.post("/params").name("Add numbers")
    ([](const wpp::request& req){
        std::ostringstream os;

        // To get a simple string from the url params
        // To see it in action /params?foo='blabla'
        os << "Params: " << req.url_params << "\n\n";
        os << "The key 'foo' was " << (req.url_params.get("foo") == nullptr ? "not " : "") << "found.\n";

        // To get a double from the request
        // To see in action submit something like '/params?pew=42'
        if(req.url_params.get("pew") != nullptr) {
            double countD = boost::lexical_cast<double>(req.url_params.get("pew"));
            os << "The value of 'pew' is " <<  countD << '\n';
        }

        // To get a list from the request
        // You have to submit something like '/params?count[]=a&count[]=b' to have a list with two values (a and b)
        auto count = req.url_params.get_list("count");
        os << "The key 'count' contains " << count.size() << " value(s).\n";
        for(const auto& countVal : count) {
            os << " - " << countVal << '\n';
        }
        return wpp::response{os.str()};
    });


}


#endif //WPP_WEB_H
