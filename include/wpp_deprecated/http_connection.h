#pragma once
#include <boost/asio.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <atomic>
#include <chrono>
#include <vector>

#include "http_parser.h"

#include "parser.h"
#include "http_response.h"
#include "logging.h"
#include "settings.h"
#include "dumb_timer_queue.h"
#include "middleware_context.h"
#include "socket_adaptors.h"


namespace wpp
{
    using namespace boost;
    using tcp = asio::ip::tcp;

    // utilities
    namespace detail
    {
        template <typename MW>
        struct check_before_handle_arity_3_const
        {
            template <typename T,
                void (T::*)(request&, response&, typename MW::context&) const = &T::before_handle
            >
            struct get
            { };
        };

        template <typename MW>
        struct check_before_handle_arity_3
        {
            template <typename T,
                void (T::*)(request&, response&, typename MW::context&) = &T::before_handle
            >
            struct get
            { };
        };

        template <typename MW>
        struct check_after_handle_arity_3_const
        {
            template <typename T,
                void (T::*)(request&, response&, typename MW::context&) const = &T::after_handle
            >
            struct get
            { };
        };

        template <typename MW>
        struct check_after_handle_arity_3
        {
            template <typename T,
                void (T::*)(request&, response&, typename MW::context&) = &T::after_handle
            >
            struct get
            { };
        };

        template <typename T>
        struct is_before_handle_arity_3_impl
        {
            template <typename C>
            static std::true_type f(typename check_before_handle_arity_3_const<T>::template get<C>*);

            template <typename C>
            static std::true_type f(typename check_before_handle_arity_3<T>::template get<C>*);

            template <typename C>
            static std::false_type f(...);

        public:
            static const bool value = decltype(f<T>(nullptr))::value;
        };

        template <typename T>
        struct is_after_handle_arity_3_impl
        {
            template <typename C>
            static std::true_type f(typename check_after_handle_arity_3_const<T>::template get<C>*);

            template <typename C>
            static std::true_type f(typename check_after_handle_arity_3<T>::template get<C>*);

            template <typename C>
            static std::false_type f(...);

        public:
            static const bool value = decltype(f<T>(nullptr))::value;
        };

        template <typename MW, typename Context, typename ParentContext>
        typename std::enable_if<!is_before_handle_arity_3_impl<MW>::value>::type
        before_handler_call(MW& mw, request& req, response& res, Context& ctx, ParentContext& /*parent_ctx*/)
        {
            mw.before_handle(req, res, ctx.template get<MW>(), ctx);
        }

        template <typename MW, typename Context, typename ParentContext>
        typename std::enable_if<is_before_handle_arity_3_impl<MW>::value>::type
        before_handler_call(MW& mw, request& req, response& res, Context& ctx, ParentContext& /*parent_ctx*/)
        {
            mw.before_handle(req, res, ctx.template get<MW>());
        }

        template <typename MW, typename Context, typename ParentContext>
        typename std::enable_if<!is_after_handle_arity_3_impl<MW>::value>::type
        after_handler_call(MW& mw, request& req, response& res, Context& ctx, ParentContext& /*parent_ctx*/)
        {
            mw.after_handle(req, res, ctx.template get<MW>(), ctx);
        }

        template <typename MW, typename Context, typename ParentContext>
        typename std::enable_if<is_after_handle_arity_3_impl<MW>::value>::type
        after_handler_call(MW& mw, request& req, response& res, Context& ctx, ParentContext& /*parent_ctx*/)
        {
            mw.after_handle(req, res, ctx.template get<MW>());
        }

        template <int N, typename Context, typename Container, typename CurrentMW, typename ... Middlewares>
        bool middleware_call_helper(Container& middlewares, request& req, response& res, Context& ctx)
        {
            using parent_context_t = typename Context::template partial<N-1>;
            before_handler_call<CurrentMW, Context, parent_context_t>(std::get<N>(middlewares), req, res, ctx, static_cast<parent_context_t&>(ctx));

            if (res.is_completed())
            {
                after_handler_call<CurrentMW, Context, parent_context_t>(std::get<N>(middlewares), req, res, ctx, static_cast<parent_context_t&>(ctx));
                return true;
            }

            if (middleware_call_helper<N+1, Context, Container, Middlewares...>(middlewares, req, res, ctx))
            {
                after_handler_call<CurrentMW, Context, parent_context_t>(std::get<N>(middlewares), req, res, ctx, static_cast<parent_context_t&>(ctx));
                return true;
            }

            return false;
        }

