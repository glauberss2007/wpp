#######################################################
###                 GOOGLE BENCHMARK                ###
#######################################################
add_subdirectory(google_benchmark)

#######################################################
###         YAML PARSER FOR USER-AGENT PARSER        ##
#######################################################
add_subdirectory(yaml-cpp)
include_directories(yaml-cpp/include/)

#######################################################
###                 USER-AGENT PARSER                ##
#######################################################
add_library(ua-parser ${CMAKE_SOURCE_DIR}/components/uap-cpp/UaParser.cpp)
target_link_libraries(ua-parser yaml-cpp)
set(ALL_LIBRARIES ${ALL_LIBRARIES} ua-parser)

