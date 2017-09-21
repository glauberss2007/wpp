#pragma once
#include <boost/asio.hpp>
#ifdef WPP_ENABLE_SSL
#include <boost/asio/ssl.hpp>
#endif
#include "settings.h"

namespace wpp
{
    using namespace boost;
    using tcp = asio::ip::tcp;

    // wrapper for a tcp::socket, already receiving the io_service
    // a socket will represent the connection to the client
    struct SocketAdaptor
    {
        // the context is used only in the SSL socket
        using context = void;
        SocketAdaptor(boost::asio::io_service& io_service, context*)
            : socket_(io_service)
        {
        }

        // get the io service
        boost::asio::io_service& get_io_service()
        {
            return socket_.get_io_service();
        }

        // get the raw socket
        tcp::socket& raw_socket()
        {
            return socket_;
        }

        // get the raw socket (in ssl sockets this function differs from raw_socket())
        tcp::socket& socket()
        {
            return socket_;
        }

        // get endpoint (server name, port, ip, protocol, etc)
        tcp::endpoint remote_endpoint()
        {
            return socket_.remote_endpoint();
        }

        // get if it is open
        bool is_open()
        {
            return socket_.is_open();
        }

        // closes it
        void close()
        {
            socket_.close();
        }

        // start a function that returns nothing with error code as parameter (usual server function)
        template <typename F> 
        void start(F f)
        {
            f(boost::system::error_code());
        }

        // raw socket
        tcp::socket socket_;
    };

#ifdef WPP_ENABLE_SSL
    // the adaptor for SSL sockets is special
    // the raw socket is now a unique_ptr<boost::asio::ssl::stream<tcp::socket>>
    // encrypted communication (the socket) goes on top of an existing stream
    struct SSLAdaptor
    {
        // used to set SSL options such as verification mode, certificate files, and so on
        using context = boost::asio::ssl::context;
        // the socket already through a stream
        using ssl_socket_t = boost::asio::ssl::stream<tcp::socket>;

        // constructor just copies data and context to socket
        SSLAdaptor(boost::asio::io_service& io_service, context* ctx)
            : ssl_socket_(new ssl_socket_t(io_service, *ctx))
        {
        }

        // return the socket (through the stream)
        boost::asio::ssl::stream<tcp::socket>& socket()
        {
            return *ssl_socket_;
        }

        // To perform socket-specific operations, such as establishing an outbound connection or accepting an incoming one, the underlying socket must first be obtained using the ssl::stream template's lowest_layer() member function
        tcp::socket::lowest_layer_type&
        raw_socket()
        {
            return ssl_socket_->lowest_layer();
        }

        // remote end point from the raw socket
        tcp::endpoint remote_endpoint()
        {
            return raw_socket().remote_endpoint();
        }

        // check raw socket is open
        bool is_open()
        {
            return raw_socket().is_open();
        }

        // close raw socket
        void close()
        {
            raw_socket().close();
        }

        // original io from raw socket
        boost::asio::io_service& get_io_service()
        {
            return raw_socket().get_io_service();
        }

        // start a function that returns nothing with error code as parameter (usual server function)
        // the function now has to go through the socket stream
        template <typename F>
        void start(F f)
        {
            ssl_socket_->async_handshake(boost::asio::ssl::stream_base::server,
                    [f](const boost::system::error_code& ec) {
                        f(ec);
                    });
        }

        // the ssl socket is special
        std::unique_ptr<boost::asio::ssl::stream<tcp::socket>> ssl_socket_;
    };
#endif
}
