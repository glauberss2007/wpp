// https://theboostcpplibraries.com/boost.thread-management
#define BOOST_THREAD_PROVIDES_FUTURE

#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Creating and Managing Threads"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::thread" << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        auto thread = [&wait]() {
            for (int i = 0; i < 5; ++i) {
                wait(1);
                std::cout << i << '\n';
            }
        };

        boost::thread t{thread};
        t.join();
    }

    std::cout << termcolor::bold << termcolor::underline
              << "Waiting for a thread with boost::scoped_thread (There is no counterpart in the standard library)"
              << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        auto thread = [&wait]() {
            for (int i = 0; i < 5; ++i) {
                wait(1);
                std::cout << i << '\n';
            }
        };

        boost::scoped_thread<> t{boost::thread{thread}};
    }

    std::cout << termcolor::bold << termcolor::underline
              << "An interruption point with boost::this_thread::sleep_for() (supported by Boost.Thread and not by the standard library)"
              << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        auto thread = [&wait]() {
            try {
                for (int i = 0; i < 5; ++i) {
                    wait(1);
                    std::cout << i << '\n';
                }
            }
            catch (boost::thread_interrupted &) {
            }
        };

        boost::thread t{thread};
        wait(3);
        t.interrupt();
        t.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "Disabling interruption points with disable_interruption"
              << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        auto thread = [&wait]() {
            boost::this_thread::disable_interruption no_interruption;
            try {
                for (int i = 0; i < 5; ++i) {
                    wait(1);
                    std::cout << i << '\n';
                }
            }
            catch (boost::thread_interrupted &) {
            }
        };

        boost::thread t{thread};
        wait(3);
        t.interrupt();
        t.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "Setting thread attributes with boost::thread::attributes"
              << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        auto thread = [&wait]() {
            try {
                for (int i = 0; i < 5; ++i) {
                    wait(1);
                    std::cout << i << '\n';
                }
            }
            catch (boost::thread_interrupted &) {
            }
        };

        boost::thread::attributes attrs;
        attrs.set_stack_size(1024);
        boost::thread t{attrs, thread};
        t.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "Detecting the thread ID and number of available processors"
              << termcolor::reset << std::endl;
    {
        std::cout << boost::this_thread::get_id() << '\n';
        std::cout << boost::thread::hardware_concurrency() << '\n';
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Synchronizing Threads"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Exclusive access with boost::mutex" << termcolor::reset
              << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        boost::mutex mutex;

        auto thread = [&wait, &mutex]() {
            using boost::this_thread::get_id;
            for (int i = 0; i < 5; ++i) {
                wait(1);
                // prevent other threads from taking ownership while a particular thread owns the mutex
                mutex.lock();
                std::cout << "Thread " << get_id() << ": " << i << std::endl;
                mutex.unlock();
            }
        };

        boost::thread t1{thread};
        boost::thread t2{thread};
        t1.join();
        t2.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::lock_guard with guaranteed mutex release"
              << termcolor::reset << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        boost::mutex mutex;

        auto thread = [&wait, &mutex]() {
            using boost::this_thread::get_id;
            for (int i = 0; i < 5; ++i) {
                wait(1);
                boost::lock_guard<boost::mutex> lock{mutex};
                std::cout << "Thread " << get_id() << ": " << i << std::endl;
            }
        };

        boost::thread t1{thread};
        boost::thread t2{thread};
        t1.join();
        t2.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "The versatile lock boost::unique_lock" << termcolor::reset
              << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        boost::timed_mutex mutex;

        auto thread1 = [&wait, &mutex]() {
            using boost::this_thread::get_id;
            for (int i = 0; i < 5; ++i) {
                wait(1);
                boost::unique_lock<boost::timed_mutex> lock{mutex};
                std::cout << "Thread " << get_id() << ": " << i << std::endl;
                boost::timed_mutex *m = lock.release();
                m->unlock();
            }
        };

        auto thread2 = [&wait, &mutex]() {
            using boost::this_thread::get_id;
            for (int i = 0; i < 5; ++i) {
                wait(1);
                boost::unique_lock<boost::timed_mutex> lock{mutex,
                                                            boost::try_to_lock};
                if (lock.owns_lock() || lock.try_lock_for(boost::chrono::seconds{1})) {
                    std::cout << "Thread " << get_id() << ": " << i << std::endl;
                }
            }
        };

        boost::thread t1{thread1};
        boost::thread t2{thread2};
        t1.join();
        t2.join();
    }

    std::cout << termcolor::bold << termcolor::underline << "Shared locks with boost::shared_lock" << termcolor::reset
              << std::endl;
    {
        auto wait = [](int seconds) {
            boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
        };

        boost::shared_mutex mutex;
        std::vector<int> random_numbers;

        auto fill = [&mutex, &wait, &random_numbers]() {
            std::srand(static_cast<unsigned int>(std::time(0)));
            for (int i = 0; i < 3; ++i) {
                boost::unique_lock<boost::shared_mutex> lock{mutex};
                random_numbers.push_back(std::rand());
                lock.unlock();
                wait(1);
            }
        };

        auto print = [&mutex, &wait, &random_numbers]() {
            for (int i = 0; i < 3; ++i) {
                wait(1);
                boost::shared_lock<boost::shared_mutex> lock{mutex};
                std::cout << random_numbers.back() << '\n';
            }
        };

        int sum = 0;

        auto count = [&mutex, &wait, &random_numbers, &sum]() {
            for (int i = 0; i < 3; ++i) {
                wait(1);
                boost::shared_lock<boost::shared_mutex> lock{mutex};
                sum += random_numbers.back();
            }
        };

        boost::thread t1{fill}, t2{print}, t3{count};
        t1.join();
        t2.join();
        t3.join();
        std::cout << "Sum: " << sum << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Condition variables with boost::condition_variable_any"
              << termcolor::reset
              << std::endl;
    {
        boost::mutex mutex;
        boost::condition_variable_any cond;
        std::vector<int> random_numbers;

        auto fill = [&mutex, &random_numbers, &cond]() {
            std::srand(static_cast<unsigned int>(std::time(0)));
            for (int i = 0; i < 3; ++i) {
                boost::unique_lock<boost::mutex> lock{mutex};
                random_numbers.push_back(std::rand());
                cond.notify_all();
                cond.wait(mutex);
            }
        };

        auto print = [&mutex, &random_numbers, &cond]() {
            std::size_t next_size = 1;
            for (int i = 0; i < 3; ++i) {
                boost::unique_lock<boost::mutex> lock{mutex};
                while (random_numbers.size() != next_size) {
                    cond.wait(mutex);
                }
                std::cout << random_numbers.back() << '\n';
                ++next_size;
                cond.notify_all();
            }
        };

        boost::thread t1{fill};
        boost::thread t2{print};
        t1.join();
        t2.join();
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Thread Local Storage"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Synchronizing multiple threads with static variables"
              << termcolor::reset << std::endl;
    {
        boost::mutex mutex;

        auto init = [&mutex]() {
            static bool done = false;
            boost::lock_guard<boost::mutex> lock{mutex};
            if (!done) {
                done = true;
                std::cout << "done" << '\n';
            }
        };

        auto thread = [&init]() {
            init();
            init();
        };

        boost::thread t[3];

        for (int i = 0; i < 3; ++i) {
            t[i] = boost::thread{thread};
        }

        for (int i = 0; i < 3; ++i) {
            t[i].join();
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Synchronizing multiple threads with TLS"
              << termcolor::reset << std::endl;
    {
        boost::mutex mutex;

        auto init = [&mutex]() {
            static boost::thread_specific_ptr<bool> tls;
            if (!tls.get()) {
                tls.reset(new bool {true});
                boost::lock_guard<boost::mutex> lock{mutex};
                std::cout << "done" << '\n';
            }
        };

        auto thread = [&init]() {
            init();
            init();
        };

        boost::thread t[3];

        for (int i = 0; i < 3; ++i) {
            t[i] = boost::thread{thread};
        }

        for (int i = 0; i < 3; ++i) {
            t[i].join();
        }
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Futures and Promises"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::future and boost::promise"
              << termcolor::reset << std::endl;
    {
        auto accumulate = [](boost::promise<int> &p) {
            int sum = 0;
            for (int i = 0; i < 5; ++i) {
                sum += i;
            }
            p.set_value(sum);
        };

        boost::promise<int> p;
        boost::future<int> f = p.get_future();
        boost::thread t{accumulate, std::ref(p)};
        std::cout << f.get() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::packaged_task" << termcolor::reset << std::endl;
    {
        auto accumulate = []() {
            int sum = 0;
            for (int i = 0; i < 5; ++i)
                sum += i;
            return sum;
        };

        boost::packaged_task<int> task{accumulate};
        boost::future<int> f = task.get_future();
        boost::thread t{std::move(task)};
        std::cout << f.get() << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::async()" << termcolor::reset << std::endl;
    {
        auto accumulate = []() {
            int sum = 0;
            for (int i = 0; i < 5; ++i)
                sum += i;
            return sum;
        };

        // It starts accumulate() in a new thread and returns a future
        boost::future<int> f = boost::async(accumulate);
        std::cout << f.get() << '\n';
    }

    return 0;
}
