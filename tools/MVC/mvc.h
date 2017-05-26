//
// Created by Alan de Freitas on 08/02/17.
//

#ifndef WPP_MVC_H
#define WPP_MVC_H

#include "controller/routes/web_routes.h"
#include <wpp.h>
#include <regex>

using namespace std;
using namespace wpp;


void setup_mvc(wpp_app& app){
    // register_middlewares(app);
    // register_permissions(app);
    register_web_routes(app);
    // register_api_routes(app);
//    app.print_routes();
}





#endif //WPP_MVC_H
