//
// Created by Alan de Freitas on 08/02/17.
//

#ifndef WPP_MVC_H
#define WPP_MVC_H

#include "utils/logging.h"
#include "controller/routes/web_routes.h"
#include <w++>

using namespace wpp;

/// setup_mvc - include the data of our mvc in the application
///
/// @param app - reference to the w++ application
void setup_mvc(application& app){
    utils::default_log_level::default_level = utils::log_level::debug;
//void setup_mvc(wpp::application& app){
    // register_middlewares(app);
    // register_permissions(app);
    //register_default_routes(app);
    register_web_routes(app);
    // register_api_routes(app);
//    app.print_routes();
}

#endif //WPP_MVC_H