//
// Created by Alan de Freitas on 06/10/16.
//

#ifndef WPP_WEB_H
#define WPP_WEB_H

#include <algorithm>
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

void register_web_routes(application &app) {

    app.any("/", [](wpp::response &res, wpp::request &req) {
        //boost::iostreams::mapped_file_source file("templates/home.html");
        res.body = "Hello world";
        // set format
        //        mustache::format format{"Welcome to my page: {{title}}"};
        //        mustache::format format(file);
        //        // set title
        //        mustache::object data{{"title", "Home"}};
        //        // set timestamp
        //        using namespace boost::posix_time;
        //        boost::gregorian::date d(2009, 1, 7);
        //        // create your formatting
        //        boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y%m%d_%H%M%S");
        //        // set your formatting
        //        ostringstream is;
        //        is.imbue(std::locale(is.getloc(), df));
        //        is << d << endl;

        //return is.str();
    }).name("home");

    app.route({method::get, method::post}, "{string:nome}",
              [](wpp::response &res, wpp::request &req) {
                  std::string content = req.body;
                  //auto content_ = request->content_.string();
                  res.body = "Bem vindo, " + req.query_parameters.get(0) + "!";
              }).name("Print name").where("nome","[A-Za-z]+");

    app.post("json", [](wpp::response &res, wpp::request &req) {
        try {

            auto name = "Json String";

            res.body = name;
        }
        catch (const std::exception &e) {
            res.code = status_code::client_error_bad_request;
            res.body = e.what();
        }
    });

    app.get("/info", [](wpp::response &res, wpp::request &req) {
        stringstream stream;
        stream << "<h1>request from " << req.remote_endpoint_address << " (" << req.remote_endpoint_port
               << ")</h1>";
        stream << method_string(req.method_requested) << " " << req.url << " HTTP/" << req.http_version << "<br>";
        for (auto &header : req.headers) {
            stream << header.first << ": " << header.second << "<br>";
        }
        res.body = stream.str();
    });

    app.get("/match/{int:number?}", [](wpp::response &res, wpp::request &req) {
        string number = req.query_parameters.get(0);
        res.body = number;
    });

    app.get("work", [](wpp::response &res, wpp::request &req) {
        thread work_thread([&res] {
            this_thread::sleep_for(chrono::seconds(5));
            res.body = "Work done";
        });
        work_thread.join();
    });

    app.any("/helloworld", [](wpp::response &res, wpp::request &req) {
        return wpp::response(string("Oi"));
    }).name("Hi");



    app.any("/requests/tellme", [](wpp::response &res, wpp::request &req) {
        string all_requests;
        all_requests += "\nreq.method: \t" + wpp::method_string(req.method_requested) + "\n";
        all_requests += "req.raw_url: \t" + req.raw_url + "\n";
        all_requests += "req.url: \t" + req.url + "\n";
        all_requests += "req.url_params: \t\n";
        for (auto &&item : req.url_params) {
            all_requests += "                \t" + item.first + "=" + item.second + "\n";
        }
        all_requests += "req.headers: \n";
        for (auto header :req.headers) {
            all_requests += "     " + header.first + ": \t" + header.second + "\n";
        }
        all_requests += "req.body: \t" + req.body + "\n";
        return all_requests;
    }).name("requests");

    app.route({method::post, method::get}, "/link/{string:slug}", [](wpp::response &res, wpp::request &req) {
        string link_id = req.query_parameters.get(0);
        mustache::format format{"Welcome to my page: {{title}}"};
        wpp::mustache::object data;
        data["title"] = "Link " + link_id;
        using namespace boost::posix_time;
        boost::gregorian::date d(2009, 1, 7);

        // create your formatting
        boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y%m%d_%H%M%S");
        // set your formatting
        ostringstream is;
        is.imbue(std::locale(is.getloc(), df));
        is << d << endl;

        data["dt"] = is.str();
        return format(data);
    }).name("Link");

    app.any("/json", [](wpp::response &res, wpp::request &req) {
        wpp::json j;
        j["project"] = "rapidjson";
        j["stars"] = 10;
        return j;
    }).name("Json");

    app.any("/beer/{int:number}", [](wpp::response &res, wpp::request &req) {
        int count = stoi(req.query_parameters.get(0));
        if (count > 100)
            return wpp::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return wpp::response(os.str());
    }).name("beer");

    // route with route parameters
    app.any("/users/{int:id}", [](wpp::response &res, wpp::request &req) {
        int user_id = stoi(req.query_parameters.get(0));
        return string("Hello user " + to_string(user_id));
    }).name("User profile");

    app.any("/add/{int:id}/{int:id2}", [](wpp::response &res, wpp::request &req) {
        int a = stoi(req.query_parameters.get(0));
        int b = stoi(req.query_parameters.get(1));
        std::ostringstream os;
        os << a + b;
        res.write(os.str());
        res.end();
    }).name("Add numbers").where({{"id","[0-9]+"},{"id2","[0-9]+"}});

    app.redirect("redirecting","Add numbers");

    app.post("/add_json", [](wpp::response &res, wpp::request &req) {
        json x = json::parse(req.body);
        if (!x)
            return wpp::response(400);
        int sum = stoi(x["a"].get<std::string>()) + stoi(x["b"].get<std::string>());
//        int sum = 2 + 2;
        std::ostringstream os;
        os << sum;
        return wpp::response{os.str()};
    }).name("Add numbers");

    // {ip}:18080/params?foo='blabla'&pew=32&count[]=a&count[]=b
    app.post("/params", [](wpp::response &res, wpp::request &req) {
        std::ostringstream os;

        // To get a simple string from the url params
        // To see it in action /params?foo='blabla'
        os << "Params: " << req.url_params << "\n\n";
        os << "The key 'foo' was " << (req.url_params.find("foo") == req.url_params.end() ? "not " : "") << "found.\n";

        // To get a double from the request
        // To see in action submit something like '/params?pew=42'
        if (req.url_params.find("pew") != req.url_params.end()) {
            double countD = boost::lexical_cast<double>(req.url_params.find("pew")->second);
            os << "The value of 'pew' is " << countD << '\n';
        }

        // To get a list from the request
        // You have to submit something like '/params?count[]=a&count[]=b' to have a list with two values (a and b)
        auto count = req.url_params.equal_range("count[]");
        os << "The key 'count' contains " << req.url_params.count("count[]") << " value(s).\n";
        for (auto iter = count.first; iter != count.second; ++iter) {
            os << " - " << iter->second << '\n';
        }
        return wpp::response{os.str()};
    }).name("Add numbers");

}

#endif //WPP_WEB_H
