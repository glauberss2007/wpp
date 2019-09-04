#######################################################
### CMAKE SETTINGS                                  ###
#######################################################
cmake_minimum_required(VERSION 3.6)
project(wpp)
set(CMAKE_CXX_STANDARD 17)
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
set(WPP_SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/application.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/cache.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/cookie_parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/crypto.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/database.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/detect_ssl.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/encryption.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/enums.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/guard.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/http_server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/methods.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/query_string.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/regex_order.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/request.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/request.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/response.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/response.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/route_properties.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/routing_parameters.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/server_certificate.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/ssl_stream.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/trie.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/utility.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/w++/w++
        )

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

