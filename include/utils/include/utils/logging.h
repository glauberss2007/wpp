#pragma once

#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "../termcolor/termcolor.hpp"

namespace logging {

    using namespace termcolor;

    enum class color {none, red, green, yellow, blue, magenta, cyan, grey, black};

    enum log_level { debug = 0, info, warning, error, critical };

    ///////////////////////////////////////////////////////////////
    //                  From color enum to stream                //
    ///////////////////////////////////////////////////////////////
    inline std::ostream &
        stream_text_properties(std::ostream &stream, bool bold, bool underline, color color_, color background_) {
            if (bold) {
                stream << termcolor::bold;
            }
            if (underline) {
                stream << termcolor::underline;
            }
            if (color_ != color::none) {
                switch (color_) {
                    case (color::blue):
                        stream << termcolor::blue;
                        break;
                    case (color::cyan):
                        stream << termcolor::cyan;
                        break;
                    case (color::green):
                        stream << termcolor::green;
                        break;
                    case (color::black):
                        stream << termcolor::grey;
                        break;
                    case (color::magenta):
                        stream << termcolor::magenta;
                        break;
                    case (color::red):
                        stream << termcolor::red;
                        break;
                    case (color::grey):
                        stream << termcolor::white;
                        break;
                    case (color::yellow):
                        stream << termcolor::yellow;
                        break;
                    case (color::none):
                        break;
                }
            }
            if (background_ != color::none) {
                switch (background_) {
                    case (color::blue):
                        stream << termcolor::on_blue;
                        break;
                    case (color::cyan):
                        stream << termcolor::on_cyan;
                        break;
                    case (color::green):
                        stream << termcolor::on_green;
                        break;
                    case (color::black):
                        stream << termcolor::on_grey;
                        break;
                    case (color::magenta):
                        stream << termcolor::on_magenta;
                        break;
                    case (color::red):
                        stream << termcolor::on_red;
                        break;
                    case (color::grey):
                        stream << termcolor::on_white;
                        break;
                    case (color::yellow):
                        stream << termcolor::on_yellow;
                        break;
                    case (color::none):
                        break;
                }
            }
            return stream;
        }
    ///////////////////////////////////////////////////////////////
    //                 STATIC DEFAULT LOG LEVEL                  //
    ///////////////////////////////////////////////////////////////
    // inline log_level default_log_level = {log_level::info};
    template <typename T>
    struct default_log_level_holder {
        static T default_level;
    };
    template <typename T> T default_log_level_holder<T>::default_level{log_level::info};

    class default_log_level : public default_log_level_holder<bool> {};

    //inline bool enable_logging = {wpp_settings::enable_logging};
    template <typename T>
    struct enable_logging_holder {
        static T enable;
    };
    template <typename T> T enable_logging_holder<T>::enable{true};

    class enable_logging : public enable_logging_holder<bool> {};

    // level defaults
    struct level_default {
        log_level level;
        std::string prefix;
        color text_color;
        color background_color;
        bool time;
        bool bold;
        bool underline;
    };

    template <typename T>
    struct level_default_settings_holder {
        static T settings;
        static level_default get(log_level rl);
    };

    template <typename T> T level_default_settings_holder<T>::settings{
        {log_level::debug   ,"DEBUG   ",color::black,color::none,true,false,false},
        {log_level::info    ,"INFO    ",color::blue,color::none,true,false,false},
        {log_level::warning ,"WARNING ",color::none,color::yellow,true,true,false},
        {log_level::error   ,"ERROR   ",color::red,color::none,true,true,true},
        {log_level::critical,"CRITICAL",color::yellow,color::red,true,true,true}};

    template <typename T> level_default level_default_settings_holder<T>::get(log_level rl){
        return *std::find_if(settings.begin(),settings.end(),[&rl](level_default ll){return ll.level == rl;});
    };

    struct level_default_settings : public level_default_settings_holder<std::vector<level_default>> {};

