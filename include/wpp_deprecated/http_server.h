#pragma once

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>
#ifdef WPP_ENABLE_SSL
#include <boost/asio/ssl.hpp>
#endif
#include <cstdint>
#include <atomic>
#include <future>
#include <vector>

#include <memory>

#include "http_connection.h"
#include "logging.h"
#include "dumb_timer_queue.h"

namespace wpp
{
    using namespace boost;
    using tcp = asio::ip::tcp;

    // the server depends on a boost adaptor and middlewares
    template <typename Handler, typename Adaptor = SocketAdaptor, typename ... Middlewares>
    class Server
    {
    public:
        // constructor
        Server(Handler* handler, std::string bindaddr, uint16_t port, std::tuple<Middlewares...>* middlewares = nullptr, uint16_t concurrency = 1, typename Adaptor::context* adaptor_ctx = nullptr)
            : acceptor_(io_service_, tcp::endpoint(boost::asio::ip::address::from_string(bindaddr), port)),
            signals_(io_service_, SIGINT, SIGTERM),
            tick_timer_(io_service_),
            handler_(handler),
            concurrency_(concurrency),
            port_(port),
            bindaddr_(bindaddr),
            middlewares_(middlewares),
            adaptor_ctx_(adaptor_ctx)
        {
        }

        // ticks
        void set_tick_function(std::chrono::milliseconds d, std::function<void()> f)
        {
            tick_interval_ = d;
            tick_function_ = f;
        }

        // runs tick function on tick
        void on_tick()
        {
            // runs the function
            tick_function_();
            // push the next tick forward in the tick timer
            tick_timer_.expires_from_now(boost::posix_time::milliseconds(tick_interval_.count()));
            // tick timer waits until next tick to run the function again
            tick_timer_.async_wait([this](const boost::system::error_code& ec)
                    {
                        if (ec)
                            return;
                        on_tick();
                    });
        }

        // run the server
        void run()
        {
            // concurrency is at least 1 thread
            if (concurrency_ < 0)
                concurrency_ = 1;

            // create one io_service for each thread
            for(int i = 0; i < concurrency_;  i++)
                io_service_pool_.emplace_back(new boost::asio::io_service());

            // one date string for each thread
            get_cached_date_str_pool_.resize(concurrency_);

            // one timer_queue for each thread
            timer_queue_pool_.resize(concurrency_);

            // create vector of functions to execute (thread pool)
            std::vector<std::future<void>> v;

            // atomic counter for the number of threads initialized
            std::atomic<int> init_count(0);

            // for each thread function
            for(uint16_t i = 0; i < concurrency_; i ++)
                // push back the initialising (asynchronous) function
                v.push_back(
                        std::async(std::launch::async, [this, i, &init_count]{

                            // thread local date string get function
                            auto last = std::chrono::steady_clock::now();

                            // update date string
                            std::string date_str;
                            auto update_date_str = [&]
                            {
                                auto last_time_t = time(0);
                                tm my_tm;

#ifdef _MSC_VER
                                gmtime_s(&my_tm, &last_time_t);
#else
                                gmtime_r(&last_time_t, &my_tm);
#endif
                                date_str.resize(100);
                                size_t date_str_sz = strftime(&date_str[0], 99, "%a, %d %b %Y %H:%M:%S GMT", &my_tm);
                                date_str.resize(date_str_sz);
                            };
                            update_date_str();

                            // create function to get date string pool
                            get_cached_date_str_pool_[i] = [&]()->std::string
                            {
                                if (std::chrono::steady_clock::now() - last >= std::chrono::seconds(1))
                                {
                                    last = std::chrono::steady_clock::now();
                                    update_date_str();
                                }
                                return date_str;
                            };

                            // initializing timer queue
                            detail::dumb_timer_queue timer_queue;
                            timer_queue_pool_[i] = &timer_queue;

                            timer_queue.set_io_service(*io_service_pool_[i]);
                            boost::asio::deadline_timer timer(*io_service_pool_[i]);
                            timer.expires_from_now(boost::posix_time::seconds(1));

                            std::function<void(const boost::system::error_code& ec)> handler;
                            handler = [&](const boost::system::error_code& ec){
                                if (ec)
                                    return;
                                timer_queue.process();
                                timer.expires_from_now(boost::posix_time::seconds(1));
                                timer.async_wait(handler);
                            };
                            timer.async_wait(handler);

                            // one more thread initialized
                            init_count ++;
                            try 
                            {
                                // run the io_service of this thread
                                io_service_pool_[i]->run();
                            } catch(std::exception& e)
                            {
                                log_error << "Worker Crash: An uncaught exception occurred: " << e.what() << std::endl;
                            }
                        }));

            // if we have the tick function, we start the timer
            if (tick_function_ && tick_interval_.count() > 0) 
            {
                tick_timer_.expires_from_now(boost::posix_time::milliseconds(tick_interval_.count()));
                tick_timer_.async_wait([this](const boost::system::error_code& ec)
                        {
                            if (ec)
                                return;
                            on_tick();
                        });
            }

            log_info << server_name_ << " server is running, local port " << port_ << std::endl;

            // initialize signals
            signals_.async_wait(
                [&](const boost::system::error_code& /*error*/, int /*signal_number*/){
                    stop();
                });

            // yield the threads
            while(concurrency_ != init_count)
                std::this_thread::yield();

            do_accept();

            // run and join
            std::thread([this]{
                io_service_.run();
                log_info << "Exiting." << std::endl;
            }).join();
        }

        // stop the server
        void stop()
        {
            // stop boost io_service
            io_service_.stop();
            // stop io_service on the threads
            for(auto& io_service:io_service_pool_)
                io_service->stop();
        }

    private:
        asio::io_service& pick_io_service()
        {
            // TODO load balancing
            roundrobin_index_++;
            if (roundrobin_index_ >= io_service_pool_.size())
                roundrobin_index_ = 0;
            return *io_service_pool_[roundrobin_index_];
        }

        void do_accept()
        {
            asio::io_service& is = pick_io_service();
            auto p = new Connection<Adaptor, Handler, Middlewares...>(
                is, handler_, server_name_, middlewares_,
                get_cached_date_str_pool_[roundrobin_index_], *timer_queue_pool_[roundrobin_index_],
                adaptor_ctx_);
            acceptor_.async_accept(p->socket(),
                [this, p, &is](boost::system::error_code ec)
                {
                    if (!ec)
                    {
                        is.post([p]
                        {
                            p->start();
                        });
                    }
                    do_accept();
                });
        }

    private:
        asio::io_service io_service_;
        std::vector<std::unique_ptr<asio::io_service>> io_service_pool_;
        std::vector<detail::dumb_timer_queue*> timer_queue_pool_;
        std::vector<std::function<std::string()>> get_cached_date_str_pool_;
        tcp::acceptor acceptor_;
        boost::asio::signal_set signals_;
        boost::asio::deadline_timer tick_timer_;

        Handler* handler_;
        uint16_t concurrency_{1};
        std::string server_name_ = "W++ Server";
        uint16_t port_;
        std::string bindaddr_;
        unsigned int roundrobin_index_{};

        std::chrono::milliseconds tick_interval_;
        std::function<void()> tick_function_;

        std::tuple<Middlewares...>* middlewares_;

#ifdef WPP_ENABLE_SSL
        bool use_ssl_{false};
        boost::asio::ssl::context ssl_context_{boost::asio::ssl::context::sslv23};
#endif
        typename Adaptor::context* adaptor_ctx_;
    };
}
