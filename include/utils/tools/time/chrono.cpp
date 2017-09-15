#define BOOST_CHRONO_VERSION 2
#include <boost/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::chrono;


int main()
{
    std::cout << termcolor::bold << termcolor::underline << "All clocks from Boost.Chrono" << termcolor::reset << std::endl;
    {
        std::cout << system_clock::now() << '\n';
        #ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
        std::cout << steady_clock::now() << '\n';
        #endif
        std::cout << high_resolution_clock::now() << '\n';

        #ifdef BOOST_CHRONO_HAS_PROCESS_CLOCKS
        std::cout << process_real_cpu_clock::now() << '\n';
        std::cout << process_user_cpu_clock::now() << '\n';
        std::cout << process_system_cpu_clock::now() << '\n';
        std::cout << process_cpu_clock::now() << '\n';
        #endif

        #ifdef BOOST_CHRONO_HAS_THREAD_CLOCK
        std::cout << thread_clock::now() << '\n';
        #endif
    }

    std::cout << termcolor::bold << termcolor::underline << "Adding and subtracting durations using Boost.Chrono" << termcolor::reset << std::endl;
    {
        process_real_cpu_clock::time_point p = process_real_cpu_clock::now();
        std::cout << p << '\n';
        std::cout << p - nanoseconds{1} << '\n';
        std::cout << p + milliseconds{1} << '\n';
        std::cout << p + seconds{1} << '\n';
        std::cout << p + minutes{1} << '\n';
        std::cout << p + hours{1} << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Casting timepoints with boost::chrono::time_point_cast()" << termcolor::reset << std::endl;
    {
        process_real_cpu_clock::time_point p = process_real_cpu_clock::now();
        std::cout << p << '\n';
        std::cout << time_point_cast<minutes>(p) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Casting durations with boost::chrono::duration_cast()" << termcolor::reset << std::endl;
    {
        minutes m{1};
        seconds s{35};

        std::cout << m + s << '\n';
        std::cout << duration_cast<minutes>(m + s) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Rounding durations" << termcolor::reset << std::endl;
    {
        std::cout << floor<minutes>(minutes{1} + seconds{45}) << '\n';
        std::cout << round<minutes>(minutes{1} + seconds{15}) << '\n';
        std::cout << ceil<minutes>(minutes{1} + seconds{15}) << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Stream manipulators for user-defined output" << termcolor::reset << std::endl;
    {

        std::cout << symbol_format << minutes{10} << '\n';

        std::cout << symbol_format << minutes{1} + seconds{45} << '\n';

        std::cout << time_fmt(boost::chrono::timezone::local, "%H:%M:%S") <<
                  system_clock::now() << '\n';

    }

    return 0;
}
