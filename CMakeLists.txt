cmake_minimum_required(VERSION 3.6)

project(wpp)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wno-deprecated-declarations -Wno-trigraphs)

# External components from package managers
include(components/findpackages.cmake)
add_subdirectory(components)

# wpp include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/wpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/crow)

# wpp sources
file(GLOB WPP_SRC_FILES lib/wpp/*.cpp)

# wpp executables
add_subdirectory(tools)
