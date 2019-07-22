//
// Created by Alan de Freitas on 08/02/17.
//

#ifndef WPP_MVC_H
#define WPP_MVC_H

// #include "utils/logging.h"

// model

// controller
//#include "controller/middlewares/middlewares.h"
#include "controller/routes/web_routes.h"
#include "controller/routes/error_routes.h"
// view
#include "view/lambdas.h"
#include "view/view_data.h"
// server
#include "config.h"
#include "environment.h"

#include <w++>

using namespace wpp;

/// setup_mvc - include the data of our mvc in the application
///
/// @param app - reference to the w++ application
void setup_mvc(application &app) {
    config(app);
    // Model

    // View
    register_view_lambdas(app);
    register_view_data(app);
    // Controller
    //register_middlewares(app);
    register_web_routes(app);
    register_error_routes(app);
}

#endif //WPP_MVC_H