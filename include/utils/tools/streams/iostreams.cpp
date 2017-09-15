#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/filter/counter.hpp>
//#include <boost/iostreams/filter/zlib.hpp>
#include <boost/regex.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace boost::iostreams;

int main()
{
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Devices" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using an array as a device with boost::iostreams::array_sink" << termcolor::reset << std::endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        stream<array_sink> os{sink};
        os << "Boost" << std::flush;
        std::cout.write(buffer, 5);
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Using an array as a device with boost::iostreams::array_source" << termcolor::reset << std::endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        stream<array_sink> os{sink};
        os << "Boost" << std::endl;

        array_source source{buffer};
        stream<array_source> is{source};
        std::string s;
        is >> s;
        std::cout << s << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a vector as a device with boost::iostreams::back_insert_device" << termcolor::reset << std::endl;
    {
        std::vector<char> v;
        back_insert_device<std::vector<char>> sink{v};
        stream<back_insert_device<std::vector<char>>> os{sink};
        os << "Boost" << std::endl;

        array_source source{v.data(), v.size()};
        stream<array_source> is{source};
        std::string s;
        is >> s;
        std::cout << s << '\n';
    }

    std::cout << termcolor::bold << termcolor::underline << "Using a file as a device with boost::iostreams::file_source" << termcolor::reset << std::endl;
    {
        file_source f{"main.cpp"};
        if (f.is_open())
        {
            stream<file_source> is{f};
            std::cout << is.rdbuf() << '\n';
            f.close();
        }
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Filters" << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Using boost::iostreams::regex_filter" << termcolor::reset << std::endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        filtering_ostream os;
        os.push(regex_filter{boost::regex{"Bo+st"}, "C++"});
        os.push(sink);
        os << "Boost" << std::flush;
        os.pop();
        std::cout.write(buffer, 3);
    }

    std::cout << termcolor::bold << termcolor::underline << "Accessing filters in boost::iostreams::filtering_ostream" << termcolor::reset << std::endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        filtering_ostream os;
        os.push(counter{});
        os.push(sink);
        os << "Boost" << std::flush;
        os.pop();
        counter *c = os.component<counter>(0);
        std::cout << c->characters() << '\n';
        std::cout << c->lines() << '\n';
    }

    //std::cout << termcolor::bold << termcolor::underline << "Writing and reading data compressed with ZLIB" << termcolor::reset << std::endl;
    //{
    //    std::vector<char> v;
    //    back_insert_device<std::vector<char>> snk{v};
    //    filtering_ostream os;
    //    os.push(zlib_compressor{});
    //    os.push(snk);
    //    os << "Boost" << std::flush;
    //    os.pop();
    //
    //    array_source src{v.data(), v.size()};
    //    filtering_istream is;
    //    is.push(zlib_decompressor{});
    //    is.push(src);
    //    std::string s;
    //    is >> s;
    //    std::cout << s << '\n';
    //}

    return 0;
}
