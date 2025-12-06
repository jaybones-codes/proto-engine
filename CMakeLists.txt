cmake_minimum_required(VERSION 3.20)
project(proto_engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(proto_engine ${SOURCES})

# Link SDL3
target_link_libraries(proto_engine PRIVATE SDL3::SDL3)