        template <int N, typename Context, typename Container>
        bool middleware_call_helper(Container& /*middlewares*/, request& /*req*/, response& /*res*/, Context& /*ctx*/)
        {
            return false;
        }

        template <int N, typename Context, typename Container>
        typename std::enable_if<(N<0)>::type 
        after_handlers_call_helper(Container& /*middlewares*/, Context& /*context*/, request& /*req*/, response& /*res*/)
        {
        }

        template <int N, typename Context, typename Container>
        typename std::enable_if<(N==0)>::type after_handlers_call_helper(Container& middlewares, Context& ctx, request& req, response& res)
        {
            using parent_context_t = typename Context::template partial<N-1>;
            using CurrentMW = typename std::tuple_element<N, typename std::remove_reference<Container>::type>::type;
            after_handler_call<CurrentMW, Context, parent_context_t>(std::get<N>(middlewares), req, res, ctx, static_cast<parent_context_t&>(ctx));
        }

        template <int N, typename Context, typename Container>
        typename std::enable_if<(N>0)>::type after_handlers_call_helper(Container& middlewares, Context& ctx, request& req, response& res)
        {
            using parent_context_t = typename Context::template partial<N-1>;
            using CurrentMW = typename std::tuple_element<N, typename std::remove_reference<Container>::type>::type;
            after_handler_call<CurrentMW, Context, parent_context_t>(std::get<N>(middlewares), req, res, ctx, static_cast<parent_context_t&>(ctx));
            after_handlers_call_helper<N-1, Context, Container>(middlewares, ctx, req, res);
        }
    }

    // wpp::connectioncount will count the # of users connected
    static int connectionCount;

    // Connection uses a boost io_service, server name, middlewares, timer, context (for ssl)
    template <typename Adaptor, typename Handler, typename ... Middlewares>
    class Connection
    {
    public:
        // create the connection with boost io_service, name, middleware, context, etc
        Connection(
            boost::asio::io_service& io_service,
            Handler* handler,
            const std::string& server_name,
            std::tuple<Middlewares...>* middlewares,
            std::function<std::string()>& get_cached_date_str_f,
            detail::dumb_timer_queue& timer_queue,
            typename Adaptor::context* adaptor_ctx_
            )
            : adaptor_(io_service, adaptor_ctx_),
            handler_(handler),
            parser_(this),
            server_name_(server_name),
            middlewares_(middlewares),
            get_cached_date_str(get_cached_date_str_f),
            timer_queue(timer_queue)
        {
            // we count that there is one more connection made
            connectionCount ++;
            if (wpp_settings::enable_debug)
                log_debug << "Connection open, total " << connectionCount << ", " << this << std::endl;
        }

        // delete connection
        ~Connection()
        {
            res.complete_request_handler_ = nullptr;
            cancel_deadline_timer();
            connectionCount --;
            if (wpp_settings::enable_debug)
                log_debug << "Connection closed, total " << connectionCount << ", " << this << std::endl;
        }

        // return raw socket used in this connection
        decltype(std::declval<Adaptor>().raw_socket())& socket()
        {
            return adaptor_.raw_socket();
        }

        // start socket adaptor with function that reads data
        void start()
        {
            // the adaptor will run this function with its own error code (the ssl adaptor will do the same but encrypted)
            adaptor_.start([this](const boost::system::error_code& ec) {
                // if there is no error (it's not over), read data from the client
                if (!ec)
                {
                    start_deadline();

                    do_read();
                }
                // if there is error (it's over), destroy
                else
                {
                    check_destroy();
                }
            });
        }

        // if the request was read, we handle what the header asks us to do (usually 100-continue)
        void handle_header()
        {
            // HTTP 1.1 Expect: 100-continue
            if (parser_.check_version(1, 1) && parser_.headers.count("expect") && get_header_value(parser_.headers, "expect") == "100-continue")
            {
                buffers_.clear();
                static std::string expect_100_continue = "HTTP/1.1 100 Continue\r\n\r\n";
                buffers_.emplace_back(expect_100_continue.data(), expect_100_continue.size());
                do_write();
            }
        }

