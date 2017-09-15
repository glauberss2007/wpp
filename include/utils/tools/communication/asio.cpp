#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <chrono>
#include <thread>
#include <functional>

#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
std::array<char, 4096> bytes;

tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
std::string data;



int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::asio::steady_timer" << termcolor::reset
              << std::endl;
    {
        io_service ioservice;

        steady_timer timer{ioservice, std::chrono::seconds{3}};
        timer.async_wait([](const boost::system::error_code &ec) { std::cout << "3 sec\n"; });

        ioservice.run();
    }

    std::cout << termcolor::bold << termcolor::underline << "Two asynchronous operations with boost::asio::steady_timer"
              << termcolor::reset << std::endl;
    {
        io_service ioservice;

        steady_timer timer1{ioservice, std::chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { std::cout << "3 sec\n"; });

        steady_timer timer2{ioservice, std::chrono::seconds{4}};
        timer2.async_wait([](const boost::system::error_code &ec) { std::cout << "4 sec\n"; });

        ioservice.run();
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Two threads for the I/O service object to execute handlers concurrently" << termcolor::reset
              << std::endl;
    {
        io_service ioservice;

        steady_timer timer1{ioservice, std::chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { std::cout << "3 sec\n"; });

        steady_timer timer2{ioservice, std::chrono::seconds{4}};
        timer2.async_wait([](const boost::system::error_code &ec) { std::cout << "4 sec\n"; });

        // run() is called on the only I/O service object in each thread
        // I/O service object to use both threads to execute handlers
        // Calling run() repeatedly on a single I/O service object is the recommended method to make a program based on Boost.Asio more scalable.
        std::thread thread1{[&ioservice]() { ioservice.run(); }};
        std::thread thread2{[&ioservice]() { ioservice.run(); }};
        thread1.join();
        thread2.join();
    }

    std::cout << termcolor::bold << termcolor::underline
              << "One thread for each of two I/O service objects to execute handlers concurrently" << termcolor::reset
              << std::endl;
    {
        // However, instead of providing several threads to one I/O service object, you could also create multiple I/O service objects.


        io_service ioservice1;
        io_service ioservice2;

        steady_timer timer1{ioservice1, std::chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { std::cout << "3 sec\n"; });

        steady_timer timer2{ioservice2, std::chrono::seconds{3}};
        timer2.async_wait([](const boost::system::error_code &ec) { std::cout << "3 sec\n"; });

        std::thread thread1{[&ioservice1]() { ioservice1.run(); }};
        std::thread thread2{[&ioservice2]() { ioservice2.run(); }};
        thread1.join();
        thread2.join();
    }

    using namespace boost::asio;
    using namespace boost::asio::ip;

    std::cout << termcolor::bold << termcolor::underline << "A web client with boost::asio::ip::tcp::socket"
              << termcolor::reset << std::endl;
    {
        std::cout
                << "Even though Boost.Asio can process any kind of data asynchronously, it is mainly used for network programming"
                << std::endl;

        std::function<void(const boost::system::error_code,std::size_t)> read_handler;
        read_handler = [&read_handler](const boost::system::error_code &ec,
                               std::size_t bytes_transferred) {
            if (!ec) {
                std::cout.write(bytes.data(), bytes_transferred);
                tcp_socket.async_read_some(buffer(bytes), read_handler);
            }
        };

        auto connect_handler = [&read_handler](const boost::system::error_code &ec) {
            if (!ec) {
                std::string r =
                        "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
                write(tcp_socket, buffer(r));
                tcp_socket.async_read_some(buffer(bytes), read_handler);
            }
        };

        auto resolve_handler = [&connect_handler](const boost::system::error_code &ec,
                                  tcp::resolver::iterator it) {
            if (!ec) {
                tcp_socket.async_connect(*it, connect_handler);
            }
        };

        tcp::resolver::query q{"theboostcpplibraries.com", "80"};
        resolv.async_resolve(q, resolve_handler);
        ioservice.run();
    }

    std::cout << termcolor::bold << termcolor::underline << "A time server with boost::asio::ip::tcp::acceptor"
              << termcolor::reset << std::endl;
    {

        std::function<void(const boost::system::error_code,std::size_t)> write_handler;
        write_handler = [&write_handler](const boost::system::error_code &ec,std::size_t bytes_transferred) {
            if (!ec) {
                tcp_socket.shutdown(tcp::socket::shutdown_send);
            }
        };

        std::function<void(const boost::system::error_code)> accept_handler;
        accept_handler = [&write_handler](const boost::system::error_code &ec) {
            if (!ec) {
                std::time_t now = std::time(nullptr);
                data = std::ctime(&now);
                async_write(tcp_socket, buffer(data), write_handler);
            }
        };

        tcp_acceptor.listen();
        tcp_acceptor.async_accept(tcp_socket, accept_handler);
        ioservice.run();
    }
}