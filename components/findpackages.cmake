# Find packages and (if not found) do something about it

# Local modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/components/cmake/Modules/")

# find packages for web
find_package(Tcmalloc)
find_package(Threads)
find_package(OpenSSL)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

# boost
if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package( Boost COMPONENTS system thread regex REQUIRED )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pedantic -Wextra")
    find_package( Boost COMPONENTS system thread REQUIRED )
endif()

include_directories(${Boost_INCLUDE_DIR})
set(ALL_LIBRARIES ${Boost_LIBRARIES})

# Poco from conan on mac
if (${APPLE})
    include(components/conan.cmake)
    set(ALL_LIBRARIES ${ALL_LIBRARIES} ${CONAN_LIBS})
else()
    find_package(Poco REQUIRED COMPONENTS Util Foundation XML Zip Crypto Data Net)
    include_directories(${Poco_INCLUDE_DIR})
    set(ALL_LIBRARIES ${ALL_LIBRARIES} ${Poco_LIBRARIES})
endif()