        // handle the whole connection request
        void handle()
        {
            cancel_deadline_timer();
            bool is_invalid_request = false;
            add_keep_alive_ = false;

            // create the request object from the string we already parsed
            req_ = std::move(parser_.to_request());
            request& req = req_;

            // if client asked for http/1.0
            if (parser_.check_version(1, 0))
            {
                // HTTP/1.0
                // if one of the headers (headers is a cimap) is asking for "connection"
                int connection = req.headers.count("connection") > 0 ? 1 : req.headers.count("Connection") > 0 ? 2 : 0;
                if (connection)
                {
                    // check if the value (case insensitively) is "Keep-Alive"
                    if (boost::iequals(req.get_header_value(connection == 1 ? "connection" : "Connection"),"Keep-Alive"))
                        // if so, we do keep it alive
                        add_keep_alive_ = true;
                }
                else
                    close_connection_ = true;
            }
            // if client asked for http/1.1
            else if (parser_.check_version(1, 1))
            {
                // HTTP/1.1
                // if one of the headers (headers is a cimap) is asking for "connection"
                int connection = req.headers.count("connection") > 0 ? 1 : req.headers.count("Connection") > 0 ? 2 : 0;
                if (connection)
                {
                    // check if the value is "close"
                    if (req.get_header_value(req.get_header_value(connection == 1 ? "connection" : "Connection")) == "close")
                        close_connection_ = true;
                    // else, it might be asking to keep alive
                    else if (boost::iequals(req.get_header_value(connection == 1 ? "connection" : "Connection"),"Keep-Alive"))
                        add_keep_alive_ = true;
                }
                // if there is no host on the headers
                int host = req.headers.count("host") > 0 ? 1 : req.headers.count("Host") > 0 ? 2 : 0;
                if (!host)
                {
                    // the request is marked as invalid
                    is_invalid_request = true;
                    // we respond with 400
                    res = response(400);
                }
                // the request is asking to upgrade/change the protocol
				if (parser_.is_upgrade())
				{
                    // we check if it's asking for HTTP/2
                    int upgrade = req.headers.count("upgrade") > 0 ? 1 : req.headers.count("Upgrade") > 0 ? 2 : 0;
					if (req.get_header_value(upgrade == 1 ? "upgrade" : "Upgrade") == "h2c")
					{
                        // if it is, we'll just ignore for now
						// TODO HTTP/2
                        // currently, ignore upgrade header
					}
                    else
                    {
                        // else (upgrade not to h2c), it's because we close the connection
                        close_connection_ = true;
                        handler_->handle_upgrade(req, res, std::move(adaptor_));
                        return;
                    }
				}
            }

            wpp::log_info << "Request: " << boost::lexical_cast<std::string>(adaptor_.remote_endpoint()) << " " << this << " HTTP/" << parser_.http_major << "." << parser_.http_minor << ' '
             << method_name(req.method) << " " << req.url << std::endl;

            wpp::log_info << "Request headers: " << std::endl;
            for (auto &&item : req.headers) {
                wpp::log_info << "                 " << item.first << ": " << item.second << "; " << std::endl;
            }

            // make a response
            need_to_call_after_handlers_ = false;
            // if the request is not invalid
            if (!is_invalid_request)
            {
                // std::function<void()> that will handle the request goes from nullptr to a function that does nothing
                res.complete_request_handler_ = []{};
                // std::function<bool()> that tell us if the adaptor is open
                res.is_alive_helper_ = [this]()->bool{ return adaptor_.is_open(); };

                // ctx becomes a new object of the middlewares that can be called
                ctx_ = detail::context<Middlewares...>();
                // pointer to the middleware context (request)
                req.middleware_context = (void*)&ctx_;
                // boost io_service
                req.io_service = &adaptor_.get_io_service();

                // helper (call middlewares)
                detail::middleware_call_helper<0, decltype(ctx_), decltype(*middlewares_), Middlewares...>(*middlewares_, req, res, ctx_);

                // if the response is not complete yet
                if (!res.completed_)
                {
                    // std::function<void()> handler is updated with the function from the connector
                    res.complete_request_handler_ = [this]{ this->complete_request(); };
                    need_to_call_after_handlers_ = true;
                    // handle request and response in their new state
                    handler_->handle(req, res);
                    // if it's alive, keep alive to the response
                    if (add_keep_alive_)
                        res.set_header("connection", "Keep-Alive");
                }
                else
                {
                    // if the response is completed...
                    complete_request();
                }
            }
            else
            {
                // if the request is invalid
                complete_request();
            }
        }

