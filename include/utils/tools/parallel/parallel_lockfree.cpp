// https://theboostcpplibraries.com/boost.lockfree
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/policies.hpp>
#include <boost/lockfree/queue.hpp>
#include <atomic>
#include <thread>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::lockfree::spsc_queue" << termcolor::reset
              << std::endl;
    {
        boost::lockfree::spsc_queue<int> q{100};
        int sum = 0;

        auto produce = [&q]() {
            for (int i = 1; i <= 100; ++i) {
                q.push(i);
            }
        };

        auto consume = [&q, &sum]() {
            int i;
            while (q.pop(i)) {
                sum += i;
            }
        };

        std::thread t1{produce};
        std::thread t2{consume};
        t1.join();
        t2.join();
        consume();
        std::cout << sum << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::lockfree::spsc_queue with boost::lockfree::capacity"
              << termcolor::reset << std::endl;
    {
        using namespace boost::lockfree;

        spsc_queue<int, capacity<100>> q;
        int sum = 0;

        auto produce = [&q]() {
            for (int i = 1; i <= 100; ++i) {
                q.push(i);
            }
        };

        auto consume = [&q, &sum]() {
            while (q.consume_one([&sum](int i) { sum += i; })) {
            }
        };

        std::thread t1{produce};
        std::thread t2{consume};
        t1.join();
        t2.join();
        q.consume_all([&sum](int i) { sum += i; });
        std::cout << sum << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << " boost::lockfree::queue with variable container size"
              << termcolor::reset << std::endl;
    {
        boost::lockfree::queue<int> q{100};
        std::atomic<int> sum{0};

        auto produce = [&q]() {
            for (int i = 1; i <= 10000; ++i) {
                q.push(i);
            }
        };

        auto consume = [&q, &sum]() {
            int i;
            while (q.pop(i)) {
                sum += i;
            }
        };

        std::thread t1{produce};
        std::thread t2{consume};
        std::thread t3{consume};
        t1.join();
        t2.join();
        t3.join();
        consume();
        std::cout << sum << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::lockfree::queue with constant container size"
              << termcolor::reset << std::endl;
    {
        using namespace boost::lockfree;

        queue<int, fixed_sized<true>> q{10000};
        std::atomic<int> sum{0};

        auto produce = [&q]() {
            for (int i = 1; i <= 10000; ++i) {
                q.push(i);
            }
        };

        auto consume = [&q, &sum]() {
            int i;
            while (q.pop(i)) {
                sum += i;
            }
        };

        std::thread t1{produce};
        std::thread t2{consume};
        std::thread t3{consume};
        t1.join();
        t2.join();
        t3.join();
        consume();
        std::cout << sum << '\n';
    }

    return 0;
}
