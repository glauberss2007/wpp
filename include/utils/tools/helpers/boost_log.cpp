// https://theboostcpplibraries.com/boost.accumulators
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/utility/empty_deleter.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::log;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", int)

bool only_warnings(const attribute_value_set &set)
{
    return set["Severity"].extract<int>() > 0;
}

void severity_and_message(const record_view &view, formatting_ostream &os)
{
    os << view.attribute_values()["Severity"].extract<int>() << ": " <<
       view.attribute_values()["Message"].extract<std::string>();
}

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Back-end, front-end, core, and logger"
              << termcolor::reset << std::endl;
    {
        typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
        boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

        boost::shared_ptr<std::ostream> stream{&std::clog,
                                               boost::empty_deleter{}};
        sink->locked_backend()->add_stream(stream);

        core::get()->add_sink(sink);

        sources::logger lg;

        BOOST_LOG(lg) << "note";
        sink->flush();
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::sources::severity_logger with a filter"
              << termcolor::reset << std::endl;
    {
        typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
        boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

        boost::shared_ptr<std::ostream> stream{&std::clog,
                                               boost::empty_deleter{}};
        sink->locked_backend()->add_stream(stream);
        sink->set_filter(&only_warnings);

        core::get()->add_sink(sink);

        sources::severity_logger<int> lg;

        BOOST_LOG(lg) << "note";
        BOOST_LOG_SEV(lg, 0) << "another note";
        BOOST_LOG_SEV(lg, 1) << "warning";
        sink->flush();
    }

    std::cout << termcolor::bold << termcolor::underline << "Changing the format of a log entry with set_formatter()" << termcolor::reset << std::endl;
    {
        typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
        boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

        boost::shared_ptr<std::ostream> stream{&std::clog,
                                               boost::empty_deleter{}};
        sink->locked_backend()->add_stream(stream);
        sink->set_formatter(&severity_and_message);

        core::get()->add_sink(sink);

        sources::severity_logger<int> lg;

        BOOST_LOG_SEV(lg, 0) << "note";
        BOOST_LOG_SEV(lg, 1) << "warning";
        sink->flush();
    }

    std::cout << termcolor::bold << termcolor::underline << "Filtering log entries and formatting them with lambda functions" << termcolor::reset << std::endl;
    {
        typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
        boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

        boost::shared_ptr<std::ostream> stream{&std::clog,
                                               boost::empty_deleter{}};
        sink->locked_backend()->add_stream(stream);
        sink->set_filter(expressions::attr<int>("Severity") > 0);
        sink->set_formatter(expressions::stream <<
                                                expressions::attr<int>("Severity") << ": " << expressions::smessage);

        core::get()->add_sink(sink);

        sources::severity_logger<int> lg;

        BOOST_LOG_SEV(lg, 0) << "note";
        BOOST_LOG_SEV(lg, 1) << "warning";
        BOOST_LOG_SEV(lg, 2) << "error";
        sink->flush();
    }

    std::cout << termcolor::bold << termcolor::underline << "" << termcolor::reset << std::endl;
    {
        typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
        boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

        boost::shared_ptr<std::ostream> stream{&std::clog,
                                               boost::empty_deleter{}};
        sink->locked_backend()->add_stream(stream);
        sink->set_filter(severity > 0);
        sink->set_formatter(expressions::stream << severity << ": " <<
                                                expressions::smessage);

        core::get()->add_sink(sink);

        sources::severity_logger<int> lg;

        BOOST_LOG_SEV(lg, 0) << "note";
        BOOST_LOG_SEV(lg, 1) << "warning";
        BOOST_LOG_SEV(lg, 2) << "error";
        sink->flush();
    }
}
