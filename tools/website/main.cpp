#include "setup_mvc.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <w++>
//#include <pqxx/pqxx>

int main() {
    wpp::application app;
    setup_mvc(app);
    app.port(8080).multithreaded().start();
    return 0;
}