# STM Realtime Location

This project uses the [STM](https://www.stm.info/en) [GTFS API](https://gtfs.org/) to retrieve the realtime location of STM trains.

## Prerequisites

- CMake (version 3.12 or above)
- Protobuf (make sure it's installed on your system)
- libcurl (make sure it's installed on your system)

## Build Instructions

1. Clone or download this repository
2. Navigate to the project directory
3. Create a build directory: `mkdir build && cd build`
4. Generate the build files: `cmake ..`
5. Build the project: `cmake --build .`
6. Run the executable `HttpPostProtoExample`
