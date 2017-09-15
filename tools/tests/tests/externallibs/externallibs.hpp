//
// Created by Alan de Freitas on 18/06/17.
//

#ifndef WPP_EXTERNALLIBS_H
#define WPP_EXTERNALLIBS_H

#include <catch.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include <stdio.h>

#include <bustache/model.hpp>
#include <boost/unordered_map.hpp>

#include <json.hpp>

#include <wpp.h>

TEST_CASE("External Libraries"){

    SECTION("JSON Modern C++"){
        using json = nlohmann::json;
        using namespace std;


        // create an empty structure (null)
        json j;

        j = {
                {"pi", 3.141},
                {"happy", true},
                {"name", "Niels"},
                {"nothing", nullptr},
                {"answer", {
                               {"everything", 42}
                       }},
                {"list", {1, 0, 2}},
                {"object", {
                               {"currency", "USD"},
                             {"value", 42.99}
                       }}
        };

        j["object"] = {
                {"currency", "USD"},
                {"value", 42.99},
                {"country", "USA"}
        };

        cout << j << endl;

        j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

        cout << j << endl;

        j = R"(
      {
        "happy": true,
        "pi": 3.141
      }
    )"_json;

        cout << j << endl;

        j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

        cout << j << endl;

        std::string s = j.dump();    // {\"happy\":true,\"pi\":3.141}

        cout << s << endl;

        // serialization with pretty printing
        // pass in the amount of spaces to indent
        std::cout << j.dump(4) << std::endl;
        // {
        //     "happy": true,
        //     "pi": 3.141
        // }
    }

    SECTION("SHA1 Cryptography"){
        std::string header_value = "Value-of-Sec-WebSocket-Key";
        std::string secret = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        std::string magic = header_value + secret;
        // SHA1 cryptographic hash function object
        sha1::SHA1 s;
        // Receiving the input and keeping hash value (the digest) in the object
        s.processBytes(magic.data(), magic.size());
        // SHA1-produces a 20 byte hash value
        using byte = uint8_t;
        byte digest[20];
        s.getDigestBytes(digest);
        // the digest is typically rendered as a 40 digits long hexadecimal number
        std::string hash;
        for (auto &&item : digest) {
            hash += std::to_string((int)item);
        }
        CHECK(hash == std::string("22215621422113913812031301762231932197174106130115212142"));
    }

    SECTION("Query URL strings") {
        // query string
        unsigned NUMKVPAIRS = 256;
        unsigned VALSIZE = 512;

        CHECK(VALSIZE == 512);

        // for the pre-processed version
        int n; // where the parameters begin
        char *kvpairs[NUMKVPAIRS]; // the pairs

        // to keep the value of a parameter
        char value[VALSIZE];
        char *value_ptr;

        char getstring[] = "scheme://username:password@domain:port/path?foo=bar&frob&baz=quux&color=09FA#anchor";

        CHECK_THAT(getstring,
                Catch::Equals("scheme://username:password@domain:port/path?foo=bar&frob&baz=quux&color=09FA#anchor"));

        SECTION("Easy and Slow Scan Value") {

            if (wpp::qs_scanvalue("foo", getstring, value, sizeof(value)) != nullptr)
            CHECK(string(value) == string("bar"));

            if (wpp::qs_scanvalue("baz", getstring, value, sizeof(value)) != nullptr)
            CHECK(string(value) == string("quux"));

            if (wpp::qs_scanvalue("frob", getstring, value, sizeof(value)) != nullptr)
            CHECK(string(value) == string(""));

            CHECK(wpp::qs_scanvalue("blah", getstring, value, sizeof(value)) == nullptr);

        }


        SECTION("Fast, Complex, Destructive, Pre-processed Scan Value") {
            /*  ***THIS WILL ALTER getstring***  */
            n = wpp::qs_parse(getstring, kvpairs, NUMKVPAIRS);
            CHECK(n == 4);

            CHECK(string(kvpairs[0]) == string("baz=quux"));
            CHECK(string(kvpairs[1]) == string("color=09FA"));
            CHECK(string(kvpairs[2]) == string("foo=bar"));
            CHECK(string(kvpairs[3]) == string("frob"));

            if ((value_ptr = wpp::qs_k2v("foo", kvpairs, n)) != nullptr)
            CHECK(string(value_ptr) == string("bar"));

            if ((value_ptr = wpp::qs_k2v("baz", kvpairs, n)) != nullptr)
            CHECK(string(value_ptr) == string("quux"));

            if ((value_ptr = wpp::qs_k2v("frob", kvpairs, n)) != nullptr)
            CHECK(string(value_ptr) == string(""));

            REQUIRE((value_ptr = wpp::qs_k2v("blah", kvpairs, n)) == nullptr);

        }
    }

    SECTION("HTTP Parsing") {
        http_parser hp;
        http_parser_settings hps;
        size_t response;
        http_parser_init(&hp, http_parser_type::HTTP_REQUEST);
        SECTION("Simple GET"){
            char data1[] = "GET /hello.htm HTTP/1.1\n"
                    "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                    "Host: www.tutorialspoint.com\n"
                    "Accept-Language: en-us\n"
                    "Accept-Encoding: gzip, deflate\n"
                    "Connection: Keep-Alive";
            response = http_parser_execute(&hp, &hps, data1, std::strlen(data1));
            CHECK(response == 188);
            // cout << "Response: " << response << endl;
            CHECK(http_should_keep_alive(&hp) == true);
            // cout << "Should keep alive? " << (http_should_keep_alive(&hp) ? "Yes" : "No") << endl;
        }
        SECTION("POST with simple content type (simple web form data)") {
            char data2[] = "POST /cgi-bin/process.cgi HTTP/1.1\n"
                    "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                    "Host: www.tutorialspoint.com\n"
                    "Content-Type: application/x-www-form-urlencoded\n"
                    "Content-Length: 50\n"
                    "Accept-Language: en-us\n"
                    "Accept-Encoding: gzip, deflate\n"
                    "Connection: Keep-Alive\n"
                    "\n"
                    "licenseID=string&content=string&/paramsXML=string";
            response = http_parser_execute(&hp, &hps, data2, std::strlen(data2));
            CHECK(response == 317);
            // cout << "Response: " << response << endl;
            CHECK(http_should_keep_alive(&hp) == true);
            // cout << "Should keep alive? " << (http_should_keep_alive(&hp) ? "Yes" : "No") << endl;
        }
        SECTION("POST with xml data"){
            char data3[] = "POST /cgi-bin/process.cgi HTTP/1.1\n"
                    "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                    "Host: www.tutorialspoint.com\n"
                    "Content-Type: text/xml; charset=utf-8\n"
                    "Content-Length: 110\n"
                    "Accept-Language: en-us\n"
                    "Accept-Encoding: gzip, deflate\n"
                    "Connection: Keep-Alive\n"
                    "\n"
                    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                    "<string xmlns=\"http://clearforest.com/\">string</string>";
            response = http_parser_execute(&hp, &hps, data3, std::strlen(data3));
            // cout << "Response: " << response << endl;
            CHECK(response == 353);
            // cout << "Should keep alive? " << (http_should_keep_alive(&hp) ? "Yes" : "No") << endl;
            CHECK(http_should_keep_alive(&hp) == true);

            // cout << "hp.content_length = " << hp.content_length << endl;
            CHECK(hp.content_length == 16);
            // cout << "hp.data = " << hp.data << endl;
            // cout << "hp.flags = " << hp.flags << endl;
            CHECK(hp.flags == 2);
            // cout << "hp.header_state = " << hp.header_state << endl;
            CHECK(hp.header_state == 17);
            // cout << "hp.http_errno = " << http_errno_name((http_errno)hp.http_errno) << endl;
            // cout << "hp.http_errno = " << http_errno_description((http_errno)hp.http_errno) << endl;
            // cout << "hp.http_major = " << hp.http_major << endl;
            // cout << "hp.http_minor = " << hp.http_minor << endl;
            // cout << "hp.index = " << hp.index << endl;
            // cout << "hp.method = " << http_method_str((http_method)hp.method) << endl;
            CHECK(string(http_method_str((http_method)hp.method)) == string("POST"));
            // cout << "hp.nread = " << hp.nread << endl;
            CHECK(hp.nread == 0);
            // cout << "hp.state = " << hp.state << endl;
            CHECK(hp.state == 60);
            // cout << "hp.status_code = " << hp.status_code << endl;
            CHECK(hp.status_code == 0);
            // cout << "hp.type = " << hp.type << endl;
            CHECK(hp.type == 0);
            // cout << "hp.upgrade = " << hp.upgrade << endl;
            CHECK(hp.upgrade == 0);
        }
    }

    #include "bustache.hpp"
}

#endif //WPP_EXTERNALLIBS_H
