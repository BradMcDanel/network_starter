cmake_minimum_required(VERSION 3.1)
project(network_starter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -O2 -Wextra")

set(SOURCE_FILES )

add_subdirectory(third_party/kissnet)
include_directories(third_party/kissnet)

add_executable(server src/server.cpp ${SOURCE_FILES})
target_include_directories(server PRIVATE include)
target_link_libraries(kissnet)

add_executable(client src/client.cpp ${SOURCE_FILES})
target_include_directories(client PRIVATE include)
target_link_libraries(kissnet)
