#include <iostream>
#include "termcolor/termcolor.hpp"
#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

//using namespace std;
using namespace boost::filesystem;

template<typename T> void printElement(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}


int main() {
    // set path
    path p{"/Users/alandefreitas/Sync/Downloads"};
    p /= "52374.pdf";

    // get path string properties
    std::cout << std::endl;
    std::cout << "p: " << p << std::endl;
    std::cout << "p.root_name(): " << p.root_name() << std::endl;
    std::cout << "p.root_directory(): " << p.root_directory() << std::endl;
    std::cout << "p.root_path(): " << p.root_path() << std::endl;
    std::cout << "p.relative_path(): " << p.relative_path() << std::endl;
    std::cout << "p.parent_path(): " << p.parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path(): " << p.parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [3]: " << p.parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [4]: " << p.parent_path().parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [5]: " << p.parent_path().parent_path().parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [6]: " << p.parent_path().parent_path().parent_path().parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [7]: " << p.parent_path().parent_path().parent_path().parent_path().parent_path().parent_path() << std::endl;
    std::cout << "p.parent_path().parent_path() [8]: " << p.parent_path().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path() << std::endl;
    std::cout << "p.filename(): " << p.filename() << std::endl;
    std::cout << "p.stem(): " << p.stem() << std::endl;
    std::cout << "p.extension(): " << p.extension() << std::endl;
    for (const path &pp : p) {
        std::cout << pp << std::endl;
    }

    // get status of file in the path
    file_status s = status(p);
    std::cout << std::boolalpha << exists(s) << std::endl;
    if (exists(s)) {
        std::cout << std::boolalpha << is_directory(s) << std::endl;
        std::cout << std::boolalpha << is_regular_file(s) << std::endl;
        std::cout << std::boolalpha << is_symlink(s) << std::endl;

    }

    // file size
    boost::system::error_code ec;
    boost::uintmax_t filesize = file_size(p, ec);
    if (!ec) {
        std::cout << filesize << std::endl;
    } else {
        std::cout << ec << std::endl;
    }

    // file properties
    try {
        std::time_t t = last_write_time(p);
        std::cout << std::ctime(&t) << std::endl;
    }
    catch (filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }

    // system space
    try {
        space_info s = space(p);
        std::cout << s.capacity << std::endl;
        std::cout << s.free << std::endl;
        std::cout << s.available << std::endl;
    }
    catch (filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }


    path cur{current_path()};
    cur /= "resources";
    std::cout << "Current path is -> " << cur << std::endl;

    // create directory
    try {
        // try to create the directory on the path
        if (create_directory(cur)) {
            std::cout << "We can create directory" << std::endl;
            // rename what we created
            rename(cur, absolute("latex_resources"), ec);
            if (!ec) {
                std::cout << cur << std::endl;
            } else {
                std::cout << ec << std::endl;
            }
            boost::filesystem::remove(absolute("latex_resources"));
            // Additional functions such as create_symlink() to create symbolic links or
            // copy_file() and
            // copy_directory() to copy files and directories are available as well.
        } else {
            std::cout << "We couldn't create directory" << cur << std::endl;
        }
    }
    catch (filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }

    // find out a path based on a file name or path section
    try {
        std::cout << absolute("Make") << std::endl;
    }
    catch (filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }

    // iterate over files
    p = path{current_path()};
    {
        directory_iterator it{p};
        while (it != directory_iterator{}) {
            std::cout << *(it++) << '\n';
        }
    }
    {
        recursive_directory_iterator it{p};
        while (it != recursive_directory_iterator{}) {
            std::cout << *(it++) << '\n';
        }
    }

    // file streams
    p = path{"main.tex"};
    ofstream ofs{p};
    ofs << "Hello, world!\n";

    using namespace std;

    // colors
    //cout << "\x1b[%dm" << "Hello world" << endl; // where %d is one of the following values for commonly supported colors:
    cout << "\x1b[0m" << "Hello world (Reset)" << endl;
    cout << "\x1b[1m" << "Hello world" << "\x1b[0m" << endl;
    cout << "\x1b[4m" << "Hello world" << "\x1b[0m" << endl;
    cout << "\x1b[1;4m" << "Hello world" << "\x1b[0m" << endl; // to change multiple attributes at once, you can specify them all at once
    // black, red, green, yellow, blue, magenta, cyan, and white text
    for (int i = 30; i <= 37 ; ++i) {
        cout << "\x1b["+to_string(i)+"m" << "Hello world" << "\x1b[0m" << endl;
    }
    // black, red, green, yellow, blue, magenta, cyan, and white background
    for (int i = 40; i <= 47 ; ++i) {
        cout << "\x1b["+to_string(i)+"m" << "Hello world" << "\x1b[0m" << endl;
    }
    cout << "\x1b[0m" << "Hello world (Reset)" << "\x1b[0m" << endl;

}