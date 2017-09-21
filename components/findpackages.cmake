# Find packages and (if not found) do something about it

# Local modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/components/cmake/Modules/")

# find packages for web
#find_package(Tcmalloc)
find_package(Threads)
find_package(OpenSSL)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

# boost
set(Boost_USE_STATIC_LIBS ON)
set(boost_lib_names filesystem regex system iostreams date_time chrono timer thread coroutine log program_options serialization)
find_package(Boost REQUIRED COMPONENTS ${boost_lib_names})
#if (MSVC)
#    set(Boost_USE_STATIC_LIBS "On")
#    find_package( Boost COMPONENTS system iostreams thread regex REQUIRED )
#else()
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pedantic -Wextra")
#    find_package( Boost COMPONENTS system iostreams thread REQUIRED )
#endif()
include_directories(${Boost_INCLUDE_DIR})
set(ALL_LIBRARIES ${Boost_LIBRARIES})

find_package(PCRE REQUIRED)
set(ALL_LIBRARIES ${ALL_LIBRARIES} ${PCRE_LIBRARIES})


