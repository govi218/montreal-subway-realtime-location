# STM Realtime Location

This project uses the [STM](https://www.stm.info/en) [GTFS API](https://gtfs.org/) to retrieve the realtime location of STM trains.

## Prerequisites

- CMake (version 3.12 or above)
- Protobuf (make sure it's installed on your system)
- libcurl (make sure it's installed on your system)

## Build Instructions

1. Clone or download this repository
2. Download and extract the information files from [STM](http://www.stm.info/sites/default/files/gtfs/gtfs_stm.zip); extract them to `stm_data`
3. Navigate to the project directory
4. Create a build directory: `mkdir build && cd build`
5. Generate the build files: `cmake ..`
6. Build the project: `cmake --build .`
7. Run the executable `HttpPostProtoExample`