    ///////////////////////////////////////////////////////////////
    //          LOGGER CLASS (creates new custom loggers)        //
    ///////////////////////////////////////////////////////////////
    class logger
            : public std::ostream {
        public:
            // Other constructors could specify filename, etc
            // just remember to pass whatever you need to logger_buffer
            logger() : std::ostream(new logger_buffer()) {}

            logger(log_level level) : std::ostream(new logger_buffer(level)) {}

            logger(log_level level, std::string prefix) : std::ostream(new logger_buffer(level, prefix)) {}

            logger(log_level level, std::string prefix, bool time, color text_color = color::none, color background_color = color::none, bool bold = false, bool underline = false) : std::ostream(new logger_buffer(level, prefix, time, text_color, background_color, bold, underline)) {}

            ~logger() { delete rdbuf(); }

        private:
            class logger_buffer
                    : public std::stringbuf {
                public:
                    logger_buffer() : prefix_("DEBUG   "), level_(log_level::debug) {}

                    logger_buffer(log_level level) : level_(level), prefix_(level_default_settings::get(level).prefix), time_(level_default_settings::get(level).time), text_color_(level_default_settings::get(level).text_color), background_color_(level_default_settings::get(level).background_color), bold_(level_default_settings::get(level).bold), underline_(level_default_settings::get(level).underline) {}

                    logger_buffer(log_level level, std::string prefix) : level_(level), prefix_(prefix), time_(level_default_settings::get(level).time), text_color_(level_default_settings::get(level).text_color), background_color_(level_default_settings::get(level).background_color), bold_(level_default_settings::get(level).bold), underline_(level_default_settings::get(level).underline) {}

                    logger_buffer(log_level level, std::string prefix, bool time, color text_color = color::none, color background_color = color::none, bool bold = false, bool underline = false) : level_(level), prefix_(prefix), time_(time), text_color_(text_color), background_color_(background_color), bold_(bold), underline_(underline) {}

                    ~logger_buffer() {} // pubsync();

                    int sync() {
                        if (enable_logging::enable) {
                            if ((int) level_ >= (int) default_log_level::default_level) {
                                stream_text_properties(std::cout,bold_,underline_,text_color_,background_color_);
                                if (time_){
                                    std::cout << "(" << timestamp() << ") ";
                                }
                                std::cout << "[" << prefix_ << "] " << str();
                                std::cout << termcolor::reset;
                                str("");
                                return std::cout ? 0 : -1;
                            } else {
                                return std::cout ? 0 : -1;
                            }
                        } else {
                            return std::cout ? 0 : -1;
                        }
                    }

                private:
                    std::string prefix_;
                    log_level level_;
                    color text_color_;
                    color background_color_;
                    bool time_;
                    bool bold_;
                    bool underline_;

                    static std::string timestamp() {
                        char date[32];
                        time_t t = time(0);
                        tm my_tm;
                        #if defined(_MSC_VER)
                        gmtime_s(&my_tm, &t);
                        #else
                        gmtime_r(&t, &my_tm);
                        #endif
                        size_t sz = strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &my_tm);
                        return std::string(date, date + sz);
                    }


            };

    };

    ///////////////////////////////////////////////////////////////
    //                     Default Loggers                       //
    ///////////////////////////////////////////////////////////////
    template <typename T>
    struct log_holder {
        static T critical;
        static T error;
        static T warning;
        static T info;
        static T debug;
        static T log;
    };

    template <typename T> T log_holder<T>::critical(log_level::critical);
    template <typename T> T log_holder<T>::error(log_level::error);
    template <typename T> T log_holder<T>::warning(log_level::warning);
    template <typename T> T log_holder<T>::info(log_level::info);
    template <typename T> T log_holder<T>::debug(log_level::debug);
    template <typename T> T log_holder<T>::log(default_log_level::default_level);

    struct log : public log_holder<logger> {};

}