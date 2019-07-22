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

    app.group({"web"},[](application &app) {

        app.get("/home", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");



        app.get("hello", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello2", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello3", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello4", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello5", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello6", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello7", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello8", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello9", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello10", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello11", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello12", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello13", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello14", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello15", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello16", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello17", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello18", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello19", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello20", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello21", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello22", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello23", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello24", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello25", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello26", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello27", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello28", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello29", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello30", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello31", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello32", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello33", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello34", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello35", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello36", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello37", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello38", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello39", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello40", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello41", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello42", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello43", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello44", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello45", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello46", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello47", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello48", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello49", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello50", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello51", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello52", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello53", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello54", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello55", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello56", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello57", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello58", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello59", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello60", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello61", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello62", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello63", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello64", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello65", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello66", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello67", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello68", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello69", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello70", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello71", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello72", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello73", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello74", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello75", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello76", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello77", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello78", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello79", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello80", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello81", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello82", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello83", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello84", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello85", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello86", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello87", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello88", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello89", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello90", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello91", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello92", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello93", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello94", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello95", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello96", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello97", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello98", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello99", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello100", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello101", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello102", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello103", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello104", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello105", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello106", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello107", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello108", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello109", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello110", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello111", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello112", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello113", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello114", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello115", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello116", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello117", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello118", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello119", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello120", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello121", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello122", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello123", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello124", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello125", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello126", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello127", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello128", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello129", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello130", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello131", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello132", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello133", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello134", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello135", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello136", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello137", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello138", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello139", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello140", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello141", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello142", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello143", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello144", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello145", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello146", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello147", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello148", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello149", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello150", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello151", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello152", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello153", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello154", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello155", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello156", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello157", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello158", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello159", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello160", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello161", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello162", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello163", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello164", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello165", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello166", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello167", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello168", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello169", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello170", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello171", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello172", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello173", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello174", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello175", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello176", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello177", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello178", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello179", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello180", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello181", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello182", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello183", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello184", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello185", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello186", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello187", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello188", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello189", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello190", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello191", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello192", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello193", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello194", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello195", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello196", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello197", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello198", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello199", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello200", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello201", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello202", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello203", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello204", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello205", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello206", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello207", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello208", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello209", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello210", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello211", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello212", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello213", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello214", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello215", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello216", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello217", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello218", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello219", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello220", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello221", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello222", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello223", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello224", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello225", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello226", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello227", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello228", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello229", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello230", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello231", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello232", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello233", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello234", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello235", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello236", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello237", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello238", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello239", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello240", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello241", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello242", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello243", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello244", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello245", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello246", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello247", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello248", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello249", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello250", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello251", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello252", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello253", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello254", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello255", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello256", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello257", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello258", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello259", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello260", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello261", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello262", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello263", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello264", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello265", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello266", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello267", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello268", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello269", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello270", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello271", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello272", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello273", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello274", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello275", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello276", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello277", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello278", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello279", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello280", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello281", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello282", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello283", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello284", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello285", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello286", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello287", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello288", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello289", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello290", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello291", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello292", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello293", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello294", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello295", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello296", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello297", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello298", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello299", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello300", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello301", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello302", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello303", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello304", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello305", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello306", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello307", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello308", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello309", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello310", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello311", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello312", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello313", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello314", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello315", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello316", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello317", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello318", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello319", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello320", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello321", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello322", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello323", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello324", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello325", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello326", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello327", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello328", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello329", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello330", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello331", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello332", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello333", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello334", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello335", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello336", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello337", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello338", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello339", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello340", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello341", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello342", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello343", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello344", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello345", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello346", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello347", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello348", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello349", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello50", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello351", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello352", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello353", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello354", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello355", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello356", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello357", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello358", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello359", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello360", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello361", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello362", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello363", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello364", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello365", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello366", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello367", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello368", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello369", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello370", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello371", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello372", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello373", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello374", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello375", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello376", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello377", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello378", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello379", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello380", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello381", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello382", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello383", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello384", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello385", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello386", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello387", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello388", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello389", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello390", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello391", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello392", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello393", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello394", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello395", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello396", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello397", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello398", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello399", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello400", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello401", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello402", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello403", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello404", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello405", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello406", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello407", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello408", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello409", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello410", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello411", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello412", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello413", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello414", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello415", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello416", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello417", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello418", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello419", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello420", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello421", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello422", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello423", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello424", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello425", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello426", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello427", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello428", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello429", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello430", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello431", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello432", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello433", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello434", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello435", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello436", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello437", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello438", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello439", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello440", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello441", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello442", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello443", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello444", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello445", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello446", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello447", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello448", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello449", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello450", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello451", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello452", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello453", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello454", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello455", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello456", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello457", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello458", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello459", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello460", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello461", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello462", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello463", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello464", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello465", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello466", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello467", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello468", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello469", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello470", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello471", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello472", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello473", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello474", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello475", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello476", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello477", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello478", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello479", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello480", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello481", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello482", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello483", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello484", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello485", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello486", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello487", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello488", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello489", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello490", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello500", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello501", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello502", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello503", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello504", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello505", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello506", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello507", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello508", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello509", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello510", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello511", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello512", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello513", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello514", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello515", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello516", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello517", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello518", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello519", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello520", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello521", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello522", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello523", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello524", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello525", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello526", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello527", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello528", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello529", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello530", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello531", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello532", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello533", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello534", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello535", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello536", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello537", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello538", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello539", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello540", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello541", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello542", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello543", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello544", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello545", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello546", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello547", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello548", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello549", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello550", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello551", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello552", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello553", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello554", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello555", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello556", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello557", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello558", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello559", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello560", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello561", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello562", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello563", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello564", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello565", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello566", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello567", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello568", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello569", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello570", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello571", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello572", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello573", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello574", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello575", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello576", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello577", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello578", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello579", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello580", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello581", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello582", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello583", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello584", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello585", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello586", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello587", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello588", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello589", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello590", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello591", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello592", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello593", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello594", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello595", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello596", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello597", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello598", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello599", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello600", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello601", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello602", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello603", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello604", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello605", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello606", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello607", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello608", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello609", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello610", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello611", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello612", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello613", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello614", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello615", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello616", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello617", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello618", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello619", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello620", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello621", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello622", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello623", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello624", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello625", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello626", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello627", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello628", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello629", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello630", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello631", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello632", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello633", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello634", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello635", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello636", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello637", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello638", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello639", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello640", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello641", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello642", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello643", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello644", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello645", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello646", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello647", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello648", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello649", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello650", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello651", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello652", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello653", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello654", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello655", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello656", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello657", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello658", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello659", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello660", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello661", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello662", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello663", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello664", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello665", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello666", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello667", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello668", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello669", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello670", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello671", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello672", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello673", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello674", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello675", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello676", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello677", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello678", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello679", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello680", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello681", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello682", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello683", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello684", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello685", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello686", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello687", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello688", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello689", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello690", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello691", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello692", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello693", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello694", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello695", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello696", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello697", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello698", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello699", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello700", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello701", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello702", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello703", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello704", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello705", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello706", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello707", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello708", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello709", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello710", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello711", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello712", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello713", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello714", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello715", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello716", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello717", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello718", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello719", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello720", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello721", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello722", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello723", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello724", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello725", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello726", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello727", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello728", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello729", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello730", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello731", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello732", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello733", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello734", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello735", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello736", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello737", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello738", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello239", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello740", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello741", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello742", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello743", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello744", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello745", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello746", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello747", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello748", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello749", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello750", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello751", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello752", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello753", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello754", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello755", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello756", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello757", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello758", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello759", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello760", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello761", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello762", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello763", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello764", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello765", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello766", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello767", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello768", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello769", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello770", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello771", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello772", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello773", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello774", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello775", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello776", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello777", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello778", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello779", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello780", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello781", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello782", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello783", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello784", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello785", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello786", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello787", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello788", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello789", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello790", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello791", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello792", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello793", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello794", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello795", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello796", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello797", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello798", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello799", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello800", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello801", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello802", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello803", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello804", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello805", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello806", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello807", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello808", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello809", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello810", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello811", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello812", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello813", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello814", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello815", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello816", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello817", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello818", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello819", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello820", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello821", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello822", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello823", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello824", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello825", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello826", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello827", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello828", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello829", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello830", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello831", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello832", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello833", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello834", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello835", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello836", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello837", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello838", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello839", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello840", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello841", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello842", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello843", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello844", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello845", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello846", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello847", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello848", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello849", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello850", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello851", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello852", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello853", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello854", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello855", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello856", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello857", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello858", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello859", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello860", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello861", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello862", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello863", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello864", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello865", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello866", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello867", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello868", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello869", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello870", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello871", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello872", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello873", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello874", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello875", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello876", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello877", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello878", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello879", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello880", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello881", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello882", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello883", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello884", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello885", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello886", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello887", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello888", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello889", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello890", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello891", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello892", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello893", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello894", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello895", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello896", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello897", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello898", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello899", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello900", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello901", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello902", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello903", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello904", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello905", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello906", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello907", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello908", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello909", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello910", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello911", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello912", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello913", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello914", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello915", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello916", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello917", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello918", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello919", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello920", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello921", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello922", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello923", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello924", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello925", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello926", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello927", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello928", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello929", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello930", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello931", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello932", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello933", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello934", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello935", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello936", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello937", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello938", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello939", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello940", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello941", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello942", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello943", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello944", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello945", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello946", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello947", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello948", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello949", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello950", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello951", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello952", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello953", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello954", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello955", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello956", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello957", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello958", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello959", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello960", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello961", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello962", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello963", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello964", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello965", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello966", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello967", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello968", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello969", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello970", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello971", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello972", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello973", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello974", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello975", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello976", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello977", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello978", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello979", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello980", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello981", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello982", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello983", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello984", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello985", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello986", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello987", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello988", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello989", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello990", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello991", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello992", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello993", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello994", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello995", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello996", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello997", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello998", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello999", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");

        app.get("hello1000", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("hello.html", context);
        }).name("hello");
/*

        app.get("/home", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home1", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home2", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home3", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home4", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home5", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home6", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home7", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home8", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home9", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home10", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home11", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home12", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home13", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home14", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home15", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home16", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home17", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home18", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home19", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home20", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home21", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home22", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home23", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home24", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home25", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home26", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home27", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home28", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home29", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home30", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home31", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home32", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home33", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home34", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home35", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home36", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home37", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home38", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home39", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home40", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home41", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home42", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home43", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home44", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home45", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home46", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home47", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home48", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home49", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home50", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home51", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home52", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home53", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home54", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home55", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home56", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home57", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home58", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home59", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home60", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home61", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home62", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home63", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home64", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home65", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home66", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home67", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home68", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home69", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home70", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home71", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home72", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home73", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home74", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home75", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home76", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home77", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home78", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home79", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home80", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home81", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home82", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home83", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home84", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home85", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home86", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home87", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home88", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home89", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home90", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home91", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home92", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home93", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home94", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home95", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home96", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home97", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home98", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home99", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");

        app.get("/home100", [&app](wpp::request &req) {
            wpp::json context;
            return app.view("home/home.html", context);
        }).name("home");
*/
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
