cmake_minimum_required(VERSION 3.12)
project(HttpPostProtoExample)

set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

message(${Protobuf_INCLUDE_DIRS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--copy-dt-needed-entries")

add_executable(HttpPostProtoExample main.cc protobuf/gtfs-realtime.pb.cc)
target_link_libraries(HttpPostProtoExample ${Protobuf_LIBRARIES} curl)
