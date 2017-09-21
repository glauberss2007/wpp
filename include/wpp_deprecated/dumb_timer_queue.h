#pragma once

#include <boost/asio.hpp>
#include <deque>
#include <functional>
#include <chrono>
#include <thread>

#include "logging.h"

namespace wpp
{
    namespace detail 
    {
        // fast timer queue for fixed tick value.
        class dumb_timer_queue
        {
        public:
            using key = std::pair<dumb_timer_queue*, int>;

            // set that key's function from the queue
            void cancel(key& k)
            {
                // address of a timer_queue
                dumb_timer_queue* self = k.first;
                // erase the keys pointer to a time queue
                k.first = nullptr;
                // if original pointer was null (didn't point to any queue): return
                if (!self)
                    return;

                // else: get index of this key by the second
                unsigned int index = (unsigned int)(k.second - self->step_);
                // make the function relative to this key null on the deck
                if (index < self->dq_.size())
                    self->dq_[index].second = nullptr;
            }

            // add a function to the queue
            key add(std::function<void()> f)
            {
                // create pair of time and function in place
                dq_.emplace_back(std::chrono::steady_clock::now(), std::move(f));
                // position of the new function
                int ret = step_+dq_.size()-1;
                // print timer and position
                log_debug << "Timer add inside: " << this << ' ' << ret  << std::endl;
                // return a key with a pointer to this queuer and the position of the function
                return {this, ret};
            }

            //
            void process()
            {
                // if io_service is not initialized yet: return
                if (!io_service_)
                    return;

                // get time
                auto now = std::chrono::steady_clock::now();
                // get first in the queue
                while(!dq_.empty())
                {
                    auto& x = dq_.front();
                    // if 5 seconds haven't passed for first in line, we break
                    if (now - x.first < std::chrono::seconds(tick))
                        break;
                    // else, if the function is valid, we execute it
                    if (x.second)
                    {
                        log_debug << "Timer call: " << this << ' ' << step_ << std::endl;
                        // We know that timer handlers are very simple currently; call here
                        x.second();
                    }
                    // take executed function out of the queue
                    dq_.pop_front();
                    // one more executed so indexes have +1
                    step_++;
                }
        }

        void set_io_service(boost::asio::io_service& io_service)
        {
            // initialize the service object
            io_service_ = &io_service;
        }

        dumb_timer_queue() noexcept
        {
        }

        private:

            // 5 seconds between calling each function
            int tick{5};
            // I/O service object (Every program based on Boost.Asio uses)
            boost::asio::io_service* io_service_{};
            // Double ended queue of functions and their times
            std::deque<std::pair<decltype(std::chrono::steady_clock::now()), std::function<void()>>> dq_;
            // initial step size from the first position in deque == 0
            int step_{};
        };
    }
}