        // if response is complete or invalid, we complete it
        void complete_request()
        {
            // response to the request of that url with response code res.code
            wpp::log_info << "Response: " << this << ' ' << req_.raw_url << ' ' << res.code << ' ' << close_connection_ << std::endl;

            wpp::log_info << "Response headers: " << std::endl;
            for (auto &&item : res.headers) {
                wpp::log_info << "                 " << item.first << ": " << item.second << "; " << std::endl;
            }


            // if we need to call after handlers (that is, response is not completed)
            if (need_to_call_after_handlers_)
            {
                need_to_call_after_handlers_ = false;

                // call all after_handler of middlewares
                detail::after_handlers_call_helper<
                    ((int)sizeof...(Middlewares)-1),
                    decltype(ctx_),
                    decltype(*middlewares_)>
                (*middlewares_, ctx_, req_, res);
            }

            //auto self = this->shared_from_this();
            res.complete_request_handler_ = nullptr;

            // if the adaptor is not open anymore, we cancel
            if (!adaptor_.is_open())
            {
                //log_debug << this << " delete (socket is closed) " << is_reading << ' ' << is_writing;
                //delete this;
                return;
            }

            // possible statusCodes
            static std::unordered_map<int, std::string> statusCodes = {
                {200, "HTTP/1.1 200 OK\r\n"},
                {201, "HTTP/1.1 201 Created\r\n"},
                {202, "HTTP/1.1 202 Accepted\r\n"},
                {204, "HTTP/1.1 204 No Content\r\n"},

                {300, "HTTP/1.1 300 Multiple Choices\r\n"},
                {301, "HTTP/1.1 301 Moved Permanently\r\n"},
                {302, "HTTP/1.1 302 Moved Temporarily\r\n"},
                {304, "HTTP/1.1 304 Not Modified\r\n"},

                {400, "HTTP/1.1 400 Bad Request\r\n"},
                {401, "HTTP/1.1 401 Unauthorized\r\n"},
                {403, "HTTP/1.1 403 Forbidden\r\n"},
                {404, "HTTP/1.1 404 Not Found\r\n"},

                {500, "HTTP/1.1 500 Internal Server Error\r\n"},
                {501, "HTTP/1.1 501 Not Implemented\r\n"},
                {502, "HTTP/1.1 502 Bad Gateway\r\n"},
                {503, "HTTP/1.1 503 Service Unavailable\r\n"},
            };

            static std::string separator = ": ";
            static std::string crlf = "\r\n";

            // define buffers
            buffers_.clear();
            buffers_.reserve(4*(res.headers.size()+5)+3);

            // if response is json
            if (res.body.empty() && res.json_value.is_object())
            {
                // we dump the json into the body
                res.body = res.json_value.dump();
            }

            // is response code is not in the list of statusCodes
            if (!statusCodes.count(res.code))
                // we change the code to 500
                res.code = 500;
            {
                auto& status = statusCodes.find(res.code)->second;
                buffers_.emplace_back(status.data(), status.size());
            }

            // if response if more than 400 (problems) and there is no body
            if (res.code >= 400 && res.body.empty())
                // body becomes the string from the status code
                res.body = statusCodes[res.code].substr(9);

            // for each response header
            for(auto& kv : res.headers)
            {
                // we put it in the buffers
                buffers_.emplace_back(kv.first.data(), kv.first.size());
                buffers_.emplace_back(separator.data(), separator.size());
                buffers_.emplace_back(kv.second.data(), kv.second.size());
                buffers_.emplace_back(crlf.data(), crlf.size());

            }

            // if there is no header "content-length"
            if (!res.headers.count("content-length"))
            {
                // we measure it and insert it
                content_length_ = std::to_string(res.body.size());
                static std::string content_length_tag = "Content-Length: ";
                buffers_.emplace_back(content_length_tag.data(), content_length_tag.size());
                buffers_.emplace_back(content_length_.data(), content_length_.size());
                buffers_.emplace_back(crlf.data(), crlf.size());
                wpp::log_info << "                 " << content_length_tag << content_length_ << std::endl ;
            }

            // if there is no header "server"
            if (!res.headers.count("server"))
            {
                // we find include the server name
                static std::string server_tag = "Server: ";
                buffers_.emplace_back(server_tag.data(), server_tag.size());
                buffers_.emplace_back(server_name_.data(), server_name_.size());
                buffers_.emplace_back(crlf.data(), crlf.size());
                wpp::log_info << "                 " << server_tag << server_name_ << std::endl ;
            }

            // is there is no header "date"
            if (!res.headers.count("date"))
            {
                // we include the date
                static std::string date_tag = "Date: ";
                date_str_ = get_cached_date_str();
                buffers_.emplace_back(date_tag.data(), date_tag.size());
                buffers_.emplace_back(date_str_.data(), date_str_.size());
                buffers_.emplace_back(crlf.data(), crlf.size());
                wpp::log_info << "                 " << date_tag << date_str_ << std::endl ;
            }

            // if we want to keep the connection alive,
            if (add_keep_alive_)
            {
                // we insert the header to do that
                static std::string keep_alive_tag = "Connection: Keep-Alive";
                buffers_.emplace_back(keep_alive_tag.data(), keep_alive_tag.size());
                buffers_.emplace_back(crlf.data(), crlf.size());
                wpp::log_info << "                 " << keep_alive_tag << std::endl ;
            }

            // insert a new line break
            buffers_.emplace_back(crlf.data(), crlf.size());
            // make a copy of the old response body
            res_body_copy_.swap(res.body);
            // emplace that copy at the buffer
            buffers_.emplace_back(res_body_copy_.data(), res_body_copy_.size());

            // write response back to whoever
            // asked for it
            do_write();

            // if we needed to read after complete
            if (need_to_start_read_after_complete_)
            {
                // we don't need anymore
                need_to_start_read_after_complete_ = false;
                // set timeout to start reading
                start_deadline();
                // start reading
                do_read();
            }
        }

