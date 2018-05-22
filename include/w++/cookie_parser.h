#pragma once
#include <boost/algorithm/string/trim.hpp>
#include "request.h"
#include "response.h"

namespace wpp
{
    // Any middleware requires following 3 members: context, before_handle, after_handle
    struct response;

    struct cookie_parser
    {
        // struct context;
        //      storing data for the middleware; can be read from another middleware or handlers
        struct context
        {
            // the cookies that already exist
            std::unordered_map<std::string, std::string> jar;
            // the cookies we are going to add in the next response
            std::unordered_map<std::string, std::string> cookies_to_add;

            // cookies come from the jar
            std::string get_cookie(const std::string& key);

            // new cookies go to the list to add cookies
            void set_cookie(const std::string& key, const std::string& value);
        };

        // before_handle (in this case, puts the cookies in the jar)
        //      called before handling the request.
        //      if res.end() is called, the operation is halted.
        //      (still call after_handle of this middleware)
        //      2 signatures:
        //      void before_handle(request& req, response& res, context& ctx)
        //          if you only need to access this middlewares context.
        //      template <typename AllContext>
        //      void before_handle(request& req, response& res, context& ctx, AllContext& all_ctx)
        //          you can access another middlewares' context by calling `all_ctx.template get<MW>()'
        //          ctx == all_ctx.template get<CurrentMiddleware>()
        void before_handle(request& req, response& res, context& ctx);

        // after_handle
        //      called after handling the request.
        //      void after_handle(request& req, response& res, context& ctx)
        //      template <typename AllContext>
        //      void after_handle(request& req, response& res, context& ctx, AllContext& all_ctx)
        void after_handle(request& /*req*/, response& res, context& ctx);

    };

    /*
    App<cookie_parser, AnotherJarMW> app;
    A B C
    A::context
        int aa;

    ctx1 : tools A::context
    ctx2 : tools ctx1, tools B::context
    ctx3 : tools ctx2, tools C::context

    C depends on A

    C::handle
        context.aaa

    App::context : private cookie_parser::contetx, ...
    {
        jar

    }

    SimpleApp
    */
}
