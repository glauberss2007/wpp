#include <wpp.h>
#include "mvc.h"

int main()
{
    wpp::wpp_app app;
    setup_mvc(app);
    app.port(9980).multithreaded().run();
    return 0;
}