    private:
        // read from the request
        void do_read()
        {
            //auto self = this->shared_from_this();
            is_reading = true;
            adaptor_.socket().async_read_some(boost::asio::buffer(buffer_),
                [this](const boost::system::error_code& ec, std::size_t bytes_transferred)
                {
                    bool error_while_reading = true;
                    if (!ec)
                    {
                        bool ret = parser_.feed(buffer_.data(), bytes_transferred);
                        if (ret && adaptor_.is_open())
                        {
                            error_while_reading = false;
                        }
                    }

                    if (error_while_reading)
                    {
                        cancel_deadline_timer();
                        parser_.done();
                        adaptor_.close();
                        is_reading = false;
                        log_debug << this << " from read(1)" << std::endl;
                        check_destroy();
                    }
                    else if (close_connection_)
                    {
                        cancel_deadline_timer();
                        parser_.done();
                        is_reading = false;
                        check_destroy();
                        // adaptor will close after write
                    }
                    else if (!need_to_call_after_handlers_)
                    {
                        start_deadline();
                        do_read();
                    }
                    else
                    {
                        // res will be completed later by user
                        need_to_start_read_after_complete_ = true;
                    }
                });
        }

        // write the response back to who requested it
        void do_write()
        {
            //auto self = this->shared_from_this();
            is_writing = true;
            boost::asio::async_write(adaptor_.socket(), buffers_,
                [&](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/)
                {
                    is_writing = false;
                    res.clear();
                    res_body_copy_.clear();
                    if (!ec)
                    {
                        if (close_connection_)
                        {
                            adaptor_.close();
                            log_debug << this << " from write(1)" << std::endl;
                            check_destroy();
                        }
                    }
                    else
                    {
                        log_debug << this << " from write(2)" << std::endl;
                        check_destroy();
                    }
                });
        }

        void check_destroy()
        {
            log_debug << this << " is_reading " << is_reading << " is_writing " << is_writing << std::endl;
            if (!is_reading && !is_writing)
            {
                log_debug << this << " delete (idle) " << std::endl;
                delete this;
            }
        }

        void cancel_deadline_timer()
        {
            log_debug << this << " timer cancelled: " << timer_cancel_key_.first << ' ' << timer_cancel_key_.second << std::endl;
            timer_queue.cancel(timer_cancel_key_);
        }

        // start to count the timeout
        void start_deadline(/*int timeout = 5*/)
        {
            cancel_deadline_timer();

            timer_cancel_key_ = timer_queue.add([this]
            {
                if (!adaptor_.is_open())
                {
                    return;
                }
                adaptor_.close();
            });
            log_debug << this << " timer added: " << timer_cancel_key_.first << ' ' << timer_cancel_key_.second << std::endl;
        }

    private:
        Adaptor adaptor_;
        Handler* handler_;

        boost::array<char, 4096> buffer_;

        HTTPParser<Connection> parser_;
        request req_;
        response res;

        bool close_connection_ = false;

        const std::string& server_name_;
        std::vector<boost::asio::const_buffer> buffers_;

        std::string content_length_;
        std::string date_str_;
        std::string res_body_copy_;

        //boost::asio::deadline_timer deadline_;
        detail::dumb_timer_queue::key timer_cancel_key_;

        bool is_reading{};
        bool is_writing{};
        bool need_to_call_after_handlers_{};
        bool need_to_start_read_after_complete_{};
        bool add_keep_alive_{};

        std::tuple<Middlewares...>* middlewares_;
        detail::context<Middlewares...> ctx_;

        std::function<std::string()>& get_cached_date_str;
        detail::dumb_timer_queue& timer_queue;
    };

}
