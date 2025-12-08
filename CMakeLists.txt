
cmake_minimum_required(VERSION 3.20)
project(proto_engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config to find SDL3
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)

include_directories(${SDL3_INCLUDE_DIRS})
link_directories(${SDL3_LIBRARY_DIRS})

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(proto_engine ${SOURCES})

# Link SDL3
target_link_libraries(proto_engine ${SDL3_LIBRARIES})

