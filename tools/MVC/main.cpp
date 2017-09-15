#include <wpp.h>
#include "mvc.h"

#include <iostream>
#include <sstream>
#include <string>

int main()
{
    wpp::application app;
    setup_mvc(app);
    app.port(9980).multithreaded().run();
    return 0;
}