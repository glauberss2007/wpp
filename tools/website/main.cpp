#include "setup_mvc.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <w++>

int main()
{
    //wpp::application app;
    wpp::application app;
    setup_mvc(app);
    //Start server
    app.port(8080).start();
    //Wait for server to start so that the client can connect
    //app.port(9980).multithreaded().run();
    return 0;
}