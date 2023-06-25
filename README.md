# HTTP POST with Protobuf Example

This C++ project demonstrates how to make an HTTP POST request to a specified server and deserialize the response as a Protobuf message.

## Prerequisites

- CMake (version 3.12 or above)
- Protobuf (make sure it's installed on your system)
- libcurl (make sure it's installed on your system)

## Build Instructions

1. Clone or download this repository.
2. Navigate to the project directory.
3. Create a build directory: `mkdir build && cd build`.
4. Generate the build files: `cmake ..`.
5. Build the project: `cmake --build .`.

## Run Instructions

After building the project, you can run the executable `HttpPostProtoExample`. Make sure to replace the URL in `main.cc` with the actual server URL you want to send the HTTP POST request to.
