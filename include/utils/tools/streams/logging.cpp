#include <vector>
#include <iostream>
#include "utils/logging.h"

int main() {
    // this is the lowest level
    utils::default_log_level::default_level = utils::log_level::debug;
    utils::log::info << "Information on the program..." << std::endl;
    // to make it more convenient
    using log = utils::log;
    log::critical << "Really serious problem!" << std::endl;
    log::debug << "This won't show up" << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::info << "Some normal information on what's happening" << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::warning << "This is something you might want to put in your todo list!" << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::error << "Ooooops... There's an error in your code." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::critical << "THERE IS A SERIOUS ERROR IN YOU CODE." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;
    log::debug << "Details..." << std::endl;

    return 0;
}
