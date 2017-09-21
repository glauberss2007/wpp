#add_subdirectory(MVC)
add_subdirectory(website)

if (WPP_ENABLE_TESTING)
    add_subdirectory(tests)
endif()


