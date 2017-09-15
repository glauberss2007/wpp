configure_file(environment.h.in environment.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES main.cpp ${WPP_SRC_FILES})

#file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/view/templates
#        DESTINATION ${CMAKE_BINARY_DIR}/bin/
#        PATTERN .svn EXCLUDE
#        )

add_executable(scratch ${SOURCE_FILES})
target_link_libraries(scratch ${ALL_LIBRARIES} wpp)