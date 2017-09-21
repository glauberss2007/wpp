#pragma once
#include <boost/algorithm/string/trim.hpp>
#include "http_request.h"
#include "http_response.h"

namespace wpp
{
    // Any middleware requires following 3 members: context, before_handle, after_handle

    struct CookieParser
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
            std::string get_cookie(const std::string& key)
            {
                if (jar.count(key))
                    return jar[key];
                return {};
            }

            // new cookies go to the list to add cookies
            void set_cookie(const std::string& key, const std::string& value)
            {
                cookies_to_add.emplace(key, value);
            }
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
        void before_handle(request& req, response& res, context& ctx)
        {
            // get the cookies from the user
            int count = req.headers.count("Cookie");
            if (!count)
                return; // return if there are no cookies
            if (count > 1)
            {
                // return BadRequest 400 if there is more than one cookie header
                res.code = 400;
                res.end();
                return;
            }
            // string with all cookies
            std::string cookies = req.get_header_value("Cookie");
            size_t pos = 0;
            while(pos < cookies.size())
            {
                // find position of next "=" of a cookie
                size_t pos_equal = cookies.find('=', pos);
                if (pos_equal == cookies.npos)
                    break;
                // then we have the cookie's key from pos to pos_equal
                std::string name = cookies.substr(pos, pos_equal-pos);
                boost::trim(name);

                // then we look for the cookies value
                pos = pos_equal+1;
                // ignore spaces
                while(pos < cookies.size() && cookies[pos] == ' ') pos++;
                // check if there are still chars to check
                if (pos == cookies.size())
                    break;
                // begin to parse string
                std::string value;
                // cookie value has to begin with " (opening string) or ; (empty cookie)
                if (cookies[pos] == '"')
                {
                    int dquote_meet_count = 0;
                    pos ++;
                    size_t pos_dquote = pos-1;
                    // look for closing quote after position of opening quote (and skipping the escaped quotes \\")
                    do
                    {
                        pos_dquote = cookies.find('"', pos_dquote+1);
                        dquote_meet_count ++;
                    } while(pos_dquote < cookies.size() && cookies[pos_dquote-1] == '\\');
                    // break if we got to the last position in the string
                    if (pos_dquote == cookies.npos)
                        break;
                    // if there are no escaped \\s we just copy the whole thing as the cookie value
                    if (dquote_meet_count == 1)
                        value = cookies.substr(pos, pos_dquote - pos);
                    // else
                    else
                    {
                        // reserve space for the whole value
                        value.clear();
                        value.reserve(pos_dquote-pos);
                        // go position by position
                        for(size_t p = pos; p < pos_dquote; p++)
                        {
                            // FIXME minimal escaping
                            // TODO: improve the parse cookie function
                            // if it's a \\ that comes before the last position found
                            if (cookies[p] == '\\' && p + 1 < pos_dquote)
                            {
                                p++;
                                // if the pos_dquote represents a legitimate \\ ou "
                                if (cookies[p] == '\\' || cookies[p] == '"')
                                    // we copy the value without the \\ straight to the value string
                                    value += cookies[p];
                                else
                                {
                                    // else, just add \\ and whatever follows
                                    value += '\\';
                                    value += cookies[p];
                                }
                            }
                            else
                                // if it's not a \\ we just copy it
                                value += cookies[p];
                        }
                    }
                    // we put the cookies we found in the jar
                    ctx.jar.emplace(std::move(name), std::move(value));
                    // find where the next cookie begins
                    pos = cookies.find(";", pos_dquote+1);
                    // check if it's not over
                    if (pos == cookies.npos)
                        break;
                    pos++;
                    // skip spaces
                    while(pos < cookies.size() && cookies[pos] == ' ') pos++;
                    // check if it's not over
                    if (pos == cookies.size())
                        break;
                }
                // else (if there is no " to mark the beggining of a cookie)
                else
                {
                    // look for the next cookie
                    size_t pos_semicolon = cookies.find(';', pos);
                    // put whatever is between = and the ; (even if it's without the "s)
                    value = cookies.substr(pos, pos_semicolon - pos);
                    // trim the value (probably is going to be empty but this is just a workaround on an invalid input)
                    boost::trim(value);
                    // put the cookie in the jar
                    ctx.jar.emplace(std::move(name), std::move(value));
                    // go to next cookie
                    pos = pos_semicolon;
                    // check if it's over
                    if (pos == cookies.npos)
                        break;
                    // advance
                    pos ++;
                    // skip spaces
                    while(pos < cookies.size() && cookies[pos] == ' ') pos++;
                    // check if it's over
                    if (pos == cookies.size())
                        break;
                }
            }
        }

        // after_handle
        //      called after handling the request.
        //      void after_handle(request& req, response& res, context& ctx)
        //      template <typename AllContext>
        //      void after_handle(request& req, response& res, context& ctx, AllContext& all_ctx)
        void after_handle(request& /*req*/, response& res, context& ctx)
        {
            for(auto& cookie:ctx.cookies_to_add)
            {
                res.add_header("Set-Cookie", cookie.first + "=" + cookie.second);
            }
        }
    };

    /*
    App<CookieParser, AnotherJarMW> app;
    A B C
    A::context
        int aa;

    ctx1 : tools A::context
    ctx2 : tools ctx1, tools B::context
    ctx3 : tools ctx2, tools C::context

    C depends on A

    C::handle
        context.aaa

    App::context : private CookieParser::contetx, ... 
    {
        jar

    }

    SimpleApp
    */
}
