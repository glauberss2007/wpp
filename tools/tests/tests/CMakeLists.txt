function(add_catch_test name)
    set(TEST_TARGET test_${name})
    add_executable(${TEST_TARGET} ${name}.cpp)
    target_link_libraries(${TEST_TARGET} ${ALL_LIBRARIES} wpp)
    add_test(${TEST_TARGET} ${TEST_TARGET})
endfunction()

add_catch_test(unittests)