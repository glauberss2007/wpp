cmake_minimum_required(VERSION 3.6)

project(wpp)

if (${APPLE})
    set(CMAKE_CXX_STANDARD 14)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_compile_options(-Wno-deprecated-declarations -Wno-trigraphs -Wno-deprecated-register)

# Settings
set(WPP_ENABLE_TESTING ON)

## External components
# Locate 3rd party libs on the computer
include(components/findpackages.cmake)
# Compile other 3rd party cmake projects
add_subdirectory(components)
# Add 3d party scrs and headers
include(components/3rdsrcsandlibs.cmake)

# define settings
include(settings.cmake)

# wpp include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/w++)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/utils/include)

# wpp sources
file(GLOB WPP_SRC_FILES lib/w++/*.cpp)

# create library that will be used by all executables (mvcs, tests, and benchmarks)
# but there are no cpps so there is nothing to create
add_library(wpp_lib STATIC ${3rdPARTY_SRC} ${WPP_SRC_FILES})

# wpp executables
add_subdirectory(tools)
add_subdirectory(include/utils)

