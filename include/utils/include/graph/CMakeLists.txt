cmake_minimum_required(VERSION 3.6)
project(tree)

set(CMAKE_CXX_STANDARD 14)

# see https://cmake.org/cmake/help/v3.5/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(tree ${SOURCE_FILES})