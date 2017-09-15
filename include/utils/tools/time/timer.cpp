#include <boost/timer/timer.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"
#include <cmath>

using namespace boost::timer;

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Measuring time with boost::timer::cpu_timer"
              << termcolor::reset << std::endl;
    {
        cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }
        std::cout << "timer.format(): " << timer.format() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Stopping and resuming timers" << termcolor::reset
              << std::endl;
    {
        cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }
        std::cout << "timer.format(): " << timer.format() << '\n';

        timer.stop();

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }
        std::cout << "timer.format(): " << timer.format() << '\n';

        timer.resume();

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }
        std::cout << "timer.format(): " << timer.format() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Getting wall and CPU time as a tuple" << termcolor::reset
              << std::endl;
    {
        cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }

        cpu_times times = timer.elapsed();
        std::cout << "times.wall: " << times.wall << '\n';
        std::cout << "times.user: " << times.user << '\n';
        std::cout << "times.system: " << times.system << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Measuring times automatically with boost::timer::auto_cpu_timer" << termcolor::reset << std::endl;
    {
        auto_cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            std::pow(1.234, i);
        }
    }

    return 0;
}
