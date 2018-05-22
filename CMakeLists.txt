#######################################################
### CMAKE SETTINGS                                  ###
#######################################################
cmake_minimum_required(VERSION 3.6)
project(wpp)
if (${APPLE})
    set(CMAKE_CXX_STANDARD 14)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
add_compile_options(-Wno-deprecated-declarations -Wno-trigraphs -Wno-deprecated-register -Wno-parentheses)

#######################################################
### W++ SETTINGS                                    ###
#######################################################
set(WPP_ENABLE_TESTING ON)
# define settings
include(settings.cmake)

#######################################################
### EXTERNAL COMPONENTS                             ###
#######################################################
## External components
# Locate 3rd party libs on the computer
include(components/findpackages.cmake)
# Compile other 3rd party cmake projects
add_subdirectory(components)

#######################################################
### INCLUDES                                        ###
#######################################################
# wpp include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/w++)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/utils/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/lru-cache/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/components/uap-cpp/)

#######################################################
### SOURCES                                         ###
#######################################################
# wpp sources
#file(GLOB WPP_SRC_FILES lib/w++/*.cpp)

#######################################################
### LIBRARIES                                       ###
#######################################################
# create library that will be used by all executables (mvcs, tests, and benchmarks)
#add_library(wpp_lib STATIC ${3rdPARTY_SRC} ${WPP_SRC_FILES})
#set(ALL_LIBRARIES ${ALL_LIBRARIES} wpp_lib)
set(ALL_LIBRARIES ${ALL_LIBRARIES} ua-parser)

#######################################################
### EXECUTABLES                                     ###
#######################################################
# wpp executables
add_subdirectory(tools)
#add_subdirectory(include/utils)

