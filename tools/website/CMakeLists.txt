# SECURE
# Generate key
# openssl genrsa -des3 -out server.key 1024
# Generate certificate (Common Name is sth. like public.akadia.com)
# openssl req -new -key server.key -out server.csr
# Remove password from key (leave access to the root user only)
# cp server.key server.key.org
# openssl rsa -in server.key.org -out server.key
# Creating certificate
# openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt

# PATHS
set(WEB_ROOT_PATH http://localhost:8080/)
set(HTTPS_KEYS_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/controller/keys/)
set(ASSETS_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/model/assets/)
set(TEMPLATES_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/view/templates/)
set(DATABASE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/model/data)
set(USER_AGENT_PARSER_ROOT_PATH ${CMAKE_SOURCE_DIR}/components/uap-cpp)

configure_file(environment.h.in environment.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES main.cpp)

add_executable(w++ ${SOURCE_FILES})
target_link_libraries(w++ ${ALL_LIBRARIES})
