set(SOURCE_FILES benchmarks.cpp ${WPP_SRC_FILES})

include_directories(${CMAKE_SRC_DIRECTORY}/components/google_benchmark/include)

add_executable(benchmarks ${SOURCE_FILES})
target_link_libraries(benchmarks ${ALL_LIBRARIES} benchmark wpp)