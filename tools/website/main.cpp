#include "setup_mvc.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <w++>
//#include <pqxx/pqxx>

int main(){
    /*int argc, char* argv[]) {
    if (argc != 5)
    {
        std::cerr <<
                  "Usage: advanced-server-flex <address> <port> <doc_root> <threads>\n" <<
                  "Example:\n" <<
                  "    advanced-server-flex 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
     */

    wpp::application app;
    setup_mvc(app);
    //app.start_beast(argc, argv, app);
    app.port(8080).multithreaded().start();

    return 0;
}