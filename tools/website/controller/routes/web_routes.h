//
// Created by Alan de Freitas on 06/10/16.
//

#ifndef WPP_WEB_H
#define WPP_WEB_H

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

void register_web_routes(application &app) {

    app.group({"web"},[](application &app)
    {
        app.get("/", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("features", [&app](wpp::request &req) {
            wpp::json context;
            context["subtitle"] = "Features";
            context["active_title"] = "Features";
            context["banner"]["title"] = "Features";
            context["banner"]["subtitle"] = "All kinds all tools to boost your business";
            context["banner"]["breadcrumbs"] = {
                    {{"title", "Home"},     {"link", app.url_for("home")}},
                    {{"title", "Features"}, {"link", app.url_for("features")}},
            };
            return app.view("home/features.html", context);
        }).name("features");

        app.get("pricing", [&app]() {
            wpp::json context;
            context["active_title"] = "Pricing";
            context["subtitle"] = "Pricing";
            context["banner"]["title"] = "Pricing";
            context["banner"]["subtitle"] = "Software that scales with your business";
            context["banner"]["breadcrumbs"] = {
                    {{"title", "Home"},    {"link", app.url_for("home")}},
                    {{"title", "Pricing"}, {"link", app.url_for("pricing")}},
            };
            return app.view("home/pricing.html", context);
        }).name("pricing");

        app.get("login", [&app]() {
            wpp::json context;
            context["active_title"] = "Login";
            context["subtitle"] = "Login";
            context["banner"]["title"] = "Login";
            context["banner"]["subtitle"] = "Welcome to Smart LAO";
            context["banner"]["breadcrumbs"] = {
                    {{"title", "Home"},  {"link", app.url_for("home")}},
                    {{"title", "Login"}, {"link", app.url_for("login")}},
            };
            return app.view("home/login.html", context);
        }).name("login");

        app.post("login", [&app](wpp::request &req) {
            wpp::json context;
            context["active_title"] = "Login";
            context["subtitle"] = "Login";
            context["banner"]["title"] = "Login - Try again";
            context["banner"]["subtitle"] = req.body;
            context["banner"]["breadcrumbs"] = {
                    {{"title", "Home"},  {"link", app.url_for("home")}},
                    {{"title", "Login"}, {"link", app.url_for("login")}},
            };
            return app.view("home/login.html", context);
        }).name("login");

        app.get("signup", [&app]() {
            return response::redirect(app.url_for("login"));
            //wpp::json context;
            //context["menu"][0]["active"] = false;
            //context["menu"][1]["active"] = false;
            //context["menu"][2]["active"] = false;
            //context["menu"][3]["active"] = true;
            //context["subtitle"] = "Sign-up";
            //context["banner"]["title"] = "Sign-up";
            //context["banner"]["subtitle"] = "Welcome to Smart LAO";
            //context["banner"]["breadcrumbs"] = {
            //        {{"title","Home"},{"link",app.url_for("home")}},
            //        {{"title","Sign-up"},{"link",app.url_for("signup")}},
            //};
            //return app.view("home/signup.html", context);
        }).name("signup");

        app.any("/info", [&app](wpp::response &res, wpp::request &req) {
            wpp::json context;
            context["active_title"] = "Info";

            context["table_data"] = {
                    {{"name", "method_requested"},                {"value", (int) req.method_requested}},
                    {{"name", "path()"},                          {"value", req.path()}},
                    {{"name", "url()"},                           {"value", req.url()}},
                    {{"name", "full_url()"},                      {"value", req.full_url()}},
                    {{"name", "route_name()"},                    {"value", req.route_name()}},
                    {{"name", "is(\"info\")"},                    {"value", req.is("info") ? "true" : "false"}},
                    {{"name", "is_method(method::get)"},          {"value", req.is_method(method::get) ? "true"
                                                                                                       : "false"}},
                    {{"name", "is_method(\"get\")"},              {"value", req.is_method("get") ? "true" : "false"}},
                    {{"name", "all().dump()"},                    {"value", req.all().dump()}},
                    {{"name", "has(\"queryparam\").dump()"},      {"value", req.has("queryparam") ? "true" : "false"}},
                    {{"name", "input(\"queryparam\").dump()"},    {"value", req.input("queryparam").dump()}},
                    {{"name", "only({\"queryparam\"}).dump()"},   {"value", req.only({"queryparam"}).dump()}},
                    {{"name", "except({\"queryparam\"}).dump()"}, {"value", req.except({"queryparam"}).dump()}},
                    {{"name", "query_string"},                    {"value", req.query_string}},
                    {{"name", "body"},                            {"value", req.body}},
                    {{"name", "http_version"},                    {"value", req.http_version}},
                    {{"name", "method_string"},                   {"value", req.method_string}},
                    {{"name", "remote_endpoint_address"},         {"value", req.remote_endpoint_address}},
                    {{"name", "remote_endpoint_port"},            {"value", req.remote_endpoint_port}},
            };

            wpp::json request_parameters;
            for (auto &&item : req.request_parameters) {
                request_parameters.push_back({{"name",  item.first},
                                              {"value", item.second}});
            }
            if (!request_parameters.empty()) {
                context["request_parameters"] = request_parameters;
            }

            wpp::json headers;
            for (auto header :req.headers) {
                headers.push_back({{"name",  header.first},
                                   {"value", header.second}});
            }
            context["headers"] = headers;

            res.cookie("happyness", "john");

            wpp::json cookies;
            for (auto cookie : req.cookie_jar) {
                cookies.push_back({{"name",  cookie.first},
                                   {"value", cookie.second}});
            }
            context["cookies"] = cookies;

            req.session_keep("flashed_crazy");
            req.session_flash("flashed_crazy", "value").session_flash("flashed_crazy2", "value2");

            wpp::json session_data;
            for (json::iterator it = req.session_data.begin(); it != req.session_data.end(); ++it) {
                string first = it.key();
                string second;
                if (it.value().is_string()) {
                    second = it.value();
                } else {
                    second = it.value().dump();
                }
                session_data.push_back({{"name",  first},
                                        {"value", second}});
            }
            context["session_data"] = session_data;

            request::user_agent uagent = req.user_agent_object();
            wpp::json user_agent_data;
            user_agent_data.push_back({{"name",  "toFullString()"},
                                       {"value", uagent.toFullString()}});
            user_agent_data.push_back({{"name",  "request is_mobile()"},
                                       {"value", req.is_mobile() ? "true" : "false"}});
            user_agent_data.push_back({{"name",  "isSpider()"},
                                       {"value", (uagent.isSpider()) ? "true" : "false"}});

            user_agent_data.push_back({{"hr", true}});

            user_agent_data.push_back({{"name",  "device family"},
                                       {"value", uagent.device.family}});
            user_agent_data.push_back({{"name",  "device model"},
                                       {"value", uagent.device.model}});
            user_agent_data.push_back({{"name",  "device brand"},
                                       {"value", uagent.device.brand}});

            user_agent_data.push_back({{"hr", true}});

            user_agent_data.push_back({{"name",  "os family"},
                                       {"value", uagent.os.family}});
            user_agent_data.push_back({{"name",  "os major"},
                                       {"value", uagent.os.major}});
            user_agent_data.push_back({{"name",  "os minor"},
                                       {"value", uagent.os.minor}});
            user_agent_data.push_back({{"name",  "os patch"},
                                       {"value", uagent.os.patch}});
            user_agent_data.push_back({{"name",  "os patch_minor"},
                                       {"value", uagent.os.patch_minor}});
            user_agent_data.push_back({{"name",  "os toString()"},
                                       {"value", uagent.os.toString()}});
            user_agent_data.push_back({{"name",  "os toVersionString()"},
                                       {"value", uagent.os.toVersionString()}});

            user_agent_data.push_back({{"hr", true}});

            user_agent_data.push_back({{"name",  "browser family"},
                                       {"value", uagent.browser.family}});
            user_agent_data.push_back({{"name",  "browser major"},
                                       {"value", uagent.browser.major}});
            user_agent_data.push_back({{"name",  "browser minor"},
                                       {"value", uagent.browser.minor}});
            user_agent_data.push_back({{"name",  "browser patch"},
                                       {"value", uagent.browser.patch}});
            user_agent_data.push_back({{"name",  "browser patch_minor"},
                                       {"value", uagent.browser.patch_minor}});
            user_agent_data.push_back({{"name",  "browser toString()"},
                                       {"value", uagent.browser.toString()}});
            user_agent_data.push_back({{"name",  "browser toVersionString()"},
                                       {"value", uagent.browser.toVersionString()}});

            context["user_agent_data"] = user_agent_data;

            // create a response.view so that the session data can be sent to the context automatically
            return app.view("home/info.html", context);
        }).name("info");

    });
    /*
    app.any("/returningstrings", []() {
        return "Welcome to my home page!";
    });

    app.route({method::get, method::post}, "/{string:nome}", [](std::string nome) {
        return "Bem vindo, " + nome + "!";
    }).name("Print name").where("nome", "[A-Za-z]+");

    app.get("/match/{int:number?}", [](optional<int> number) {
        if (number) {
            return *number;
        } else {
            return 0;
        }
    });

    app.get("work", [](wpp::response &res) {
        thread work_thread([] {
            this_thread::sleep_for(chrono::seconds(5));
        });
        work_thread.join();
        res.body = "Work done";
    });

    app.any("/json", []() {
        wpp::json j;
        j["project"] = "rapidjson";
        j["stars"] = 10;
        return j;
    }).name("json");

    app.any("/beer/{int:number}", [](int count) {
        if (count > 100) {
            return std::string("400");
        }
        std::ostringstream os;
        os << count << " bottles of beer!";
        return std::string(os.str());
    }).name("beer");

    app.any("/users/{int:id}", [](wpp::request &req) {
        int user_id = stoi(req.query_parameters.get(0));
        return string("Hello user " + to_string(user_id));
    }).name("User profile");

    app.any("/add/{int:id}/{int:id2}", [](int a, int b) {
        return a + b;
    }).name("Add numbers").where({{"id",  "[0-9]+"},
                                  {"id2", "[0-9]+"}});

    app.redirect("redirecting", "Add numbers");

    app.post("/add_json", [](wpp::request &req) {
        json x = json::parse(req.body);
        if (!x) {
            return string("400");
        }
        int sum = stoi(x["a"].get<std::string>()) + stoi(x["b"].get<std::string>());
        return to_string(sum);
    }).name("Add numbers");

    // {ip}:18080/params?foo='blabla'&pew=32&count[]=a&count[]=b
    app.post("/params", [](wpp::response &res, wpp::request &req) {
        std::ostringstream os;
        // To get a simple string from the url params
        // To see it in action /params?foo='blabla'
        os << "Params: " << req.request_parameters << "\n\n";
        os << "The key 'foo' was " << (req.request_parameters.find("foo") == req.request_parameters.end() ? "not " : "") << "found.\n";
        // To get a double from the request
        // To see in action submit something like '/params?pew=42'
        if (req.request_parameters.find("pew") != req.request_parameters.end()) {
            double countD = boost::lexical_cast<double>(req.request_parameters.find("pew")->second);
            os << "The value of 'pew' is " << countD << '\n';
        }
        // To get a list from the request
        // You have to submit something like '/params?count[]=a&count[]=b' to have a list with two values (a and b)
        auto count = req.request_parameters.equal_range("count[]");
        os << "The key 'count' contains " << req.request_parameters.count("count[]") << " value(s).\n";
        for (auto iter = count.first; iter != count.second; ++iter) {
            os << " - " << iter->second << '\n';
        }
        return string({os.str()});
        //return wpp::response{os.str()};
    }).name("Add numbers");
    */

}

#endif //WPP_WEB_H
