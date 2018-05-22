# Set local modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/components/cmake/Modules/")

#######################################################
###       OPENSSL ENCRYPTION LIBRARY                ###
#######################################################
if (${APPLE})  # brew install openssl
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)
endif()
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
set(ALL_LIBRARIES ${ALL_LIBRARIES} ${OPENSSL_LIBRARIES})

#######################################################
###              BOOST LIBRARIES                    ###
#######################################################
# brew install boost
set(Boost_USE_STATIC_LIBS ON)
set(boost_lib_names filesystem regex system iostreams date_time chrono timer thread coroutine log program_options serialization)
find_package(Boost REQUIRED QUIET COMPONENTS ${boost_lib_names})
include_directories(${Boost_INCLUDE_DIR})
set(ALL_LIBRARIES ${ALL_LIBRARIES} ${Boost_LIBRARIES})
message("${Boost_LIBRARIES}")

#######################################################
###             POSTGRESQL LIBRARIES                ###
#######################################################
# brew install boost
# find_package(POSTGRES REQUIRED)
#include_directories(${POSTGRES_INCLUDE_DIRS})
#set(ALL_LIBRARIES ${ALL_LIBRARIES} ${POSTGRES_LIBRARIES})
#message("${POSTGRES_LIBRARIES}")

#######################################################
###                 SQLITE LIBRARIES                ###
#######################################################
# brew install boost
find_package(SQLITE3 REQUIRED)
include_directories(${SQLITE3_INCLUDE_DIRS})
set(ALL_LIBRARIES ${ALL_LIBRARIES} ${SQLITE3_LIBRARIES})
message("${SQLITE3_LIBRARIES}")