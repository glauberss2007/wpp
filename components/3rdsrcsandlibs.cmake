include_directories(${CMAKE_SOURCE_DIR}/components/bustache/include)
file(GLOB BUSTACHE_SRC_FILES ${CMAKE_SOURCE_DIR}/components/bustache/src/*.cpp)

set(3rdPARTY_SRC ${BUSTACHE_SRC_FILES})

include_directories(${CMAKE_SOURCE_DIR}/components/r3/include)
