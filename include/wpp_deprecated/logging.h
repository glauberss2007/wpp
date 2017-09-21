#pragma once

#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

#include "settings.h"

namespace wpp
{

    int default_log_level = {wpp_settings::wpp_log_level};
    bool enable_logging = {wpp_settings::enable_logging};

    enum log_level {debug = 0,info,warning,error,critical};

    class logger : public std::ostream {
    public:
        // Other constructors could specify filename, etc
        // just remember to pass whatever you need to logger_buffer
        logger() : std::ostream(new logger_buffer()) {}
        logger(log_level level) : std::ostream(new logger_buffer(level)) {}
        logger(std::string prefix, log_level level) : std::ostream(new logger_buffer(prefix,level)) {}
        ~logger() { delete rdbuf(); }

    private:
        class logger_buffer : public std::stringbuf {
        public:
            logger_buffer() : prefix_("DEBUG   "), level_(log_level::debug) {}
            logger_buffer(log_level level) :  level_(level) {
                    switch (level){
                        case log_level::debug:
                            prefix_ = "DEBUG   ";
                        break;
                        case log_level::info:
                            prefix_ = "INFO    ";
                        break;
                        case log_level::warning:
                            prefix_ = "WARNING ";
                        break;
                        case log_level::error:
                            prefix_ = "ERROR   ";
                        break;
                        case log_level::critical:
                            prefix_ = "CRITICAL";
                        break;
                    }
            }

            logger_buffer(std::string prefix, log_level level) : prefix_(prefix), level_(level) {}

            ~logger_buffer() { } // pubsync();

            int sync() {
                if (enable_logging) {
                    if (level_ >= default_log_level) {
                        std::cout << "(" << timestamp() << ") [" << prefix_ << "] " << str();
                        str("");
                        return std::cout?0:-1;
                    } else {
                        return std::cout?0:-1;
                    }
                } else {
                    return std::cout?0:-1;
                }
            }
        private:
            std::string prefix_;
            log_level level_;

            static std::string timestamp()
            {
                char date[32];
                time_t t = time(0);
                tm my_tm;
#if defined(_MSC_VER)
                gmtime_s(&my_tm, &t);
#else
                gmtime_r(&t, &my_tm);
#endif
                size_t sz = strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &my_tm);
                return std::string(date, date+sz);
            }
        };

    };

    logger log_critical("CRITICAL", log_level::critical);
    logger log_error("ERROR   ", log_level::error);
    logger log_warning("WARNING ", log_level::warning);
    logger log_info("INFO    ", log_level::info);
    logger log_debug("DEBUG   ", log_level::debug);
    logger log((log_level)default_log_level);

}