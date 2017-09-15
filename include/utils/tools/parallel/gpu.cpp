// See the tutorial at: http://www.boost.org/doc/libs/1_64_0/libs/compute/doc/html/index.html
// See the presentation at: http://www.iwocl.org/wp-content/uploads/iwocl-2016-boost-compute.pdf

// TODO: This file has a few examples on GPUs. We can include these concepts little by little in our algorithms
// Book: Massively Parallel Evolutionary Computation on GPGPUs
// http://www.springer.com/la/book/9783642379581

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
#include <math.h>

#include <boost/compute.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/core.hpp>

#include <boost/timer/timer.hpp>

#include "utils/container_overloads.h"
#include "termcolor/termcolor.hpp"
#include "utils/progress_bar.h"


int main()
{
    namespace compute = boost::compute;
    using namespace utils;

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "GPU OpenCL Compute"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Get default GPU device and setup context" << termcolor::reset << std::endl;
    {
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device, compute::command_queue::enable_profiling);
        std::cout << "timer1 considers time to copy data" << std::endl;
        std::cout << "timer2 ignores time to copy data" << std::endl;
        boost::timer::cpu_timer timer;
        boost::timer::cpu_timer timer2;
        timer.stop();
        timer2.stop();
        std::string result1;
        std::string result2;
        std::string result3;

        int goal = 1000;
        progress_bar p(goal,20);
        std::cout << p.bar() << std::endl;
        for (int i = 0; i < goal; ++i) {
            std::cout << p.star(i);
            // generate random data on the host
            std::vector<float> host_vector(100000);
            std::generate(host_vector.begin(), host_vector.end(), rand);

            // print data
            // std::cout << "Host data" << host_vector << std::endl;

            timer.resume();

            // create a vector on the device
            compute::vector<float> device_vector(host_vector.size(), context);

            // transfer data from the host to the device
            compute::copy(
                    host_vector.begin(), host_vector.end(), device_vector.begin(), queue
            );

            timer2.resume();

            // calculate the square-root of each element in-place
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );
            compute::transform(
                    device_vector.begin(),
                    device_vector.end(),
                    device_vector.begin(),
                    compute::sqrt<float>(),
                    queue
            );

            timer2.stop();

            // Copy values back to the host
            compute::copy(
                    device_vector.begin(), device_vector.end(), host_vector.begin(), queue
            );

            timer.stop();

            // std::cout << timer.format() << '\n';
            // std::cout << timer2.format() << '\n';

            // print values
            // std::cout << "Host data returned" << host_vector << std::endl;

        }
        std::cout << std::endl;
        result1 = timer.format();
        result3 = timer2.format();
        timer.start();
        timer.stop();
        std::cout << termcolor::bold << termcolor::underline << "Transforming data sequentially for comparison" << termcolor::reset << std::endl;

        p.reset(goal,20);
        std::cout << p.bar() << std::endl;
        for (int i = 0; i < goal; ++i) {
            std::cout << p.star(i);
            // generate random data on the host
            std::vector<float> host_vector(100000);
            std::generate(host_vector.begin(), host_vector.end(), rand);

            // std::cout << "Host data: " << host_vector << std::endl;

            timer.resume();

            // calculate the square-root of each element in-place
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );
            std::transform(
                    host_vector.begin(),
                    host_vector.end(),
                    host_vector.begin(),
                    [](float x){return sqrt(x);}
            );

            timer.stop();

            // std::cout << timer.format() << '\n';

            // std::cout << "Host data returned" << host_vector << std::endl;

        }
        result2 = timer.format();

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Time sync GPU: " << result1 << std::endl;
        std::cout << "Time async GPU" << result3 << std::endl;
        std::cout << "Time sequential: " << result2 << std::endl;

        return 0;


    }


    // hello world
    {
        // get the default device
        compute::device device = compute::system::default_device();

        // print the device's name
        std::cout << "Device name: " << device.name() << std::endl;
        std::cout << "Vendor: " << device.vendor() << std::endl;
        std::cout << "Compute units: " << device.compute_units() << std::endl;
        std::cout << "Clock frequency: " << device.clock_frequency() << std::endl;
        std::cout << "Driver Version: " << device.driver_version() << std::endl;
        std::cout << "Global memory size: " << device.global_memory_size() << std::endl;
        std::cout << "Local memory size: " << device.local_memory_size() << std::endl;
        std::cout << "Device id: " << device.id() << std::endl;
        std::cout << "Driver version: " << device.driver_version() << std::endl;
        std::cout << "Profile: " << device.profile() << std::endl;

    }

    // transfering data
    {
        // get default device and setup context
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device);

        // create data array on host
        int host_data[] = { 1, 3, 5, 7, 9 };

        // create vector on device
        compute::vector<int> device_vector(5, context);

        // copy from host to device
        compute::copy(
                host_data, host_data + 5, device_vector.begin(), queue
        );

        // create vector on host
        std::vector<int> host_vector(5);

        // copy data back to host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        std::cout << "Copying data: " << std::endl;
        for (auto &item : host_vector) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // transforming data on the device
    {
        // get default device and setup context
        compute::device device = compute::system::default_device();
        compute::context context(device);
        compute::command_queue queue(context, device);

        // generate random data on the host
        std::vector<float> host_vector(10000);
        std::generate(host_vector.begin(), host_vector.end(), rand);
        // print the host vector
        std::cout << "Random Floats: " << std::endl;
        for (auto &item : host_vector) {
            std::cout << item << " ";
        }
        std::cout << std::endl;

        // create a vector on the device
        compute::vector<float> device_vector(host_vector.size(), context);

        // transfer data from the host to the device
        compute::copy(
                host_vector.begin(), host_vector.end(), device_vector.begin(), queue
        );

        // calculate the square-root of each element in-place
        compute::transform(
                device_vector.begin(),
                device_vector.end(),
                device_vector.begin(),
                compute::sqrt<float>(),
                queue
        );

        // copy values back to the host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        std::cout << "Square roots: " << std::endl;
        for (auto &item : host_vector) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // sorting data
    {
        // get the default compute device
        compute::device gpu = compute::system::default_device();

        // create a compute context and command queue
        compute::context ctx(gpu);
        compute::command_queue queue(ctx, gpu);

        // generate random numbers on the host
        std::vector<float> host_vector(1000000);
        std::generate(host_vector.begin(), host_vector.end(), rand);

        // create vector on the device
        compute::vector<float> device_vector(1000000, ctx);

        // copy data to the device
        compute::copy(
                host_vector.begin(), host_vector.end(), device_vector.begin(), queue
        );

        // sort data on the device
        compute::sort(
                device_vector.begin(), device_vector.end(), queue
        );

        // copy data back to the host
        compute::copy(
                device_vector.begin(), device_vector.end(), host_vector.begin(), queue
        );

        // print the host vector
        std::cout << "Sorted data: " << std::endl;
        for (auto &item : host_vector) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}