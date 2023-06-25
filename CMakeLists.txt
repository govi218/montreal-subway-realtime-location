cmake_minimum_required(VERSION 3.12)
project(HttpPostProtoExample)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

add_executable(HttpPostProtoExample main.cc protobuf/gtfs-realtime.proto3.pb.cc)
target_link_libraries(HttpPostProtoExample ${Protobuf_LIBRARIES} curl)
