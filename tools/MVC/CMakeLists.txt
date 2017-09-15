configure_file(environment.h.in environment.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES main.cpp)

file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/view/templates
        DESTINATION ${CMAKE_BINARY_DIR}/bin/
        PATTERN .svn EXCLUDE
        )

add_executable(wpp_app ${SOURCE_FILES})
target_link_libraries(wpp_app ${ALL_LIBRARIES} wpp_lib)