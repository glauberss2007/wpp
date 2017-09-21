#pragma once

// Settings
    // many settings from CMAKE we need in the code
    #include "settings.h"

        // External libs
            // query/extract GET parameters from url (https://github.com/bartgrantham/qs_parse)
            #include "query_string.h"
            // a C (not object-oriented) http parser (Joyent)
            #include "http_parser.h"
            // mustache template library (https://github.com/jamboree/bustache)
            #include "bustache/model.hpp"
            // SHA1 cryptographic hash function algorithm (https://github.com/mohaps/TinySHA1)
            #include "TinySHA1.hpp"
            // json library (https://github.com/nlohmann/json)
            #include "json.hpp"

        // Simple Data structures
            // a simple unordered_multimap<std::string,std::string> and json alias
            #include "structures.h"

        // Utilities
            // logger that prints accordingly to the level defined in the settings
            #include "logging.h"
            // asynchronous queue of functions
            #include "dumb_timer_queue.h"

        // Communication (based on boost asio)
            // class parses and the keeps the request data (but doesn't process much)
            #include "http_request.h"
            // wrappers for boost::asio::tcp::socket, representing connection to the client
            #include "socket_adaptors.h"
            // wrapper adapting the sockets (normal or ssl) above for creating a connection
            // a connection makes a handshake, replies, and keeps on reading state (replying as needed)
            #include "websocket.h"

        // Receiving/returning data
            // C++ wrapper for the C style http_parser.h functions
            // Return a request parsed in the http_request.h style (struct request)
            #include "parser.h"
            // Creates the response and converts it to a string
            #include "http_response.h"

        // Routing libraries (crow server)
            // recursive meta-templates for middleware context
            #include "middleware_context.h"
            // middleware (cookieparser) that parses cookies (before_handler) and add cookies for user next session (after_handler)
            #include "middleware.h"
            // meta-programming: const string, param to tag, and tag to param
            #include "const_str.h"
            // identifies function traits, get elements from tuple by type
            #include "function_traits.h"
            // HTTP methods, parameter types, struct with routing_params
            #include "common.h"
            // rules that represent urls/routes
            #include "rule.h"
            // trie data structure to keep the routes
            #include "trie.h"
            // defines rules that match routes to functions (keeps the trie and vector of routes)
            #include "routing.h"
            // connection between server and client (handles requests and makes responses)
            #include "http_connection.h"
            // defines main tick_function, create io_services for threads, and runs
            #include "http_server.h"

        // App library
            #include "app.h"

