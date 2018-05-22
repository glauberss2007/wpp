set(WEB_ROOT_PATH http://localhost:8080/)
set(ASSETS_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/model/assets/)
set(TEMPLATES_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/view/templates/)
set(DATABASE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/model/data)
set(USER_AGENT_PARSER_ROOT_PATH ${CMAKE_SOURCE_DIR}/components/uap-cpp)

configure_file(environment.h.in environment.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#set(SOURCE_FILES main.cpp)
#add_executable(sqlorm ${SOURCE_FILES})
#target_link_libraries(sqlorm ${ALL_LIBRARIES})

set(SOURCE_FILES data_object.cpp)
add_executable(data_object ${SOURCE_FILES})
target_link_libraries(data_object ${ALL_LIBRARIES} ${SQLITE3_LIBRARY})
