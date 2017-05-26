set(SOURCE_FILES MVC/main.cpp ${WPP_SRC_FILES})


file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/MVC/view/templates
        DESTINATION ${CMAKE_BINARY_DIR}/bin/
        PATTERN .svn EXCLUDE
        )


add_executable(wpp ${SOURCE_FILES})
target_link_libraries(wpp ${ALL_LIBRARIES})