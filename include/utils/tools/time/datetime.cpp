#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <string>
#include <vector>
#include <locale>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;

int main()
{
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Calendar Dates" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Creating a date with boost::gregorian::date" << termcolor::reset << std::endl;
    {
        boost::gregorian::date d{2014, 1, 31};
        std::cout << "d.year(): " << d.year() << '\n';
        std::cout << "d.month(): " << d.month() << '\n';
        std::cout << "d.day(): " << d.day() << '\n';
        std::cout << "d.day_of_week(): " << d.day_of_week() << '\n';
        std::cout << "d.end_of_month(): " << d.end_of_month() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Getting a date from a clock or a string" << termcolor::reset << std::endl;
    {
        date d = day_clock::universal_day();
        std::cout << "d.year(): " << d.year() << '\n';
        std::cout << "d.month(): " << d.month() << '\n';
        std::cout << "d.day(): " << d.day() << '\n';

        d = date_from_iso_string("20140131");
        std::cout << "d.year(): " << d.year() << '\n';
        std::cout << "d.month(): " << d.month() << '\n';
        std::cout << "d.day(): " << d.day() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::gregorian::date_duration" << termcolor::reset << std::endl;
    {
        date d1{2014, 1, 31};
        date d2{2014, 2, 28};
        date_duration dd = d2 - d1;
        std::cout << "dd.days(): " << dd.days() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Specialized durations" << termcolor::reset << std::endl;
    {
        date_duration dd{4};
        std::cout << "dd.days(): " << dd.days() << '\n';
        weeks ws{4};
        std::cout << "ws.days(): " << ws.days() << '\n';
        months ms{4};
        std::cout << "ms.number_of_months(): " << ms.number_of_months() << '\n';
        years ys{4};
        std::cout << "ys.number_of_years(): " << ys.number_of_years() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Processing specialized durations" << termcolor::reset << std::endl;
    {
        date d{2014, 1, 31};
        months ms{1};
        date d2 = d + ms;
        std::cout << "d2: " << d2 << '\n';
        date d3 = d2 - ms;
        std::cout << "d3: " << d3 << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Surprises when processing specialized durations" << termcolor::reset << std::endl;
    {
        date d{2014, 1, 30};
        months ms{1};
        date d2 = d + ms;
        std::cout << "d2: " << d2 << '\n';
        date d3 = d2 - ms;
        std::cout << "d3: " << d3 << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::gregorian::date_period" << termcolor::reset << std::endl;
    {
        date d1{2014, 1, 1};
        date d2{2014, 2, 28};
        date_period dp{d1, d2};
        date_duration dd = dp.length();
        std::cout << "dd.days(): " << dd.days() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Testing whether a period contains dates" << termcolor::reset << std::endl;
    {
        date d1{2014, 1, 1};
        date d2{2014, 2, 28};
        date_period dp{d1, d2};
        std::cout.setf(std::ios::boolalpha);
        std::cout << "dp.contains(d1): " << dp.contains(d1) << '\n';
        std::cout << "dp.contains(d2): " << dp.contains(d2) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Iterating over dates" << termcolor::reset << std::endl;
    {
        gregorian::date d{2014, 5, 12};
        gregorian::day_iterator it{d};
        std::cout << "*++it: " << *++it << '\n';
        std::cout << "date_time::next_weekday(*it,gregorian::greg_weekday(date_time::Friday)): "
                  << date_time::next_weekday(*it, gregorian::greg_weekday(date_time::Friday)) << '\n';
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Location-independent Times" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::posix_time::ptime" << termcolor::reset << std::endl;
    {
        ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
        date d = pt.date();
        std::cout << "d: " << d << '\n';
        time_duration td = pt.time_of_day();
        std::cout << "td: " << td << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Creating a timepoint with a clock or a string" << termcolor::reset << std::endl;
    {
        ptime pt = second_clock::universal_time();
        std::cout << "pt.date(): " << pt.date() << '\n';
        std::cout << "pt.time_of_day(): " << pt.time_of_day() << '\n';

        pt = from_iso_string("20140512T120000");
        std::cout << "pt.date(): " << pt.date() << '\n';
        std::cout << "pt.time_of_day(): " << pt.time_of_day() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::posix_time::time_duration" << termcolor::reset << std::endl;
    {
        time_duration td{16, 30, 0};
        std::cout << "td.hours(): " << td.hours() << '\n';
        std::cout << "td.minutes(): " << td.minutes() << '\n';
        std::cout << "td.seconds(): " << td.seconds() << '\n';
        std::cout << "td.total_seconds(): " << td.total_seconds() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Processing timepoints" << termcolor::reset << std::endl;
    {
        ptime pt1{date{2014, 5, 12}, time_duration{12, 0, 0}};
        ptime pt2{date{2014, 5, 12}, time_duration{18, 30, 0}};
        time_duration td = pt2 - pt1;
        std::cout << "td.hours(): " << td.hours() << '\n';
        std::cout << "td.minutes(): " << td.minutes() << '\n';
        std::cout << "td.seconds(): " << td.seconds() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Processing time durations" << termcolor::reset << std::endl;
    {
        ptime pt1{date{2014, 5, 12}, time_duration{12, 0, 0}};
        time_duration td{6, 30, 0};
        ptime pt2 = pt1 + td;
        std::cout << "pt2.time_of_day(): " << pt2.time_of_day() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::posix_time::time_period" << termcolor::reset << std::endl;
    {
        ptime pt1{date{2014, 5, 12}, time_duration{12, 0, 0}};
        ptime pt2{date{2014, 5, 12}, time_duration{18, 30, 0}};
        time_period tp{pt1, pt2};
        std::cout.setf(std::ios::boolalpha);
        std::cout << "tp.contains(pt1): " << tp.contains(pt1) << '\n';
        std::cout << "tp.contains(pt2): " << tp.contains(pt2) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Iterating over points in time" << termcolor::reset << std::endl;
    {
        ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
        time_iterator it{pt, time_duration{6, 30, 0}};
        std::cout << "*++it: " << *++it << '\n';
        std::cout << "*++it: " << *++it << '\n';
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Location-dependent Times" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::local_time::local_date_time" << termcolor::reset << std::endl;
    {
        time_zone_ptr tz{new posix_time_zone{"CET+1"}};
        ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
        local_date_time dt{pt, tz};
        std::cout << "dt.utc_time(): " << dt.utc_time() << '\n';
        std::cout << "dt: " << dt << '\n';
        std::cout << "dt.local_time(): " << dt.local_time() << '\n';
        std::cout << "dt.zone_name(): " << dt.zone_name() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Location-dependent points in time and different time zones" << termcolor::reset << std::endl;
    {
        time_zone_ptr tz{new posix_time_zone{"CET+1"}};

        ptime pt{date{2014, 5, 12}, time_duration{12, 0, 0}};
        local_date_time dt{pt, tz};
        std::cout << "dt.local_time(): " << dt.local_time() << '\n';

        time_zone_ptr tz2{new posix_time_zone{"EET+2"}};
        std::cout << "dt.local_time_in(tz2).local_time(): " << dt.local_time_in(tz2).local_time() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::local_time::local_time_period" << termcolor::reset << std::endl;
    {
        time_zone_ptr tz{new posix_time_zone{"CET+0"}};

        ptime pt1{date{2014, 12, 5}, time_duration{12, 0, 0}};
        local_date_time dt1{pt1, tz};

        ptime pt2{date{2014, 12, 5}, time_duration{18, 0, 0}};
        local_date_time dt2{pt2, tz};

        local_time_period tp{dt1, dt2};

        std::cout.setf(std::ios::boolalpha);
        std::cout << "tp.contains(dt1): " << tp.contains(dt1) << '\n';
        std::cout << "tp.contains(dt2): " << tp.contains(dt2) << '\n';
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Formatted Input and Output" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "A user-defined format for a date" << termcolor::reset << std::endl;
    {
        date d{2014, 5, 12};
        date_facet *df = new date_facet{"%A, %d %B %Y"};
        std::cout.imbue(std::locale{std::cout.getloc(), df});
        std::cout << "d: " << d << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Changing names of weekdays and months" << termcolor::reset << std::endl;
    {
        std::locale::global(std::locale{"de_DE"});
        // std::locale::global(std::locale{"German"}); // on windows
        std::string months[12]{"Januar", "Februar", "M\xe4rz", "April",
                               "Mai", "Juni", "Juli", "August", "September", "Oktober",
                               "November", "Dezember"};
        std::string weekdays[7]{"Sonntag", "Montag", "Dienstag",
                                "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
        date d{2014, 5, 12};
        date_facet *df = new date_facet{"%A, %d. %B %Y"};
        df->long_month_names(std::vector<std::string>{months, months + 12});
        df->long_weekday_names(std::vector<std::string>{weekdays,
                                                        weekdays + 7});
        std::cout.imbue(std::locale{std::cout.getloc(), df});
        std::cout << d << '\n';
    }

    return 0;
}
