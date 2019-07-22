set(ENABLE_DEBUG 1)

# debug = 0,info=1,warning=2,error=1,critical
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    set(WPP_LOG_LEVEL 0)
else ()
    set(WPP_LOG_LEVEL 1)
endif()

set(ENABLE_LOGGING 1)

set(WPP_ENABLE_SSL 1)

set(_MSC_VERSION 0)

find_package(Threads)
link_libraries(${CMAKE_THREAD_LIBS_INIT})